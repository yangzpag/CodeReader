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


#ifndef PANEL_H
#define PANEL_H



namespace VCF{

#define PANEL_CLASSID		"ED88C0A0-26AB-11d4-B539-00C04F0196DA"	

class APPKIT_API Panel :  public ControlContainer{
public:
	BEGIN_CLASSINFO(Panel, "VCF::Panel", "VCF::ControlContainer", PANEL_CLASSID )
	END_CLASSINFO(Panel)

	Panel();

	virtual ~Panel();

    virtual void paint( GraphicsContext * context );

    virtual void setCaption( const String& caption );

    virtual String getCaption();

	void init();	

	virtual String toString();

	void setShowBorder( const bool& showBorder );

	bool getShowBorder() {
		return m_showBorder;
	}
private:    
    String m_caption;
	bool m_showBorder;

	Border* m_basicBorder;
};

};
#endif //PANEL_H