cmake_minimum_required(VERSION 3.28)
project(T_Rex_Clone_SFML_)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)
include(FetchContent)

fetchcontent_declare(
        SFML
        GIT_REPOSITORY https://github.com/sfml/sfml
        GIT_TAG 2.6.1
)

fetchcontent_makeavailable(sfml)

add_executable(main main.cpp)
target_link_libraries(main sfml-graphics)
