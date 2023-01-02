#include "rt_matrixlib.h"
void rt_BackwardSubstitutionRR_Dbl ( real_T * pU , const real_T * pb , real_T
* x , int_T N , int_T P , boolean_T unit_upper ) { int_T i , k ; for ( k = P
; k > 0 ; k -- ) { real_T * pUcol = pU ; for ( i = 0 ; i < N ; i ++ ) {
real_T * xj = x + k * N - 1 ; real_T s = 0.0 ; real_T * pUrow = pUcol -- ; {
int_T j = i ; while ( j -- > 0 ) { s += * pUrow * * xj -- ; pUrow -= N ; } }
if ( unit_upper ) { * xj = * pb -- - s ; } else { * xj = ( * pb -- - s ) / *
pUrow ; } } } }
