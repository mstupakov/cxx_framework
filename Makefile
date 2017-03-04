all: main.cpp
	g++ -ggdb $< -o wm

clean:
	rm -rf wm *.o
