# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/whale-file-manager_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/whale-file-manager_autogen.dir/ParseCache.txt"
  "whale-file-manager_autogen"
  )
endif()
