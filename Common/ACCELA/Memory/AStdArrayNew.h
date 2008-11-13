//**************************************************************************************// Filename:	AStdArrayNew.h//				Part of Contextual Menu Workshop by Abracode Inc.//				http://free.abracode.com/cmworkshop/// Copyright � 2003 Abracode, Inc.  All rights reserved.//// Description:	Extension to David Catmull's ACCELA Mac toolbox C++ wrapper library//**************************************************************************************#pragma once#include "AMemoryCommon.h"#include "CThrownResult.h"#include <string.h>template <class T>class AStdArrayNew{public:		AStdArrayNew()			: mObject(NULL), mIsOwner(kMemObj_NotOwned) {}		AStdArrayNew(T *inObj, EMemObjOwnershipType inIsOwner = kMemObj_Owned)			: mObject(inObj), mIsOwner(inIsOwner) { }				//copy constructor - only shallow copy is allowed here		//the object is detached from the original		AStdArrayNew(const AStdArrayNew& inOrig)			: mObject(NULL), mIsOwner(kMemObj_NotOwned)		{			EMemObjOwnershipType isOwner = inOrig.mIsOwner;			Reset(inOrig.Detach(), isOwner );		}	//CAUTION: the size is interpreted as a count of T objects		AStdArrayNew(SInt32 inSize, EMemObjClearOption inClearOption = kMemObj_DontClearMemory)			: mObject(NULL), mIsOwner(kMemObj_NotOwned)			{				mObject = new T[inSize];				if(inClearOption == kMemObj_ClearMemory)				{					::memset(mObject, 0, inSize*sizeof(T) );				}			}		virtual		~AStdArrayNew() { Dispose(); }		//object assignment as a shallow copy with ownership change	AStdArrayNew&		operator=(				const AStdArrayNew& inObj)		{			EMemObjOwnershipType isOwner = inObj.mIsOwner;			Reset(inObj.Detach(), isOwner );			return *this;		}		//plain pointer assignment with ownership taking, no copy		//inObj must be allocated with "new []"	AStdArrayNew&		operator=(				const T* inObj)		{			Reset(inObj, kMemObj_Owned);			return *this;		}	T *		Get() const		{			return mObject;		}		operator T*() const		{			return mObject;		}			T&		operator [] (UInt32 index) const		{			return mObject[index];		}	T*		operator -> () const		{			return mObject;		}	T *		Detach() const		{			mIsOwner = kMemObj_NotOwned;			return mObject;		}	void		Reset(				T *inObject,				EMemObjOwnershipType inIsOwner = kMemObj_Owned)		{			if ((mIsOwner == kMemObj_Owned) && (mObject != NULL) && (inObject != mObject)) DisposeSelf();			mObject = inObject;			mIsOwner = inIsOwner;		}	void		Dispose()		{			if (mObject != NULL)			{				if(mIsOwner == kMemObj_Owned) DisposeSelf();				mObject = NULL;			}			mIsOwner = kMemObj_NotOwned;		}	static void		DisposeProc(void *inObj)		{			if(inObj != NULL)			{				T** objPtr = reinterpret_cast<T **>(inObj);				delete [] *objPtr;				*objPtr = NULL;			}		}protected:	void		DisposeSelf()		{			delete [] mObject;		}protected:	T *mObject;	mutable EMemObjOwnershipType mIsOwner;};