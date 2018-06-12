#include <Windows.h>
#include <memory.h>
#include <stdio.h>
#include "macros.h"
#include "graphic.h"
#include "sys.h"
#include "input.h"
#include "file.h"
#include "types.h"
#include "3DDisplay.h"
#include "mathFP.h"
#include "resman.h"
PROFILER_INC
PROFILER_DEC

extern IMAGE		bb;
extern IMAGE		tb;

extern int cX;
extern int cY;
extern int cZ;

CBMatrix	mat;
VB			vxBuffer[1];
VB*			pvxBuffer= vxBuffer;
char		texte[64];

void main(void)
{
  int run= 1;
  MSG msg;
  int rotX=0;int posX=0;
  int rotY=64;int posY=0;int posZ=142;
  int i= 100;
  int incX= 1, incY= 1;
  int posCX=0;
  int posCY=0;
  int x= 0, y=0;

  PROFILER_INIT;
  SYS_Init("Test", "TestClass", 640, 480);
  VID_Init(640, 480, 16, 0);
  INP_Init();
  V3D_Init();
  RM_Init();

  RM_Allocate(RMI_TEXTURE, 1);
  RM_Allocate(RMI_TPIXEL, 256*256);
  RM_Allocate(RMI_VERTEX, 6);

  V3D_LoadVB(&pvxBuffer, CUR_VERTEX, 6);

  vxBuffer[0].m_start[0].orig[0]= -10240*1;vxBuffer[0].m_start[0].orig[1]= -10240*1;  vxBuffer[0].m_start[0].orig[2]= 0;
  vxBuffer[0].m_start[1].orig[0]=  10240*1;vxBuffer[0].m_start[1].orig[1]= -10240*1;  vxBuffer[0].m_start[1].orig[2]= 0;
  vxBuffer[0].m_start[2].orig[0]= -10240*1;vxBuffer[0].m_start[2].orig[1]=  10240*1;  vxBuffer[0].m_start[2].orig[2]= 0;
  vxBuffer[0].m_start[3].orig[0]=  10240*1;vxBuffer[0].m_start[3].orig[1]= -10240*1;  vxBuffer[0].m_start[3].orig[2]= 0;
  vxBuffer[0].m_start[4].orig[0]=  10240*1;vxBuffer[0].m_start[4].orig[1]=  10240*1;  vxBuffer[0].m_start[4].orig[2]= 0;
  vxBuffer[0].m_start[5].orig[0]= -10240*1;vxBuffer[0].m_start[5].orig[1]=  10240*1;  vxBuffer[0].m_start[5].orig[2]= 0;

  vxBuffer[0].m_start[0].m_U1= IFP(0)	;	vxBuffer[0].m_start[0].m_V1=IFP(0);
  vxBuffer[0].m_start[1].m_U1= IFP(256)	;	vxBuffer[0].m_start[1].m_V1=IFP(0);
  vxBuffer[0].m_start[2].m_U1= IFP(0)	;	vxBuffer[0].m_start[2].m_V1=IFP(256);
  vxBuffer[0].m_start[3].m_U1= IFP(256)	;	vxBuffer[0].m_start[3].m_V1=IFP(0);
  vxBuffer[0].m_start[4].m_U1= IFP(256)	;	vxBuffer[0].m_start[4].m_V1=IFP(256);
  vxBuffer[0].m_start[5].m_U1= IFP(0)	;	vxBuffer[0].m_start[5].m_V1=IFP(256);

  VID_LoadTGATexture(CUR_TEXTURE, CUR_TPIXEL, "Data\\cloud.tga");

  V3D_SetRendererStage(RST_TEXT);
  while(!INP_IsMouseDown()){
		PROFILER_BEFORE;	TRAP_MSG(msg);										PROFILER_AFTER("TRAP_MSG ", " ");
		PROFILER_BEFORE;	VID_Clear(bb, CLR_ZERO, 0);							PROFILER_AFTER("VID_Clear ", " ");
		PROFILER_BEFORE;	V3D_Clear();										PROFILER_AFTER("V3D_Clear ", " ");

		PROFILER_BEFORE;
		for(int i= 0; i < 8; ++i){
			for(int j= 0; j < 8; ++j){
				mat.Identity();													
				cX= IFP(75-posX-(i*20));cY= IFP(75-posY-(j*20));cZ= 0;
				mat.Rotate( 0, 0, 0);										
				mat.Rotate( 32, rotY>>2, 0);										
				mat.Translate(0, 0, IFP(posZ));	
				mat.Translate(0, 0, 0);	

				V3D_ProcessVB(mat, &vxBuffer[0]);								
				V3D_DrawPrimitive(&AR_VERTEX[0], &AR_TEXTURE[0], 6);			
			}
		}
		PROFILER_AFTER("All Map ", " ");

		PROFILER_BEFORE;	if((++rotY)>=1024) rotY= 1;							PROFILER_AFTER("if ", " ");
		PROFILER_BEFORE;	V3D_Flip();											PROFILER_AFTER("V3D_Flip ", " ");
		PROFILER_BEFORE;	VID_Flip();											PROFILER_AFTER("VID_Flip ", "\n\r");
		if(INP_IsKeyDown(KEY_DOWN)){
			++posZ;
		}else if(INP_IsKeyDown(KEY_UP)){
			--posZ;
		}
	}
	RM_Quit();
	V3D_Quit();
	INP_Quit();
	VID_Quit();
	SYS_Quit("Test", "TestClass");
}

/*commctrl.lib coredll.lib */
/*  for(int i= 0; i < 256; ++i){
	  for(int i= 0; i < 256; ++i){
		  vxBuffer[0].m_start[i*6+0].orig[0]= -1024*i;vxBuffer[0].m_start[i*6+0].orig[1]= -102400*4;  vxBuffer[0].m_start[i*6+0].orig[2]= 0;
		  vxBuffer[0].m_start[i*6+1].orig[0]=  1024;vxBuffer[0].m_start[i*6+1].orig[1]= -102400*4;  vxBuffer[0].m_start[i*6+1].orig[2]= 0;
		  vxBuffer[0].m_start[i*6+2].orig[0]= -1024;vxBuffer[0].m_start[i*6+2].orig[1]=  102400*4;  vxBuffer[0].m_start[i*6+2].orig[2]= 0;
		  vxBuffer[0].m_start[i*6+3].orig[0]=  1024;vxBuffer[0].m_start[i*6+3].orig[1]= -102400*4;  vxBuffer[0].m_start[i*6+3].orig[2]= 0;
		  vxBuffer[0].m_start[i*6+4].orig[0]=  1024;vxBuffer[0].m_start[i*6+4].orig[1]=  102400*4;  vxBuffer[0].m_start[i*6+4].orig[2]= 0;
		  vxBuffer[0].m_start[i*6+5].orig[0]= -1024;vxBuffer[0].m_start[i*6+5].orig[1]=  102400*4;  vxBuffer[0].m_start[i*6+5].orig[2]= 0;
	  }
  }
*/