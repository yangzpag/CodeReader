/* Generated by Together */
#include "ApplicationKit.h"
#include "DataType.h"



using namespace VCF;

DataType::DataType( const unsigned long & rawType )
{
	if ( rawType == BASIC_DATA_TYPE ){
		//throw an exception here or error out 
	}
	this->m_rawType = rawType;
}

unsigned long DataType::getRawType()
{
	return m_rawType;
}

String DataType::getMimeEncodedInfo()
{
	String result = "";
	return result;
}
