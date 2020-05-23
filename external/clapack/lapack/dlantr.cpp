#include "clapack.h"
#include "f2cP.h"

/* Subroutine */ double dlantr_(const char *norm, const char *uplo, const char *diag, integer *m, integer *n,
	 double *a, integer *lda, double *work)
{
	/* Table of constant values */
	static integer c__1 = 1;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4;
    double ret_val, d__1, d__2, d__3;

    /* Local variables */
    integer i__, j;
    double sum, scale;
    bool udiag;
    double value;


/*  -- LAPACK auxiliary routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLANTR  returns the value of the one norm,  or the Frobenius norm, or */
/*  the  infinity norm,  or the  element of  largest absolute value  of a */
/*  trapezoidal or triangular matrix A. */

/*  Description */
/*  =========== */

/*  DLANTR returns the value */

/*     DLANTR = ( max(abs(A(i,j))), NORM = 'M' or 'm' */
/*              ( */
/*              ( norm1(A),         NORM = '1', 'O' or 'o' */
/*              ( */
/*              ( normI(A),         NORM = 'I' or 'i' */
/*              ( */
/*              ( normF(A),         NORM = 'F', 'f', 'E' or 'e' */

/*  where  norm1  denotes the  one norm of a matrix (maximum column sum), */
/*  normI  denotes the  infinity norm  of a matrix  (maximum row sum) and */
/*  normF  denotes the  Frobenius norm of a matrix (square root of sum of */
/*  squares).  Note that  max(abs(A(i,j)))  is not a consistent matrix norm. */

/*  Arguments */
/*  ========= */

/*  NORM    (input) CHARACTER*1 */
/*          Specifies the value to be returned in DLANTR as described */
/*          above. */

/*  UPLO    (input) CHARACTER*1 */
/*          Specifies whether the matrix A is upper or lower trapezoidal. */
/*          = 'U':  Upper trapezoidal */
/*          = 'L':  Lower trapezoidal */
/*          Note that A is triangular instead of trapezoidal if M = N. */

/*  DIAG    (input) CHARACTER*1 */
/*          Specifies whether or not the matrix A has unit diagonal. */
/*          = 'N':  Non-unit diagonal */
/*          = 'U':  Unit diagonal */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0, and if */
/*          UPLO = 'U', M <= N.  When M = 0, DLANTR is set to zero. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0, and if */
/*          UPLO = 'L', N <= M.  When N = 0, DLANTR is set to zero. */

/*  A       (input) DOUBLE PRECISION array, dimension (LDA,N) */
/*          The trapezoidal matrix A (A is triangular if M = N). */
/*          If UPLO = 'U', the leading m by n upper trapezoidal part of */
/*          the array A contains the upper trapezoidal matrix, and the */
/*          strictly lower triangular part of A is not referenced. */
/*          If UPLO = 'L', the leading m by n lower trapezoidal part of */
/*          the array A contains the lower trapezoidal matrix, and the */
/*          strictly upper triangular part of A is not referenced.  Note */
/*          that when DIAG = 'U', the diagonal elements of A are not */
/*          referenced and are assumed to be one. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(M,1). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (MAX(1,LWORK)), */
/*          where LWORK >= M when NORM = 'I'; otherwise, WORK is not */
/*          referenced. */

/* ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --work;

    /* Function Body */
    if (std::min(*m,*n) == 0) {
	value = 0.;
    } else if (lsame_(norm, "M")) {

/*        Find max(abs(A(i,j))). */

	if (lsame_(diag, "U")) {
	    value = 1.;
	    if (lsame_(uplo, "U")) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
/* Computing MIN */
		    i__3 = *m, i__4 = j - 1;
		    i__2 = std::min(i__3,i__4);
		    for (i__ = 1; i__ <= i__2; ++i__) {
/* Computing MAX */
			d__2 = value, d__3 = (d__1 = a[i__ + j * a_dim1], abs(
				d__1));
			value = std::max(d__2,d__3);
/* L10: */
		    }
/* L20: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m;
		    for (i__ = j + 1; i__ <= i__2; ++i__) {
/* Computing MAX */
			d__2 = value, d__3 = (d__1 = a[i__ + j * a_dim1], abs(
				d__1));
			value = std::max(d__2,d__3);
/* L30: */
		    }
/* L40: */
		}
	    }
	} else {
	    value = 0.;
	    if (lsame_(uplo, "U")) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = std::min(*m,j);
		    for (i__ = 1; i__ <= i__2; ++i__) {
/* Computing MAX */
			d__2 = value, d__3 = (d__1 = a[i__ + j * a_dim1], abs(
				d__1));
			value = std::max(d__2,d__3);
/* L50: */
		    }
/* L60: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m;
		    for (i__ = j; i__ <= i__2; ++i__) {
/* Computing MAX */
			d__2 = value, d__3 = (d__1 = a[i__ + j * a_dim1], abs(
				d__1));
			value = std::max(d__2,d__3);
/* L70: */
		    }
