# MAKEFILE for Jeu de la Vie 
#
#

#
# Directories
#
top_dir = .
include Makefile.dir

all :
	cd $(DirCommun) ; make -f Makefile all ; cd $(top_dir)
	cd $(DirCoord) ; make -f Makefile all ; cd $(top_dir)
	cd $(DirCellule) ; make -f Makefile all ; cd $(top_dir)
	cd $(DirAutomate) ; make -f Makefile all ; cd $(top_dir)
	cd $(DirEcran) ; make -f Makefile all ; cd $(top_dir)
	cd $(DirProgStandard) ; make -f Makefile all ; cd $(top_dir) 

clean :
	- find . -name "*~" -exec rm {} \;
	cd $(DirCommun) ; make -f Makefile clean ; cd $(top_dir)	
	cd $(DirCoord) ; make -f Makefile clean ; cd $(top_dir)
	cd $(DirCellule) ; make -f Makefile clean ; cd $(top_dir)
	cd $(DirAutomate) ; make -f Makefile clean ; cd $(top_dir)
	cd $(DirEcran) ; make -f Makefile clean ; cd $(top_dir)
	cd $(DirProgStandard) ; make -f Makefile clean ; cd $(top_dir)

tags :
	etags */*.c */*.h -o TAGS_JEUVIE


tests :
	cd $(DirCommun) ; make -f Makefile tests ; cd $(top_dir)
	cd $(DirEcran) ; make -f Makefile tests ; cd $(top_dir)
	cd $(DirCoord) ; make -f Makefile tests ; cd $(top_dir)
	cd $(DirCellule) ; make -f Makefile tests ; cd $(top_dir)
	cd $(DirAutomate) ; make -f Makefile tests ; cd $(top_dir)

#
#-- Documentation
#

doc :
	$(doxygen) config_doxygen
