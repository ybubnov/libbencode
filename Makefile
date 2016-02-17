.PHONY: all, clean

NAME    := bde

BUILD   := build
INCLUDE := -Iinclude
INCLUDE += -Iinclude/bencode
INCLUDE += -Iinclude/bencode/token

SOURCE  += include/bencode/token/*.hpp
SOURCE  += include/*.hpp

WARNING := -Wall
WARNING += -Wpedantic
WARNING += -Werror
WARNING += -Wunused

CCFLAGS  := $(WARNING) $(INCLUDE) -g -std=c++11

OBJECTS := $(wildcard $(SOURCE))
OBJECTS := $(subst .hpp,.o,$(OBJECTS))
OBJECTS := $(subst .cpp,.o,$(OBJECTS))

CC      := g++

all: $(BUILD) $(BUILD)/$(NAME)

%.o: %.hpp
	$(CC) $(CCFLAGS) -x c++ -c $^ -o $@

%.o: %.cpp
	$(CC) $(CCFLAGS) -x c++ -c $^ -o $@

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/$(NAME): main.cpp $(OBJECTS)
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD)
	rm -rf $(OBJECTS)
