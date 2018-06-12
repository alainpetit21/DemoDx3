#ifndef _SYS_H_
#define _SYS_H_
/*=========================*/
/*=========================*/
#define SCREEN_PITCH	640
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
/*=========================*/
/*=========================*/
void SYS_Init(string p_appName, string p_className, int w, int h);
void SYS_Quit(string p_appName, string p_className);
int	SYS_DoFrame(void);
/*=========================*/
/*=========================*/
#endif	/*_SYS_H_*/
