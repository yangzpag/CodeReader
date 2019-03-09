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

#ifndef MENUITEM_H
#define MENUITEM_H




namespace VCF 
{

class MenuItemPeer;

class MenuItemListener;

class Menu;

#define MENUITEM_CLASSID		"1E8CBE22-2915-11d4-8E88-00207811CFAB"

class APPKIT_API MenuItem : public Item {
public:

	BEGIN_ABSTRACT_CLASSINFO(MenuItem, "VCF::MenuItem", "VCF::Item", MENUITEM_CLASSID)
	EVENT( "VCF::MenuItemEventHandler", "VCF::MenuItemEvent", "MenuItemClicked" )
	EVENT( "VCF::MenuItemEventHandler", "VCF::MenuItemEvent", "MenuItemUpdate" )
	END_CLASSINFO(MenuItem)

	MenuItem(){
		
	};

	virtual ~MenuItem(){};

	virtual void addMenuItemClickedHandler( EventHandler* handler ) = 0;

	virtual void removeMenuItemClickedHandler( EventHandler* handler ) = 0;

	virtual void addMenuItemUpdateHandler( EventHandler* handler ) = 0;

	virtual void removeMenuItemUpdateHandler( EventHandler* handler ) = 0;	

	virtual Enumerator<MenuItem*>* getChildren() = 0;	

	virtual void addChild( MenuItem* child ) = 0;

	virtual void insertChild( const unsigned long& index, MenuItem* child ) = 0;
	
	virtual void deleteChild( MenuItem* child ) = 0;

	virtual void deleteChild( const unsigned long& index ) = 0;

	virtual void clearChildren() = 0;

	virtual bool isChecked() = 0;

	virtual void setChecked( const bool& checked ) = 0;

	virtual bool hasParent() = 0;

	virtual bool hasChildren() = 0;

	/**
	*returns the owner of the menu item. This generally
	is either a MenuBar or a PopupMenu
	*/
	virtual Menu* getMenuOwner() = 0;

	/**
	*sets the Owner for the MenuItem and for all it's children as 
	*well
	*/
	virtual void setMenuOwner( Menu* menuOwner ) = 0;

	virtual MenuItem* getParent() = 0;

	virtual void setParent( MenuItem* parent ) = 0;

	virtual MenuItem* getChildAt( const unsigned long& index ) = 0;

	virtual bool isEnabled() = 0;

	virtual void setEnabled( const bool& enabled ) = 0;

	virtual bool isVisible() = 0;

	virtual void setVisible( const bool& visible ) = 0;

	virtual bool getRadioItem() = 0;

	virtual void setRadioItem( const bool& value ) = 0;

	virtual void setCaption( const String& caption ) = 0;
	
	virtual String getCaption() = 0;

	virtual MenuItemPeer* getPeer() = 0;

	virtual bool isSeparator() = 0;

	virtual void setSeparator( const bool& separator ) = 0;
	
	virtual void click() = 0;

	virtual void update() = 0;
};

};
#endif //MENUITEM_H
