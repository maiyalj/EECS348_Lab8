CXX := g++

all: matrix.exe

matrix.exe: main.cpp matrix.cpp
	@$(CXX) main.cpp matrix.cpp -o matrix.exe
	@./matrix.exe
	@rm -f matrix.exe
