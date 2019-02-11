#include "StdAfx.h"
#include "Caculate.h"
#include <math.h>

#define __PI	3.14159265
#define FP1  127.252
#define FP2  -481.141
#define FP3  -657.831
#define FP4  1.829
#define FP5  -2.092
#define FP6  8.406
#define FP7  -6.354

namespace GlobalUtil
{
		double Caculate::m_PAI = 0.0;
		double Caculate::m_RAD1= 0.0;
		double Caculate::m_PAI4= 0.0;
		double Caculate::m_FP4= 0.0;
		double Caculate::m_FP5= 0.0;
		double Caculate::m_FP6= 0.0;
		double Caculate::m_FP7= 0.0;
		double Caculate::m_B0 = 0.0;



	/*
	Caculate* Caculate::m_pThis = NULL;

	Caculate* Caculate::GetInstance()
	{
		if( m_pThis == NULL )
		{
			m_pThis = new Caculate;		
		}
		return m_pThis;
	}

	void Caculate::ReleaseInstance()
	{
		if( m_pThis != NULL )
		{
			delete m_pThis;
			m_pThis = NULL;
		}
	}
	*/

	void Caculate::travers_coord(double a, double E2, double K0, double Phi0, double Lamda0, double Phi, double Lamda,
	   double &X, double &Y, double &K, double &Cov)
	{

	  double CosSQ, dLamda, Mu, TT, RO, M0, Aa, N, T, C, M, Ep2, E4, E6; 

	  RO = 180.0 * 60.0 * 60.0 / __PI;
	  if (K0 < 0.0001) 
		return;

	  Ep2 = E2 / (1.0 - E2);
	  E4 = pow(E2, 2);
	  E6 = E4 * E2;
	  Aa = cos(Phi) * (Lamda - Lamda0);
	  N  = a / sqrt(1.0 - E2 * (pow(sin(Phi),2)));
	  T  = pow(tan(Phi),2);
	  C  = Ep2 * (pow(cos(Phi), 2));
	  M  = a * ((1.0 - E2 / 4.0 - 3.0 * E4 / 64.0 - 5.0 * E6 / 256.0) * Phi -
		(3.0 * E2 / 8.0 + 3.0 * E4 / 32.0 + 45.0 * E6 / 1024.0) * sin(2.0 * Phi) +
		(15.0 * E4 / 256.0 + 45.0 * E6 / 1024.0) * sin(4.0 * Phi) - (35.0 * E6 / 3072.0) * sin(6.0 * Phi));
	  M0 = a * ((1.0 - E2 / 4.0 - 3.0 * E4 / 64.0 - 5.0 * E6 / 256.0) * Phi0 -
		(3.0 * E2 / 8.0 + 3.0 * E4 / 32.0 + 45.0 * E6 / 1024.0) * sin(2.0 * Phi0) +
		(15.0 * E4 / 256.0 + 45.0 * E6 / 1024.0) * sin(4.0 * Phi0) - (35.0 * E6 / 3072.0) * sin(6.0 * Phi0));

	  //X = K0 * N * (Aa + (1 - T + C) * IntPower(Aa, 3) / 6 +
	  X = K0 * N * (Aa + (1.0 - T + C) * pow(Aa, 3) / 6.0 +
	  //  (5 - 18 * T + (T)^2 + 71 * C - 58 * Ep2) * IntPower(Aa, 5) / 120);
		(5.0 - 18.0 * T + pow(T, 2) + 71.0 * C - 58.0 * Ep2) * pow(Aa, 5) / 120.0);
	  Y = K0 * (M - M0 + N * tan(Phi) * (pow(Aa,2) / 2.0 + (5.0 - T + 9.0 * C + 4.0 * pow(C,2)) *
	   // IntPower(Aa, 4) / 24 + (61 - 58 * T + (T)^2 + 600 * C - 330 * Ep2) *
	   // IntPower(Aa, 6) / 720));
		pow(Aa, 4) / 24.0 + (61.0 - 58.0 * T + pow(T,2) + 600.0 * C - 330.0 * Ep2) *
		pow(Aa, 6) / 720.0));
	  K = K0 * (1.0 + (1.0 + Ep2 * pow(cos(Phi),2)) * pow(X,2)/ (2.0 *pow(K0 * N,2)));

	  dLamda = Lamda - Lamda0;
	  Mu  = E2 * pow(cos(Phi),2) / (1.0 - E2);
	  TT  = tan(Phi);
	  CosSQ = pow(cos(Phi),2);
	  Cov = -1.0 * dLamda * sin(Phi) * (1.0 + pow(dLamda,2) * CosSQ *
		(1.0 + 3.0 * Mu) / (3.0 * pow(RO,2)) + pow(pow(dLamda, 2) * CosSQ, 2) *
		(2.0 - pow(TT,2)) / (15.0 * pow(RO,2) * pow(RO, 2)));

	}

