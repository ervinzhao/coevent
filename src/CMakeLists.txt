cmake_minimum_required(VERSION 2.8)
aux_source_directory(.          SRC_LIST)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND SRC_LIST  ./coevent/ae.c)
list(APPEND SRC_LIST  ./coevent/event_loop.cpp)
#if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
#    list(APPEND SRC_LIST  ./coevent/ae_epoll.c)
#else()
#    list(APPEND SRC_LIST  ./coevent/ae_select.c)
#endif()

aux_source_directory(./cothread SRC_LIST)
aux_source_directory(./cosched  SRC_LIST)
include_directories(./)
add_executable(${PROJECT_NAME} ${SRC_LIST})

#target_link_libraries(${PROJECT_NAME} uv)
#target_link_libraries(${PROJECT_NAME} boost_coroutine)
