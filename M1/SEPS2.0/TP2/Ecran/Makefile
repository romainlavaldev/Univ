# MAKEFILE pour l'Ecran
#
#

#
# Directories
#
top_dir = ..
include $(top_dir)/Makefile.compilation
include $(top_dir)/Makefile.dir

#
# Macros Object files
#

#--- mains




#--- tests

fich_obj_test_ecran = test_ecran.o \
	ecran.o \
	$(DirCommun)/commun.o \
	$(DirCoord)/coord.o 


#
#-------- Mains ---------------
#



#
#-------- Modules -------------
#

MOD = ecran.o

ecran.o : ecran.c ecran.h 
	$(CCOBJ) $(CFLAGS) ecran.c -o ecran.o -I./ \
	-I$(DirCommun) \
	-I$(DirCoord) 

#
#-------- Modules externes -------------
#

# --- Commun ---
include $(top_dir)/Makefile.Commun

# --- Coord ---
include $(top_dir)/Makefile.Coord

#
#-------- Tests -------------
#

BIN = test_ecran

test_ecran : $(fich_obj_test_ecran)
	$(CCLNK) $(CFLAGS) $(fich_obj_test_ecran) -o test_ecran $(LIB_CURSES)

test_ecran.o : test_ecran.c 
	$(CCOBJ) $(CFLAGS) test_ecran.c -o test_ecran.o -I./ \
	-I$(DirCommun) \
	-I$(DirCoord) 


#
#-------- Headers -------------
#

ecran.h : $(DirCommun)/commun.h $(DirCoord)/coord.h
	touch ecran.h

#
#-------- Clean objects -------
#

clean : 
	- rm $(BIN) 
	- rm *.o 
	- rm *~

#
#-------- All executables -------
#

all : $(MOD) $(BIN) 

#
#-------- All tests -------
#

tests : 
	./test_ecran 5 20


