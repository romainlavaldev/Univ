# MAKEFILE for TDA Cellule
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

fich_obj_test_cellule_stdio = test_cellule_stdio.o \
	cellule.o cellule_stdio.o \
	$(DirCommun)/commun.o \
	$(DirCoord)/coord.o $(DirCoord)/coord_stdio.o \
	$(DirCoord)/coords.o $(DirCoord)/coords_stdio.o

fich_obj_test_cellule_ecran = test_cellule_ecran.o \
	cellule.o cellule_ecran.o \
	$(DirCommun)/commun.o \
	$(DirCoord)/coord.o \
	$(DirCoord)/coords.o \
	$(DirEcran)/ecran.o

#
#-------- Mains ---------------
#


#
#-------- Utilitaires ---------------
#

#
# --- Tests ---
#
BIN= test_cellule_stdio test_cellule_ecran

test_cellule_stdio : $(fich_obj_test_cellule_stdio)
	$(CCLNK) $(fich_obj_test_cellule_stdio) $(CFLAGS) -o test_cellule_stdio 

test_cellule_stdio.o : test_cellule_stdio.c cellule_stdio.h
	$(CCOBJ) $(CFLAGS) test_cellule_stdio.c -o test_cellule_stdio.o -I./ -I$(DirCommun) -I$(DirCoord)

test_cellule_ecran : $(fich_obj_test_cellule_ecran)
	$(CCLNK) $(fich_obj_test_cellule_ecran) $(CFLAGS) -o test_cellule_ecran $(LIB_CURSES)

test_cellule_ecran.o : test_cellule_ecran.c cellule_stdio.h
	$(CCOBJ) $(CFLAGS) test_cellule_ecran.c -o test_cellule_ecran.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirEcran)

#
#-------- Modules -------------
#

MOD = cellule.o cellule_stdio.o cellule_ecran.o

# --- Cellule ---

cellule.o : cellule.c cellule.h 
	$(CCOBJ) $(CFLAGS) cellule.c -o cellule.o -I./ -I$(DirCommun) -I$(DirCoord) 

cellule_stdio.o : cellule_stdio.c cellule_stdio.h  
	$(CCOBJ) $(CFLAGS) cellule_stdio.c -o cellule_stdio.o -I./ -I$(DirCommun) -I$(DirCoord)

cellule_ecran.o : cellule_ecran.c cellule_ecran.h  
	$(CCOBJ) $(CFLAGS) cellule_ecran.c -o cellule_ecran.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirEcran)

# --- Commun ---
include $(top_dir)/Makefile.Commun

# --- Coord ---
include $(top_dir)/Makefile.Coord

# --- Ecran ---
include $(top_dir)/Makefile.Ecran


#
#-------- Headers -------------
#

cellule.h : $(DirCommun)/commun.h $(DirCoord)/coord.h
	touch cellule.h

cellule_stdio.h : cellule.h $(DirCoord)/coord_stdio.h
	touch cellule_stdio.h

cellule_ecran.h : cellule.h $(DirEcran)/ecran.h 
	touch cellule_ecran.h

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
#-------- All executables -------
#

tests : 
	@ echo "TEST CELLULE SUR STDIO" 
	@ echo 
	./test_cellule_stdio 10 10

	@ echo "TEST CELLULE SUR ECRAN" 
	@ echo 
	./test_cellule_ecran 10 20 5 10


