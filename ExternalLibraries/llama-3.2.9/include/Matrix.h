// -*- C++ -*-

#ifndef   _LLAMA_MATRIX_H_
#define   _LLAMA_MATRIX_H_

#include "Decls.h"
#include "General.h"
#include "Exception.h"
#include "AbstMatrix.h"
#include "Diagonal.h"
#include "f77fun.h"

#include <iostream>
#include <cstdlib>

namespace Llama {

  /**
     This is the concrete basic matrix class.  Memory allocated is contiguous 
     and entries are stored in column-major order for ease of interface with BLAS
     and LAPACK routines.  Matrix arithmetic utilizes inlined BLAS routines
     for speed and efficiency, at the cost of compilation speed.
  */
  template <class Scalar>
  class Matrix : public AbstMatrix<Scalar> {

  private:
    // Implementation
    Index _size;
    Index _dims[2];
    Scalar *_data;

    // Initialize the matrix with data d
    void _init (Index s, Scalar *d) {
      _size = s;
      delete[] _data;
      _data = d;
    };

    static void _copy (Scalar *dest, const Index incd, const Scalar *src, 
		       const Index incs, const Index sz) {
      for (Index j = 0; j < sz; j++)
	dest[j * incd] = src[j * incs];
    };

    static void _axpy (Scalar *y, const Index incy, const Scalar a, const Scalar *x, 
		       const Index incx, const Index sz) {
      for (Index j = 0; j < sz; j++) 
	y[j * incy] += a * x[j * incx];
    };

    static void _scal (Scalar *x, const Index inc, const Scalar a, const Index sz)
    {
      for (Index j = 0; j < sz; j++) 
	x[j * inc] *= a;
    };

    static void _gemm (const Transpose_t lt, const Transpose_t rt, 
		       const Index m, const Index n, const Index k,
		       const Scalar alpha, 
		       const Scalar *a, const Index lda,
		       const Scalar *b, const Index ldb,
		       const Scalar beta,
		       Scalar *c, const Index ldc) {

      if (lt == NOTRANSPOSE) {

	if (rt == NOTRANSPOSE) {

	  for (Index j = 0; j < n; j++)
	    for (Index i = 0; i < m; i++) {
	      c[i+j*ldc] *= beta;
	      for (Index p = 0; p < k; p++) 
		c[i+j*ldc] += alpha * a[i+p*lda] * b[p+j*ldb];
	    }

	} else if (rt == TRANSPOSE) {

	  for (Index j = 0; j < n; j++)
	    for (Index i = 0; i < m; i++) {
	      c[i+j*ldc] *= beta;
	      for (Index p = 0; p < k; p++) 
		c[i+j*ldc] += alpha * a[i+p*lda] * b[j+p*ldb];
	    }

	} else if (rt == CONJTRANSPOSE) {

	  for (Index j = 0; j < n; j++)
	    for (Index i = 0; i < m; i++) {
	      c[i+j*ldc] *= beta;
	      for (Index p = 0; p < k; p++) 
		c[i+j*ldc] += alpha * a[i+p*lda] * conj(b[j+p*ldb]);
	    }

	} else {
	  throw LogicError("matrix multiply");
	}

      } else if (lt == TRANSPOSE) {

	if (rt == NOTRANSPOSE) {

	  for (Index j = 0; j < n; j++)
	    for (Index i = 0; i < m; i++) {
	      c[i+j*ldc] *= beta;
	      for (Index p = 0; p < k; p++) 
		c[i+j*ldc] += alpha * a[p+i*lda] * b[p+j*ldb];
	    }

	} else if (rt == TRANSPOSE) {

	  for (Index j = 0; j < n; j++)
	    for (Index i = 0; i < m; i++) {
	      c[i+j*ldc] *= beta;
	      for (Index p = 0; p < k; p++) 
		c[i+j*ldc] += alpha * a[p+i*lda] * b[j+p*ldb];
	    }

	} else if (rt == CONJTRANSPOSE) {

	  for (Index j = 0; j < n; j++)
	    for (Index i = 0; i < m; i++) {
	      c[i+j*ldc] *= beta;
	      for (Index p = 0; p < k; p++) 
		c[i+j*ldc] += alpha * a[p+i*lda] * conj(b[j+p*ldb]);
	    }

	} else {
	  throw LogicError("matrix multiply");
	}

      } else if (lt == CONJTRANSPOSE) {

	if (rt == NOTRANSPOSE) {

	  for (Index j = 0; j < n; j++)
	    for (Index i = 0; i < m; i++) {
	      c[i+j*ldc] *= beta;
	      for (Index p = 0; p < k; p++) 
		c[i+j*ldc] += alpha * conj(a[p+i*lda]) * b[p+j*ldb];
	    }

	} else if (rt == TRANSPOSE) {

	  for (Index j = 0; j < n; j++)
	    for (Index i = 0; i < m; i++) {
	      c[i+j*ldc] *= beta;
	      for (Index p = 0; p < k; p++) 
		c[i+j*ldc] += alpha * conj(a[p+i*lda]) * b[j+p*ldb];
	    }

	} else if (rt == CONJTRANSPOSE) {

	  for (Index j = 0; j < n; j++)
	    for (Index i = 0; i < m; i++) {
	      c[i+j*ldc] *= beta;
	      for (Index p = 0; p < k; p++) 
		c[i+j*ldc] += alpha * conj(a[p+i*lda]) * conj(b[j+p*ldb]);
	    }

	} else {
	  throw LogicError("matrix multiply");
	}

      } else {
	throw LogicError("matrix multiply");
      }

    };

