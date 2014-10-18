// SorStringArray.h: interface for the CSorStringArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SORSTRINGARRAY_H__3C954350_8EDA_4932_AE25_12050CA98D0A__INCLUDED_)
#define AFX_SORSTRINGARRAY_H__3C954350_8EDA_4932_AE25_12050CA98D0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSorStringArray : public CStringArray  
{
public:
	CSorStringArray();
	virtual ~CSorStringArray();
	BOOL ComPareAndSwap(int pos);
    void sort();
};

#endif // !defined(AFX_SORSTRINGARRAY_H__3C954350_8EDA_4932_AE25_12050CA98D0A__INCLUDED_)
