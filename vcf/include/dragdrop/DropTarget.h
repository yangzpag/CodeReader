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


#ifndef DROPTARGET_H
#define DROPTARGET_H




namespace VCF{

class Control;

class DropTargetPeer;

class APPKIT_API DropTarget : public Object {
public:        

    void getSupportedActions();
	
    DropTarget( Control * component );

	virtual ~DropTarget();
	
	EVENT_HANDLER_LIST(DropTargetDraggingOver)
	EVENT_HANDLER_LIST(DropTargetDropped)
	EVENT_HANDLER_LIST(DropTargetLeft)
	EVENT_HANDLER_LIST(DropTargetEntered)

	ADD_EVENT(DropTargetDraggingOver)
	ADD_EVENT(DropTargetDropped)
	ADD_EVENT(DropTargetLeft)
	ADD_EVENT(DropTargetEntered)

	REMOVE_EVENT(DropTargetDraggingOver)
	REMOVE_EVENT(DropTargetDropped)
	REMOVE_EVENT(DropTargetLeft)
	REMOVE_EVENT(DropTargetEntered)

	FIRE_EVENT(DropTargetDraggingOver,DragEvent)
	FIRE_EVENT(DropTargetDropped,DropEvent)
	FIRE_EVENT(DropTargetLeft,DragEvent)
	FIRE_EVENT(DropTargetEntered,DragEvent)

	virtual void processEvents( Event* event );

	DropTargetPeer* getDropTargetPeer();

private:
	DropTargetPeer* m_dropTargetPeer;
};

};
#endif //DROPTARGET_H