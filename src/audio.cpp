#include <windows.h>
#include "audio.h"
#include "file.h"
#include "Macros.h"

HWAVEOUT		gHWO;
WAVEFORMATEX	gWF;
WAVEHDR		gHW;
ui32			gbCanWrite=0;

void
AUD_Init(i32 bps, i32 channels, i32 khz)
{
  VERIFY((waveOutGetNumDevs() != 0), 
    _T"No Sound Devices");

  memset(&gHWO,	0, sizeof(gHWO));
  memset(&gWF,	0, sizeof(gWF));
  memset(&gHW,	0, sizeof(gHW));
	
  gWF.cbSize		= 0;
  gWF.wFormatTag	= WAVE_FORMAT_PCM;
  gWF.wBitsPerSample= (ui16)bps;
  gWF.nChannels		= (ui16)channels;
  gWF.nSamplesPerSec= khz;
  gWF.nBlockAlign	= (channels * bps / 8);
  gWF.nAvgBytesPerSec= (gWF.nBlockAlign * khz);

  VERIFY((waveOutOpen(&gHWO, 0, 
    (WAVEFORMATEX*)&gWF, 0, 0, 
    CALLBACK_NULL) == MMSYSERR_NOERROR),
    _T"Cant Open Wave Device");

  gbCanWrite	= 1;
}

long
AUD_Trap(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch(message){
    case WOM_DONE:{
      waveOutUnprepareHeader(gHWO, &gHW, 
        (ui32)sizeof(WAVEHDR));
      gbCanWrite= 1;
      return 1;
    }	
  }
  return 0;
}

void
AUD_Quit(void)
{
  VERIFY((waveOutReset(gHWO) == 
    MMSYSERR_NOERROR), 
    _T"Can't Reset Device");
  VERIFY((waveOutClose(gHWO) == 
    MMSYSERR_NOERROR), 
    _T"Can't Close Device");
}

void
AUD_IPreWavAllocation(WAVESOUND **pWSnd, 
PTFILE pWaveFile)
{
  typedef struct tagWAVE_CHUNK{
    ulong ckid;
    ulong cksize;
  } WAVE_CHUNK;
	
  WAVE_CHUNK waveChunk = {0,0};
  ulong		buf32;
  uchar		bFinished = 0;
  uchar		miniBuffer= 0;
    

//read the first chunk of the file
  FS_ReadFile(pWaveFile, &waveChunk, 
    sizeof(WAVE_CHUNK));
  ASSERT(((waveChunk.ckid) || 
    (waveChunk.cksize)), _T"Wrong Format File 1");

//check if we have a RIFF file with a WAVE type
  FS_ReadFile(pWaveFile, &buf32, sizeof(ulong));
  ASSERT(((waveChunk.ckid == 
    mmioFOURCC('R','I','F','F')) && 
    (buf32 == mmioFOURCC('W','A','V','E'))), 
    _T"Wrong Format File 2");

//parses the wave file for sub-chunks
  do{
    FS_ReadFile(pWaveFile, &buf32, sizeof(ulong));
  }while(buf32 != mmioFOURCC('d','a','t','a'));
	
  FS_ReadFile(pWaveFile, &buf32, sizeof(ulong));
  (*pWSnd)->dwDataSize= buf32;
  (*pWSnd)->dwDataLeft= buf32;
}

void
AUD_IPostWavAllocation(WAVESOUND **pWSnd, 
PTFILE pWaveFile)
{
//read whole rest of file as raw wavedata
  FS_ReadFile(pWaveFile, (*pWSnd)->pData, (*pWSnd)->dwDataSize);
}

void
AUD_InitWaveSound16(WAVESOUND **pSnd, ui16** p_mem, string filename)
{
  PTFILE pWaveFile= FS_CreateFile(filename, GENERIC_READ);

  AUD_IPreWavAllocation(pSnd, pWaveFile);
  (*pSnd)->pData= (*p_mem);
  AUD_IPostWavAllocation(pSnd, pWaveFile);
  (*p_mem)+= (*pSnd)->dwDataSize;
  (*pSnd)++;
}

void
AUD_InitWaveSound8(WAVESOUND **pSnd, ui8** p_mem, string filename)
{
  PTFILE pWaveFile= FS_CreateFile(filename, GENERIC_READ);

  AUD_IPreWavAllocation(pSnd, pWaveFile);
  (*pSnd)->pData= (*p_mem);
  AUD_IPostWavAllocation(pSnd, pWaveFile);
  (*p_mem)+= (*pSnd)->dwDataSize;
  (*pSnd)++;
}

