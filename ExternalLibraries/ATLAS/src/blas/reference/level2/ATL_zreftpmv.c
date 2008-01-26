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
#include "atlas_reflvl2.h"
#include "atlas_reflevel2.h"

void ATL_zreftpmv
(
   const enum ATLAS_UPLO      UPLO,
   const enum ATLAS_TRANS     TRANS,
   const enum ATLAS_DIAG      DIAG,
   const int                  N,
   const double               * A,
   double                     * X,
   const int                  INCX
)
{
/*
 * Purpose
 * =======
 *
 * ATL_zreftpmv performs one of the matrix-vector operations
 *
 *    x := A * x,   or   x := conjg( A  ) * x,   or
 *
 *    x := A'* x,   or   x := conjg( A' ) * x,
 *
 * where x is an n-element vector and  A is an n by n unit, or non-unit,
 * upper or lower triangular matrix, supplied in packed form.
 *
 * Arguments
 * =========
 *
 * UPLO    (input)                       const enum ATLAS_UPLO
 *         On entry, UPLO  specifies whether  the  matrix is an upper or
 *         lower triangular matrix as follows:
 *
 *             UPLO = AtlasUpper   A is an upper triangular matrix.
 *
 *             UPLO = AtlasLower   A is a lower triangular matrix.
 *
 *         Unchanged on exit.
 *
 * TRANS   (input)                       const enum ATLAS_TRANS
 *         On entry,  TRANS  specifies the  operation to be performed as
 *         follows:
 *
 *            TRANS = AtlasNoTrans     x := A *x,
 *
 *            TRANS = AtlasConj        x := conjg( A ) * x,
 *
 *            TRANS = AtlasTrans       x := A'*x,
 *
 *            TRANS = AtlasConjTrans   x := conjg( A' )*x.
 *
 *         Unchanged on exit.
 *
 * DIAG    (input)                       const enum ATLAS_DIAG
 *         On entry, DIAG specifies whether or not A is unit triangu-
 *         lar as follows:
 *
 *            DIAG = AtlasUnit       A is assumed to be unit triangular,
 *
 *            DIAG = AtlasNonUnit    A is not assumed to be unit trian-
 *                                   gular.
 *
 *         Unchanged on exit.
 *
 * N       (input)                       const int
 *         On entry, N specifies the order of the matrix A. N must be at
 *         least zero. Unchanged on exit.
 *
 * A       (input)                       const double *
 *         On entry,  A  points  to an array of size equal to or greater
 *         than   (( n*(n+1) ) / 2) * sizeof( double[2] ).  Before entry
 *         with UPLO = AtlasUpper, the array  A  must  contain the upper
 *         triangular matrix packed sequentially, column by  column,  so
 *         that A[ 0 ] contains a(0,0), A[ 1 ] and A[ 2 ] contain a(0,1)
 *         and  a(1,1)  respectively,  and  so  on.  Before  entry  with
 *         UPLO = AtlasLower, the array  A  must contain the  lower tri-
 *         angular matrix packed sequentially, column by column, so that
 *         A[ 0 ] contains a(0,0), A[ 1 ] and A[ 2 ] contain a(1,0)  and
 *         a( 2, 0 ) respectively, and so on.
 *
 *         Note that when  DIAG = AtlasUnit,  the diagonal elements of A
 *         are not referenced,  but are  assumed to be unity.  Unchanged
 *         on exit.
 *
 * X       (input/output)                double *
 *         On entry,  X  points to the  first entry to be accessed of an
 *         incremented array of size equal to or greater than
 *            ( 1 + ( n - 1 ) * abs( INCX ) ) * sizeof( double[2] ),
 *         that contains the vector x.  On exit,  X  is overwritten with
 *         the tranformed vector x.
 *
 * INCX    (input)                       const int
 *         On entry, INCX specifies the increment for the elements of X.
 *         INCX must not be zero. Unchanged on exit.
 *
 * ---------------------------------------------------------------------
 */
/* ..
 * .. Executable Statements ..
 *
 */
   if( N == 0 ) return;

   if( UPLO == AtlasUpper )
   {
      if(      TRANS == AtlasNoTrans )
      {
         if( DIAG == AtlasNonUnit )
         {
            ATL_zreftpmvUNN( N,    A, 1,   X, INCX );
         }
         else
         {
            ATL_zreftpmvUNU( N,    A, 1,   X, INCX );
         }
      }
      else if( TRANS == AtlasConj    )
      {
         if( DIAG == AtlasNonUnit )
         {
            ATL_zreftpmvUCN( N,    A, 1,   X, INCX );
         }
         else
         {
            ATL_zreftpmvUCU( N,    A, 1,   X, INCX );
         }
      }
      else if( TRANS == AtlasTrans   )
      {
         if( DIAG == AtlasNonUnit )
         {
            ATL_zreftpmvUTN( N,    A, 1,   X, INCX );
         }
         else
         {
            ATL_zreftpmvUTU( N,    A, 1,   X, INCX );
         }
      }
      else
      {
         if( DIAG == AtlasNonUnit )
         {
            ATL_zreftpmvUHN( N,    A, 1,   X, INCX );
         }
         else
         {
            ATL_zreftpmvUHU( N,    A, 1,   X, INCX );
         }
      }
   }
   else
   {
      if(      TRANS == AtlasNoTrans )
      {
         if( DIAG == AtlasNonUnit )
         {
            ATL_zreftpmvLNN( N,    A, N,   X, INCX );
         }
         else
         {
            ATL_zreftpmvLNU( N,    A, N,   X, INCX );
         }
      }
      else if( TRANS == AtlasConj    )
      {
         if( DIAG == AtlasNonUnit )
         {
            ATL_zreftpmvLCN( N,    A, N,   X, INCX );
         }
         else
         {
            ATL_zreftpmvLCU( N,    A, N,   X, INCX );
         }
      }
      else if( TRANS == AtlasTrans   )
      {
         if( DIAG == AtlasNonUnit )
         {
            ATL_zreftpmvLTN( N,    A, N,   X, INCX );
         }
         else
         {
            ATL_zreftpmvLTU( N,    A, N,   X, INCX );
         }
      }
      else
      {
         if( DIAG == AtlasNonUnit )
         {
            ATL_zreftpmvLHN( N,    A, N,   X, INCX );
         }
         else
         {
            ATL_zreftpmvLHU( N,    A, N,   X, INCX );
         }
      }
   }
/*
 * End of ATL_zreftpmv
 */
}
