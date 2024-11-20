add_library(sclp STATIC
    ${CMAKE_CURRENT_LIST_DIR}/control/pid/pid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/module/md/md.cpp
    ${CMAKE_CURRENT_LIST_DIR}/module/qei/qei.cpp
    ${CMAKE_CURRENT_LIST_DIR}/module/servo/servo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/utils/pwm_func/pwm_func.cpp
)

target_link_libraries(
    sclp
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_dma
    hardware_pio
    hardware_pwm
    hardware_interp
    hardware_timer
    hardware_watchdog
    hardware_clocks
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")