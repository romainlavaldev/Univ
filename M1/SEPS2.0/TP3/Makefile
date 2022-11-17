include Makefile.compilation 

# MAKEFILE for TP Moniteur
#
#



#
# Directories
#


#
# Macros Object files
#

#--- mains

fich_obj_trafic_1 = trafic_1.o \
	sens_stdio.o \
	train.o train_stdio.o \
	voie_unique.o voie_unique_stdio.o \
	moniteur_voie_unique.o 


fich_obj_trafic_2 = trafic_2.o \
	sens_stdio.o \
	train.o train_stdio.o \
	voie_unique.o voie_unique_stdio.o \
	moniteur_voie_unique.o  \
	ligne.o ligne_stdio.o 

fich_obj_trafic_3 = trafic_3.o \
	ecran.o \
	sens_string.o sens_ncurses.o \
	train.o train_ncurses.o \
	voie_unique.o voie_unique_ncurses.o \
	moniteur_voie_unique.o  \
	ligne.o ligne_ncurses.o 


#--- tests

fich_obj_test_ecran = test_ecran.o \
	ecran.o 

fich_obj_test_sens = test_sens.o \
	sens_stdio.o sens_string.o

fich_obj_test_sens_ncurses = test_sens_ncurses.o \
	ecran.o \
	sens_ncurses.o 

fich_obj_test_train = test_train.o \
	sens_stdio.o \
	train.o train_stdio.o

fich_obj_test_train_ncurses = test_train_ncurses.o \
	ecran.o \
	sens_ncurses.o \
	train.o train_ncurses.o

fich_obj_test_voie_unique = test_voie_unique.o \
	sens_stdio.o \
	train.o train_stdio.o \
	voie_unique.o voie_unique_stdio.o 

fich_obj_test_voie_unique_ncurses = test_voie_unique_ncurses.o \
	ecran.o \
	sens_ncurses.o \
	train.o train_ncurses.o \
	voie_unique.o voie_unique_ncurses.o 

fich_obj_test_ligne = test_ligne.o \
	sens_stdio.o \
	train.o train_stdio.o \
	voie_unique.o voie_unique_stdio.o \
	moniteur_voie_unique.o \
	ligne.o ligne_stdio.o

fich_obj_test_ligne_ncurses = test_ligne_ncurses.o \
	ecran.o \
	sens_ncurses.o \
	train.o train_ncurses.o \
	voie_unique.o voie_unique_ncurses.o \
	moniteur_voie_unique.o \
	ligne.o ligne_ncurses.o 




#
#-------- Mains ---------------
#

BIN = trafic_1 trafic_2 trafic_3

trafic_1 : $(fich_obj_trafic_1)
	$(CCLNK) $(CFLAGS) $(fich_obj_trafic_1) $(opt) $(LIB_PTHREAD) $(MACRO_PTHREAD) -o trafic_1 

trafic_1.o : trafic_1.c voie_unique_stdio.h moniteur_voie_unique.h
	$(CCOBJ) $(CFLAGS) $(opt)  trafic_1.c -o trafic_1.o 

trafic_2 : $(fich_obj_trafic_2)
	$(CCLNK) $(CFLAGS) $(fich_obj_trafic_2) $(opt) $(LIB_PTHREAD) $(MACRO_PTHREAD) -o trafic_2 

trafic_2.o : trafic_2.c ligne_stdio.h
	$(CCOBJ) $(CFLAGS) $(opt)  trafic_2.c -o trafic_2.o

trafic_3 : $(fich_obj_trafic_3)
	$(CCLNK) $(CFLAGS) $(fich_obj_trafic_3) $(opt) $(LIB_PTHREAD) $(MACRO_PTHREAD) -o trafic_3 $(LIB_CURSES)

trafic_3.o : trafic_3.c ligne_ncurses.h
	$(CCOBJ) $(CFLAGS) $(opt)  trafic_3.c -o trafic_3.o 

#
#-------- Modules -------------
#

MOD = sens_stdio.o sens_ncurses.o sens_string.o \
	train.o train_stdio.o train_ncurses.o \
	voie_unique.o voie_unique_stdio.o voie_unique_ncurses.o \
	moniteur_voie_unique.o  \
	ligne.o ligne_stdio.o ligne_ncurses.o \
	ecran.o

# --- sens ---

