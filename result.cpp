#include "result.h"


/* ------------------------------------------------------------------------------------- */
/* 					   STRUCTURES                                                        */
/* ------------------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------------------- */
/* 					   TRESULT                                                           */
/* ------------------------------------------------------------------------------------- */

result::TResult::TResult ( const vector & x ) : m_Vector ( x )
{
	static int cnt = 0;
	m_Id = ++ cnt;
}


/* -------------------------------------------------------------------------------------- */
/*                     PROTECTED FUNCTIONS                                                */
/* -------------------------------------------------------------------------------------- */

void result::resize ( int size )
{
	if ( size == -1 )
		size = m_MaxSize * 2;
	m_MaxSize = size;
	TResult ** newpole = new TResult * [ size ];
	for ( int i = 0; i < ( m_Size > size ? size : m_Size ); i ++ )
		newpole [ i ] = m_Results [ i ];
	for ( int i = size; i < m_Size; i ++ )
		delete m_Results [ i ];
	delete [] m_Results;
	m_Results = newpole;
}


/* -------------------------------------------------------------------------------------- */
/*                     CONSTRUCTORS	                                                      */
/* -------------------------------------------------------------------------------------- */

result::result ( int size ) : m_MaxSize ( size )
{
	m_Size = 0;
	m_Results = new TResult * [ m_MaxSize ];
}
result::result ( const result & x ) : m_Size ( x . m_Size ), m_MaxSize ( x . m_MaxSize )
{
	m_Results = new TResult * [ m_MaxSize ];
	for ( int i = 0; i < m_Size; i ++ )
		m_Results [ i ] = new TResult ( *x . m_Results [ i ] );
}
result::~result ( void )
{
	for ( int i = 0; i < m_Size; i ++ )
		delete m_Results [ i ];
	delete [] m_Results;
}

/* -------------------------------------------------------------------------------------- */
/*                     FUNCTIONS 	                                                      */
/* -------------------------------------------------------------------------------------- */

result & result::add ( const vector & x /**, const string & name */ )
{
	m_Results [ m_Size ++ ] = new TResult ( x );
	return *this;
}

result::TResult & result::operator [] ( int index )
{
	if ( index > m_Size - 1 || index < 0 )
		throw new InvalidIndexException ( "Index is out of range" ); 
	return *m_Results[ index ];
}
const result::TResult & result::operator [] ( int index ) const
{
	if ( index > m_Size - 1 || index < 0 )
		throw new InvalidIndexException ( "Index is out of range" ); 
	return *m_Results [ index ];
}
result & result::operator = ( const result & x )
{
	if ( this == &x )
		return *this;
	for ( int i = 0; i < m_Size; i ++ )
		delete m_Results [ i ];
	delete [] m_Results;

	m_MaxSize = x . m_MaxSize;
	m_Size = x . m_Size;

	m_Results = new TResult * [ m_MaxSize ];
	for ( int i = 0; i < m_Size; i ++ )
		m_Results [ i ] = new TResult ( *x . m_Results [ i ] );

	return *this; 
}

int result::size ( void ) const
{
	return m_Size;
}


/* -------------------------------------------------------------------------------------- */
/*                     PRINT FUNCTIONS                                                    */
/* -------------------------------------------------------------------------------------- */


void result::print ( std::ostream & os ) const
{
	os << "--------------------------------------" << std::endl;
	os << "------- " << m_Size << " results found --------------" << std::endl;
	for ( int i = 0; i < m_Size; i ++ )
		os << *m_Results [ i ] << std::endl;
	os << "--------------------------------------" << std::endl;
}

std::ostream & operator << ( std::ostream & os, const result & x )
{
	x . print ( os );
	return os;
}