STD_FLAG = -O2 -Wall -std=c++11
MY_LIBS = -I./include/

all: build run
build: build_main
run: 
	./exec/main.exe

clean:
	rm *.exe
build_main:
	g++ main.cpp -o exec/main.exe $(STD_FLAG) $(MY_LIBS)
test:
	#./tester.sh

