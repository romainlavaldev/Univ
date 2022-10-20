# MAKEFILE pour TP sur la course de Petits Chevaux
#
#

#
# Directories
#


#
# Object files
#

fich_obj_cheval = cheval.o piste.o cell.o liste.o elem.o commun.o
fich_obj_test_piste = test_piste.o piste.o cell.o commun.o
fich_obj_test_liste = test_liste.o elem.o liste.o cell.o commun.o

#
# Options for compilation
#

GCCOBJ = gcc -c 
GCCLNK = gcc 

# compilation sous Linux
#opt_SE = -D_LINUX_
# compilation sous Solaris
#opt_SE = -D_SOLARIS_
# compilation sous MAC
opt_SE = -D_MAC_OS_X

# Option for debugger
opt = -g -Wall -D_DEBUG_
# opt = -O2 -Wall
#
#
#

#
#-------- Mains ---------------
#

cheval : $(fich_obj_cheval)
	$(GCCLNK) $(fich_obj_cheval) $(opt) -o cheval -I ./

cheval.o : cheval.c 
	$(GCCOBJ) $(opt_SE) $(opt) cheval.c -o cheval.o -I ./

#
# --- Tests ---
#

test_piste : $(fich_obj_test_piste)
	$(GCCLNK) $(fich_obj_test_piste) $(opt) -o test_piste -I ./

test_piste.o : test_piste.c 
	$(GCCOBJ) $(opt_SE) $(opt) test_piste.c -o test_piste.o -I ./


test_liste : $(fich_obj_test_liste)
	$(GCCLNK) $(fich_obj_test_liste) $(opt) -o test_liste -I ./

test_liste.o : test_liste.c 
	$(GCCOBJ) $(opt_SE) $(opt) test_liste.c -o test_liste.o -I ./

#
#-------- Modules -------------
#

elem.o : elem.h elem.c
	$(GCCOBJ) $(opt_SE) $(opt) elem.c -o elem.o -I ./	

liste.o : liste.h liste.c
	$(GCCOBJ) $(opt_SE) $(opt) liste.c -o liste.o -I ./	

piste.o : piste.c piste.h 
	$(GCCOBJ) $(opt_SE) $(opt) piste.c -o piste.o -I ./

cell.o : cell.c cell.h 
	$(GCCOBJ) $(opt_SE) $(opt) cell.c -o cell.o -I ./

commun.o : commun.c commun.h 
	$(GCCOBJ) $(opt_SE) $(opt) commun.c -o commun.o -I ./

#
#-------- Headers -------------
#

#
#-------- Clean objects -------
#

clean : 
	rm -f *.o 


#
#-------- All executables -------
#

all :  cheval test_piste test_liste

#
#-------- All tests -------
#

tests :
	./test_piste
	./test_liste


#
#-------- Tags -------
#

tags : *.c *.h
	etags *.c *.h
