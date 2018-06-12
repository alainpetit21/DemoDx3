#ifndef _MATHFP_H_
#define _MATHFP_H_
/*=========================*/
/*=========================*/
#define FPP 10
#define IFP(x) ((x)<<FPP)
#define FP_ONE IFP(1)
#define FPMUL(x,y) (((x)*(y))>>FPP)
#define FPDIV(x,y) (((x)<<FPP)/(y))
#define FP(x) ((int)((x)*FP_ONE+0.5f))
/*=========================*/
/*=========================*/
extern int Sin[256];
extern int Cos[256];
/*=========================*/
/*=========================*/
#undef sin
#undef cos
#define sin(x) Sin[x]
#define cos(x) Cos[x]
/*=========================*/
/*=========================*/
class CBMatrix
{
public:
  explicit CBMatrix()
    {Identity();};
  void	Identity();
  void	Rotatex(int x);
  void	Rotatey(int y);
  void	Rotatez(int z);
  void  Translate(int x, int y, int z);
  void	Concat(const CBMatrix& a_M2);
  void	Rotate(int x, int y, int z);
  int*	Getx(int* p_vec);
  int*	Gety(int* p_vec);
  int*	Getz(int* p_vec);
  union{
    int m[4][4];
    int l[16];
    struct {
      int m11,m12,m13,m14
      , m21,m22,m23,m24
      , m31,m32,m33,m34
      , m41,m42,m43,m44;
    };
  };
};
/*=========================*/
/*=========================*/
#endif	// _MATHFP_H_

