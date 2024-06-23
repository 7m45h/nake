CC := gcc
CPPFLAGS := -MMD
LINK_LIBS := sdl2 SDL2_ttf
CFLAGS := -Wall -Wextra -march=native $(shell pkg-config --cflags ${LINK_LIBS})
LDFLAGS := $(shell pkg-config --libs ${LINK_LIBS})

SRC_DIR := src
OBJ_DIR := obj
LIBS_DIRS := $(patsubst ${SRC_DIR}/%,${OBJ_DIR}/%,$(shell find ${SRC_DIR} -mindepth 1 -type d))

BUILD_DIR := build
DEBUG_DIR := ${BUILD_DIR}/debug
FINAL_DIR := ${BUILD_DIR}/final

SRCS := $(patsubst ./${SRC_DIR}/%,%,$(shell find -type f -name "*.c"))
OBJS := $(patsubst %.c,%.o,${SRCS})
BIN := $(shell basename ${CURDIR})

ifeq (${MODE}, final)
CFLAGS += -Ofast -s
OBJ_DIR := $(addprefix ${FINAL_DIR}/,${OBJ_DIR})
LIBS_DIRS := $(addprefix ${FINAL_DIR}/,${LIBS_DIRS})
BIN := $(addprefix ${FINAL_DIR}/,${BIN})
else
CFLAGS += -g
OBJ_DIR := $(addprefix ${DEBUG_DIR}/,${OBJ_DIR})
LIBS_DIRS := $(addprefix ${DEBUG_DIR}/,${LIBS_DIRS})
BIN := $(addprefix ${DEBUG_DIR}/,${BIN})
endif

${BIN}: $(addprefix ${OBJ_DIR}/,${OBJS}) | ${BUILD_DIR} ${DEBUG_DIR} ${FINAL_DIR} ${LIBS_DIRS}
ifndef LDFLAGS
	${CC} ${CFLAGS} -o $@ $^
else
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^
endif

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c | ${OBJ_DIR} ${LIBS_DIRS}
	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ -c $<

${BUILD_DIR} ${DEBUG_DIR} ${FINAL_DIR}:
	mkdir $@

${LIBS_DIRS}: | ${OBJ_DIR}
	mkdir $@

${OBJ_DIR}: | ${BUILD_DIR} ${DEBUG_DIR} ${FINAL_DIR}
	mkdir $@

.PHONY: clean
clean:
	rm -r $(wildcard ${DEBUG_DIR}/*) $(wildcard ${FINAL_DIR}/*)

-include $(addprefix ${OBJ_DIR}/,$(patsubst %.o,%.d,${OBJS}))
