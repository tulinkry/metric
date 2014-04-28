#ifndef VECTOR_H_df3g21dfgdfb1c2vb13cvb1df5d1f65b1d6f5b1d65f6b1f6
#define VECTOR_H_df3g21dfgdfb1c2vb13cvb1df5d1f65b1d6f5b1d65f6b1f6

#include <iostream>
#include <iomanip>

#include "exceptions.h"

class vector
{
	protected:
		/**
		 * vector array
		 */
		double * m_Vector;
		/**
		 * capacity of the vector
		 */
		int m_MaxSize;
		/**
		 * actual size of the vector
		 */
		int m_Size;
		/**
		 * resizes the vector on size if specified
		 * @param size the new size
		 */
		void resize ( int size );
		/**
		 * handling the output to the output stream
		 * @param os the output stream
		 */
		void print ( std::ostream & os ) const;
	public:
		/**
		 * Default constructor of vector class\n
		 * Initializes the vector size on the number, default is 10
		 * @param size the default size
		 */
		vector ( int size = 10 );
		/**
		 * Constructor\n
		 * Initializes the vector to size @param size and fills it with number @param number
		 * @param size default size
		 * @param number number to fill the vector
		 */
		vector ( int size, double number = 0 );
		/**
		 * Copy constructor
		 * @param x the source vector
		 */
		vector ( const vector & x );
		/**
		 * Destructor
		 */
		~vector ( void );

		/**
		 * Overloaded operator [] to easy access the property
		 * @param index index in array
		 * @return reference to the value on specified index
		 * @throws InvalidIndexException if the index is invalid
		 */
		double & operator [] ( int index );
		/**
		 * Overloaded operator [] to easy access the property
		 * @param index index in array
		 * @return reference to the value on specified index
		 * @throws InvalidIndexException if the index is invalid
		 */
		const double & operator [] ( int index ) const;
		/**
		 * Overloaded operator =
		 * @param x the source vector
		 * @return *this
		 */
		vector & operator = ( const vector & x );
		/**
		 * @return actual size of the vector
		 */
		int size ( void ) const;
 		/**
 		 * Overloaded operator << for easy handling the output
 		 */
		friend std::ostream & operator << ( std::ostream & os, const vector & x );
};



#endif