OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers
INCLUDES = -I include

all: program.exe

program.exe: program.o Ciutat.o Cjt_ciutats.o Cjt_productes.o Vaixell.o Viatge.o Llanxa.o
	g++ $(OPCIONS) -o program.exe program.o Ciutat.o Cjt_ciutats.o Cjt_productes.o Vaixell.o Viatge.o Llanxa.o
	rm *.o

program.o: src/program.cc
	g++ $(OPCIONS) -c src/program.cc -o program.o $(INCLUDES)

Ciutat.o: src/Ciutat.cc
	g++ $(OPCIONS) -c src/Ciutat.cc -o Ciutat.o $(INCLUDES)

Cjt_ciutats.o: src/Cjt_ciutats.cc
	g++ $(OPCIONS) -c src/Cjt_ciutats.cc -o Cjt_ciutats.o $(INCLUDES)

Cjt_productes.o: src/Cjt_productes.cc
	g++ $(OPCIONS) -c src/Cjt_productes.cc -o Cjt_productes.o $(INCLUDES)

Vaixell.o: src/Vaixell.cc
	g++ $(OPCIONS) -c src/Vaixell.cc -o Vaixell.o $(INCLUDES)

Viatge.o: src/Viatge.cc
	g++ $(OPCIONS) -c src/Viatge.cc -o Viatge.o $(INCLUDES)

Llanxa.o: src/Llanxa.cc
	g++ $(OPCIONS) -c src/Llanxa.cc -o Llanxa.o $(INCLUDES)

entrega:
	tar -cvf entrega.tar Makefile src/*.cc include/*.hh

entrega_final:
	doxygen Doxyfile
	(cd DOC/html && zip -r ../../html.zip .)
	tar -cvf entrega_final.tar Makefile src/*.cc include/*.hh Justificacio_Final.pdf html.zip

clean:
	rm -rf *.o main.exe