
find_package(SQLiteCpp REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_library(room_lib
    MessageRoom.cpp
    MessageRoom.h
)

target_include_directories(room_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(room_lib
    PUBLIC
        SQLiteCpp
        Qt::Core
        Qt::Widgets
)

if(MSVC)
    target_compile_options(room_lib PRIVATE /W3)
else()
    target_compile_options(room_lib PRIVATE -Wall)
endif()

