cmake_minimum_required(VERSION 3.30)

project(LazarOpenGLEngine3DTemplateMinGW LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VENDOR_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/include")
set(VENDOR_LIB_DIR "${PROJECT_SOURCE_DIR}/libraries/lib")
set(VENDOR_DLL_DIR "${PROJECT_SOURCE_DIR}/libraries/dll")
set(VENDOR_SRC_DIR "${PROJECT_SOURCE_DIR}/libraries/src")

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/*.hpp"
)

add_executable(main
	${PROJECT_SOURCES}
	${VENDOR_SRC_DIR}/glad/glad.c
)

target_include_directories(main PRIVATE
	${VENDOR_INCLUDE_DIR}
)

target_link_directories(main PRIVATE
	${VENDOR_LIB_DIR}/glfw3
	${VENDOR_LIB_DIR}/assimp
)

target_link_libraries(main PRIVATE
	glfw3
	assimp
	z
)

if(UNIX AND NOT APPLE)
	target_link_libraries(main PRIVATE
		dl           # dynamic loading
		pthread      # threading
		X11          # core X11
		Xrandr       # monitor resolution handling
		Xi           # raw input
		Xxf86vm      # video mode switching
		Xcursor      # cursors
		GL           # OpenGL
	)
endif()

if(WIN32)
	add_custom_command(TARGET main POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${VENDOR_DLL_DIR}" $<TARGET_FILE_DIR:main>
	)
endif()
