# MAKEFILE for TP Bataille Navale 
# version Verrous
#
#

top_dir = ..
include $(top_dir)/Makefile.dir
include $(top_dir)/Makefile.compilation


#
# Object files
#

fich_obj_navire = navire.o \
	$(mer_dir)/mer.o \
	$(bateau_dir)/bateau.o $(bateau_dir)/bateaux.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o

fich_obj_vision = vision.o \
	$(mer_dir)/mer.o \
	$(bateau_dir)/bateau.o $(bateau_dir)/bateaux.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o 

#
#-------- Mains ---------------
#

navire : $(fich_obj_navire)
	$(CCLNK) $(fich_obj_navire) $(FLAGS)  -o navire -I./ -I$(commun_dir) -I$(coord_dir) -I$(bateau_dir) -I$(mer_dir)

navire.o : navire.c $(commun_dir)/commun.h $(coord_dir)/coord.h $(bateau_dir)/bateau.h $(mer_dir)/mer.h
	$(CCOBJ) $(FLAGS)  navire.c -o navire.o -I./ -I$(commun_dir) -I$(coord_dir) -I$(bateau_dir) -I$(mer_dir)

vision : $(fich_obj_vision)
	$(CCLNK) $(fich_obj_vision) $(FLAGS)  -o vision -I$(commun_dir) -I$(mer_dir)

vision.o : vision.c $(commun_dir)/commun.h $(mer_dir)/mer.h
	$(CCOBJ) $(FLAGS)  vision.c -o vision.o -I$(commun_dir) -I$(coord_dir) -I$(bateau_dir) -I$(mer_dir)

#
# --- Tests ---
#


#
#-------- Modules -------------
#

$(mer_dir)/mer.o : 
	cd $(mer_dir) ; make -f Makefile mer.o 

$(bateau_dir)/bateau.o : 
	cd $(bateau_dir) ; make -f Makefile bateau.o 
$(bateau_dir)/bateaux.o : 
	cd $(bateau_dir) ; make -f Makefile bateaux.o 

$(coord_dir)/coord.o : 
	cd $(coord_dir) ; make -f Makefile coord.o 
$(coord_dir)/coords.o : 
	cd $(coord_dir) ; make -f Makefile coords.o 

#
#-------- Headers -------------
#

#
#-------- Clean objects -------
#

clean : 
	- rm *.o 


#
#-------- All executables -------
#

all : navire vision

#
#-------- All tests -------
#

#
#-------- Tags -------
#

tags :
	etags *.c 
#
#------- Program verifier ----------
#

lint :
	lint navire.c $(coord_dir)/coord.c $(bateau_dir)/bateau.c $(mer_dir)/mer.c -I$(commun_dir) -I$(mer_dir) -I$(coord_dir) -I$(bateau_dir)
