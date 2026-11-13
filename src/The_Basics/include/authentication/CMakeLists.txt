find_package(SQLiteCpp REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Network)

add_library(Authentication_lib
    Authentication.cpp
    Authentication.h
    migrate.cpp
    migrate.h
    passwordHasher.cpp
    passwordHasher.h

)

target_include_directories(Authentication_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Authentication_lib
    PRIVATE
        SQLiteCpp
        Qt::Core
        Qt::Network
)
target_compile_definitions(Authentication_lib
    PRIVATE
        DB_PATH="${PROJECT_SOURCE_DIR}/app.sqlite"
        MIGRATIONS_DIR="${PROJECT_SOURCE_DIR}/migrations"
)
if(MSVC)
    target_compile_options(Authentication_lib PRIVATE /W3)
else()
    target_compile_options(Authentication_lib PRIVATE -Wall)
endif()

