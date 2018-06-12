/*
Low level hardware access
This sample belongs to of the Low Level Access Part Series, Part I
(c) Inaki Castillo 2001
*/

//CASIO EM500 Sample 1

#include <windows.h>

//special include: if you have Platform Builder you can replace this with #include <pkfuncs.h>
extern BOOL VirtualCopy(LPVOID lpvDest, LPVOID lpvSrc, DWORD cbSize, DWORD fdwProtect);

#ifdef ARM
PAGE_SIZE = 0x1000; //4KB Size for ARM SA1100 and SA1110
#else
PAGE_SIZE = 0x400; // 1KB Size for MIPS VR41xx and SH3
#endif
//endif of special include

/*---------------------------------------------------------------------------------
PVOID MapHardwareZone (DWORD physicalAddress, DWORD *alignedVirtualAddress )
Returns a virtual address that maps to a physical address range of size equal to PAGE_SIZE

DWORD physicalAddress INPUT parameter. It is the starting physical address
PVOID *alignedVirtualAddress OUTPUT parameter. Contains page aligned virtual address at return.

Returns: Virtual Address that points to the requested physical address, or NULL if error.
---------------------------------------------------------------------------------------------------*/
PVOID MapHardwareZone (IN DWORD physicalAddress, OUT PVOID *alignedVirtualAddress )
{
PVOID pVirtualAddress;
ULONG alignedPhysicalAddress;
ULONG size = (PAGE_SIZE) * 2;

	//Align source physical address to a page boundary
	alignedPhysicalAddress = physicalAddress & ~(PAGE_SIZE - 1);

	//Reserve linear address range 
	pVirtualAddress = VirtualAlloc(0, size, MEM_RESERVE, PAGE_NOACCESS);

	//Maps to physical range
	if ( pVirtualAddress != NULL && VirtualCopy( pVirtualAddress, (PVOID)(alignedPhysicalAddress >> 8), size,
	PAGE_PHYSICAL | PAGE_READWRITE | PAGE_NOCACHE))
		{
		//Copy the aligned virtual address to destination
		*alignedVirtualAddress = pVirtualAddress;

		//adjust the final virtual address adding the reminder from page boundary to our desired offset
		(ULONG)pVirtualAddress += physicalAddress & (PAGE_SIZE - 1);
		}
	else 
		{
		//oops!, something wrong has occurred, free virtual area and return NULL 
		VirtualFree(pVirtualAddress, size, MEM_RELEASE);
		pVirtualAddress = NULL;
		}


return (pVirtualAddress);
}
/*------------------------------------------------------------------------------------------------------
PVOID UnMapHardwareZone ( PVOID alignedVirtualAddress )
Frees a hardware mapped zone.

PVOID alignedVirtualAddress. INPUT parameter. Contains page aligned virtual address.

Returns: nothing
------------------------------------------------------------------------------------------------*/
VOID UnMapHardwareZone (IN PVOID alignedVirtualAddress )
{
	VirtualFree(alignedVirtualAddress, 0, MEM_RELEASE);
}
//-------------------------------------------------------------------------------
void TestCasioBrightness(void)
{
PVOID alignedVirtualAddress;
WORD *ptrW;
int i,currentContrast,currentBrightness;
#define BRIGHTNESS_REGISTER (0xC/2)
#define CONTRAST_REGISTER (0x1C/2)

	//map zone
/*	ptrW = MapHardwareZone (0x0A000980, &alignedVirtualAddress );*/
	ptrW = (unsigned short*)0xAA000980;
	if(ptrW)
		{
		//Read current brightness and contrast
		currentBrightness = ptrW[BRIGHTNESS_REGISTER];
		currentContrast   = ptrW[CONTRAST_REGISTER];

		//Slow ramp of brightness
		for(i=0;i<0x1FF;i++){
			ptrW[BRIGHTNESS_REGISTER]=i;
			Sleep(30);
		}

		ptrW[BRIGHTNESS_REGISTER]=currentBrightness;

		//Slow ramp of contrast
		for(i=0;i<0x1FF;i++){
			ptrW[CONTRAST_REGISTER]=i;
			Sleep(30);
		}

		ptrW[CONTRAST_REGISTER]=currentContrast;	

		
		//Unmap zone
/*		UnMapHardwareZone ( alignedVirtualAddress );*/
		}
} 
/********************************************************************/
int pascal WinMain(HINSTANCE h1,HINSTANCE h2,LPWSTR lpCmdLine,int c)
{

	TestCasioBrightness();
	return 0;

}