void
AUD_WavePlay(WAVESOUND *pSnd, i32 nMode)
{
  ui32 nPlayFlags = SND_ASYNC | SND_MEMORY | SND_NODEFAULT; 
	
  pSnd->nPlayingMode= nMode;

//set up WAVEHDR for playback
  gHW.lpData		= (char*)pSnd->pData;
  gHW.dwBufferLength	= pSnd->dwDataSize;
  gHW.dwUser		= 0;
	
  switch (nMode){                               
    case SND_PLAYLOOP:
      gHW.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
      gHW.dwLoops = 0xFFFFFFFF;
      break;
    case SND_PLAYONCE:
      gHW.dwFlags = 0;
      break;                                  	
  }

  waveOutPrepareHeader(gHWO, &gHW, (ui32)sizeof(WAVEHDR));
			
//if another sound is playing now we "overwrite" by resetting waveOut and playing ours
//otherwise we queue the sounds one after the other.
  VERIFY((waveOutReset(gHWO) == 
    MMSYSERR_NOERROR), 
    _T"Can't Reset Device");

//plays the sound and activates the callback
  VERIFY((waveOutWrite(gHWO, &gHW, (ui32)sizeof(WAVEHDR)) == 
    MMSYSERR_NOERROR),
    _T"Cant Write to Device")
	waveOutUnprepareHeader(gHWO, &gHW, (ui32)sizeof(WAVEHDR));

  gbCanWrite= 0;
}

void
AUD_WavePause(WAVESOUND *pWaveSnd, ulong* lpdwPos)
{
  MMTIME mmtime;
  ASSERT(pWaveSnd, _T"invalid wave")

//sets up a structure to receive play offset 
  mmtime.wType = TIME_BYTES;
	
//gets the byte offset of the play pointer
  VERIFY((waveOutGetPosition(gHWO, &mmtime, 
    sizeof(mmtime)) == MMSYSERR_NOERROR), 
    _T"Cant Get Wave Position")

//retrieve offset
  *lpdwPos= (ulong)mmtime.u.cb;
  pWaveSnd->lPosition= *lpdwPos;

VERIFY((waveOutPause(gHWO) == 
    MMSYSERR_NOERROR), 
    _T"Cant Pause Wave");
}

void
AUD_WaveResume(WAVESOUND *pWaveSnd, ulong* lpdwPos, short nMode)
{
  ASSERT(pWaveSnd, _T"invalid wave")
  VERIFY((waveOutReset(gHWO) == 
    MMSYSERR_NOERROR), 
    _T"Can't Reset Device")
  AUD_WavePlay(pWaveSnd, nMode);
}

void
AUD_WaveStop(WAVESOUND *pWaveSnd)
{
  ASSERT(pWaveSnd, _T"invalid wave")
  VERIFY((waveOutReset(gHWO) == 
    MMSYSERR_NOERROR), 
    _T"Can't Reset Device");
  pWaveSnd->nPlayingMode= NULL;
}

void
AUD_WaveGetStatus(WAVESOUND *pWaveSnd, long *plStatus)
{
}

void
AUD_WaveGetVolume(WAVESOUND *pWaveSnd, long *lVolume)
{
  ASSERT(pWaveSnd, _T"invalid wave")
  VERIFY((waveOutGetVolume(gHWO, (ulong*)lVolume) == MMSYSERR_NOERROR), 
  _T"Cant Get Volume")

  *lVolume = (long)((*lVolume)&0xFF);
}

void
AUD_WaveSetVolume(WAVESOUND *pWaveSnd, long lVolume)
{
  i32 	x;
  uchar 	octet= lVolume & 0xFF;
  ulong dwVol=(ulong)MAKELPARAM(((octet)|(octet<<8)),((octet)|(octet<<8)));	

	VERIFY(((x= waveOutSetVolume(gHWO, dwVol)) == MMSYSERR_NOERROR), _T"Can't Set Volume")
	if(x){
		VERIFY((waveOutReset(gHWO) == MMSYSERR_NOERROR), _T"Can't Reset Device");
	}
}

void
AUD_UnInitWaveSound(WAVESOUND *pWaveSnd)
{
	ASSERT(pWaveSnd, _T"invalid wave")
	ASSERT(pWaveSnd->pData, _T"invalid wave Data")

	AUD_WaveStop(pWaveSnd);
	pWaveSnd->pData= 0;
}

void
AUD_SetMasterVolume(long lVolume)
{
	AUD_WaveSetVolume(0, lVolume);
}

void
AUD_GetMasterVolume(long* lVolume)
{
}
