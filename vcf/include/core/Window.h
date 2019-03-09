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


#ifndef WINDOW_H
#define WINDOW_H



namespace VCF {

class WindowPeer;


#define WINDOW_CLASSID				"ED88C0A1-26AB-11d4-B539-00C04F0196DA"


/**
 * A frame with min. max, restore, and system buttons. 
 * Has a caption of the standard height. 
 */
class APPKIT_API Window : public Frame {
public:

	BEGIN_CLASSINFO(Window, "VCF::Window", "VCF::Frame", WINDOW_CLASSID )
	OBJECT_PROPERTY( MenuBar, "menuBar", Window::getMenuBar, Window::setMenuBar );	
	EVENT("VCF::WindowEventHandler", "WindowEvent", "WindowClose" )
	EVENT("VCF::WindowEventHandler", "WindowEvent", "WindowRestore" )
	EVENT("VCF::WindowEventHandler", "WindowEvent", "WindowMaximize" )
	EVENT("VCF::WindowEventHandler", "WindowEvent", "WindowMinimize" )
	END_CLASSINFO(Window)

	Window();
	virtual ~Window();

	EVENT_HANDLER_LIST(WindowClose)
	EVENT_HANDLER_LIST(WindowRestore)
	EVENT_HANDLER_LIST(WindowMaximize)
	EVENT_HANDLER_LIST(WindowMinimize)
	
	ADD_EVENT(WindowClose)
	ADD_EVENT(WindowRestore)
	ADD_EVENT(WindowMaximize)
	ADD_EVENT(WindowMinimize)

	REMOVE_EVENT(WindowClose)
	REMOVE_EVENT(WindowRestore)
	REMOVE_EVENT(WindowMaximize)
	REMOVE_EVENT(WindowMinimize)
	
	FIRE_EVENT(WindowClose,WindowEvent)
	FIRE_EVENT(WindowRestore,WindowEvent)
	FIRE_EVENT(WindowMaximize,WindowEvent)
	FIRE_EVENT(WindowMinimize,WindowEvent)

	virtual void setCaption( const String& caption );

	virtual void paint(GraphicsContext * context);

	/**
	*overridden to take into account client bounds
	**/
	virtual void resizeChildren();

	virtual Rect* getClientBounds();

	virtual void  setClientBounds( Rect* bounds );

	MenuBar* getMenuBar();

	void setMenuBar( MenuBar* menuBar );

	virtual void beforeDestroy( ComponentEvent* event );

	virtual void close();

	virtual void setFrameStyle( const FrameStyleType& frameStyle );

	virtual void setFrameTopmost( const bool& isTopmost );

	virtual double getPreferredWidth();

	virtual double getPreferredHeight();
private:    
    WindowPeer * m_windowPeer;	
	MenuBar* m_menuBar;
};

};
#endif //WINDOW_H_H