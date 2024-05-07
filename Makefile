OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers
INCLUDES = -I include

all: directories main.exe

main.exe: objects/program.o objects/Producte.o objects/Ciutat.o objects/Cjt_ciutats.o objects/Cjt_productes.o objects/Vaixell.o
	g++ $(OPCIONS) -o main.exe objects/program.o objects/Producte.o objects/Ciutat.o objects/Cjt_ciutats.o objects/Cjt_productes.o objects/Vaixell.o

objects/program.o: src/program.cc
	g++ $(OPCIONS) -c src/program.cc -o objects/program.o $(INCLUDES)

objects/Ciutat.o: src/Ciutat.cc
	g++ $(OPCIONS) -c src/Ciutat.cc -o objects/Ciutat.o $(INCLUDES)

objects/Cjt_ciutats.o: src/Cjt_ciutats.cc
	g++ $(OPCIONS) -c src/Cjt_ciutats.cc -o objects/Cjt_ciutats.o $(INCLUDES)

objects/Cjt_productes.o: src/Cjt_productes.cc
	g++ $(OPCIONS) -c src/Cjt_productes.cc -o objects/Cjt_productes.o $(INCLUDES)

objects/Producte.o: src/Producte.cc
	g++ $(OPCIONS) -c src/Producte.cc -o objects/Producte.o $(INCLUDES)

objects/Vaixell.o: src/Vaixell.cc
	g++ $(OPCIONS) -c src/Vaixell.cc -o objects/Vaixell.o $(INCLUDES)

directories:
	mkdir -p objects

clean:
	rm -rf objects main.exe