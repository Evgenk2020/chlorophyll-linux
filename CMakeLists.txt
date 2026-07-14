cmake_minimum_required(VERSION 3.31)
project(chloro VERSION 1.0.4 LANGUAGES CXX)

# -------------------------------------------------------------
# to switch packaging to *.tar.gz >>> set(assemble_tgz ON)
set(assemble_tgz OFF)
# -------------------------------------------------------------

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(RapidJSON REQUIRED)

add_library(chloro_wlib SHARED ${CMAKE_SOURCE_DIR}/lib/chloro.cpp)
target_include_directories(chloro_wlib PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_library(chloro_wlib_output SHARED ${CMAKE_SOURCE_DIR}/lib/output.cpp)
target_include_directories(chloro_wlib_output PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(chloro_wlib_output PRIVATE ${RAPIDJSON_INCLUDE_DIRS})

add_library(chloro_wlib_proc SHARED ${CMAKE_SOURCE_DIR}/lib/proc.cpp)
target_include_directories(chloro_wlib_proc PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE chloro_wlib chloro_wlib_output chloro_wlib_proc)

# file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/sources/" DESTINATION "${CMAKE_BINARY_DIR}")

# -------------------------------------------------------------
# Google Test

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(chloro_tests ${CMAKE_SOURCE_DIR}/tests/test_chloro.cpp)
target_include_directories(chloro_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(chloro_tests PRIVATE chloro_wlib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(chloro_tests)

# -------------------------------------------------------------
# packaging

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Chlorophyll A and B maintenance for Linux terminal")

if (assemble_tgz)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
    install(TARGETS chloro_wlib chloro_wlib_output chloro_wlib_proc LIBRARY DESTINATION lib)
    install(FILES ${CMAKE_SOURCE_DIR}/sources/chloro DESTINATION "." PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
    set(CPACK_GENERATOR "TGZ")
else ()
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
    install(TARGETS chloro_wlib chloro_wlib_output chloro_wlib_proc LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    set(CPACK_GENERATOR "RPM")
    set(CPACK_RPM_PACKAGE_RELOCATABLE "TRUE")
endif ()

include(CPack)
