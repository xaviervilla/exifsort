CPP = g++ -std=c++11
OPT = -g
INC = -I inc

OBJ = src/ExifTool.o src/ExifToolPipe.o src/TagInfo.o Place.o
HDR = inc/ExifTool.h inc/ExifToolPipe.h inc/TagInfo.h Place.hpp

all:    exifsort 

clean:
	rm -f src/*.o *.o exifsort

exifsort: exifsort.o $(OBJ)
	$(CPP) $(OPT) -o exifsort exifsort.o $(OBJ)

%.o: %.cpp $(HDR)
	$(CPP) $(OPT) $(INC) -o $@ -c $<
