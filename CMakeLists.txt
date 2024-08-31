cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Core3D)

# source
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB IMGUI_SRC_FILES vendor/imgui/*.cpp)
add_executable(${PROJECT_NAME}
  ${SRC_FILES}
  ${IMGUI_SRC_FILES}
  ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
  ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
  )

# include dir
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/vendor
  ${CMAKE_SOURCE_DIR}/vendor/assimp
  ${CMAKE_SOURCE_DIR}/vendor/glm
  ${CMAKE_SOURCE_DIR}/vendor/glew
  ${CMAKE_SOURCE_DIR}/vendor/GLFW
  ${CMAKE_SOURCE_DIR}/vendor/imgui
  ${CMAKE_SOURCE_DIR}/vendor/imgui/backends
  ${CMAKE_SOURCE_DIR}/vendor/stb
  ${CMAKE_SOURCE_DIR}/src
  )

# windows
if(WIN32)
  target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib-vc2022
    ${CMAKE_SOURCE_DIR}/dependencies/glew/lib/Release/x64
    ${CMAKE_SOURCE_DIR}/dependencies/assimp
    )
  target_link_libraries(${PROJECT_NAME} glfw3 glew32 assimp-vc143-mt opengl32)
# mac
elseif(APPLE)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for lsp
  set(CMAKE_CXX_FLAGS_DEBUG "-g") # for debug symbols
  set(CMAKE_C_FLAGS_DEBUG "-g") # for debug symbols
  target_link_directories(${PROJECT_NAME} PRIVATE
    /opt/homebrew/lib
    )
  target_link_libraries(${PROJECT_NAME} glfw GLEW assimp)
  find_library(OpenGL_LIBRARY OpenGL)
  target_link_libraries(${PROJECT_NAME} ${OpenGL_LIBRARY})
ENDIF()

# move exe to root dir
# POST BUILD
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_SOURCE_DIR})
