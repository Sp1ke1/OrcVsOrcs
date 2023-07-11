CXX = g++
CXXFLAGS = -std=c++17 -Wno-long-long -Wall -pedantic -g -fsanitize=address -O2
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
EXE = cherkand
SOURCES_ALL := $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp)
SOURCES:= $(filter-out src/tests/%.cpp, $(SOURCES_ALL))
TESTS:= $(wildcard src/tests/*.test.cpp)

%.o: %.cpp
	@echo "Building: $^ with flags: $(CXXFLAGS)"
	@$(CXX) $(CXXFLAGS) -c -o $@ $^
	@echo "Creating dependency file: $*.d"
	@$(CXX) $(CXXFLAGS) -MM -MT $@ $^ > $*.d

all: doc compile

compile: $(SOURCES:.cpp=.o)
	@echo "Linking object files with flags: $(LDFLAGS)"
	@$(CXX) $(CXXFLAGS) $(SOURCES:.cpp=.o) -o $(EXE) $(LDFLAGS)

run: compile
	@echo "Running executable"
	@./$(EXE)

src/tests/Tester: src/tests/Tester.o $(filter-out src/main.o, $(SOURCES:.cpp=.o))
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test_all: src/tests/Tester
		./src/tests/Tester

clean:
	@echo "Deleting object files"
	@rm -f -- src/*.o src/*/*.o src/*/*/*.o src/*/*/*/*.o
	@echo "Deleting dependency files"
	@rm -f -- src/*.d src/*/*.d src/*/*/*.d src/*/*/*/*.d
	@echo "Deleting executable"
	@rm -f $(EXE)
	@echo "Deleting documentation"
	@rm -rf -- doc/
	@echo "Deleting tests"
	@rm -rf -- src/tests/Tester

doc:
	@echo "Generation documentation"
	doxygen Doxyfile
	mv doc/html/* doc/
	rm -r doc/html

