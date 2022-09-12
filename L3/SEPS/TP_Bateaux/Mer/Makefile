# MAKEFILE for TDA Mer in TP Bataille Navale
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

fich_obj_test_mer = test_mer.o mer.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o \
	$(bateau_dir)/bateau.o

fich_obj_init_fich_mer = init_fich_mer.o mer.o  \
	$(coord_dir)/coord.o $(coord_dir)/coords.o \
	$(bateau_dir)/bateau.o



#
#-------- Mains ---------------
#

init_fich_mer : $(fich_obj_init_fich_mer)
	$(CCLNK) $(fich_obj_init_fich_mer) $(FLAGS)  -o init_fich_mer -I./ -I$(commun_dir) -I$(mer_dir) -I$(bateau_dir) -I$(coord_dir)

init_fich_mer.o : init_fich_mer.c mer.h
	$(CCOBJ) $(FLAGS)  init_fich_mer.c -o init_fich_mer.o -I./ -I$(commun_dir) -I$(mer_dir) -I$(bateau_dir) -I$(coord_dir)

#
# --- Tests ---
#

test_mer : $(fich_obj_test_mer)
	$(CCLNK) $(fich_obj_test_mer) $(FLAGS)  -o test_mer -I./ -I$(commun_dir) -I$(mer_dir) -I$(bateau_dir)

test_mer.o : test_mer.c $(commun_dir)/commun.h $(coord_dir)/coord.h mer.h
	$(CCOBJ) $(FLAGS)  test_mer.c -o test_mer.o -I./ -I$(commun_dir) -I$(mer_dir) -I$(coord_dir) -I$(bateau_dir)

#
#-------- Modules -------------
#

mer.o : mer.c mer.h 
	$(CCOBJ) $(FLAGS)  mer.c -o mer.o -I./ -I$(commun_dir) -I$(mer_dir) -I$(coord_dir) -I$(bateau_dir)

$(coord_dir)/coord.o :
	cd $(coord_dir) ; make -f Makefile coord.o 

$(coord_dir)/coords.o :
	cd $(coord_dir) ; make -f Makefile coords.o 

$(bateau_dir)/bateau.o :
	cd $(bateau_dir) ; make -f Makefile bateau.o 

#
#-------- Headers -------------
#

mer.h : $(commun_dir)/commun.h $(coord_dir)/coord.h $(bateau_dir)/bateau.h
	touch mer.h

#
#-------- Clean objects -------
#

clean : 
	- rm *.o 


#
#-------- All executables -------
#

all : init_fich_mer test_mer 

#
#-------- Tests -------
#

tests : 
	./init_fich_mer ../Fichiers/mer.bin 10 10 
	./test_mer ../Fichiers/mer.bin 10 
	rm ../Fichiers/mer.bin




