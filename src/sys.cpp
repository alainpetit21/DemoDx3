#include <windows.h>
#include "types.h"
#include "sys.h"
#include "graphic.h"
#include "input.h"
#include "macros.h"

WNDCLASS	wc;

__int64		gFreq;
HINSTANCE	ghInstance	=0;
HWND		ghWnd		=0;
string		ghAppName	=0;
string		ghClassName	=0;

extern void main(void);

long FAR PASCAL 
WindowProc(HWND hWnd, UINT message,	WPARAM wParam, LPARAM lParam)
{
  INP_Trap(hWnd, message, wParam, lParam);
	
  switch(message){
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      return ::DefWindowProc(hWnd, message, 
        wParam, lParam);
  }
  return 1;
}

int pascal 
WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int c)
{
  ghInstance= hInstance;
  main();
  return 0;
}

void SYS_Init(string p_appName, string p_className, int w, int h)
{
	wc.style			= CS_HREDRAW | CS_VREDRAW; 
	wc.lpfnWndProc		= (WNDPROC) WindowProc;
	wc.cbClsExtra		= 0; 
	wc.cbWndExtra		= 0; 
	wc.hInstance		= ghInstance; 
	wc.hIcon			= LoadIcon((HINSTANCE) NULL, IDI_APPLICATION); 
	wc.hCursor			= LoadCursor((HINSTANCE) NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH); 
	wc.lpszMenuName		= "Menu"; 
	wc.lpszClassName	= p_className; 
	VERIFY(RegisterClass(&wc), "Cant register class");
	VERIFY((ghWnd= CreateWindow ( p_className,
					p_appName,
					WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,/* WS_OVERLAPPEDWINDOW,*/
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					w, h,
					(HWND) NULL,
					(HMENU) NULL,
					ghInstance,
					(LPVOID) NULL)), "Cant register class");
	QueryPerformanceFrequency((LARGE_INTEGER*)&gFreq);
	ShowWindow(ghWnd, SW_SHOWNORMAL);
}

void SYS_Quit(string p_appName, string p_className)
{
	DestroyWindow ( ghWnd );
	UnregisterClass(p_className, ghInstance);
}

int SYS_DoFrame(void)
{
	static MSG message;
  if(PeekMessage(&message,NULL,0,0,PM_REMOVE)){
    if(message.message == WM_QUIT) return 1;
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
  return 0;
}