# MAKEFILE for TP Course de Processus
# version Sans perte de message/paquet
#
#
top_dir = ..
include $(top_dir)/Makefile.dir
include $(top_dir)/Makefile.compilation



#
# Object files
#

fich_obj_coureur = coureur.o \
	$(DirMessages)/messages.o 

#
#-------- Mains ---------------
#

BIN= coureur

coureur : $(fich_obj_coureur)
	$(CCLNK) $(fich_obj_coureur) $(FLAGS)  -o coureur  

coureur.o : coureur.c $(DirMessages)/messages.h
	$(CCOBJ) $(FLAGS)  coureur.c -o coureur.o -I./ -I./ -I$(DirMessages) 

#
# --- Tests ---
#


#
#-------- Modules externes -------------
#

$(DirMessages)/messages.o : 
	cd $(DirMessages) ; make -f Makefile messages.o 

#
#-------- Headers -------------
#

#
#-------- Clean objects -------
#

clean : 



#
#-------- All executables -------
#

all : $(BIN)
