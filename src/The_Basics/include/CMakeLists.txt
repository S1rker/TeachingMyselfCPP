
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_subdirectory(authentication)
add_subdirectory(room)
add_subdirectory(login)

add_library(include_lib
    MainWindow.cpp
    MainWindow.h
    
)

target_include_directories(include_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(include_lib
    PUBLIC
        Qt::Core
        Qt::Widgets
        room_lib
        Authentication_lib
        login_lib
)

if(MSVC)
    target_compile_options(include_lib PRIVATE /W3)
else()
    target_compile_options(include_lib PRIVATE -Wall)
endif()