  public:

    /**
       Return number of rows x columns
    */
    Index size (void) const {
      return _size;
    };

    /**
       Return number of rows
    */
    Index rows (void) const {
      return _dims[0];
    };

    /**
       Return number of columns
    */
    Index cols (void) const {
      return _dims[1];
    };

    /**
       Pointer to data storage.
    */
    Scalar *data (void) const {
      return _data;
    };

    /**
       Return transpose status
    */
    Transpose_t trans (void) const {
      return NOTRANSPOSE;
    };

    /**
       Access to elements: vector format
    */
    Scalar operator () (const Index k) const {
      return _data[k];
    };

    /**
       Access to elements: vector format
    */
    Scalar& operator () (const Index k) {
      return _data[k];
    };

    /**
       Access to elements: matrix format
    */
    Scalar operator () (const Index j, const Index k) const {
      return (*this)(j + k * _dims[0]);
    };

    /**
       Access to elements: matrix format
    */
    Scalar& operator () (const Index j, const Index k) {
      return (*this)(j + k * _dims[0]);
    };

    /**
       Destructor
    */
    ~Matrix (void) { 
      if (_data != 0) delete[] _data;
    };

    /**
       Default constructor
    */
    Matrix (Index r = 0, Index c = 1, Scalar *d = 0, Index inc = 1) 
    {
      _size = r * c;
      _data = 0;
      try {
	if (_size > 0) _data = new Scalar[_size];
      } catch (std::bad_alloc) {
	throw OutOfMemory("matrix constructor");
      }
      if (d != 0) _copy(_data, 1, d, inc, _size);
      _dims[0] = r;
      _dims[1] = c;
    };

    /**
       Copy constructor
    */
    Matrix (const Matrix& x) {
      Scalar *newdata = 0;
      _data = 0;
      try {
	newdata = new Scalar[x.size()];
      } catch (std::bad_alloc) {
	throw OutOfMemory("matrix copy constructor");
      }
      if (x.data() != 0) _copy(newdata, 1, x.data(), 1, x.size());
      _init(x.size(), newdata);
      _dims[0] = x.rows();
      _dims[1] = x.cols();
    };

    // Matrix-matrix operations
    /**
       Matrix assignment.  Data are copied.
    */
    Matrix& operator = (const Matrix& x) {
      Scalar *newdata = 0;
      try {
	newdata= new Scalar[x.size()];
      } catch (std::bad_alloc) {
	throw OutOfMemory("matrix =");
      }
      _copy(newdata, 1, x.data(), 1, x.size());
      _init(x.size(), newdata);
      _dims[0] = x.rows();
      _dims[1] = x.cols();
      return *this;
    };

