#include "laesa.h"


/* ------------------------------------------------------------------------------------- */
/* 					   STRUCTURES                                                        */
/* ------------------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------------------- */
/* 					   TOBJECT                                                           */
/* ------------------------------------------------------------------------------------- */

static int cnt = 1;

laesa::TObjects::TObject::TObject ( const vector & x ) : m_Vector ( x ), m_Size ( 0 ), m_SizeMax ( 10 ) 
{
	m_Id = cnt ++;
	m_Array = new double * [ m_SizeMax ];
	for ( int i = 0; i < m_SizeMax; i ++ )
		m_Array [ i ] = new double;
}

void laesa::TObjects::TObject::resize ( int size )
{
	if ( size == - 1 ) // default
		size = m_SizeMax * 2;
	m_SizeMax = size;
	double ** newpole = new double* [ size ];

	for ( int i = 0; i < ( m_SizeMax > size ? size : m_SizeMax ); i ++ )
		newpole [ i ] = m_Array [ i ];

	delete [] m_Array;
	m_Array = newpole; 	
}


/* ------------------------------------------------------------------------------------- */
/* 					   TPIVOT                                                            */
/* ------------------------------------------------------------------------------------- */

laesa::TPivots::TPivot::TPivot ( const vector & x ) : TObject ( x ) {}


void laesa::TPivots::TPivot::resize ( int size )
{
	if ( size == - 1 ) // default
		size = m_SizeMax * 2;
	int prevSize = m_SizeMax;
	m_SizeMax = size;
	double ** newpole = new double* [ size ];

	for ( int i = 0; i < prevSize; i ++ )
		newpole [ i ] = m_Array [ i ];
	for ( int i = prevSize; i < m_SizeMax; i ++ )
		newpole [ i ] = new double;

	for ( int i = size; i < m_SizeMax; i ++ )
		delete m_Array [ i ];

	delete [] m_Array;
	m_Array = newpole; 	
}

/* ------------------------------------------------------------------------------------- */
/* 					   TOBJECTS                                                          */
/* ------------------------------------------------------------------------------------- */




laesa::TObjects::TObjects ( void )
{
	m_Size = 0;
	m_SizeMax = 10;
	m_Objects = new TObject* [ m_SizeMax ];
}

laesa::TObjects::~TObjects ( void )
{
	for ( int i = 0; i < m_Size; i ++ )
		delete m_Objects [ i ];
	delete [] m_Objects;
}

int laesa::TObjects::add ( const vector & x )
{
	if ( m_Size + 1 >= m_SizeMax )
		resize ();
	m_Objects [ m_Size ++ ] = new TObject ( x );
	return m_Size - 1;;
}

void laesa::TObjects::resize ( int size )
{
	if ( size == - 1 ) // default
		size = m_SizeMax * 2;
	m_SizeMax = size;
	TObject ** newpole = new TObject* [ size ];
	for ( int i = 0; i < ( m_Size > size ? size : m_Size ); i ++ )
		newpole [ i ] = m_Objects [ i ];
	for ( int i = size; i < m_Size; i ++ )
		delete m_Objects [ i ];
	m_Size = m_Size > size ? size : m_Size;
	delete [] m_Objects;
	m_Objects = newpole; 
}

laesa::TObjects::TObject & laesa::TObjects::operator [] ( int index )
{
	return *m_Objects [ index ];
}
const laesa::TObjects::TObject & laesa::TObjects::operator [] ( int index ) const
{
	return *m_Objects [ index ];
}

/* ------------------------------------------------------------------------------------- */
/* 					   TPIVOTS                                                           */
/* ------------------------------------------------------------------------------------- */


laesa::TPivots::TPivots ( void )
{
	m_Size = 0;
	m_SizeMax = 10;
	m_Pivots = new TPivot* [ m_SizeMax ];
}

laesa::TPivots::~TPivots ( void )
{
	for ( int i = 0; i < m_Size; i ++ )
		delete m_Pivots [ i ];
	delete [] m_Pivots;
}

