cmake_minimum_required (VERSION 3.1)
project (RaspiStation)



list(APPEND mySOURCES
    "${CMAKE_CURRENT_LIST_DIR}/MainComponent.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Logger.cpp"
)

set (CMAKE_CXX_STANDARD 14)

add_executable(RaspiStation ${mySOURCES})