    /**
       Add a matrix to a matrix
    */
    Matrix& operator += (const Matrix& x) {
      if (
	  (this->rows() != x.rows()) ||
	  (this->cols() != x.cols())
	  )
	throw DimError("matrix +=");
      _axpy(this->data(), 1, Scalar(1), x.data(), 1, x.size());
      return *this;
    };

    /**
       Subtract a matrix from a matrix
    */
    Matrix& operator -= (const Matrix& x) {
      if (
	  (this->rows() != x.rows()) ||
	  (this->cols() != x.cols())
	  )
	throw DimError("matrix -=");
      _axpy(this->data(), 1, Scalar(-1), x.data(), 1, x.size());
      return *this;
    };

    /**
       The ordinary matrix transpose.
    */
    Transpose<Scalar> t (void) const {
      return Transpose<Scalar>(this, TRANSPOSE);
    };

    /**
       The Hermitian transpose (conjugate transpose).
    */
    Transpose<Scalar> h (void) const {
      return Transpose<Scalar>(this, CONJTRANSPOSE);
    };

    /**
       Copy from abstract matrix
    */
    Matrix (const CAbstMatrix<Scalar>& x) {
      Scalar *newdata = 0, *p;
      _data = 0;
      try {
	p = newdata = new Scalar[x.size()];
      } catch (std::bad_alloc) {
	throw OutOfMemory("matrix copy constructor");
      }
      for (Index k = 0; k < x.size(); k++) *(p++) = x(k);
      _init(x.size(), newdata);
      _dims[0] = x.rows();
      _dims[1] = x.cols();
    };

    /**
       Assign from abstract matrix.
    */
    Matrix& operator = (const CAbstMatrix<Scalar>& x) {
      Scalar *newdata = 0, *p;
      try {
	p = newdata = new Scalar[x.size()];
      } catch (std::bad_alloc) {
	throw OutOfMemory("matrix =");
      }
      for (Index k = 0; k < x.size(); k++) *(p++) = x(k);
      _init(x.size(), newdata);
      _dims[0] = x.rows();
      _dims[1] = x.cols();
      return *this;
    };

    /**
       Add elements from an abstract matrix to a matrix
    */
    Matrix& operator += (const CAbstMatrix<Scalar>& x) {
      if (
	  (this->rows() != x.rows()) ||
	  (this->cols() != x.cols())
	  )
	throw DimError("matrix +=");
      for (Index k = 0; k < x.size(); k++) (*this)(k) += x(k);
      return *this;
    };
 
    /**
       Subtract elements from an abstract matrix from a matrix
    */
    Matrix& operator -= (const CAbstMatrix<Scalar>& x) {
      if (
	  (this->rows() != x.rows()) ||
	  (this->cols() != x.cols())
	  )
	throw DimError("matrix -=");
      for (Index k = 0; k < x.size(); k++) (*this)(k) -= x(k);
      return *this;
    };

    // Submatrix extraction
    /**
       Reference the submatrix consisting of a range of elements
       in the r-th row
    */
    Submatrix<Scalar> operator () (const Index r, const Range& c) {
      return Submatrix<Scalar>(this, r, c);
    };

    /**
       Reference the submatrix consisting of a range of elements
       in the c-th column
    */
    Submatrix<Scalar> operator () (const Range& r, const Index c) {
      return Submatrix<Scalar>(this, r, c);
    };

    /**
       Reference the submatrix defined by two ranges of indices
    */
    Submatrix<Scalar> operator () (const Range& r, const Range& c) {
      return Submatrix<Scalar>(this, r, c);
    };

    /**
       Reference the submatrix consisting of a set of elements
       in the r-th row
    */
    Submatrix<Scalar> operator () (const Index r, const Matrix<Index>& c) {
      return Submatrix<Scalar>(this, r, &c);
    };

