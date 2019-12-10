cmake_minimum_required (VERSION 2.8)

project (LockService)

include_directories(./include)
include_directories(./lib/rpclib/include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(LINK_LIB ls rpc pthread)

add_subdirectory(src)
add_subdirectory(lib/rpclib)

add_executable(server Server.cpp)
add_executable(client Client.cpp)

target_link_libraries(server ${LINK_LIB})
target_link_libraries(client ${LINK_LIB})
