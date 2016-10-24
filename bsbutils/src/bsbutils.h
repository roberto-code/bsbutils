#ifndef _BSB_UTILS_H
#define _BSB_UTILS_H

#include <Rcpp.h>

#include <vector>

RcppExport SEXP rarefy( SEXP theMatrix, SEXP theSampleDepth, SEXP theSumSample, SEXP theSelSampleCall );

template <typename T>
void selectionSample( const std::vector<T> theVector, const size_t theSize, std::vector<T> &theResultVector, size_t theExecutionNumber );


#endif
