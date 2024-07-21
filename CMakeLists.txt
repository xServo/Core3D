# dlls must be in path
# MSBuild.exe must be in path:
    # %ProgramFiles%\Microsoft Visual Studio\2022\<YOUR_VS_EDITION>\MSBuild\Current\Bin
# $ cmake -B build/win
# $ msbuild build/win/Core3D.sln /p:Configuration=Debug /p:Platform=x64
# $ mv build/win/Debug/Core3D.exe ./

cmake_minimum_required(VERSION 3.13)
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
## create exe in Core3D root
#set_target_properties(${PROJECT_NAME} PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ../../
#)

# include dir
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor
    ${CMAKE_SOURCE_DIR}/vendor/assimp
    ${CMAKE_SOURCE_DIR}/vendor/glm
    ${CMAKE_SOURCE_DIR}/vendor/glew
    ${CMAKE_SOURCE_DIR}/vendor/glfw
    ${CMAKE_SOURCE_DIR}/vendor/imgui
    ${CMAKE_SOURCE_DIR}/vendor/imgui/backends
    ${CMAKE_SOURCE_DIR}/vendor/stb
    ${CMAKE_SOURCE_DIR}/src
)

# windows
target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib-vc2022
    ${CMAKE_SOURCE_DIR}/dependencies/glew/lib/Release/x64
    ${CMAKE_SOURCE_DIR}/dependencies/assimp
)
target_link_libraries(${PROJECT_NAME} glfw3 glew32 assimp-vc143-mt opengl32)