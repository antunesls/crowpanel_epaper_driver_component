cmake_minimum_required(VERSION 3.5)

# Add the parent directory to the component path to find the driver
get_filename_component(COMPONENT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../.. ABSOLUTE)
set(EXTRA_COMPONENT_DIRS ${COMPONENT_DIR})

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(crowpanel_4.2_inch_example)
