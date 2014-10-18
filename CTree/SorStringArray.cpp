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
              for(int pos = 0; pos < GetUpperBound(); pos++)//��CString�����������
              {
                     bNotDone |= ComPareAndSwap(pos);
 
              }
       }
      
}
 
BOOL CSorStringArray::ComPareAndSwap(int pos)//�Ƚ�CString�����������ַ����Ĵ�С������С��������
{
       CString temp;
       int posFirst = pos;
       int posNext = pos +1;
       if (GetAt(pos).CompareNoCase(GetAt(posNext)) >0)//�ȱȽ�ǰ�������ַ��Ĵ�С�����ǰ�ߴ��ں��ߣ�����е���λ��
       {
              temp = GetAt(pos);
              SetAt(posFirst, GetAt(posNext));
              SetAt(posNext,temp);
 
              return TRUE;
       }
       return FALSE;
 
}
