#ifndef INDEX_TABLES_H_as54sdf6sd1fsd61f6sdf1sd65f1sd6f16sd5f16sd5f16sd5
#define INDEX_TABLES_H_as54sdf6sd1fsd61f6sdf1sd65f1sd6f16sd5f16sd5f16sd5

#include <iostream>
#include <cmath>

#include "exceptions.h"
#include "vector.h"
#include "result.h"

class IndexTables
{

		virtual void print ( std::ostream & os ) const = 0;
	public:
		/**
		 * kNN query
		 * @param x Query vector
		 * @param k is the number of nearest neighbours
		 * @param results if specified the results are stored here; if not the new memory is allocated end returned
		 * @return return the pointer to the results
		 */
		virtual result * kNN ( const vector & x, int k, result * results = NULL ) const = 0;
		/**
		 * Range query
		 * @param x Query vector
		 * @param range is the maximum range
		 * @param results if specified the results are stored here; if not the new memory is allocated end returned
		 * @return return the pointer to the results
		 */
		virtual result * range ( const vector & x, double range, result * results = NULL ) const = 0;

		/**
		 * Distance function
		 * Uses euclidean space metric
		 * ret = SQRT( SUM ( (x[i] - y[i])^2 ) )
		 * @param x vector x
		 * @param y vector y
		 * @return distance between vector x and y
		 */
		static double distance ( const vector & x, const vector & y )
		{
			if ( x . size () != y . size () )
				throw new InvalidVectorSizeException ( "Size of the vectors has to be equal" );
			
			int size = x . size ();
			double result = 0;

			for ( int i = 0; i < size; i ++ )
				result += ( x [ i ] - y [ i ] ) * ( x [ i ] - y [ i ] );

			return sqrt ( result );
		}

};



#endif