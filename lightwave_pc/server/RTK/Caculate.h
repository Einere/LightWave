#pragma once


namespace GlobalUtil
{
	class Caculate
	{
		/*
	protected:
		static Caculate* m_pThis;

	public:
		static Caculate* GetInstance();
		static void ReleaseInstance();
		*/

	public:
		static double m_PAI;
		static double m_RAD1;
		static double m_FP4;
		static double m_FP5;
		static double m_FP6;
		static double m_FP7;
		static double m_PAI4; 
		static double m_B0;

	public:


		static void CalcCoord(double orgin, double dLatitude, double dLongitude, double &Xx, double &Yy);
		static void travers_coord(double a, double e2, double K0, double phi0, double lamda0, double phi, double lamda,
								 double &X, double &Y, double &K, double &Cov);

		static double DMS(double Xx);
		static double GPS_DECODE(double Xx);
		static double cRAD(double Xx);
		static void transCoord(double wb, double wl, double &Xx, double &Yy);
		static void TRANSF(double wlat, double wlon, double wh, double &blat, double &blon, double &bh);
		static void MAP11(int ND, int IBL, double &B, double &C, double &C0, double &X, double &Y);
		static void DMS_Dev(double DEGRAD, double &JD, double &JM, double &DS);
		static void BLHXYZ(double IFLAG, double B, double c, double h, double &X, double &Y, double &Z);
		static void RMN(double IFLAG, double B, double & RM, double & RN, double & ESQ);
		static void XYZBLH(double IFLAG, double X1, double Y1,  double Z1,  double & B1, double & C1,double & H1);
		static void DBLFWD1(int ND, double & Bl, double &Cl, double &X, double &Y, double &B0, double &C0);
		static void ORIGIN(double & B0,double & BS0, double &ESQ, double &U, double &CAPA);
	};
};

