VPATH := $(shell find ./src -type d)

SOURCES := $(shell find ./src -type f -name *.cpp)
tmp := $(patsubst %.cpp, %.o, $(SOURCES))
OBJECTS := $(foreach obj, $(tmp), bin/$(notdir $(obj)))

tmp := $(shell find ./src -type d)
INCLUDEDIRS := $(foreach dir, $(tmp), -I$(dir))

tmp := /usr/local/lib 
LIBDIRS := $(foreach dir, $(tmp), -L$(dir))

LIBS = -lm -lstdc++
CXXFLAGS = -ansi -O3 -std=c++11

CXXFLAGS += $(INCLUDEDIRS)
CXXFLAGS += $(LIBDIRS)

aisde23: $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ bin/*.o $(LIBS)
	

bin/%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	@rm -f aisde23 core bin/*.o

run: clean aisde23
	./aisde23