    /**
       Reference the submatrix consisting of a set of elements
       in the c-th column
    */
    Submatrix<Scalar> operator () (const Matrix<Index>& r, const Index c) {
      return Submatrix<Scalar>(this, &r, c);
    };

    /**
       Reference the submatrix with row and column indices specified by
       a range and a vector of indices.
    */
    Submatrix<Scalar> operator () (const Range& r, const Matrix<Index>& c) {
      return Submatrix<Scalar>(this, r, &c);
    };

    /**
       Reference the submatrix with row and column indices specified by
       a vector and a range of indices.
    */
    Submatrix<Scalar> operator () (const Matrix<Index>& r, const Range& c) {
      return Submatrix<Scalar>(this, &r, c);
    };

    /**
       Reference the submatrix with row and column indices specified by
       two vectors of indices.
    */
    Submatrix<Scalar> operator () (const Matrix<Index>& r, const Matrix<Index>& c) {
      return Submatrix<Scalar>(this, &r, &c);
    };

    /**
       Reference the k-th diagonal.  If k > 0, a superdiagonal is
       referenced; if k < 0, a subdiagonal is referenced.  
    */
    Diagonal<Scalar> diag (Integer k = 0) {
      return Diagonal<Scalar>(this, k);
    };

    // Unary operators
    /**
       Unary plus
    */
    Matrix& operator + (void) {
      return *this;
    };

    /**
       Unary minus
    */
    SMClosure<Scalar> operator - (void) {
      return SMClosure<Scalar>(-1, this);
    };

    // Scalar-matrix operations
    /**
       Set a matrix equal to a scalar multiple of the identity matrix.
       If the matrix is nonsquare, only the diagonal elements will be
       nonzero.
    */
    Matrix& operator = (const Scalar& a) {
      for (Index k = 0; k < this->size(); k++) 
	(*this)(k) = 0;
      for (Index k = 0; k < min(this->rows(), this->cols()); k++) 
	(*this)(k,k) = a;
      return *this;
    };

    /**
       Add a scalar multiple of the identity matrix
    */
    Matrix& operator += (const Scalar& a) {
      for (Index k = 0; k < min(this->rows(), this->cols()); k++) 
	(*this)(k,k) += a;
      return *this;
    };

    /**
       Subtract a scalar multiple of the identity matrix
    */
    Matrix& operator -= (const Scalar& a) {
      for (Index k = 0; k < min(this->rows(), this->cols()); k++) 
	(*this)(k,k) -= a;
      return *this;
    };

    /**
       Multiply a matrix by a scalar
    */
    Matrix& operator *= (const Scalar& a) {
      _scal(this->data(), 1, a, this->size());
      return *this;
    };

    /**
       Divide a matrix by a scalar
    */
    Matrix& operator /= (const Scalar& a) {
      if (a == 0) throw DivideError("matrix /=");
      _scal(this->data(), 1, 1/a, this->size());
      return *this;
    };

    // Scalar * matrix
    Matrix& operator = (const SMClosure<Scalar>& x) {
      _dims[0] = x.rows();
      _dims[1] = x.cols();
      *this = *(x.matrix());
      _scal(this->data(), 1, x.alpha(), x.size());
      return *this;
    };

    Matrix& operator += (const SMClosure<Scalar>& x) {
      if (
	  (this->cols() != x.cols()) || 
	  (this->rows() != x.rows())
	  )
	throw DimError("matrix +=");
      _axpy (this->data(), 1, x.alpha(), x.matrix()->data(), 1, x.size());
      return *this;
    };

    Matrix& operator -= (const SMClosure<Scalar>& x) {
      if (
	  (this->cols() != x.cols()) || 
	  (this->rows() != x.rows())
	  )
	throw DimError("matrix -=");
      _axpy (this->data(), 1, -x.alpha(), x.matrix()->data(), 1, x.size());
      return *this;
    };

    // Matrix * matrix
    Matrix& operator = (const MMClosure<Scalar>& x) {
      Index sz = x.rows() * x.cols();
      Scalar *newdata = new Scalar[sz];
      _gemm(x.ltrans(), x.rtrans(), x.rows(), x.cols(), x.sumlength(), 
	    x.alpha(), x.lmatrix()->data(), x.lld(), x.rmatrix()->data(), x.rld(),
	    0, newdata, x.rows() );
      _init(sz, newdata);
      _dims[0] = x.rows();
      _dims[1] = x.cols();
      return *this;
    };

