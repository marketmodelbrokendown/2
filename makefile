
all: GSLexe
    
GSLexe: GSLobj
	 g++ -o ./src/GSL ./obj/GSL.o 
	 rm -f ./bin/GSL.o
GSLobj: ./src/GSL.cpp
	 g++ -c -lgsl -o ./obj/GSL.o ./src/GSL.cpp
     
clean:
	 rm -f ./bin/GSL

all: Gnuplotexe
    
Gnuplotexe: Gnuplotobj
	 g++ -o ./src/Gnuplot ./obj/Gnuplot.o 
	 rm -f ./bin/Gnuplot.o
Gnuplotobj: ./src/Gnuplot.cpp
	 g++ -c -lgsl -o ./obj/Gnuplot.o ./src/Gnuplot.cpp
clean:
	 rm -f ./bin/Gnuplot     