/* L80: */
		}
	    }
	}
    } else if (lsame_(norm, "O") || *(unsigned char *)
	    norm == '1') {

/*        Find norm1(A). */

	value = 0.;
	udiag = lsame_(diag, "U");
	if (lsame_(uplo, "U")) {
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		if (udiag && j <= *m) {
		    sum = 1.;
		    i__2 = j - 1;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			sum += (d__1 = a[i__ + j * a_dim1], abs(d__1));
/* L90: */
		    }
		} else {
		    sum = 0.;
		    i__2 = std::min(*m,j);
		    for (i__ = 1; i__ <= i__2; ++i__) {
			sum += (d__1 = a[i__ + j * a_dim1], abs(d__1));
/* L100: */
		    }
		}
		value = std::max(value,sum);
/* L110: */
	    }
	} else {
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		if (udiag) {
		    sum = 1.;
		    i__2 = *m;
		    for (i__ = j + 1; i__ <= i__2; ++i__) {
			sum += (d__1 = a[i__ + j * a_dim1], abs(d__1));
/* L120: */
		    }
		} else {
		    sum = 0.;
		    i__2 = *m;
		    for (i__ = j; i__ <= i__2; ++i__) {
			sum += (d__1 = a[i__ + j * a_dim1], abs(d__1));
/* L130: */
		    }
		}
		value = std::max(value,sum);
/* L140: */
	    }
	}
    } else if (lsame_(norm, "I")) {

/*        Find normI(A). */

	if (lsame_(uplo, "U")) {
	    if (lsame_(diag, "U")) {
		i__1 = *m;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    work[i__] = 1.;
/* L150: */
		}
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
/* Computing MIN */
		    i__3 = *m, i__4 = j - 1;
		    i__2 = std::min(i__3,i__4);
		    for (i__ = 1; i__ <= i__2; ++i__) {
			work[i__] += (d__1 = a[i__ + j * a_dim1], abs(d__1));
/* L160: */
		    }
/* L170: */
		}
	    } else {
		i__1 = *m;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    work[i__] = 0.;
/* L180: */
		}
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = std::min(*m,j);
		    for (i__ = 1; i__ <= i__2; ++i__) {
			work[i__] += (d__1 = a[i__ + j * a_dim1], abs(d__1));
/* L190: */
		    }
/* L200: */
		}
	    }
	} else {
	    if (lsame_(diag, "U")) {
		i__1 = *n;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    work[i__] = 1.;
/* L210: */
		}
		i__1 = *m;
		for (i__ = *n + 1; i__ <= i__1; ++i__) {
		    work[i__] = 0.;
/* L220: */
		}
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m;
		    for (i__ = j + 1; i__ <= i__2; ++i__) {
			work[i__] += (d__1 = a[i__ + j * a_dim1], abs(d__1));
/* L230: */
		    }
/* L240: */
		}
	    } else {
		i__1 = *m;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    work[i__] = 0.;
/* L250: */
		}
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m;
		    for (i__ = j; i__ <= i__2; ++i__) {
			work[i__] += (d__1 = a[i__ + j * a_dim1], abs(d__1));
/* L260: */
		    }
/* L270: */
		}
	    }
	}
	value = 0.;
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	    d__1 = value, d__2 = work[i__];
	    value = std::max(d__1,d__2);
/* L280: */
	}
    } else if (lsame_(norm, "F") || lsame_(norm, "E")) {

/*        Find normF(A). */

	if (lsame_(uplo, "U")) {
	    if (lsame_(diag, "U")) {
		scale = 1.;
		sum = (double) std::min(*m,*n);
		i__1 = *n;
		for (j = 2; j <= i__1; ++j) {
/* Computing MIN */
		    i__3 = *m, i__4 = j - 1;
		    i__2 = std::min(i__3,i__4);
		    dlassq_(&i__2, &a[j * a_dim1 + 1], &c__1, &scale, &sum);
/* L290: */
		}
	    } else {
		scale = 0.;
		sum = 1.;
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = std::min(*m,j);
		    dlassq_(&i__2, &a[j * a_dim1 + 1], &c__1, &scale, &sum);
/* L300: */
		}
	    }
	} else {
	    if (lsame_(diag, "U")) {
		scale = 1.;
		sum = (double) std::min(*m,*n);
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m - j;
/* Computing MIN */
		    i__3 = *m, i__4 = j + 1;
		    dlassq_(&i__2, &a[std::min(i__3, i__4)+ j * a_dim1], &c__1, &
			    scale, &sum);
/* L310: */
		}
	    } else {
		scale = 0.;
		sum = 1.;
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m - j + 1;
		    dlassq_(&i__2, &a[j + j * a_dim1], &c__1, &scale, &sum);
/* L320: */
		}
	    }
	}
	value = scale * sqrt(sum);
    }

    ret_val = value;
    return ret_val;

/*     End of DLANTR */

} /* dlantr_ */
