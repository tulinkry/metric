#include "exceptions.h"

/* -------------------------------------------------------------------------------------- */
/*                     EXCEPTION                                                          */
/* -------------------------------------------------------------------------------------- */

Exception::Exception ( const char * msg, int error ) : m_Msg ( msg ), m_Error ( error ) {}

const char * Exception::what ( void ) const
{
	return m_Msg . c_str ();
}
const int Exception::error ( void ) const
{
	return m_Error;
}

/* -------------------------------------------------------------------------------------- */
/*                     INVALID INDEX                                                      */
/* -------------------------------------------------------------------------------------- */

InvalidIndexException::InvalidIndexException ( const char * msg, int error ) : Exception ( msg, error ) {}

/* -------------------------------------------------------------------------------------- */
/*                     INVALID SIZE                                                       */
/* -------------------------------------------------------------------------------------- */

InvalidVectorSizeException::InvalidVectorSizeException ( const char * msg, int error ) : Exception ( msg, error ) {}

/* -------------------------------------------------------------------------------------- */
/*                     BAD PARAMETER                                                      */
/* -------------------------------------------------------------------------------------- */

BadParameterException::BadParameterException ( const char * msg, int error ) : Exception ( msg, error ) {}
