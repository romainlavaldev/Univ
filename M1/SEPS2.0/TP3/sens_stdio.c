#include <stdio.h>
#include <sens_stdio.h>

extern
void sens_print( sens_t s )
{
     switch( s )
     {
	case OUEST_EST : 
	     printf( "->" ) ;
	     break ;
	case EST_OUEST : 
	     printf( "<-" ) ;
	     break ;
	default : 
	     printf( "??" ) ;
	     break ;
     }
}

extern
void sens_blanc_print()
{
    printf( "  " ) ;
}

extern
void sens_vide_print()
{
    printf( ".." ) ;
}
