cmake_minimum_required(VERSION 3.10)

project(TP1_SO)

set(SOURCES
	src/main.c
	src/stepA.c
	src/stepB.c
	src/stepC.c
	src/stepD.c
	src/usocomun.c
)

set(HEADERS
	${PROJECT_SOURCE_DIR}/inc
)

add_executable(${PROJECT_NAME} ${SOURCES})
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ${HEADERS})
