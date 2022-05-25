# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(LedDriver)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/gpio.c)
target_sources(app PRIVATE src/leds.c)
target_sources(app PRIVATE src/adc.c)
target_sources(app PRIVATE src/filter.c)
target_sources(app PRIVATE src/pwm.c)