sens_stdio.o : sens_stdio.c sens_stdio.h 
	$(CCOBJ) $(CFLAGS) $(opt)  sens_stdio.c -o sens_stdio.o 

sens_ncurses.o : sens_ncurses.c sens_ncurses.h 
	$(CCOBJ) $(CFLAGS) $(opt)  sens_ncurses.c -o sens_ncurses.o 

sens_string.o : sens_string.c sens_string.h 
	$(CCOBJ) $(CFLAGS) $(opt)  sens_string.c -o sens_string.o 

# --- train ---

train.o : train.c train.h 
	$(CCOBJ) $(CFLAGS) $(opt)  train.c -o train.o 

train_stdio.o : train_stdio.c train_stdio.h 
	$(CCOBJ) $(CFLAGS) $(opt)  train_stdio.c -o train_stdio.o 

train_ncurses.o : train_ncurses.c train_ncurses.h 
	$(CCOBJ) $(CFLAGS) $(opt)  train_ncurses.c -o train_ncurses.o 

# --- section voie unique ---

voie_unique.o : voie_unique.c voie_unique.h 
	$(CCOBJ) $(CFLAGS) $(opt)  voie_unique.c -o voie_unique.o 

voie_unique_stdio.o : voie_unique_stdio.c voie_unique_stdio.h 
	$(CCOBJ) $(CFLAGS) $(opt)  voie_unique_stdio.c -o voie_unique_stdio.o 

voie_unique_ncurses.o : voie_unique_ncurses.c voie_unique_ncurses.h 
	$(CCOBJ) $(CFLAGS) $(opt)  voie_unique_ncurses.c -o voie_unique_ncurses.o 



moniteur_voie_unique.o : moniteur_voie_unique.c moniteur_voie_unique.h
	$(CCOBJ) $(CFLAGS) $(opt)  moniteur_voie_unique.c -o moniteur_voie_unique.o 

# --- ecran ---

ecran.o : ecran.c ecran.h 
	$(CCOBJ) $(CFLAGS) $(opt)  ecran.c -o ecran.o 

# --- ligne ---

ligne.o : ligne.c ligne.h 
	$(CCOBJ) $(CFLAGS) $(opt)  ligne.c -o ligne.o 

ligne_stdio.o : ligne_stdio.c ligne_stdio.h 
	$(CCOBJ) $(CFLAGS) $(opt)  ligne_stdio.c -o ligne_stdio.o

ligne_ncurses.o : ligne_ncurses.c ligne_ncurses.h 
	$(CCOBJ) $(CFLAGS) $(opt)  ligne_ncurses.c -o ligne_ncurses.o 


#
#-------- Tests -------------
#
TESTS = test_sens test_sens_ncurses \
	test_train test_train_ncurses \
	test_voie_unique test_voie_unique_ncurses \
	test_ligne test_ligne_ncurses \
	test_ecran 

test_sens : $(fich_obj_test_sens)
	$(CCLNK) $(CFLAGS) $(fich_obj_test_sens) $(opt) -o test_sens 

test_sens.o : test_sens.c sens_stdio.h sens_string.h
	$(CCOBJ) $(CFLAGS) $(opt)  test_sens.c -o test_sens.o 

test_sens_ncurses : $(fich_obj_test_sens_ncurses)
	$(CCLNK) $(CFLAGS) $(fich_obj_test_sens_ncurses) $(opt) -o test_sens_ncurses $(LIB_CURSES)

test_sens_ncurses.o : test_sens_ncurses.c 
	$(CCOBJ) $(CFLAGS) $(opt)  test_sens_ncurses.c -o test_sens_ncurses.o 



test_train : $(fich_obj_test_train)
	$(CCLNK) $(CFLAGS) $(fich_obj_test_train) $(opt) -o test_train 

test_train.o : test_train.c 
	$(CCOBJ) $(CFLAGS) $(opt)  test_train.c -o test_train.o 

test_train_ncurses : $(fich_obj_test_train_ncurses)
	$(CCLNK) $(CFLAGS) $(fich_obj_test_train_ncurses) $(opt) -o test_train_ncurses $(LIB_CURSES)

test_train_ncurses.o : test_train_ncurses.c 
	$(CCOBJ) $(CFLAGS) $(opt)  test_train_ncurses.c -o test_train_ncurses.o 



