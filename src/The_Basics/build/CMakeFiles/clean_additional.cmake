# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Test_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Test_autogen.dir/ParseCache.txt"
  "Test_autogen"
  "include/CMakeFiles/include_lib_autogen.dir/AutogenUsed.txt"
  "include/CMakeFiles/include_lib_autogen.dir/ParseCache.txt"
  "include/authentication/Authentication_lib_autogen"
  "include/authentication/CMakeFiles/Authentication_lib_autogen.dir/AutogenUsed.txt"
  "include/authentication/CMakeFiles/Authentication_lib_autogen.dir/ParseCache.txt"
  "include/include_lib_autogen"
  "include/login/CMakeFiles/login_lib_autogen.dir/AutogenUsed.txt"
  "include/login/CMakeFiles/login_lib_autogen.dir/ParseCache.txt"
  "include/login/login_lib_autogen"
  "include/room/CMakeFiles/room_lib_autogen.dir/AutogenUsed.txt"
  "include/room/CMakeFiles/room_lib_autogen.dir/ParseCache.txt"
  "include/room/room_lib_autogen"
  )
endif()
