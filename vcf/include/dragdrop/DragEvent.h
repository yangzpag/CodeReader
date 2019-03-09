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


#ifndef DRAGEVENT_H
#define DRAGEVENT_H


namespace VCF{

enum DragActionType{
	DRAG_ACTION_COPY=0,
	DRAG_ACTION_MOVE,
	DRAG_ACTION_LINK
};

class APPKIT_API DragEvent : public Event {
public:
	DragEvent( Object* source, VCF::ClipboardDataObject* data ):
		Event( source ){
		m_data = data;
	};
	
	DragEvent( Object* source, VCF::ClipboardDataObject* data, 
		       const unsigned long& keyMask, const unsigned long& buttonMask,
			   const DragActionType& action ):
		Event( source ){
		m_data = data;
		m_keyMask = keyMask;
		m_buttonMask = buttonMask;
		m_action = action;
	};

	virtual ~DragEvent(){};

	VCF::ClipboardDataObject* getDataObject();
    
	unsigned long getButtonMask();
	void setButtonMask( const unsigned long& buttonMask ); 

    unsigned long getKeyMask();
	void setKeyMask( const unsigned long& keyMask ); 
	
	/**
	*
	*/
	void setActionType( const DragActionType& action );
	/**
	*get the type of action the event represents
	*/
	DragActionType getAction();

private:    
    VCF::ClipboardDataObject* m_data;
	unsigned long m_keyMask;
    unsigned long m_buttonMask;
	DragActionType m_action;
};

}
#endif //DRAGEVENT_H