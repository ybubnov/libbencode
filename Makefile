.PHONY: all, clean, test

NAME    := main

BUILD   := build
INCLUDE := -Iinclude
INCLUDE += -Iinclude/bencode

SOURCE  += include/bencode/*.hpp
SOURCE  += src/bencode/*.cpp

TESTS   := $(wildcard test/*.cpp)
RUNNERS := $(subst .cpp,.out,$(TESTS))

TFLAGS  := --log_level=test_suite
TFLAGS  += --show_progress

DEVLIBS := -lboost_unit_test_framework

WARNING := -Wall
WARNING += -Wpedantic
WARNING += -Werror
WARNING += -Wunused

CCFLAGS  := $(WARNING) $(INCLUDE) -g -std=c++11

OBJECTS := $(wildcard $(SOURCE))
OBJECTS := $(subst .hpp,.o,$(OBJECTS))
OBJECTS := $(subst .cpp,.o,$(OBJECTS))

CXX     := g++

all: $(BUILD) $(BUILD)/$(NAME)

%.o: %.hpp
	$(CXX) $(CCFLAGS) -x c++ -c $^ -o $@

%.o: %.cpp
	$(CXX) $(CCFLAGS) -x c++ -c $^ -o $@

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/$(NAME): main.cpp $(OBJECTS)
	$(CXX) $(CCFLAGS) $^ -o $@

test/%: test/%.cpp $(OBJECTS)
	$(CXX) $(CCFLAGS) -o $@ $^ $(DEVLIBS)

run-%: test/%
	$^ $(TFLAGS)

test: $(RUNNERS) $(subst test/,run-,$(RUNNERS))

clean:
	rm -rf $(BUILD)
	rm -rf $(OBJECTS)
	rm -rf $(RUNNERS)
