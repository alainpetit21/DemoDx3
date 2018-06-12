#ifndef _3D_H_
#define _3D_H_
/*=====================*/
/*=====================*/
#include "types.h"
/*=====================*/
/*=====================*/
typedef struct tagVX{
  i32	orig[3]
  ,	rot[3]	
  ,	nor[3]
  ,	sX
  ,	sY							
  ,	m_U1, m_V1			
  ,	m_R, m_G, m_B;	
}VX;
/*=====================*/
typedef struct tagVX2{
  i32	orig[3]
  ,	rot[3]	
  ,	nor[3]
  ,	sX
  ,	sY							
  ,	m_R, m_G, m_B;	
}VX2;
/*=====================*/
typedef struct tag_TC2{
  i32		m_U1, m_V1;			
}TC2;
/*=====================*/
typedef struct tagTRI2
{
  i32	idxVertex[3]
  ,	idxTexCoor[3];
}TRI2;
/*=====================*/
/*=====================*/
#endif //_3D_H_




