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

#ifndef TOOLBAR_H
#define TOOLBAR_H


namespace VCF{

class ToolbarButton;

class ToolbarDock;

#define TOOLBAR_CLASSID		"D8B85915-BCE1-44e3-8FBB-3B43427F99F1"

/**
 *a floating frame that remains top level, has a close button, 
 *and a caption height that is shorter than normal. 
 */
class APPKIT_API Toolbar : public CustomControl, public AbstractContainer {
public:
	BEGIN_CLASSINFO(Toolbar, "VCF::Toolbar", "VCF::CustomControl", TOOLBAR_CLASSID);
	OBJECT_PROPERTY( ToolbarDock, "dock", Toolbar::getDock, Toolbar::setDock );
	PROPERTY( ulong32, "dockRow", Toolbar::getDockRow, Toolbar::setDockRow, PROP_ULONG );	
	PROPERTY( bool, "handleVisible", Toolbar::isHandleVisible, Toolbar::setHandleVisible, PROP_BOOL );	
	END_CLASSINFO(Toolbar);

	Toolbar();

	virtual ~Toolbar();

	void init();

	virtual void setBounds( Rect* rect, const bool& anchorDeltasNeedUpdating=true );

	ToolbarDock* getDock();

	void setDock( ToolbarDock* dock );

	ulong32 getDockRow();

	void setDockRow( const ulong32& dockRow );

	bool isDocked();
	
	virtual void paint( GraphicsContext* context );

	bool isHandleVisible();

	void setHandleVisible( const bool& handleVisible );	

	virtual void addButton( ToolbarButton* button );

	virtual void removeButton( ToolbarButton* button );

	virtual void resizeChildren();

	virtual void add( Control* child );

	virtual void mouseDown( MouseEvent* event );

	virtual void mouseMove( MouseEvent* event );

	virtual void mouseUp( MouseEvent* event );
protected:
	void paintHandle( GraphicsContext* context );
	Rect m_buttonsClientRect; //remaing area for buttons to paint themselves
	Rect m_gripperHandleRect;
	int m_gripperWidth;
	void dockChanged( ToolbarDock* oldDock );

	void gripperHandleMouseMove( MouseEvent* event );
private:
	std::vector<ToolbarButton*> m_toolbarBtns;
	bool m_isDocked;
	bool m_isHandleVisible;
	ToolbarDock* m_dock;
	ulong32 m_dockRow;
	bool m_toolbarIsDragging;
	Rect m_draggingOutlineRect;
	Point m_dragPt;
public:
	/**
	*inner class used by the Toolbar to create a Floating 
	*toolbar window when the Toolbar is dragged out of it's dock.
	*/
	class FloatingToolbar : public Window {
	public:
		FloatingToolbar();

		virtual ~FloatingToolbar();
	protected:
	private:
	};

};

};
#endif //TOOLBAR_H