	double Caculate::DMS(double Xx)
	{

	  double d, d1, m, s, dms;


	  d  = INT(Xx);
	  d1 = (Xx - d) * 60.0;
	  m  = int(d1 + 0.00000000001);
	  s = (d1 - m) * 60.0;
	  if ((s >= 59.99999999998) || (s == 60.0))
	  {
		m = m + 1.0;
		s = s - 60.0;
	  };

	  if ((m >= 59.99999999998) || (m == 60.0)) 
	  {
		d = d + 1.0;
		m = m - 60.0;
	  };

	  dms = d + m / 100.0 + s / 10000.0;
	  return dms;
	}

	double Caculate::GPS_DECODE(double Xx)
	{
		double Doo, Bun, dResult;

		Doo = (int)(Xx / 100.0);
		Bun = 100.0 * (Xx / 100.0 - Doo);
		dResult = Doo + Bun / 60.0;

		return dResult;
	}

	void Caculate::CalcCoord(double orgine, double dLatitude, double dLongitude, double &Xx, double &Yy)
	{
		double North;
		double East;
		double North_dev;
		double East_dev;
		double K1;
		double Conv;

		North = GPS_DECODE(dLatitude);
		East  = GPS_DECODE(dLongitude);

		North_dev = DMS(North);
		East_dev  = DMS(East);

		double dDevXx, dDevYy;
		dDevXx =0;
		dDevYy =0;

		transCoord(North_dev, East_dev, dDevXx, dDevYy);

		travers_coord(6377397.15507604, 0.0066743722306, 1.0, cRAD(38.0), //0.006674372231315
			cRAD(orgine), cRAD(North), cRAD(East), East, North, K1, Conv);

		Xx = East + 200000 + dDevXx;
		if (orgine==125)
		{
			Yy = North + 550000 + dDevYy;
		}
		else
		{
			Yy = North + 500000 + dDevYy;
		}

	}

	double Caculate::cRAD(double Xx)
	{
	  double nResult;	  
	  nResult = Xx * __PI / 180.0;
	  return nResult;
	}

	void Caculate::transCoord(double wb, double wl, double &Xx, double &Yy)
	{
		double wlat, wlon,wh, fp1, fp2, fp3, fp4, fp5, fp6, fp7 ;  //rad,pai,
		double SECB, SECl, xb, yb, xw, yw, cc, c0, blat, blon, bh;  //rad,pai,
		double KLD, KLM, WCS, KBD, KBM, WBS;
		CString st;

		wh = 0.0;

		m_PAI = atan(1.0)*4.0;
		m_RAD1 = m_PAI / 180;
  //wb = wlat1.Value;
  //wl = wlon1.Value;

		wlat = wb * m_RAD1;
		wlon = wl * m_RAD1;
		//C     WH=HH
		TRANSF(wlat, wlon, wh, blat, blon, bh);

		cc = blon / m_RAD1;
		c0 = 127. * m_RAD1;
		if (cc < 126)
			c0 = 125.0 * m_RAD1;
		if (cc >= 128.0)
			c0 = 129.0 * m_RAD1;

		MAP11(1, 1, blat, blon, c0, xb, yb);//    ! BESSEL PLANE COORD.
		MAP11(1, 1, wlat, wlon, c0, xw, yw);  //  ! WGS-84 PLANE COORD.

//		SECB = (blat - wlat) / RAD1 * 3600;
//		SECl = (blon - wlon) / RAD1 * 3600;

//		DMS_Dev(wlat, KBD, KBM, WBS);
//		DMS_Dev(wlon, KLD, KLM, WCS);

		Xx = yb - yw;
		Yy = xb - xw;
	}

