cmake_minimum_required(VERSION 4.2)
project(C_Backend)
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 20)
find_package(ZLIB REQUIRED)
find_package(laserpants_dotenv)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

add_executable(C_Backend
        main.cpp
        src/router.cpp
        headers/router.h
        src/httpRequest.cpp
        headers/httpRequest.h
        headers/httpStatusCodes.h
        src/controller.cpp
        headers/controller.h
        src/httpResponse.cpp
        headers/httpResponse.h
        src/user.cpp
        headers/user.h
        src/modelPqxx.cpp
        headers/modelPqxx.h)
target_link_libraries(C_Backend PUBLIC ${PQXX_LIB} ${PQ_LIB} PRIVATE laserpants::dotenv nlohmann_json::nlohmann_json ZLIB::ZLIB)
