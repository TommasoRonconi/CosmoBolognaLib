C = g++

FLAGS0 = -std=c++11 -fopenmp 
FLAGS = -O3 -unroll -Wall -Wextra -pedantic -Wfatal-errors -Werror

dirLib = $(PWD)/../../
dirH = $(dirLib)Headers/Lib/
dirHO = $(dirLib)Headers/Objects/
dirEH = $(dirLib)External/EH/
dir_Eigen = $(dirLib)External/eigen-3.3.4/
dir_CCfits = $(dirLib)External/CCfits/include
dirCUBA = $(dirLib)External/Cuba-4.2/

varDIR = -DDIRCOSMO=\"$(dirLib)\" -DDIRL=\"$(PWD)/\"

FLAGS_LIB = -Wl,-rpath,$(HOME)/lib/ -Wl,-rpath,$(dirLib) -L$(dirLib) -lFUNC
FLAGS_INC = -I$(HOME)/include/ -I/usr/local/include/ -I$(dirH) -I$(dirHO) -I$(dirEH) -I$(dirCUBA) -I$(dir_Eigen) -I$(dir_CCfits)

OBJ1 = integration_gsl.o
OBJ2 = integration_cuba.o
OBJ3 = minimisation.o
OBJ4 = fits.o

ES = so

SYS:=$(shell uname -s)

ifeq ($(SYS),Darwin)
        ES = dylib
endif

integration_gsl: $(OBJ1) 
	$(C) $(OBJ1) -o integration_gsl $(FLAGS_LIB) 

integration_cuba: $(OBJ2) 
	$(C) $(OBJ2) -o integration_cuba $(FLAGS_LIB) 

minimisation: $(OBJ3) 
	$(C) $(OBJ3) -o minimisation $(FLAGS_LIB) 

fits: $(OBJ4) 
	$(C) $(OBJ4) -o fits $(FLAGS_LIB) 

clean:
	rm -f *.o integration_gsl integration_cuba minimisation fits catalogue_with_weights.fits *~ \#* temp* core*

integration_gsl.o: integration_gsl.cpp makefile $(dirLib)*.$(ES)
	$(C) $(FLAGS0) $(FLAGS) $(FLAGS_INC) $(varDIR) -c integration_gsl.cpp 

integration_cuba.o: integration_cuba.cpp makefile $(dirLib)*.$(ES)
	$(C) $(FLAGS0) $(FLAGS) $(FLAGS_INC) $(varDIR) -c integration_cuba.cpp 

minimisation.o: minimisation.cpp makefile $(dirLib)*.$(ES)
	$(C) $(FLAGS0) $(FLAGS) $(FLAGS_INC) $(varDIR) -c minimisation.cpp 

fits.o: fits.cpp makefile $(dirLib)*.$(ES)
	$(C) $(FLAGS0) $(FLAGS) $(FLAGS_INC) $(varDIR) -c fits.cpp 

