#include <windows.h>
#include "types.h"
#include "TileMap.h"
#include "resman.h"
#include "file.h"
#include "graphic.h"

void TM_Init(string filename)
{	
	ui32 nbBitmap;
	ui32 w;
	ui32 h;
	PTFILE fichier= FS_CreateFile(filename, GENERIC_READ);

	nbBitmap= FS_ReadDword(fichier);
	w= FS_ReadDword(fichier);
	h= FS_ReadDword(fichier);

	for(ui32 i= 0; i < nbBitmap;++i){
		char filename2[128];
		FS_ReadFile(fichier, filename2, sizeof(char)*128);
		VID_LoadTGA(CUR_IMAGE, CUR_PIXEL, filename2);
	}
}