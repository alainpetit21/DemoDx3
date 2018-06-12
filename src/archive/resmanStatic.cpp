#include <windows.h>
#include "3D.h"
#include "3DDisplay.h"
#include "resman.h"

IMAGE		gArImage[1]			;//= (IMAGE*)malloc(sizeof(IMAGE)*1);
ushort		gArPixel[256*256]	;//= (ushort*)malloc(sizeof(ushort)*256*256);
VERTEX		gArVertex[1]		;//
VERTEX2 	gArVertex2[100000]	;//
TEXCOORD2 	gArTexCoord[512]	;//
TRIANGLES2 	gArTriangle[1024]	;//
MESH_MD2	gArMeshMD2[1]		;//= (MESH_MD2*)malloc(sizeof(MESH_MD2)*1);
MESH_3DS	gArMesh3DS[1]		;//= (MESH_MD2*)malloc(sizeof(MESH_MD2)*1);
IMAGE		*gcurImage		= gArImage		;
ushort		*gcurPixel		= gArPixel		;
VERTEX		*gcurVertex		= gArVertex		;
VERTEX2 	*gcurVertex2	= gArVertex2	;
TEXCOORD2 	*gcurTexCoord	= gArTexCoord	;
TRIANGLES2 	*gcurTriangle	= gArTriangle	;
MESH_MD2	*gcurMeshMD2	= gArMeshMD2	;
MESH_3DS	*gcurMesh3DS	= gArMesh3DS	;

void**		gAllBuffer[]={
	(void**)&gArImage,
	(void**)&gArPixel,
	(void**)&gArVertex,
	(void**)&gArVertex2,
	(void**)&gArTexCoord,
	(void**)&gArTriangle,
	(void**)&gArMeshMD2,
	(void**)&gArMesh3DS,
};

void**		gcurPts[]={
	(void**)&gcurImage,
	(void**)&gcurPixel,
	(void**)&gcurVertex,
	(void**)&gcurVertex2,
	(void**)&gcurTexCoord,
	(void**)&gcurTriangle,
	(void**)&gcurMeshMD2,
	(void**)&gcurMesh3DS,
};

int	gsizeof[]={
	sizeof(IMAGE)		,
	sizeof(ushort)		,
	sizeof(VERTEX)		,
	sizeof(VERTEX2)		,
	sizeof(TEXCOORD2)	,
	sizeof(TRIANGLES2)	,
	sizeof(MESH_MD2)	,
	sizeof(MESH_3DS)	,
};

void 
RM_Init()
{
}

void 
RM_Quit()
{
}

void 
RM_Allocate(int wichBuffer, int size)
{
	(*gcurPts[wichBuffer])= gAllBuffer[wichBuffer];
}

void*
RM_GetBufferStart(int wichBuffer)
{
	return gAllBuffer[wichBuffer];
}

void**
RM_GetBufferCur(int wichBuffer)
{
	return gcurPts[wichBuffer];
}
