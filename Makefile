CXX ?= g++


hanoi: *.cpp
	$(CXX) $^ -o $@