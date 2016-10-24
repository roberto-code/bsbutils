#include "bsbutils.h"

#include <time.h>

SEXP rarefy( SEXP theMatrix, SEXP theSampleDepth, SEXP theSumSample, SEXP theSelSampleCall )
{
	Rcpp::NumericMatrix lvOrigMatrix( theMatrix );
	Rcpp::NumericMatrix lvRarefiedMatrix( lvOrigMatrix.nrow(), lvOrigMatrix.ncol() );
	
	Rcpp::NumericVector lvSumSample( theSumSample );
	
	int lvSampleDepth = Rcpp::as<int>(theSampleDepth);
	int lvSelSampleCall = Rcpp::as<int>(theSelSampleCall);
	
	for( int i = 0; i < lvOrigMatrix.ncol();i++ )
	{
		//if( lvSampleDepth > lvSumSample[i] )
		//{
		//	Rprintf("Skipping sample %d\n", i);
		//}
		//vector whose size is the total amount of reads for this sample
		std::vector<size_t> lvPreSamp( lvSumSample(i) ); 
		
		//fill the vectors with increasing values from 1 to the total amount of reads for this sample
		for( int lvCounter = 0; lvCounter < lvPreSamp.size(); lvCounter++ )
		{
			lvPreSamp[lvCounter] = lvCounter+1;
		}
		std::vector<size_t> lvSampVecR;
		
		//fill lvSampVecR with random elements from lvPreSamp. The size of lvSampVecR is the depth of the rarefaction
		selectionSample<size_t>( lvPreSamp, lvSampleDepth, lvSampVecR, lvSelSampleCall );
		

		size_t runSum = 0, idx = 0, totalSum = 0, cnt = 0;
		size_t lvSampleVectorSize = lvSampVecR.size();

		for( int j = 0; j < lvOrigMatrix.nrow(); j++ )
		{
			cnt++;
			size_t rare = 0;
			runSum += lvOrigMatrix(j,i); //running over the matrix by samples(columns)
			while( runSum >= lvSampVecR[idx] && idx < lvSampleVectorSize)
			{
				idx++;
				rare++;
				totalSum++;
			}
		
			lvRarefiedMatrix(j,i) = rare;
			
		}
	}
	
	return lvRarefiedMatrix;
}

template <typename T>
void selectionSample( const std::vector<T> theVector, const size_t theSize, std::vector<T> &theResultVector, size_t theExecutionNumber )
{
	srand (time(NULL) + theExecutionNumber ); //set the seed
	size_t lvPos = 0;
	
	while( theResultVector.size() < theSize )
	{
		while( rand()%(theVector.size()-lvPos) + 1 > ( theSize-theResultVector.size() ) )
		{
			lvPos++;
		}
		theResultVector.push_back( theVector[lvPos++] );
	}
}