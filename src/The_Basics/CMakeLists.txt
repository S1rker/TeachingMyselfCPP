cmake_minimum_required(VERSION 3.16)
option(TUTORIAL_BUILD_UTILITIES "Build the Test executable" ON)

project(Test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

add_subdirectory(
    include 
)

add_executable(Test
    main.cpp

)

target_compile_features(Test
    PRIVATE
        cxx_std_17
)

target_link_libraries(Test
    PRIVATE
        include_lib
)
add_custom_command(TARGET Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/migrations
        $<TARGET_FILE_DIR:Test>/migrations
)

if(MSVC)
    target_compile_options(Test PRIVATE /W3)
else()
    target_compile_options(Test PRIVATE -Wall)
endif()