    Matrix& operator += (const MMClosure<Scalar>& x) {
      if (
	  (this->cols() != x.cols()) || 
	  (this->rows() != x.rows())
	  )
	throw DimError("matrix +=");
      _gemm(x.ltrans(), x.rtrans(), 
	    x.rows(), x.cols(), x.sumlength(), 
	    x.alpha(), 
	    x.lmatrix()->data(), x.lld(), 
	    x.rmatrix()->data(), x.rld(),
	    1,
	    this->data(), x.rows()
	    );
      return *this;
    };

    Matrix& operator -= (const MMClosure<Scalar>& x) {
      if (
	  (this->cols() != x.cols()) || 
	  (this->rows() != x.rows())
	  )
	throw DimError("matrix -=");
      _gemm(x.ltrans(), x.rtrans(),
	    x.rows(), x.cols(), x.sumlength(), 
	    -x.alpha(), 
	    x.lmatrix()->data(), x.lld(), 
	    x.rmatrix()->data(), x.rld(),
	    1,
	    this->data(), x.rows()
	    );
      return *this;
    };

    /**
       Apply a function elementwise
    */
    template <class OScalar>
    FAMClosure<OScalar, Scalar> apply (OScalar f(Scalar)) {
      return FAMClosure<OScalar, Scalar>(this, f);
    };

    // Binary I/O
    /**
       Binary input.
    */
    Matrix& operator << (std::istream& i) {
      try {

	Scalar *newdata = 0;
	i.read((char *) _dims, 2 * sizeof(Index));
	i.read((char *) &_size, sizeof(Index));
	try {
	  newdata = new Scalar[_size];
	} catch (std::bad_alloc) {
	  throw OutOfMemory();
	}
	i.read((char *) newdata, _size * sizeof(Scalar));
	_init(_size, newdata);

      } catch (Exception e) {
	std::cerr << e;
	throw Exception("matrix binary read");
      }
      return *this;
    };

    /**
       Binary output.
    */
    void operator >> (std::ostream& o) const {
      try {
	o.write((char *) _dims, 2 * sizeof(Index));
	o.write((char *) &_size, sizeof(Index));
	o.write((char *) this->data(), this->size() * sizeof(Scalar));
      } catch (Exception e) {
	std::cerr << e;
	throw Exception("matrix binary write");
      }
    };

    /**
       Resize a matrix.  All data are destroyed.  This policy may change in future.
    */
    Matrix& resize (Index r, Index c = 1) {
      if (_data != 0) delete[] _data;
      _dims[0] = r;
      _dims[1] = c;
      _size = r*c;
      if (_size > 0) _data = new Scalar[_size];
      return *this;
    };

    /**
       Reshape a matrix as a vector.
    */
    Matrix& reshape (void) {
      _dims[0] = _size;
      _dims[1] = 1;
      return *this;
    };

    /**
       Reshape a matrix arbitrarily.
    */
    Matrix& reshape (Index r, Index c) {
      if (this->size() != r * c) 
	throw DimError("matrix reshape");
      _dims[0] = r;
      _dims[1] = c;
      return *this;
    };

    /**
       Append columns in matrix x.
    */
    Matrix& append_cols (const CAbstMatrix<Scalar>& x) {
      if (this->rows() != x.rows()) 
	throw DimError("matrix append cols");
      Index c = this->cols(), sz = this->rows() * (c + x.cols());
      Scalar *newdata = 0;
      try {
	newdata = new Scalar[sz];
      } catch (std::bad_alloc) {
	throw OutOfMemory("matrix append columns");
      }
      _copy(newdata, 1, this->data(), 1, this->size());
      _init(sz, newdata);
      _dims[1] += x.cols();
      for (Index k = 0; k < x.cols(); k++)
	for (Index j = 0; j < x.rows(); j++)
	  (*this)(j,c + k) = x(j,k);
      return *this;
    };

