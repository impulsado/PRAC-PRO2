OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers
INCLUDES = -I include

all: directories main.exe

main.exe: objects/program.o objects/Producte.o
	g++ $(OPCIONS) -o main.exe objects/program.o objects/Producte.o

objects/program.o: src/program.cc
	g++ $(OPCIONS) -c src/program.cc -o objects/program.o $(INCLUDES)

objects/Producte.o: src/Producte.cc
	g++ $(OPCIONS) -c src/Producte.cc -o objects/Producte.o $(INCLUDES)

directories:
	mkdir -p objects

clean:
	rm -rf objects main.exe