int laesa::TPivots::add ( const vector & x )
{
	if ( m_Size + 1 >= m_SizeMax )
		resize ();
	m_Pivots [ m_Size ++ ] = new TPivot ( x );
	return m_Size - 1;
}
void laesa::TPivots::resize ( int size )
{
	if ( size == - 1 ) // default
		size = m_SizeMax * 2;
	m_SizeMax = size;
	TPivot ** newpole = new TPivot* [ size ];
	for ( int i = 0; i < ( m_Size > size ? size : m_Size ); i ++ )
		newpole [ i ] = m_Pivots [ i ];
	for ( int i = size; i < m_Size; i ++ )
		delete m_Pivots [ i ];
	m_Size = m_Size > size ? size : m_Size;
	delete [] m_Pivots;
	m_Pivots = newpole; 	
}

laesa::TPivots::TPivot & laesa::TPivots::operator [] ( int index )
{
	return *m_Pivots [ index ];
}
const laesa::TPivots::TPivot & laesa::TPivots::operator [] ( int index ) const
{
	return *m_Pivots [ index ];
}




/* ------------------------------------------------------------------------------------- */
/* 					    LAESA                                                            */
/* ------------------------------------------------------------------------------------- */




/**
 *
 * Member variables
 *
 *	TObject	 ** m_Objects;
 *	TPivot	 ** m_Pivots;
 *
 */


/* -------------------------------------------------------------------------------------- */
/*                     PROTECTED FUNCTIONS                                                */
/* -------------------------------------------------------------------------------------- */


void laesa::resize ( int size )
{
}
void laesa::generate ( int n )
{
	if ( n > m_Objects . m_Size )
		throw new BadParameterException ( "The parameter given is greater than the actual size of table" );

	int cnt = 0;
	while ( cnt < n )
	{
		int random = rand () % ( m_Objects . m_Size / n ) + cnt * ( m_Objects . m_Size / n ) + ( ( cnt - 1 == n ) ? m_Objects . m_Size % n : 0 );

		m_Pivots . add ( m_Objects [ random ] . m_Vector );

		//double * ptr = m_Pivots [ pvtidx ] . m_Array [ random ];
		//m_Objects [ random ] . setPivot ( pvtidx,  ptr );

		cnt ++;
	} 

	refresh ();
}
void laesa::refresh ( void )
{
	if ( m_Pivots . m_Size )
	{
		for ( int i = 0; i < m_Objects . m_Size; i ++ )
		{
			for ( int j = 0; j < m_Pivots . m_Size; j ++ )
			{
				if ( m_Pivots [ j ] . m_SizeMax < m_Objects . m_Size )
					m_Pivots [ j ] . resize ( m_Objects . m_Size );
				if ( m_Objects [ i ] . m_SizeMax < m_Pivots . m_Size )
					m_Objects [ i ] . resize ( m_Pivots . m_Size );

				m_Objects [ i ] . m_Array [ j ] = m_Pivots  [ j ] . m_Array [ i ];
				m_Pivots [ j ]  . m_Array [ i ] = m_Objects [ i ] . m_Array [ j ];
				*(m_Pivots [ j ] . m_Array [ i ]) = distance ( m_Pivots [ j ] . m_Vector, m_Objects [ i ] . m_Vector );
			}
		}		
	}



}

laesa::Proxy laesa::operator [] ( int index )
{
	if ( index > m_Pivots . m_Size - 1 || index < 0 )
		throw new InvalidIndexException ( "Index is out of range" );

	return Proxy ( m_Pivots [ index ] . m_Array, m_Objects . m_Size );
}
const laesa::Proxy laesa::operator [] ( int index ) const
{
	if ( index > m_Pivots . m_Size - 1 || index < 0 )
		throw new InvalidIndexException ( "Index is out of range" );
	return Proxy ( m_Pivots [ index ] . m_Array, m_Objects . m_Size );
}

/* -------------------------------------------------------------------------------------- */
/*                     CONSTRUCTORS	                                                      */
/* -------------------------------------------------------------------------------------- */

laesa::laesa ( void )
{

}
laesa::laesa ( const laesa & x )
{

}
laesa::~laesa ( void )
{

}

/* -------------------------------------------------------------------------------------- */
/*                     FUNCTIONS 	                                                      */
/* -------------------------------------------------------------------------------------- */


laesa & laesa::add ( const vector & x )
{
	m_Objects . add ( x );


	refresh ();
	return *this;
}


/* -------------------------------------------------------------------------------------- */
/*                     QUERY    	                                                      */
/* -------------------------------------------------------------------------------------- */

#include <cstdlib>

