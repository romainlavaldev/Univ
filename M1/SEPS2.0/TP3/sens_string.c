#include <stdio.h>
#include <sens_string.h>

extern
char * sens_string( sens_t s )
{
     switch( s )
     {
	case OUEST_EST : 
	  return( "->" ) ;
	case EST_OUEST : 
	  return( "<-" ) ;
	default : 
	  return( "??" ) ;
     }
}

extern
char * sens_blanc_string()
{
    return( "  " ) ;
}

extern
char * sens_vide_string()
{
    return( ".." ) ;
}
