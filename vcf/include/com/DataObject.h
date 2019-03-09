/* Generated by Together */

#pragma warning (disable : 4786) //vector warnings about string too long...

#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include "COMObject.h"
#include "DataObjectPeer.h"
#include "ClipboardDataObject.h"

#include "EnumObject.h"

#include <vector>
#include <map>


namespace VCFCOM{
/**
 * base implementation of IDataObject 
 */

class DataRendering : public VCF::Object{
public:
	DataRendering( FORMATETC * formatETC, STGMEDIUM * stgMedium, IUnknown* newStorageOwner );
	virtual ~DataRendering();

	FORMATETC       m_formatETC;             
    STGMEDIUM       m_storage;            
    IUnknown*       m_owner;     
	
	virtual VCF::String toString(){
		VCF::String result;
		result = format( "DataRendering @ %p \n", this );
		switch ( m_formatETC.cfFormat ){
			case CF_BITMAP:{
				result += "m_formatETC.cfFormat = CF_BITMAP";		
			}
			break;
			
			case CF_DIB:{
				result += "m_formatETC.cfFormat = CF_DIB";		
			}
			break;

			case CF_DIF:{
				result += "m_formatETC.cfFormat = CF_DIF";		
			}
			break;

			case CF_HDROP:{
				result += "m_formatETC.cfFormat = CF_HDROP";		
			}
			break;

			case CF_METAFILEPICT:{
				result += "m_formatETC.cfFormat = CF_METAFILEPICT";		
			}
			break;

			case CF_OEMTEXT:{
				result += "m_formatETC.cfFormat = CF_OEMTEXT";		
			}
			break;

			case CF_TEXT:{
				result += "m_formatETC.cfFormat = CF_TEXT";		
			}
			break;
			
			case CF_WAVE:{
				result += "m_formatETC.cfFormat = CF_WAVE";		
			}
			break;
			
			case CF_TIFF:{
				result += "m_formatETC.cfFormat = CF_TIFF";		
			}
			break;
		};		
		return result;
	};

	bool operator == ( const DataRendering& dataRenderToCompare )const
	{	
		bool result = false;
		
		result = ( (this->m_formatETC.cfFormat == dataRenderToCompare.m_formatETC.cfFormat) &&
		           (this->m_formatETC.dwAspect == dataRenderToCompare.m_formatETC.dwAspect) &&		
				   (this->m_formatETC.tymed == dataRenderToCompare.m_formatETC.tymed) );

		return result;
	};

	bool operator == ( const FORMATETC& formatETCToCompare )const
	{	
		bool result = false;
		
		result = ( (this->m_formatETC.cfFormat == formatETCToCompare.cfFormat) &&
		           (this->m_formatETC.dwAspect == formatETCToCompare.dwAspect) &&		
				   (this->m_formatETC.tymed == formatETCToCompare.tymed) );

		return result;
	};
};	

class DataObject : public IDataObject, public COMObject, public VCF::DataObjectPeer {
public:    

   	DataObject();
	virtual ~DataObject();

	/**
     * Adds a new data type that the dataobject supports. 
     */
	virtual void addSupportedData( const unsigned long & dataType, VCF::ClipboardDataObject* data );  
	
	virtual VCF::ClipboardDataObject* getSupportedData( const unsigned long & dataType );

    /**
     * is the data type passed in supported by the data object ?
     */
    virtual bool isTypeSupported(const unsigned long & dataType );    
	
	virtual bool supportsInterface( REFIID riid, void** object );

	void clearRenderings();

	
	COMOBJ_QUERY_INTERFACE_IMPL;

	COMOBJ_ADD_REF_IMPL;

	COMOBJ_RELEASE_IMPL;


	//IDropSource
	STDMETHODIMP GetData( FORMATETC * formatETC, STGMEDIUM * stgMedium );	
	STDMETHODIMP GetDataHere( FORMATETC * formatETC, STGMEDIUM * stgMedium );
	STDMETHODIMP QueryGetData( FORMATETC * formatETC );
	STDMETHODIMP GetCanonicalFormatEtc( FORMATETC * formatETCIn, FORMATETC * formatETCOut );	
	STDMETHODIMP SetData( FORMATETC * formatETC, STGMEDIUM * stgMedium, BOOL releaseData );
	STDMETHODIMP EnumFormatEtc( DWORD dwDirection, IEnumFORMATETC ** ppenumFormatetc );
	STDMETHODIMP DAdvise( FORMATETC * formatETC, DWORD advf, IAdviseSink * pAdvSink,  DWORD * pdwConnection );
	STDMETHODIMP DUnadvise( DWORD dwConnection );
	STDMETHODIMP EnumDAdvise( IEnumSTATDATA ** ppenumAdvise );
 
private:
	DataRendering* findDataRenderingForType( FORMATETC* formatETC );

	UINT translateFrameworkFormat( const unsigned long& dataType );
	FORMATETC translateFrameworkFormatToFormatETC( const unsigned long& dataType );
	VCF::String translateClipboardFmt( const UINT& fmtType );

	std::vector< DataRendering* > m_renderings;
	std::map<unsigned long, VCF::ClipboardDataObject*> m_dataMap;
};


class EnumFormatETC : public IEnumFORMATETC, public EnumObject<FORMATETC> {
public:

	EnumFormatETC():
		EnumObject<FORMATETC>(){};

	EnumFormatETC( const EnumFormatETC& enumObj ):
		EnumObject<FORMATETC>( enumObj ){};

	virtual ~EnumFormatETC(){};
	
	COMOBJ_QUERY_INTERFACE_IMPL;

	COMOBJ_ADD_REF_IMPL;

	COMOBJ_RELEASE_IMPL;	

	STDMETHODIMP Next( ULONG elementsRequested, FORMATETC *elementList, ULONG *elementsFetched ){
		return EnumObject<FORMATETC>::Next( elementsRequested, elementList, elementsFetched );
	};

	STDMETHODIMP Skip( ULONG elementsToSkip ){
		return EnumObject<FORMATETC>::Skip( elementsToSkip );
	};

	STDMETHODIMP Reset(void){
		return EnumObject<FORMATETC>::Reset();
	};

	STDMETHODIMP Clone( IEnumFORMATETC** enumFmtEtc ){
		EnumObject<FORMATETC>* enumFmt = NULL;
		//HRESULT result = EnumObject<FORMATETC>::Clone( &enumFmt );
		enumFmt = new EnumFormatETC( *this );
		*enumFmtEtc = (IEnumFORMATETC*)(COMObject*)enumFmt;
		return NOERROR;//result;//E_NOTIMPL;
	};


	virtual bool supportsInterface( REFIID riid, void** object ){
		bool result = 0 != (IID_IEnumFORMATETC == riid);
		if ( true == result ){
			*object = (IEnumFORMATETC*)(COMObject*)this;
		}
		return 	result;
	};

	
};


};
#endif //DATAOBJECT_HCT_H