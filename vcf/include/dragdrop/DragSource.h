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

#ifndef DRAGSOURCE_H
#define DRAGSOURCE_H


namespace VCF{


class DragDropPeer;

class ClipboardDataObject;


class APPKIT_API DragSource : public Object {

public:
	DragSource();
	virtual ~DragSource();    	

	void startDragDrop( ClipboardDataObject* data );

    void copyDataToClipboard();

	void setActionType( const DragActionType& actionType );

	DragActionType getActionType();

	EVENT_HANDLER_LIST(SourceBegin)
	EVENT_HANDLER_LIST(SourceDropped)
	EVENT_HANDLER_LIST(SourceEnd)
	EVENT_HANDLER_LIST(SourceGiveFeedback)
	EVENT_HANDLER_LIST(SourceCanContinueDragOp)

	ADD_EVENT(SourceBegin)
	ADD_EVENT(SourceDropped)
	ADD_EVENT(SourceEnd)
	ADD_EVENT(SourceGiveFeedback)
	ADD_EVENT(SourceCanContinueDragOp)

	REMOVE_EVENT(SourceBegin)
	REMOVE_EVENT(SourceDropped)
	REMOVE_EVENT(SourceEnd)
	REMOVE_EVENT(SourceGiveFeedback)
	REMOVE_EVENT(SourceCanContinueDragOp)
	
	FIRE_EVENT(SourceBegin,DragEvent)
	FIRE_EVENT(SourceDropped,DragEvent)
	FIRE_EVENT(SourceEnd,DragEvent)
	FIRE_EVENT(SourceGiveFeedback,DragEvent)
	FIRE_EVENT(SourceCanContinueDragOp,DragEvent)	
	
protected:    
    DragActionType m_actionType;
    DragDropPeer * m_dragDropPeer;

    ClipboardDataObject * m_clipboardDataObject;
};

};



#endif //DRAGSOURCE_H