	void Caculate::TRANSF(double WLAT, double WLON, double WH, double &blat, double &blon, double &bh)
	{
		double DX, DY, DZ, WX, WY, WZ;
		BLHXYZ(1, WLAT, WLON, WH, WX, WY, WZ);//             ! ON WGS84

	    m_FP4  = FP4 ;
		m_FP5  = FP5;
		m_FP6  = FP6;
		m_FP7  = FP7;

		m_FP4  = m_FP4 / 3600. * m_RAD1;
		m_FP5  = m_FP5 / 3600. * m_RAD1;
		m_FP6  = m_FP6 / 3600. * m_RAD1;
		m_FP7  = m_FP7 * 0.000001;//1.-6

		DX = FP1 + (WX * m_FP7) - (WZ * m_FP5) + (WY * m_FP6);//          ! CORR. BY FIXED PARA
		DY = FP2 + WY * m_FP7 + WZ * m_FP4 - WX * m_FP6;
		DZ = FP3 + WZ * m_FP7 - WY * m_FP4 + WX * m_FP5;
		WX = WX + DX;
		WY = WY + DY;
		WZ = WZ + DZ;

		XYZBLH(2, WX, WY, WZ, blat, blon, bh);//   ! LAT,LON,HEIGHT ON BESSEL
	
	}

	void Caculate::MAP11(int ND, int IBL, double &B, double &C, double &C0, double &X, double &Y)
	{
		double PAI, RAD1, BREF ;

		PAI = atan(1.0) * 4.0;
		RAD1 = PAI / 180.0;
		BREF = 38.0;
		m_B0 = BREF * RAD1;


		DBLFWD1(ND, B, C, X, Y, m_B0, C0);

	}

	void Caculate::DMS_Dev(double DEGRAD, double &JD, double &JM, double &DS)
	{
		double DD, DEG, DMN;
		int DM, err;
		double PAI, RAD1;

		PAI = atan(1.0) * 4.0;
		RAD1 = PAI / 180.0;

		DEG = DEGRAD / RAD1;
		DD  = int(DEG);
		DMN = (DEG - DD) * 60.0;

		CString cDMN, cDMNDM;
		DM = (int)((double)((int)(DMN * 10000 + 0.5)) / 10000.0 +0.5);



//		Round(

  /*val(floattostrf(DMN, fffixed, 10, 4), DM, err);
  val(floattostrf((DMN - DM) * 60.0, fffixed, 10, 4), DS, err);
  JD = DD;
  JM = DM;*/
	
	}

	void Caculate::BLHXYZ(double IFLAG, double B, double c, double h, double &X, double &Y, double &Z)
	{
		double RR, ES, RM, RN, ESQ;

		RMN(IFLAG, B, RM, RN, ESQ);
		ES = 1.0 - ESQ;
		X  = (RN + h) * cos(B) *cos(c);      // ! (3.15)
		Y  = (RN + h) * cos(B) * sin(c);
		Z  = (ES * RN + h) * sin(B);
		RR = sqrt(RM * RN);
	
	}

	void Caculate::RMN(double IFLAG, double B, double & RM, double & RN, double & ESQ)
	{

		double W2, W1, F, RA, AA1, AA2, FF1, FF2;

		AA1 = 6378137.0;
		FF1 = 298.257223563;
		AA2 = 6377397.155;
		FF2 = 299.1528;

		if (IFLAG == 1)
		{

			RA = AA1;
			F  = 1.0 / FF1;
		}
		else
		{
			RA = AA2;
			F  = 1.0 / FF2;
		}

		ESQ = 2.0 * F - F * F;
		W2  = 1.0 - ESQ * sin(B) * sin(B);
		W1  = sqrt(W2);
		RM  = RA * (1.0 - ESQ) / W2 / W1;
		RN  = RA / W1;
	}


