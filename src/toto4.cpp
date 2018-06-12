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
#include "audio.h"
PROFILER_INC
PROFILER_DEC

extern IMAGE		bb;
extern IMAGE		tb;

char		texte[64];

void main(void)
{
  MSG msg;
  int rotX=0;int posX=0;
  int rotY=0;int posY=0;int posZ=450;
  int i= 100;
  int incX= 1, incY= 1;
  int posCX=0;
  int posCY=0;
  int x= 0, y=0;

  PROFILER_INIT;
  SYS_Init("Test", "TestClass", 640, 480);
  VID_Init(640, 480, 16, 0);
  AUD_Init(16, 2, 22050);
  INP_Init();
  RM_Init();

  RM_Allocate(RMI_IMAGE, 1);

  VID_LoadTGA(CUR_IMAGE, CUR_PIXEL, "Data\\cloud.tga");
  while(!INP_IsKeyDown(KEY_ANY_KEY)){
		PROFILER_BEFORE;	TRAP_MSG(msg);																PROFILER_AFTER("TRAP_MSG ", " ");
		PROFILER_BEFORE;	VID_Clear(bb, CLR_ZERO, 0);													PROFILER_AFTER("VID_Clear ", " ");
		PROFILER_BEFORE;	VID_Blt(bb, posX, posY, 256, 256, BLT_COPY, AR_IMAGE[0], 0, 0, 256, 256);	PROFILER_AFTER("VID_Blt ", " ");
		PROFILER_BEFORE;	VID_Flip();																	PROFILER_AFTER("VID_Flip ", "\n\r");
	Sleep(1);

	posX+= incX;
	posY+= incY;
	if(posX<0) incX*=-1;
	if(posX>(640-256)) incX*=-1;
	if(posY<0) incY*=-1;
	if(posY>(480-256)) incY*=-1;
  }
  RM_Quit();
  INP_Quit();
  VID_Quit();
  AUD_Quit();
  SYS_Quit("Test", "TestClass");
}