    // Vector sort
    /**
       Sort all elements linearly, assuming vector format,
       using a given total order.  The latter is passed in the form
       of a function of type

       int (*Order)(const void *a, const void *b)

       This function should have return values of 1, 0, or -1 for any
       combination of inputs a, b.  The entries will be sorted so that if
       for all j, k, j < k implies (*order)(&x(j), &x(k)) <= 0.
    */
    Matrix& sort (Order o)
    {
      qsort(this->data(), this->size(), sizeof(Scalar), o);
      return *this;
    };

    // (1-norm) column-sum norm
    /**
       Return the matrix 1-norm (column-sum norm).
    */
    Real norm1 (void) const {
      Real s, t = 0;
      for (Index k = 0; k < this->cols(); k++) {
	s = 0;
	for (Index j = 0; j < this->rows(); j++) 
	  s += (Real) abs((*this)(j,k));
	t = max(t, s);
      }
      return t;
    };

    /**
       Return the matrix infinity-norm (row-sum norm).
    */
    Real norminf (void) const {
      Real s, t = 0;
      for (Index j = 0; j < this->rows(); j++) {
	s = 0;
	for (Index k = 0; k < this->cols(); k++)
	  s += (Real) abs((*this)(j,k));
	t = max(t, s);
      }
      return t;
    };

    /**
       Return the Frobenius norm.
    */
    Real frobnorm (void) const {
      Real s = 0;
      for (Index k = 0; k < this->size(); k++)
	s = pythag(s, (Real) abs((*this)(k)));
      return s;
    };

    /**
       The vector 2-norm (Euclidean norm)
    */
    virtual Real norm (void) const {
      Real s = 0;
      for (Index k = 0; k < this->size(); k++)
	s = pythag(s, (Real) abs((*this)(k)));
      return s;
    };

    /**
       The vector 1-norm (sum-norm).
    */
    virtual Real sumnorm (void) const {
      Real s = 0;
      for (Index k = 0; k < this->size(); k++)
	s += (Real) abs((*this)(k));
      return s;
    };

    /**
       The vector infinity-norm (max-norm).
    */
    virtual Real maxnorm (void) const {
      Real s = 0;
      for (Index k = 0; k < this->size(); k++)
	s = max(s, (Real) abs((*this)(k)));
      return s;
    };

    /**
       Inner product with another vector.
    */
    virtual Scalar dot (const Matrix<Scalar>& x) const {
      Scalar d = 0;
      if (this->size() != x.size())
	throw DimError("scalar product");
      for (Index k = 0; k < this->size(); k++)
	d += (*this)(k) * x(k);
      return d;
    }

    /**
       Randomize the matrix
    */
    Matrix& operator = (Random& r) {
      for (Index k = 0; k < this->size(); k++)
	(*this)(k) = r();
      return *this;
    };

    /**
       Set all entries equal to a constant
    */
    template <class RScalar> 
    Matrix& all_entries (const RScalar& t) {
      for (Index k = 0; k < this->size(); k++) (*this)(k) = t;
      return *this;
    };


    // Friend classes & functions
    friend class EigenDecomposition<Scalar>;
    friend class LUDecomposition<Scalar>;
    friend class SVDecomposition<Scalar>;
    friend class QRDecomposition<Scalar>;
    friend class CholeskyDecomposition<Scalar>;

  };

  Matrix<Complex> *eigenvals (const Matrix<Real>&);
  Matrix<Real> *singvals (const Matrix<Real>&);

  /**
     Formatted output
  */
  template <class Scalar>
  inline std::ostream&
  operator << (std::ostream& o, const Matrix<Scalar>& x)
  {
    o << NewLine;
    for (Index j = 0; j < x.rows(); j++) {
      for (Index k = 0; k < x.cols(); k++) o << Blank << Blank << x(j,k);
      o << NewLine;
    }
    return o;
  }

}

#include "GenMatrix.h"
#include "RealMatrix.h"
#include "ComplexMatrix.h"

#endif



