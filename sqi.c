#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nstdio.h"

#define NINT   3
#define NTIMES 5
#define NSIZE 10

int main(int argc, char **argv)
{
    int      it, i ;
    int      iter ;
    double   array_o[ NTIMES ][ NSIZE ] ;
    double   array_i[ NTIMES ][ NSIZE ] ;
///
    NET      *nt ;
    ND       *nd ;
    NHDL     *hdl ;
    char     *ipaddr_r = argv[ 1 ] ;
    char     *port_0   = argv[ 2 ] ;

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    for( it = 0 ; it < NTIMES ; it++ ) {
        for( i = 0 ; i < NSIZE ; i++ ) {
            array_o[ it ][ i ] = 0 ;
            array_i[ it ][ i ] = 0 ;
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    nt = setnet( ipaddr_r, port_0, NTCP ) ;
    nd = nopen( nt, "c" ) ;
///
    fprintf( stdout, "sqi: here.\n" ) ;
    fprintf( stdout, "sqi: open as client:  %s %s\n", ipaddr_r, port_0 ) ;

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    for( iter = 0 ; iter < NINT ; iter++ ) {
        ///
        /// recv array_i
        ///
        for( it = 0 ; it < NTIMES ; it++ ) {
            hdl = nread ( nd, array_i[ it ], NSIZE * sizeof( double ) ) ;
            while( nquery( hdl ) ) ;
        }
        for( it = 0 ; it < NTIMES ; it++ ) {
            for( i = 0 ; i < NSIZE ; i++ ) {
                fprintf( stdout, "%5d:%5d%10d%16.4f\n", iter, it, i, array_i[ it ][ i ] ) ;
            }
        }
/*
///
        ///
        /// array_i => array_o
        ///
        for( it = 0 ; it < NTIMES ; it++ ) {
            for( i = 0 ; i < NSIZE ; i++ ) {
                array_o[ it ][ i ] = array_i[ it ][ i ] / 2 ;
            }
        }
///
        ///
        /// send array_o
        ///
        for( it = 0 ; it < NTIMES ; it++ ) {
            hdl = nwrite( nd, array_o[ it ], NSIZE * sizeof( double ) ) ;
            while( nquery( hdl ) ) ;
        }
///
        for( it = 0 ; it < NTIMES ; it++ ) {
            for( i = 0 ; i < NSIZE ; i++ ) {
                fprintf( stdout, "%5d:%5d%10d%16.4f%16.4f\n", iter, it, i, array_i[ it ][ i ], array_o[ it ][ i ] ) ;
            }
        }
*/
    }

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    nclose ( nd ) ;
    freenet( nt ) ;
    return 0;
}

