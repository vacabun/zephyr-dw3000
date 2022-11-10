# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

set(BOARD stm32f401_mini)
set(BOARD_FLASH_RUNNER openocd)

set(DTC_OVERLAY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/stm32f401_mini.overlay)

list(APPEND ZEPHYR_EXTRA_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/zephyr-dw3000-decadriver/)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(hello_world)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
