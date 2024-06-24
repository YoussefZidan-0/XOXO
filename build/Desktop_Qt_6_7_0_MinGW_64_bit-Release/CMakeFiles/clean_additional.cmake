# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\XOXO_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\XOXO_autogen.dir\\ParseCache.txt"
  "XOXO_autogen"
  )
endif()
