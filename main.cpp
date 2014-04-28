#include <iostream>
#include <iomanip>
#include <fstream>


#include "exceptions.h"
#include "vector.h"
#include "result.h"
#include "laesa.h"

using namespace std;




int main ( int argc, char ** argv )
{
	srand ( time ( NULL ) );

	laesa x;

	for ( int i = 1; i < 10; i ++ )
		x . add ( vector ( 1, i ) );

	x . generate ( 2 );


	cout << x << endl; 


	result res;
	//x . range ( vector ( 1, 5 ), 1, &res );
	

	//cout << res << endl;
	
	//for ( int i = 0; i < res . size (); i ++ )
	//{
	//	cout << res [ i ] << " -> ";
	//	cout << laesa::distance ( res [ i ] . m_Vector, vector ( 1, 5 ) ) << endl;
	//}

	x . kNN ( vector ( 1, 5 ), 1, &res );
	



	return 0;
}