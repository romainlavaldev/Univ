# MAKEFILE for TP Bataille Navale
#
#

#
# Directories
#

top_dir = .
include $(top_dir)/Makefile.dir 

all : 
	cd $(coord_dir) ; make -f Makefile all 
	cd $(bateau_dir) ; make -f Makefile all 
	cd $(mer_dir) ; make -f Makefile all 
	cd $(verrous_dir) ; make -f Makefile all 
	cd $(signaux_dir) ; make -f Makefile all 



clean :
	cd $(coord_dir) ; make -f Makefile clean 
	cd $(bateau_dir) ; make -f Makefile clean 
	cd $(mer_dir) ; make -f Makefile clean 
	cd $(verrous_dir) ; make -f Makefile clean 
	cd $(signaux_dir) ; make -f Makefile clean 



tags : 
	etags --language=c  */*.[ch] --output=BATAILLE_NAVALE.TAGS

tests : 
	cd $(bateau_dir) ; make -f Makefile tests
	cd $(coord_dir) ; make -f Makefile tests
	cd $(mer_dir) ; make -f Makefile tests

dist : 
	find $(distrib_dir)/TP_Bataille_Navale \( -name '*~' -o -name '*.o' \) -exec rm {} \;
	cp $(commun_dir)/*.[ch] $(distrib_dir)/TP_Bataille_Navale/Commun/.
	cp $(coord_dir)/*.c $(coord_dir)/*.h $(coord_dir)/Makefile $(distrib_dir)/TP_Bataille_Navale/Coord/. 
	cp $(mer_dir)/*.[hc] $(mer_dir)/Makefile $(distrib_dir)/TP_Bataille_Navale/Mer/.
	cp $(bateau_dir)/*.[ch] $(bateau_dir)/Makefile  $(distrib_dir)/TP_Bataille_Navale/Bateau/.
#       Dans $(verrous_dir) : les squelettes navire.c et vision.c sont deja installes et on ne les ecrase pas par leur solution
	cp $(verrous_dir)/Makefile $(verrous_dir)/lancer_navires.sh $(distrib_dir)/TP_Bataille_Navale/Verrous/.
#       Dans $(signaux_dir) : les squelettes navire.c et amiral.c sont deja installes et on ne les ecrase pas par leur solution
	cp $(signaux_dir)/Makefile $(signaux_dir)/lancer_navires.sh $(distrib_dir)/TP_Bataille_Navale/Signaux/.
	cp Makefile* $(distrib_dir)/TP_Bataille_Navale/.
	cp Sujet/sujet_tp_bataille.pdf $(distrib_dir)/TP_Bataille_Navale/Sujet/.
	- rm $(distrib_dir)/TP_Bataille_Navale.tar.gz
#       Dans $(distrib_dir)/TP_Bataille_Navale : le README est deja installe
	cd $(distrib_dir) ; tar cvf TP_Bataille_Navale.tar TP_Bataille_Navale ; gzip TP_Bataille_Navale.tar 

