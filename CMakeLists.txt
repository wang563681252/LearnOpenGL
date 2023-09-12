cmake_minimum_required(VERSION 3.13)

project(OPENGL)

file(GLOB_RECURSE APP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h, ${CMAKE_CURRENT_SOURCE_DIR}/*.inl, ${CMAKE_CURRENT_SOURCE_DIR}/*.c*)

add_executable(OPENGL ${APP_FILES})

target_include_directories(OPENGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLEW/include ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLFW/include)

target_link_libraries(
    OPENGL
PUBLIC
    
)