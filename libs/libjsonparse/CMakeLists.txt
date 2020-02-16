cmake_minimum_required(VERSION 2.6)

project(libjsonparse_sbc)

set(CMAKE_CXX_EXTRA_FLAGS "-std=c++11 -Wall -O2 -fdata-sections -ffunction-sections -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_EXTRA_FLAGS}")
set(JSON_PARSE_OUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../out")
set(JSON_PARSE_OUT_INC_DIR "${JSON_PARSE_OUT_DIR}/include")

include_directories(include)

set(SOURCES src/ccan_json.c
            src/util.c
    )

set(HEADERS include/ccan_json.h
    include/defs.h)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(jsonparse_sbc ${SOURCES} ${HEADERS})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_executable(main_sbc main.c)
#add executable file and link with static library now
target_link_libraries(main_sbc jsonparse_sbc ${LINKER_FLAGS})

install(TARGETS jsonparse_sbc            #installation rules
        ARCHIVE DESTINATION ${JSON_PARSE_OUT_DIR}
        LIBRARY DESTINATION ${JSON_PARSE_OUT_DIR}
        )

install(FILES ${INCLUDES} DESTINATION ${JSON_PARSE_OUT_INC_DIR})
