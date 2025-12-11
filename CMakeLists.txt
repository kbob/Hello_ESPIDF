cmake_minimum_required(VERSION 3.22)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
include(default-board.cmake)

# sdkconfig files are evaluated left to right.  The last definition
# of a variable wins.

if ("${board_config}" STREQUAL "")
    set(board_config "${default_board_config}")
endif()

set(SDKCONFIG_DEFAULTS "sdkconfig.defaults;${board_config}")

set(COMPONENTS main)

project(Hello_ESPIDF)
