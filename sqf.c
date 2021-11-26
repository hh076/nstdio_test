#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nstdio.h"

#define NINT   3
#define NTIMES 5
#define NSIZE 10

int main(int argc, char **argv)
{
    int      iter ;
    int      it, i ;
    double   array_i[ NTIMES ][ NSIZE ] ;
    double   array_o[ NTIMES ][ NSIZE ] ;
///
    NET      *nt0, *nt1 ;
    ND       *nd0, *nd1 ;
    NHDL     *hdl ;
    char     *ipaddr_l = argv[ 1 ] ;
    char     *port_0   = argv[ 2 ] ;
    char     *ipaddr_r = argv[ 3 ] ;
    char     *port_1   = argv[ 4 ] ;

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
    nt1 = setnet( ipaddr_r, port_1, NTCP ) ;
    nt0 = setnet( ipaddr_l, port_0, NTCP ) ;
    nd1 = nopen( nt1, "s" ) ;
    fprintf( stdout, "sqf: open as server: %s %s\n", ipaddr_r, port_1 ) ;
    nd0 = nopen( nt0, "s" ) ;
    fprintf( stdout, "sqf: open as server: %s %s\n", ipaddr_l, port_0 ) ;
///
    fprintf( stdout, "sqf: here.\n" ) ;

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
    for( iter = 0 ; iter < NINT ; iter++ ) {
        ///
        /// B -> nread F nwrite -> I
        ///
        for( it = 0 ; it < NTIMES ; it++ ) {
            hdl = nread(  nd0, array_i[ it ], NSIZE * sizeof( double ) ) ;
            while( nquery( hdl ) ) ;
            for( i = 0 ; i < NSIZE ; i++ ) {
                array_o[ it ][ i ] = array_i[ it ][ i ] * 2 ; 
            }
            hdl = nwrite( nd1, array_o[ it ], NSIZE * sizeof( double ) ) ;
            while( nquery( hdl ) ) ;
        }

        for( it = 0 ; it < NTIMES ; it++ ) {
            for( i = 0 ; i < NSIZE ; i++ ) {
                fprintf( stdout, "%5d%10d%16.4f%16.4f\n",
                        it, i, array_i[ it ][ i ], array_o[ it ][ i ] ) ;
            }
        }
///
        ///
        /// I -> nread F nwrite -> B
        ///
        for( it = 0 ; it < NTIMES ; it++ ) {
            hdl = nread(  nd1, array_i[ it ], NSIZE * sizeof( double ) ) ;
            while( nquery( hdl ) ) ;
            for( i = 0 ; i < NSIZE ; i++ ) {
                array_o[ it ][ i ] = array_i[ it ][ i ] * 10 ; 
            }
            hdl = nwrite( nd0, array_o[ it ], NSIZE * sizeof( double ) ) ;
            while( nquery( hdl ) ) ;
        }
///
        for( it = 0 ; it < NTIMES ; it++ ) {
            for( i = 0 ; i < NSIZE ; i++ ) {
                fprintf( stdout, "%5d%10d%16.4f%16.4f\n",
                        it, i, array_i[ it ][ i ], array_o[ it ][ i ] ) ;
            }
        }
    }

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
    for( it = 0 ; it < NTIMES ; it++ ) {
        for( i = 0 ; i < NSIZE ; i++ ) {
            fprintf( stdout, "%5d%10d%16.4f%16.4f\n", it, i, array_i[ it ][ i ], array_o[ it ][ i ] ) ;
        }
    }
///
    nclose ( nd0 ) ;
    nclose ( nd1 ) ;
    freenet( nt0 ) ;
    freenet( nt1 ) ;
///
    return 0;
}

