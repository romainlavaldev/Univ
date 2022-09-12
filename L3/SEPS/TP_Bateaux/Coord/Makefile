# MAKEFILE for TDA Coord (coordonnees d'une case)
#
#

#
# Directories
#
#top_dir = /lium/buster1/jacob/Enseignements/Licence/L3/Inf310A_SE/TP/TP_Bataille_Navale
top_dir = ..
include $(top_dir)/Makefile.dir
include $(top_dir)/Makefile.compilation

#
# Object files
#

fich_obj_test_coord = test_coord.o coord.o 
fich_obj_test_coords = test_coords.o coords.o coord.o 

#
#-------- Mains ---------------
#


#
#-------- Utilitaires ---------------
#

#
# --- Tests ---
#

test_coord : $(fich_obj_test_coord)
	$(CCLNK) $(fich_obj_test_coord) $(FLAGS)  -o test_coord -I./ -I$(commun_dir)

test_coord.o : test_coord.c coord.h
	$(CCOBJ) $(FLAGS)  test_coord.c -o test_coord.o -I./ -I$(commun_dir)

test_coords : $(fich_obj_test_coords)
	$(CCLNK) $(fich_obj_test_coords) $(FLAGS)  -o test_coords -I./ -I$(commun_dir)

test_coords.o : test_coords.c coords.h
	$(CCOBJ) $(FLAGS)  test_coords.c -o test_coords.o -I./ -I$(commun_dir)

#
#-------- Modules -------------
#

coord.o : coord.c coord.h 
	$(CCOBJ) $(FLAGS) coord.c -o coord.o -I./ -I$(commun_dir)

coords.o : coords.c coords.h 
	$(CCOBJ) $(FLAGS) coords.c -o coords.o -I./ -I$(commun_dir)

#
#-------- Headers -------------
#

coord.h : $(commun_dir)/commun.h
	touch coord.h

coords.h : coord.h
	touch coords.h 

#
#-------- Clean objects -------
#

clean : 
	rm -f *.o 


#
#-------- All executables -------
#

all : test_coord test_coords

#
#-------- Tests -------
#

tests : 
	./test_coord 5 6 7
	./test_coords 10







