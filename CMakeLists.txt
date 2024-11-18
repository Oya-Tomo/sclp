add_library(sclp STATIC
    ${CMAKE_CURRENT_LIST_DIR}/module/qei/qei.cpp
    ${CMAKE_CURRENT_LIST_DIR}/module/servo/servo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/control/pid/pid.cpp
)

target_link_libraries(
    sclp
    pico_stdlib
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")