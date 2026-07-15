include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(googletest)

add_executable(chloro_tests EXCLUDE_FROM_ALL ${CMAKE_CURRENT_SOURCE_DIR}/test_chloro.cpp)
target_include_directories(chloro_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(chloro_tests PRIVATE chloro_wlib GTest::gtest_main)
set_target_properties(chloro_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

include(GoogleTest)
gtest_discover_tests(chloro_tests DISCOVERY_MODE PRE_TEST)
