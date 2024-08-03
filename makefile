CC := gcc
CPPFLAGS := -MMD
CFLAGS := -Wall -Wextra -march=native
LDFLAGS := -lm
LIBS := sdl2 SDL2_ttf

ifdef LIBS
CFLAGS += $(shell pkg-config --cflags ${LIBS})
LDFLAGS += $(shell pkg-config --libs ${LIBS})
endif

SOURCE_DIR := ./src
BUILD_BASE_DIR := ./build
DEBUG_DIR := ${BUILD_BASE_DIR}/debug
FINAL_DIR := ${BUILD_BASE_DIR}/final
PROJECT_NAME := le_nake

MODULE_DIRS := $(patsubst ${SOURCE_DIR}/%,%,$(shell find ${SOURCE_DIR} -mindepth 1 -type d))
SRCS := $(patsubst ${SOURCE_DIR}/%,%,$(shell find ${SOURCE_DIR} -type f -name "*.c"))
OBJS := $(patsubst %.c,%.o,${SRCS})

ifeq (${MODE},final)
MODE := FINAL
CFLAGS += -Ofast -s
BUILD_DIR := ${FINAL_DIR}
else
MODE := DEBUG
CFLAGS += -Og -g
BUILD_DIR := ${DEBUG_DIR}
endif

MODULE_DIRS := $(addprefix ${BUILD_DIR}/,${MODULE_DIRS})
BIN := $(addprefix ${BUILD_DIR}/,${PROJECT_NAME})

${BIN}: $(addprefix ${BUILD_DIR}/,${OBJS}) | ${BUILD_DIR} ${MODULE_DIRS}
	@printf "\n%-17s%16s @ %s\n" "build complete!" "executable" $@
ifndef LDFLAGS
	@${CC} ${CFLAGS} -o $@ $^
else
	@${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^
endif

${BUILD_DIR}/%.o: ${SOURCE_DIR}/%.c | ${BUILD_DIR} ${MODULE_DIRS}
	@printf "%-32s -> %s\n" $< $@
	@${CC} ${CPPFLAGS} ${CFLAGS} -o $@ -c $<

${MODULE_DIRS}: | ${BUILD_DIR}
	@mkdir $@

${BUILD_DIR}: | ${BUILD_BASE_DIR}
	@mkdir $@

${BUILD_BASE_DIR}:
	@mkdir $@

.PHONY: clean
clean:
	@if [ -d ${BUILD_BASE_DIR} ]; then rm -r ${BUILD_BASE_DIR}; fi
	@echo clean!

-include $(addprefix ${OBJ_DIR}/,$(patsubst %.o,%.d,${OBJS}))
