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
//Enumerator.h

#ifndef ENUMERATOR_H
#define ENUMERATOR_H

#include <algorithm>


namespace VCF{
/**
 * This is a template class that provides an interface for 
 * iterating through a collection, and provides a standard set of methods. 
 * Either multiply inherited by classes that want to public expose a single set of children,
 *or as  a returned object for safe enumeration of data collections.
 */

template <class COLLECTION_TYPE> class FRAMEWORK_API Enumerator{
public:
	Enumerator(){
		m_supportsEditing = false;
	};

	virtual ~Enumerator(){};
	
	/**
	*indicates whether there are any more children to enumerate
	*through
	*@param bool specifies whether the enumeration should be forwards
	*or backwards. The default value is true for enumerating forwards.
	*@return bool true if there are any elements left to enumerate,
	*otherwise returns false.
	*/
	virtual bool hasMoreElements(const bool& backward=false)=0;
	
	/**
	*returns the next element in the enumeration. Moves the internal
	*iterator forward
	*@return COLLECTION_TYPE returns a COLLECTION_TYPE value of whatever type
	*was specified in the template argument to the Enumerator
	*/
	virtual COLLECTION_TYPE nextElement()=0;
	
	/**
	*returns the previous element in the enumeration. Moves the internal
	*iterator backward
	*@return COLLECTION_TYPE returns a COLLECTION_TYPE value of whatever type
	*was specified in the template argument to the Enumerator
	*/
	virtual COLLECTION_TYPE prevElement()=0;
	
	/**
	*Resets the Enumerator's internal iterator back to the beginning (or end, 
	*if backward is true).
	*@param bool specifies which direction to reset to
	*/
	virtual void reset(const bool& backward=false)=0;	

	/**
	*Currently not used. Will allow editing of the Enumerator in the 
	*future, in which case this will return whether or not this instance
	*of the enumerator allows adding or removing of elements
	*@return bool true if the enumerator allows editing, otherwise false.
	*/
	bool supportsEditing(){
		return m_supportsEditing;
	};
protected:
	bool m_supportsEditing;
};



/**
*EnumeratorContainer is based on some COLLECTION class that represents a collection
*class of some sort, i.e. std::vector<>, std::list, et al.
*The internal implementation counts on the collection having a common interface to 
*STL's collection classes.
*The collection must support forward and reverse iterators
*The COLLECTION type specifies the full collection associated with 
*the enumerator. FOr example, an enumerator container of Object* using 
*a std::vector as it's collection would like this:
*<pre>
*	EnumeratorContainer<std::vector<Object*>,Object*> objectVecEnumerator;
*</pre>
*The COLLECTION_TYPE represents the type of an individual element in the enumerator.
*Passing in a reference to the collection variable in the contstructor will automatically 
*set up the internal iterator, nothing further need be done. Alternatively, you may
*call the initContainer() method with a reference to the collection
*/
template <class COLLECTION, class COLLECTION_TYPE> class FRAMEWORK_API EnumeratorContainer : public Enumerator<COLLECTION_TYPE>{
public:
	
	EnumeratorContainer( COLLECTION &container ){
		m_container = &container;
		this->reset();
		m_supportsEditing = true;
	};

	EnumeratorContainer(){
		m_supportsEditing = true;
	};

	virtual ~EnumeratorContainer(){};

	/**
	*Initializes the container with a reference to an
	*existing collection
	*/
	virtual void initContainer( COLLECTION &container ){
		m_container = &container;
		this->reset();	
	};

	virtual bool hasMoreElements(const bool& backward=false){
		bool result = false;
		if ( true == backward ){
			result = m_containerIterator != m_container->begin();
		}
		else{
			result = m_containerIterator != m_container->end();
		}
		return result;
	};

	virtual COLLECTION_TYPE nextElement(){
		if (m_containerIterator != m_container->end() ){			
			return *m_containerIterator++;
		}
		else {
			return NULL;
		}
	};

	virtual COLLECTION_TYPE prevElement(){
		if (m_containerIterator != m_container->begin() ){			
			return *--m_containerIterator;
		}		
		else {
			return NULL;
		}
	};

	virtual void reset(const bool& backward=false){
		if ( true != backward ){
			m_containerIterator = m_container->begin();
		}
		else {
			m_containerIterator = m_container->end();			
		}
	};

	/**
	*returns a pointer to the Enumerator interface of this
	*container. Automatically resets the collection before 
	*returning the pointer.
	*@return Enumerator<COLLECTION_TYPE> a pointer to the 
	*collection as an Enumerator interface.
	*/
	virtual Enumerator<COLLECTION_TYPE>* getEnumerator(){
		this->reset();
		return (Enumerator<COLLECTION_TYPE>*)this;
	};
private:
	typename COLLECTION::iterator m_containerIterator;	
	COLLECTION* m_container;
};

/**
*EnumeratorMapContainer is based on some COLLECTION class that represents 
*an  associative collection of some sort, i.e. std::map<>
*The internal implementation counts on the collection having a common interface to 
*STL's collection classes.
*The collection must support forward and reverse iterators
*The COLLECTION type specifies the full collection associated with 
*the enumerator. FOr example, an enumerator container of Object* using 
*a std::map as it's collection would like this:
*<pre>
*	EnumeratorMapContainer<std::map<String,Object*>,Object*> objectMapEnumerator;
*</pre>
*The COLLECTION_TYPE represents the type of an individual element in the enumerator.
*In EnumeratorMapContainer the enumeration will only return the value of the maps
*pair, not the key.
*/
template <class COLLECTION, class COLLECTION_TYPE> class FRAMEWORK_API EnumeratorMapContainer : public Enumerator<COLLECTION_TYPE>{
public:
	EnumeratorMapContainer( COLLECTION &container ){
		m_container = &container;
		this->reset();
	};

	EnumeratorMapContainer(){};

	virtual ~EnumeratorMapContainer(){};

	virtual void initContainer( COLLECTION &container ){
		m_container = &container;
		this->reset();	
	};

	virtual Enumerator<COLLECTION_TYPE>* getEnumerator(){
		this->reset();
		return (Enumerator<COLLECTION_TYPE>*)this;
	};

	virtual bool hasMoreElements(const bool& backward=false){
		bool result = false;
		if ( true == backward ){
			result = m_containerIterator != m_container->begin();
		}
		else{
			result = m_containerIterator != m_container->end();
		}
		return result;
	};

	virtual COLLECTION_TYPE nextElement(){
		if (m_containerIterator != m_container->end() ){
			COLLECTION_TYPE result = m_containerIterator->second;
			m_containerIterator ++;
			return result;
		}
		else {
			return NULL;
		}
	};

	virtual COLLECTION_TYPE prevElement(){
		if (m_containerIterator != m_container->begin() ){
			COLLECTION_TYPE result = m_containerIterator->second;
			m_containerIterator --;
			return result;
		}
		else {
			return NULL;
		}
	};

	virtual void reset(const bool& backward=false){
		if ( true != backward ){
			m_containerIterator = m_container->begin();
		}
		else {
			m_containerIterator = (m_container->end());			
		}
	};

private:
	typename COLLECTION::iterator m_containerIterator;	
	COLLECTION* m_container;
};


};

#endif //ENUMERATOR_H
