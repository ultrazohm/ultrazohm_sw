#include "rt_matrixlib.h"
void rt_ForwardSubstitutionRR_Dbl ( real_T * pL , const real_T * pb , real_T
* x , int_T N , int_T P , const int32_T * piv , boolean_T unit_lower ) {
int_T i , k ; for ( k = 0 ; k < P ; k ++ ) { real_T * pLcol = pL ; for ( i =
0 ; i < N ; i ++ ) { real_T * xj = x + k * N ; real_T s = 0.0 ; real_T *
pLrow = pLcol ++ ; { int_T j = i ; while ( j -- > 0 ) { s += * pLrow * * xj ;
pLrow += N ; xj ++ ; } } if ( unit_lower ) { * xj = pb [ piv [ i ] ] - s ; }
else { * xj = ( pb [ piv [ i ] ] - s ) / * pLrow ; } } pb += N ; } }
