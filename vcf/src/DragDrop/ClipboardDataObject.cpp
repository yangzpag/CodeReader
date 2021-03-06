/**
*Copyright (c) 2000-2001, Jim Crafton
*All rights reserved.
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions
*are met:
*	Redistributions of source code must retain the above copyright
*	notice, this list of conditions and the following disclaimer.
*
*	Redistributions in binary form must reproduce the above copyright
*	notice, this list of conditions and the following disclaimer in 
*	the documentation and/or other materials provided with the distribution.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
*OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
*PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
*LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
*NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*NB: This software will not save the world.
*/

/* Generated by Together */
#include "ApplicationKit.h"

#include <algorithm>

using namespace VCF;


ClipboardDataObject::ClipboardDataObject( const char* dataToInitWith,  const unsigned long& dataSize, const unsigned long& dataType )
{
	this->m_dataSize = dataSize;
	this->m_rawData = new char[ m_dataSize ];
	strncpy( m_rawData, dataToInitWith, m_dataSize );
	
	this->init();

	this->addSupportedDataType( dataType );
}


ClipboardDataObject::~ClipboardDataObject()
{
	delete[] this->m_rawData;
	for ( std::vector<DataType*>::iterator it = m_types.begin(); it != m_types.end(); it++ ){
		delete (*it);		
	}
	m_types.clear();
}

void ClipboardDataObject::init()
{

}

void ClipboardDataObject::addSupportedDataType( const unsigned long & dataType )
{
	this->m_types.push_back( new DataType( dataType ) );	
}
	
bool ClipboardDataObject::isTypeSupported( const unsigned long & dataType )
{
	bool result = false;
	
	for (std::vector<DataType*>::iterator it = m_types.begin(); it != m_types.end(); it ++ ){
		DataType* dataTypeObj = *it;
		if ( dataType == dataTypeObj->getRawType() ){
			result = true;
			break;
		}
	}

	return result;
}

void ClipboardDataObject::saveToStream( OutputStream * stream )
{
	stream->write( m_rawData, m_dataSize );
}

void ClipboardDataObject::loadFromStream( InputStream * stream )
{
	delete[]m_rawData;
	m_rawData = new char[m_dataSize];
	stream->read( m_rawData, m_dataSize );
}

Enumerator<DataType*> * ClipboardDataObject::getSupportedDataTypes()
{
	m_typesContainer.initContainer( m_types );
	return m_typesContainer.getEnumerator();	
}