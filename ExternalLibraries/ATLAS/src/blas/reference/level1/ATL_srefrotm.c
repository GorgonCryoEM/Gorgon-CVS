/* ---------------------------------------------------------------------
 *
 * -- Automatically Tuned Linear Algebra Software (ATLAS)
 *    (C) Copyright 2000 All Rights Reserved
 *
 * -- ATLAS routine -- Version 3.2 -- December 25, 2000
 *
 * -- Suggestions,  comments,  bugs reports should be sent to the follo-
 *    wing e-mail address: atlas@cs.utk.edu
 *
 * Author         : Antoine P. Petitet
 * University of Tennessee - Innovative Computing Laboratory
 * Knoxville TN, 37996-1301, USA.
 *
 * ---------------------------------------------------------------------
 *
 * -- Copyright notice and Licensing terms:
 *
 *  Redistribution  and  use in  source and binary forms, with or without
 *  modification, are  permitted provided  that the following  conditions
 *  are met:
 *
 * 1. Redistributions  of  source  code  must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce  the above copyright
 *    notice,  this list of conditions, and the  following disclaimer in
 *    the documentation and/or other materials provided with the distri-
 *    bution.
 * 3. The name of the University,  the ATLAS group,  or the names of its
 *    contributors  may not be used to endorse or promote products deri-
 *    ved from this software without specific written permission.
 *
 * -- Disclaimer:
 *
 * THIS  SOFTWARE  IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,  INDIRECT, INCIDENTAL, SPE-
 * CIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO,  PROCUREMENT  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEO-
 * RY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  (IN-
 * CLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ---------------------------------------------------------------------
 */
/*
 * Include files
 */
#include "atlas_refmisc.h"
#include "atlas_reflevel1.h"

