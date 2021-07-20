# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Lcd1602Emulator_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Lcd1602Emulator_autogen.dir/ParseCache.txt"
  "Lcd1602Emulator_autogen"
  )
endif()
