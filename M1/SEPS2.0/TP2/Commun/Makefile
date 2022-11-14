# MAKEFILE for Commun
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
fich_obj_test_commun = test_commun.o commun.o

#
#-------- Mains ---------------
#


#
#-------- Utilitaires ---------------
#

#
# --- Executables ---
#

BIN = test_commun

test_commun : $(fich_obj_test_commun)
	$(CCLNK) $(fich_obj_test_commun) $(CFLAGS) -o test_commun 

test_commun.o : test_commun.c commun.h
	$(CCOBJ) $(CFLAGS) test_commun.c -o test_commun.o -I./ 

#
#-------- Modules -------------
#

MOD = commun.o

commun.o : commun.c commun.h 
	$(CCOBJ) $(CFLAGS) commun.c -o commun.o -I./

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

all : $(MOD) $(BIN)


#
#-------- Test -------
#

tests : 
	@ echo "TEST commun"
	@ echo 
	./test_commun  
