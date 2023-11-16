cmake_minimum_required (VERSION 3.8)
project ("helloworld")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/out")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED glib-2.0 gio-unix-2.0)

message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
add_custom_command(OUTPUT helloWorld.c helloWorld.h
        COMMAND gdbus-codegen --generate-c-code helloWorld --c-namespace Example --interface-prefix com.example. ${CMAKE_CURRENT_SOURCE_DIR}/com.example.helloWorld.xml
        DEPENDS com.example.helloWorld.xml
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} #当前命令在当前目录下运行, 是生成的文件在当前目录下
        COMMENT "build helloWorld xml2cpp file")

add_custom_target(helloWorld ALL DEPENDS helloWorld.c helloWorld.h)

include_directories(
        ${GLIB2_INCLUDE_DIRS}
        ${GIO2_INCLUDE_DIRS}
)




add_executable(server server.c ${CMAKE_CURRENT_SOURCE_DIR}/helloWorld.c)
add_executable(client client.c ${CMAKE_CURRENT_SOURCE_DIR}/helloWorld.c)



target_link_libraries(server ${GLIB2_LIBRARIES})
target_link_libraries(client ${GLIB2_LIBRARIES})


