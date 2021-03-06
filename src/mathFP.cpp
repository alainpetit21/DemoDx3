#define EXTERN extern
#include <memory.h>
#include "MathFP.h"
int Sin[256]={
0		,25		,50		,75		,100	,125	,150	,175	,
200		,224	,249	,273	,297	,321	,345	,369	,
392		,415	,438	,460	,483	,505	,526	,548	,
569		,590	,610	,630	,650	,669	,688	,706	,
724		,742	,759	,775	,792	,807	,822	,837	,
851		,865	,878	,891	,903	,915	,926	,936	,
946		,955	,964	,972	,980	,987	,993	,999	,
1004	,1009	,1013	,1016	,1019	,1021	,1023	,1024	,
1024	,1024	,1023	,1021	,1019	,1016	,1013	,1009	,
1004	,999	,993	,987	,980	,972	,964	,955	,
946		,936	,926	,915	,903	,891	,878	,865	,
851		,837	,822	,807	,792	,775	,759	,742	,
724		,706	,688	,669	,650	,630	,610	,590	,
569		,548	,526	,505	,483	,460	,438	,415	,
392		,369	,345	,321	,297	,273	,249	,224	,
200		,175	,150	,125	,100	,75		,50		,25		,
0		,-24	,-49	,-74	,-99	,-124	,-149	,-174	,
-199	,-223	,-248	,-272	,-296	,-320	,-344	,-368	,
-391	,-414	,-437	,-459	,-482	,-504	,-525	,-547	,
-568	,-589	,-609	,-629	,-649	,-668	,-687	,-705	,
-723	,-741	,-758	,-774	,-791	,-806	,-821	,-836	,
-850	,-864	,-877	,-890	,-902	,-914	,-925	,-935	,
-945	,-954	,-963	,-971	,-979	,-986	,-992	,-998	,
-1003	,-1008	,-1012	,-1015	,-1018	,-1020	,-1022	,-1023	,
-1023	,-1023	,-1022	,-1020	,-1018	,-1015	,-1012	,-1008	,
-1003	,-998	,-992	,-986	,-979	,-971	,-963	,-954	,
-945	,-935	,-925	,-914	,-902	,-890	,-877	,-864	,
-850	,-836	,-821	,-806	,-791	,-774	,-758	,-741	,
-723	,-705	,-687	,-668	,-649	,-629	,-609	,-589	,
-568	,-547	,-525	,-504	,-482	,-459	,-437	,-414	,
-391	,-368	,-344	,-320	,-296	,-272	,-248	,-223	,
-199	,-174	,-149	,-124	,-99	,-74	,-49	,-24	,
};

int Cos[256]={
1024	,1024	,1023	,1021	,1019	,1016	,1013	,1009	,
1004	,999	,993	,987	,980	,972	,964	,955	,
946		,936	,926	,915	,903	,891	,878	,865	,
851		,837	,822	,807	,792	,775	,759	,742	,
724		,706	,688	,669	,650	,630	,610	,590	,
569		,548	,526	,505	,483	,460	,438	,415	,
392		,369	,345	,321	,297	,273	,249	,224	,
200		,175	,150	,125	,100	,75		,50		,25		,
0		,-24	,-49	,-74	,-99	,-124	,-149	,-174	,
-199	,-223	,-248	,-272	,-296	,-320	,-344	,-368	,
-391	,-414	,-437	,-459	,-482	,-504	,-525	,-547	,
-568	,-589	,-609	,-629	,-649	,-668	,-687	,-705	,
-723	,-741	,-758	,-774	,-791	,-806	,-821	,-836	,
-850	,-864	,-877	,-890	,-902	,-914	,-925	,-935	,
-945	,-954	,-963	,-971	,-979	,-986	,-992	,-998	,
-1003	,-1008	,-1012	,-1015	,-1018	,-1020	,-1022	,-1023	,
-1023	,-1023	,-1022	,-1020	,-1018	,-1015	,-1012	,-1008	,
-1003	,-998	,-992	,-986	,-979	,-971	,-963	,-954	,
-945	,-935	,-925	,-914	,-902	,-890	,-877	,-864	,
-850	,-836	,-821	,-806	,-791	,-774	,-758	,-741	,
-723	,-705	,-687	,-668	,-649	,-629	,-609	,-589	,
-568	,-547	,-525	,-504	,-482	,-459	,-437	,-414	,
-391	,-368	,-344	,-320	,-296	,-272	,-248	,-223	,
-199	,-174	,-149	,-124	,-99	,-74	,-49	,-24	,
0		,25		,50		,75		,100	,125	,150	,175	,
200		,224	,249	,273	,297	,321	,345	,369	,
392		,415	,438	,460	,483	,505	,526	,548	,
569		,590	,610	,630	,650	,669	,688	,706	,
724		,742	,759	,775	,792	,807	,822	,837	,
851		,865	,878	,891	,903	,915	,926	,936	,
946		,955	,964	,972	,980	,987	,993	,999	,
1004	,1009	,1013	,1016	,1019	,1021	,1023	,1024	,
};

void CBMatrix::Identity()
{
	memset(l, 0x0, sizeof(int)*16);
	l[0] = l[5] = l[10] = l[15] = FP_ONE;
}

void CBMatrix::Rotatex( int a_X )
{
	int sinx = Sin[a_X];
	int cosx = Cos[a_X];
	l[5] = cosx;
	l[6] = sinx;
	l[9] = -sinx;
	l[10] = cosx;
}

void CBMatrix::Rotatey( int a_Y )
{
	int siny = Sin[a_Y];
	int cosy = Cos[a_Y];
	l[0] = cosy;
	l[2] = -siny;
	l[8] = siny;
	l[10] = cosy;
}

void CBMatrix::Rotatez( int a_Z )
{
	int sinz = Sin[a_Z];
	int cosz = Cos[a_Z];
	l[0] = cosz;
	l[1] = sinz;
	l[4] = -sinz;
	l[5] = cosz;
}

void CBMatrix::Translate( int a_X, int a_Y, int a_Z )
{
	l[3] += a_X;
	l[7] += a_Y;
	l[11]+= a_Z;
}

void CBMatrix::Concat( const CBMatrix& a_M2)
{
	CBMatrix res;
	for ( int col = 0; col < 4; col++ )
		for ( int row = 0; row < 4; row++ )
			res.l[row * 4 + col] = 
				FPMUL(l[row * 4], a_M2.l[col] ) +
				FPMUL(l[row * 4 + 1], a_M2.l[col + 4] ) +
				FPMUL(l[row * 4 + 2], a_M2.l[col + 8] );

	res.Translate(m14, m24, m34);
	memcpy(l, res.l, sizeof(int)*16);
}

void CBMatrix::Rotate( int a_RX, int a_RY, int a_RZ )
{	
	CBMatrix tempmat;
	tempmat.Identity();
	tempmat.Rotatex( a_RX );
	this->Rotatey( a_RY );
	this->Concat( tempmat );
	tempmat.Rotatez( a_RZ );
	this->Concat( tempmat );
}

int*
CBMatrix::Getx(int* p_vec)
{
	p_vec[0]= l[0];
	p_vec[1]= l[4];
	p_vec[2]= l[8];
	return p_vec;
}

int*
CBMatrix::Gety(int* p_vec)
{
	p_vec[0]= l[1];
	p_vec[1]= l[5];
	p_vec[2]= l[9];
	return p_vec;
}

int*
CBMatrix::Getz(int* p_vec)
{
	p_vec[0]= l[2];
	p_vec[1]= l[6];
	p_vec[2]= l[10];
	return p_vec;
}

