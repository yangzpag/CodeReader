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


#ifndef LISTBOXCONTROL_H
#define LISTBOXCONTROL_H


namespace VCF{

class ListModel;

class ListItem;

class ListModelEvent;

class ListModelHandler;

#define LISTBOXCONTROL_CLASSID		"ED88C0A5-26AB-11d4-B539-00C04F0196DA"

class APPKIT_API ListBoxControl : public CustomControl {

public:
	BEGIN_CLASSINFO(ListBoxControl, "VCF::ListBoxControl", "VCF::CustomControl", LISTBOXCONTROL_CLASSID )
	PROPERTY( double, "defaultItemHeight", ListBoxControl::getDefaultItemHeight, ListBoxControl::setDefaultItemHeight, PROP_DOUBLE );
	PROPERTY( bool, "allowsMultiSelect", ListBoxControl::getAllowsMultiSelect, ListBoxControl::setAllowsMultiSelect, PROP_BOOL );
	OBJECT_PROPERTY( ListModel, "listModel", ListBoxControl::getListModel, ListBoxControl::setListModel );
	END_CLASSINFO(ListBoxControl)

	ListBoxControl();

	virtual ~ListBoxControl();

    ListModel* getListModel();

    void setListModel(ListModel * model);	

	virtual void rangeSelect( const bool & isSelected, ListItem * first, ListItem * last );

	void onListModelContentsChanged( ListModelEvent* event );

    void onItemAdded( ListModelEvent* event );

    void onItemDeleted( ListModelEvent* event );

	virtual void paint( GraphicsContext* ctx );

	virtual void mouseDown( MouseEvent* event );

	virtual void mouseMove( MouseEvent* event );

	virtual void mouseUp( MouseEvent* event );

	virtual void mouseClick( MouseEvent* event );

	virtual void mouseDblClick( MouseEvent* event );

	virtual void keyDown( KeyboardEvent* event );

	virtual void keyUp( KeyboardEvent* event );

	virtual void keyPressed( KeyboardEvent* event );

	double getDefaultItemHeight() {
		return m_defaultItemHeight;
	}

	void setDefaultItemHeight( const double& defaultItemHeight );

	bool getAllowsMultiSelect() {
		return m_allowsMultiSelect;
	}

	void setAllowsMultiSelect( const bool& allowsMultiSelect );

	Enumerator<ListItem*>* getSelectedItems();
	
	ListItem* getSelectedItem() {
		return m_singleSelectedItem;
	}

	void setSelectedItem( ListItem* selectedItem );
protected:    
	ListModel* m_listModel;
	ListModelHandler* m_modelHandler;
	double m_defaultItemHeight;
	bool m_allowsMultiSelect;
	ListItem* m_singleSelectedItem;
	std::vector<ListItem*> m_selectedItems;
	EnumeratorContainer<std::vector<ListItem*>,ListItem*> m_selectedItemsContainer;

	void paintSelectionRect( GraphicsContext* ctx, Rect* rect, ListItem* item );

	ListItem* findSingleSelectedItem( Point* pt );
};

};
#endif //LISTBOXCONTROL_H