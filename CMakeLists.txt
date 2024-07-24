# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(IoTFullStack_Firmware)


target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "main/cert/client.crt" TEXT)
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "main/cert/client.key" TEXT)
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "main/cert/mosquitto.org.crt" TEXT)