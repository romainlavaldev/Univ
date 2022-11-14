# MAKEFILE for TDA Coord (coordonnees d'une case)
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

fich_obj_test_coord_stdio = test_coord_stdio.o \
	coord.o coord_stdio.o \
	$(DirCommun)/commun.o

fich_obj_test_coords_stdio = test_coords_stdio.o \
	coords.o coords_stdio.o \
	coord.o coord_stdio.o \
	$(DirCommun)/commun.o

#
#-------- Mains ---------------
#


#
#-------- Utilitaires ---------------
#

#
# --- Executables ---
#

BIN = test_coord_stdio test_coords_stdio

test_coord_stdio : $(fich_obj_test_coord_stdio)
	$(CCLNK) $(fich_obj_test_coord_stdio) $(CFLAGS) -o test_coord_stdio 

test_coord_stdio.o : test_coord_stdio.c coord_stdio.h
	$(CCOBJ) $(CFLAGS) test_coord_stdio.c -o test_coord_stdio.o -I./ -I$(DirCommun)

test_coords_stdio : $(fich_obj_test_coords_stdio)
	$(CCLNK) $(fich_obj_test_coords_stdio) $(CFLAGS) -o test_coords_stdio 

test_coords_stdio.o : test_coords_stdio.c coords_stdio.h
	$(CCOBJ) $(CFLAGS) test_coords_stdio.c -o test_coords_stdio.o -I./ -I$(DirCommun)

#
#-------- Modules -------------
#

MOD = coord.o coord_stdio.o coords.o coords_stdio.o

# --- Coord ---

coord.o : coord.c coord.h 
	$(CCOBJ) $(CFLAGS) coord.c -o coord.o -I./ -I$(DirCommun)

coord_stdio.o : coord_stdio.c coord_stdio.h
	$(CCOBJ) $(CFLAGS) coord_stdio.c -o coord_stdio.o -I./ -I$(DirCommun)

coords.o : coords.c coords.h 
	$(CCOBJ) $(CFLAGS) coords.c -o coords.o -I./ -I$(DirCommun)

coords_stdio.o :  coords_stdio.c coords_stdio.h 
	$(CCOBJ) $(CFLAGS) coords_stdio.c -o coords_stdio.o -I./ -I$(DirCommun)

# --- Commun ---
include $(top_dir)/Makefile.Commun

#
#-------- Headers -------------
#

coord.h : $(DirCommun)/commun.h
	touch coord.h

coords.h : coord.h
	touch coords.h

coord_stdio.h : coord.h
	touch coord_stdio.h

coords_stdio.h : coords.h
	touch coords_stdio.h


#
#-------- Clean objects -------
#

clean : 
	- rm *.o $(BIN) *~


#
#-------- All executables -------
#

all : $(MOD) $(BIN)


#
#-------- Test -------
#

tests : 
	@ echo "TEST COORD SUR STDIO"
	@ echo 
	./test_coord_stdio 1 2 
	@ echo "TEST COORDS SUR STDIO"
	@ echo 
	./test_coords_stdio 10
