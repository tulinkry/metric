#ifndef LAESA_H_321551dgs65fds1f65sd1fs6df51sd6f51sd6f51s6d5fs6df
#define LAESA_H_321551dgs65fds1f65sd1fs6df51sd6f51sd6f51s6d5fs6df

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "vector.h"
#include "result.h"


#include "indexTables.h"



using namespace std;
/**
 * Class laesa\n
 * Implements the basics of the metric access\n
 * 
 * The types of queries implemented:\n
 * kNN query\n
 * range query\n
 */ 
class laesa : public IndexTables
{
	public:


		struct TObjects
		{
			struct TObject
			{
				int 			m_Id;
				vector 			m_Vector;
				double ** 		m_Array;
				int 			m_Size;
				int 			m_SizeMax;

									TObject 	( const vector & x );
				void				resize		( int size = -1 );
				friend ostream & 	operator << ( ostream & os, const TObject & x )
				{
					os << "[" << setw ( 4 ) << x . m_Id << "]: O";
					return os;
				}
			};


			int 				m_Size;
			int 				m_SizeMax;
			TObject ** 			m_Objects;

								TObjects 		( void );
								~TObjects		( void );
			int 				add 			( const vector & x );
			void 				resize 			( int size = -1 );
			TObject & 			operator [] 	( int index );
			const TObject & 	operator [] 	( int index ) const;
		};

		struct TPivots
		{
			struct TPivot : TObjects::TObject
			{	
									TPivot 		( const vector & x );
				void				resize		( int size = -1 );
				friend ostream & operator << 	( ostream & os, const TPivot & x )
				{
					os << "[" << setw ( 4 ) << x . m_Id << "]: P";
					return os;
				}
			};
			int 		m_Size;
			int 		m_SizeMax;
			TPivot ** 	m_Pivots;

							TPivots 		( void );
							~TPivots		( void );
			int 			add 			( const vector & x );
			void 			resize 			( int size = -1 );
			TPivot & 		operator [] 	( int index );
			const TPivot & 	operator [] 	( int index ) const;
		};
		/**
		 * Helper class for the oveloaded operator [][]
		 */
		class Proxy
		{
			protected:
				double ** m_Array;
				int m_Size;
			public:
				Proxy ( double ** array, int size ) : m_Array ( array ), m_Size ( size ) {}
				/**
				 * Overloaed operator [][] for easy access to the laesa table
				 * @param index second index to the laesa table, e. g. row
				 * @return the value
				 * @throws InvalidIndexException if the index is invalid
				 */
				double & operator [] ( int index )
				{
					if ( index > m_Size - 1 || index < 0 )
						throw new InvalidIndexException ( "Index is out of range" );
					return *m_Array[ index ];
				}
				/**
				 * Overloaed operator [][] for easy access to the laesa table
				 * @param index second index to the laesa table, e. g. row
				 * @return the value
				 * @throws InvalidIndexException if the index is invalid
				 */
				const double & operator [] ( int index ) const
				{
					if ( index > m_Size - 1 || index < 0 )
						throw new InvalidIndexException ( "Index is out of range" );
					return *m_Array[ index ];
				}
		};

		TObjects 		m_Objects;
		TPivots 		m_Pivots;

		void 				resize 				( int size = -1 );
		void 				print 				( ostream & os ) const;
		void 				refresh 			( void );

		void sort ( TObjects::TObject ** objects, int len ) const;
		//static int cmp ( TObjects::TObject * a, TObjects::TObject * b );

	public:
							laesa 				( void );
							laesa 				( const laesa & x );
		virtual 			~laesa 				( void );

		/**
		 * Add object to the database
		 * the objects is represented by the vector
		 * @param x object vector
		 * @return *this for chaining
		 */
		laesa & 			add 				( const vector & x );
		/**
		 * Generate the number of pivots\n
		 * pivots are from the object space
		 * @param n the number of pivots to generate
		 */
		void 				generate 			( int n = 3 );
		/**
		 * {@inheritDoc}
		 */
		result *			kNN 				( const vector & x, int k, result * results = NULL ) const;
		/**
		 * {@inheritDoc}
		 */
		result *			range 				( const vector & x, double range, result * results = NULL ) const;
		
		/**
		 * Overloaed operator [][] for easy access to the laesa table
		 * @param index first index to the laesa table, e. g. column
		 * @return helper class for the second index @see Proxy
		 * @throws InvalidIndexException if the index is invalid
		 */
		Proxy				operator []			( int index );
		/**
		 * Overloaed operator [][] for easy access to the laesa table
		 * @param index first index to the laesa table, e. g. column
		 * @return helper class for the second index @see Proxy
		 * @throws InvalidIndexException if the index is invalid
		 */
		const Proxy 		operator []			( int index ) const;

		friend ostream & 	operator << 		( ostream & os, const laesa & x );
};




#endif