void ATL_srefrotm
(
   const int                  N,
   float                      * X,
   const int                  INCX,
   float                      * Y,
   const int                  INCY,
   const float                * PARAM
)
{
/*
 * Purpose
 * =======
 *
 * ATL_srefrotm applies the modified-Givens rotation  H  stored in PARAM
 * to the two n-vectors x and y as follows:
 *
 *    [ x_i ]   [ h_11 h_12 ] [ x_i ]
 *    [ y_i ] = [ h_21 h_22 ] [ y_i ]    for all i = 1 .. n.
 *
 * If n <= 0 or if H is the identity matrix, this subroutine returns im-
 * mediately.
 *
 * See ``Basic Linear Algebra Subprograms for Fortran Usage'' by C. Law-
 * son, R. Hanson, D. Kincaid and F. Krogh, ACM Transactions on Mathema-
 * tical Software, 1979, 5(3) pp 308-323, for further information.
 *
 * Arguments
 * =========
 *
 * N       (input)                       const int
 *         On entry, N specifies the length of the vector x. N  must  be
 *         at least zero. Unchanged on exit.
 *
 * X       (input/output)                float *
 *         On entry,  X  points to the  first entry to be accessed of an
 *         incremented array of size equal to or greater than
 *            ( 1 + ( n - 1 ) * abs( INCX ) ) * sizeof(   float   ),
 *         that contains the vector x.  On exit,  the entries of the in-
 *         cremented array  X are rotated with the entries of the incre-
 *         mented array  Y.
 *
 * INCX    (input)                       const int
 *         On entry, INCX specifies the increment for the elements of X.
 *         INCX must not be zero. Unchanged on exit.
 *
 * Y       (input/output)                float *
 *         On entry,  Y  points to the  first entry to be accessed of an
 *         incremented array of size equal to or greater than
 *            ( 1 + ( n - 1 ) * abs( INCY ) ) * sizeof(   float   ),
 *         that contains the vector y.  On exit,  the entries of the in-
 *         cremented array  Y are rotated with the entries of the incre-
 *         mented array  X.
 *
 * INCY    (input)                       const int
 *         On entry, INCY specifies the increment for the elements of Y.
 *         INCY must not be zero. Unchanged on exit.
 *
 * PARAM   (input)                       const float *
 *         On entry, PARAM is an array of dimension at least 5 that con-
 *         tains the matrix  H  as encoded by the routine ATL__refrotmg.
 *         Unchanged on exit.
 *
 * ---------------------------------------------------------------------
 */
/*
 * .. Local Variables ..
 */
   register float             h11, h12, h21, h22, x0, x1, x2, x3,
                              y0, y1, y2, y3;
   float                      * StX;
   register int               i;
   int                        nu;
   const int                  incX2 = 2 * INCX, incY2 = 2 * INCY,
                              incX3 = 3 * INCX, incY3 = 3 * INCY,
                              incX4 = 4 * INCX, incY4 = 4 * INCY;
/* ..
 * .. Executable Statements ..
 *
 */
   if( ( N > 0 ) && ( *PARAM != ATL_sNTWO ) )
   {
      if(      *PARAM   == ATL_sNONE )
      {
         h11 = PARAM[1]; h21 = PARAM[2]; h12 = PARAM[3]; h22 = PARAM[4];

         if( ( nu = ( N >> 2 ) << 2 ) != 0 )
         {
            StX = (float *)X + nu * INCX;

            do
            {
               x0 = (*X);     y0 = (*Y);     x1 = X[INCX ]; y1 = Y[INCY ];
               x2 = X[incX2]; y2 = Y[incY2]; x3 = X[incX3]; y3 = Y[incY3];

               *X        = ( x0 * h11 ) + ( y0 * h12 );
               *Y        = ( x0 * h21 ) + ( y0 * h22 );
               X[INCX ]  = ( x1 * h11 ) + ( y1 * h12 );
               Y[INCY ]  = ( x1 * h21 ) + ( y1 * h22 );
               X[incX2]  = ( x2 * h11 ) + ( y2 * h12 );
               Y[incY2]  = ( x2 * h21 ) + ( y2 * h22 );
               X[incX3]  = ( x3 * h11 ) + ( y3 * h12 );
               Y[incY3]  = ( x3 * h21 ) + ( y3 * h22 );

               X  += incX4;
               Y  += incY4;

            } while( X != StX );
         }

         for( i = N - nu; i != 0; i-- )
         {
            x0  = (*X); y0  = (*Y);

            *X  = ( x0 * h11 ) + ( y0 * h12 );
            *Y  = ( x0 * h21 ) + ( y0 * h22 );

            X  += INCX;
            Y  += INCY;
         }
      }
      else if( *PARAM == ATL_sZERO )
      {
         h21 = PARAM[2]; h12 = PARAM[3];

         if( ( nu = ( N >> 2 ) << 2 ) != 0 )
         {
            StX = (float *)X + nu * INCX;

            do
            {
               x0 = (*X);     y0 = (*Y);     x1 = X[INCX ]; y1 = Y[INCY ];
               x2 = X[incX2]; y2 = Y[incY2]; x3 = X[incX3]; y3 = Y[incY3];

               *X       = x0 + ( y0 * h12 ); *Y       = y0 + ( x0 * h21 );
               X[INCX ] = x1 + ( y1 * h12 ); Y[INCY ] = y1 + ( x1 * h21 );
               X[incX2] = x2 + ( y2 * h12 ); Y[incY2] = y2 + ( x2 * h21 );
               X[incX3] = x3 + ( y3 * h12 ); Y[incY3] = y3 + ( x3 * h21 );

               X  += incX4;
               Y  += incY4;

            } while( X != StX );
         }

         for( i = N - nu; i != 0; i-- )
         {
            x0  = (*X); y0  = (*Y);
            *X  = x0 + ( y0 * h12 ); *Y  = y0 + ( x0 * h21 );
            X  += INCX; Y  += INCY;
         }
      }
      else if( *PARAM == ATL_sONE )
      {
         h11 = PARAM[1]; h22 = PARAM[4];

         if( ( nu = ( N >> 2 ) << 2 ) != 0 )
         {
            StX = (float *)X + nu * INCX;

            do
            {
               x0 = (*X);     y0 = (*Y);     x1 = X[INCX ]; y1 = Y[INCY ];
               x2 = X[incX2]; y2 = Y[incY2]; x3 = X[incX3]; y3 = Y[incY3];

               *X       = ( x0 * h11 ) + y0; *Y       = ( y0 * h22 ) - x0;
               X[INCX ] = ( x1 * h11 ) + y1; Y[INCY ] = ( y1 * h22 ) - x1;
               X[incX2] = ( x2 * h11 ) + y2; Y[incY2] = ( y2 * h22 ) - x2;
               X[incX3] = ( x3 * h11 ) + y3; Y[incY3] = ( y3 * h22 ) - x3;

               X  += incX4;
               Y  += incY4;

            } while( X != StX );
         }

         for( i = N - nu; i != 0; i-- )
         {
            x0  = (*X); y0  = (*Y);
            *X  = ( x0 * h11 ) + y0; *Y  = ( h22 * y0 ) - x0;
            X  += INCX; Y  += INCY;
         }
      }
   }
/*
 * End of ATL_srefrotm
 */
}
