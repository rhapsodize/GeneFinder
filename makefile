CC=g++
DEV= -g -std=c++14
OPT=-O3 -std=c++14

.PHONY: all
all: GeneFinder

GeneFinder:
	$(CC) $(DEV) GeneFinder.cpp -o GeneFinder.exe

# Build
.PHONY: clean
clean:
	
	rm -f *.exe
	

.PHONY: update
update:
	make clean
	make all
