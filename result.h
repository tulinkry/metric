#ifndef RESULT_H_65sdfs6d5fs4d65f4sd65f16cxv16516s5d16s51d6d5f
#define RESULT_H_65sdfs6d5fs4d65f4sd65f16cxv16516s5d16s51d6d5f

#include <iostream>
#include <iomanip>

#include "result.h"
#include "vector.h"
#include "exceptions.h"

class result
{
	protected:
		struct TResult
		{
			int m_Id;
			vector m_Vector;
			/**
			 * std::string m_Name;
			 */
			TResult ( const vector & x );
			friend std::ostream & operator << ( std::ostream & os, const TResult & x )
			{
				os << "[" << std::setw ( 4 ) << x . m_Id << "] -> " << x . m_Vector;
				return os;
			}
		};

		TResult ** m_Results;
		int m_Size;
		int m_MaxSize;

		void resize ( int size = -1 );
		void print ( std::ostream & os ) const;
	public:
		result ( int size = 10 );
		result ( const result & x );
		~result ( void );

		result & add ( const vector & x /**, const string & name */ );

		TResult & operator [] ( int index );
		const TResult & operator [] ( int index ) const;
		result & operator = ( const result & x );

		int size ( void ) const;
 
		friend std::ostream & operator << ( std::ostream & os, const result & x );
};




#endif