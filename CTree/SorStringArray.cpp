// SorStringArray.cpp: implementation of the CSorStringArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CTree.h"
#include "SorStringArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSorStringArray::CSorStringArray()
{
	
}

CSorStringArray::~CSorStringArray()
{

}
void CSorStringArray::sort()
{
       BOOL bNotDone = TRUE;
       while(bNotDone)
       {
              bNotDone = FALSE;
              for(int pos = 0; pos < GetUpperBound(); pos++)//对CString数组进行排序
              {
                     bNotDone |= ComPareAndSwap(pos);
 
              }
       }
      
}
 
BOOL CSorStringArray::ComPareAndSwap(int pos)//比较CString数组中两个字符串的大小，按从小到大排序
{
       CString temp;
       int posFirst = pos;
       int posNext = pos +1;
       if (GetAt(pos).CompareNoCase(GetAt(posNext)) >0)//先比较前后两个字符的大小，如果前者大于后者，则进行调换位置
       {
              temp = GetAt(pos);
              SetAt(posFirst, GetAt(posNext));
              SetAt(posNext,temp);
 
              return TRUE;
       }
       return FALSE;
 
}
