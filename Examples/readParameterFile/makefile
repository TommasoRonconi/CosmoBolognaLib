C = g++

FLAGS0 = -std=c++11 -fopenmp 
FLAGS = -O3 -unroll -Wall -Wextra -pedantic -Wfatal-errors -Werror 

dirLib = $(PWD)/../../
dirH = $(dirLib)Headers/Lib/
dirHO = $(dirLib)Headers/Objects/
dirHM = $(dirLib)Headers/Models/
dirEH = $(dirLib)External/EH/
dir_Eigen = $(dirLib)External/eigen-3.3.4/
dir_CCfits = $(dirLib)External/CCfits/include
dirCUBA = $(dirLib)External/Cuba-4.2/

varDIR = -DDIRCOSMO=\"$(dirLib)\" -DDIRL=\"$(PWD)/\"

FLAGS_LIB = -Wl,-rpath,$(HOME)/lib/ -Wl,-rpath,$(dirLib) -L$(dirLib) -lFUNC -lREADP
FLAGS_INC = -I$(HOME)/include/ -I/usr/local/include/ -I$(dirH) -I$(dirHO) -I$(dirHM) -I$(dirEH) -I$(dirCUBA) -I$(dir_Eigen) -I$(dir_CCfits)

OBJ = readParameterFile.o

ES = so

SYS:=$(shell uname -s)

ifeq ($(SYS),Darwin)
        ES = dylib
endif

readParameterFile: $(OBJ) 
	$(C) $(OBJ) -o readParameterFile $(FLAGS_LIB)

clean:
	rm -f *.o readParameterFile *~ \#* temp* core*


readParameterFile.o: readParameterFile.cpp makefile $(dirLib)*.$(ES)
	$(C) $(FLAGS0) $(FLAGS) $(FLAGS_INC) $(varDIR) -c readParameterFile.cpp

