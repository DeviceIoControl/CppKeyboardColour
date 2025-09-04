# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\KeyboardColor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\KeyboardColor_autogen.dir\\ParseCache.txt"
  "KeyboardColor_autogen"
  )
endif()
