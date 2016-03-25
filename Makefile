.PHONY: all, clean, test

INCLUDE := -Iinclude
INCLUDE += -Iinclude/bencode

SOURCE  := include/bencode/*.hpp

TESTS   := $(wildcard test/*.cpp)
RUNNERS := $(subst .cpp,.out,$(TESTS))

TFLAGS  := --log_level=test_suite
TFLAGS  += --show_progress

DEVLIBS := -lboost_unit_test_framework

WARNING := -Wall
WARNING += -Wpedantic
WARNING += -Werror
WARNING += -Wunused

CCFLAGS := $(WARNING) $(INCLUDE) -std=c++11

OBJECTS := $(wildcard $(SOURCE))
OBJECTS := $(subst .hpp,.o,$(OBJECTS))
OBJECTS := $(subst .cpp,.o,$(OBJECTS))

CXX     := g++

all: test

%.o: %.hpp
	$(CXX) $(CCFLAGS) -x c++ -c $^ -o $@

%.o: %.cpp
	$(CXX) $(CCFLAGS) -x c++ -c $^ -o $@

test/%: test/%.cpp $(OBJECTS)
	$(CXX) $(CCFLAGS) -o $@ $^ $(DEVLIBS)

run-%: test/%
	$^ $(TFLAGS)

test: $(RUNNERS) $(subst test/,run-,$(RUNNERS))

clean:
	rm -rf $(OBJECTS)
	rm -rf $(RUNNERS)
