#include "vector.h"


using namespace std;

/* -------------------------------------------------------------------------------------- */
/*                     PROTECTED FUNCTIONS                                                */
/* -------------------------------------------------------------------------------------- */

void vector::resize ( int size )
{
	m_MaxSize = size;
	double * newpole = new double [ size ];
	for ( int i = 0; i < ( m_Size > size ? size : m_Size ); i ++ )
		newpole [ i ] = m_Vector [ i ];
	m_Size = m_Size > size ? size : m_Size;
	delete [] m_Vector;
	m_Vector = newpole; 
}


/* -------------------------------------------------------------------------------------- */
/*                     CONSTRUCTORS	                                                      */
/* -------------------------------------------------------------------------------------- */

vector::vector ( int size ) : m_MaxSize ( size ), m_Size ( 0 )
{
	m_Vector = new double [ m_MaxSize ];
	for ( int i = 0; i < m_MaxSize; i ++ )
		m_Vector [ i ] = 0.0;
}

vector::vector ( int size, double number ) : m_MaxSize ( size ), m_Size ( size )
{	
	m_Vector = new double [ m_MaxSize ];
	for ( int i = 0; i < m_MaxSize; i ++ )
		m_Vector [ i ] = number;
}
vector::vector ( const vector & x ) : m_MaxSize ( x . m_MaxSize ), m_Size ( x . m_Size )
{
	m_Vector = new double [ m_MaxSize ];
	for ( int i = 0; i < m_MaxSize; i ++ )
		m_Vector [ i ] = x . m_Vector [ i ];
}
vector::~vector ( void )
{
	delete [] m_Vector;
}


/* -------------------------------------------------------------------------------------- */
/*                     FUNCTIONS 	                                                      */
/* -------------------------------------------------------------------------------------- */


vector & vector::operator = ( const vector & x )
{
	if ( &x == this )
		return *this;
	
	delete [] m_Vector;

	m_MaxSize = x . m_MaxSize;
	m_Size = x . m_Size;

	m_Vector = new double [ m_MaxSize ];

	for ( int i = 0; i < m_MaxSize; i ++ )
		m_Vector [ i ] = x . m_Vector [ i ];

	return *this;
}
double & vector::operator [] ( int index )
{
	if ( index > m_MaxSize - 1 || index < 0 )
		throw new InvalidIndexException ( "Index is out of range" );
	m_Size = index + 1;
	return m_Vector [ index ];
}
const double & vector::operator [] ( int index ) const
{
	if ( index > m_MaxSize - 1 || index < 0 )
		throw new InvalidIndexException ( "Index is out of range" );
	return m_Vector [ index ];	
}

int vector::size ( void ) const
{
	return m_Size;
}

/* -------------------------------------------------------------------------------------- */
/*                     PRINT FUNCTIONS                                                    */
/* -------------------------------------------------------------------------------------- */

void vector::print ( ostream & os ) const 
{
	os << "[ ";
	for ( int i = 0; i < m_Size; i ++ )
	{
		os << m_Vector [ i ];

		if ( i != m_Size - 1 )
			os << ", ";
	}
	os << " ]";
}


ostream & operator << ( ostream & os, const vector & x )
{
	x . print ( os );
	return os;
}