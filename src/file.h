#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_
#pragma message("_FILE_SYSTEM_H_")
/*=============================*/
/*=============================*/
#include "types.h"
/*=============================*/
/*=============================*/
#ifdef _POCKET_PC
typedef HANDLE		PTFILE;
#define OPT_READ	GENERIC_READ
#define OPT_WRITE	GENERIC_WRITE
#define FRM_BEGIN	FILE_BEGIN
#define FRM_CURRENT	FILE_CURRENT
#define FRM_END		FILE_END
#elif defined _WIN32
typedef HANDLE		PTFILE;
#define OPT_READ	GENERIC_READ
#define OPT_WRITE	GENERIC_WRITE
#define FRM_BEGIN	FILE_BEGIN
#define FRM_CURRENT	FILE_CURRENT
#define FRM_END		FILE_END
#endif
/*=============================*/
/*=============================*/
PTFILE	FS_CreateFile(string filename, i32 option);
BOOL	FS_ReadFile	(PTFILE file, void* buf, ulong len);
BOOL	FS_Write(PTFILE file, void* p_buf, ulong p_nb);
byte	FS_ReadByte	(PTFILE file);
float	FS_ReadFloat(PTFILE file);
word	FS_ReadWord	(PTFILE file);
dword	FS_ReadDword(PTFILE file);
BOOL	FS_CloseFile(PTFILE file);
BOOL	FS_SetPos(PTFILE file, i32 pos, i32 flag);
BOOL	FS_CloseFile(PTFILE file);
/*=============================*/
/*=============================*/
#endif /*_FILE_SYSTEM_H_*/