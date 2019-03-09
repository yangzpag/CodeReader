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

#include "GraphicsKit.h"

using namespace VCF;

AbstractImage::AbstractImage( const bool& needsMemAlloc )
{
	INIT_EVENT_HANDLER_LIST(ImageSizeChanged);

	m_imageBits = new ImageBits(0,0,needsMemAlloc);
	m_bitDepth = BD_32BP;
	m_context = NULL;
	this->m_isTransparent = false;
}

AbstractImage::~AbstractImage()
{
	delete m_context;
	delete m_imageBits;
}

void AbstractImage::setWidth(const unsigned long & width)
{
	this->m_width = width;
	this->m_imageBits->setWidth( width );
	ImageEvent event(this);
	event.setType( IMAGE_EVENT_WIDTH_CHANGED );
	event.setNewWidth( width );
	fireOnImageSizeChanged( &event );
}

unsigned long AbstractImage::getWidth()
{
	return this->m_width;
}

void AbstractImage::setHeight(const unsigned long & height){
	this->m_height = height;
	 this->m_imageBits->setHeight( height );

	ImageEvent event(this);
	event.setType( IMAGE_EVENT_HEIGHT_CHANGED );
	event.setNewHeight( height );
	fireOnImageSizeChanged( &event );
}

unsigned long AbstractImage::getHeight(){
	return this->m_height;
}

GraphicsContext* AbstractImage::getImageContext()
{
	return m_context;
}

ImageBits* AbstractImage::getImageBits()
{
	return m_imageBits;
}

ImageBitDepth AbstractImage::getBitDepth()
{
	return m_bitDepth;
}

void AbstractImage::saveToStream( OutputStream * stream )
{
	stream->write( m_bitDepth );
	stream->write( (long)m_imageBits->m_height );
	stream->write( (long)m_imageBits->m_width );		
	char* buffer = (char*)m_imageBits->m_bits;
	stream->write( buffer, m_imageBits->getSize() );
}

void AbstractImage::loadFromStream( InputStream * stream )
{
	int bitDepth;
	stream->read( bitDepth );
	m_bitDepth = (ImageBitDepth)bitDepth;
	long height = 0;
	long width = 0;
	stream->read( height );
	stream->read( width );
	this->setHeight( height );
	this->setWidth( width );
	char* buffer = (char*)m_imageBits->m_bits;
	stream->read( buffer, m_imageBits->getSize() );
}