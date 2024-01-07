# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Espressif/frameworks/esp-idf-v4.4.6/components/bootloader/subproject"
  "D:/ESP32Project/GPIO-Interrupt/build/bootloader"
  "D:/ESP32Project/GPIO-Interrupt/build/bootloader-prefix"
  "D:/ESP32Project/GPIO-Interrupt/build/bootloader-prefix/tmp"
  "D:/ESP32Project/GPIO-Interrupt/build/bootloader-prefix/src/bootloader-stamp"
  "D:/ESP32Project/GPIO-Interrupt/build/bootloader-prefix/src"
  "D:/ESP32Project/GPIO-Interrupt/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/ESP32Project/GPIO-Interrupt/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
