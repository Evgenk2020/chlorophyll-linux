set(assemble_tgz OFF)

cmake_minimum_required(VERSION 3.31)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib/static)

project(chloro VERSION 1.0.1 LANGUAGES CXX)

add_library(chloro_wlib SHARED ${CMAKE_SOURCE_DIR}/lib/chloro.cpp)
target_include_directories(chloro_wlib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(chloro_wlib_output SHARED ${CMAKE_SOURCE_DIR}/lib/output.cpp)
target_include_directories(chloro_wlib_output PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(chloro_wlib_proc SHARED ${CMAKE_SOURCE_DIR}/lib/proc.cpp)
target_include_directories(chloro_wlib_proc PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC chloro_wlib chloro_wlib_output chloro_wlib_proc)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(TARGETS chloro_wlib chloro_wlib_output chloro_wlib_proc LIBRARY DESTINATION lib)

if(assemble_tgz)
    install(FILES ${CMAKE_SOURCE_DIR}/sources/chloro DESTINATION "."
                        PERMISSIONS
                        OWNER_READ OWNER_WRITE OWNER_EXECUTE
                        GROUP_READ GROUP_EXECUTE 
                        WORLD_READ WORLD_EXECUTE)
endif()

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Chlorophyll A and B maintenance for Linux terminal")

if(assemble_tgz)
    set(CPACK_GENERATOR "TGZ")
else()
    set(CPACK_GENERATOR "RPM")
    set(CPACK_RPM_PACKAGE_RELOCATABLE "TRUE")
endif()

include(CPack)