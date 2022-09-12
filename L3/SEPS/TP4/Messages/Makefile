# MAKEFILE pour Cours sur les files de messages
#
#

include ../Makefile.compilation 
include ../Makefile.dir         

#
#--------  Objets -------- 
#

fich_obj_test_messages=test_messages.o messages.o 

#
# Tests (executables+objets)
#

BIN = test_messages 

test_messages : $(fich_obj_test_messages) 
	$(CCLNK) $(CFLAGS) $(fich_obj_test_messages) -o test_messages 

test_messages.o : test_messages.c messages.h 
	$(CCOBJ) $(CFLAGS) test_messages.c -o test_messages.o -I./ 

#
#-------- Modules -------------
#

OBJ = messages.o

messages.o : messages.c messages.h 
	$(CCOBJ) $(CFLAGS) messages.c -o messages.o -I ./

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

all : $(OBJ) $(BIN)



