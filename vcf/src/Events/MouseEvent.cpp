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


using namespace VCF;


MouseEvent::MouseEvent( Object* source ):
	Event( source )
{
	this->init();
}

MouseEvent::MouseEvent( Object* source, const unsigned long& eventType ):
	Event( source )
{
	this->init();
	this->setType( eventType );
}
	
MouseEvent::MouseEvent( Object* source, const unsigned long& eventType, const unsigned long& buttonMask, 
					    const unsigned long& keyMask, Point* point ):
	Event( source )
{
	this->init();
	this->setType( eventType );
	this->m_buttonMask = buttonMask;
	this->m_keyMask = keyMask;
	this->m_point = *point;	
}

void MouseEvent::init()
{
	m_point.m_x = 0.0;
	m_point.m_y = 0.0;

	this->m_keyMask = 0;
	this->m_buttonMask = 0;
}

unsigned long MouseEvent::getButtonMask()
{
	return m_buttonMask;
}

unsigned long MouseEvent::getKeyMask()
{
	return m_keyMask;
}

Point* MouseEvent::getPoint()
{
	return &this->m_point;
}

void MouseEvent::setPoint( Point* point )
{
	this->m_point.m_x = point->m_x;
	this->m_point.m_y = point->m_y;
}

bool MouseEvent::hasLeftButton()
{
	return ( MOUSE_LEFT_BUTTON & this->m_buttonMask ) != 0;
}

bool MouseEvent::hasMiddleButton()
{
	return ( MOUSE_MIDDLE_BUTTON & this->m_buttonMask ) != 0;
}

bool MouseEvent::hasRightButton()
{
	return ( MOUSE_RIGHT_BUTTON & this->m_buttonMask ) != 0;
}

bool MouseEvent::hasShiftKey()
{
	return ( KEY_SHIFT & this->m_keyMask ) != 0;
}

bool MouseEvent::hasAltKey()
{
	return ( KEY_ALT & this->m_keyMask ) != 0;
}

bool MouseEvent::hasControlKey()
{
	return ( KEY_CTRL & this->m_keyMask ) != 0;
}