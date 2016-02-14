.PHONY: all, clean

BUILD   := build
INCLUDE := -Iinclude
INCLUDE += -Iinclude/bencode

SOURCE  := src/bencode/*.c
SOURCE  += src/bencode/token/*.c

WARNING := -Wall
WARNING += -Wpedantic
WARNING += -Werror
WARNING += -Wunused

CCFLAGS  := $(WARNING) $(INCLUDE) -g -std=c++11

OBJECTS := $(wildcard $(SOURCE))
OBJECTS := $(subst .c,.o,$(OBJECTS))

CC      := g++

all: $(BUILD) $(BUILD)/$(NAME)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/$(NAME): main.c $(OBJECTS)
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD)
	rm -rf $(OBJECTS)
