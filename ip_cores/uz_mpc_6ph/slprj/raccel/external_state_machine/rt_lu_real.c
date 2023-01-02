#include <math.h>
#include "rt_matrixlib.h"
void rt_lu_real ( real_T * A , const int_T n , int32_T * piv ) { int_T k ;
for ( k = 0 ; k < n ; k ++ ) { piv [ k ] = k ; } for ( k = 0 ; k < n ; k ++ )
{ const int_T kn = k * n ; int_T p = k ; { int_T i ; real_T Amax = fabs ( A [
p + kn ] ) ; for ( i = k + 1 ; i < n ; i ++ ) { real_T q = fabs ( A [ i + kn
] ) ; if ( q > Amax ) { p = i ; Amax = q ; } } } if ( p != k ) { int_T j ;
int32_T t1 ; for ( j = 0 ; j < n ; j ++ ) { real_T t ; const int_T j_n = j *
n ; t = A [ p + j_n ] ; A [ p + j_n ] = A [ k + j_n ] ; A [ k + j_n ] = t ; }
t1 = piv [ p ] ; piv [ p ] = piv [ k ] ; piv [ k ] = t1 ; } { real_T Adiag =
A [ k + kn ] ; int_T i , j ; if ( Adiag != 0.0 ) { Adiag = 1.0 / Adiag ; for
( i = k + 1 ; i < n ; i ++ ) { A [ i + kn ] *= Adiag ; } for ( j = k + 1 ; j
< n ; j ++ ) { int_T j_n = j * n ; for ( i = k + 1 ; i < n ; i ++ ) { A [ i +
j_n ] -= A [ i + kn ] * A [ k + j_n ] ; } } } } } }
