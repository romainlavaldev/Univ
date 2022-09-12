# MAKEFILE for TDA Bateau
#
#

#
# Directories
#
top_dir = ..
include $(top_dir)/Makefile.dir
include $(top_dir)/Makefile.compilation

#
# Object files
#

fich_obj_test_bateau = test_bateau.o bateau.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o

fich_obj_test_bateaux = test_bateaux.o bateaux.o bateau.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o


#
#-------- Mains ---------------
#


#
# --- Tests ---
#

test_bateau : $(fich_obj_test_bateau)
	$(CCLNK) $(fich_obj_test_bateau) $(FLAGS)  -o test_bateau -I$(commun_dir) -I$(coord_dir) -I$(bateau_dir) 

test_bateau.o : test_bateau.c bateau.h
	$(CCOBJ) $(FLAGS)  test_bateau.c -o test_bateau.o -I$(commun_dir) -I$(coord_dir) -I$(bateau_dir)


test_bateaux : $(fich_obj_test_bateaux)
	$(CCLNK) $(fich_obj_test_bateaux) $(FLAGS)  -o test_bateaux -I$(commun_dir) -I$(coord_dir) -I$(bateau_dir) 

test_bateaux.o : test_bateaux.c bateau.h
	$(CCOBJ) $(FLAGS)  test_bateaux.c -o test_bateaux.o -I$(commun_dir) -I$(coord_dir) -I$(bateau_dir)

#
#-------- Modules -------------
#

bateau.o : bateau.c bateau.h  
	$(CCOBJ) $(FLAGS)  bateau.c -o bateau.o -I$(commun_dir) -I$(coord_dir) -I./

bateaux.o : bateaux.c bateaux.h  
	$(CCOBJ) $(FLAGS)  bateaux.c -o bateaux.o -I$(commun_dir) -I$(coord_dir) -I./

$(coord_dir)/coord.o : 
	cd $(coord_dir) ; make -f Makefile coord.o

$(coord_dir)/coords.o : 
	cd $(coord_dir) ; make -f Makefile coords.o 

#
#-------- Headers -------------
#

bateau.h : $(coord_dir)/coords.h
	touch bateau.h

bateaux.h : bateau.h
	touch bateaux.h

#
#-------- Clean objects -------
#

clean : 
	- rm *.o 


#
#-------- All executables -------
#

all : test_bateau test_bateaux

#
#-------- Tests -------
#

tests :
	./test_bateau
	./test_bateaux 10 
