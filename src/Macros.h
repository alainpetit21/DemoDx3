#ifndef _MACROS_H_
#define _MACROS_H_
#pragma message("_MACROS_H_")
/*=========================*/
/*=========================*/
#undef 	SAFE_DELETE
#define SAFE_DELETE(a)\
  if (a){delete a; a= 0;}
/*=========================*/
#undef	SAFE_RELEASE
#define SAFE_RELEASE(a)\
  if (a){a->Release(); a= 0;}
/*=========================*/
#undef	SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(a)\
  if (a){delete []a; a= 0;}
/*=========================*/
#undef	ARRAY_SIZE
#define ARRAY_SIZE(a)			(sizeof(a) / sizeof(a[0]))
/*=========================*/
#undef _T
#ifndef _UNICODE
  #define _T
#else
  #define _T	L
#endif
/*=========================*/
#undef ASSERT
#ifdef _POCKET_PC
  #ifdef _DEBUG
    #define ASSERT(a, s)\
      if(!a){::MessageBox(NULL, s, 0, 0);exit(-1);}
  #else
    #define ASSERT(a, s)
  #endif	// DEBUG
#elif defined _DX3
  #ifdef _DEBUG
    #define ASSERT(a, s)\
      if(!a){::MessageBox(NULL, s, 0, 0);exit(-1);}
  #else
    #define ASSERT(a, s)
  #endif	// DEBUG
#else
  #ifdef _DEBUG
    #define ASSERT(a, s)	if (!a)	{9/a;}
  #else
    #define ASSERT(a, s)
  #endif	// DEBUG
#endif	// _WIN32
/*=========================*/
#undef	VERIFY
#ifdef _POCKET_PC
#pragma message("VERIFY for _POCKET_PC")
  #ifdef _DEBUG
    #pragma message("_DEBUG VERIFY for _POCKET_PC")
    #define VERIFY(a, s)	\
      if(!(a)){::MessageBox(NULL, s, 0, 0);exit(-1);}
  #else
    #pragma message("NDEBUG VERIFY for _POCKET_PC")
    #define VERIFY(a, s)	a;
  #endif	// DEBUG
#elif defined _DX3
#pragma message("VERIFY for _DX3")
  #ifdef _DEBUG
    #pragma message("_DEBUG VERIFY for _DX3")
    #define VERIFY(a, s)	\
      if(!(a)){::MessageBox(NULL, s, 0, 0);exit(-1);}
  #else
    #pragma message("NDEBUG VERIFY for _DX3")
    #define VERIFY(a, s)	a;
  #endif	// DEBUG
#else
  #pragma message("VERIFY for else")
  #ifdef _DEBUG
    #pragma message("_DEBUG VERIFY for else")
    #define VERIFY(a, s)	\
      if (!(a)){9/a;}	// Will crash!
  #else
    #pragma message("NDEBUG VERIFY for else")
    #define VERIFY(a, s)	a	
  #endif // DEBUG
#endif	// _WIN32
/*=========================*/
#undef TRAP_MSG
#if defined(_WIN32)||defined(_POCKET_PC)
  #define TRAP_MSG(a)	\
    if(PeekMessage(&a,NULL,0,0,PM_REMOVE)){\
      if(a.message == WM_QUIT) break;\
        TranslateMessage(&a);	\
        DispatchMessage(&a);	\
      }
#elif defined(_DOS)
  typedef int	MSG;
  #define TRAP_WINDOWS(a)
#elif defined(_OS9)
  typedef int	MSG;
  #define TRAP_WINDOWS(a)
#elif defined(_TES)
  typedef int	MSG;
  #define TRAP_WINDOWS(a)
#elif defined(_LINUX)
  typedef int	MSG;
  #define TRAP_WINDOWS(a)
#endif
/*=========================*/
/*=========================*/
#define _QUOTE(x) # x
#define QUOTE(x) _QUOTE(x)
#define __FILE__LINE__ __FILE__ "(" QUOTE(__LINE__) ") : "
/*=========================*/
#define NOTE( x ) message( x )
#define FILE_LINE message( __FILE__LINE__ )
/*=========================*/
#define TODO( x ) message( __FILE__LINE__"\n"\
        " ------------------------------------------------\n" \
        "|  TODO :   " #x "\n" \
        " -------------------------------------------------\n" )
/*=========================*/
#define FIXME( x ) message(  __FILE__LINE__"\n"\
        " ------------------------------------------------\n" \
        "|  FIXME :  " #x "\n" \
        " -------------------------------------------------\n" )
/*=========================*/
#define todo( x ) message( __FILE__LINE__" \
  TODO :   " #x "\n" ) 
