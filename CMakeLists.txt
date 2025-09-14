cmake_minimum_required(VERSION 3.30.4)
project(LazarOpenGLEngine3DTemplate LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32 AND MINGW)
	set(VENDOR_DIR "${CMAKE_SOURCE_DIR}/libraries/windows-mingw")
elseif(WIN32 AND MSVC)
	set(VENDOR_DIR "${CMAKE_SOURCE_DIR}/libraries/windows-msvc")
elseif(UNIX AND NOT APPLE)
	set(VENDOR_DIR "${CMAKE_SOURCE_DIR}/libraries/linux-gcc")
else()
	message(FATAL_ERROR "Unsupported platform/toolchain")
endif()

set(VENDOR_INCLUDE_DIR "${VENDOR_DIR}/include")
set(VENDOR_LIB_DIR "${VENDOR_DIR}/lib")
set(VENDOR_DLL_DIR "${VENDOR_DIR}/dll")
set(VENDOR_SRC_DIR "${VENDOR_DIR}/src")

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_SOURCE_DIR}/src/*.hpp"
)
list(APPEND PROJECT_SOURCES "${VENDOR_SRC_DIR}/glad/glad.c")

add_executable(main ${PROJECT_SOURCES})
target_include_directories(main PRIVATE ${VENDOR_INCLUDE_DIR})

if(WIN32)
	target_link_directories(main PRIVATE
		${VENDOR_LIB_DIR}/GLFW
		${VENDOR_LIB_DIR}/assimp
		${VENDOR_LIB_DIR}/z
	)

	target_link_libraries(main PRIVATE
		glfw3
		assimp
		zs
		opengl32
	)

	add_custom_command(TARGET main POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${VENDOR_DLL_DIR}" $<TARGET_FILE_DIR:main>
	)

elseif(UNIX AND NOT APPLE)
	target_link_directories(main PRIVATE
		${VENDOR_LIB_DIR}/GLFW
		${VENDOR_LIB_DIR}/assimp
		${VENDOR_LIB_DIR}/z
	)

	target_link_libraries(main PRIVATE
		glfw3
		assimp
		z
		dl
		pthread
		X11
		Xrandr
		Xi
		Xxf86vm
		Xcursor
		GL
	)
endif()
