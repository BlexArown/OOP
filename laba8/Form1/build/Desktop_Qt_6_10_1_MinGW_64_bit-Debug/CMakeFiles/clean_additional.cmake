# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Form1_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Form1_autogen.dir\\ParseCache.txt"
  "Form1_autogen"
  )
endif()
