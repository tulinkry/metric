#ifndef EXCEPTIONS_H_5ff6s5df16d5s1df6s5df16ds5f16sd5f16sdf1
#define EXCEPTIONS_H_5ff6s5df16d5s1df6s5df16ds5f16sd5f16sdf1

#include <string>

class Exception
{
	protected:
		std::string m_Msg;
		int m_Error;
	public:
		Exception ( const char * msg = "", int error = 0 );
		virtual const char * what ( void ) const;
		virtual const int error ( void ) const;
};


class InvalidIndexException : public Exception
{
	public:
		InvalidIndexException ( const char * msg = "", int error = 0 );
};

class InvalidVectorSizeException : public Exception
{
	public:
		InvalidVectorSizeException ( const char * msg = "", int error = 0 );
};

class BadParameterException : public Exception
{
	public:
		BadParameterException ( const char * msg = "", int error = 0 );
};

#endif