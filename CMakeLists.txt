cmake_minimum_required(VERSION 3.30)
project(engine)

# -------------------------------
# C++ standard
# -------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------
# Output directories
# -------------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# -------------------------------
# Detect platform and compiler
# -------------------------------
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor/linux-gcc")
    set(PLATFORM_STATIC_EXT "a")
    set(PLATFORM_SHARED_EXT "so")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor/windows-msvc")
    else()
        set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor/windows-mingw")
    endif()
    set(PLATFORM_STATIC_EXT "lib")
    set(PLATFORM_SHARED_EXT "dll")
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

# -------------------------------
# Include directories
# -------------------------------
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${VENDOR_DIR}/include)
include_directories(${VENDOR_DIR}/ext-src) # glad headers

# -------------------------------
# Source files
# -------------------------------
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# -------------------------------
# Add platform-specific glad.c
# -------------------------------
if (EXISTS "${VENDOR_DIR}/ext-src/glad/glad.c")
    list(APPEND SOURCES "${VENDOR_DIR}/ext-src/glad/glad.c")
else()
    message(FATAL_ERROR "glad.c not found in ${VENDOR_DIR}/ext-src/glad")
endif()

# -------------------------------
# Create executable
# -------------------------------
add_executable(engine ${SOURCES})

# -------------------------------
# Collect vendor static libraries
# -------------------------------
function(collect_vendor_static_libraries out_var)
    set(libs "")
    file(GLOB_RECURSE STATIC_LIBS ${VENDOR_DIR}/static-lib/*/*.${PLATFORM_STATIC_EXT})
    list(APPEND libs ${STATIC_LIBS})
    set(${out_var} ${libs} PARENT_SCOPE)
endfunction()

collect_vendor_static_libraries(VENDOR_STATIC_LIBS)

# -------------------------------
# Link vendor static libraries
# -------------------------------
target_link_libraries(engine PRIVATE ${VENDOR_STATIC_LIBS})

# -------------------------------
# Linux system libraries
# -------------------------------
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(engine PRIVATE dl pthread X11 Xrandr Xi)
endif()

# -------------------------------
# Smart OpenGL detection
# -------------------------------
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(OpenGL REQUIRED)
    target_link_libraries(engine PRIVATE OpenGL::GL)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(engine PRIVATE opengl32)
endif()

# -------------------------------
# Copy resources after build (file by file for better change detection)
# -------------------------------
file(GLOB_RECURSE RESOURCE_FILES "${PROJECT_SOURCE_DIR}/res/*")
foreach(resource ${RESOURCE_FILES})
    # Get relative path from res directory
    file(RELATIVE_PATH rel_path "${PROJECT_SOURCE_DIR}/res" ${resource})

    add_custom_command(TARGET engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:engine>/res
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${resource} $<TARGET_FILE_DIR:engine>/res/${rel_path}
        COMMENT "Copying resource: ${rel_path}"
    )
endforeach()

# -------------------------------
# Print debug info about what was found
# -------------------------------
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Vendor directory: ${VENDOR_DIR}")
message(STATUS "Static library extension: ${PLATFORM_STATIC_EXT}")
message(STATUS "Shared library extension: ${PLATFORM_SHARED_EXT}")
list(LENGTH VENDOR_STATIC_LIBS VENDOR_STATIC_LIBS_COUNT)
message(STATUS "Found ${VENDOR_STATIC_LIBS_COUNT} static libraries")
