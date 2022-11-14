# MAKEFILE for jeu de la vie
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

fich_obj_automate_synchrone_stdio = automate_synchrone_stdio.o \
	$(DirCommun)/commun.o \
	$(DirAutomate)/automate.o $(DirAutomate)/automate_stdio.o \
	$(DirCoord)/coord.o $(DirCoord)/coords.o $(DirCoord)/coord_stdio.o $(DirCoord)/coords_stdio.o \
	$(DirCellule)/cellule.o $(DirCellule)/cellule_stdio.o

fich_obj_automate_asynchrone_stdio = automate_asynchrone_stdio.o \
	$(DirCommun)/commun.o \
	$(DirAutomate)/automate.o $(DirAutomate)/automate_stdio.o \
	$(DirCoord)/coord.o $(DirCoord)/coords.o $(DirCoord)/coord_stdio.o $(DirCoord)/coords_stdio.o \
	$(DirCellule)/cellule.o $(DirCellule)/cellule_stdio.o

fich_obj_automate_asynchrone_memoire_stdio = automate_asynchrone_memoire_stdio.o \
	$(DirCommun)/commun.o \
	$(DirAutomate)/automate.o $(DirAutomate)/automate_stdio.o \
	$(DirCoord)/coord.o $(DirCoord)/coords.o $(DirCoord)/coord_stdio.o $(DirCoord)/coords_stdio.o \
	$(DirCellule)/cellule.o $(DirCellule)/cellule_stdio.o


fich_obj_automate_synchrone_ecran = automate_synchrone_ecran.o \
	$(DirCommun)/commun.o \
	$(DirAutomate)/automate.o $(DirAutomate)/automate_ecran.o \
	$(DirCoord)/coord.o $(DirCoord)/coords.o $(DirCoord)/coord_stdio.o $(DirCoord)/coords_stdio.o \
	$(DirCellule)/cellule.o $(DirCellule)/cellule_ecran.o \
	$(DirEcran)/ecran.o

fich_obj_automate_asynchrone_ecran = automate_asynchrone_ecran.o \
	$(DirCommun)/commun.o \
	$(DirAutomate)/automate.o $(DirAutomate)/automate_ecran.o \
	$(DirCoord)/coord.o $(DirCoord)/coords.o $(DirCoord)/coord_stdio.o $(DirCoord)/coords_stdio.o \
	$(DirCellule)/cellule.o $(DirCellule)/cellule_ecran.o \
	$(DirEcran)/ecran.o

fich_obj_automate_asynchrone_memoire_ecran = automate_asynchrone_memoire_ecran.o \
	$(DirCommun)/commun.o \
	$(DirAutomate)/automate.o $(DirAutomate)/automate_ecran.o \
	$(DirCoord)/coord.o $(DirCoord)/coords.o $(DirCoord)/coord_stdio.o $(DirCoord)/coords_stdio.o \
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

BIN = automate_synchrone_stdio automate_asynchrone_stdio automate_asynchrone_memoire_stdio automate_synchrone_ecran automate_asynchrone_ecran automate_asynchrone_memoire_ecran

automate_synchrone_stdio : $(fich_obj_automate_synchrone_stdio)
	$(CCLNK) $(fich_obj_automate_synchrone_stdio) $(CFLAGS) -o automate_synchrone_stdio 

automate_synchrone_stdio.o : automate_synchrone_stdio.c $(DirAutomate)/automate_stdio.h $(DirCoord)/coords_stdio.h
	$(CCOBJ) $(CFLAGS) automate_synchrone_stdio.c -o automate_synchrone_stdio.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirCellule) -I$(DirAutomate)

automate_asynchrone_stdio : $(fich_obj_automate_asynchrone_stdio)
	$(CCLNK) $(fich_obj_automate_asynchrone_stdio) $(CFLAGS) -o automate_asynchrone_stdio 

automate_asynchrone_stdio.o : automate_asynchrone_stdio.c $(DirAutomate)/automate_stdio.h $(DirCoord)/coords_stdio.h
	$(CCOBJ) $(CFLAGS) automate_asynchrone_stdio.c -o automate_asynchrone_stdio.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirCellule) -I$(DirAutomate)

automate_asynchrone_memoire_stdio : $(fich_obj_automate_asynchrone_memoire_stdio)
	$(CCLNK) $(fich_obj_automate_asynchrone_memoire_stdio) $(CFLAGS) -o automate_asynchrone_memoire_stdio 

automate_asynchrone_memoire_stdio.o : automate_asynchrone_memoire_stdio.c $(DirAutomate)/automate_stdio.h $(DirCoord)/coords_stdio.h
	$(CCOBJ) $(CFLAGS) automate_asynchrone_memoire_stdio.c -o automate_asynchrone_memoire_stdio.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirCellule) -I$(DirAutomate)


automate_synchrone_ecran : $(fich_obj_automate_synchrone_ecran)
	$(CCLNK) $(fich_obj_automate_synchrone_ecran) $(CFLAGS) -o automate_synchrone_ecran $(LIB_CURSES)

automate_synchrone_ecran.o : automate_synchrone_ecran.c $(DirAutomate)/automate_ecran.h $(DirCoord)/coords_stdio.h
	$(CCOBJ) $(CFLAGS) automate_synchrone_ecran.c -o automate_synchrone_ecran.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirCellule) -I$(DirAutomate) -I$(DirEcran)

automate_asynchrone_ecran : $(fich_obj_automate_asynchrone_ecran)
	$(CCLNK) $(fich_obj_automate_asynchrone_ecran) $(CFLAGS) -o automate_asynchrone_ecran $(LIB_CURSES)

automate_asynchrone_ecran.o : automate_asynchrone_ecran.c $(DirAutomate)/automate_ecran.h $(DirCoord)/coords_stdio.h
	$(CCOBJ) $(CFLAGS) automate_asynchrone_ecran.c -o automate_asynchrone_ecran.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirCellule) -I$(DirAutomate) -I$(DirEcran)

automate_asynchrone_memoire_ecran : $(fich_obj_automate_asynchrone_memoire_ecran)
	$(CCLNK) $(fich_obj_automate_asynchrone_memoire_ecran) $(CFLAGS) -o automate_asynchrone_memoire_ecran $(LIB_CURSES)

automate_asynchrone_memoire_ecran.o : automate_asynchrone_memoire_ecran.c $(DirAutomate)/automate_ecran.h $(DirCoord)/coords_stdio.h
	$(CCOBJ) $(CFLAGS) automate_asynchrone_memoire_ecran.c -o automate_asynchrone_memoire_ecran.o -I./ -I$(DirCommun) -I$(DirCoord) -I$(DirCellule) -I$(DirAutomate) -I$(DirEcran)

#
#-------- Modules -------------
#

# --- Automate ---
include $(top_dir)/Makefile.Automate

# --- Coord ---
include $(top_dir)/Makefile.Coord

# --- Cellule ---
include $(top_dir)/Makefile.Cellule

# --- Commun ---
include $(top_dir)/Makefile.Commun

#
#-------- Headers -------------
#



#
#-------- Clean objects -------
#

clean : 
	- rm *.o $(BIN) *~


#
#-------- All executables -------
#

all : $(BIN)

#
#-------- Make tags  -------
#



#
#-------- All executables -------
#

test : 