int cmp ( const void * a, const void * b )
{
	cout << (*(*(laesa::TObjects::TObject ***)a)) -> m_Size << endl;
	double max1 = 0, max2 = 0;
	for ( int i = 0; i < (*(laesa::TObjects::TObject *)a) . m_Size; i ++ )
		if ( *(*(laesa::TObjects::TObject *)a) . m_Array [ i ] > max1 )
			max1 = *(*(laesa::TObjects::TObject *)a) . m_Array [ i ];
	for ( int i = 0; i < (*(laesa::TObjects::TObject *)b) . m_Size; i ++ )
		if ( *(*(laesa::TObjects::TObject *)b) . m_Array [ i ] > max2 )
			max2 = *(*(laesa::TObjects::TObject *)b) . m_Array [ i ];	
	return max1 - max2;
}

void laesa::sort ( TObjects::TObject ** objects, int len ) const
{
    /*bool done = false;
	int size = len;
    while ( ! done )
    {
        done = true;
        for (int i = 0 ; i < size-1 ; i++)
        {
            if ( (*this)[ i ][ 0 ] > (*this) [ i + 1 ] [ 0 ] )
            {
                done = false;
                TObjects::TObject * tmp = objects [ i ];
                objects [ i ] = objects [ i + 1 ];
                objects [ i + 1 ] = tmp;
            }
        }
        size--;
    }	*/
    qsort ( objects, len, sizeof ( *objects ), cmp );

}

result * laesa::kNN ( const vector & x, int k, result * results ) const
{
	sort ( m_Objects . m_Objects, m_Objects . m_Size );
/**
	TObjects::TObject ** obj = new TObjects::TObject*[ m_Objects . m_Size ];

	for ( int i = 0; i < m_Objects . m_Size; i ++ )
		obj [ i ] = m_Objects . m_Objects [ i ];


	for ( int i = 0; i < m_Objects . m_Size; i ++ )
		cout << *obj [ i ] << endl;

	sort ( obj, m_Objects . m_Size );

	for ( int i = 0; i < m_Objects . m_Size; i ++ )
		cout << *obj [ i ] << endl;


	delete [] obj;

	*/
	return NULL;
}

result * laesa::range ( const vector & x, double range, result * results ) const
{
	if ( ! results )
		results = new result;

	bool * isAdded = new bool [ m_Objects . m_Size ];
	for ( int i = 0; i < m_Objects . m_Size; i ++ )
		isAdded [ i ] = false;

	for ( int i = 0; i < m_Pivots . m_Size; i ++ )
	{
		for ( int j = 0; j < m_Objects . m_Size; j ++ )
		{
			if ( range <= ( distance ( x, m_Pivots [ i ] . m_Vector ) + (*this)[i][j] ) )
			{
				// prepocitej vzdalenost
				// uloz
				if ( distance ( x, m_Objects [ j ] . m_Vector) <= range )
				{
					if ( ! isAdded [ j ] )
					{
						isAdded [ j ] = true;
						results -> add ( m_Objects [ j ] . m_Vector );
						//results [ size ++ ] = new vector ( m_Objects [ j ] . m_Vector );
					}
				}
			}
			// neni takze nas nezajima
		}
	}
	return results;
}



/* -------------------------------------------------------------------------------------- */
/*                     PRINT FUNCTIONS                                                    */
/* -------------------------------------------------------------------------------------- */

void laesa::print ( ostream & os ) const
{

	os << "  laesa  |";
	for ( int i = 0; i < m_Objects . m_Size; i ++ )
	{
		os << setw ( 0 ) << m_Objects [ i ] << "|";
		if ( i != m_Objects . m_Size - 1 )
			cout << " ";
	}
	if ( m_Pivots . m_Size > 0 )
	{
		cout << endl;
		cout << setw ( m_Objects . m_Size * 11 + 9 ) << setfill ( '=' ) << "|" << setfill ( ' ' ) << endl;
		
	}
	for ( int i = 0; i < m_Pivots . m_Size; i ++ )
	{
		os << setw ( 0 ) << m_Pivots [ i ] << "|";
		for ( int j = 0; j < m_Objects . m_Size; j ++ )
		{
			os << setw ( 9 ) << *(m_Pivots . m_Pivots [ i ] -> m_Array [ j ]) << "|";
			if ( j != m_Objects . m_Size - 1 )
				os << " ";
		}
		if ( i != m_Pivots . m_Size - 1 )
			cout << endl;
	}

}


ostream & operator << ( ostream & os, const laesa & x )
{
	x . print ( os );
	return os;
}