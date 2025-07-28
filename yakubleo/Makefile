#compiler
CXX=g++
#linker
LD=g++
#compiler flags
CXXFLAGS=-Wall -pedantic -g -std=c++17 -fsanitize=address
#library flags
LDFLAGS=-lncurses -lform

# wildcard - serves to expand *.h
HEADERS = $(wildcard src/*.h)
SOURCE = $(wildcard src/*.cpp)
# patsubst - serves to replace src/*.cpp with build/*.o
# $(patsubst pattern, replacement, text)
OBJECTS=$(patsubst src/%.cpp, build/%.o, $(SOURCE))

# all=main target
# .PHONY - performes the comand even if there is a file named the same as the target
.PHONY: all
all: yakubleo doc

.PHONY: run
run: yakubleo
	./yakubleo

.PHONY: compile
compile: yakubleo

# $@ = target file
# $^ = all dependencies
yakubleo: $(OBJECTS)
	$(LD) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# macro to compile .cpp to .o
# @< = first dependency
# $(@D) = directory of target
build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: doc
doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf yakubleo build/ doc/







