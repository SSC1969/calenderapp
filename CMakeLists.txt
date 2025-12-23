cmake_minimum_required(VERSION 4.2)
project(CalenderApp VERSION 0.0.1 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
file(GLOB_RECURSE SOURCES src/*.cpp)

find_package(wxWidgets COMPONENTS core base REQUIRED)
find_package(SQLite3)

add_subdirectory(dependencies)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE wxWidgets::wxWidgets SQLite::SQLite3 sqlite_orm::sqlite_orm)


# Source - https://stackoverflow.com/a
# Posted by Mike Repass, modified by community. See post 'Timeline' for change history
# Retrieved 2025-12-23, License - CC BY-SA 4.0

# Code to disable compiler warnings for sqlite_orm
get_target_property(sqlite_orm_include_dirs sqlite_orm INTERFACE_INCLUDE_DIRECTORIES)
set_target_properties(sqlite_orm PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${sqlite_orm_include_dirs}")

# install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
