//**************************************************************************************// Filename:	AStdNew.h//				Part of Contextual Menu Workshop by Abracode Inc.//				http://free.abracode.com/cmworkshop/// Copyright � 2003 Abracode, Inc.  All rights reserved.//// Description:	Extension to David Catmull's ACCELA Mac toolbox C++ wrapper library//**************************************************************************************#pragma once#include "AMemoryCommon.h"#include "CThrownResult.h"template <class T>class AStdNew{public:		AStdNew()			: mObject(NULL), mIsOwner(kMemObj_NotOwned) {}		AStdNew(T *inObj, EMemObjOwnershipType inIsOwner = kMemObj_Owned)			: mObject(inObj), mIsOwner(inIsOwner) { }				//copy constructor - only shallow copy is allowed here		//the object is detached from the original		AStdNew(const AStdNew& inOrig)			: mObject(NULL), mIsOwner(kMemObj_NotOwned)		{			EMemObjOwnershipType isOwner = inOrig.mIsOwner;			Reset(inOrig.Detach(), isOwner );		}	virtual		~AStdNew() { Dispose(); }		//object assignment as a shallow copy with ownership change	AStdNew&		operator=(				const AStdNew& inObj)		{			EMemObjOwnershipType isOwner = inObj.mIsOwner;			Reset(inObj.Detach(), isOwner );			return *this;		}		//plain pointer assignment with ownership taking, no copy		//inObj must be allocated with "new"	AStdNew&		operator=(				const T* inObj)		{			Reset(inObj, kMemObj_Owned);			return *this;		}	T *		Get() const		{			return mObject;		}		operator T*() const		{			return mObject;		}			T&		operator * () const		{			return *mObject;		}	T*		operator -> () const		{			return mObject;		}	T *		Detach() const		{			mIsOwner = kMemObj_NotOwned;			return mObject;		}	void		Reset(				T *inObject,				EMemObjOwnershipType inIsOwner = kMemObj_Owned)		{			if ((mIsOwner == kMemObj_Owned) && (mObject != NULL) && (inObject != mObject)) DisposeSelf();			mObject = inObject;			mIsOwner = inIsOwner;		}	void		Dispose()		{			if (mObject != NULL)			{				if(mIsOwner == kMemObj_Owned) DisposeSelf();				mObject = NULL;			}			mIsOwner = kMemObj_NotOwned;		}	static void		DisposeProc(void *inObj)		{			if(inObj != NULL)			{				T** objPtr = reinterpret_cast<T **>(inObj);				delete *objPtr;				*objPtr = NULL;			}		}protected:	void		DisposeSelf()		{			delete mObject;		}protected:	T *mObject;	mutable EMemObjOwnershipType mIsOwner;};