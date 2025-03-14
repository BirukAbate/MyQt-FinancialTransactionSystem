# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/MyQt_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/MyQt_autogen.dir/ParseCache.txt"
  "MyQt_autogen"
  )
endif()
