# MAKEFILE for TDA Automate
#
#


#
# Directories
#
top_dir = ..
include $(top_dir)/Makefile.compilation
include $(top_dir)/Makefile.dir

#
# Object files
#

fich_obj_test_automate_stdio = test_automate_stdio.o \
	automate.o automate_stdio.o \
	$(DirCommun)/commun.o \
	$(DirCoord)/coord.o $(DirCoord)/coords.o $(DirCoord)/coord_stdio.o $(DirCoord)/coords_stdio.o \
	$(DirCellule)/cellule.o $(DirCellule)/cellule_stdio.o

fich_obj_test_automate_ecran = test_automate_ecran.o \
	automate.o automate_ecran.o \
	$(DirCommun)/commun.o \
	$(DirCoord)/coord.o $(DirCoord)/coords.o  $(DirCoord)/coord_stdio.o $(DirCoord)/coords_stdio.o \
	$(DirCellule)/cellule.o $(DirCellule)/cellule_ecran.o \
	$(DirEcran)/ecran.o

#
#
#-------- Mains ---------------
#


#
#-------- Utilitaires ---------------
#

#
# --- Executables ---
#

BIN = test_automate_stdio test_automate_ecran

test_automate_stdio : $(fich_obj_test_automate_stdio)
	$(CCLNK) $(fich_obj_test_automate_stdio) $(CFLAGS) -o test_automate_stdio 

test_automate_stdio.o : test_automate_stdio.c automate_stdio.h $(DirCoord)/coords_stdio.h
	$(CCOBJ) $(CFLAGS) test_automate_stdio.c -o test_automate_stdio.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirCellule)

test_automate_ecran : $(fich_obj_test_automate_ecran)
	$(CCLNK) $(fich_obj_test_automate_ecran) $(CFLAGS) -o test_automate_ecran $(LIB_CURSES)

test_automate_ecran.o : test_automate_ecran.c automate_ecran.h 
	$(CCOBJ) $(CFLAGS) test_automate_ecran.c -o test_automate_ecran.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirCellule) -I$(DirEcran)

#
#-------- Modules -------------
#

# --- Automate ---

MOD = automate.o automate_stdio.o automate_ecran.o

automate.o : automate.c automate.h
	$(CCOBJ) $(CFLAGS) automate.c -o automate.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirCellule)


automate_stdio.o : automate_stdio.c automate_stdio.h
	$(CCOBJ) $(CFLAGS) automate_stdio.c -o automate_stdio.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirCellule)

automate_ecran.o : automate_ecran.c automate_ecran.h
	$(CCOBJ) $(CFLAGS) automate_ecran.c -o automate_ecran.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirCellule) -I$(DirEcran)

# --- Commun ---
include $(top_dir)/Makefile.Commun

# --- Coord ---
include $(top_dir)/Makefile.Coord

# --- Cellule ---
include $(top_dir)/Makefile.Cellule

# --- Ecran ---
include $(top_dir)/Makefile.Ecran

#
#-------- Headers -------------
#

automate.h : $(DirCoord)/coords.h $(DirCellule)/cellule.h
	touch automate.h

automate_stdio.h : automate.h
	touch automate_stdio.h

automate_ecran.h : automate.h $(DirCellule)/cellule_ecran.h
	touch automate_ecran.h

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
#-------- Tests  -------
#


#
#-------- All executables -------
#

tests : 
	@ echo "TEST AUTOMATE STANDARD" 
	@ echo
	echo " " > input
	./test_automate_stdio < input
	rm input 
	@ echo "TEST AUTOMATE ECRAN" 
	@ echo 
	./test_automate_ecran