/*=========================*/
#define fixme( x )  message( __FILE__LINE__" \
FIXME:   " #x "\n" ) 
/*=========================*/
/*=========================*/
#undef ENTER_FUNCTION
#if defined(_WIN32) || defined(_POCKET_PC)
  #define ENTER_FUNCTION(x)		\
    OutputDebugString(L"\n");	\
    OutputDebugString(L#x);
/*=========================*/
#define si(x) if(x){							\
  OutputDebugString(L"\n\tEnter Condition : ");	\
  OutputDebugString(L#x);
#else
  #define ENTER_FUNCTION(x)
  #define si(x) if(x){
#endif
/*=========================*/
/*=========================*/
#undef PROFILER_INC
#undef PROFILER_DEC
#undef PROFILER_INIT
#undef PROFILER_BEFORE
#undef PROFILER_AFTER
#ifdef _PROFILE
  #if defined(_POCKET_PC)
    #define PROFILER_INC
    #define PROFILER_DEC	\
      __int64 freq;		\
      __int64 timePrev;		\
      __int64 time;		\
      wchar_t  buf[64];														      
   #define PROFILER_INIT	\
    ::QueryPerformanceFrequency(	\
      (LARGE_INTEGER*)&freq);	\
    buf[0]='\0';
  #define PROFILER_BEFORE	\
    ::QueryPerformanceCounter(	\
      (LARGE_INTEGER*)&time);	\
    timePrev= time;
  #define PROFILER_AFTER(string, returnLine)\
    ::QueryPerformanceCounter(	\
      (LARGE_INTEGER*)&time);	\
    swprintf(buf,_T"%s%d%s", string,\
      (uint)(time-timePrev), returnLine);\
    OutputDebugString(buf);
  #elif defined(_DX3)
    #define PROFILER_INC
    #define PROFILER_DEC	\
      __int64 freq;		\
      __int64 timePrev;		\
      __int64 time;		\
      char  buf[64];														      
   #define PROFILER_INIT	\
    ::QueryPerformanceFrequency(	\
      (LARGE_INTEGER*)&freq);	\
    buf[0]='\0';
  #define PROFILER_BEFORE	\
    ::QueryPerformanceCounter(	\
      (LARGE_INTEGER*)&time);	\
    timePrev= time;
  #define PROFILER_AFTER(string, returnLine)\
    ::QueryPerformanceCounter(	\
      (LARGE_INTEGER*)&time);	\
    sprintf(buf,"%s%d%s", string,\
      (uint)(time-timePrev), returnLine);\
    OutputDebugString(buf);
  #endif	//	_POCKET_PC
#endif	//	_PROFILE
/*=========================*/
/*=========================*/
#undef CHAR_TO_DIGIT
#define CHAR_TO_DIGIT(a)	((a) - '0')
/*=========================*/
#undef DIGIT_TO_CHAR
#define DIGIT_TO_CHAR(a)	((a) + '0')
/*=========================*/
#undef	SWAP32
#define SWAP32(a)					 \
((( (long)a) & 0xff000000)	>> 24)	|\
((( (long)a) & 0x00ff0000)	>> 8)	|\
((( (long)a) & 0x0000ff00)	<< 8)	|\
((( (long)a) & 0x000000ff)	<< 24)
/*=========================*/
#undef	SWAP16
#define SWAP16(a)					 \
(((((short)a) & 0xff00) >> 8)		|\
((( (short)a) & 0x00ff) << 8))
/*=========================*/
/*=========================*/
#undef	PI
#define PI	3.1415926535f
/*=========================*/
#undef	IS_ODD
#define IS_ODD(a)	(((uchar)a)&1)
/*=========================*/
#undef	IS_EVEN
#define IS_EVEN(a)	(!(((uchar)a)&1))
/*=========================*/
#undef	NUM_SIGN
#define NUM_SIGN(a)	((p<0)?-1:1)
/*=========================*/
#undef	DEG_TO_RAD
#define DEG_TO_RAD(a)	(p*PI/180.0f)
/*=========================*/
#undef	RAD_TO_DEG
#define RAD_TO_DEG(a)	(p*180.0f/PI)
/*=========================*/
#undef	RAND_RANGE
#define RAND_RANGE(a,b)	(a + (rand()%(b-a+1)))
/*=========================*/
#undef	MIN
#define MIN(a,b)	((a<b)?a:b)
/*=========================*/
#undef	MAX
#define MAX(a,b)	((a>b)?a:b)
/*=========================*/
#undef	ABS
#define ABS(a)		((a>0)?a:-a)
/*=========================*/
#undef	SWAP
#define SWAP(a,b,t)	t=a;a=b;a=t;
/*=========================*/
#endif	// _MACROS_H_
