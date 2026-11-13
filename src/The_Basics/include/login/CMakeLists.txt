find_package(Qt6 REQUIRED COMPONENTS Core Network)
find_library(Authentication_lib
    NAMES Authentication
    HINTS ../authentication/
)

add_library(login_lib
    loginScreen.cpp
    loginScreen.h
    signUpDialog.cpp
    signUpDialog.h

)

target_include_directories(login_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(login_lib
    PRIVATE
        Qt::Core
        Qt::Widgets
        Authentication_lib
)

if(MSVC)
    target_compile_options(login_lib PRIVATE /W3)
else()
    target_compile_options(login_lib PRIVATE -Wall)
endif()