cmake_minimum_required(VERSION 3.10)
project(s2o)

set(CMAKE_C_STANDARD 11)

# src 디렉토리의 모든 헤더 파일과 소스 파일 포함
include_directories(src)
file(GLOB SOURCES src/*.c src/*.hpp src/lib/*.c src/lib/*.hpp)

# l8w8jwt 라이브러리 추가
include_directories(src/l8w8jwt)
add_subdirectory(src/lib/l8w8jwt)

# openssl 라이브러리 추가
include_directories(/opt/homebrew/opt/openssl/include)
link_directories(/opt/homebrew/opt/openssl/lib)


# s2o 실행 파일 생성
# add_executable(s2o ${SOURCES})
# target_link_libraries(s2o l8w8jwt)

# IT.srvd 실행 파일 생성
add_executable(IT.srvd ${SOURCES})
target_link_libraries(IT.srvd ssl crypto)