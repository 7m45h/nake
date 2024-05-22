CC := gcc
CPPFLAGS := -MMD
CFLAGS := -march=native
LDFLAGS := -lSDL2

SRC_DIR := src
OBJ_DIR := obj

BUILD_DIR := build
DEBUG_DIR := ${BUILD_DIR}/debug
FINAL_DIR := ${BUILD_DIR}/final

SRCS := $(patsubst ${SRC_DIR}/%,%,$(wildcard ${SRC_DIR}/*.c))
OBJS := $(patsubst %.c,%.o,${SRCS})
BIN := $(shell basename ${CURDIR})

ifeq (${MODE}, final)
CFLAGS += -Ofast -s
OBJ_DIR := $(addprefix ${FINAL_DIR}/,${OBJ_DIR})
BIN := $(addprefix ${FINAL_DIR}/,${BIN})
else
CFLAGS += -Wall -Wextra -g
OBJ_DIR := $(addprefix ${DEBUG_DIR}/,${OBJ_DIR})
BIN := $(addprefix ${DEBUG_DIR}/,${BIN})
endif

${BIN}: $(addprefix ${OBJ_DIR}/,${OBJS}) | ${BUILD_DIR} ${DEBUG_DIR} ${FINAL_DIR}
ifndef LDFLAGS
	${CC} ${CFLAGS} -o $@ $^
else
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^
endif

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c | ${OBJ_DIR}
	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ -c $<

${BUILD_DIR} ${DEBUG_DIR} ${FINAL_DIR}:
	mkdir $@

${OBJ_DIR}: | ${BUILD_DIR} ${DEBUG_DIR} ${FINAL_DIR}
	mkdir $@

.PHONY: clean
clean:
	rm -r $(wildcard ${DEBUG_DIR}/*) $(wildcard ${FINAL_DIR}/*)

-include $(addprefix ${OBJ_DIR}/,$(patsubst %.o,%.d,${OBJS}))
