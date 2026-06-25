.PHONY: run build

CXX = clang++
CXXFLAGS = -std=c++17 -I include
SRC = src/*.cpp
OUT = build/engine

run: build
	./$(OUT)

build:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)