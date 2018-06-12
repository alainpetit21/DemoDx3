#ifndef _RES_MANAGER_H_
#define _RES_MANAGER_H_

enum{
	RMI_IMAGE	= 0	,
	RMI_PIXEL		,
	RMI_VERTEX		,
	RMI_VERTEX2		,
	RMI_TEXCOORD2	,
	RMI_TRIANGLES2	,
	RMI_MESH_MD2	,
	RMI_MESH_3DS	,
};

void	RM_Init(void);
void	RM_Quit(void);
void	RM_Allocate(int wichBuffer, int size);
void*	RM_GetBufferStart(int wichBuffer);
void**	RM_GetBufferCur(int wichBuffer);

#define CUR_IMAGE		(IMAGE**)RM_GetBufferCur(RMI_IMAGE)
#define CUR_PIXEL		(ushort**)RM_GetBufferCur(RMI_PIXEL)
#define CUR_VERTEX		(VERTEX**)RM_GetBufferCur(RMI_VERTEX)
#define CUR_VERTEX2		(VERTEX2**)RM_GetBufferCur(RMI_VERTEX2)
#define CUR_TEXCOORD2	(TEXCOORD2**)RM_GetBufferCur(RMI_TEXCOORD2)
#define CUR_TRIANGLES2	(TRIANGLES2**)RM_GetBufferCur(RMI_TRIANGLES2)
#define CUR_MESH_MD2	(MESH_MD2**)RM_GetBufferCur(RMI_MESH_MD2)
#define CUR_MESH_3DS	(MESH_3DS**)RM_GetBufferCur(RMI_MESH_3DS)

#define AR_IMAGE		((IMAGE*)RM_GetBufferStart(RMI_IMAGE))
#define AR_PIXEL		((ushort*)RM_GetBufferStart(RMI_PIXEL))
#define AR_VERTEX		((VERTEX*)RM_GetBufferStart(RMI_VERTEX))
#define AR_VERTEX2		((VERTEX2*)RM_GetBufferStart(RMI_VERTEX2))
#define AR_TEXCOORD2	((TEXCOORD2*)RM_GetBufferStart(RMI_TEXCOORD2))
#define AR_TRIANGLES2	((TRIANGLES2*)RM_GetBufferStart(RMI_TRIANGLES2))
#define AR_MESH_MD2		((MESH_MD2*)RM_GetBufferStart(RMI_MESH_MD2))
#define AR_MESH_3DS		((MESH_3DS*)RM_GetBufferStart(RMI_MESH_3DS))
#endif /*_RES_MANAGER_H_*/