test_voie_unique : $(fich_obj_test_voie_unique)
	$(CCLNK) $(CFLAGS) $(fich_obj_test_voie_unique) $(opt) $(LIB_PTHREAD) $(MACRO_PTHREAD) -o test_voie_unique 

test_voie_unique.o : test_voie_unique.c 
	$(CCOBJ) $(CFLAGS) $(opt)  test_voie_unique.c -o test_voie_unique.o

test_voie_unique_ncurses : $(fich_obj_test_voie_unique_ncurses)
	$(CCLNK) $(CFLAGS) $(fich_obj_test_voie_unique_ncurses) $(opt) $(LIB_PTHREAD) $(MACRO_PTHREAD) -o test_voie_unique_ncurses $(LIB_CURSES)

test_voie_unique_ncurses.o : test_voie_unique_ncurses.c 
	$(CCOBJ) $(CFLAGS) $(opt)  test_voie_unique_ncurses.c -o test_voie_unique_ncurses.o



test_ligne : $(fich_obj_test_ligne)
	$(CCLNK) $(CFLAGS) $(fich_obj_test_ligne) $(opt) $(LIB_PTHREAD) $(MACRO_PTHREAD) -o test_ligne

test_ligne.o : test_ligne.c voie_unique.h
	$(CCOBJ) $(CFLAGS) $(opt)  test_ligne.c -o test_ligne.o 

test_ligne_ncurses : $(fich_obj_test_ligne_ncurses)
	$(CCLNK) $(CFLAGS) $(fich_obj_test_ligne_ncurses) $(opt) $(LIB_PTHREAD) $(MACRO_PTHREAD) -o test_ligne_ncurses $(LIB_CURSES)

test_ligne_ncurses.o : test_ligne_ncurses.c voie_unique.h
	$(CCOBJ) $(CFLAGS) $(opt)  test_ligne_ncurses.c -o test_ligne_ncurses.o 


test_ecran : $(fich_obj_test_ecran)
	$(CCLNK) $(CFLAGS) $(fich_obj_test_ecran) $(opt) -o test_ecran $(LIB_CURSES)

test_ecran.o : test_ecran.c 
	$(CCOBJ) $(CFLAGS) $(opt)  test_ecran.c -o test_ecran.o 

#
#-------- Headers -------------
#

sens_stdio.h : sens.h
	touch sens_stdio.h 

sens_ncurses.h : sens.h
	touch sens_ncurses.h 

sens_string.h : sens.h
	touch sens_string.h

train.h : sens.h commun.h 
	touch train.h 

train_stdio.h : train.h sens_stdio.h
	touch train_stdio.h

train_ncurses.h : train.h sens_ncurses.h
	touch train_ncurses.h


voie_unique.h : train.h
	touch voie_unique.h

voie_unique_stdio.h : voie_unique.h train_stdio.h
	touch voie_unique_stdio.h

voie_unique_ncurses.h : voie_unique.h train_ncurses.h
	touch voie_unique_ncurses.h


moniteur_voie_unique.h : voie_unique.h 
	touch moniteur_voie_unique.h 


ligne.h : moniteur_voie_unique.h
	touch ligne.h 

ligne_stdio.h : ligne.h voie_unique_stdio.h
	touch ligne_stdio.h 

ligne_ncurses.h : ligne.h voie_unique_ncurses.h
	touch ligne_ncurses.h 


ecran.h : commun.h
	touch ecran.h

#
#-------- Clean objects -------
#

clean : 
	- rm $(BIN) $(TESTS) 
	- rm *.o 
	- rm *~

#
#-------- All executables -------
#

all : $(BIN) $(TESTS) 

#
#-------- Tags for emacs -------
#

tags :
	etags *.c *.h -o TAGS_TRAINS

#
#-------- All modules -------
#

modules : $(MOD)

#
#-------- All tests -------
#

tests : 
	@ echo "Tests sur stdio"
	./test_sens 
	./test_train  
	./test_voie_unique 
	./test_ligne 3
	@ echo "Tests sur ncurses"
	@ sleep 2
	./test_ecran
	./test_sens_ncurses 
	./test_train_ncurses 	
	./test_voie_unique_ncurses
	./test_ligne_ncurses 5 3 1 2 3  


#
#-------- Distrib -------
#

distrib : clean 
	- rm TP_Chemin_Fer.tar.gz
	tar cvf TP_Chemin_Fer.tar *.[ch] Makefile*
	gzip TP_Chemin_Fer.tar