	void Caculate::XYZBLH(double IFLAG, double X1, double Y1,  double Z1,  double & B1, double & C1,double & H1)
	{
		double EPS ;
		double RM0, P, C0, H0, DB, RN0, ESQ;
		int I;

		EPS = 0.00000000001;//.-11

		RMN(IFLAG, m_B0, RM0, RN0, ESQ);
		P  = sqrt(X1 * X1 + Y1 * Y1);
        m_B0 = Z1 / P / (1.0 - ESQ);

		I = 0;
		DB = 1000000;
		while (DB > EPS) 
		{
  
			I++;
			RMN(IFLAG, m_B0, RM0, RN0, ESQ);
			H0 = P / cos(m_B0) - RN0;
			B1 = Z1 / P / (1.0 - ESQ * RN0 / (RN0 + H0));
			B1 = atan(B1);
			DB = abs(B1 - m_B0);
			m_B0 = B1;
		}
		//     memo2.Lines.Add('XYZBLH--->'+#9+inttostr(I)+#9+floattostrf(DB,fffixed,10,5));
		B1 = m_B0;
		C0 = atan2(Y1,X1);
		if (C0 < 0)
		{
		C0 = C0 + m_PAI * 2.0;
		}
		C1 = C0;
		H1 = H0;
	}

	void Caculate::DBLFWD1(int ND, double & Bl, double &Cl, double &X, double &Y, double &m_B0, double &C0)
	{
		 double B, C, A, H, sinc, RR, CS, cc, CS0, bi, BS, SINB, q1, q2, r, E, RM, x1, RN, ESQ, BS0, U, CAPA;
		 int i;

		 m_PAI4 = atan(1.0);

		  RMN(2, m_B0, RM, RN, ESQ);
		  RR = sqrt(RM * RN);
		  E  = sqrt(ESQ);

		  ORIGIN(m_B0, BS0, ESQ, U, CAPA);//  ! BS0 :PROJ. ORIGIN ON THE SPHERE

		  B  = Bl;
		  C  = Cl;
		  SINB = sin(B);
		  BS = CAPA * pow(((1.0 - E * SINB) / (1.0 + E * SINB)), (U * E / 2.0));

		  BS = BS * pow(((1.0 + SINB) / (1.0 - SINB)), (U / 2.0));
		  BS = 2.0 * atan(BS) - m_PAI4 * 2.0;
		  CS = U * C;

		  CS0 = U * C0;



		  H = cos(BS) * sin(CS - CS0);      //    ! D_LON (Y)
		  H = asin(H);
		  A = tan(BS) / cos(CS - CS0);        //  ! D_LAT (X)
		  A = atan(A);
		  //      X[I]:=RR*(A-BS0);
		  //      Y[I]:=RR*LOG10(tan(PAI4+H/2.0));
		  X = RR * (A - BS0);

		 // Y = RR * logN(exp(1), tan(m_PAI4 + H / 2.0));
		  Y = RR * log(tan(m_PAI4 + H / 2.0));
  //      end;
	}

	void Caculate::ORIGIN(double & m_B0,double & BS0, double &ESQ, double &U, double &CAPA)
	{
		double PAI4, E, E2SQ, SINB0;

		PAI4 = atan(1.0);
		E2SQ = ESQ / (1.0 - ESQ);
		E = sqrt(ESQ);
		U = 1.0 + E2SQ * pow(cos(m_B0), 4);
		U = sqrt(U);
		BS0 = asin(sin(m_B0) / U);

		SINB0 = sin(m_B0);//                                   ! YANG (NISSOKU)
		CAPA  = tan(PAI4 + BS0 / 2.0);
		CAPA  = CAPA * pow(((1.0 + E * SINB0) / (1.0 - E * SINB0)), (U * E / 2.0));
		CAPA  = CAPA * pow(((1.0 - SINB0) / (1.0 + SINB0)), (U / 2.0));
	}

};
