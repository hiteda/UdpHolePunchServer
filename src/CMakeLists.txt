file (GLOB SRC_HEADERS
		"Client.h"
		"ClientMap.h"
		"IpEndpoint.h"
		"Server.h"
		"ServerSocket.h"
		"windows/ServerSocket.h")
file (GLOB SRC_SOURCES
		"ClientMap.cpp"
		"Main.cpp"
		"Server.cpp"
		"windows/ServerSocket.cpp")

source_group("source" FILES ${SRC_SOURCES})
source_group("headers" FILES ${SRC_HEADERS})

include_directories(. ./windows)

add_executable(server ${SRC_SOURCES} ${SRC_HEADERS})

set_target_properties(server PROPERTIES
						RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)