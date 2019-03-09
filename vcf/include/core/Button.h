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

#ifndef BUTTON_H
#define BUTTON_H


namespace VCF{

class ButtonListener;

/**
*The Button interface represents a standard set of behaviours
*for any control that wishes to act like a button. Currently the 
*basic behaviour is to fire click events when the click() method 
*is invoked.
*/
class APPKIT_API Button {
public:    

	/**
	*This represents the user pressing the button,
	*which then invokes whatever command is associated
	*with the button. It should be called in the implementing
	*controls class whenever the control is "clicked" on 
	*(see Control::mouseClick() ), it can also be called 
	*programmticalyy as well.
	*/
    virtual void click() = 0;

	/**
	*Adds a new EventHandler for button click events
	*/
	virtual void addButtonClickHandler( EventHandler* handler ) = 0;

	/**
	*Removes an EventHandler for button click events
	*/
	virtual void removeButtonClickHandler( EventHandler* handler ) = 0;

};

}
#endif //BUTTON_H