cmake_minimum_required (VERSION 3.5.1)
project (RaspiStation)


## library name
set(PAHO_MQTT_CPP paho-mqttpp3)
set(PAHO_MQTT_CPP_STATIC ${PAHO_MQTT_CPP}-static)

## build settings
set(PAHO_VERSION_MAJOR 1)
set(PAHO_VERSION_MINOR 0)
set(PAHO_VERSION_PATCH 0)

set(CLIENT_VERSION ${PAHO_VERSION_MAJOR}.${PAHO_VERSION_MINOR}.${PAHO_VERSION_PATCH})

set(CPACK_PACKAGE_VERSION_MAJOR ${PAHO_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PAHO_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PAHO_VERSION_PATCH})

## --- Build options ---

if(WIN32)
  set(PAHO_BUILD_STATIC TRUE  CACHE BOOL "Build static library")
  set(PAHO_BUILD_SHARED FALSE CACHE BOOL "Build shared library (DLL)")
  set(PAHO_WITH_SSL FALSE CACHE BOOL "Build SSL-enabled library")
else()
  set(PAHO_BUILD_STATIC FALSE CACHE BOOL "Build static library")
  set(PAHO_BUILD_SHARED TRUE CACHE BOOL "Build shared library")
  set(PAHO_WITH_SSL TRUE CACHE BOOL "Build SSL-enabled library")
endif()

set(PAHO_BUILD_SAMPLES FALSE CACHE BOOL "Build sample programs")
set(PAHO_BUILD_DOCUMENTATION FALSE CACHE BOOL "Create and install the API documentation (requires Doxygen)")
set(PAHO_MQTT_C_PATH "" CACHE PATH "Add a path to paho.mqtt.c library and headers")
set(PAHO_MQTT_C paho-mqtt3a)

## --- C++11 build flags ---

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)
add_subdirectory(src/mqtt)


list(APPEND mySOURCES
    "${CMAKE_CURRENT_LIST_DIR}/MainComponent.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Logger.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MqttConnector.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PressureSensor.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/HumiditySensor.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Camera.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/base64.cpp"
)

## --- MY EXECUTABLE ---

add_executable(RaspiStation ${mySOURCES})

## link directories
link_directories(${PAHO_MQTT_C_LIB_DIR})
link_directories(${PAHO_MQTT_CPP_LIB_DIR})

target_link_libraries(RaspiStation
    ${PAHO_MQTT_C}
    ${PAHO_MQTT_CPP})


## --- Packaging settings ---

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
elseif(UNIX)
    set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)
