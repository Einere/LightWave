/********************************************************************
* VeCAD version 6
* Copyright (c) 2003-2005 by Oleg Kolbaskin.
* All rights reserved.
*
* This file must be included in C++ project
* that used library Vecad.dll
* This file makes dynamic linking with VeCAD functions.
*
* Visual C++ applications can not include this file,
* but use cad.lib file instead
********************************************************************/
#include "stdafx.h"
#include <windows.h>

#include "cadapi.h"


namespace CadApi
{
	static HINSTANCE ghLibInst=0;

	BOOL CadLoadLibrary()
	{
	  ghLibInst = LoadLibrary( "vecad.dll" );
	  return (ghLibInst)? TRUE : FALSE;
	}

	VOID CadFreeLibrary()
	{
	  FreeLibrary( ghLibInst );
	  ghLibInst = 0;
	}

	typedef BOOL (CADAPI *tfCadRegistration)(int RegCode);
	typedef int (CADAPI *tfCadGetVersion)(TCHAR* szVer);
	typedef void (CADAPI *tfCadOnEventMouseMove)(F_MOUSEMOVE pFunc);
	typedef void (CADAPI *tfCadOnEventMouseDown)(F_MOUSEDOWN pFunc);
	typedef void (CADAPI *tfCadOnEventMouseUp)(F_MOUSEUP pFunc);
	typedef void (CADAPI *tfCadOnEventMouseDblClk)(F_MOUSEDBLCLK pFunc);
	typedef void (CADAPI *tfCadOnEventMouseWheel)(F_MOUSEWHEEL pFunc);
	typedef void (CADAPI *tfCadOnEventMouseSnap)(F_MOUSESNAP pFunc);
	typedef void (CADAPI *tfCadOnEventKeyDown)(F_KEYDOWN pFunc);
	typedef void (CADAPI *tfCadOnEventRegen)(F_REGEN pFunc);
	typedef void (CADAPI *tfCadOnEventLoadSave)(F_LOADSAVE pFunc);
	typedef void (CADAPI *tfCadOnEventDistance)(F_DISTANCE pFunc);
	typedef void (CADAPI *tfCadOnEventArea)(F_AREA pFunc);
	typedef void (CADAPI *tfCadOnEventPrompt)(F_PROMPT pFunc);
	typedef void (CADAPI *tfCadOnEventSelPage)(F_SELPAGE pFunc);
	typedef void (CADAPI *tfCadOnEventSelCodepage)(F_SELCODEPAGE pFunc);
	typedef void (CADAPI *tfCadOnEventFontReplace)(F_FONTREPLACE pFunc);
	typedef void (CADAPI *tfCadOnEventPaint)(F_PAINT pFunc);
	typedef void (CADAPI *tfCadOnEventView)(F_VIEW pFunc);
	typedef void (CADAPI *tfCadOnEventDrawImage)(F_DRAWIMAGE pFunc);
	typedef void (CADAPI *tfCadOnEventSaveDib)(F_SAVEDIB pFunc);
	typedef void (CADAPI *tfCadOnEventEntCreate)(F_ENTCREATE pFunc);
	typedef void (CADAPI *tfCadOnEventEntLoad)(F_ENTLOAD pFunc);
	typedef void (CADAPI *tfCadOnEventEntCopy)(F_ENTCOPY pFunc);
	typedef void (CADAPI *tfCadOnEventEntErase)(F_ENTERASE pFunc);
	typedef void (CADAPI *tfCadOnEventEntMove)(F_ENTMOVE pFunc);
	typedef void (CADAPI *tfCadOnEventEntRotate)(F_ENTROTATE pFunc);
	typedef void (CADAPI *tfCadOnEventEntScale)(F_ENTSCALE pFunc);
	typedef void (CADAPI *tfCadOnEventEntChange)(F_ENTCHANGE pFunc);
	typedef void (CADAPI *tfCadOnEventEntSelect)(F_ENTSELECT pFunc);
	typedef void (CADAPI *tfCadOnEventPlineInsVer)(F_PLINEINSVER pFunc);
	typedef void (CADAPI *tfCadOnEventPlineDelVer)(F_PLINEDELVER pFunc);
	typedef void (CADAPI *tfCadOnEventPlineEditVer)(F_PLINEEDITVER pFunc);
	typedef void (CADAPI *tfCadOnEventExecute)(F_EXECUTE pFunc);
	typedef void (CADAPI *tfCadOnEventGripDrag)(F_GRIPDRAG pFunc);
	typedef void (CADAPI *tfCadOnEventGripMove)(F_GRIPMOVE pFunc);
	typedef void (CADAPI *tfCadOnEventCmdStart)(F_CMDSTART pFunc);
	typedef void (CADAPI *tfCadOnEventCmdLBDown)(F_CMDLBDOWN pFunc);
	typedef void (CADAPI *tfCadOnEventCmdFinish)(F_CMDFINISH pFunc);
	typedef void (CADAPI *tfCadOnEventEngrave)(F_ENGRAVE pFunc);
	typedef void (CADAPI *tfCadOnEventPolyFill)(F_POLYFILL pFunc, BOOL bText);
	typedef void (CADAPI *tfCadOnEventBlockCreate)(F_BLOCKCREATE pFunc);
	typedef void (CADAPI *tfCadOnEventCEntGetName)(F_CE_GETNAME pFunc);
	typedef void (CADAPI *tfCadOnEventCEntGetProps)(F_CE_GETPROPS pFunc);
	typedef void (CADAPI *tfCadOnEventCEntPutProp)(F_CE_PUTPROP pFunc);
	typedef void (CADAPI *tfCadOnEventCEntGetExts)(F_CE_GETEXTS pFunc);
	typedef void (CADAPI *tfCadOnEventCEntNumGrips)(F_CE_NGRIPS pFunc);
	typedef void (CADAPI *tfCadOnEventCEntGetGrip)(F_CE_GETGRIP pFunc);
	typedef void (CADAPI *tfCadOnEventCEntMoveGrip)(F_CE_MOVEGRIP pFunc);
	typedef void (CADAPI *tfCadOnEventCEntMove)(F_CE_MOVE pFunc);
	typedef void (CADAPI *tfCadOnEventCEntRotate)(F_CE_ROTATE pFunc);
	typedef void (CADAPI *tfCadOnEventCEntScale)(F_CE_SCALE pFunc);
	typedef void (CADAPI *tfCadOnEventCEntMirror)(F_CE_MIRROR pFunc);
	typedef void (CADAPI *tfCadOnEventCEntDisplay)(F_CE_DISPLAY pFunc);
	typedef void (CADAPI *tfCadOnEventCCmdExecute)(F_CC_EXECUTE pFunc);
	typedef void (CADAPI *tfCadOnEventCCmdDrag)(F_CC_DRAG pFunc);
	typedef void (CADAPI *tfCadSetReturnStr)(LPCTSTR szText);
	typedef void (CADAPI *tfCadSetReturnInt)(int val);
	typedef void (CADAPI *tfCadSetReturnDbl)(double val);
	typedef double (CADAPI *tfCadGetReturnX)();
	typedef double (CADAPI *tfCadGetReturnY)();
	typedef double (CADAPI *tfCadGetReturnZ)();
	typedef double (CADAPI *tfCadGetReturnVar)();
	typedef int (CADAPI *tfCadSetParam)(int Param, int Value);
	typedef int (CADAPI *tfCadGetParam)(int Param);
	typedef void (CADAPI *tfCadSetDefaultDir)(LPCTSTR szDir);
	typedef void (CADAPI *tfCadGetDefaultDir)(TCHAR* szDir);
	typedef BOOL (CADAPI *tfCadSetDefaultFont)(LPCTSTR szFontFile);
	typedef void (CADAPI *tfCadGetDefaultFont)(TCHAR* szFontFile);
	typedef void (CADAPI *tfCadSetMsgTitle)(LPCTSTR szTitle);
	typedef void (CADAPI *tfCadSetViewCoefs)(double ZoomVal, double PanHor, double PanVer);
	typedef void (CADAPI *tfCadGetViewCoefs)(double* pZoomVal, double* pPanHor, double* pPanVer);
	typedef BOOL (CADAPI *tfCadProfileLoad)(LPCTSTR szName);
	typedef BOOL (CADAPI *tfCadProfileSave)(LPCTSTR szName);
	typedef void (CADAPI *tfCadProfileGetName)(TCHAR* szName);
	typedef COLORREF (CADAPI *tfCadSetColor)(UINT iColor, COLORREF ColorRGB);
	typedef COLORREF (CADAPI *tfCadGetColor)(UINT iColor);
	typedef UINT (CADAPI *tfCadSeekColor)(COLORREF ColorRGB);
	typedef BOOL (CADAPI *tfCadLoadColors)(LPCTSTR szFileName);
	typedef BOOL (CADAPI *tfCadSaveColors)(LPCTSTR szFileName);
	typedef COLORREF (CADAPI *tfCadColorPutRGB)(UINT iColor, COLORREF ColorRGB);
	typedef COLORREF (CADAPI *tfCadColorGetRGB)(UINT iColor);
	typedef UINT (CADAPI *tfCadColorSeek)(COLORREF ColorRGB);
	typedef HBRUSH (CADAPI *tfCadGetBrush)(UINT iColor);
	typedef HPEN (CADAPI *tfCadGetPen)(UINT iColor, int Width);
	typedef BOOL (CADAPI *tfCadGetLayerWndVisible)();
	typedef void (CADAPI *tfCadSetShowSysCursor)(BOOL bShow);
	typedef BOOL (CADAPI *tfCadGetShowSysCursor)();
	typedef void (CADAPI *tfCadSetCrossSize)(UINT Size);
	typedef UINT (CADAPI *tfCadGetCrossSize)();
	typedef void (CADAPI *tfCadSetShowCross)(BOOL bShow);
	typedef BOOL (CADAPI *tfCadGetShowCross)();
	typedef void (CADAPI *tfCadSetCurveQuality)(UINT Quality);
	typedef UINT (CADAPI *tfCadGetCurveQuality)();
	typedef void (CADAPI *tfCadSetCharQuality)(UINT Quality);
	typedef UINT (CADAPI *tfCadGetCharQuality)();
	typedef void (CADAPI *tfCadSetDrawCheckStep)(UINT Step);
	typedef UINT (CADAPI *tfCadGetDrawCheckStep)();
	typedef void (CADAPI *tfCadSetMinCharSize)(int Size);
	typedef int (CADAPI *tfCadGetMinCharSize)();
	typedef void (CADAPI *tfCadSetMinCharFSize)(int Size);
	typedef int (CADAPI *tfCadGetMinCharFSize)();
	typedef void (CADAPI *tfCadSetMinEntSize)(int Size);
	typedef int (CADAPI *tfCadGetMinEntSize)();
	typedef void (CADAPI *tfCadSetMiterLimit)(int MLimit);
	typedef int (CADAPI *tfCadGetMiterLimit)();
	typedef void (CADAPI *tfCadSetAutoSel)(BOOL bAutoSel);
	typedef BOOL (CADAPI *tfCadGetAutoSel)();
	typedef void (CADAPI *tfCadSetAutoSelRect)(BOOL bAutoSelRect);
	typedef int (CADAPI *tfCadGetAutoSelRect)();
	typedef void (CADAPI *tfCadSetSelShiftAdd)(BOOL bSelShiftAdd);
	typedef BOOL (CADAPI *tfCadGetSelShiftAdd)();
	typedef void (CADAPI *tfCadSetSelInside)(BOOL bSelInside);
	typedef BOOL (CADAPI *tfCadGetSelInside)();
	typedef void (CADAPI *tfCadSetSelByLayer)(BOOL bSelByLayer);
	typedef BOOL (CADAPI *tfCadGetSelByLayer)();
	typedef void (CADAPI *tfCadSetUnselAfterEdit)(BOOL bUnselAfterEdit);
	typedef BOOL (CADAPI *tfCadGetUnselAfterEdit)();
	typedef COLORREF (CADAPI *tfCadSetSelColor)(COLORREF SelColor);
	typedef COLORREF (CADAPI *tfCadGetSelColor)();
	typedef void (CADAPI *tfCadSetSelLine)(int SelLine);
	typedef int (CADAPI *tfCadGetSelLine)();
	typedef void (CADAPI *tfCadSetPickboxSize)(int PickboxSize);
	typedef int (CADAPI *tfCadGetPickboxSize)();
	typedef void (CADAPI *tfCadSetUseGrips)(BOOL bUseGrips);
	typedef BOOL (CADAPI *tfCadGetUseGrips)();
	typedef COLORREF (CADAPI *tfCadSetGripColor)(COLORREF GripColor);
	typedef COLORREF (CADAPI *tfCadGetGripColor)();
	typedef void (CADAPI *tfCadSetGripSize)(int GripSize);
	typedef int (CADAPI *tfCadGetGripSize)();
	typedef void (CADAPI *tfCadSetImageBorder)(BOOL bImgBorder);
	typedef BOOL (CADAPI *tfCadGetImageBorder)();
	typedef void (CADAPI *tfCadSetDxfDecPrec)(UINT dec);
	typedef UINT (CADAPI *tfCadGetDxfDecPrec)();
	typedef void (CADAPI *tfCadSetDxfVersion)(UINT ver);
	typedef UINT (CADAPI *tfCadGetDxfVersion)();
	typedef void (CADAPI *tfCadSetDwgVersion)(UINT ver);
	typedef UINT (CADAPI *tfCadGetDwgVersion)();
	typedef void (CADAPI *tfCadSetAngleUnit)(int uang);
	typedef int (CADAPI *tfCadGetAngleUnit)();
	typedef void (CADAPI *tfCadSetFileFilter)(int ExtType);
	typedef int (CADAPI *tfCadGetFileFilter)();
	typedef void (CADAPI *tfCadShowEmptyRect)(BOOL bShow);
	typedef void (CADAPI *tfCadSetBlinkTime)(int nMSec);
	typedef VDWG (CADAPI *tfCadCreate)();
	typedef void (CADAPI *tfCadDelete)(VDWG hDwg);
	typedef void (CADAPI *tfCadPurge)(VDWG hDwg, int Mode);
	typedef void (CADAPI *tfCadFileNew)(VDWG hDwg, HWND hWin);
	typedef BOOL (CADAPI *tfCadFileOpen)(VDWG hDwg, HWND hWin, LPCTSTR szFileName);
	typedef BOOL (CADAPI *tfCadFileOpenMem)(VDWG hDwg, HWND hWin, void* pMem);
	typedef BOOL (CADAPI *tfCadFileSave)(VDWG hDwg, HWND hWin);
	typedef BOOL (CADAPI *tfCadFileSaveAs)(VDWG hDwg, HWND hWin, LPCTSTR szFileName);
	typedef UINT (CADAPI *tfCadFileSaveMem)(VDWG hDwg, HWND hWin, void* pMem, UINT MaxSize);
	typedef BOOL (CADAPI *tfCadRasterize)(VDWG hDwg, LPCTSTR szFileName, double Left, double Bottom, double Right, double Top, double Res);
	typedef void (CADAPI *tfCadFireLoadSaveEvent)(VDWG hDwg, int Mode, int Step, int Percent);
	typedef void (CADAPI *tfCadPutOwner)(VDWG hDwg, void* pObject);
	typedef DWORD (CADAPI *tfCadGetOwner)(VDWG hDwg);
	typedef HWND (CADAPI *tfCadGetWindow)(VDWG hDwg);
	typedef void (CADAPI *tfCadPutWindow)(VDWG hDwg, HWND hWnd);
	typedef void (CADAPI *tfCadPutFileName)(VDWG hDwg, LPCTSTR szFileName);
	typedef void (CADAPI *tfCadGetFileName)(VDWG hDwg, TCHAR* szFileName);
	typedef void (CADAPI *tfCadGetShortFileName)(VDWG hDwg, TCHAR* szFileName);
	typedef double (CADAPI *tfCadGetExtentXmin)(VDWG hDwg);
	typedef double (CADAPI *tfCadGetExtentYmin)(VDWG hDwg);
	typedef double (CADAPI *tfCadGetExtentZmin)(VDWG hDwg);
	typedef double (CADAPI *tfCadGetExtentXmax)(VDWG hDwg);
	typedef double (CADAPI *tfCadGetExtentYmax)(VDWG hDwg);
	typedef double (CADAPI *tfCadGetExtentZmax)(VDWG hDwg);
	typedef double (CADAPI *tfCadGetExtentLeft)(VDWG hDwg);
	typedef double (CADAPI *tfCadGetExtentRight)(VDWG hDwg);
	typedef double (CADAPI *tfCadGetExtentTop)(VDWG hDwg);
	typedef double (CADAPI *tfCadGetExtentBottom)(VDWG hDwg);
	typedef void (CADAPI *tfCadGetExtentRect)(VDWG hDwg, double* pLeft, double* pBottom, double* pRight, double* pTop);
	typedef double (CADAPI *tfCadGetWinLeft)(VDWG hDwg);
	typedef double (CADAPI *tfCadGetWinRight)(VDWG hDwg);
	typedef double (CADAPI *tfCadGetWinTop)(VDWG hDwg);
	typedef double (CADAPI *tfCadGetWinBottom)(VDWG hDwg);
	typedef void (CADAPI *tfCadGetWinRect)(VDWG hDwg, double* pLeft, double* pBottom, double* pRight, double* pTop);
	typedef void (CADAPI *tfCadPutDrawOnlyCurLayer)(VDWG hDwg, BOOL b);
	typedef BOOL (CADAPI *tfCadGetDrawOnlyCurLayer)(VDWG hDwg);
	typedef void (CADAPI *tfCadPutReadOnly)(VDWG hDwg, BOOL b);
	typedef BOOL (CADAPI *tfCadGetReadOnly)(VDWG hDwg);
	typedef void (CADAPI *tfCadPutDirty)(VDWG hDwg, BOOL b);
	typedef BOOL (CADAPI *tfCadGetDirty)(VDWG hDwg);
	typedef void (CADAPI *tfCadPutExData)(VDWG hDwg, void* pData, int nBytes);
	typedef int (CADAPI *tfCadGetExDataSize)(VDWG hDwg);
	typedef void (CADAPI *tfCadGetExData)(VDWG hDwg, void* pData);
	typedef VHANDLE (CADAPI *tfCadGetExDataPtr)(VDWG hDwg);
	typedef void (CADAPI *tfCadPutDescr)(VDWG hDwg, LPCTSTR Str, int nChars);
	typedef int (CADAPI *tfCadGetDescrLen)(VDWG hDwg);
	typedef void (CADAPI *tfCadGetDescr)(VDWG hDwg, TCHAR* pStr);
	typedef void (CADAPI *tfCadPutPaintMark)(VDWG hDwg, BOOL b);
	typedef void (CADAPI *tfCadPutPointMode)(VDWG hDwg, int mode);
	typedef int (CADAPI *tfCadGetPointMode)(VDWG hDwg);
	typedef void (CADAPI *tfCadPutPointSize)(VDWG hDwg, double size);
	typedef double (CADAPI *tfCadGetPointSize)(VDWG hDwg);
	typedef void (CADAPI *tfCadPutDistScale)(VDWG hDwg, double Scal);
	typedef double (CADAPI *tfCadGetDistScale)(VDWG hDwg);
	typedef int (CADAPI *tfCadGetNumEntities)(VDWG hDwg);
	typedef void (CADAPI *tfCadGridPutShow)(VDWG hDwg, BOOL bShow);
	typedef BOOL (CADAPI *tfCadGridGetShow)(VDWG hDwg);
	typedef void (CADAPI *tfCadGridPutSnap)(VDWG hDwg, BOOL bSnap);
	typedef BOOL (CADAPI *tfCadGridGetSnap)(VDWG hDwg);
	typedef void (CADAPI *tfCadGridPutSize)(VDWG hDwg, double dx, double dy, double dz);
	typedef void (CADAPI *tfCadGridGetSize)(VDWG hDwg, double* pdx, double* pdy, double* pdz);
	typedef void (CADAPI *tfCadGridPutBoldStep)(VDWG hDwg, int cx, int cy, int cz);
	typedef void (CADAPI *tfCadGridGetBoldStep)(VDWG hDwg, int* pcx, int* pcy, int* pcz);
	typedef void (CADAPI *tfCadGridPutColor)(VDWG hDwg, BOOL bBold, COLORREF Color);
	typedef COLORREF (CADAPI *tfCadGridGetColor)(VDWG hDwg, BOOL bBold);
	typedef void (CADAPI *tfCadGridPutType)(VDWG hDwg, BOOL bBold, int Typ);
	typedef int (CADAPI *tfCadGridGetType)(VDWG hDwg, BOOL bBold);
	typedef void (CADAPI *tfCadGridPutLevel)(VDWG hDwg, int Level);
	typedef int (CADAPI *tfCadGridGetLevel)(VDWG hDwg);
	typedef void (CADAPI *tfCadPutLwDefault)(VDWG hDwg, int Lweight);
	typedef int (CADAPI *tfCadGetLwDefault)(VDWG hDwg);
	typedef void (CADAPI *tfCadPutLwScale)(VDWG hDwg, int Scal);
	typedef int (CADAPI *tfCadGetLwScale)(VDWG hDwg);
	typedef void (CADAPI *tfCadPutLwDisplay)(VDWG hDwg, BOOL bDisplay);
	typedef BOOL (CADAPI *tfCadGetLwDisplay)(VDWG hDwg);
	typedef void (CADAPI *tfCadSetCurLweight)(VDWG hDwg, int Lweight);
	typedef int (CADAPI *tfCadGetCurLweight)(VDWG hDwg);
	typedef void (CADAPI *tfCadSetCurColor)(VDWG hDwg, int Color);
	typedef int (CADAPI *tfCadGetCurColor)(VDWG hDwg);
	typedef void (CADAPI *tfCadSetSystemCursor)(VDWG hDwg, HCURSOR hCurs);
	typedef void (CADAPI *tfCadPolarPutOn)(VDWG hDwg, BOOL bOn);
	typedef BOOL (CADAPI *tfCadPolarGetOn)(VDWG hDwg);
	typedef void (CADAPI *tfCadPolarPutInc)(VDWG hDwg, int Angle);
	typedef int (CADAPI *tfCadPolarGetInc)(VDWG hDwg);
	typedef BOOL (CADAPI *tfCadPolarAddAngle)(VDWG hDwg, double Angle);
	typedef BOOL (CADAPI *tfCadPolarDelAngle)(VDWG hDwg, int iAngle);
	typedef double (CADAPI *tfCadPolarGetAngle)(VDWG hDwg, int iAngle);
	typedef int (CADAPI *tfCadPolarGetNumAng)(VDWG hDwg);
	typedef void (CADAPI *tfCadPolarPutAbs)(VDWG hDwg, BOOL bAbs);
	typedef BOOL (CADAPI *tfCadPolarGetAbs)(VDWG hDwg);
	typedef void (CADAPI *tfCadPolarPutDist)(VDWG hDwg, double Dist);
	typedef double (CADAPI *tfCadPolarGetDist)(VDWG hDwg);
	typedef void (CADAPI *tfCadPolarPutDistOn)(VDWG hDwg, BOOL bDist);
	typedef BOOL (CADAPI *tfCadPolarGetDistOn)(VDWG hDwg);
	typedef void (CADAPI *tfCadSnapPutOn)(VDWG hDwg, BOOL bOn);
	typedef BOOL (CADAPI *tfCadSnapGetOn)(VDWG hDwg);
	typedef void (CADAPI *tfCadSnapPutMode)(VDWG hDwg, int Mode);
	typedef int (CADAPI *tfCadSnapGetMode)(VDWG hDwg);
	typedef int (CADAPI *tfCadSnapGetIndMode)(VDWG hDwg);
	typedef BOOL (CADAPI *tfCadSetPlineMark)(VDWG hDwg, int Id, VHANDLE hEnt, double Start, double Length, COLORREF Color, int Width, BOOL bBlink);
	typedef VHANDLE (CADAPI *tfCadAddPlineMark)(VDWG hDwg, VHANDLE hEnt, double Start, double Length);
	typedef void (CADAPI *tfCadWinCreate)(VDWG hDwg, HWND hWin);
	typedef void (CADAPI *tfCadWinPaint)(VDWG hDwg, HWND hWin);
	typedef void (CADAPI *tfCadWinDraw)(VDWG hDwg, HWND hWin, HDC dc, int Left, int Top, int Right, int Bottom);
	typedef void (CADAPI *tfCadWinKeyDown)(VDWG hDwg, HWND hWin, UINT Char, UINT Flags);
	typedef void (CADAPI *tfCadWinKeyUp)(VDWG hDwg, HWND hWin, UINT Char, UINT Flags);
	typedef void (CADAPI *tfCadWinMouseMove)(VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	typedef void (CADAPI *tfCadWinMouseLeave)(VDWG hDwg, HWND hWnd);
	typedef void (CADAPI *tfCadWinMouseWheel)(VDWG hDwg, HWND hWin, UINT Flags, int zDelta, int x, int y);
	typedef void (CADAPI *tfCadWinLButtonDown)(VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	typedef void (CADAPI *tfCadWinLButtonUp)(VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	typedef void (CADAPI *tfCadWinLButtonDblClk)(VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	typedef void (CADAPI *tfCadWinRButtonDown)(VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	typedef void (CADAPI *tfCadWinRButtonUp)(VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	typedef void (CADAPI *tfCadWinMButtonDown)(VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	typedef void (CADAPI *tfCadWinMButtonUp)(VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	typedef void (CADAPI *tfCadWinHScroll)(VDWG hDwg, HWND hWin, UINT SBCode, UINT Pos);
	typedef void (CADAPI *tfCadWinVScroll)(VDWG hDwg, HWND hWin, UINT SBCode, UINT Pos);
	typedef void (CADAPI *tfCadWinSize)(VDWG hDwg, HWND hWin, UINT SizeType, int cx, int cy);
	typedef void (CADAPI *tfCadWinSetFocus)(VDWG hDwg, HWND hWin);
	typedef void (CADAPI *tfCadWinKillFocus)(VDWG hDwg, HWND hWin);
	typedef void (CADAPI *tfCadWinDestroy)(VDWG hDwg, HWND hWin);
	typedef BOOL (CADAPI *tfCadWinClose)(VDWG hDwg, HWND hWin);
	typedef BOOL (CADAPI *tfCadWinTimer)(VDWG hDwg, HWND hWin, int Id);
	typedef void (CADAPI *tfCadExecute)(VDWG hDwg, HWND hWin, int Command);
	typedef void (CADAPI *tfCadSetCmdParam)(VDWG hDwg, int Command, void* pData);
	typedef void (CADAPI *tfCadGetCmdParam)(VDWG hDwg, int Command, void* pData);
	typedef void (CADAPI *tfCadSetCmdPoint)(VDWG hDwg, double X, double Y, double Z);
	typedef VHANDLE (CADAPI *tfCadAddLayer)(VDWG hDwg, LPCTSTR szName, int Color, IDOBJ IdLtype, int Lweight);
	typedef BOOL (CADAPI *tfCadDeleteLayer)(VDWG hDwg, VHANDLE hLayer);
	typedef UINT (CADAPI *tfCadCountLayers)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetCurLayer)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadSetCurLayer)(VDWG hDwg, VHANDLE hLayer);
	typedef VHANDLE (CADAPI *tfCadSetCurLayerByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadSetCurLayerByName)(VDWG hDwg, LPCTSTR szLayerName);
	typedef VHANDLE (CADAPI *tfCadGetFirstLayer)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetNextLayer)(VDWG hDwg, VHANDLE hLayer);
	typedef VHANDLE (CADAPI *tfCadGetLayerByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadGetLayerByName)(VDWG hDwg, LPCTSTR szName);
	typedef void (CADAPI *tfCadSortLayers)(VDWG hDwg);
	typedef IDOBJ (CADAPI *tfCadLayerGetID)(VHANDLE hLayer);
	typedef void (CADAPI *tfCadLayerGetName)(VHANDLE hLayer, TCHAR* szName);
	typedef void (CADAPI *tfCadLayerPutName)(VHANDLE hLayer, LPCTSTR szName);
	typedef int (CADAPI *tfCadLayerGetColor)(VHANDLE hLayer);
	typedef void (CADAPI *tfCadLayerPutColor)(VHANDLE hLayer, int Color);
	typedef int (CADAPI *tfCadLayerGetLineweight)(VHANDLE hLayer);
	typedef void (CADAPI *tfCadLayerPutLineweight)(VHANDLE hLayer, int lw);
	typedef IDOBJ (CADAPI *tfCadLayerGetLinetypeID)(VHANDLE hLayer);
	typedef void (CADAPI *tfCadLayerPutLinetypeID)(VHANDLE hLayer, IDOBJ Id);
	typedef int (CADAPI *tfCadLayerGetLevel)(VHANDLE hLayer);
	typedef void (CADAPI *tfCadLayerPutLevel)(VHANDLE hLayer, int Level);
	typedef DWORD (CADAPI *tfCadLayerGetUserData)(VHANDLE hLayer);
	typedef void (CADAPI *tfCadLayerPutUserData)(VHANDLE hLayer, DWORD Val);
	typedef BOOL (CADAPI *tfCadLayerGetLock)(VHANDLE hLayer);
	typedef void (CADAPI *tfCadLayerPutLock)(VHANDLE hLayer, BOOL bLock);
	typedef BOOL (CADAPI *tfCadLayerGetVisible)(VHANDLE hLayer);
	typedef void (CADAPI *tfCadLayerPutVisible)(VHANDLE hLayer, BOOL bVisible);
	typedef BOOL (CADAPI *tfCadLayerGetPrintable)(VHANDLE hLayer);
	typedef void (CADAPI *tfCadLayerPutPrintable)(VHANDLE hLayer, BOOL bPrintable);
	typedef UINT (CADAPI *tfCadLayerCountEntities)(VHANDLE hLayer);
	typedef VHANDLE (CADAPI *tfCadLayerGetFirstEntity)(VHANDLE hLayer);
	typedef VHANDLE (CADAPI *tfCadLayerGetNextEntity)(VHANDLE hLayer, VHANDLE hEnt);
	typedef void (CADAPI *tfCadLayerPutDescr)(VHANDLE hLayer, LPCTSTR Str, int nChars);
	typedef int (CADAPI *tfCadLayerGetDescrLen)(VHANDLE hLayer);
	typedef void (CADAPI *tfCadLayerGetDescr)(VHANDLE hLayer, TCHAR* pStr);
	typedef BOOL (CADAPI *tfCadLayerGetDeleted)(VHANDLE hLayer);
	typedef void (CADAPI *tfCadLayerPurge)(VHANDLE hLayer);
	typedef VHANDLE (CADAPI *tfCadAddLinetype)(VDWG hDwg, LPCTSTR szName, LPCTSTR szFormat, LPCTSTR szPict);
	typedef VHANDLE (CADAPI *tfCadAddLinetypeF)(VDWG hDwg, LPCTSTR szName, LPCTSTR szFileName);
	typedef BOOL (CADAPI *tfCadDeleteLinetype)(VDWG hDwg, VHANDLE hLtype);
	typedef UINT (CADAPI *tfCadCountLinetypes)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetCurLinetype)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadSetCurLinetype)(VDWG hDwg, VHANDLE hLtype);
	typedef VHANDLE (CADAPI *tfCadSetCurLinetypeByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadSetCurLinetypeByName)(VDWG hDwg, LPCTSTR szLtypeName);
	typedef VHANDLE (CADAPI *tfCadGetFirstLinetype)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetNextLinetype)(VDWG hDwg, VHANDLE hLtype);
	typedef VHANDLE (CADAPI *tfCadGetLinetypeByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadGetLinetypeByName)(VDWG hDwg, LPCTSTR szName);
	typedef VHANDLE (CADAPI *tfCadGetLinetypeByLayer)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetLinetypeByBlock)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetLinetypeContinuous)(VDWG hDwg);
	typedef IDOBJ (CADAPI *tfCadLinetypeGetID)(VHANDLE hLtype);
	typedef void (CADAPI *tfCadLinetypeGetName)(VHANDLE hLtype, TCHAR* szName);
	typedef void (CADAPI *tfCadLinetypePutName)(VHANDLE hLtype, LPCTSTR szName);
	typedef void (CADAPI *tfCadLinetypeGetData)(VHANDLE hLtype, TCHAR* szData);
	typedef void (CADAPI *tfCadLinetypePutData)(VHANDLE hLtype, LPCTSTR szData);
	typedef BOOL (CADAPI *tfCadLinetypePutDataF)(VHANDLE hLtype, LPCTSTR szFileName);
	typedef void (CADAPI *tfCadLinetypeGetDescr)(VHANDLE hLtype, TCHAR* szDescr);
	typedef void (CADAPI *tfCadLinetypePutDescr)(VHANDLE hLtype, LPCTSTR szDescr);
	typedef double (CADAPI *tfCadLinetypeGetScale)(VHANDLE hLtype);
	typedef void (CADAPI *tfCadLinetypePutScale)(VHANDLE hLtype, double Scal);
	typedef BOOL (CADAPI *tfCadLinetypeIsByLayer)(VHANDLE hLtype);
	typedef BOOL (CADAPI *tfCadLinetypeIsByBlock)(VHANDLE hLtype);
	typedef BOOL (CADAPI *tfCadLinetypeIsContinuous)(VHANDLE hLtype);
	typedef VHANDLE (CADAPI *tfCadAddPage)(VDWG hDwg, LPCTSTR szName, int Size, int Orient, UINT Width, UINT Height);
	typedef BOOL (CADAPI *tfCadDeletePage)(VDWG hDwg, VHANDLE hPage);
	typedef UINT (CADAPI *tfCadCountPages)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetCurPage)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadSetCurPage)(VDWG hDwg, VHANDLE hPage);
	typedef VHANDLE (CADAPI *tfCadSetCurPageByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadSetCurPageByName)(VDWG hDwg, LPCTSTR szName);
	typedef VHANDLE (CADAPI *tfCadGetFirstPage)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetNextPage)(VDWG hDwg, VHANDLE hPage);
	typedef VHANDLE (CADAPI *tfCadGetPageByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadGetPageByName)(VDWG hDwg, LPCTSTR szName);
	typedef IDOBJ (CADAPI *tfCadPageGetID)(VHANDLE hPage);
	typedef void (CADAPI *tfCadPageGetName)(VHANDLE hPage, TCHAR* szName);
	typedef void (CADAPI *tfCadPagePutName)(VHANDLE hPage, LPCTSTR szName);
	typedef UINT (CADAPI *tfCadPageGetSize)(VHANDLE hPage);
	typedef void (CADAPI *tfCadPagePutSize)(VHANDLE hPage, UINT Size);
	typedef UINT (CADAPI *tfCadPageGetOrient)(VHANDLE hPage);
	typedef void (CADAPI *tfCadPagePutOrient)(VHANDLE hPage, UINT Orient);
	typedef UINT (CADAPI *tfCadPageGetWidth)(VHANDLE hPage);
	typedef void (CADAPI *tfCadPagePutWidth)(VHANDLE hPage, UINT Width);
	typedef UINT (CADAPI *tfCadPageGetHeight)(VHANDLE hPage);
	typedef void (CADAPI *tfCadPagePutHeight)(VHANDLE hPage, UINT Height);
	typedef BOOL (CADAPI *tfCadPageSave)(VDWG hDwg, VHANDLE hPage, LPCTSTR szFileName);
	typedef BOOL (CADAPI *tfCadPageCopy)(VDWG hSrcDwg, VHANDLE hSrcPage, VDWG hDestDwg, VHANDLE hDestPage);
	typedef VHANDLE (CADAPI *tfCadAddTStyle)(VDWG hDwg, LPCTSTR szName, LPCTSTR szFontName);
	typedef BOOL (CADAPI *tfCadDeleteTStyle)(VDWG hDwg, VHANDLE hTStyle);
	typedef UINT (CADAPI *tfCadCountTStyles)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetCurTStyle)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadSetCurTStyle)(VDWG hDwg, VHANDLE hTStyle);
	typedef VHANDLE (CADAPI *tfCadSetCurTStyleByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadSetCurTStyleByName)(VDWG hDwg, LPCTSTR szName);
	typedef VHANDLE (CADAPI *tfCadGetFirstTStyle)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetNextTStyle)(VDWG hDwg, VHANDLE hTStyle);
	typedef VHANDLE (CADAPI *tfCadGetTStyleByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadGetTStyleByName)(VDWG hDwg, LPCTSTR szName);
	typedef IDOBJ (CADAPI *tfCadTStyleGetID)(VHANDLE hTStyle);
	typedef void (CADAPI *tfCadTStyleGetName)(VHANDLE hTStyle, TCHAR* szName);
	typedef void (CADAPI *tfCadTStylePutName)(VHANDLE hTStyle, LPCTSTR szName);
	typedef double (CADAPI *tfCadTStyleGetOblique)(VHANDLE hTStyle);
	typedef void (CADAPI *tfCadTStylePutOblique)(VHANDLE hTStyle, double Angle);
	typedef double (CADAPI *tfCadTStyleGetWidth)(VHANDLE hTStyle);
	typedef void (CADAPI *tfCadTStylePutWidth)(VHANDLE hTStyle, double Width);
	typedef double (CADAPI *tfCadTStyleGetHeight)(VHANDLE hTStyle);
	typedef void (CADAPI *tfCadTStylePutHeight)(VHANDLE hTStyle, double Height);
	typedef BOOL (CADAPI *tfCadTStyleGetUpsideDown)(VHANDLE hTStyle);
	typedef void (CADAPI *tfCadTStylePutUpsideDown)(VHANDLE hTStyle, BOOL bUpsideDown);
	typedef BOOL (CADAPI *tfCadTStyleGetBackward)(VHANDLE hTStyle);
	typedef void (CADAPI *tfCadTStylePutBackward)(VHANDLE hTStyle, BOOL bBackward);
	typedef void (CADAPI *tfCadTStyleGetFont)(VHANDLE hTStyle, TCHAR* szFontName);
	typedef void (CADAPI *tfCadTStylePutFont)(VHANDLE hTStyle, LPCTSTR szFontName);
	typedef void (CADAPI *tfCadTStyleGetTTFName)(VHANDLE hTStyle, TCHAR* szTTFName);
	typedef void (CADAPI *tfCadTStylePutTTFName)(VHANDLE hTStyle, LPCTSTR szTTFName);
	typedef VHANDLE (CADAPI *tfCadAddBlock)(VDWG hDwg, LPCTSTR szName, double X, double Y, double Z);
	typedef VHANDLE (CADAPI *tfCadAddBlockFromFile)(VDWG hDwg, LPCTSTR szFileName, LPCTSTR szName);
	typedef VHANDLE (CADAPI *tfCadAddBlockFromDrw)(VDWG hDwgDest, VDWG hDwgSrc, LPCTSTR szName);
	typedef VHANDLE (CADAPI *tfCadAddBlockFile)(VDWG hDwg, LPCTSTR szFileName);
	typedef VHANDLE (CADAPI *tfCadAddBlockXref)(VDWG hDwg, LPCTSTR szFileName);
	typedef VHANDLE (CADAPI *tfCadAddBlockClip)(VDWG hDwg, LPCTSTR szName, double Lef, double Bot, double W, double H);
	typedef BOOL (CADAPI *tfCadDeleteBlock)(VDWG hDwg, VHANDLE hBlock);
	typedef UINT (CADAPI *tfCadCountBlocks)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetFirstBlock)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetNextBlock)(VDWG hDwg, VHANDLE hBlock);
	typedef VHANDLE (CADAPI *tfCadGetBlockByID)(VDWG hDwg, IDOBJ idBlock);
	typedef VHANDLE (CADAPI *tfCadGetBlockByName)(VDWG hDwg, LPCTSTR szName);
	typedef VHANDLE (CADAPI *tfCadGetCurBlock)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadSetCurBlock)(VDWG hDwg, VHANDLE hBlock);
	typedef IDOBJ (CADAPI *tfCadBlockGetID)(VHANDLE hBlock);
	typedef void (CADAPI *tfCadBlockGetName)(VHANDLE hBlock, TCHAR* szName);
	typedef BOOL (CADAPI *tfCadBlockPutName)(VHANDLE hBlock, LPCTSTR szName);
	typedef double (CADAPI *tfCadBlockGetBaseX)(VHANDLE hBlock);
	typedef void (CADAPI *tfCadBlockPutBaseX)(VHANDLE hBlock, double X);
	typedef double (CADAPI *tfCadBlockGetBaseY)(VHANDLE hBlock);
	typedef void (CADAPI *tfCadBlockPutBaseY)(VHANDLE hBlock, double Y);
	typedef double (CADAPI *tfCadBlockGetBaseZ)(VHANDLE hBlock);
	typedef void (CADAPI *tfCadBlockPutBaseZ)(VHANDLE hBlock, double Z);
	typedef void (CADAPI *tfCadBlockGetBase)(VHANDLE hBlock, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadBlockPutBase)(VHANDLE hBlock, double X, double Y, double Z);
	typedef UINT (CADAPI *tfCadBlockCountEntities)(VHANDLE hBlock);
	typedef void (CADAPI *tfCadBlockClear)(VHANDLE hBlock);
	typedef void (CADAPI *tfCadBlockAddEntity)(VHANDLE hBlock, VHANDLE hEnt);
	typedef VHANDLE (CADAPI *tfCadBlockGetFirstPtr)(VHANDLE hBlock);
	typedef VHANDLE (CADAPI *tfCadBlockGetNextPtr)(VHANDLE hBlock, VHANDLE hPtr);
	typedef BOOL (CADAPI *tfCadBlockHasAttribs)(VHANDLE hBlock);
	typedef VHANDLE (CADAPI *tfCadBlockGetAttrib)(VHANDLE hBlock, LPCTSTR szTag);
	typedef BOOL (CADAPI *tfCadBlockIsXref)(VHANDLE hBlock);
	typedef void (CADAPI *tfCadXrefGetPath)(VHANDLE hBlock, TCHAR* szPathName);
	typedef BOOL (CADAPI *tfCadXrefPutPath)(VHANDLE hBlock, LPCTSTR szPathName);
	typedef BOOL (CADAPI *tfCadXrefReload)(VHANDLE hBlock);
	typedef int (CADAPI *tfCadXrefGetStatus)(VHANDLE hBlock);
	typedef void (CADAPI *tfCadBlockPutExData)(VHANDLE hBlock, void* pData, int nBytes);
	typedef int (CADAPI *tfCadBlockGetExDataSize)(VHANDLE hBlock);
	typedef void (CADAPI *tfCadBlockGetExData)(VHANDLE hBlock, void* pData);
	typedef VHANDLE (CADAPI *tfCadAddPntStyle)(VDWG hDwg, LPCTSTR szName, IDOBJ BlockId, double BlockScale, LPCTSTR szFontName, double TxtH, double TxtW);
	typedef BOOL (CADAPI *tfCadDeletePntStyle)(VDWG hDwg, VHANDLE hPntStyle);
	typedef UINT (CADAPI *tfCadCountPntStyles)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetCurPntStyle)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadSetCurPntStyle)(VDWG hDwg, VHANDLE hPntStyle);
	typedef VHANDLE (CADAPI *tfCadSetCurPntStyleByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadSetCurPntStyleByName)(VDWG hDwg, LPCTSTR szName);
	typedef VHANDLE (CADAPI *tfCadGetFirstPntStyle)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetNextPntStyle)(VDWG hDwg, VHANDLE hPntStyle);
	typedef VHANDLE (CADAPI *tfCadGetPntStyleByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadGetPntStyleByName)(VDWG hDwg, LPCTSTR szName);
	typedef IDOBJ (CADAPI *tfCadPntStyleGetID)(VHANDLE hPntStyle);
	typedef void (CADAPI *tfCadPntStyleGetName)(VHANDLE hPntStyle, TCHAR* szName);
	typedef void (CADAPI *tfCadPntStylePutName)(VHANDLE hPntStyle, LPCTSTR szName);
	typedef IDOBJ (CADAPI *tfCadPntStyleGetBlockID)(VHANDLE hPntStyle);
	typedef void (CADAPI *tfCadPntStylePutBlockID)(VHANDLE hPntStyle, IDOBJ IdBlock);
	typedef double (CADAPI *tfCadPntStyleGetBlockScale)(VHANDLE hPntStyle);
	typedef void (CADAPI *tfCadPntStylePutBlockScale)(VHANDLE hPntStyle, double Scal);
	typedef void (CADAPI *tfCadPntStyleGetFont)(VHANDLE hPntStyle, TCHAR* szFontName);
	typedef void (CADAPI *tfCadPntStylePutFont)(VHANDLE hPntStyle, LPCTSTR szFontName);
	typedef double (CADAPI *tfCadPntStyleGetTextHeight)(VHANDLE hPntStyle);
	typedef void (CADAPI *tfCadPntStylePutTextHeight)(VHANDLE hPntStyle, double TxtH);
	typedef double (CADAPI *tfCadPntStyleGetTextWidth)(VHANDLE hPntStyle);
	typedef void (CADAPI *tfCadPntStylePutTextWidth)(VHANDLE hPntStyle, double TxtW);
	typedef int (CADAPI *tfCadPntStyleGetDrawMode)(VHANDLE hPntStyle);
	typedef void (CADAPI *tfCadPntStylePutDrawMode)(VHANDLE hPntStyle, int Mode);
	typedef BOOL (CADAPI *tfCadPntStyleGetSnap)(VHANDLE hPntStyle);
	typedef void (CADAPI *tfCadPntStylePutSnap)(VHANDLE hPntStyle, BOOL bSnap);
	typedef BOOL (CADAPI *tfCadPntStyleGetFixed)(VHANDLE hPntStyle);
	typedef void (CADAPI *tfCadPntStylePutFixed)(VHANDLE hPntStyle, BOOL bFixed);
	typedef VHANDLE (CADAPI *tfCadAddMlineStyle)(VDWG hDwg, LPCTSTR szName);
	typedef BOOL (CADAPI *tfCadDeleteMlineStyle)(VDWG hDwg, VHANDLE hMStyle);
	typedef UINT (CADAPI *tfCadCountMlineStyles)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetCurMlineStyle)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadSetCurMlineStyle)(VDWG hDwg, VHANDLE hMStyle);
	typedef VHANDLE (CADAPI *tfCadSetCurMlineStyleByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadSetCurMlineStyleByName)(VDWG hDwg, LPCTSTR szName);
	typedef VHANDLE (CADAPI *tfCadGetFirstMlineStyle)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetNextMlineStyle)(VDWG hDwg, VHANDLE hMStyle);
	typedef VHANDLE (CADAPI *tfCadGetMlineStyleByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadGetMlineStyleByName)(VDWG hDwg, LPCTSTR szName);
	typedef IDOBJ (CADAPI *tfCadMlineStyleGetID)(VHANDLE hMStyle);
	typedef void (CADAPI *tfCadMlineStyleGetName)(VHANDLE hMStyle, TCHAR* szName);
	typedef void (CADAPI *tfCadMlineStylePutName)(VHANDLE hMStyle, LPCTSTR szName);
	typedef UINT (CADAPI *tfCadMlineStyleGetDrawMode)(VHANDLE hMStyle);
	typedef void (CADAPI *tfCadMlineStylePutDrawMode)(VHANDLE hMStyle, UINT Mode);
	typedef UINT (CADAPI *tfCadMlineStyleGetNumLines)(VHANDLE hMStyle);
	typedef void (CADAPI *tfCadMlineStylePutNumLines)(VHANDLE hMStyle, UINT nLines);
	typedef int (CADAPI *tfCadMlineStyleGetColor)(VHANDLE hMStyle, UINT iLine);
	typedef void (CADAPI *tfCadMlineStylePutColor)(VHANDLE hMStyle, UINT iLine, int Color);
	typedef IDOBJ (CADAPI *tfCadMlineStyleGetLtypeID)(VHANDLE hMStyle, UINT iLine);
	typedef void (CADAPI *tfCadMlineStylePutLtypeID)(VHANDLE hMStyle, UINT iLine, IDOBJ Id);
	typedef double (CADAPI *tfCadMlineStyleGetOffset)(VHANDLE hMStyle, UINT iLine);
	typedef void (CADAPI *tfCadMlineStylePutOffset)(VHANDLE hMStyle, UINT iLine, double Offset);
	typedef VHANDLE (CADAPI *tfCadAddDimStyle)(VDWG hDwg, LPCTSTR szName);
	typedef BOOL (CADAPI *tfCadDeleteDimStyle)(VDWG hDwg, VHANDLE hStyle);
	typedef UINT (CADAPI *tfCadCountDimStyles)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetCurDimStyle)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadSetCurDimStyle)(VDWG hDwg, VHANDLE hStyle);
	typedef VHANDLE (CADAPI *tfCadSetCurDimStyleByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadSetCurDimStyleByName)(VDWG hDwg, LPCTSTR szName);
	typedef VHANDLE (CADAPI *tfCadGetFirstDimStyle)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetNextDimStyle)(VDWG hDwg, VHANDLE hStyle);
	typedef VHANDLE (CADAPI *tfCadGetDimStyleByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadGetDimStyleByName)(VDWG hDwg, LPCTSTR szName);
	typedef IDOBJ (CADAPI *tfCadDimStyleGetID)(VHANDLE hStyle);
	typedef void (CADAPI *tfCadDimStyleGetName)(VHANDLE hStyle, TCHAR* szName);
	typedef void (CADAPI *tfCadDimStylePutName)(VHANDLE hStyle, LPCTSTR szName);
	typedef int (CADAPI *tfCadDimStyleGetColor)(VHANDLE hStyle, int Item);
	typedef void (CADAPI *tfCadDimStylePutColor)(VHANDLE hStyle, int Item, int Color);
	typedef int (CADAPI *tfCadDimStyleGetLweight)(VHANDLE hStyle, int Item);
	typedef void (CADAPI *tfCadDimStylePutLweight)(VHANDLE hStyle, int Item, int Lweight);
	typedef double (CADAPI *tfCadDimStyleGetExtBeyond)(VHANDLE hStyle);
	typedef void (CADAPI *tfCadDimStylePutExtBeyond)(VHANDLE hStyle, double val);
	typedef double (CADAPI *tfCadDimStyleGetExtOffset)(VHANDLE hStyle);
	typedef void (CADAPI *tfCadDimStylePutExtOffset)(VHANDLE hStyle, double val);
	typedef int (CADAPI *tfCadDimStyleGetArrow)(VHANDLE hStyle, int Place);
	typedef void (CADAPI *tfCadDimStylePutArrow)(VHANDLE hStyle, int Place, int ArrType);
	typedef double (CADAPI *tfCadDimStyleGetArrowSize)(VHANDLE hStyle);
	typedef void (CADAPI *tfCadDimStylePutArrowSize)(VHANDLE hStyle, double Size);
	typedef double (CADAPI *tfCadDimStyleGetCenMark)(VHANDLE hStyle);
	typedef void (CADAPI *tfCadDimStylePutCenMark)(VHANDLE hStyle, double Size);
	typedef double (CADAPI *tfCadDimStyleGetTextHeight)(VHANDLE hStyle);
	typedef void (CADAPI *tfCadDimStylePutTextHeight)(VHANDLE hStyle, double Height);
	typedef double (CADAPI *tfCadDimStyleGetTextGap)(VHANDLE hStyle);
	typedef void (CADAPI *tfCadDimStylePutTextGap)(VHANDLE hStyle, double Gap);
	typedef IDOBJ (CADAPI *tfCadDimStyleGetTextStyleID)(VHANDLE hStyle);
	typedef void (CADAPI *tfCadDimStylePutTextStyleID)(VHANDLE hStyle, IDOBJ Id);
	typedef UINT (CADAPI *tfCadDimStyleGetTextPlace)(VHANDLE hStyle);
	typedef void (CADAPI *tfCadDimStylePutTextPlace)(VHANDLE hStyle, UINT Placement);
	typedef double (CADAPI *tfCadDimStyleGetScale)(VHANDLE hStyle);
	typedef void (CADAPI *tfCadDimStylePutScale)(VHANDLE hStyle, double Scal);
	typedef double (CADAPI *tfCadDimStyleGetRound)(VHANDLE hStyle);
	typedef void (CADAPI *tfCadDimStylePutRound)(VHANDLE hStyle, double RoundOff);
	typedef int (CADAPI *tfCadDimStyleGetUnits)(VHANDLE hStyle, BOOL bAngular);
	typedef void (CADAPI *tfCadDimStylePutUnits)(VHANDLE hStyle, BOOL bAngular, int UnitsType);
	typedef int (CADAPI *tfCadDimStyleGetPrecision)(VHANDLE hStyle, BOOL bAngular);
	typedef void (CADAPI *tfCadDimStylePutPrecision)(VHANDLE hStyle, BOOL bAngular, int Prec);
	typedef BOOL (CADAPI *tfCadDimStyleGetZeroSup)(VHANDLE hStyle, BOOL bAngular);
	typedef void (CADAPI *tfCadDimStylePutZeroSup)(VHANDLE hStyle, BOOL bAngular, BOOL bSuppress);
	typedef int (CADAPI *tfCadDimStyleGetSeparator)(VHANDLE hStyle);
	typedef void (CADAPI *tfCadDimStylePutSeparator)(VHANDLE hStyle, int DecSep);
	typedef void (CADAPI *tfCadDimStyleGetPrefix)(VHANDLE hStyle, TCHAR* szPrefix);
	typedef void (CADAPI *tfCadDimStylePutPrefix)(VHANDLE hStyle, LPCTSTR szPrefix);
	typedef void (CADAPI *tfCadDimStyleGetSuffix)(VHANDLE hStyle, TCHAR* szSuffix);
	typedef void (CADAPI *tfCadDimStylePutSuffix)(VHANDLE hStyle, LPCTSTR szSuffix);
	typedef VHANDLE (CADAPI *tfCadGetEntityByCursor)(VDWG hDwg);
	typedef void (CADAPI *tfCadGetEntitiesByPoint)(VDWG hDwg, int Xwin, int Ywin, int* phEnt, int* pnEnts, int iMax);
	typedef void (CADAPI *tfCadGetEntitiesByRect)(VDWG hDwg, int Lwin, int Twin, int Rwin, int Bwin, int* phEnt, int* pnEnts, int nMax);
	typedef VHANDLE (CADAPI *tfCadGetEntityByPoint)(VDWG hDwg, int Xwin, int Ywin);
	typedef VHANDLE (CADAPI *tfCadGetEntityByPointIn)(VDWG hDwg, double Xdisp, double Ydisp);
	typedef VHANDLE (CADAPI *tfCadGetEntityByID)(VDWG hDwg, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadGetEntityByUserData)(VDWG hDwg, DWORD UserData);
	typedef VHANDLE (CADAPI *tfCadGetEntityByPtr)(VHANDLE hPtr);
	typedef VHANDLE (CADAPI *tfCadGetFirstEntity)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetNextEntity)(VDWG hDwg, VHANDLE hEnt);
	typedef VHANDLE (CADAPI *tfCadGetPickEntity)(VDWG hDwg);
	typedef IDOBJ (CADAPI *tfCadEntityGetID)(VHANDLE hEnt);
	typedef DWORD (CADAPI *tfCadEntityGetType)(VHANDLE hEnt);
	typedef double (CADAPI *tfCadEntityGetLeft)(VHANDLE hEnt);
	typedef double (CADAPI *tfCadEntityGetBottom)(VHANDLE hEnt);
	typedef double (CADAPI *tfCadEntityGetRight)(VHANDLE hEnt);
	typedef double (CADAPI *tfCadEntityGetTop)(VHANDLE hEnt);
	typedef int (CADAPI *tfCadEntityGetNumPaths)(VHANDLE hEnt);
	typedef int (CADAPI *tfCadEntityGetPathSize)(VHANDLE hEnt, int iPath);
	typedef void (CADAPI *tfCadEntityGetVer)(VHANDLE hEnt, int iVer, double* pX, double* pY);
	typedef BOOL (CADAPI *tfCadEntityGetGrip)(VHANDLE hEnt, int iGrip, double* pX, double* pY, double* pZ);
	typedef IDOBJ (CADAPI *tfCadEntityGetLayerID)(VHANDLE hEnt);
	typedef BOOL (CADAPI *tfCadEntityPutLayerID)(VHANDLE hEnt, VDWG hDwg, IDOBJ LayerID);
	typedef IDOBJ (CADAPI *tfCadEntityGetPageID)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutPageID)(VHANDLE hEnt, IDOBJ PageID);
	typedef IDOBJ (CADAPI *tfCadEntityGetLinetypeID)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutLinetypeID)(VHANDLE hEnt, IDOBJ Id);
	typedef double (CADAPI *tfCadEntityGetLtScale)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutLtScale)(VHANDLE hEnt, double lts);
	typedef int (CADAPI *tfCadEntityGetColor)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutColor)(VHANDLE hEnt, int Color);
	typedef DWORD (CADAPI *tfCadEntityGetLineweight)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutLineweight)(VHANDLE hEnt, int lw);
	typedef DWORD (CADAPI *tfCadEntityGetUserData)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutUserData)(VHANDLE hEnt, DWORD val);
	typedef BOOL (CADAPI *tfCadEntityGetFilled)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutFilled)(VHANDLE hEnt, BOOL bFilled);
	typedef BOOL (CADAPI *tfCadEntityGetBorder)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutBorder)(VHANDLE hEnt, BOOL bBorder);
	typedef int (CADAPI *tfCadEntityGetBordColor)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutBordColor)(VHANDLE hEnt, int Color);
	typedef BOOL (CADAPI *tfCadEntityGetBlink)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutBlink)(VHANDLE hEnt, BOOL bBlink);
	typedef BOOL (CADAPI *tfCadEntityGetVisible)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutVisible)(VHANDLE hEnt, BOOL bVisible);
	typedef BOOL (CADAPI *tfCadEntityGetDeleted)(VHANDLE hEnt);
	typedef BOOL (CADAPI *tfCadEntityGetSelected)(VDWG hDwg, VHANDLE hEnt);
	typedef BOOL (CADAPI *tfCadEntityGetLocked)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutLocked)(VHANDLE hEnt, BOOL bLock);
	typedef void (CADAPI *tfCadEntityPutExData)(VHANDLE hEnt, void* pData, int nBytes);
	typedef int (CADAPI *tfCadEntityGetExDataSize)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityGetExData)(VHANDLE hEnt, void* pData);
	typedef VHANDLE (CADAPI *tfCadEntityGetExDataPtr)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityPutParkData)(VHANDLE hEnt, LPCTSTR szPark, LPCTSTR szWay);
	typedef BOOL (CADAPI *tfCadEntityGetParkData)(VHANDLE hEnt, TCHAR* szPark, TCHAR* szWay);
	typedef void (CADAPI *tfCadEntityErase)(VHANDLE hEnt, BOOL bErase);
	typedef VHANDLE (CADAPI *tfCadEntityCopy)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityMove)(VHANDLE hEnt, double dx, double dy, double dz);
	typedef void (CADAPI *tfCadEntityMoveGrip)(VHANDLE hEnt, int iGrip, double dx, double dy, double dz);
	typedef void (CADAPI *tfCadEntityScale)(VHANDLE hEnt, double x0, double y0, double z0, double Scal);
	typedef void (CADAPI *tfCadEntityRotate)(VHANDLE hEnt, double x0, double y0, double z0, double Angle);
	typedef void (CADAPI *tfCadEntityMirror)(VHANDLE hEnt, double x0, double y0, double z0, double x1, double y1, double z1);
	typedef BOOL (CADAPI *tfCadEntityExplode)(VHANDLE hEnt, long* pnOutEnts, long* pFirstID);
	typedef BOOL (CADAPI *tfCadAddEdge)(VHANDLE hEnt);
	typedef BOOL (CADAPI *tfCadEntityTrim)(VHANDLE hEnt, double x, double y);
	typedef BOOL (CADAPI *tfCadEntityExtend)(VHANDLE hEnt, double x, double y);
	typedef void (CADAPI *tfCadEntityToTop)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntityToBottom)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadEntitySwap)(VHANDLE hEnt1, VHANDLE hEnt2);
	typedef VHANDLE (CADAPI *tfCadAddPoint)(VDWG hDwg, double X, double Y, double Z);
	typedef IDOBJ (CADAPI *tfCadPointGetStyleID)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPointPutStyleID)(VHANDLE hEnt, IDOBJ Id);
	typedef double (CADAPI *tfCadPointGetX)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPointPutX)(VHANDLE hEnt, double X);
	typedef double (CADAPI *tfCadPointGetY)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPointPutY)(VHANDLE hEnt, double Y);
	typedef double (CADAPI *tfCadPointGetZ)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPointPutZ)(VHANDLE hEnt, double Z);
	typedef void (CADAPI *tfCadPointGetCoord)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadPointPutCoord)(VHANDLE hEnt, double X, double Y, double Z);
	typedef void (CADAPI *tfCadPointGetTextOffset)(VHANDLE hEnt, double* pDX, double* pDY, double* pDZ);
	typedef void (CADAPI *tfCadPointPutTextOffset)(VHANDLE hEnt, double DX, double DY, double DZ);
	typedef double (CADAPI *tfCadPointGetTextX)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPointPutTextX)(VHANDLE hEnt, double X);
	typedef double (CADAPI *tfCadPointGetTextY)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPointPutTextY)(VHANDLE hEnt, double Y);
	typedef void (CADAPI *tfCadPointGetText)(VHANDLE hEnt, TCHAR* szText);
	typedef void (CADAPI *tfCadPointPutText)(VHANDLE hEnt, LPCTSTR szText);
	typedef double (CADAPI *tfCadPointGetTextAngle)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPointPutTextAngle)(VHANDLE hEnt, double Angle);
	typedef double (CADAPI *tfCadPointGetBlockAngle)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPointPutBlockAngle)(VHANDLE hEnt, double Angle);
	typedef VHANDLE (CADAPI *tfCadAddLine)(VDWG hDwg, double x1, double y1, double z1, double x2, double y2, double z2);
	typedef VHANDLE (CADAPI *tfCadAddXLine)(VDWG hDwg, double x, double y, double z, double dx, double dy, double dz);
	typedef VHANDLE (CADAPI *tfCadAddRay)(VDWG hDwg, double x, double y, double z, double dx, double dy, double dz);
	typedef double (CADAPI *tfCadLineGetX1)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadLinePutX1)(VHANDLE hEnt, double X);
	typedef double (CADAPI *tfCadLineGetY1)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadLinePutY1)(VHANDLE hEnt, double Y);
	typedef double (CADAPI *tfCadLineGetZ1)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadLinePutZ1)(VHANDLE hEnt, double Z);
	typedef double (CADAPI *tfCadLineGetX2)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadLinePutX2)(VHANDLE hEnt, double X);
	typedef double (CADAPI *tfCadLineGetY2)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadLinePutY2)(VHANDLE hEnt, double Y);
	typedef double (CADAPI *tfCadLineGetZ2)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadLinePutZ2)(VHANDLE hEnt, double Z);
	typedef void (CADAPI *tfCadLineGetPoint1)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadLinePutPoint1)(VHANDLE hEnt, double X, double Y, double Z);
	typedef void (CADAPI *tfCadLineGetPoint2)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadLinePutPoint2)(VHANDLE hEnt, double X, double Y, double Z);
	typedef BOOL (CADAPI *tfCadLineIsX)(VHANDLE hEnt);
	typedef BOOL (CADAPI *tfCadLineIsRay)(VHANDLE hEnt);
	typedef VHANDLE (CADAPI *tfCadAddCircle)(VDWG hDwg, double X, double Y, double Z, double Radius);
	typedef VHANDLE (CADAPI *tfCadAddCircle3P)(VDWG hDwg, double X1, double Y1, double Z, double X2, double Y2, double X3, double Y3);
	typedef VHANDLE (CADAPI *tfCadAddArc)(VDWG hDwg, double X, double Y, double Z, double Radius, double StartAngle, double ArcAngle);
	typedef VHANDLE (CADAPI *tfCadAddArc3P)(VDWG hDwg, double X1, double Y1, double Z, double X2, double Y2, double X3, double Y3);
	typedef VHANDLE (CADAPI *tfCadAddArcCSE)(VDWG hDwg, double Xc, double Yc, double Z, double Xs, double Ys, double Xe, double Ye, BOOL bCCW);
	typedef VHANDLE (CADAPI *tfCadAddArcSED)(VDWG hDwg, double Xs, double Ys, double Z, double Xe, double Ye, double DirAngle);
	typedef VHANDLE (CADAPI *tfCadAddArcContinue)(VDWG hDwg, VHANDLE hEnt, double Xe, double Ye, double Z);
	typedef VHANDLE (CADAPI *tfCadAddEllipse)(VDWG hDwg, double X, double Y, double Z, double RadH, double RadV, double RotAngle);
	typedef int (CADAPI *tfCadArcGetType)(VHANDLE hEnt);
	typedef double (CADAPI *tfCadArcGetCenterX)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadArcPutCenterX)(VHANDLE hEnt, double X);
	typedef double (CADAPI *tfCadArcGetCenterY)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadArcPutCenterY)(VHANDLE hEnt, double Y);
	typedef double (CADAPI *tfCadArcGetCenterZ)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadArcPutCenterZ)(VHANDLE hEnt, double Z);
	typedef void (CADAPI *tfCadArcGetCenter)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadArcPutCenter)(VHANDLE hEnt, double X, double Y, double Z);
	typedef double (CADAPI *tfCadArcGetRadius)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadArcPutRadius)(VHANDLE hEnt, double R);
	typedef double (CADAPI *tfCadArcGetRadHor)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadArcPutRadHor)(VHANDLE hEnt, double R);
	typedef double (CADAPI *tfCadArcGetRadVer)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadArcPutRadVer)(VHANDLE hEnt, double R);
	typedef double (CADAPI *tfCadArcGetStartAngle)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadArcPutStartAngle)(VHANDLE hEnt, double Ang);
	typedef double (CADAPI *tfCadArcGetAngle)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadArcPutAngle)(VHANDLE hEnt, double Ang);
	typedef double (CADAPI *tfCadArcGetRotAngle)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadArcPutRotAngle)(VHANDLE hEnt, double Ang);
	typedef BOOL (CADAPI *tfCadArcGetSector)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadArcPutSector)(VHANDLE hEnt, BOOL bSector);
	typedef void (CADAPI *tfCadArcGetStartPt)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef BOOL (CADAPI *tfCadArcPutStartPt)(VHANDLE hEnt, double X, double Y, double Z);
	typedef void (CADAPI *tfCadArcGetEndPt)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef BOOL (CADAPI *tfCadArcPutEndPt)(VHANDLE hEnt, double X, double Y, double Z);
	typedef void (CADAPI *tfCadArcGetMidPt)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef BOOL (CADAPI *tfCadArcPutMidPt)(VHANDLE hEnt, double X, double Y, double Z);
	typedef void (CADAPI *tfCadArcGet3Pt)(VHANDLE hEnt, double* pXsta, double* pYsta, double* pZ, double* pXmid, double* pYmid, double* pXend, double* pYend);
	typedef BOOL (CADAPI *tfCadArcPut3Pt)(VHANDLE hEnt, double Xsta, double Ysta, double Z, double Xmid, double Ymid, double Xe, double Ye);
	typedef void (CADAPI *tfCadArcDivide)(VHANDLE hEnt, int nPoints, double* X, double* Y);
	typedef void (CADAPI *tfCadClearVertices)();
	typedef void (CADAPI *tfCadAddVertex)(double X, double Y, double Z);
	typedef void (CADAPI *tfCadAddVertex2)(double X, double Y, double Z, double Prm, double StartW, double EndW);
	typedef VHANDLE (CADAPI *tfCadAddPolyline)(VDWG hDwg, int FitType, BOOL bClosed);
	typedef VHANDLE (CADAPI *tfCadAddPolylineW)(VDWG hDwg, int FitType, BOOL bClosed, double Width);
	typedef VHANDLE (CADAPI *tfCadAddPolygon)(VDWG hDwg, int Color, BOOL bBorder);
	typedef VHANDLE (CADAPI *tfCadAddBoundPolygon)(VDWG hDwg, double X, double Y, double Z);
	typedef VHANDLE (CADAPI *tfCadAddBoundary)(VDWG hDwg, double X, double Y, double Z);
	typedef BOOL (CADAPI *tfCadPlineInsertVer)(VHANDLE hEnt, UINT iVer);
	typedef BOOL (CADAPI *tfCadPlineDeleteVer)(VHANDLE hEnt, UINT iVer);
	typedef UINT (CADAPI *tfCadPlineGetNumVers)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPlinePutNumVers)(VHANDLE hEnt, UINT nVers);
	typedef double (CADAPI *tfCadPlineGetX)(VHANDLE hEnt, UINT iVer);
	typedef void (CADAPI *tfCadPlinePutX)(VHANDLE hEnt, UINT iVer, double X);
	typedef double (CADAPI *tfCadPlineGetY)(VHANDLE hEnt, UINT iVer);
	typedef void (CADAPI *tfCadPlinePutY)(VHANDLE hEnt, UINT iVer, double Y);
	typedef double (CADAPI *tfCadPlineGetZ)(VHANDLE hEnt, UINT iVer);
	typedef void (CADAPI *tfCadPlinePutZ)(VHANDLE hEnt, UINT iVer, double Z);
	typedef void (CADAPI *tfCadPlineGetVer)(VHANDLE hEnt, UINT iVer, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadPlinePutVer)(VHANDLE hEnt, UINT iVer, double X, double Y, double Z);
	typedef double (CADAPI *tfCadPlineGetPrm)(VHANDLE hEnt, UINT iVer);
	typedef void (CADAPI *tfCadPlinePutPrm)(VHANDLE hEnt, UINT iVer, double Prm);
	typedef double (CADAPI *tfCadPlineGetStartW)(VHANDLE hEnt, UINT iVer);
	typedef void (CADAPI *tfCadPlinePutStartW)(VHANDLE hEnt, UINT iVer, double Width);
	typedef double (CADAPI *tfCadPlineGetEndW)(VHANDLE hEnt, UINT iVer);
	typedef void (CADAPI *tfCadPlinePutEndW)(VHANDLE hEnt, UINT iVer, double Width);
	typedef void (CADAPI *tfCadPlinePutZ1)(VHANDLE hEnt, double Z);
	typedef double (CADAPI *tfCadPlineGetRadius)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPlinePutRadius)(VHANDLE hEnt, double Rad);
	typedef double (CADAPI *tfCadPlineGetWidth)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPlinePutWidth)(VHANDLE hEnt, double Width);
	typedef BOOL (CADAPI *tfCadPlineGetClosed)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPlinePutClosed)(VHANDLE hEnt, BOOL bClosed);
	typedef int (CADAPI *tfCadPlineGetFit)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadPlinePutFit)(VHANDLE hEnt, int FitType);
	typedef void (CADAPI *tfCadPlineGetStartTan)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadPlinePutStartTan)(VHANDLE hEnt, double X, double Y, double Z);
	typedef void (CADAPI *tfCadPlineGetEndTan)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadPlinePutEndTan)(VHANDLE hEnt, double X, double Y, double Z);
	typedef double (CADAPI *tfCadPlineGetLength)(VHANDLE hEnt);
	typedef double (CADAPI *tfCadPlineGetArea)(VHANDLE hEnt);
	typedef BOOL (CADAPI *tfCadPlineContainPoint)(VHANDLE hEnt, double X, double Y);
	typedef double (CADAPI *tfCadPlineGetNearPoint)(VHANDLE hEnt, double X, double Y, double Z, double* pX, double* pY, double* pZ, double* pDist);
	typedef BOOL (CADAPI *tfCadPlineGetDistPoint)(VHANDLE hEnt, double Dist, double* pX, double* pY, double* pZ, double* pDirAngle);
	typedef BOOL (CADAPI *tfCadPlineGetInterPoint)(VHANDLE hEnt, double x1, double y1, double x2, double y2, double* pX, double* pY, double* pDist);
	typedef VHANDLE (CADAPI *tfCadAddRect)(VDWG hDwg, double X, double Y, double Z, double Width, double Height, double Angle);
	typedef void (CADAPI *tfCadRectGetCenter)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadRectPutCenter)(VHANDLE hEnt, double X, double Y, double Z);
	typedef double (CADAPI *tfCadRectGetWidth)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadRectPutWidth)(VHANDLE hEnt, double Width);
	typedef double (CADAPI *tfCadRectGetHeight)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadRectPutHeight)(VHANDLE hEnt, double Height);
	typedef double (CADAPI *tfCadRectGetAngle)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadRectPutAngle)(VHANDLE hEnt, double Angle);
	typedef double (CADAPI *tfCadRectGetRadius)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadRectPutRadius)(VHANDLE hEnt, double Radius);
	typedef BOOL (CADAPI *tfCadRectGetPrint)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadRectPutPrint)(VHANDLE hEnt, BOOL bPrnRect);
	typedef void (CADAPI *tfCadRectGetName)(VHANDLE hEnt, TCHAR* szName);
	typedef void (CADAPI *tfCadRectPutName)(VHANDLE hEnt, LPCTSTR szName);
	typedef BOOL (CADAPI *tfCadRectPrint)(VDWG hDwg, VHANDLE hEnt, HDC hDC);
	typedef VHANDLE (CADAPI *tfCadAddMline)(VDWG hDwg, BOOL bClosed);
	typedef BOOL (CADAPI *tfCadMlineInsertVer)(VHANDLE hEnt, UINT iVer);
	typedef BOOL (CADAPI *tfCadMlineDeleteVer)(VHANDLE hEnt, UINT iVer);
	typedef UINT (CADAPI *tfCadMlineGetNumVers)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadMlinePutNumVers)(VHANDLE hEnt, UINT nVers);
	typedef void (CADAPI *tfCadMlineGetVer)(VHANDLE hEnt, UINT iVer, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadMlinePutVer)(VHANDLE hEnt, UINT iVer, double X, double Y, double Z);
	typedef void (CADAPI *tfCadMlinePutZ1)(VHANDLE hEnt, double Z);
	typedef BOOL (CADAPI *tfCadMlineGetClosed)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadMlinePutClosed)(VHANDLE hEnt, BOOL bClosed);
	typedef void (CADAPI *tfCadMlinePutScale)(VHANDLE hEnt, double Scal);
	typedef double (CADAPI *tfCadMlineGetScale)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadMlinePutJust)(VHANDLE hEnt, int Just);
	typedef int (CADAPI *tfCadMlineGetJust)(VHANDLE hEnt);
	typedef double (CADAPI *tfCadMlineGetLength)(VHANDLE hEnt);
	typedef IDOBJ (CADAPI *tfCadMlineGetStyleID)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadMlinePutStyleID)(VHANDLE hEnt, IDOBJ Id);
	typedef int (CADAPI *tfCadSetTextAlign)(VDWG hDwg, int Align);
	typedef double (CADAPI *tfCadSetTextHeight)(VDWG hDwg, double Height);
	typedef double (CADAPI *tfCadSetTextWidth)(VDWG hDwg, double Width);
	typedef double (CADAPI *tfCadSetTextRotAngle)(VDWG hDwg, double Angle);
	typedef double (CADAPI *tfCadSetTextOblique)(VDWG hDwg, double Angle);
	typedef BOOL (CADAPI *tfCadSetTextUpsideDown)(VDWG hDwg, BOOL bUpDown);
	typedef BOOL (CADAPI *tfCadSetTextBackward)(VDWG hDwg, BOOL bBack);
	typedef VHANDLE (CADAPI *tfCadAddText)(VDWG hDwg, LPCTSTR szText, double X, double Y, double Z);
	typedef VHANDLE (CADAPI *tfCadAddText2)(VDWG hDwg, LPCTSTR szText, double X, double Y, double Z, int Align, double H, double W, double RotAngle, double Oblique);
	typedef IDOBJ (CADAPI *tfCadTextGetStyleID)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextPutStyleID)(VHANDLE hEnt, IDOBJ Id);
	typedef double (CADAPI *tfCadTextGetX)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextPutX)(VHANDLE hEnt, double X);
	typedef double (CADAPI *tfCadTextGetY)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextPutY)(VHANDLE hEnt, double Y);
	typedef double (CADAPI *tfCadTextGetZ)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextPutZ)(VHANDLE hEnt, double Z);
	typedef void (CADAPI *tfCadTextGetPoint)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadTextPutPoint)(VHANDLE hEnt, double X, double Y, double Z);
	typedef UINT (CADAPI *tfCadTextGetLen)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextGetText)(VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	typedef void (CADAPI *tfCadTextPutText)(VHANDLE hEnt, LPCTSTR szText);
	typedef double (CADAPI *tfCadTextGetAngle)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextPutAngle)(VHANDLE hEnt, double Angle);
	typedef double (CADAPI *tfCadTextGetHeight)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextPutHeight)(VHANDLE hEnt, double Height);
	typedef double (CADAPI *tfCadTextGetWidth)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextPutWidth)(VHANDLE hEnt, double Width);
	typedef double (CADAPI *tfCadTextGetOblique)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextPutOblique)(VHANDLE hEnt, double Angle);
	typedef int (CADAPI *tfCadTextGetAlign)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextPutAlign)(VHANDLE hEnt, int Align);
	typedef BOOL (CADAPI *tfCadTextGetBackward)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextPutBackward)(VHANDLE hEnt, BOOL bBackward);
	typedef BOOL (CADAPI *tfCadTextGetUpsideDown)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextPutUpsideDown)(VHANDLE hEnt, BOOL bUpsideDown);
	typedef double (CADAPI *tfCadTextGetBoxWidth)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadTextGetPoint0)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef VHANDLE (CADAPI *tfCadAddMText)(VDWG hDwg, LPCTSTR szText, double RectWidth, double X, double Y, double Z, int Align, double RotAngle);
	typedef IDOBJ (CADAPI *tfCadMTextGetStyleID)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadMTextPutStyleID)(VHANDLE hEnt, IDOBJ Id);
	typedef void (CADAPI *tfCadMTextGetPoint)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadMTextPutPoint)(VHANDLE hEnt, double X, double Y, double Z);
	typedef UINT (CADAPI *tfCadMTextGetLen)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadMTextGetText)(VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	typedef void (CADAPI *tfCadMTextPutText)(VHANDLE hEnt, LPCTSTR szText);
	typedef double (CADAPI *tfCadMTextGetRectWidth)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadMTextPutRectWidth)(VHANDLE hEnt, double RectWidth);
	typedef int (CADAPI *tfCadMTextGetAlign)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadMTextPutAlign)(VHANDLE hEnt, int Align);
	typedef double (CADAPI *tfCadMTextGetHeight)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadMTextPutHeight)(VHANDLE hEnt, double Height);
	typedef double (CADAPI *tfCadMTextGetAngle)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadMTextPutAngle)(VHANDLE hEnt, double Angle);
	typedef double (CADAPI *tfCadMTextGetWidth)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadMTextPutWidth)(VHANDLE hEnt, double Width);
	typedef double (CADAPI *tfCadMTextGetLineSpace)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadMTextPutLineSpace)(VHANDLE hEnt, double LineSpace);
	typedef double (CADAPI *tfCadMTextGetAW)(VHANDLE hEnt);
	typedef double (CADAPI *tfCadMTextGetAH)(VHANDLE hEnt);
	typedef VHANDLE (CADAPI *tfCadAddWText)(VDWG hDwg, LPCTSTR szText, double X, double Y, double Z);
	typedef VHANDLE (CADAPI *tfCadAddWText2)(VDWG hDwg, LPCTSTR szText, double X, double Y, double Z, int Align, double H, double RotAngle, bool bItalic, bool bUnderline, bool bStrikeout);
	typedef IDOBJ (CADAPI *tfCadWTextGetStyleID)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadWTextPutStyleID)(VHANDLE hEnt, IDOBJ Id);
	typedef void (CADAPI *tfCadWTextGetPoint)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadWTextPutPoint)(VHANDLE hEnt, double X, double Y, double Z);
	typedef UINT (CADAPI *tfCadWTextGetLen)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadWTextGetText)(VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	typedef void (CADAPI *tfCadWTextPutText)(VHANDLE hEnt, LPCTSTR szText);
	typedef double (CADAPI *tfCadWTextGetAngle)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadWTextPutAngle)(VHANDLE hEnt, double Angle);
	typedef double (CADAPI *tfCadWTextGetHeight)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadWTextPutHeight)(VHANDLE hEnt, double Height);
	typedef int (CADAPI *tfCadWTextGetAlign)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadWTextPutAlign)(VHANDLE hEnt, int Align);
	typedef BOOL (CADAPI *tfCadWTextGetItalic)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadWTextPutItalic)(VHANDLE hEnt, BOOL bItalic);
	typedef BOOL (CADAPI *tfCadWTextGetStrikeout)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadWTextPutStrikeout)(VHANDLE hEnt, BOOL bStrikeout);
	typedef BOOL (CADAPI *tfCadWTextGetUnderline)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadWTextPutUnderline)(VHANDLE hEnt, BOOL bUnderline);
	typedef VHANDLE (CADAPI *tfCadAddInsBlock)(VDWG hDwg, IDOBJ idBlock, double X, double Y, double Z, double Scal, double Angle);
	typedef VHANDLE (CADAPI *tfCadAddInsBlockM)(VDWG hDwg, IDOBJ idBlock, double X, double Y, double Z, double Scal, double Angle, int NumCols, int NumRows, double ColDist, double RowDist);
	typedef IDOBJ (CADAPI *tfCadInsBlockGetBlockID)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutBlockID)(VHANDLE hEnt, IDOBJ Id);
	typedef double (CADAPI *tfCadInsBlockGetX)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutX)(VHANDLE hEnt, double X);
	typedef double (CADAPI *tfCadInsBlockGetY)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutY)(VHANDLE hEnt, double Y);
	typedef double (CADAPI *tfCadInsBlockGetZ)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutZ)(VHANDLE hEnt, double Z);
	typedef void (CADAPI *tfCadInsBlockGetPoint)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadInsBlockPutPoint)(VHANDLE hEnt, double X, double Y, double Z);
	typedef double (CADAPI *tfCadInsBlockGetScale)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutScale)(VHANDLE hEnt, double Scal);
	typedef double (CADAPI *tfCadInsBlockGetScaleX)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutScaleX)(VHANDLE hEnt, double Sx);
	typedef double (CADAPI *tfCadInsBlockGetScaleY)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutScaleY)(VHANDLE hEnt, double Sy);
	typedef double (CADAPI *tfCadInsBlockGetScaleZ)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutScaleZ)(VHANDLE hEnt, double Sz);
	typedef double (CADAPI *tfCadInsBlockGetAngle)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutAngle)(VHANDLE hEnt, double Angle);
	typedef UINT (CADAPI *tfCadInsBlockGetNumRows)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutNumRows)(VHANDLE hEnt, UINT NumRows);
	typedef UINT (CADAPI *tfCadInsBlockGetNumCols)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutNumCols)(VHANDLE hEnt, UINT NumCols);
	typedef double (CADAPI *tfCadInsBlockGetRowDist)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutRowDist)(VHANDLE hEnt, double RowDist);
	typedef double (CADAPI *tfCadInsBlockGetColDist)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadInsBlockPutColDist)(VHANDLE hEnt, double ColDist);
	typedef BOOL (CADAPI *tfCadInsBlockHasAttribs)(VHANDLE hEnt);
	typedef VHANDLE (CADAPI *tfCadInsBlockGetFirstAtt)(VHANDLE hEnt);
	typedef VHANDLE (CADAPI *tfCadInsBlockGetNextAtt)(VHANDLE hEnt, VHANDLE hAtt);
	typedef VHANDLE (CADAPI *tfCadAddAttrib)(VDWG hDwg, LPCTSTR szTag, LPCTSTR szDefValue, double X, double Y, double Z);
	typedef IDOBJ (CADAPI *tfCadAttGetStyleID)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadAttPutStyleID)(VHANDLE hEnt, IDOBJ Id);
	typedef void (CADAPI *tfCadAttGetPoint)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadAttPutPoint)(VHANDLE hEnt, double X, double Y, double Z);
	typedef void (CADAPI *tfCadAttGetTag)(VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	typedef void (CADAPI *tfCadAttPutTag)(VHANDLE hEnt, LPCTSTR szText);
	typedef void (CADAPI *tfCadAttGetPrompt)(VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	typedef void (CADAPI *tfCadAttPutPrompt)(VHANDLE hEnt, LPCTSTR szText);
	typedef void (CADAPI *tfCadAttGetDefValue)(VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	typedef void (CADAPI *tfCadAttPutDefValue)(VHANDLE hEnt, LPCTSTR szText);
	typedef void (CADAPI *tfCadAttGetValue)(VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	typedef void (CADAPI *tfCadAttPutValue)(VHANDLE hEnt, LPCTSTR szText);
	typedef double (CADAPI *tfCadAttGetAngle)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadAttPutAngle)(VHANDLE hEnt, double Angle);
	typedef double (CADAPI *tfCadAttGetHeight)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadAttPutHeight)(VHANDLE hEnt, double Height);
	typedef double (CADAPI *tfCadAttGetWidth)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadAttPutWidth)(VHANDLE hEnt, double Width);
	typedef double (CADAPI *tfCadAttGetOblique)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadAttPutOblique)(VHANDLE hEnt, double Angle);
	typedef int (CADAPI *tfCadAttGetAlign)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadAttPutAlign)(VHANDLE hEnt, int Align);
	typedef BOOL (CADAPI *tfCadAttGetBackward)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadAttPutBackward)(VHANDLE hEnt, BOOL bBackward);
	typedef BOOL (CADAPI *tfCadAttGetUpsideDown)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadAttPutUpsideDown)(VHANDLE hEnt, BOOL bUpsideDown);
	typedef int (CADAPI *tfCadAttGetMode)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadAttPutMode)(VHANDLE hEnt, int Mode);
	typedef VHANDLE (CADAPI *tfCadAddImage)(VDWG hDwg, LPCTSTR szFileName, double X, double Y, double Z, double Scal);
	typedef VHANDLE (CADAPI *tfCadAddImagePlace)(VDWG hDwg, int Id, int Width, int Height, double X, double Y, double Z, double Scal);
	typedef void (CADAPI *tfCadImageGetFile)(VHANDLE hEnt, TCHAR* szFileName);
	typedef void (CADAPI *tfCadImagePutFile)(VHANDLE hEnt, LPCTSTR szFileName);
	typedef double (CADAPI *tfCadImageGetX)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadImagePutX)(VHANDLE hEnt, double X);
	typedef double (CADAPI *tfCadImageGetY)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadImagePutY)(VHANDLE hEnt, double Y);
	typedef double (CADAPI *tfCadImageGetZ)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadImagePutZ)(VHANDLE hEnt, double Z);
	typedef void (CADAPI *tfCadImageGetPoint)(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadImagePutPoint)(VHANDLE hEnt, double X, double Y, double Z);
	typedef double (CADAPI *tfCadImageGetScale)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadImagePutScale)(VHANDLE hEnt, double Scal);
	typedef double (CADAPI *tfCadImageGetScaleX)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadImagePutScaleX)(VHANDLE hEnt, double Sx);
	typedef double (CADAPI *tfCadImageGetScaleY)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadImagePutScaleY)(VHANDLE hEnt, double Sy);
	typedef void (CADAPI *tfCadImagePutSize)(VHANDLE hEnt, int Width, int Height);
	typedef BOOL (CADAPI *tfCadImageGetTransparent)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadImagePutTransparent)(VHANDLE hEnt, BOOL bTransp);
	typedef COLORREF (CADAPI *tfCadImageGetTColor)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadImagePutTColor)(VHANDLE hEnt, COLORREF ColorRGB);
	typedef BOOL (CADAPI *tfCadAddHatchPoint)(VDWG hDwg, double X, double Y);
	typedef BOOL (CADAPI *tfCadAddHatchPath)(VDWG hDwg, VHANDLE hEnt);
	typedef VHANDLE (CADAPI *tfCadAddHatch)(VDWG hDwg, LPCTSTR szFileName, LPCTSTR szPatName, double Scal, double Angle);
	typedef UINT (CADAPI *tfCadEngrave)(VDWG hDwg, BOOL bSelected, LPCTSTR szBlockName, double Step, double Angle);
	typedef void (CADAPI *tfCadHatchPutPattern)(VHANDLE hEnt, LPCTSTR szFileName, LPCTSTR szPatName);
	typedef void (CADAPI *tfCadHatchGetName)(VHANDLE hEnt, TCHAR* szName);
	typedef UINT (CADAPI *tfCadHatchGetPattern)(VHANDLE hEnt, TCHAR* szPattern);
	typedef void (CADAPI *tfCadHatchPutScale)(VHANDLE hEnt, double Scal);
	typedef double (CADAPI *tfCadHatchGetScale)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadHatchPutAngle)(VHANDLE hEnt, double Angle);
	typedef double (CADAPI *tfCadHatchGetAngle)(VHANDLE hEnt);
	typedef double (CADAPI *tfCadHatchGetSize)(VHANDLE hEnt);
	typedef BOOL (CADAPI *tfCadAddDimPoint)(UINT Index, double X, double Y, double Z);
	typedef VHANDLE (CADAPI *tfCadAddDim)(VDWG hDwg, int DimType);
	typedef IDOBJ (CADAPI *tfCadDimGetStyleID)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadDimPutStyleID)(VHANDLE hEnt, IDOBJ Id);
	typedef void (CADAPI *tfCadDimPutText)(VHANDLE hEnt, LPCTSTR szText);
	typedef void (CADAPI *tfCadDimGetText)(VHANDLE hEnt, TCHAR* szText);
	typedef void (CADAPI *tfCadDimGetPoint)(VHANDLE hEnt, int Index, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadDimPutPoint)(VHANDLE hEnt, int Index, double X, double Y, double Z);
	typedef int (CADAPI *tfCadDimGetType)(VHANDLE hEnt);
	typedef double (CADAPI *tfCadDimGetValue)(VHANDLE hEnt);
	typedef VHANDLE (CADAPI *tfCadAddLeader)(VDWG hDwg, LPCTSTR szText);
	typedef UINT (CADAPI *tfCadLeaderGetNumVers)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadLeaderPutNumVers)(VHANDLE hEnt, UINT nVers);
	typedef void (CADAPI *tfCadLeaderGetVer)(VHANDLE hEnt, UINT iVer, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadLeaderPutVer)(VHANDLE hEnt, UINT iVer, double X, double Y, double Z);
	typedef BOOL (CADAPI *tfCadLeaderGetSpline)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadLeaderPutSpline)(VHANDLE hEnt, BOOL bSpline);
	typedef UINT (CADAPI *tfCadLeaderGetTextLen)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadLeaderGetText)(VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	typedef void (CADAPI *tfCadLeaderPutText)(VHANDLE hEnt, LPCTSTR szText);
	typedef double (CADAPI *tfCadLeaderGetTextH)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadLeaderPutTextH)(VHANDLE hEnt, double Height);
	typedef double (CADAPI *tfCadLeaderGetArrSize)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadLeaderPutArrSize)(VHANDLE hEnt, double Size);
	typedef IDOBJ (CADAPI *tfCadLeaderGetTextStyleID)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadLeaderPutTextStyleID)(VHANDLE hEnt, IDOBJ Id);
	typedef VHANDLE (CADAPI *tfCadAddFace)(VDWG hDwg);
	typedef UINT (CADAPI *tfCadFaceGetNumVers)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadFaceGetVer)(VHANDLE hEnt, UINT iVer, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadFacePutVer)(VHANDLE hEnt, UINT iVer, double X, double Y, double Z);
	typedef BOOL (CADAPI *tfCadFaceGetEdge)(VHANDLE hEnt, UINT iEdge);
	typedef void (CADAPI *tfCadFacePutEdge)(VHANDLE hEnt, UINT iEdge, BOOL bVisible);
	typedef VHANDLE (CADAPI *tfCadAddVport)(VDWG hDwg, double X, double Y, double W, double H);
	typedef VHANDLE (CADAPI *tfCadAddCustom)(VDWG hDwg, int CustType, void* pData, int nBytes);
	typedef void (CADAPI *tfCadCustomPutOwner)(VHANDLE hEnt, void* pObject);
	typedef DWORD (CADAPI *tfCadCustomGetOwner)(VHANDLE hEnt);
	typedef int (CADAPI *tfCadCustomGetType)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadCustomPutData)(VHANDLE hEnt, void* pData, int nBytes);
	typedef void (CADAPI *tfCadCustomGetData)(VHANDLE hEnt, void* pData);
	typedef int (CADAPI *tfCadCustomGetSize)(VHANDLE hEnt);
	typedef VHANDLE (CADAPI *tfCadCustomGetDataPtr)(VHANDLE hEnt);
	typedef void (CADAPI *tfCadDrawSet)(int Mode, int Value);
	typedef HDC (CADAPI *tfCadDrawGetDC)();
	typedef void (CADAPI *tfCadDrawAddVertex)(double X, double Y, double Z);
	typedef int (CADAPI *tfCadDrawGenArc)(double Xcen, double Ycen, double Zcen, double Radius, double AngStart, double AngArc, int nVers);
	typedef int (CADAPI *tfCadDrawGenCircle)(double X, double Y, double Z, double Radius, int nVers);
	typedef int (CADAPI *tfCadDrawGenChar)(double X, double Y, double Z, double Height, double Angle, double ScaleW, UINT UCode, LPCTSTR szFont, int nVers);
	typedef void (CADAPI *tfCadDrawPolyline)();
	typedef void (CADAPI *tfCadDrawPolygon)();
	typedef void (CADAPI *tfCadDrawPolyPolygon)(int* PlineSize, int nPline);
	typedef void (CADAPI *tfCadDrawLine)(double X1, double Y1, double Z1, double X2, double Y2, double Z2);
	typedef void (CADAPI *tfCadDrawPoint)(double X, double Y, double Z, int PtMode, double PtSize);
	typedef void (CADAPI *tfCadDrawText)(VDWG hDwg, LPCTSTR szText, double X, double Y, double Z);
	typedef void (CADAPI *tfCadDrawBlock)(VDWG hDwg, VHANDLE hBlock, double X, double Y, double Z, double ScaleX, double ScaleY, double ScaleZ, double RotAngle);
	typedef void (CADAPI *tfCadDrawObject)(double Xcen, double Ycen, double Zcen, double W, double H, F_DISPOWNERDRAW fnDraw, void* ptr);
	typedef BOOL (CADAPI *tfCadAddCustProp)(int IdProp, LPCTSTR szName, LPCTSTR szValue, int ValType);
	typedef BOOL (CADAPI *tfCadSetCustProp)(int IdProp, LPCTSTR szValue);
	typedef BOOL (CADAPI *tfCadSetCustPropMode)(int IdProp, BOOL bReadOnly);
	typedef BOOL (CADAPI *tfCadAddCommand)(VDWG hDwg, int Id, LPCTSTR szCmdName, LPCTSTR szAlias, HCURSOR hCurs, F_CCMD pFunc1, F_CDRAG pFunc2);
	typedef void (CADAPI *tfCadCmdPutData)(VDWG hDwg, void* pData, int nBytes);
	typedef void (CADAPI *tfCadCmdGetData)(VDWG hDwg, void* pData);
	typedef int (CADAPI *tfCadCmdGetSize)(VDWG hDwg);
	typedef void (CADAPI *tfCadCmdPrompt)(VDWG hDwg, LPCTSTR szText, LPCTSTR szDefaultVal);
	typedef void (CADAPI *tfCadCmdPromptAdd)(VDWG hDwg, LPCTSTR szValue);
	typedef int (CADAPI *tfCadCmdUserSelect)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadCmdUserGetEntity)(VDWG hDwg);
	typedef int (CADAPI *tfCadCmdUserInput)(VDWG hDwg);
	typedef void (CADAPI *tfCadCmdGetInputPoint)(VDWG hDwg, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadCmdGetInputStr)(VDWG hDwg, TCHAR* szText);
	typedef BOOL (CADAPI *tfCadCmdStrToPoint)(VDWG hDwg, LPCTSTR szValue, double* pX, double* pY, double* pZ);
	typedef void (CADAPI *tfCadCmdSetBasePoint)(VDWG hDwg, double X, double Y, double Z);
	typedef BOOL (CADAPI *tfCadCmdAddPoint)(VDWG hDwg, double X, double Y, double Z);
	typedef BOOL (CADAPI *tfCadCmdGetPoint)(VDWG hDwg, int iPoint, double* pX, double* pY, double* pZ);
	typedef int (CADAPI *tfCadCmdCountPoints)(VDWG hDwg);
	typedef void (CADAPI *tfCadSelClear)(VDWG hDwg);
	typedef void (CADAPI *tfCadSelectEntity)(VDWG hDwg, VHANDLE hEnt, BOOL bSelect);
	typedef UINT (CADAPI *tfCadSelectByLayer)(VDWG hDwg, BOOL bSelect);
	typedef UINT (CADAPI *tfCadSelectByPage)(VDWG hDwg, BOOL bSelect);
	typedef UINT (CADAPI *tfCadSelectByPolyline)(VDWG hDwg, VHANDLE hEnt, BOOL bSelect);
	typedef UINT (CADAPI *tfCadSelectByPolygon)(VDWG hDwg, VHANDLE hEnt, BOOL bCross, BOOL bSelect);
	typedef UINT (CADAPI *tfCadSelectByDist)(VDWG hDwg, double X, double Y, double Z, double Dist, BOOL bCross, BOOL bSelect);
	typedef UINT (CADAPI *tfCadSelCount)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadSelGetFirstPtr)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadSelGetNextPtr)(VDWG hDwg, VHANDLE hPtr);
	typedef void (CADAPI *tfCadSelErase)(VDWG hDwg);
	typedef void (CADAPI *tfCadSelCopy)(VDWG hDwg);
	typedef void (CADAPI *tfCadSelMove)(VDWG hDwg, double dx, double dy, double dz);
	typedef void (CADAPI *tfCadSelScale)(VDWG hDwg, double x0, double y0, double z0, double Scal);
	typedef void (CADAPI *tfCadSelRotate)(VDWG hDwg, double x0, double y0, double z0, double Angle);
	typedef void (CADAPI *tfCadSelMirror)(VDWG hDwg, double x0, double y0, double z0, double x1, double y1, double z1);
	typedef void (CADAPI *tfCadSelExplode)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadSelJoin)(VDWG hDwg, double Delta);
	typedef void (CADAPI *tfCadSelColor)(VDWG hDwg, int Color);
	typedef void (CADAPI *tfCadSelDraw)(VDWG hDwg, HDC hDC, int WinLef, int WinBot, int WinW, int WinH, double ViewLef, double ViewBot, double ViewW, double ViewH, DWORD idPage, COLORREF FillColor, COLORREF BordColor, double LwScale);
	typedef void (CADAPI *tfCadSelMakeGrips)(VDWG hDwg);
	typedef BOOL (CADAPI *tfCadCbPaste)(VDWG hDwg, HWND hWnd, double dx, double dy, double dz);
	typedef DWORD (CADAPI *tfCadCountEntities)(VDWG hDwg);
	typedef void (CADAPI *tfCadViewPutPoint)(VDWG hDwg, HWND hWin, double X, double Y, double Z);
	typedef void (CADAPI *tfCadViewGetPoint)(VDWG hDwg, HWND hWin, double* pX, double* pY, double* pZ);
	typedef double (CADAPI *tfCadViewGetPointX)(VDWG hDwg);
	typedef double (CADAPI *tfCadViewGetPointY)(VDWG hDwg);
	typedef double (CADAPI *tfCadViewGetPointZ)(VDWG hDwg);
	typedef void (CADAPI *tfCadViewPutAngles)(VDWG hDwg, HWND hWin, double AngHor, double AngVer);
	typedef double (CADAPI *tfCadViewGetAngleHor)(VDWG hDwg);
	typedef double (CADAPI *tfCadViewGetAngleVer)(VDWG hDwg);
	typedef void (CADAPI *tfCadViewRect)(VDWG hDwg, HWND hWin, double Xmin, double Ymin, double Xmax, double Ymax);
	typedef void (CADAPI *tfCadViewScale)(VDWG hDwg, HWND hWin, double Scal, int Xcen, int Ycen);
	typedef void (CADAPI *tfCadCoordModelToDisp)(VDWG hDwg, double Xm, double Ym, double Zm, double* pXd, double* pYd);
	typedef void (CADAPI *tfCadCoordModelToWin)(VDWG hDwg, double Xm, double Ym, double Zm, long* pXw, long* pYw);
	typedef void (CADAPI *tfCadCoordDispToModel)(VDWG hDwg, double Xd, double Yd, double* pXm, double* pYm, double* pZm);
	typedef void (CADAPI *tfCadCoordDispToWin)(VDWG hDwg, double Xd, double Yd, long* pXw, long* pYw);
	typedef void (CADAPI *tfCadCoordWinToModel)(VDWG hDwg, int Xw, int Yw, double* pXm, double* pYm, double* pZm);
	typedef void (CADAPI *tfCadCoordWinToDisp)(VDWG hDwg, int Xw, int Yw, double* pXd, double* pYd);
	typedef double (CADAPI *tfCadDistWinToModel)(VDWG hDwg, int Dwin);
	typedef int (CADAPI *tfCadDistModelToWin)(VDWG hDwg, double Dmod);
	typedef void (CADAPI *tfCadPrintGetRect)(double* pLeft, double* pBottom, double* pRight, double* pTop);
	typedef void (CADAPI *tfCadPrintPutRect)(double Left, double Bottom, double Right, double Top);
	typedef void (CADAPI *tfCadPrintPutScale)(double Scal);
	typedef double (CADAPI *tfCadPrintGetScale)();
	typedef void (CADAPI *tfCadPrintPutScaleLW)(BOOL bScaleLW);
	typedef BOOL (CADAPI *tfCadPrintGetScaleLW)();
	typedef void (CADAPI *tfCadPrintPutOffset)(double DX, double DY);
	typedef void (CADAPI *tfCadPrintGetOffset)(double* pDX, double* pDY);
	typedef void (CADAPI *tfCadPrintPutColor)(BOOL bColor);
	typedef BOOL (CADAPI *tfCadPrintGetColor)();
	typedef void (CADAPI *tfCadPrintPutCopies)(UINT Ncopy);
	typedef UINT (CADAPI *tfCadPrintGetCopies)();
	typedef void (CADAPI *tfCadPrintPutOrient)(UINT Orient);
	typedef UINT (CADAPI *tfCadPrintGetOrient)();
	typedef void (CADAPI *tfCadPrintPutStampPos)(UINT Pos);
	typedef UINT (CADAPI *tfCadPrintGetStampPos)();
	typedef void (CADAPI *tfCadPrintPutStampSize)(double TextHeight);
	typedef double (CADAPI *tfCadPrintGetStampSize)();
	typedef void (CADAPI *tfCadPrintPutStampColor)(DWORD Color);
	typedef DWORD (CADAPI *tfCadPrintGetStampColor)();
	typedef void (CADAPI *tfCadPrintPutStampText)(LPCTSTR szText1, LPCTSTR szText2);
	typedef void (CADAPI *tfCadPrintGetStampText)(TCHAR* szText1, TCHAR* szText2);
	typedef void (CADAPI *tfCadPrintAtCenter)(BOOL bCenter);
	typedef BOOL (CADAPI *tfCadPrint)(VDWG hDwg, BOOL bPrintStamp, HDC hDC);
	typedef BOOL (CADAPI *tfCadPrintSetup)(HWND hwParent);
	typedef double (CADAPI *tfCadPrintGetPaperW)();
	typedef double (CADAPI *tfCadPrintGetPaperH)();
	typedef void (CADAPI *tfCadPrintGetPaperSize)(double* pWidth, double* pHeight);
	typedef int (CADAPI *tfCadPrnRectAdd)(VDWG hDwg, LPCTSTR szName, double Xcen, double Ycen, double W, double H, double Angle);
	typedef BOOL (CADAPI *tfCadPrnRectDelete)(VDWG hDwg, int iRect);
	typedef int (CADAPI *tfCadPrnRectCount)(VDWG hDwg);
	typedef BOOL (CADAPI *tfCadPrnRectGet)(VDWG hDwg, int iRect, TCHAR* szName, double* pXcen, double* pYcen, double* pW, double* pH, double* pAngle);
	typedef BOOL (CADAPI *tfCadPrnRectPut)(VDWG hDwg, int iRect, LPCTSTR szName, double Xcen, double Ycen, double W, double H, double Angle);
	typedef BOOL (CADAPI *tfCadPrnRectPrint)(VDWG hDwg, int iRect, HDC hDC);
	typedef void (CADAPI *tfCadPrnRectPutShow)(VDWG hDwg, BOOL bShow);
	typedef BOOL (CADAPI *tfCadPrnRectGetShow)(VDWG hDwg);
	typedef void (CADAPI *tfCadRegen)(VDWG hDwg);
	typedef void (CADAPI *tfCadUpdate)(VDWG hDwg);
	typedef HWND (CADAPI *tfCadWndCreate)(VDWG hDwg, HWND hWndParent, int CadStyle, int X, int Y, int W, int H);
	typedef BOOL (CADAPI *tfCadWndResize)(HWND hWin, int X, int Y, int W, int H);
	typedef BOOL (CADAPI *tfCadWndRedraw)(HWND hWin);
	typedef HWND (CADAPI *tfCadWndSetFocus)(HWND hWin);
	typedef void (CADAPI *tfCadAccelSetKey)(int Command, int VirtKey, int Flags);
	typedef void (CADAPI *tfCadAccelSetDefault)();
	typedef HWND (CADAPI *tfCadCWCreate)(HWND hwParent, int Left, int Top, int Width, int Height);
	typedef void (CADAPI *tfCadCWDelete)();
	typedef BOOL (CADAPI *tfCadCWResize)(int Left, int Top, int Width, int Height);
	typedef void (CADAPI *tfCadCWPutText)(VDWG hDwg, LPCTSTR szText);
	typedef void (CADAPI *tfCadMagPutSize)(int Size);
	typedef int (CADAPI *tfCadMagGetSize)();
	typedef void (CADAPI *tfCadMagPutScale)(int Scal);
	typedef int (CADAPI *tfCadMagGetScale)();
	typedef void (CADAPI *tfCadMagPutPos)(int Pos);
	typedef int (CADAPI *tfCadMagGetPos)();
	typedef void (CADAPI *tfCadMagPutShow)(BOOL bShow);
	typedef BOOL (CADAPI *tfCadMagGetShow)();
	typedef HWND (CADAPI *tfCadNavCreate)(HWND hWndParent, int X, int Y, int W, int H, int Flags);
	typedef void (CADAPI *tfCadNavResize)(int X, int Y, int W, int H);
	typedef int (CADAPI *tfCadNavGetParam)(int Prm);
	typedef void (CADAPI *tfCadNavReturnFocus)(BOOL bReturn, HWND hWnd);
	typedef void (CADAPI *tfCadNavSetLink)(HWND hVecWnd);
	typedef HWND (CADAPI *tfCadCboxCreate)(int CbType, HWND hwParent, int Left, int Top, int Width, int Height, int Hdown);
	typedef void (CADAPI *tfCadCboxSetActive)(int CbType, HWND hwCbox);
	typedef void (CADAPI *tfCadMenuClear)(int MenuId);
	typedef void (CADAPI *tfCadMenuAdd)(int MenuId, LPCTSTR szItemText, int ItemCmd);
	typedef BOOL (CADAPI *tfCadRecentLoad)(LPCTSTR szFileName);
	typedef BOOL (CADAPI *tfCadRecentSave)();
	typedef BOOL (CADAPI *tfCadRecentDialog)(HWND hWin, TCHAR* szOutFileName, int* pbShowAtStartup);
	typedef BOOL (CADAPI *tfCadRecentAdd)(LPCTSTR szFileName);
	typedef BOOL (CADAPI *tfCadDialogOpenFile)(HWND hwParent, TCHAR* szOutFileName);
	typedef BOOL (CADAPI *tfCadDialogSaveFile)(HWND hwParent, TCHAR* szOutFileName);
	typedef void (CADAPI *tfCadTipOfTheDay)(HWND hwParent, LPCTSTR szFileName, int* pbShowOnStartup, int* pTipIndex);
	typedef void (CADAPI *tfCadHelp)(HWND hWin, LPCTSTR szTopic);
	typedef void (CADAPI *tfCadTTF2VCF)(HWND hwParent);
	typedef void (CADAPI *tfCadSHX2VCF)(HWND hwParent);
	typedef void (CADAPI *tfCadFontsList)(HWND hwParent);
	typedef void (CADAPI *tfCadPluginsDlg)(HWND hwParent);
	typedef int (CADAPI *tfCadGetError)();
	typedef void (CADAPI *tfCadGetErrorStr)(int ErrCode, TCHAR* szStr);
	typedef void (CADAPI *tfCadSetString)(int IdStr, LPCTSTR szStr);
	typedef BOOL (CADAPI *tfCadPluginImageRead)(LPCTSTR szExt, LPCTSTR szLibName, LPCTSTR szFuncName, int Mode);
	typedef BOOL (CADAPI *tfCadConvertAcadFile)(LPCTSTR szInFile, LPCTSTR szOutFile);
	typedef UINT (CADAPI *tfCadExtractImage)(LPCTSTR szFileName, BYTE* Buffer);
	typedef UINT (CADAPI *tfCadExtractImageMem)(void* pMem, BYTE* Buffer);
	typedef void (CADAPI *tfCadGetVBString)(int Val, TCHAR* szStr);
	typedef BOOL (CADAPI *tfvuGetWindowSize)(HWND hWin, int* pW, int* pH);
	typedef BOOL (CADAPI *tfCadGetWindowSize)(HWND hWin, int* pW, int* pH);
	typedef int (CADAPI *tfvuCompress)(BYTE* Dest, UINT DestMaxLen, CBYTE* Source, UINT SourceLen, int Level);
	typedef int (CADAPI *tfvuExpand)(BYTE* Dest, UINT DestMaxLen, CBYTE* Source, UINT SourceLen);
	typedef void (CADAPI *tfvuRotatePoint)(double* pX, double* pY, double* pZ, double Xcen, double Ycen, double Zcen, double Angle, int Plane);
	typedef void (CADAPI *tfvuPolarPoint)(double* pX, double* pY, double* pZ, double Angle, double Dist, int Plane);
	typedef void (CADAPI *tfvuScalePoint)(double* pX, double* pY, double* pZ, double Xcen, double Ycen, double Zcen, double ScaleX, double ScaleY, double ScaleZ);
	typedef void (CADAPI *tfvuMirrorPoint)(double* pX, double* pY, double* pZ, double A1, double B1, int Plane);
	typedef double (CADAPI *tfvuGetAngle)(double x1, double y1, double z1, double x2, double y2, double z2, int Plane);
	typedef double (CADAPI *tfvuGetDist)(double x1, double y1, double z1, double x2, double y2, double z2, int Plane);
	typedef double (CADAPI *tfvuNormalizeAngle)(double Angle);
	typedef void (CADAPI *tfvuNumToStr)(double Val, TCHAR* szOutStr, DWORD MaxDec, BOOL bTrimZero, BOOL bRemainPoint);
	typedef VHANDLE (CADAPI *tfCadAddRPlan)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetRPlan)(VDWG hDwg);
	typedef void (CADAPI *tfCadRPlanClear)(VHANDLE hRPlan);
	typedef void (CADAPI *tfCadRPlanSetStart)(VHANDLE hRPlan, double X, double Y, double Dist, double DirAngle);
	typedef BOOL (CADAPI *tfCadRPlanAddCurve)(VHANDLE hRPlan, double Dist, double RotAngle, int Turn, double Rad, double Len1, double Len2);
	typedef void (CADAPI *tfCadRPlanSetEnd)(VHANDLE hRPlan, double Dist);
	typedef void (CADAPI *tfCadRPlanUpdate)(VHANDLE hRPlan);
	typedef void (CADAPI *tfCadRPlanSetScale)(VHANDLE hRPlan, double Scal);
	typedef UINT (CADAPI *tfCadRPlanGetNumRecs)(VHANDLE hRPlan);
	typedef BOOL (CADAPI *tfCadRPlanGetCurveVertex)(VHANDLE hRPlan, UINT iRec, double* pX, double* pY);
	typedef BOOL (CADAPI *tfCadRPlanGetCurveCenter)(VHANDLE hRPlan, UINT iRec, double* pX, double* pY);
	typedef BOOL (CADAPI *tfCadRPlanGetCurveStart)(VHANDLE hRPlan, UINT iRec, double* pX, double* pY, double* pDirAngle);
	typedef BOOL (CADAPI *tfCadRPlanGetCurveEnd)(VHANDLE hRPlan, UINT iRec, double* pX, double* pY, double* pDirAngle);
	typedef BOOL (CADAPI *tfCadRPlanAddGrPoint)(double Offset, double Z);
	typedef BOOL (CADAPI *tfCadRPlanAddGrSection)(VHANDLE hRPlan, double Dist, double Zcen);
	typedef void (CADAPI *tfCadRPlanGenLevels)(VHANDLE hRPlan, double Precision, double ZStep, double ZStepBold, F_PROGRESS pFunc);
	typedef BOOL (CADAPI *tfCadRPlanGetPoint)(VHANDLE hRPlan, double Dist, double* pX, double* pY, double* pZ, double* pDirAngle);
	typedef BOOL (CADAPI *tfCadRPlanGetGrPoint)(VHANDLE hRPlan, double Dist, double Offset, double* pX, double* pY, double* pZ);
	typedef BOOL (CADAPI *tfCadRPlanGetDist)(VHANDLE hRPlan, double X, double Y, double* pDist, double* pOffset);
	typedef BOOL (CADAPI *tfCadRPlanGetZ)(VHANDLE hRPlan, double X, double Y, double* pZ);
	typedef void (CADAPI *tfCadRPlanPutVisible)(VHANDLE hRPlan, int Mode, BOOL bVisible);
	typedef BOOL (CADAPI *tfCadRPlanGetVisible)(VHANDLE hRPlan, int Mode);
	typedef void (CADAPI *tfCadRPlanPutColor)(VHANDLE hRPlan, int Mode, int Color);
	typedef int (CADAPI *tfCadRPlanGetColor)(VHANDLE hRPlan, int Mode);
	typedef void (CADAPI *tfCadRPlanPutLineweight)(VHANDLE hRPlan, int Mode, int lw);
	typedef int (CADAPI *tfCadRPlanGetLineweight)(VHANDLE hRPlan, int Mode);
	typedef VHANDLE (CADAPI *tfCadAddRProf)(VDWG hDwg);
	typedef VHANDLE (CADAPI *tfCadGetRProf)(VDWG hDwg);
	typedef void (CADAPI *tfCadRProfClear)(VHANDLE hRProf);
	typedef void (CADAPI *tfCadRProfAddVer)(VHANDLE hRProf, double Dist, double Y);
	typedef void (CADAPI *tfCadRProfDelVer)(VHANDLE hRProf, int iVer);
	typedef void (CADAPI *tfCadRProfPutVer)(VHANDLE hRProf, int iVer, double Dist, double Y);
	typedef void (CADAPI *tfCadRProfPutCurveLen)(VHANDLE hRProf, int iVer, double Length);
	typedef void (CADAPI *tfCadRProfUpdate)(VHANDLE hRProf);
	typedef UINT (CADAPI *tfCadRProfGetNumVers)(VHANDLE hRProf);
	typedef void (CADAPI *tfCadRProfGetVer)(VHANDLE hRProf, int iVer, double* pDist, double* pY);
	typedef void (CADAPI *tfCadRProfGetCurvePrm)(VHANDLE hRProf, int iVer, double* pRad, double* pBVC, double* pEVC, double* pLen);
	typedef void (CADAPI *tfCadRProfGetY)(VHANDLE hRProf, double Dist, double* pYold, double* pYnew);
	typedef void (CADAPI *tfCadRProfGetInterX)(VHANDLE hRProf, double Y, double* pX, int* pNumX, int MaxNumX);
	typedef void (CADAPI *tfCadRProfPutScale)(VHANDLE hRProf, double HorScale, double VerScale);
	typedef void (CADAPI *tfCadRProfPutVisible)(VHANDLE hRProf, int Mode, BOOL bVisible);
	typedef BOOL (CADAPI *tfCadRProfGetVisible)(VHANDLE hRProf, int Mode);
	typedef void (CADAPI *tfCadRProfPutColor)(VHANDLE hRProf, int Mode, int Color);
	typedef int (CADAPI *tfCadRProfGetColor)(VHANDLE hRProf, int Mode);
	typedef void (CADAPI *tfCadRProfPutLineweight)(VHANDLE hRProf, int Mode, int lw);
	typedef int (CADAPI *tfCadRProfGetLineweight)(VHANDLE hRProf, int Mode);
	typedef void (CADAPI *tfCadGetInterPoints)(VDWG hDwg, VHANDLE hEnt1, VHANDLE hEnt2, double* pX, double* pY, int* pNumPt, int MaxNumPt);

	//--------------
	BOOL CADAPI CadRegistration (int RegCode)
	{
	  tfCadRegistration pfCadRegistration;
	  pfCadRegistration = (tfCadRegistration)GetProcAddress( ghLibInst, "CadRegistration" );
	  if (pfCadRegistration){
		return (*pfCadRegistration)(RegCode);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadGetVersion (TCHAR* szVer)
	{
	  tfCadGetVersion pfCadGetVersion;
	  pfCadGetVersion = (tfCadGetVersion)GetProcAddress( ghLibInst, "CadGetVersion" );
	  if (pfCadGetVersion){
		return (*pfCadGetVersion)(szVer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadOnEventMouseMove (F_MOUSEMOVE pFunc)
	{
	  tfCadOnEventMouseMove pfCadOnEventMouseMove;
	  pfCadOnEventMouseMove = (tfCadOnEventMouseMove)GetProcAddress( ghLibInst, "CadOnEventMouseMove" );
	  if (pfCadOnEventMouseMove){
		(*pfCadOnEventMouseMove)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventMouseDown (F_MOUSEDOWN pFunc)
	{
	  tfCadOnEventMouseDown pfCadOnEventMouseDown;
	  pfCadOnEventMouseDown = (tfCadOnEventMouseDown)GetProcAddress( ghLibInst, "CadOnEventMouseDown" );
	  if (pfCadOnEventMouseDown){
		(*pfCadOnEventMouseDown)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventMouseUp (F_MOUSEUP pFunc)
	{
	  tfCadOnEventMouseUp pfCadOnEventMouseUp;
	  pfCadOnEventMouseUp = (tfCadOnEventMouseUp)GetProcAddress( ghLibInst, "CadOnEventMouseUp" );
	  if (pfCadOnEventMouseUp){
		(*pfCadOnEventMouseUp)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventMouseDblClk (F_MOUSEDBLCLK pFunc)
	{
	  tfCadOnEventMouseDblClk pfCadOnEventMouseDblClk;
	  pfCadOnEventMouseDblClk = (tfCadOnEventMouseDblClk)GetProcAddress( ghLibInst, "CadOnEventMouseDblClk" );
	  if (pfCadOnEventMouseDblClk){
		(*pfCadOnEventMouseDblClk)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventMouseWheel (F_MOUSEWHEEL pFunc)
	{
	  tfCadOnEventMouseWheel pfCadOnEventMouseWheel;
	  pfCadOnEventMouseWheel = (tfCadOnEventMouseWheel)GetProcAddress( ghLibInst, "CadOnEventMouseWheel" );
	  if (pfCadOnEventMouseWheel){
		(*pfCadOnEventMouseWheel)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventMouseSnap (F_MOUSESNAP pFunc)
	{
	  tfCadOnEventMouseSnap pfCadOnEventMouseSnap;
	  pfCadOnEventMouseSnap = (tfCadOnEventMouseSnap)GetProcAddress( ghLibInst, "CadOnEventMouseSnap" );
	  if (pfCadOnEventMouseSnap){
		(*pfCadOnEventMouseSnap)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventKeyDown (F_KEYDOWN pFunc)
	{
	  tfCadOnEventKeyDown pfCadOnEventKeyDown;
	  pfCadOnEventKeyDown = (tfCadOnEventKeyDown)GetProcAddress( ghLibInst, "CadOnEventKeyDown" );
	  if (pfCadOnEventKeyDown){
		(*pfCadOnEventKeyDown)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventRegen (F_REGEN pFunc)
	{
	  tfCadOnEventRegen pfCadOnEventRegen;
	  pfCadOnEventRegen = (tfCadOnEventRegen)GetProcAddress( ghLibInst, "CadOnEventRegen" );
	  if (pfCadOnEventRegen){
		(*pfCadOnEventRegen)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventLoadSave (F_LOADSAVE pFunc)
	{
	  tfCadOnEventLoadSave pfCadOnEventLoadSave;
	  pfCadOnEventLoadSave = (tfCadOnEventLoadSave)GetProcAddress( ghLibInst, "CadOnEventLoadSave" );
	  if (pfCadOnEventLoadSave){
		(*pfCadOnEventLoadSave)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventDistance (F_DISTANCE pFunc)
	{
	  tfCadOnEventDistance pfCadOnEventDistance;
	  pfCadOnEventDistance = (tfCadOnEventDistance)GetProcAddress( ghLibInst, "CadOnEventDistance" );
	  if (pfCadOnEventDistance){
		(*pfCadOnEventDistance)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventArea (F_AREA pFunc)
	{
	  tfCadOnEventArea pfCadOnEventArea;
	  pfCadOnEventArea = (tfCadOnEventArea)GetProcAddress( ghLibInst, "CadOnEventArea" );
	  if (pfCadOnEventArea){
		(*pfCadOnEventArea)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventPrompt (F_PROMPT pFunc)
	{
	  tfCadOnEventPrompt pfCadOnEventPrompt;
	  pfCadOnEventPrompt = (tfCadOnEventPrompt)GetProcAddress( ghLibInst, "CadOnEventPrompt" );
	  if (pfCadOnEventPrompt){
		(*pfCadOnEventPrompt)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventSelPage (F_SELPAGE pFunc)
	{
	  tfCadOnEventSelPage pfCadOnEventSelPage;
	  pfCadOnEventSelPage = (tfCadOnEventSelPage)GetProcAddress( ghLibInst, "CadOnEventSelPage" );
	  if (pfCadOnEventSelPage){
		(*pfCadOnEventSelPage)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventSelCodepage (F_SELCODEPAGE pFunc)
	{
	  tfCadOnEventSelCodepage pfCadOnEventSelCodepage;
	  pfCadOnEventSelCodepage = (tfCadOnEventSelCodepage)GetProcAddress( ghLibInst, "CadOnEventSelCodepage" );
	  if (pfCadOnEventSelCodepage){
		(*pfCadOnEventSelCodepage)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventFontReplace (F_FONTREPLACE pFunc)
	{
	  tfCadOnEventFontReplace pfCadOnEventFontReplace;
	  pfCadOnEventFontReplace = (tfCadOnEventFontReplace)GetProcAddress( ghLibInst, "CadOnEventFontReplace" );
	  if (pfCadOnEventFontReplace){
		(*pfCadOnEventFontReplace)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventPaint (F_PAINT pFunc)
	{
	  tfCadOnEventPaint pfCadOnEventPaint;
	  pfCadOnEventPaint = (tfCadOnEventPaint)GetProcAddress( ghLibInst, "CadOnEventPaint" );
	  if (pfCadOnEventPaint){
		(*pfCadOnEventPaint)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventView (F_VIEW pFunc)
	{
	  tfCadOnEventView pfCadOnEventView;
	  pfCadOnEventView = (tfCadOnEventView)GetProcAddress( ghLibInst, "CadOnEventView" );
	  if (pfCadOnEventView){
		(*pfCadOnEventView)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventDrawImage (F_DRAWIMAGE pFunc)
	{
	  tfCadOnEventDrawImage pfCadOnEventDrawImage;
	  pfCadOnEventDrawImage = (tfCadOnEventDrawImage)GetProcAddress( ghLibInst, "CadOnEventDrawImage" );
	  if (pfCadOnEventDrawImage){
		(*pfCadOnEventDrawImage)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventSaveDib (F_SAVEDIB pFunc)
	{
	  tfCadOnEventSaveDib pfCadOnEventSaveDib;
	  pfCadOnEventSaveDib = (tfCadOnEventSaveDib)GetProcAddress( ghLibInst, "CadOnEventSaveDib" );
	  if (pfCadOnEventSaveDib){
		(*pfCadOnEventSaveDib)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventEntCreate (F_ENTCREATE pFunc)
	{
	  tfCadOnEventEntCreate pfCadOnEventEntCreate;
	  pfCadOnEventEntCreate = (tfCadOnEventEntCreate)GetProcAddress( ghLibInst, "CadOnEventEntCreate" );
	  if (pfCadOnEventEntCreate){
		(*pfCadOnEventEntCreate)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventEntLoad (F_ENTLOAD pFunc)
	{
	  tfCadOnEventEntLoad pfCadOnEventEntLoad;
	  pfCadOnEventEntLoad = (tfCadOnEventEntLoad)GetProcAddress( ghLibInst, "CadOnEventEntLoad" );
	  if (pfCadOnEventEntLoad){
		(*pfCadOnEventEntLoad)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventEntCopy (F_ENTCOPY pFunc)
	{
	  tfCadOnEventEntCopy pfCadOnEventEntCopy;
	  pfCadOnEventEntCopy = (tfCadOnEventEntCopy)GetProcAddress( ghLibInst, "CadOnEventEntCopy" );
	  if (pfCadOnEventEntCopy){
		(*pfCadOnEventEntCopy)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventEntErase (F_ENTERASE pFunc)
	{
	  tfCadOnEventEntErase pfCadOnEventEntErase;
	  pfCadOnEventEntErase = (tfCadOnEventEntErase)GetProcAddress( ghLibInst, "CadOnEventEntErase" );
	  if (pfCadOnEventEntErase){
		(*pfCadOnEventEntErase)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventEntMove (F_ENTMOVE pFunc)
	{
	  tfCadOnEventEntMove pfCadOnEventEntMove;
	  pfCadOnEventEntMove = (tfCadOnEventEntMove)GetProcAddress( ghLibInst, "CadOnEventEntMove" );
	  if (pfCadOnEventEntMove){
		(*pfCadOnEventEntMove)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventEntRotate (F_ENTROTATE pFunc)
	{
	  tfCadOnEventEntRotate pfCadOnEventEntRotate;
	  pfCadOnEventEntRotate = (tfCadOnEventEntRotate)GetProcAddress( ghLibInst, "CadOnEventEntRotate" );
	  if (pfCadOnEventEntRotate){
		(*pfCadOnEventEntRotate)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventEntScale (F_ENTSCALE pFunc)
	{
	  tfCadOnEventEntScale pfCadOnEventEntScale;
	  pfCadOnEventEntScale = (tfCadOnEventEntScale)GetProcAddress( ghLibInst, "CadOnEventEntScale" );
	  if (pfCadOnEventEntScale){
		(*pfCadOnEventEntScale)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventEntChange (F_ENTCHANGE pFunc)
	{
	  tfCadOnEventEntChange pfCadOnEventEntChange;
	  pfCadOnEventEntChange = (tfCadOnEventEntChange)GetProcAddress( ghLibInst, "CadOnEventEntChange" );
	  if (pfCadOnEventEntChange){
		(*pfCadOnEventEntChange)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventEntSelect (F_ENTSELECT pFunc)
	{
	  tfCadOnEventEntSelect pfCadOnEventEntSelect;
	  pfCadOnEventEntSelect = (tfCadOnEventEntSelect)GetProcAddress( ghLibInst, "CadOnEventEntSelect" );
	  if (pfCadOnEventEntSelect){
		(*pfCadOnEventEntSelect)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventPlineInsVer (F_PLINEINSVER pFunc)
	{
	  tfCadOnEventPlineInsVer pfCadOnEventPlineInsVer;
	  pfCadOnEventPlineInsVer = (tfCadOnEventPlineInsVer)GetProcAddress( ghLibInst, "CadOnEventPlineInsVer" );
	  if (pfCadOnEventPlineInsVer){
		(*pfCadOnEventPlineInsVer)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventPlineDelVer (F_PLINEDELVER pFunc)
	{
	  tfCadOnEventPlineDelVer pfCadOnEventPlineDelVer;
	  pfCadOnEventPlineDelVer = (tfCadOnEventPlineDelVer)GetProcAddress( ghLibInst, "CadOnEventPlineDelVer" );
	  if (pfCadOnEventPlineDelVer){
		(*pfCadOnEventPlineDelVer)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventPlineEditVer (F_PLINEEDITVER pFunc)
	{
	  tfCadOnEventPlineEditVer pfCadOnEventPlineEditVer;
	  pfCadOnEventPlineEditVer = (tfCadOnEventPlineEditVer)GetProcAddress( ghLibInst, "CadOnEventPlineEditVer" );
	  if (pfCadOnEventPlineEditVer){
		(*pfCadOnEventPlineEditVer)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventExecute (F_EXECUTE pFunc)
	{
	  tfCadOnEventExecute pfCadOnEventExecute;
	  pfCadOnEventExecute = (tfCadOnEventExecute)GetProcAddress( ghLibInst, "CadOnEventExecute" );
	  if (pfCadOnEventExecute){
		(*pfCadOnEventExecute)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventGripDrag (F_GRIPDRAG pFunc)
	{
	  tfCadOnEventGripDrag pfCadOnEventGripDrag;
	  pfCadOnEventGripDrag = (tfCadOnEventGripDrag)GetProcAddress( ghLibInst, "CadOnEventGripDrag" );
	  if (pfCadOnEventGripDrag){
		(*pfCadOnEventGripDrag)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventGripMove (F_GRIPMOVE pFunc)
	{
	  tfCadOnEventGripMove pfCadOnEventGripMove;
	  pfCadOnEventGripMove = (tfCadOnEventGripMove)GetProcAddress( ghLibInst, "CadOnEventGripMove" );
	  if (pfCadOnEventGripMove){
		(*pfCadOnEventGripMove)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCmdStart (F_CMDSTART pFunc)
	{
	  tfCadOnEventCmdStart pfCadOnEventCmdStart;
	  pfCadOnEventCmdStart = (tfCadOnEventCmdStart)GetProcAddress( ghLibInst, "CadOnEventCmdStart" );
	  if (pfCadOnEventCmdStart){
		(*pfCadOnEventCmdStart)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCmdLBDown (F_CMDLBDOWN pFunc)
	{
	  tfCadOnEventCmdLBDown pfCadOnEventCmdLBDown;
	  pfCadOnEventCmdLBDown = (tfCadOnEventCmdLBDown)GetProcAddress( ghLibInst, "CadOnEventCmdLBDown" );
	  if (pfCadOnEventCmdLBDown){
		(*pfCadOnEventCmdLBDown)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCmdFinish (F_CMDFINISH pFunc)
	{
	  tfCadOnEventCmdFinish pfCadOnEventCmdFinish;
	  pfCadOnEventCmdFinish = (tfCadOnEventCmdFinish)GetProcAddress( ghLibInst, "CadOnEventCmdFinish" );
	  if (pfCadOnEventCmdFinish){
		(*pfCadOnEventCmdFinish)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventEngrave (F_ENGRAVE pFunc)
	{
	  tfCadOnEventEngrave pfCadOnEventEngrave;
	  pfCadOnEventEngrave = (tfCadOnEventEngrave)GetProcAddress( ghLibInst, "CadOnEventEngrave" );
	  if (pfCadOnEventEngrave){
		(*pfCadOnEventEngrave)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventPolyFill (F_POLYFILL pFunc, BOOL bText)
	{
	  tfCadOnEventPolyFill pfCadOnEventPolyFill;
	  pfCadOnEventPolyFill = (tfCadOnEventPolyFill)GetProcAddress( ghLibInst, "CadOnEventPolyFill" );
	  if (pfCadOnEventPolyFill){
		(*pfCadOnEventPolyFill)(pFunc, bText);
	  }
	}


	//--------------
	void CADAPI CadOnEventBlockCreate (F_BLOCKCREATE pFunc)
	{
	  tfCadOnEventBlockCreate pfCadOnEventBlockCreate;
	  pfCadOnEventBlockCreate = (tfCadOnEventBlockCreate)GetProcAddress( ghLibInst, "CadOnEventBlockCreate" );
	  if (pfCadOnEventBlockCreate){
		(*pfCadOnEventBlockCreate)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCEntGetName (F_CE_GETNAME pFunc)
	{
	  tfCadOnEventCEntGetName pfCadOnEventCEntGetName;
	  pfCadOnEventCEntGetName = (tfCadOnEventCEntGetName)GetProcAddress( ghLibInst, "CadOnEventCEntGetName" );
	  if (pfCadOnEventCEntGetName){
		(*pfCadOnEventCEntGetName)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCEntGetProps (F_CE_GETPROPS pFunc)
	{
	  tfCadOnEventCEntGetProps pfCadOnEventCEntGetProps;
	  pfCadOnEventCEntGetProps = (tfCadOnEventCEntGetProps)GetProcAddress( ghLibInst, "CadOnEventCEntGetProps" );
	  if (pfCadOnEventCEntGetProps){
		(*pfCadOnEventCEntGetProps)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCEntPutProp (F_CE_PUTPROP pFunc)
	{
	  tfCadOnEventCEntPutProp pfCadOnEventCEntPutProp;
	  pfCadOnEventCEntPutProp = (tfCadOnEventCEntPutProp)GetProcAddress( ghLibInst, "CadOnEventCEntPutProp" );
	  if (pfCadOnEventCEntPutProp){
		(*pfCadOnEventCEntPutProp)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCEntGetExts (F_CE_GETEXTS pFunc)
	{
	  tfCadOnEventCEntGetExts pfCadOnEventCEntGetExts;
	  pfCadOnEventCEntGetExts = (tfCadOnEventCEntGetExts)GetProcAddress( ghLibInst, "CadOnEventCEntGetExts" );
	  if (pfCadOnEventCEntGetExts){
		(*pfCadOnEventCEntGetExts)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCEntNumGrips (F_CE_NGRIPS pFunc)
	{
	  tfCadOnEventCEntNumGrips pfCadOnEventCEntNumGrips;
	  pfCadOnEventCEntNumGrips = (tfCadOnEventCEntNumGrips)GetProcAddress( ghLibInst, "CadOnEventCEntNumGrips" );
	  if (pfCadOnEventCEntNumGrips){
		(*pfCadOnEventCEntNumGrips)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCEntGetGrip (F_CE_GETGRIP pFunc)
	{
	  tfCadOnEventCEntGetGrip pfCadOnEventCEntGetGrip;
	  pfCadOnEventCEntGetGrip = (tfCadOnEventCEntGetGrip)GetProcAddress( ghLibInst, "CadOnEventCEntGetGrip" );
	  if (pfCadOnEventCEntGetGrip){
		(*pfCadOnEventCEntGetGrip)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCEntMoveGrip (F_CE_MOVEGRIP pFunc)
	{
	  tfCadOnEventCEntMoveGrip pfCadOnEventCEntMoveGrip;
	  pfCadOnEventCEntMoveGrip = (tfCadOnEventCEntMoveGrip)GetProcAddress( ghLibInst, "CadOnEventCEntMoveGrip" );
	  if (pfCadOnEventCEntMoveGrip){
		(*pfCadOnEventCEntMoveGrip)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCEntMove (F_CE_MOVE pFunc)
	{
	  tfCadOnEventCEntMove pfCadOnEventCEntMove;
	  pfCadOnEventCEntMove = (tfCadOnEventCEntMove)GetProcAddress( ghLibInst, "CadOnEventCEntMove" );
	  if (pfCadOnEventCEntMove){
		(*pfCadOnEventCEntMove)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCEntRotate (F_CE_ROTATE pFunc)
	{
	  tfCadOnEventCEntRotate pfCadOnEventCEntRotate;
	  pfCadOnEventCEntRotate = (tfCadOnEventCEntRotate)GetProcAddress( ghLibInst, "CadOnEventCEntRotate" );
	  if (pfCadOnEventCEntRotate){
		(*pfCadOnEventCEntRotate)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCEntScale (F_CE_SCALE pFunc)
	{
	  tfCadOnEventCEntScale pfCadOnEventCEntScale;
	  pfCadOnEventCEntScale = (tfCadOnEventCEntScale)GetProcAddress( ghLibInst, "CadOnEventCEntScale" );
	  if (pfCadOnEventCEntScale){
		(*pfCadOnEventCEntScale)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCEntMirror (F_CE_MIRROR pFunc)
	{
	  tfCadOnEventCEntMirror pfCadOnEventCEntMirror;
	  pfCadOnEventCEntMirror = (tfCadOnEventCEntMirror)GetProcAddress( ghLibInst, "CadOnEventCEntMirror" );
	  if (pfCadOnEventCEntMirror){
		(*pfCadOnEventCEntMirror)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCEntDisplay (F_CE_DISPLAY pFunc)
	{
	  tfCadOnEventCEntDisplay pfCadOnEventCEntDisplay;
	  pfCadOnEventCEntDisplay = (tfCadOnEventCEntDisplay)GetProcAddress( ghLibInst, "CadOnEventCEntDisplay" );
	  if (pfCadOnEventCEntDisplay){
		(*pfCadOnEventCEntDisplay)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCCmdExecute (F_CC_EXECUTE pFunc)
	{
	  tfCadOnEventCCmdExecute pfCadOnEventCCmdExecute;
	  pfCadOnEventCCmdExecute = (tfCadOnEventCCmdExecute)GetProcAddress( ghLibInst, "CadOnEventCCmdExecute" );
	  if (pfCadOnEventCCmdExecute){
		(*pfCadOnEventCCmdExecute)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadOnEventCCmdDrag (F_CC_DRAG pFunc)
	{
	  tfCadOnEventCCmdDrag pfCadOnEventCCmdDrag;
	  pfCadOnEventCCmdDrag = (tfCadOnEventCCmdDrag)GetProcAddress( ghLibInst, "CadOnEventCCmdDrag" );
	  if (pfCadOnEventCCmdDrag){
		(*pfCadOnEventCCmdDrag)(pFunc);
	  }
	}


	//--------------
	void CADAPI CadSetReturnStr (LPCTSTR szText)
	{
	  tfCadSetReturnStr pfCadSetReturnStr;
	  pfCadSetReturnStr = (tfCadSetReturnStr)GetProcAddress( ghLibInst, "CadSetReturnStr" );
	  if (pfCadSetReturnStr){
		(*pfCadSetReturnStr)(szText);
	  }
	}


	//--------------
	void CADAPI CadSetReturnInt (int val)
	{
	  tfCadSetReturnInt pfCadSetReturnInt;
	  pfCadSetReturnInt = (tfCadSetReturnInt)GetProcAddress( ghLibInst, "CadSetReturnInt" );
	  if (pfCadSetReturnInt){
		(*pfCadSetReturnInt)(val);
	  }
	}


	//--------------
	void CADAPI CadSetReturnDbl (double val)
	{
	  tfCadSetReturnDbl pfCadSetReturnDbl;
	  pfCadSetReturnDbl = (tfCadSetReturnDbl)GetProcAddress( ghLibInst, "CadSetReturnDbl" );
	  if (pfCadSetReturnDbl){
		(*pfCadSetReturnDbl)(val);
	  }
	}


	//--------------
	double CADAPI CadGetReturnX ()
	{
	  tfCadGetReturnX pfCadGetReturnX;
	  pfCadGetReturnX = (tfCadGetReturnX)GetProcAddress( ghLibInst, "CadGetReturnX" );
	  if (pfCadGetReturnX){
		return (*pfCadGetReturnX)();
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetReturnY ()
	{
	  tfCadGetReturnY pfCadGetReturnY;
	  pfCadGetReturnY = (tfCadGetReturnY)GetProcAddress( ghLibInst, "CadGetReturnY" );
	  if (pfCadGetReturnY){
		return (*pfCadGetReturnY)();
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetReturnZ ()
	{
	  tfCadGetReturnZ pfCadGetReturnZ;
	  pfCadGetReturnZ = (tfCadGetReturnZ)GetProcAddress( ghLibInst, "CadGetReturnZ" );
	  if (pfCadGetReturnZ){
		return (*pfCadGetReturnZ)();
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetReturnVar ()
	{
	  tfCadGetReturnVar pfCadGetReturnVar;
	  pfCadGetReturnVar = (tfCadGetReturnVar)GetProcAddress( ghLibInst, "CadGetReturnVar" );
	  if (pfCadGetReturnVar){
		return (*pfCadGetReturnVar)();
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadSetParam (int Param, int Value)
	{
	  tfCadSetParam pfCadSetParam;
	  pfCadSetParam = (tfCadSetParam)GetProcAddress( ghLibInst, "CadSetParam" );
	  if (pfCadSetParam){
		return (*pfCadSetParam)(Param, Value);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadGetParam (int Param)
	{
	  tfCadGetParam pfCadGetParam;
	  pfCadGetParam = (tfCadGetParam)GetProcAddress( ghLibInst, "CadGetParam" );
	  if (pfCadGetParam){
		return (*pfCadGetParam)(Param);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetDefaultDir (LPCTSTR szDir)
	{
	  tfCadSetDefaultDir pfCadSetDefaultDir;
	  pfCadSetDefaultDir = (tfCadSetDefaultDir)GetProcAddress( ghLibInst, "CadSetDefaultDir" );
	  if (pfCadSetDefaultDir){
		(*pfCadSetDefaultDir)(szDir);
	  }
	}


	//--------------
	void CADAPI CadGetDefaultDir (TCHAR* szDir)
	{
	  tfCadGetDefaultDir pfCadGetDefaultDir;
	  pfCadGetDefaultDir = (tfCadGetDefaultDir)GetProcAddress( ghLibInst, "CadGetDefaultDir" );
	  if (pfCadGetDefaultDir){
		(*pfCadGetDefaultDir)(szDir);
	  }
	}


	//--------------
	BOOL CADAPI CadSetDefaultFont (LPCTSTR szFontFile)
	{
	  tfCadSetDefaultFont pfCadSetDefaultFont;
	  pfCadSetDefaultFont = (tfCadSetDefaultFont)GetProcAddress( ghLibInst, "CadSetDefaultFont" );
	  if (pfCadSetDefaultFont){
		return (*pfCadSetDefaultFont)(szFontFile);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGetDefaultFont (TCHAR* szFontFile)
	{
	  tfCadGetDefaultFont pfCadGetDefaultFont;
	  pfCadGetDefaultFont = (tfCadGetDefaultFont)GetProcAddress( ghLibInst, "CadGetDefaultFont" );
	  if (pfCadGetDefaultFont){
		(*pfCadGetDefaultFont)(szFontFile);
	  }
	}


	//--------------
	void CADAPI CadSetMsgTitle (LPCTSTR szTitle)
	{
	  tfCadSetMsgTitle pfCadSetMsgTitle;
	  pfCadSetMsgTitle = (tfCadSetMsgTitle)GetProcAddress( ghLibInst, "CadSetMsgTitle" );
	  if (pfCadSetMsgTitle){
		(*pfCadSetMsgTitle)(szTitle);
	  }
	}


	//--------------
	void CADAPI CadSetViewCoefs (double ZoomVal, double PanHor, double PanVer)
	{
	  tfCadSetViewCoefs pfCadSetViewCoefs;
	  pfCadSetViewCoefs = (tfCadSetViewCoefs)GetProcAddress( ghLibInst, "CadSetViewCoefs" );
	  if (pfCadSetViewCoefs){
		(*pfCadSetViewCoefs)(ZoomVal, PanHor, PanVer);
	  }
	}


	//--------------
	void CADAPI CadGetViewCoefs (double* pZoomVal, double* pPanHor, double* pPanVer)
	{
	  tfCadGetViewCoefs pfCadGetViewCoefs;
	  pfCadGetViewCoefs = (tfCadGetViewCoefs)GetProcAddress( ghLibInst, "CadGetViewCoefs" );
	  if (pfCadGetViewCoefs){
		(*pfCadGetViewCoefs)(pZoomVal, pPanHor, pPanVer);
	  }
	}


	//--------------
	BOOL CADAPI CadProfileLoad (LPCTSTR szName)
	{
	  tfCadProfileLoad pfCadProfileLoad;
	  pfCadProfileLoad = (tfCadProfileLoad)GetProcAddress( ghLibInst, "CadProfileLoad" );
	  if (pfCadProfileLoad){
		return (*pfCadProfileLoad)(szName);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadProfileSave (LPCTSTR szName)
	{
	  tfCadProfileSave pfCadProfileSave;
	  pfCadProfileSave = (tfCadProfileSave)GetProcAddress( ghLibInst, "CadProfileSave" );
	  if (pfCadProfileSave){
		return (*pfCadProfileSave)(szName);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadProfileGetName (TCHAR* szName)
	{
	  tfCadProfileGetName pfCadProfileGetName;
	  pfCadProfileGetName = (tfCadProfileGetName)GetProcAddress( ghLibInst, "CadProfileGetName" );
	  if (pfCadProfileGetName){
		(*pfCadProfileGetName)(szName);
	  }
	}


	//--------------
	COLORREF CADAPI CadSetColor (UINT iColor, COLORREF ColorRGB)
	{
	  tfCadSetColor pfCadSetColor;
	  pfCadSetColor = (tfCadSetColor)GetProcAddress( ghLibInst, "CadSetColor" );
	  if (pfCadSetColor){
		return (*pfCadSetColor)(iColor, ColorRGB);
	  }
	  return 0;
	}


	//--------------
	COLORREF CADAPI CadGetColor (UINT iColor)
	{
	  tfCadGetColor pfCadGetColor;
	  pfCadGetColor = (tfCadGetColor)GetProcAddress( ghLibInst, "CadGetColor" );
	  if (pfCadGetColor){
		return (*pfCadGetColor)(iColor);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadSeekColor (COLORREF ColorRGB)
	{
	  tfCadSeekColor pfCadSeekColor;
	  pfCadSeekColor = (tfCadSeekColor)GetProcAddress( ghLibInst, "CadSeekColor" );
	  if (pfCadSeekColor){
		return (*pfCadSeekColor)(ColorRGB);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadLoadColors (LPCTSTR szFileName)
	{
	  tfCadLoadColors pfCadLoadColors;
	  pfCadLoadColors = (tfCadLoadColors)GetProcAddress( ghLibInst, "CadLoadColors" );
	  if (pfCadLoadColors){
		return (*pfCadLoadColors)(szFileName);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadSaveColors (LPCTSTR szFileName)
	{
	  tfCadSaveColors pfCadSaveColors;
	  pfCadSaveColors = (tfCadSaveColors)GetProcAddress( ghLibInst, "CadSaveColors" );
	  if (pfCadSaveColors){
		return (*pfCadSaveColors)(szFileName);
	  }
	  return 0;
	}


	//--------------
	COLORREF CADAPI CadColorPutRGB (UINT iColor, COLORREF ColorRGB)
	{
	  tfCadColorPutRGB pfCadColorPutRGB;
	  pfCadColorPutRGB = (tfCadColorPutRGB)GetProcAddress( ghLibInst, "CadColorPutRGB" );
	  if (pfCadColorPutRGB){
		return (*pfCadColorPutRGB)(iColor, ColorRGB);
	  }
	  return 0;
	}


	//--------------
	COLORREF CADAPI CadColorGetRGB (UINT iColor)
	{
	  tfCadColorGetRGB pfCadColorGetRGB;
	  pfCadColorGetRGB = (tfCadColorGetRGB)GetProcAddress( ghLibInst, "CadColorGetRGB" );
	  if (pfCadColorGetRGB){
		return (*pfCadColorGetRGB)(iColor);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadColorSeek (COLORREF ColorRGB)
	{
	  tfCadColorSeek pfCadColorSeek;
	  pfCadColorSeek = (tfCadColorSeek)GetProcAddress( ghLibInst, "CadColorSeek" );
	  if (pfCadColorSeek){
		return (*pfCadColorSeek)(ColorRGB);
	  }
	  return 0;
	}


	//--------------
	HBRUSH CADAPI CadGetBrush (UINT iColor)
	{
	  tfCadGetBrush pfCadGetBrush;
	  pfCadGetBrush = (tfCadGetBrush)GetProcAddress( ghLibInst, "CadGetBrush" );
	  if (pfCadGetBrush){
		return (*pfCadGetBrush)(iColor);
	  }
	  return 0;
	}


	//--------------
	HPEN CADAPI CadGetPen (UINT iColor, int Width)
	{
	  tfCadGetPen pfCadGetPen;
	  pfCadGetPen = (tfCadGetPen)GetProcAddress( ghLibInst, "CadGetPen" );
	  if (pfCadGetPen){
		return (*pfCadGetPen)(iColor, Width);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadGetLayerWndVisible ()
	{
	  tfCadGetLayerWndVisible pfCadGetLayerWndVisible;
	  pfCadGetLayerWndVisible = (tfCadGetLayerWndVisible)GetProcAddress( ghLibInst, "CadGetLayerWndVisible" );
	  if (pfCadGetLayerWndVisible){
		return (*pfCadGetLayerWndVisible)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetShowSysCursor (BOOL bShow)
	{
	  tfCadSetShowSysCursor pfCadSetShowSysCursor;
	  pfCadSetShowSysCursor = (tfCadSetShowSysCursor)GetProcAddress( ghLibInst, "CadSetShowSysCursor" );
	  if (pfCadSetShowSysCursor){
		(*pfCadSetShowSysCursor)(bShow);
	  }
	}


	//--------------
	BOOL CADAPI CadGetShowSysCursor ()
	{
	  tfCadGetShowSysCursor pfCadGetShowSysCursor;
	  pfCadGetShowSysCursor = (tfCadGetShowSysCursor)GetProcAddress( ghLibInst, "CadGetShowSysCursor" );
	  if (pfCadGetShowSysCursor){
		return (*pfCadGetShowSysCursor)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetCrossSize (UINT Size)
	{
	  tfCadSetCrossSize pfCadSetCrossSize;
	  pfCadSetCrossSize = (tfCadSetCrossSize)GetProcAddress( ghLibInst, "CadSetCrossSize" );
	  if (pfCadSetCrossSize){
		(*pfCadSetCrossSize)(Size);
	  }
	}


	//--------------
	UINT CADAPI CadGetCrossSize ()
	{
	  tfCadGetCrossSize pfCadGetCrossSize;
	  pfCadGetCrossSize = (tfCadGetCrossSize)GetProcAddress( ghLibInst, "CadGetCrossSize" );
	  if (pfCadGetCrossSize){
		return (*pfCadGetCrossSize)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetShowCross (BOOL bShow)
	{
	  tfCadSetShowCross pfCadSetShowCross;
	  pfCadSetShowCross = (tfCadSetShowCross)GetProcAddress( ghLibInst, "CadSetShowCross" );
	  if (pfCadSetShowCross){
		(*pfCadSetShowCross)(bShow);
	  }
	}


	//--------------
	BOOL CADAPI CadGetShowCross ()
	{
	  tfCadGetShowCross pfCadGetShowCross;
	  pfCadGetShowCross = (tfCadGetShowCross)GetProcAddress( ghLibInst, "CadGetShowCross" );
	  if (pfCadGetShowCross){
		return (*pfCadGetShowCross)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetCurveQuality (UINT Quality)
	{
	  tfCadSetCurveQuality pfCadSetCurveQuality;
	  pfCadSetCurveQuality = (tfCadSetCurveQuality)GetProcAddress( ghLibInst, "CadSetCurveQuality" );
	  if (pfCadSetCurveQuality){
		(*pfCadSetCurveQuality)(Quality);
	  }
	}


	//--------------
	UINT CADAPI CadGetCurveQuality ()
	{
	  tfCadGetCurveQuality pfCadGetCurveQuality;
	  pfCadGetCurveQuality = (tfCadGetCurveQuality)GetProcAddress( ghLibInst, "CadGetCurveQuality" );
	  if (pfCadGetCurveQuality){
		return (*pfCadGetCurveQuality)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetCharQuality (UINT Quality)
	{
	  tfCadSetCharQuality pfCadSetCharQuality;
	  pfCadSetCharQuality = (tfCadSetCharQuality)GetProcAddress( ghLibInst, "CadSetCharQuality" );
	  if (pfCadSetCharQuality){
		(*pfCadSetCharQuality)(Quality);
	  }
	}


	//--------------
	UINT CADAPI CadGetCharQuality ()
	{
	  tfCadGetCharQuality pfCadGetCharQuality;
	  pfCadGetCharQuality = (tfCadGetCharQuality)GetProcAddress( ghLibInst, "CadGetCharQuality" );
	  if (pfCadGetCharQuality){
		return (*pfCadGetCharQuality)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetDrawCheckStep (UINT Step)
	{
	  tfCadSetDrawCheckStep pfCadSetDrawCheckStep;
	  pfCadSetDrawCheckStep = (tfCadSetDrawCheckStep)GetProcAddress( ghLibInst, "CadSetDrawCheckStep" );
	  if (pfCadSetDrawCheckStep){
		(*pfCadSetDrawCheckStep)(Step);
	  }
	}


	//--------------
	UINT CADAPI CadGetDrawCheckStep ()
	{
	  tfCadGetDrawCheckStep pfCadGetDrawCheckStep;
	  pfCadGetDrawCheckStep = (tfCadGetDrawCheckStep)GetProcAddress( ghLibInst, "CadGetDrawCheckStep" );
	  if (pfCadGetDrawCheckStep){
		return (*pfCadGetDrawCheckStep)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetMinCharSize (int Size)
	{
	  tfCadSetMinCharSize pfCadSetMinCharSize;
	  pfCadSetMinCharSize = (tfCadSetMinCharSize)GetProcAddress( ghLibInst, "CadSetMinCharSize" );
	  if (pfCadSetMinCharSize){
		(*pfCadSetMinCharSize)(Size);
	  }
	}


	//--------------
	int CADAPI CadGetMinCharSize ()
	{
	  tfCadGetMinCharSize pfCadGetMinCharSize;
	  pfCadGetMinCharSize = (tfCadGetMinCharSize)GetProcAddress( ghLibInst, "CadGetMinCharSize" );
	  if (pfCadGetMinCharSize){
		return (*pfCadGetMinCharSize)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetMinCharFSize (int Size)
	{
	  tfCadSetMinCharFSize pfCadSetMinCharFSize;
	  pfCadSetMinCharFSize = (tfCadSetMinCharFSize)GetProcAddress( ghLibInst, "CadSetMinCharFSize" );
	  if (pfCadSetMinCharFSize){
		(*pfCadSetMinCharFSize)(Size);
	  }
	}


	//--------------
	int CADAPI CadGetMinCharFSize ()
	{
	  tfCadGetMinCharFSize pfCadGetMinCharFSize;
	  pfCadGetMinCharFSize = (tfCadGetMinCharFSize)GetProcAddress( ghLibInst, "CadGetMinCharFSize" );
	  if (pfCadGetMinCharFSize){
		return (*pfCadGetMinCharFSize)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetMinEntSize (int Size)
	{
	  tfCadSetMinEntSize pfCadSetMinEntSize;
	  pfCadSetMinEntSize = (tfCadSetMinEntSize)GetProcAddress( ghLibInst, "CadSetMinEntSize" );
	  if (pfCadSetMinEntSize){
		(*pfCadSetMinEntSize)(Size);
	  }
	}


	//--------------
	int CADAPI CadGetMinEntSize ()
	{
	  tfCadGetMinEntSize pfCadGetMinEntSize;
	  pfCadGetMinEntSize = (tfCadGetMinEntSize)GetProcAddress( ghLibInst, "CadGetMinEntSize" );
	  if (pfCadGetMinEntSize){
		return (*pfCadGetMinEntSize)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetMiterLimit (int MLimit)
	{
	  tfCadSetMiterLimit pfCadSetMiterLimit;
	  pfCadSetMiterLimit = (tfCadSetMiterLimit)GetProcAddress( ghLibInst, "CadSetMiterLimit" );
	  if (pfCadSetMiterLimit){
		(*pfCadSetMiterLimit)(MLimit);
	  }
	}


	//--------------
	int CADAPI CadGetMiterLimit ()
	{
	  tfCadGetMiterLimit pfCadGetMiterLimit;
	  pfCadGetMiterLimit = (tfCadGetMiterLimit)GetProcAddress( ghLibInst, "CadGetMiterLimit" );
	  if (pfCadGetMiterLimit){
		return (*pfCadGetMiterLimit)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetAutoSel (BOOL bAutoSel)
	{
	  tfCadSetAutoSel pfCadSetAutoSel;
	  pfCadSetAutoSel = (tfCadSetAutoSel)GetProcAddress( ghLibInst, "CadSetAutoSel" );
	  if (pfCadSetAutoSel){
		(*pfCadSetAutoSel)(bAutoSel);
	  }
	}


	//--------------
	BOOL CADAPI CadGetAutoSel ()
	{
	  tfCadGetAutoSel pfCadGetAutoSel;
	  pfCadGetAutoSel = (tfCadGetAutoSel)GetProcAddress( ghLibInst, "CadGetAutoSel" );
	  if (pfCadGetAutoSel){
		return (*pfCadGetAutoSel)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetAutoSelRect (BOOL bAutoSelRect)
	{
	  tfCadSetAutoSelRect pfCadSetAutoSelRect;
	  pfCadSetAutoSelRect = (tfCadSetAutoSelRect)GetProcAddress( ghLibInst, "CadSetAutoSelRect" );
	  if (pfCadSetAutoSelRect){
		(*pfCadSetAutoSelRect)(bAutoSelRect);
	  }
	}


	//--------------
	int CADAPI CadGetAutoSelRect ()
	{
	  tfCadGetAutoSelRect pfCadGetAutoSelRect;
	  pfCadGetAutoSelRect = (tfCadGetAutoSelRect)GetProcAddress( ghLibInst, "CadGetAutoSelRect" );
	  if (pfCadGetAutoSelRect){
		return (*pfCadGetAutoSelRect)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetSelShiftAdd (BOOL bSelShiftAdd)
	{
	  tfCadSetSelShiftAdd pfCadSetSelShiftAdd;
	  pfCadSetSelShiftAdd = (tfCadSetSelShiftAdd)GetProcAddress( ghLibInst, "CadSetSelShiftAdd" );
	  if (pfCadSetSelShiftAdd){
		(*pfCadSetSelShiftAdd)(bSelShiftAdd);
	  }
	}


	//--------------
	BOOL CADAPI CadGetSelShiftAdd ()
	{
	  tfCadGetSelShiftAdd pfCadGetSelShiftAdd;
	  pfCadGetSelShiftAdd = (tfCadGetSelShiftAdd)GetProcAddress( ghLibInst, "CadGetSelShiftAdd" );
	  if (pfCadGetSelShiftAdd){
		return (*pfCadGetSelShiftAdd)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetSelInside (BOOL bSelInside)
	{
	  tfCadSetSelInside pfCadSetSelInside;
	  pfCadSetSelInside = (tfCadSetSelInside)GetProcAddress( ghLibInst, "CadSetSelInside" );
	  if (pfCadSetSelInside){
		(*pfCadSetSelInside)(bSelInside);
	  }
	}


	//--------------
	BOOL CADAPI CadGetSelInside ()
	{
	  tfCadGetSelInside pfCadGetSelInside;
	  pfCadGetSelInside = (tfCadGetSelInside)GetProcAddress( ghLibInst, "CadGetSelInside" );
	  if (pfCadGetSelInside){
		return (*pfCadGetSelInside)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetSelByLayer (BOOL bSelByLayer)
	{
	  tfCadSetSelByLayer pfCadSetSelByLayer;
	  pfCadSetSelByLayer = (tfCadSetSelByLayer)GetProcAddress( ghLibInst, "CadSetSelByLayer" );
	  if (pfCadSetSelByLayer){
		(*pfCadSetSelByLayer)(bSelByLayer);
	  }
	}


	//--------------
	BOOL CADAPI CadGetSelByLayer ()
	{
	  tfCadGetSelByLayer pfCadGetSelByLayer;
	  pfCadGetSelByLayer = (tfCadGetSelByLayer)GetProcAddress( ghLibInst, "CadGetSelByLayer" );
	  if (pfCadGetSelByLayer){
		return (*pfCadGetSelByLayer)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetUnselAfterEdit (BOOL bUnselAfterEdit)
	{
	  tfCadSetUnselAfterEdit pfCadSetUnselAfterEdit;
	  pfCadSetUnselAfterEdit = (tfCadSetUnselAfterEdit)GetProcAddress( ghLibInst, "CadSetUnselAfterEdit" );
	  if (pfCadSetUnselAfterEdit){
		(*pfCadSetUnselAfterEdit)(bUnselAfterEdit);
	  }
	}


	//--------------
	BOOL CADAPI CadGetUnselAfterEdit ()
	{
	  tfCadGetUnselAfterEdit pfCadGetUnselAfterEdit;
	  pfCadGetUnselAfterEdit = (tfCadGetUnselAfterEdit)GetProcAddress( ghLibInst, "CadGetUnselAfterEdit" );
	  if (pfCadGetUnselAfterEdit){
		return (*pfCadGetUnselAfterEdit)();
	  }
	  return 0;
	}


	//--------------
	COLORREF CADAPI CadSetSelColor (COLORREF SelColor)
	{
	  tfCadSetSelColor pfCadSetSelColor;
	  pfCadSetSelColor = (tfCadSetSelColor)GetProcAddress( ghLibInst, "CadSetSelColor" );
	  if (pfCadSetSelColor){
		return (*pfCadSetSelColor)(SelColor);
	  }
	  return 0;
	}


	//--------------
	COLORREF CADAPI CadGetSelColor ()
	{
	  tfCadGetSelColor pfCadGetSelColor;
	  pfCadGetSelColor = (tfCadGetSelColor)GetProcAddress( ghLibInst, "CadGetSelColor" );
	  if (pfCadGetSelColor){
		return (*pfCadGetSelColor)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetSelLine (int SelLine)
	{
	  tfCadSetSelLine pfCadSetSelLine;
	  pfCadSetSelLine = (tfCadSetSelLine)GetProcAddress( ghLibInst, "CadSetSelLine" );
	  if (pfCadSetSelLine){
		(*pfCadSetSelLine)(SelLine);
	  }
	}


	//--------------
	int CADAPI CadGetSelLine ()
	{
	  tfCadGetSelLine pfCadGetSelLine;
	  pfCadGetSelLine = (tfCadGetSelLine)GetProcAddress( ghLibInst, "CadGetSelLine" );
	  if (pfCadGetSelLine){
		return (*pfCadGetSelLine)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetPickboxSize (int PickboxSize)
	{
	  tfCadSetPickboxSize pfCadSetPickboxSize;
	  pfCadSetPickboxSize = (tfCadSetPickboxSize)GetProcAddress( ghLibInst, "CadSetPickboxSize" );
	  if (pfCadSetPickboxSize){
		(*pfCadSetPickboxSize)(PickboxSize);
	  }
	}


	//--------------
	int CADAPI CadGetPickboxSize ()
	{
	  tfCadGetPickboxSize pfCadGetPickboxSize;
	  pfCadGetPickboxSize = (tfCadGetPickboxSize)GetProcAddress( ghLibInst, "CadGetPickboxSize" );
	  if (pfCadGetPickboxSize){
		return (*pfCadGetPickboxSize)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetUseGrips (BOOL bUseGrips)
	{
	  tfCadSetUseGrips pfCadSetUseGrips;
	  pfCadSetUseGrips = (tfCadSetUseGrips)GetProcAddress( ghLibInst, "CadSetUseGrips" );
	  if (pfCadSetUseGrips){
		(*pfCadSetUseGrips)(bUseGrips);
	  }
	}


	//--------------
	BOOL CADAPI CadGetUseGrips ()
	{
	  tfCadGetUseGrips pfCadGetUseGrips;
	  pfCadGetUseGrips = (tfCadGetUseGrips)GetProcAddress( ghLibInst, "CadGetUseGrips" );
	  if (pfCadGetUseGrips){
		return (*pfCadGetUseGrips)();
	  }
	  return 0;
	}


	//--------------
	COLORREF CADAPI CadSetGripColor (COLORREF GripColor)
	{
	  tfCadSetGripColor pfCadSetGripColor;
	  pfCadSetGripColor = (tfCadSetGripColor)GetProcAddress( ghLibInst, "CadSetGripColor" );
	  if (pfCadSetGripColor){
		return (*pfCadSetGripColor)(GripColor);
	  }
	  return 0;
	}


	//--------------
	COLORREF CADAPI CadGetGripColor ()
	{
	  tfCadGetGripColor pfCadGetGripColor;
	  pfCadGetGripColor = (tfCadGetGripColor)GetProcAddress( ghLibInst, "CadGetGripColor" );
	  if (pfCadGetGripColor){
		return (*pfCadGetGripColor)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetGripSize (int GripSize)
	{
	  tfCadSetGripSize pfCadSetGripSize;
	  pfCadSetGripSize = (tfCadSetGripSize)GetProcAddress( ghLibInst, "CadSetGripSize" );
	  if (pfCadSetGripSize){
		(*pfCadSetGripSize)(GripSize);
	  }
	}


	//--------------
	int CADAPI CadGetGripSize ()
	{
	  tfCadGetGripSize pfCadGetGripSize;
	  pfCadGetGripSize = (tfCadGetGripSize)GetProcAddress( ghLibInst, "CadGetGripSize" );
	  if (pfCadGetGripSize){
		return (*pfCadGetGripSize)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetImageBorder (BOOL bImgBorder)
	{
	  tfCadSetImageBorder pfCadSetImageBorder;
	  pfCadSetImageBorder = (tfCadSetImageBorder)GetProcAddress( ghLibInst, "CadSetImageBorder" );
	  if (pfCadSetImageBorder){
		(*pfCadSetImageBorder)(bImgBorder);
	  }
	}


	//--------------
	BOOL CADAPI CadGetImageBorder ()
	{
	  tfCadGetImageBorder pfCadGetImageBorder;
	  pfCadGetImageBorder = (tfCadGetImageBorder)GetProcAddress( ghLibInst, "CadGetImageBorder" );
	  if (pfCadGetImageBorder){
		return (*pfCadGetImageBorder)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetDxfDecPrec (UINT dec)
	{
	  tfCadSetDxfDecPrec pfCadSetDxfDecPrec;
	  pfCadSetDxfDecPrec = (tfCadSetDxfDecPrec)GetProcAddress( ghLibInst, "CadSetDxfDecPrec" );
	  if (pfCadSetDxfDecPrec){
		(*pfCadSetDxfDecPrec)(dec);
	  }
	}


	//--------------
	UINT CADAPI CadGetDxfDecPrec ()
	{
	  tfCadGetDxfDecPrec pfCadGetDxfDecPrec;
	  pfCadGetDxfDecPrec = (tfCadGetDxfDecPrec)GetProcAddress( ghLibInst, "CadGetDxfDecPrec" );
	  if (pfCadGetDxfDecPrec){
		return (*pfCadGetDxfDecPrec)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetDxfVersion (UINT ver)
	{
	  tfCadSetDxfVersion pfCadSetDxfVersion;
	  pfCadSetDxfVersion = (tfCadSetDxfVersion)GetProcAddress( ghLibInst, "CadSetDxfVersion" );
	  if (pfCadSetDxfVersion){
		(*pfCadSetDxfVersion)(ver);
	  }
	}


	//--------------
	UINT CADAPI CadGetDxfVersion ()
	{
	  tfCadGetDxfVersion pfCadGetDxfVersion;
	  pfCadGetDxfVersion = (tfCadGetDxfVersion)GetProcAddress( ghLibInst, "CadGetDxfVersion" );
	  if (pfCadGetDxfVersion){
		return (*pfCadGetDxfVersion)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetDwgVersion (UINT ver)
	{
	  tfCadSetDwgVersion pfCadSetDwgVersion;
	  pfCadSetDwgVersion = (tfCadSetDwgVersion)GetProcAddress( ghLibInst, "CadSetDwgVersion" );
	  if (pfCadSetDwgVersion){
		(*pfCadSetDwgVersion)(ver);
	  }
	}


	//--------------
	UINT CADAPI CadGetDwgVersion ()
	{
	  tfCadGetDwgVersion pfCadGetDwgVersion;
	  pfCadGetDwgVersion = (tfCadGetDwgVersion)GetProcAddress( ghLibInst, "CadGetDwgVersion" );
	  if (pfCadGetDwgVersion){
		return (*pfCadGetDwgVersion)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetAngleUnit (int uang)
	{
	  tfCadSetAngleUnit pfCadSetAngleUnit;
	  pfCadSetAngleUnit = (tfCadSetAngleUnit)GetProcAddress( ghLibInst, "CadSetAngleUnit" );
	  if (pfCadSetAngleUnit){
		(*pfCadSetAngleUnit)(uang);
	  }
	}


	//--------------
	int CADAPI CadGetAngleUnit ()
	{
	  tfCadGetAngleUnit pfCadGetAngleUnit;
	  pfCadGetAngleUnit = (tfCadGetAngleUnit)GetProcAddress( ghLibInst, "CadGetAngleUnit" );
	  if (pfCadGetAngleUnit){
		return (*pfCadGetAngleUnit)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetFileFilter (int ExtType)
	{
	  tfCadSetFileFilter pfCadSetFileFilter;
	  pfCadSetFileFilter = (tfCadSetFileFilter)GetProcAddress( ghLibInst, "CadSetFileFilter" );
	  if (pfCadSetFileFilter){
		(*pfCadSetFileFilter)(ExtType);
	  }
	}


	//--------------
	int CADAPI CadGetFileFilter ()
	{
	  tfCadGetFileFilter pfCadGetFileFilter;
	  pfCadGetFileFilter = (tfCadGetFileFilter)GetProcAddress( ghLibInst, "CadGetFileFilter" );
	  if (pfCadGetFileFilter){
		return (*pfCadGetFileFilter)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadShowEmptyRect (BOOL bShow)
	{
	  tfCadShowEmptyRect pfCadShowEmptyRect;
	  pfCadShowEmptyRect = (tfCadShowEmptyRect)GetProcAddress( ghLibInst, "CadShowEmptyRect" );
	  if (pfCadShowEmptyRect){
		(*pfCadShowEmptyRect)(bShow);
	  }
	}


	//--------------
	void CADAPI CadSetBlinkTime (int nMSec)
	{
	  tfCadSetBlinkTime pfCadSetBlinkTime;
	  pfCadSetBlinkTime = (tfCadSetBlinkTime)GetProcAddress( ghLibInst, "CadSetBlinkTime" );
	  if (pfCadSetBlinkTime){
		(*pfCadSetBlinkTime)(nMSec);
	  }
	}


	//--------------
	VDWG CADAPI CadCreate ()
	{
	  tfCadCreate pfCadCreate;
	  pfCadCreate = (tfCadCreate)GetProcAddress( ghLibInst, "CadCreate" );
	  if (pfCadCreate){
		return (*pfCadCreate)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDelete (VDWG hDwg)
	{
	  tfCadDelete pfCadDelete;
	  pfCadDelete = (tfCadDelete)GetProcAddress( ghLibInst, "CadDelete" );
	  if (pfCadDelete){
		(*pfCadDelete)(hDwg);
	  }
	}


	//--------------
	void CADAPI CadPurge (VDWG hDwg, int Mode)
	{
	  tfCadPurge pfCadPurge;
	  pfCadPurge = (tfCadPurge)GetProcAddress( ghLibInst, "CadPurge" );
	  if (pfCadPurge){
		(*pfCadPurge)(hDwg, Mode);
	  }
	}


	//--------------
	void CADAPI CadFileNew (VDWG hDwg, HWND hWin)
	{
	  tfCadFileNew pfCadFileNew;
	  pfCadFileNew = (tfCadFileNew)GetProcAddress( ghLibInst, "CadFileNew" );
	  if (pfCadFileNew){
		(*pfCadFileNew)(hDwg, hWin);
	  }
	}


	//--------------
	BOOL CADAPI CadFileOpen (VDWG hDwg, HWND hWin, LPCTSTR szFileName)
	{
	  tfCadFileOpen pfCadFileOpen;
	  pfCadFileOpen = (tfCadFileOpen)GetProcAddress( ghLibInst, "CadFileOpen" );
	  if (pfCadFileOpen){
		return (*pfCadFileOpen)(hDwg, hWin, szFileName);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadFileOpenMem (VDWG hDwg, HWND hWin, void* pMem)
	{
	  tfCadFileOpenMem pfCadFileOpenMem;
	  pfCadFileOpenMem = (tfCadFileOpenMem)GetProcAddress( ghLibInst, "CadFileOpenMem" );
	  if (pfCadFileOpenMem){
		return (*pfCadFileOpenMem)(hDwg, hWin, pMem);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadFileSave (VDWG hDwg, HWND hWin)
	{
	  tfCadFileSave pfCadFileSave;
	  pfCadFileSave = (tfCadFileSave)GetProcAddress( ghLibInst, "CadFileSave" );
	  if (pfCadFileSave){
		return (*pfCadFileSave)(hDwg, hWin);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadFileSaveAs (VDWG hDwg, HWND hWin, LPCTSTR szFileName)
	{
	  tfCadFileSaveAs pfCadFileSaveAs;
	  pfCadFileSaveAs = (tfCadFileSaveAs)GetProcAddress( ghLibInst, "CadFileSaveAs" );
	  if (pfCadFileSaveAs){
		return (*pfCadFileSaveAs)(hDwg, hWin, szFileName);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadFileSaveMem (VDWG hDwg, HWND hWin, void* pMem, UINT MaxSize)
	{
	  tfCadFileSaveMem pfCadFileSaveMem;
	  pfCadFileSaveMem = (tfCadFileSaveMem)GetProcAddress( ghLibInst, "CadFileSaveMem" );
	  if (pfCadFileSaveMem){
		return (*pfCadFileSaveMem)(hDwg, hWin, pMem, MaxSize);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRasterize (VDWG hDwg, LPCTSTR szFileName, double Left, double Bottom, double Right, double Top, double Res)
	{
	  tfCadRasterize pfCadRasterize;
	  pfCadRasterize = (tfCadRasterize)GetProcAddress( ghLibInst, "CadRasterize" );
	  if (pfCadRasterize){
		return (*pfCadRasterize)(hDwg, szFileName, Left, Bottom, Right, Top, Res);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadFireLoadSaveEvent (VDWG hDwg, int Mode, int Step, int Percent)
	{
	  tfCadFireLoadSaveEvent pfCadFireLoadSaveEvent;
	  pfCadFireLoadSaveEvent = (tfCadFireLoadSaveEvent)GetProcAddress( ghLibInst, "CadFireLoadSaveEvent" );
	  if (pfCadFireLoadSaveEvent){
		(*pfCadFireLoadSaveEvent)(hDwg, Mode, Step, Percent);
	  }
	}


	//--------------
	void CADAPI CadPutOwner (VDWG hDwg, void* pObject)
	{
	  tfCadPutOwner pfCadPutOwner;
	  pfCadPutOwner = (tfCadPutOwner)GetProcAddress( ghLibInst, "CadPutOwner" );
	  if (pfCadPutOwner){
		(*pfCadPutOwner)(hDwg, pObject);
	  }
	}


	//--------------
	DWORD CADAPI CadGetOwner (VDWG hDwg)
	{
	  tfCadGetOwner pfCadGetOwner;
	  pfCadGetOwner = (tfCadGetOwner)GetProcAddress( ghLibInst, "CadGetOwner" );
	  if (pfCadGetOwner){
		return (*pfCadGetOwner)(hDwg);
	  }
	  return 0;
	}


	//--------------
	HWND CADAPI CadGetWindow (VDWG hDwg)
	{
	  tfCadGetWindow pfCadGetWindow;
	  pfCadGetWindow = (tfCadGetWindow)GetProcAddress( ghLibInst, "CadGetWindow" );
	  if (pfCadGetWindow){
		return (*pfCadGetWindow)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPutWindow (VDWG hDwg, HWND hWnd)
	{
	  tfCadPutWindow pfCadPutWindow;
	  pfCadPutWindow = (tfCadPutWindow)GetProcAddress( ghLibInst, "CadPutWindow" );
	  if (pfCadPutWindow){
		(*pfCadPutWindow)(hDwg, hWnd);
	  }
	}


	//--------------
	void CADAPI CadPutFileName (VDWG hDwg, LPCTSTR szFileName)
	{
	  tfCadPutFileName pfCadPutFileName;
	  pfCadPutFileName = (tfCadPutFileName)GetProcAddress( ghLibInst, "CadPutFileName" );
	  if (pfCadPutFileName){
		(*pfCadPutFileName)(hDwg, szFileName);
	  }
	}


	//--------------
	void CADAPI CadGetFileName (VDWG hDwg, TCHAR* szFileName)
	{
	  tfCadGetFileName pfCadGetFileName;
	  pfCadGetFileName = (tfCadGetFileName)GetProcAddress( ghLibInst, "CadGetFileName" );
	  if (pfCadGetFileName){
		(*pfCadGetFileName)(hDwg, szFileName);
	  }
	}


	//--------------
	void CADAPI CadGetShortFileName (VDWG hDwg, TCHAR* szFileName)
	{
	  tfCadGetShortFileName pfCadGetShortFileName;
	  pfCadGetShortFileName = (tfCadGetShortFileName)GetProcAddress( ghLibInst, "CadGetShortFileName" );
	  if (pfCadGetShortFileName){
		(*pfCadGetShortFileName)(hDwg, szFileName);
	  }
	}


	//--------------
	double CADAPI CadGetExtentXmin (VDWG hDwg)
	{
	  tfCadGetExtentXmin pfCadGetExtentXmin;
	  pfCadGetExtentXmin = (tfCadGetExtentXmin)GetProcAddress( ghLibInst, "CadGetExtentXmin" );
	  if (pfCadGetExtentXmin){
		return (*pfCadGetExtentXmin)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetExtentYmin (VDWG hDwg)
	{
	  tfCadGetExtentYmin pfCadGetExtentYmin;
	  pfCadGetExtentYmin = (tfCadGetExtentYmin)GetProcAddress( ghLibInst, "CadGetExtentYmin" );
	  if (pfCadGetExtentYmin){
		return (*pfCadGetExtentYmin)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetExtentZmin (VDWG hDwg)
	{
	  tfCadGetExtentZmin pfCadGetExtentZmin;
	  pfCadGetExtentZmin = (tfCadGetExtentZmin)GetProcAddress( ghLibInst, "CadGetExtentZmin" );
	  if (pfCadGetExtentZmin){
		return (*pfCadGetExtentZmin)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetExtentXmax (VDWG hDwg)
	{
	  tfCadGetExtentXmax pfCadGetExtentXmax;
	  pfCadGetExtentXmax = (tfCadGetExtentXmax)GetProcAddress( ghLibInst, "CadGetExtentXmax" );
	  if (pfCadGetExtentXmax){
		return (*pfCadGetExtentXmax)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetExtentYmax (VDWG hDwg)
	{
	  tfCadGetExtentYmax pfCadGetExtentYmax;
	  pfCadGetExtentYmax = (tfCadGetExtentYmax)GetProcAddress( ghLibInst, "CadGetExtentYmax" );
	  if (pfCadGetExtentYmax){
		return (*pfCadGetExtentYmax)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetExtentZmax (VDWG hDwg)
	{
	  tfCadGetExtentZmax pfCadGetExtentZmax;
	  pfCadGetExtentZmax = (tfCadGetExtentZmax)GetProcAddress( ghLibInst, "CadGetExtentZmax" );
	  if (pfCadGetExtentZmax){
		return (*pfCadGetExtentZmax)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetExtentLeft (VDWG hDwg)
	{
	  tfCadGetExtentLeft pfCadGetExtentLeft;
	  pfCadGetExtentLeft = (tfCadGetExtentLeft)GetProcAddress( ghLibInst, "CadGetExtentLeft" );
	  if (pfCadGetExtentLeft){
		return (*pfCadGetExtentLeft)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetExtentRight (VDWG hDwg)
	{
	  tfCadGetExtentRight pfCadGetExtentRight;
	  pfCadGetExtentRight = (tfCadGetExtentRight)GetProcAddress( ghLibInst, "CadGetExtentRight" );
	  if (pfCadGetExtentRight){
		return (*pfCadGetExtentRight)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetExtentTop (VDWG hDwg)
	{
	  tfCadGetExtentTop pfCadGetExtentTop;
	  pfCadGetExtentTop = (tfCadGetExtentTop)GetProcAddress( ghLibInst, "CadGetExtentTop" );
	  if (pfCadGetExtentTop){
		return (*pfCadGetExtentTop)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetExtentBottom (VDWG hDwg)
	{
	  tfCadGetExtentBottom pfCadGetExtentBottom;
	  pfCadGetExtentBottom = (tfCadGetExtentBottom)GetProcAddress( ghLibInst, "CadGetExtentBottom" );
	  if (pfCadGetExtentBottom){
		return (*pfCadGetExtentBottom)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGetExtentRect (VDWG hDwg, double* pLeft, double* pBottom, double* pRight, double* pTop)
	{
	  tfCadGetExtentRect pfCadGetExtentRect;
	  pfCadGetExtentRect = (tfCadGetExtentRect)GetProcAddress( ghLibInst, "CadGetExtentRect" );
	  if (pfCadGetExtentRect){
		(*pfCadGetExtentRect)(hDwg, pLeft, pBottom, pRight, pTop);
	  }
	}


	//--------------
	double CADAPI CadGetWinLeft (VDWG hDwg)
	{
	  tfCadGetWinLeft pfCadGetWinLeft;
	  pfCadGetWinLeft = (tfCadGetWinLeft)GetProcAddress( ghLibInst, "CadGetWinLeft" );
	  if (pfCadGetWinLeft){
		return (*pfCadGetWinLeft)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetWinRight (VDWG hDwg)
	{
	  tfCadGetWinRight pfCadGetWinRight;
	  pfCadGetWinRight = (tfCadGetWinRight)GetProcAddress( ghLibInst, "CadGetWinRight" );
	  if (pfCadGetWinRight){
		return (*pfCadGetWinRight)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetWinTop (VDWG hDwg)
	{
	  tfCadGetWinTop pfCadGetWinTop;
	  pfCadGetWinTop = (tfCadGetWinTop)GetProcAddress( ghLibInst, "CadGetWinTop" );
	  if (pfCadGetWinTop){
		return (*pfCadGetWinTop)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadGetWinBottom (VDWG hDwg)
	{
	  tfCadGetWinBottom pfCadGetWinBottom;
	  pfCadGetWinBottom = (tfCadGetWinBottom)GetProcAddress( ghLibInst, "CadGetWinBottom" );
	  if (pfCadGetWinBottom){
		return (*pfCadGetWinBottom)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGetWinRect (VDWG hDwg, double* pLeft, double* pBottom, double* pRight, double* pTop)
	{
	  tfCadGetWinRect pfCadGetWinRect;
	  pfCadGetWinRect = (tfCadGetWinRect)GetProcAddress( ghLibInst, "CadGetWinRect" );
	  if (pfCadGetWinRect){
		(*pfCadGetWinRect)(hDwg, pLeft, pBottom, pRight, pTop);
	  }
	}


	//--------------
	void CADAPI CadPutDrawOnlyCurLayer (VDWG hDwg, BOOL b)
	{
	  tfCadPutDrawOnlyCurLayer pfCadPutDrawOnlyCurLayer;
	  pfCadPutDrawOnlyCurLayer = (tfCadPutDrawOnlyCurLayer)GetProcAddress( ghLibInst, "CadPutDrawOnlyCurLayer" );
	  if (pfCadPutDrawOnlyCurLayer){
		(*pfCadPutDrawOnlyCurLayer)(hDwg, b);
	  }
	}


	//--------------
	BOOL CADAPI CadGetDrawOnlyCurLayer (VDWG hDwg)
	{
	  tfCadGetDrawOnlyCurLayer pfCadGetDrawOnlyCurLayer;
	  pfCadGetDrawOnlyCurLayer = (tfCadGetDrawOnlyCurLayer)GetProcAddress( ghLibInst, "CadGetDrawOnlyCurLayer" );
	  if (pfCadGetDrawOnlyCurLayer){
		return (*pfCadGetDrawOnlyCurLayer)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPutReadOnly (VDWG hDwg, BOOL b)
	{
	  tfCadPutReadOnly pfCadPutReadOnly;
	  pfCadPutReadOnly = (tfCadPutReadOnly)GetProcAddress( ghLibInst, "CadPutReadOnly" );
	  if (pfCadPutReadOnly){
		(*pfCadPutReadOnly)(hDwg, b);
	  }
	}


	//--------------
	BOOL CADAPI CadGetReadOnly (VDWG hDwg)
	{
	  tfCadGetReadOnly pfCadGetReadOnly;
	  pfCadGetReadOnly = (tfCadGetReadOnly)GetProcAddress( ghLibInst, "CadGetReadOnly" );
	  if (pfCadGetReadOnly){
		return (*pfCadGetReadOnly)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPutDirty (VDWG hDwg, BOOL b)
	{
	  tfCadPutDirty pfCadPutDirty;
	  pfCadPutDirty = (tfCadPutDirty)GetProcAddress( ghLibInst, "CadPutDirty" );
	  if (pfCadPutDirty){
		(*pfCadPutDirty)(hDwg, b);
	  }
	}


	//--------------
	BOOL CADAPI CadGetDirty (VDWG hDwg)
	{
	  tfCadGetDirty pfCadGetDirty;
	  pfCadGetDirty = (tfCadGetDirty)GetProcAddress( ghLibInst, "CadGetDirty" );
	  if (pfCadGetDirty){
		return (*pfCadGetDirty)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPutExData (VDWG hDwg, void* pData, int nBytes)
	{
	  tfCadPutExData pfCadPutExData;
	  pfCadPutExData = (tfCadPutExData)GetProcAddress( ghLibInst, "CadPutExData" );
	  if (pfCadPutExData){
		(*pfCadPutExData)(hDwg, pData, nBytes);
	  }
	}


	//--------------
	int CADAPI CadGetExDataSize (VDWG hDwg)
	{
	  tfCadGetExDataSize pfCadGetExDataSize;
	  pfCadGetExDataSize = (tfCadGetExDataSize)GetProcAddress( ghLibInst, "CadGetExDataSize" );
	  if (pfCadGetExDataSize){
		return (*pfCadGetExDataSize)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGetExData (VDWG hDwg, void* pData)
	{
	  tfCadGetExData pfCadGetExData;
	  pfCadGetExData = (tfCadGetExData)GetProcAddress( ghLibInst, "CadGetExData" );
	  if (pfCadGetExData){
		(*pfCadGetExData)(hDwg, pData);
	  }
	}


	//--------------
	VHANDLE CADAPI CadGetExDataPtr (VDWG hDwg)
	{
	  tfCadGetExDataPtr pfCadGetExDataPtr;
	  pfCadGetExDataPtr = (tfCadGetExDataPtr)GetProcAddress( ghLibInst, "CadGetExDataPtr" );
	  if (pfCadGetExDataPtr){
		return (*pfCadGetExDataPtr)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPutDescr (VDWG hDwg, LPCTSTR Str, int nChars)
	{
	  tfCadPutDescr pfCadPutDescr;
	  pfCadPutDescr = (tfCadPutDescr)GetProcAddress( ghLibInst, "CadPutDescr" );
	  if (pfCadPutDescr){
		(*pfCadPutDescr)(hDwg, Str, nChars);
	  }
	}


	//--------------
	int CADAPI CadGetDescrLen (VDWG hDwg)
	{
	  tfCadGetDescrLen pfCadGetDescrLen;
	  pfCadGetDescrLen = (tfCadGetDescrLen)GetProcAddress( ghLibInst, "CadGetDescrLen" );
	  if (pfCadGetDescrLen){
		return (*pfCadGetDescrLen)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGetDescr (VDWG hDwg, TCHAR* pStr)
	{
	  tfCadGetDescr pfCadGetDescr;
	  pfCadGetDescr = (tfCadGetDescr)GetProcAddress( ghLibInst, "CadGetDescr" );
	  if (pfCadGetDescr){
		(*pfCadGetDescr)(hDwg, pStr);
	  }
	}


	//--------------
	void CADAPI CadPutPaintMark (VDWG hDwg, BOOL b)
	{
	  tfCadPutPaintMark pfCadPutPaintMark;
	  pfCadPutPaintMark = (tfCadPutPaintMark)GetProcAddress( ghLibInst, "CadPutPaintMark" );
	  if (pfCadPutPaintMark){
		(*pfCadPutPaintMark)(hDwg, b);
	  }
	}


	//--------------
	void CADAPI CadPutPointMode (VDWG hDwg, int mode)
	{
	  tfCadPutPointMode pfCadPutPointMode;
	  pfCadPutPointMode = (tfCadPutPointMode)GetProcAddress( ghLibInst, "CadPutPointMode" );
	  if (pfCadPutPointMode){
		(*pfCadPutPointMode)(hDwg, mode);
	  }
	}


	//--------------
	int CADAPI CadGetPointMode (VDWG hDwg)
	{
	  tfCadGetPointMode pfCadGetPointMode;
	  pfCadGetPointMode = (tfCadGetPointMode)GetProcAddress( ghLibInst, "CadGetPointMode" );
	  if (pfCadGetPointMode){
		return (*pfCadGetPointMode)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPutPointSize (VDWG hDwg, double size)
	{
	  tfCadPutPointSize pfCadPutPointSize;
	  pfCadPutPointSize = (tfCadPutPointSize)GetProcAddress( ghLibInst, "CadPutPointSize" );
	  if (pfCadPutPointSize){
		(*pfCadPutPointSize)(hDwg, size);
	  }
	}


	//--------------
	double CADAPI CadGetPointSize (VDWG hDwg)
	{
	  tfCadGetPointSize pfCadGetPointSize;
	  pfCadGetPointSize = (tfCadGetPointSize)GetProcAddress( ghLibInst, "CadGetPointSize" );
	  if (pfCadGetPointSize){
		return (*pfCadGetPointSize)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPutDistScale (VDWG hDwg, double Scal)
	{
	  tfCadPutDistScale pfCadPutDistScale;
	  pfCadPutDistScale = (tfCadPutDistScale)GetProcAddress( ghLibInst, "CadPutDistScale" );
	  if (pfCadPutDistScale){
		(*pfCadPutDistScale)(hDwg, Scal);
	  }
	}


	//--------------
	double CADAPI CadGetDistScale (VDWG hDwg)
	{
	  tfCadGetDistScale pfCadGetDistScale;
	  pfCadGetDistScale = (tfCadGetDistScale)GetProcAddress( ghLibInst, "CadGetDistScale" );
	  if (pfCadGetDistScale){
		return (*pfCadGetDistScale)(hDwg);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadGetNumEntities (VDWG hDwg)
	{
	  tfCadGetNumEntities pfCadGetNumEntities;
	  pfCadGetNumEntities = (tfCadGetNumEntities)GetProcAddress( ghLibInst, "CadGetNumEntities" );
	  if (pfCadGetNumEntities){
		return (*pfCadGetNumEntities)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGridPutShow (VDWG hDwg, BOOL bShow)
	{
	  tfCadGridPutShow pfCadGridPutShow;
	  pfCadGridPutShow = (tfCadGridPutShow)GetProcAddress( ghLibInst, "CadGridPutShow" );
	  if (pfCadGridPutShow){
		(*pfCadGridPutShow)(hDwg, bShow);
	  }
	}


	//--------------
	BOOL CADAPI CadGridGetShow (VDWG hDwg)
	{
	  tfCadGridGetShow pfCadGridGetShow;
	  pfCadGridGetShow = (tfCadGridGetShow)GetProcAddress( ghLibInst, "CadGridGetShow" );
	  if (pfCadGridGetShow){
		return (*pfCadGridGetShow)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGridPutSnap (VDWG hDwg, BOOL bSnap)
	{
	  tfCadGridPutSnap pfCadGridPutSnap;
	  pfCadGridPutSnap = (tfCadGridPutSnap)GetProcAddress( ghLibInst, "CadGridPutSnap" );
	  if (pfCadGridPutSnap){
		(*pfCadGridPutSnap)(hDwg, bSnap);
	  }
	}


	//--------------
	BOOL CADAPI CadGridGetSnap (VDWG hDwg)
	{
	  tfCadGridGetSnap pfCadGridGetSnap;
	  pfCadGridGetSnap = (tfCadGridGetSnap)GetProcAddress( ghLibInst, "CadGridGetSnap" );
	  if (pfCadGridGetSnap){
		return (*pfCadGridGetSnap)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGridPutSize (VDWG hDwg, double dx, double dy, double dz)
	{
	  tfCadGridPutSize pfCadGridPutSize;
	  pfCadGridPutSize = (tfCadGridPutSize)GetProcAddress( ghLibInst, "CadGridPutSize" );
	  if (pfCadGridPutSize){
		(*pfCadGridPutSize)(hDwg, dx, dy, dz);
	  }
	}


	//--------------
	void CADAPI CadGridGetSize (VDWG hDwg, double* pdx, double* pdy, double* pdz)
	{
	  tfCadGridGetSize pfCadGridGetSize;
	  pfCadGridGetSize = (tfCadGridGetSize)GetProcAddress( ghLibInst, "CadGridGetSize" );
	  if (pfCadGridGetSize){
		(*pfCadGridGetSize)(hDwg, pdx, pdy, pdz);
	  }
	}


	//--------------
	void CADAPI CadGridPutBoldStep (VDWG hDwg, int cx, int cy, int cz)
	{
	  tfCadGridPutBoldStep pfCadGridPutBoldStep;
	  pfCadGridPutBoldStep = (tfCadGridPutBoldStep)GetProcAddress( ghLibInst, "CadGridPutBoldStep" );
	  if (pfCadGridPutBoldStep){
		(*pfCadGridPutBoldStep)(hDwg, cx, cy, cz);
	  }
	}


	//--------------
	void CADAPI CadGridGetBoldStep (VDWG hDwg, int* pcx, int* pcy, int* pcz)
	{
	  tfCadGridGetBoldStep pfCadGridGetBoldStep;
	  pfCadGridGetBoldStep = (tfCadGridGetBoldStep)GetProcAddress( ghLibInst, "CadGridGetBoldStep" );
	  if (pfCadGridGetBoldStep){
		(*pfCadGridGetBoldStep)(hDwg, pcx, pcy, pcz);
	  }
	}


	//--------------
	void CADAPI CadGridPutColor (VDWG hDwg, BOOL bBold, COLORREF Color)
	{
	  tfCadGridPutColor pfCadGridPutColor;
	  pfCadGridPutColor = (tfCadGridPutColor)GetProcAddress( ghLibInst, "CadGridPutColor" );
	  if (pfCadGridPutColor){
		(*pfCadGridPutColor)(hDwg, bBold, Color);
	  }
	}


	//--------------
	COLORREF CADAPI CadGridGetColor (VDWG hDwg, BOOL bBold)
	{
	  tfCadGridGetColor pfCadGridGetColor;
	  pfCadGridGetColor = (tfCadGridGetColor)GetProcAddress( ghLibInst, "CadGridGetColor" );
	  if (pfCadGridGetColor){
		return (*pfCadGridGetColor)(hDwg, bBold);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGridPutType (VDWG hDwg, BOOL bBold, int Typ)
	{
	  tfCadGridPutType pfCadGridPutType;
	  pfCadGridPutType = (tfCadGridPutType)GetProcAddress( ghLibInst, "CadGridPutType" );
	  if (pfCadGridPutType){
		(*pfCadGridPutType)(hDwg, bBold, Typ);
	  }
	}


	//--------------
	int CADAPI CadGridGetType (VDWG hDwg, BOOL bBold)
	{
	  tfCadGridGetType pfCadGridGetType;
	  pfCadGridGetType = (tfCadGridGetType)GetProcAddress( ghLibInst, "CadGridGetType" );
	  if (pfCadGridGetType){
		return (*pfCadGridGetType)(hDwg, bBold);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGridPutLevel (VDWG hDwg, int Level)
	{
	  tfCadGridPutLevel pfCadGridPutLevel;
	  pfCadGridPutLevel = (tfCadGridPutLevel)GetProcAddress( ghLibInst, "CadGridPutLevel" );
	  if (pfCadGridPutLevel){
		(*pfCadGridPutLevel)(hDwg, Level);
	  }
	}


	//--------------
	int CADAPI CadGridGetLevel (VDWG hDwg)
	{
	  tfCadGridGetLevel pfCadGridGetLevel;
	  pfCadGridGetLevel = (tfCadGridGetLevel)GetProcAddress( ghLibInst, "CadGridGetLevel" );
	  if (pfCadGridGetLevel){
		return (*pfCadGridGetLevel)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPutLwDefault (VDWG hDwg, int Lweight)
	{
	  tfCadPutLwDefault pfCadPutLwDefault;
	  pfCadPutLwDefault = (tfCadPutLwDefault)GetProcAddress( ghLibInst, "CadPutLwDefault" );
	  if (pfCadPutLwDefault){
		(*pfCadPutLwDefault)(hDwg, Lweight);
	  }
	}


	//--------------
	int CADAPI CadGetLwDefault (VDWG hDwg)
	{
	  tfCadGetLwDefault pfCadGetLwDefault;
	  pfCadGetLwDefault = (tfCadGetLwDefault)GetProcAddress( ghLibInst, "CadGetLwDefault" );
	  if (pfCadGetLwDefault){
		return (*pfCadGetLwDefault)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPutLwScale (VDWG hDwg, int Scal)
	{
	  tfCadPutLwScale pfCadPutLwScale;
	  pfCadPutLwScale = (tfCadPutLwScale)GetProcAddress( ghLibInst, "CadPutLwScale" );
	  if (pfCadPutLwScale){
		(*pfCadPutLwScale)(hDwg, Scal);
	  }
	}


	//--------------
	int CADAPI CadGetLwScale (VDWG hDwg)
	{
	  tfCadGetLwScale pfCadGetLwScale;
	  pfCadGetLwScale = (tfCadGetLwScale)GetProcAddress( ghLibInst, "CadGetLwScale" );
	  if (pfCadGetLwScale){
		return (*pfCadGetLwScale)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPutLwDisplay (VDWG hDwg, BOOL bDisplay)
	{
	  tfCadPutLwDisplay pfCadPutLwDisplay;
	  pfCadPutLwDisplay = (tfCadPutLwDisplay)GetProcAddress( ghLibInst, "CadPutLwDisplay" );
	  if (pfCadPutLwDisplay){
		(*pfCadPutLwDisplay)(hDwg, bDisplay);
	  }
	}


	//--------------
	BOOL CADAPI CadGetLwDisplay (VDWG hDwg)
	{
	  tfCadGetLwDisplay pfCadGetLwDisplay;
	  pfCadGetLwDisplay = (tfCadGetLwDisplay)GetProcAddress( ghLibInst, "CadGetLwDisplay" );
	  if (pfCadGetLwDisplay){
		return (*pfCadGetLwDisplay)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetCurLweight (VDWG hDwg, int Lweight)
	{
	  tfCadSetCurLweight pfCadSetCurLweight;
	  pfCadSetCurLweight = (tfCadSetCurLweight)GetProcAddress( ghLibInst, "CadSetCurLweight" );
	  if (pfCadSetCurLweight){
		(*pfCadSetCurLweight)(hDwg, Lweight);
	  }
	}


	//--------------
	int CADAPI CadGetCurLweight (VDWG hDwg)
	{
	  tfCadGetCurLweight pfCadGetCurLweight;
	  pfCadGetCurLweight = (tfCadGetCurLweight)GetProcAddress( ghLibInst, "CadGetCurLweight" );
	  if (pfCadGetCurLweight){
		return (*pfCadGetCurLweight)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetCurColor (VDWG hDwg, int Color)
	{
	  tfCadSetCurColor pfCadSetCurColor;
	  pfCadSetCurColor = (tfCadSetCurColor)GetProcAddress( ghLibInst, "CadSetCurColor" );
	  if (pfCadSetCurColor){
		(*pfCadSetCurColor)(hDwg, Color);
	  }
	}


	//--------------
	int CADAPI CadGetCurColor (VDWG hDwg)
	{
	  tfCadGetCurColor pfCadGetCurColor;
	  pfCadGetCurColor = (tfCadGetCurColor)GetProcAddress( ghLibInst, "CadGetCurColor" );
	  if (pfCadGetCurColor){
		return (*pfCadGetCurColor)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSetSystemCursor (VDWG hDwg, HCURSOR hCurs)
	{
	  tfCadSetSystemCursor pfCadSetSystemCursor;
	  pfCadSetSystemCursor = (tfCadSetSystemCursor)GetProcAddress( ghLibInst, "CadSetSystemCursor" );
	  if (pfCadSetSystemCursor){
		(*pfCadSetSystemCursor)(hDwg, hCurs);
	  }
	}


	//--------------
	void CADAPI CadPolarPutOn (VDWG hDwg, BOOL bOn)
	{
	  tfCadPolarPutOn pfCadPolarPutOn;
	  pfCadPolarPutOn = (tfCadPolarPutOn)GetProcAddress( ghLibInst, "CadPolarPutOn" );
	  if (pfCadPolarPutOn){
		(*pfCadPolarPutOn)(hDwg, bOn);
	  }
	}


	//--------------
	BOOL CADAPI CadPolarGetOn (VDWG hDwg)
	{
	  tfCadPolarGetOn pfCadPolarGetOn;
	  pfCadPolarGetOn = (tfCadPolarGetOn)GetProcAddress( ghLibInst, "CadPolarGetOn" );
	  if (pfCadPolarGetOn){
		return (*pfCadPolarGetOn)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPolarPutInc (VDWG hDwg, int Angle)
	{
	  tfCadPolarPutInc pfCadPolarPutInc;
	  pfCadPolarPutInc = (tfCadPolarPutInc)GetProcAddress( ghLibInst, "CadPolarPutInc" );
	  if (pfCadPolarPutInc){
		(*pfCadPolarPutInc)(hDwg, Angle);
	  }
	}


	//--------------
	int CADAPI CadPolarGetInc (VDWG hDwg)
	{
	  tfCadPolarGetInc pfCadPolarGetInc;
	  pfCadPolarGetInc = (tfCadPolarGetInc)GetProcAddress( ghLibInst, "CadPolarGetInc" );
	  if (pfCadPolarGetInc){
		return (*pfCadPolarGetInc)(hDwg);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPolarAddAngle (VDWG hDwg, double Angle)
	{
	  tfCadPolarAddAngle pfCadPolarAddAngle;
	  pfCadPolarAddAngle = (tfCadPolarAddAngle)GetProcAddress( ghLibInst, "CadPolarAddAngle" );
	  if (pfCadPolarAddAngle){
		return (*pfCadPolarAddAngle)(hDwg, Angle);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPolarDelAngle (VDWG hDwg, int iAngle)
	{
	  tfCadPolarDelAngle pfCadPolarDelAngle;
	  pfCadPolarDelAngle = (tfCadPolarDelAngle)GetProcAddress( ghLibInst, "CadPolarDelAngle" );
	  if (pfCadPolarDelAngle){
		return (*pfCadPolarDelAngle)(hDwg, iAngle);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadPolarGetAngle (VDWG hDwg, int iAngle)
	{
	  tfCadPolarGetAngle pfCadPolarGetAngle;
	  pfCadPolarGetAngle = (tfCadPolarGetAngle)GetProcAddress( ghLibInst, "CadPolarGetAngle" );
	  if (pfCadPolarGetAngle){
		return (*pfCadPolarGetAngle)(hDwg, iAngle);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadPolarGetNumAng (VDWG hDwg)
	{
	  tfCadPolarGetNumAng pfCadPolarGetNumAng;
	  pfCadPolarGetNumAng = (tfCadPolarGetNumAng)GetProcAddress( ghLibInst, "CadPolarGetNumAng" );
	  if (pfCadPolarGetNumAng){
		return (*pfCadPolarGetNumAng)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPolarPutAbs (VDWG hDwg, BOOL bAbs)
	{
	  tfCadPolarPutAbs pfCadPolarPutAbs;
	  pfCadPolarPutAbs = (tfCadPolarPutAbs)GetProcAddress( ghLibInst, "CadPolarPutAbs" );
	  if (pfCadPolarPutAbs){
		(*pfCadPolarPutAbs)(hDwg, bAbs);
	  }
	}


	//--------------
	BOOL CADAPI CadPolarGetAbs (VDWG hDwg)
	{
	  tfCadPolarGetAbs pfCadPolarGetAbs;
	  pfCadPolarGetAbs = (tfCadPolarGetAbs)GetProcAddress( ghLibInst, "CadPolarGetAbs" );
	  if (pfCadPolarGetAbs){
		return (*pfCadPolarGetAbs)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPolarPutDist (VDWG hDwg, double Dist)
	{
	  tfCadPolarPutDist pfCadPolarPutDist;
	  pfCadPolarPutDist = (tfCadPolarPutDist)GetProcAddress( ghLibInst, "CadPolarPutDist" );
	  if (pfCadPolarPutDist){
		(*pfCadPolarPutDist)(hDwg, Dist);
	  }
	}


	//--------------
	double CADAPI CadPolarGetDist (VDWG hDwg)
	{
	  tfCadPolarGetDist pfCadPolarGetDist;
	  pfCadPolarGetDist = (tfCadPolarGetDist)GetProcAddress( ghLibInst, "CadPolarGetDist" );
	  if (pfCadPolarGetDist){
		return (*pfCadPolarGetDist)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPolarPutDistOn (VDWG hDwg, BOOL bDist)
	{
	  tfCadPolarPutDistOn pfCadPolarPutDistOn;
	  pfCadPolarPutDistOn = (tfCadPolarPutDistOn)GetProcAddress( ghLibInst, "CadPolarPutDistOn" );
	  if (pfCadPolarPutDistOn){
		(*pfCadPolarPutDistOn)(hDwg, bDist);
	  }
	}


	//--------------
	BOOL CADAPI CadPolarGetDistOn (VDWG hDwg)
	{
	  tfCadPolarGetDistOn pfCadPolarGetDistOn;
	  pfCadPolarGetDistOn = (tfCadPolarGetDistOn)GetProcAddress( ghLibInst, "CadPolarGetDistOn" );
	  if (pfCadPolarGetDistOn){
		return (*pfCadPolarGetDistOn)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSnapPutOn (VDWG hDwg, BOOL bOn)
	{
	  tfCadSnapPutOn pfCadSnapPutOn;
	  pfCadSnapPutOn = (tfCadSnapPutOn)GetProcAddress( ghLibInst, "CadSnapPutOn" );
	  if (pfCadSnapPutOn){
		(*pfCadSnapPutOn)(hDwg, bOn);
	  }
	}


	//--------------
	BOOL CADAPI CadSnapGetOn (VDWG hDwg)
	{
	  tfCadSnapGetOn pfCadSnapGetOn;
	  pfCadSnapGetOn = (tfCadSnapGetOn)GetProcAddress( ghLibInst, "CadSnapGetOn" );
	  if (pfCadSnapGetOn){
		return (*pfCadSnapGetOn)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSnapPutMode (VDWG hDwg, int Mode)
	{
	  tfCadSnapPutMode pfCadSnapPutMode;
	  pfCadSnapPutMode = (tfCadSnapPutMode)GetProcAddress( ghLibInst, "CadSnapPutMode" );
	  if (pfCadSnapPutMode){
		(*pfCadSnapPutMode)(hDwg, Mode);
	  }
	}


	//--------------
	int CADAPI CadSnapGetMode (VDWG hDwg)
	{
	  tfCadSnapGetMode pfCadSnapGetMode;
	  pfCadSnapGetMode = (tfCadSnapGetMode)GetProcAddress( ghLibInst, "CadSnapGetMode" );
	  if (pfCadSnapGetMode){
		return (*pfCadSnapGetMode)(hDwg);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadSnapGetIndMode (VDWG hDwg)
	{
	  tfCadSnapGetIndMode pfCadSnapGetIndMode;
	  pfCadSnapGetIndMode = (tfCadSnapGetIndMode)GetProcAddress( ghLibInst, "CadSnapGetIndMode" );
	  if (pfCadSnapGetIndMode){
		return (*pfCadSnapGetIndMode)(hDwg);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadSetPlineMark (VDWG hDwg, int Id, VHANDLE hEnt, double Start, double Length, COLORREF Color, int Width, BOOL bBlink)
	{
	  tfCadSetPlineMark pfCadSetPlineMark;
	  pfCadSetPlineMark = (tfCadSetPlineMark)GetProcAddress( ghLibInst, "CadSetPlineMark" );
	  if (pfCadSetPlineMark){
		return (*pfCadSetPlineMark)(hDwg, Id, hEnt, Start, Length, Color, Width, bBlink);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddPlineMark (VDWG hDwg, VHANDLE hEnt, double Start, double Length)
	{
	  tfCadAddPlineMark pfCadAddPlineMark;
	  pfCadAddPlineMark = (tfCadAddPlineMark)GetProcAddress( ghLibInst, "CadAddPlineMark" );
	  if (pfCadAddPlineMark){
		return (*pfCadAddPlineMark)(hDwg, hEnt, Start, Length);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadWinCreate (VDWG hDwg, HWND hWin)
	{
	  tfCadWinCreate pfCadWinCreate;
	  pfCadWinCreate = (tfCadWinCreate)GetProcAddress( ghLibInst, "CadWinCreate" );
	  if (pfCadWinCreate){
		(*pfCadWinCreate)(hDwg, hWin);
	  }
	}


	//--------------
	void CADAPI CadWinPaint (VDWG hDwg, HWND hWin)
	{
	  tfCadWinPaint pfCadWinPaint;
	  pfCadWinPaint = (tfCadWinPaint)GetProcAddress( ghLibInst, "CadWinPaint" );
	  if (pfCadWinPaint){
		(*pfCadWinPaint)(hDwg, hWin);
	  }
	}


	//--------------
	void CADAPI CadWinDraw (VDWG hDwg, HWND hWin, HDC dc, int Left, int Top, int Right, int Bottom)
	{
	  tfCadWinDraw pfCadWinDraw;
	  pfCadWinDraw = (tfCadWinDraw)GetProcAddress( ghLibInst, "CadWinDraw" );
	  if (pfCadWinDraw){
		(*pfCadWinDraw)(hDwg, hWin, dc, Left, Top, Right, Bottom);
	  }
	}


	//--------------
	void CADAPI CadWinKeyDown (VDWG hDwg, HWND hWin, UINT Char, UINT Flags)
	{
	  tfCadWinKeyDown pfCadWinKeyDown;
	  pfCadWinKeyDown = (tfCadWinKeyDown)GetProcAddress( ghLibInst, "CadWinKeyDown" );
	  if (pfCadWinKeyDown){
		(*pfCadWinKeyDown)(hDwg, hWin, Char, Flags);
	  }
	}


	//--------------
	void CADAPI CadWinKeyUp (VDWG hDwg, HWND hWin, UINT Char, UINT Flags)
	{
	  tfCadWinKeyUp pfCadWinKeyUp;
	  pfCadWinKeyUp = (tfCadWinKeyUp)GetProcAddress( ghLibInst, "CadWinKeyUp" );
	  if (pfCadWinKeyUp){
		(*pfCadWinKeyUp)(hDwg, hWin, Char, Flags);
	  }
	}


	//--------------
	void CADAPI CadWinMouseMove (VDWG hDwg, HWND hWin, UINT Flags, int x, int y)
	{
	  tfCadWinMouseMove pfCadWinMouseMove;
	  pfCadWinMouseMove = (tfCadWinMouseMove)GetProcAddress( ghLibInst, "CadWinMouseMove" );
	  if (pfCadWinMouseMove){
		(*pfCadWinMouseMove)(hDwg, hWin, Flags, x, y);
	  }
	}


	//--------------
	void CADAPI CadWinMouseLeave (VDWG hDwg, HWND hWnd)
	{
	  tfCadWinMouseLeave pfCadWinMouseLeave;
	  pfCadWinMouseLeave = (tfCadWinMouseLeave)GetProcAddress( ghLibInst, "CadWinMouseLeave" );
	  if (pfCadWinMouseLeave){
		(*pfCadWinMouseLeave)(hDwg, hWnd);
	  }
	}


	//--------------
	void CADAPI CadWinMouseWheel (VDWG hDwg, HWND hWin, UINT Flags, int zDelta, int x, int y)
	{
	  tfCadWinMouseWheel pfCadWinMouseWheel;
	  pfCadWinMouseWheel = (tfCadWinMouseWheel)GetProcAddress( ghLibInst, "CadWinMouseWheel" );
	  if (pfCadWinMouseWheel){
		(*pfCadWinMouseWheel)(hDwg, hWin, Flags, zDelta, x, y);
	  }
	}


	//--------------
	void CADAPI CadWinLButtonDown (VDWG hDwg, HWND hWin, UINT Flags, int x, int y)
	{
	  tfCadWinLButtonDown pfCadWinLButtonDown;
	  pfCadWinLButtonDown = (tfCadWinLButtonDown)GetProcAddress( ghLibInst, "CadWinLButtonDown" );
	  if (pfCadWinLButtonDown){
		(*pfCadWinLButtonDown)(hDwg, hWin, Flags, x, y);
	  }
	}


	//--------------
	void CADAPI CadWinLButtonUp (VDWG hDwg, HWND hWin, UINT Flags, int x, int y)
	{
	  tfCadWinLButtonUp pfCadWinLButtonUp;
	  pfCadWinLButtonUp = (tfCadWinLButtonUp)GetProcAddress( ghLibInst, "CadWinLButtonUp" );
	  if (pfCadWinLButtonUp){
		(*pfCadWinLButtonUp)(hDwg, hWin, Flags, x, y);
	  }
	}


	//--------------
	void CADAPI CadWinLButtonDblClk (VDWG hDwg, HWND hWin, UINT Flags, int x, int y)
	{
	  tfCadWinLButtonDblClk pfCadWinLButtonDblClk;
	  pfCadWinLButtonDblClk = (tfCadWinLButtonDblClk)GetProcAddress( ghLibInst, "CadWinLButtonDblClk" );
	  if (pfCadWinLButtonDblClk){
		(*pfCadWinLButtonDblClk)(hDwg, hWin, Flags, x, y);
	  }
	}


	//--------------
	void CADAPI CadWinRButtonDown (VDWG hDwg, HWND hWin, UINT Flags, int x, int y)
	{
	  tfCadWinRButtonDown pfCadWinRButtonDown;
	  pfCadWinRButtonDown = (tfCadWinRButtonDown)GetProcAddress( ghLibInst, "CadWinRButtonDown" );
	  if (pfCadWinRButtonDown){
		(*pfCadWinRButtonDown)(hDwg, hWin, Flags, x, y);
	  }
	}


	//--------------
	void CADAPI CadWinRButtonUp (VDWG hDwg, HWND hWin, UINT Flags, int x, int y)
	{
	  tfCadWinRButtonUp pfCadWinRButtonUp;
	  pfCadWinRButtonUp = (tfCadWinRButtonUp)GetProcAddress( ghLibInst, "CadWinRButtonUp" );
	  if (pfCadWinRButtonUp){
		(*pfCadWinRButtonUp)(hDwg, hWin, Flags, x, y);
	  }
	}


	//--------------
	void CADAPI CadWinMButtonDown (VDWG hDwg, HWND hWin, UINT Flags, int x, int y)
	{
	  tfCadWinMButtonDown pfCadWinMButtonDown;
	  pfCadWinMButtonDown = (tfCadWinMButtonDown)GetProcAddress( ghLibInst, "CadWinMButtonDown" );
	  if (pfCadWinMButtonDown){
		(*pfCadWinMButtonDown)(hDwg, hWin, Flags, x, y);
	  }
	}


	//--------------
	void CADAPI CadWinMButtonUp (VDWG hDwg, HWND hWin, UINT Flags, int x, int y)
	{
	  tfCadWinMButtonUp pfCadWinMButtonUp;
	  pfCadWinMButtonUp = (tfCadWinMButtonUp)GetProcAddress( ghLibInst, "CadWinMButtonUp" );
	  if (pfCadWinMButtonUp){
		(*pfCadWinMButtonUp)(hDwg, hWin, Flags, x, y);
	  }
	}


	//--------------
	void CADAPI CadWinHScroll (VDWG hDwg, HWND hWin, UINT SBCode, UINT Pos)
	{
	  tfCadWinHScroll pfCadWinHScroll;
	  pfCadWinHScroll = (tfCadWinHScroll)GetProcAddress( ghLibInst, "CadWinHScroll" );
	  if (pfCadWinHScroll){
		(*pfCadWinHScroll)(hDwg, hWin, SBCode, Pos);
	  }
	}


	//--------------
	void CADAPI CadWinVScroll (VDWG hDwg, HWND hWin, UINT SBCode, UINT Pos)
	{
	  tfCadWinVScroll pfCadWinVScroll;
	  pfCadWinVScroll = (tfCadWinVScroll)GetProcAddress( ghLibInst, "CadWinVScroll" );
	  if (pfCadWinVScroll){
		(*pfCadWinVScroll)(hDwg, hWin, SBCode, Pos);
	  }
	}


	//--------------
	void CADAPI CadWinSize (VDWG hDwg, HWND hWin, UINT SizeType, int cx, int cy)
	{
	  tfCadWinSize pfCadWinSize;
	  pfCadWinSize = (tfCadWinSize)GetProcAddress( ghLibInst, "CadWinSize" );
	  if (pfCadWinSize){
		(*pfCadWinSize)(hDwg, hWin, SizeType, cx, cy);
	  }
	}


	//--------------
	void CADAPI CadWinSetFocus (VDWG hDwg, HWND hWin)
	{
	  tfCadWinSetFocus pfCadWinSetFocus;
	  pfCadWinSetFocus = (tfCadWinSetFocus)GetProcAddress( ghLibInst, "CadWinSetFocus" );
	  if (pfCadWinSetFocus){
		(*pfCadWinSetFocus)(hDwg, hWin);
	  }
	}


	//--------------
	void CADAPI CadWinKillFocus (VDWG hDwg, HWND hWin)
	{
	  tfCadWinKillFocus pfCadWinKillFocus;
	  pfCadWinKillFocus = (tfCadWinKillFocus)GetProcAddress( ghLibInst, "CadWinKillFocus" );
	  if (pfCadWinKillFocus){
		(*pfCadWinKillFocus)(hDwg, hWin);
	  }
	}


	//--------------
	void CADAPI CadWinDestroy (VDWG hDwg, HWND hWin)
	{
	  tfCadWinDestroy pfCadWinDestroy;
	  pfCadWinDestroy = (tfCadWinDestroy)GetProcAddress( ghLibInst, "CadWinDestroy" );
	  if (pfCadWinDestroy){
		(*pfCadWinDestroy)(hDwg, hWin);
	  }
	}


	//--------------
	BOOL CADAPI CadWinClose (VDWG hDwg, HWND hWin)
	{
	  tfCadWinClose pfCadWinClose;
	  pfCadWinClose = (tfCadWinClose)GetProcAddress( ghLibInst, "CadWinClose" );
	  if (pfCadWinClose){
		return (*pfCadWinClose)(hDwg, hWin);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadWinTimer (VDWG hDwg, HWND hWin, int Id)
	{
	  tfCadWinTimer pfCadWinTimer;
	  pfCadWinTimer = (tfCadWinTimer)GetProcAddress( ghLibInst, "CadWinTimer" );
	  if (pfCadWinTimer){
		return (*pfCadWinTimer)(hDwg, hWin, Id);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadExecute (VDWG hDwg, HWND hWin, int Command)
	{
	  tfCadExecute pfCadExecute;
	  pfCadExecute = (tfCadExecute)GetProcAddress( ghLibInst, "CadExecute" );
	  if (pfCadExecute){
		(*pfCadExecute)(hDwg, hWin, Command);
	  }
	}


	//--------------
	void CADAPI CadSetCmdParam (VDWG hDwg, int Command, void* pData)
	{
	  tfCadSetCmdParam pfCadSetCmdParam;
	  pfCadSetCmdParam = (tfCadSetCmdParam)GetProcAddress( ghLibInst, "CadSetCmdParam" );
	  if (pfCadSetCmdParam){
		(*pfCadSetCmdParam)(hDwg, Command, pData);
	  }
	}


	//--------------
	void CADAPI CadGetCmdParam (VDWG hDwg, int Command, void* pData)
	{
	  tfCadGetCmdParam pfCadGetCmdParam;
	  pfCadGetCmdParam = (tfCadGetCmdParam)GetProcAddress( ghLibInst, "CadGetCmdParam" );
	  if (pfCadGetCmdParam){
		(*pfCadGetCmdParam)(hDwg, Command, pData);
	  }
	}


	//--------------
	void CADAPI CadSetCmdPoint (VDWG hDwg, double X, double Y, double Z)
	{
	  tfCadSetCmdPoint pfCadSetCmdPoint;
	  pfCadSetCmdPoint = (tfCadSetCmdPoint)GetProcAddress( ghLibInst, "CadSetCmdPoint" );
	  if (pfCadSetCmdPoint){
		(*pfCadSetCmdPoint)(hDwg, X, Y, Z);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddLayer (VDWG hDwg, LPCTSTR szName, int Color, IDOBJ IdLtype, int Lweight)
	{
	  tfCadAddLayer pfCadAddLayer;
	  pfCadAddLayer = (tfCadAddLayer)GetProcAddress( ghLibInst, "CadAddLayer" );
	  if (pfCadAddLayer){
		return (*pfCadAddLayer)(hDwg, szName, Color, IdLtype, Lweight);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadDeleteLayer (VDWG hDwg, VHANDLE hLayer)
	{
	  tfCadDeleteLayer pfCadDeleteLayer;
	  pfCadDeleteLayer = (tfCadDeleteLayer)GetProcAddress( ghLibInst, "CadDeleteLayer" );
	  if (pfCadDeleteLayer){
		return (*pfCadDeleteLayer)(hDwg, hLayer);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadCountLayers (VDWG hDwg)
	{
	  tfCadCountLayers pfCadCountLayers;
	  pfCadCountLayers = (tfCadCountLayers)GetProcAddress( ghLibInst, "CadCountLayers" );
	  if (pfCadCountLayers){
		return (*pfCadCountLayers)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetCurLayer (VDWG hDwg)
	{
	  tfCadGetCurLayer pfCadGetCurLayer;
	  pfCadGetCurLayer = (tfCadGetCurLayer)GetProcAddress( ghLibInst, "CadGetCurLayer" );
	  if (pfCadGetCurLayer){
		return (*pfCadGetCurLayer)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurLayer (VDWG hDwg, VHANDLE hLayer)
	{
	  tfCadSetCurLayer pfCadSetCurLayer;
	  pfCadSetCurLayer = (tfCadSetCurLayer)GetProcAddress( ghLibInst, "CadSetCurLayer" );
	  if (pfCadSetCurLayer){
		return (*pfCadSetCurLayer)(hDwg, hLayer);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurLayerByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadSetCurLayerByID pfCadSetCurLayerByID;
	  pfCadSetCurLayerByID = (tfCadSetCurLayerByID)GetProcAddress( ghLibInst, "CadSetCurLayerByID" );
	  if (pfCadSetCurLayerByID){
		return (*pfCadSetCurLayerByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurLayerByName (VDWG hDwg, LPCTSTR szLayerName)
	{
	  tfCadSetCurLayerByName pfCadSetCurLayerByName;
	  pfCadSetCurLayerByName = (tfCadSetCurLayerByName)GetProcAddress( ghLibInst, "CadSetCurLayerByName" );
	  if (pfCadSetCurLayerByName){
		return (*pfCadSetCurLayerByName)(hDwg, szLayerName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetFirstLayer (VDWG hDwg)
	{
	  tfCadGetFirstLayer pfCadGetFirstLayer;
	  pfCadGetFirstLayer = (tfCadGetFirstLayer)GetProcAddress( ghLibInst, "CadGetFirstLayer" );
	  if (pfCadGetFirstLayer){
		return (*pfCadGetFirstLayer)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetNextLayer (VDWG hDwg, VHANDLE hLayer)
	{
	  tfCadGetNextLayer pfCadGetNextLayer;
	  pfCadGetNextLayer = (tfCadGetNextLayer)GetProcAddress( ghLibInst, "CadGetNextLayer" );
	  if (pfCadGetNextLayer){
		return (*pfCadGetNextLayer)(hDwg, hLayer);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetLayerByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadGetLayerByID pfCadGetLayerByID;
	  pfCadGetLayerByID = (tfCadGetLayerByID)GetProcAddress( ghLibInst, "CadGetLayerByID" );
	  if (pfCadGetLayerByID){
		return (*pfCadGetLayerByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetLayerByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadGetLayerByName pfCadGetLayerByName;
	  pfCadGetLayerByName = (tfCadGetLayerByName)GetProcAddress( ghLibInst, "CadGetLayerByName" );
	  if (pfCadGetLayerByName){
		return (*pfCadGetLayerByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSortLayers (VDWG hDwg)
	{
	  tfCadSortLayers pfCadSortLayers;
	  pfCadSortLayers = (tfCadSortLayers)GetProcAddress( ghLibInst, "CadSortLayers" );
	  if (pfCadSortLayers){
		(*pfCadSortLayers)(hDwg);
	  }
	}


	//--------------
	IDOBJ CADAPI CadLayerGetID (VHANDLE hLayer)
	{
	  tfCadLayerGetID pfCadLayerGetID;
	  pfCadLayerGetID = (tfCadLayerGetID)GetProcAddress( ghLibInst, "CadLayerGetID" );
	  if (pfCadLayerGetID){
		return (*pfCadLayerGetID)(hLayer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLayerGetName (VHANDLE hLayer, TCHAR* szName)
	{
	  tfCadLayerGetName pfCadLayerGetName;
	  pfCadLayerGetName = (tfCadLayerGetName)GetProcAddress( ghLibInst, "CadLayerGetName" );
	  if (pfCadLayerGetName){
		(*pfCadLayerGetName)(hLayer, szName);
	  }
	}


	//--------------
	void CADAPI CadLayerPutName (VHANDLE hLayer, LPCTSTR szName)
	{
	  tfCadLayerPutName pfCadLayerPutName;
	  pfCadLayerPutName = (tfCadLayerPutName)GetProcAddress( ghLibInst, "CadLayerPutName" );
	  if (pfCadLayerPutName){
		(*pfCadLayerPutName)(hLayer, szName);
	  }
	}


	//--------------
	int CADAPI CadLayerGetColor (VHANDLE hLayer)
	{
	  tfCadLayerGetColor pfCadLayerGetColor;
	  pfCadLayerGetColor = (tfCadLayerGetColor)GetProcAddress( ghLibInst, "CadLayerGetColor" );
	  if (pfCadLayerGetColor){
		return (*pfCadLayerGetColor)(hLayer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLayerPutColor (VHANDLE hLayer, int Color)
	{
	  tfCadLayerPutColor pfCadLayerPutColor;
	  pfCadLayerPutColor = (tfCadLayerPutColor)GetProcAddress( ghLibInst, "CadLayerPutColor" );
	  if (pfCadLayerPutColor){
		(*pfCadLayerPutColor)(hLayer, Color);
	  }
	}


	//--------------
	int CADAPI CadLayerGetLineweight (VHANDLE hLayer)
	{
	  tfCadLayerGetLineweight pfCadLayerGetLineweight;
	  pfCadLayerGetLineweight = (tfCadLayerGetLineweight)GetProcAddress( ghLibInst, "CadLayerGetLineweight" );
	  if (pfCadLayerGetLineweight){
		return (*pfCadLayerGetLineweight)(hLayer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLayerPutLineweight (VHANDLE hLayer, int lw)
	{
	  tfCadLayerPutLineweight pfCadLayerPutLineweight;
	  pfCadLayerPutLineweight = (tfCadLayerPutLineweight)GetProcAddress( ghLibInst, "CadLayerPutLineweight" );
	  if (pfCadLayerPutLineweight){
		(*pfCadLayerPutLineweight)(hLayer, lw);
	  }
	}


	//--------------
	IDOBJ CADAPI CadLayerGetLinetypeID (VHANDLE hLayer)
	{
	  tfCadLayerGetLinetypeID pfCadLayerGetLinetypeID;
	  pfCadLayerGetLinetypeID = (tfCadLayerGetLinetypeID)GetProcAddress( ghLibInst, "CadLayerGetLinetypeID" );
	  if (pfCadLayerGetLinetypeID){
		return (*pfCadLayerGetLinetypeID)(hLayer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLayerPutLinetypeID (VHANDLE hLayer, IDOBJ Id)
	{
	  tfCadLayerPutLinetypeID pfCadLayerPutLinetypeID;
	  pfCadLayerPutLinetypeID = (tfCadLayerPutLinetypeID)GetProcAddress( ghLibInst, "CadLayerPutLinetypeID" );
	  if (pfCadLayerPutLinetypeID){
		(*pfCadLayerPutLinetypeID)(hLayer, Id);
	  }
	}


	//--------------
	int CADAPI CadLayerGetLevel (VHANDLE hLayer)
	{
	  tfCadLayerGetLevel pfCadLayerGetLevel;
	  pfCadLayerGetLevel = (tfCadLayerGetLevel)GetProcAddress( ghLibInst, "CadLayerGetLevel" );
	  if (pfCadLayerGetLevel){
		return (*pfCadLayerGetLevel)(hLayer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLayerPutLevel (VHANDLE hLayer, int Level)
	{
	  tfCadLayerPutLevel pfCadLayerPutLevel;
	  pfCadLayerPutLevel = (tfCadLayerPutLevel)GetProcAddress( ghLibInst, "CadLayerPutLevel" );
	  if (pfCadLayerPutLevel){
		(*pfCadLayerPutLevel)(hLayer, Level);
	  }
	}


	//--------------
	DWORD CADAPI CadLayerGetUserData (VHANDLE hLayer)
	{
	  tfCadLayerGetUserData pfCadLayerGetUserData;
	  pfCadLayerGetUserData = (tfCadLayerGetUserData)GetProcAddress( ghLibInst, "CadLayerGetUserData" );
	  if (pfCadLayerGetUserData){
		return (*pfCadLayerGetUserData)(hLayer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLayerPutUserData (VHANDLE hLayer, DWORD Val)
	{
	  tfCadLayerPutUserData pfCadLayerPutUserData;
	  pfCadLayerPutUserData = (tfCadLayerPutUserData)GetProcAddress( ghLibInst, "CadLayerPutUserData" );
	  if (pfCadLayerPutUserData){
		(*pfCadLayerPutUserData)(hLayer, Val);
	  }
	}


	//--------------
	BOOL CADAPI CadLayerGetLock (VHANDLE hLayer)
	{
	  tfCadLayerGetLock pfCadLayerGetLock;
	  pfCadLayerGetLock = (tfCadLayerGetLock)GetProcAddress( ghLibInst, "CadLayerGetLock" );
	  if (pfCadLayerGetLock){
		return (*pfCadLayerGetLock)(hLayer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLayerPutLock (VHANDLE hLayer, BOOL bLock)
	{
	  tfCadLayerPutLock pfCadLayerPutLock;
	  pfCadLayerPutLock = (tfCadLayerPutLock)GetProcAddress( ghLibInst, "CadLayerPutLock" );
	  if (pfCadLayerPutLock){
		(*pfCadLayerPutLock)(hLayer, bLock);
	  }
	}


	//--------------
	BOOL CADAPI CadLayerGetVisible (VHANDLE hLayer)
	{
	  tfCadLayerGetVisible pfCadLayerGetVisible;
	  pfCadLayerGetVisible = (tfCadLayerGetVisible)GetProcAddress( ghLibInst, "CadLayerGetVisible" );
	  if (pfCadLayerGetVisible){
		return (*pfCadLayerGetVisible)(hLayer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLayerPutVisible (VHANDLE hLayer, BOOL bVisible)
	{
	  tfCadLayerPutVisible pfCadLayerPutVisible;
	  pfCadLayerPutVisible = (tfCadLayerPutVisible)GetProcAddress( ghLibInst, "CadLayerPutVisible" );
	  if (pfCadLayerPutVisible){
		(*pfCadLayerPutVisible)(hLayer, bVisible);
	  }
	}


	//--------------
	BOOL CADAPI CadLayerGetPrintable (VHANDLE hLayer)
	{
	  tfCadLayerGetPrintable pfCadLayerGetPrintable;
	  pfCadLayerGetPrintable = (tfCadLayerGetPrintable)GetProcAddress( ghLibInst, "CadLayerGetPrintable" );
	  if (pfCadLayerGetPrintable){
		return (*pfCadLayerGetPrintable)(hLayer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLayerPutPrintable (VHANDLE hLayer, BOOL bPrintable)
	{
	  tfCadLayerPutPrintable pfCadLayerPutPrintable;
	  pfCadLayerPutPrintable = (tfCadLayerPutPrintable)GetProcAddress( ghLibInst, "CadLayerPutPrintable" );
	  if (pfCadLayerPutPrintable){
		(*pfCadLayerPutPrintable)(hLayer, bPrintable);
	  }
	}


	//--------------
	UINT CADAPI CadLayerCountEntities (VHANDLE hLayer)
	{
	  tfCadLayerCountEntities pfCadLayerCountEntities;
	  pfCadLayerCountEntities = (tfCadLayerCountEntities)GetProcAddress( ghLibInst, "CadLayerCountEntities" );
	  if (pfCadLayerCountEntities){
		return (*pfCadLayerCountEntities)(hLayer);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadLayerGetFirstEntity (VHANDLE hLayer)
	{
	  tfCadLayerGetFirstEntity pfCadLayerGetFirstEntity;
	  pfCadLayerGetFirstEntity = (tfCadLayerGetFirstEntity)GetProcAddress( ghLibInst, "CadLayerGetFirstEntity" );
	  if (pfCadLayerGetFirstEntity){
		return (*pfCadLayerGetFirstEntity)(hLayer);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadLayerGetNextEntity (VHANDLE hLayer, VHANDLE hEnt)
	{
	  tfCadLayerGetNextEntity pfCadLayerGetNextEntity;
	  pfCadLayerGetNextEntity = (tfCadLayerGetNextEntity)GetProcAddress( ghLibInst, "CadLayerGetNextEntity" );
	  if (pfCadLayerGetNextEntity){
		return (*pfCadLayerGetNextEntity)(hLayer, hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLayerPutDescr (VHANDLE hLayer, LPCTSTR Str, int nChars)
	{
	  tfCadLayerPutDescr pfCadLayerPutDescr;
	  pfCadLayerPutDescr = (tfCadLayerPutDescr)GetProcAddress( ghLibInst, "CadLayerPutDescr" );
	  if (pfCadLayerPutDescr){
		(*pfCadLayerPutDescr)(hLayer, Str, nChars);
	  }
	}


	//--------------
	int CADAPI CadLayerGetDescrLen (VHANDLE hLayer)
	{
	  tfCadLayerGetDescrLen pfCadLayerGetDescrLen;
	  pfCadLayerGetDescrLen = (tfCadLayerGetDescrLen)GetProcAddress( ghLibInst, "CadLayerGetDescrLen" );
	  if (pfCadLayerGetDescrLen){
		return (*pfCadLayerGetDescrLen)(hLayer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLayerGetDescr (VHANDLE hLayer, TCHAR* pStr)
	{
	  tfCadLayerGetDescr pfCadLayerGetDescr;
	  pfCadLayerGetDescr = (tfCadLayerGetDescr)GetProcAddress( ghLibInst, "CadLayerGetDescr" );
	  if (pfCadLayerGetDescr){
		(*pfCadLayerGetDescr)(hLayer, pStr);
	  }
	}


	//--------------
	BOOL CADAPI CadLayerGetDeleted (VHANDLE hLayer)
	{
	  tfCadLayerGetDeleted pfCadLayerGetDeleted;
	  pfCadLayerGetDeleted = (tfCadLayerGetDeleted)GetProcAddress( ghLibInst, "CadLayerGetDeleted" );
	  if (pfCadLayerGetDeleted){
		return (*pfCadLayerGetDeleted)(hLayer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLayerPurge (VHANDLE hLayer)
	{
	  tfCadLayerPurge pfCadLayerPurge;
	  pfCadLayerPurge = (tfCadLayerPurge)GetProcAddress( ghLibInst, "CadLayerPurge" );
	  if (pfCadLayerPurge){
		(*pfCadLayerPurge)(hLayer);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddLinetype (VDWG hDwg, LPCTSTR szName, LPCTSTR szFormat, LPCTSTR szPict)
	{
	  tfCadAddLinetype pfCadAddLinetype;
	  pfCadAddLinetype = (tfCadAddLinetype)GetProcAddress( ghLibInst, "CadAddLinetype" );
	  if (pfCadAddLinetype){
		return (*pfCadAddLinetype)(hDwg, szName, szFormat, szPict);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddLinetypeF (VDWG hDwg, LPCTSTR szName, LPCTSTR szFileName)
	{
	  tfCadAddLinetypeF pfCadAddLinetypeF;
	  pfCadAddLinetypeF = (tfCadAddLinetypeF)GetProcAddress( ghLibInst, "CadAddLinetypeF" );
	  if (pfCadAddLinetypeF){
		return (*pfCadAddLinetypeF)(hDwg, szName, szFileName);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadDeleteLinetype (VDWG hDwg, VHANDLE hLtype)
	{
	  tfCadDeleteLinetype pfCadDeleteLinetype;
	  pfCadDeleteLinetype = (tfCadDeleteLinetype)GetProcAddress( ghLibInst, "CadDeleteLinetype" );
	  if (pfCadDeleteLinetype){
		return (*pfCadDeleteLinetype)(hDwg, hLtype);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadCountLinetypes (VDWG hDwg)
	{
	  tfCadCountLinetypes pfCadCountLinetypes;
	  pfCadCountLinetypes = (tfCadCountLinetypes)GetProcAddress( ghLibInst, "CadCountLinetypes" );
	  if (pfCadCountLinetypes){
		return (*pfCadCountLinetypes)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetCurLinetype (VDWG hDwg)
	{
	  tfCadGetCurLinetype pfCadGetCurLinetype;
	  pfCadGetCurLinetype = (tfCadGetCurLinetype)GetProcAddress( ghLibInst, "CadGetCurLinetype" );
	  if (pfCadGetCurLinetype){
		return (*pfCadGetCurLinetype)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurLinetype (VDWG hDwg, VHANDLE hLtype)
	{
	  tfCadSetCurLinetype pfCadSetCurLinetype;
	  pfCadSetCurLinetype = (tfCadSetCurLinetype)GetProcAddress( ghLibInst, "CadSetCurLinetype" );
	  if (pfCadSetCurLinetype){
		return (*pfCadSetCurLinetype)(hDwg, hLtype);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurLinetypeByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadSetCurLinetypeByID pfCadSetCurLinetypeByID;
	  pfCadSetCurLinetypeByID = (tfCadSetCurLinetypeByID)GetProcAddress( ghLibInst, "CadSetCurLinetypeByID" );
	  if (pfCadSetCurLinetypeByID){
		return (*pfCadSetCurLinetypeByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurLinetypeByName (VDWG hDwg, LPCTSTR szLtypeName)
	{
	  tfCadSetCurLinetypeByName pfCadSetCurLinetypeByName;
	  pfCadSetCurLinetypeByName = (tfCadSetCurLinetypeByName)GetProcAddress( ghLibInst, "CadSetCurLinetypeByName" );
	  if (pfCadSetCurLinetypeByName){
		return (*pfCadSetCurLinetypeByName)(hDwg, szLtypeName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetFirstLinetype (VDWG hDwg)
	{
	  tfCadGetFirstLinetype pfCadGetFirstLinetype;
	  pfCadGetFirstLinetype = (tfCadGetFirstLinetype)GetProcAddress( ghLibInst, "CadGetFirstLinetype" );
	  if (pfCadGetFirstLinetype){
		return (*pfCadGetFirstLinetype)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetNextLinetype (VDWG hDwg, VHANDLE hLtype)
	{
	  tfCadGetNextLinetype pfCadGetNextLinetype;
	  pfCadGetNextLinetype = (tfCadGetNextLinetype)GetProcAddress( ghLibInst, "CadGetNextLinetype" );
	  if (pfCadGetNextLinetype){
		return (*pfCadGetNextLinetype)(hDwg, hLtype);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetLinetypeByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadGetLinetypeByID pfCadGetLinetypeByID;
	  pfCadGetLinetypeByID = (tfCadGetLinetypeByID)GetProcAddress( ghLibInst, "CadGetLinetypeByID" );
	  if (pfCadGetLinetypeByID){
		return (*pfCadGetLinetypeByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetLinetypeByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadGetLinetypeByName pfCadGetLinetypeByName;
	  pfCadGetLinetypeByName = (tfCadGetLinetypeByName)GetProcAddress( ghLibInst, "CadGetLinetypeByName" );
	  if (pfCadGetLinetypeByName){
		return (*pfCadGetLinetypeByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetLinetypeByLayer (VDWG hDwg)
	{
	  tfCadGetLinetypeByLayer pfCadGetLinetypeByLayer;
	  pfCadGetLinetypeByLayer = (tfCadGetLinetypeByLayer)GetProcAddress( ghLibInst, "CadGetLinetypeByLayer" );
	  if (pfCadGetLinetypeByLayer){
		return (*pfCadGetLinetypeByLayer)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetLinetypeByBlock (VDWG hDwg)
	{
	  tfCadGetLinetypeByBlock pfCadGetLinetypeByBlock;
	  pfCadGetLinetypeByBlock = (tfCadGetLinetypeByBlock)GetProcAddress( ghLibInst, "CadGetLinetypeByBlock" );
	  if (pfCadGetLinetypeByBlock){
		return (*pfCadGetLinetypeByBlock)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetLinetypeContinuous (VDWG hDwg)
	{
	  tfCadGetLinetypeContinuous pfCadGetLinetypeContinuous;
	  pfCadGetLinetypeContinuous = (tfCadGetLinetypeContinuous)GetProcAddress( ghLibInst, "CadGetLinetypeContinuous" );
	  if (pfCadGetLinetypeContinuous){
		return (*pfCadGetLinetypeContinuous)(hDwg);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadLinetypeGetID (VHANDLE hLtype)
	{
	  tfCadLinetypeGetID pfCadLinetypeGetID;
	  pfCadLinetypeGetID = (tfCadLinetypeGetID)GetProcAddress( ghLibInst, "CadLinetypeGetID" );
	  if (pfCadLinetypeGetID){
		return (*pfCadLinetypeGetID)(hLtype);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLinetypeGetName (VHANDLE hLtype, TCHAR* szName)
	{
	  tfCadLinetypeGetName pfCadLinetypeGetName;
	  pfCadLinetypeGetName = (tfCadLinetypeGetName)GetProcAddress( ghLibInst, "CadLinetypeGetName" );
	  if (pfCadLinetypeGetName){
		(*pfCadLinetypeGetName)(hLtype, szName);
	  }
	}


	//--------------
	void CADAPI CadLinetypePutName (VHANDLE hLtype, LPCTSTR szName)
	{
	  tfCadLinetypePutName pfCadLinetypePutName;
	  pfCadLinetypePutName = (tfCadLinetypePutName)GetProcAddress( ghLibInst, "CadLinetypePutName" );
	  if (pfCadLinetypePutName){
		(*pfCadLinetypePutName)(hLtype, szName);
	  }
	}


	//--------------
	void CADAPI CadLinetypeGetData (VHANDLE hLtype, TCHAR* szData)
	{
	  tfCadLinetypeGetData pfCadLinetypeGetData;
	  pfCadLinetypeGetData = (tfCadLinetypeGetData)GetProcAddress( ghLibInst, "CadLinetypeGetData" );
	  if (pfCadLinetypeGetData){
		(*pfCadLinetypeGetData)(hLtype, szData);
	  }
	}


	//--------------
	void CADAPI CadLinetypePutData (VHANDLE hLtype, LPCTSTR szData)
	{
	  tfCadLinetypePutData pfCadLinetypePutData;
	  pfCadLinetypePutData = (tfCadLinetypePutData)GetProcAddress( ghLibInst, "CadLinetypePutData" );
	  if (pfCadLinetypePutData){
		(*pfCadLinetypePutData)(hLtype, szData);
	  }
	}


	//--------------
	BOOL CADAPI CadLinetypePutDataF (VHANDLE hLtype, LPCTSTR szFileName)
	{
	  tfCadLinetypePutDataF pfCadLinetypePutDataF;
	  pfCadLinetypePutDataF = (tfCadLinetypePutDataF)GetProcAddress( ghLibInst, "CadLinetypePutDataF" );
	  if (pfCadLinetypePutDataF){
		return (*pfCadLinetypePutDataF)(hLtype, szFileName);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLinetypeGetDescr (VHANDLE hLtype, TCHAR* szDescr)
	{
	  tfCadLinetypeGetDescr pfCadLinetypeGetDescr;
	  pfCadLinetypeGetDescr = (tfCadLinetypeGetDescr)GetProcAddress( ghLibInst, "CadLinetypeGetDescr" );
	  if (pfCadLinetypeGetDescr){
		(*pfCadLinetypeGetDescr)(hLtype, szDescr);
	  }
	}


	//--------------
	void CADAPI CadLinetypePutDescr (VHANDLE hLtype, LPCTSTR szDescr)
	{
	  tfCadLinetypePutDescr pfCadLinetypePutDescr;
	  pfCadLinetypePutDescr = (tfCadLinetypePutDescr)GetProcAddress( ghLibInst, "CadLinetypePutDescr" );
	  if (pfCadLinetypePutDescr){
		(*pfCadLinetypePutDescr)(hLtype, szDescr);
	  }
	}


	//--------------
	double CADAPI CadLinetypeGetScale (VHANDLE hLtype)
	{
	  tfCadLinetypeGetScale pfCadLinetypeGetScale;
	  pfCadLinetypeGetScale = (tfCadLinetypeGetScale)GetProcAddress( ghLibInst, "CadLinetypeGetScale" );
	  if (pfCadLinetypeGetScale){
		return (*pfCadLinetypeGetScale)(hLtype);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLinetypePutScale (VHANDLE hLtype, double Scal)
	{
	  tfCadLinetypePutScale pfCadLinetypePutScale;
	  pfCadLinetypePutScale = (tfCadLinetypePutScale)GetProcAddress( ghLibInst, "CadLinetypePutScale" );
	  if (pfCadLinetypePutScale){
		(*pfCadLinetypePutScale)(hLtype, Scal);
	  }
	}


	//--------------
	BOOL CADAPI CadLinetypeIsByLayer (VHANDLE hLtype)
	{
	  tfCadLinetypeIsByLayer pfCadLinetypeIsByLayer;
	  pfCadLinetypeIsByLayer = (tfCadLinetypeIsByLayer)GetProcAddress( ghLibInst, "CadLinetypeIsByLayer" );
	  if (pfCadLinetypeIsByLayer){
		return (*pfCadLinetypeIsByLayer)(hLtype);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadLinetypeIsByBlock (VHANDLE hLtype)
	{
	  tfCadLinetypeIsByBlock pfCadLinetypeIsByBlock;
	  pfCadLinetypeIsByBlock = (tfCadLinetypeIsByBlock)GetProcAddress( ghLibInst, "CadLinetypeIsByBlock" );
	  if (pfCadLinetypeIsByBlock){
		return (*pfCadLinetypeIsByBlock)(hLtype);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadLinetypeIsContinuous (VHANDLE hLtype)
	{
	  tfCadLinetypeIsContinuous pfCadLinetypeIsContinuous;
	  pfCadLinetypeIsContinuous = (tfCadLinetypeIsContinuous)GetProcAddress( ghLibInst, "CadLinetypeIsContinuous" );
	  if (pfCadLinetypeIsContinuous){
		return (*pfCadLinetypeIsContinuous)(hLtype);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddPage (VDWG hDwg, LPCTSTR szName, int Size, int Orient, UINT Width, UINT Height)
	{
	  tfCadAddPage pfCadAddPage;
	  pfCadAddPage = (tfCadAddPage)GetProcAddress( ghLibInst, "CadAddPage" );
	  if (pfCadAddPage){
		return (*pfCadAddPage)(hDwg, szName, Size, Orient, Width, Height);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadDeletePage (VDWG hDwg, VHANDLE hPage)
	{
	  tfCadDeletePage pfCadDeletePage;
	  pfCadDeletePage = (tfCadDeletePage)GetProcAddress( ghLibInst, "CadDeletePage" );
	  if (pfCadDeletePage){
		return (*pfCadDeletePage)(hDwg, hPage);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadCountPages (VDWG hDwg)
	{
	  tfCadCountPages pfCadCountPages;
	  pfCadCountPages = (tfCadCountPages)GetProcAddress( ghLibInst, "CadCountPages" );
	  if (pfCadCountPages){
		return (*pfCadCountPages)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetCurPage (VDWG hDwg)
	{
	  tfCadGetCurPage pfCadGetCurPage;
	  pfCadGetCurPage = (tfCadGetCurPage)GetProcAddress( ghLibInst, "CadGetCurPage" );
	  if (pfCadGetCurPage){
		return (*pfCadGetCurPage)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurPage (VDWG hDwg, VHANDLE hPage)
	{
	  tfCadSetCurPage pfCadSetCurPage;
	  pfCadSetCurPage = (tfCadSetCurPage)GetProcAddress( ghLibInst, "CadSetCurPage" );
	  if (pfCadSetCurPage){
		return (*pfCadSetCurPage)(hDwg, hPage);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurPageByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadSetCurPageByID pfCadSetCurPageByID;
	  pfCadSetCurPageByID = (tfCadSetCurPageByID)GetProcAddress( ghLibInst, "CadSetCurPageByID" );
	  if (pfCadSetCurPageByID){
		return (*pfCadSetCurPageByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurPageByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadSetCurPageByName pfCadSetCurPageByName;
	  pfCadSetCurPageByName = (tfCadSetCurPageByName)GetProcAddress( ghLibInst, "CadSetCurPageByName" );
	  if (pfCadSetCurPageByName){
		return (*pfCadSetCurPageByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetFirstPage (VDWG hDwg)
	{
	  tfCadGetFirstPage pfCadGetFirstPage;
	  pfCadGetFirstPage = (tfCadGetFirstPage)GetProcAddress( ghLibInst, "CadGetFirstPage" );
	  if (pfCadGetFirstPage){
		return (*pfCadGetFirstPage)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetNextPage (VDWG hDwg, VHANDLE hPage)
	{
	  tfCadGetNextPage pfCadGetNextPage;
	  pfCadGetNextPage = (tfCadGetNextPage)GetProcAddress( ghLibInst, "CadGetNextPage" );
	  if (pfCadGetNextPage){
		return (*pfCadGetNextPage)(hDwg, hPage);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetPageByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadGetPageByID pfCadGetPageByID;
	  pfCadGetPageByID = (tfCadGetPageByID)GetProcAddress( ghLibInst, "CadGetPageByID" );
	  if (pfCadGetPageByID){
		return (*pfCadGetPageByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetPageByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadGetPageByName pfCadGetPageByName;
	  pfCadGetPageByName = (tfCadGetPageByName)GetProcAddress( ghLibInst, "CadGetPageByName" );
	  if (pfCadGetPageByName){
		return (*pfCadGetPageByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadPageGetID (VHANDLE hPage)
	{
	  tfCadPageGetID pfCadPageGetID;
	  pfCadPageGetID = (tfCadPageGetID)GetProcAddress( ghLibInst, "CadPageGetID" );
	  if (pfCadPageGetID){
		return (*pfCadPageGetID)(hPage);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPageGetName (VHANDLE hPage, TCHAR* szName)
	{
	  tfCadPageGetName pfCadPageGetName;
	  pfCadPageGetName = (tfCadPageGetName)GetProcAddress( ghLibInst, "CadPageGetName" );
	  if (pfCadPageGetName){
		(*pfCadPageGetName)(hPage, szName);
	  }
	}


	//--------------
	void CADAPI CadPagePutName (VHANDLE hPage, LPCTSTR szName)
	{
	  tfCadPagePutName pfCadPagePutName;
	  pfCadPagePutName = (tfCadPagePutName)GetProcAddress( ghLibInst, "CadPagePutName" );
	  if (pfCadPagePutName){
		(*pfCadPagePutName)(hPage, szName);
	  }
	}


	//--------------
	UINT CADAPI CadPageGetSize (VHANDLE hPage)
	{
	  tfCadPageGetSize pfCadPageGetSize;
	  pfCadPageGetSize = (tfCadPageGetSize)GetProcAddress( ghLibInst, "CadPageGetSize" );
	  if (pfCadPageGetSize){
		return (*pfCadPageGetSize)(hPage);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPagePutSize (VHANDLE hPage, UINT Size)
	{
	  tfCadPagePutSize pfCadPagePutSize;
	  pfCadPagePutSize = (tfCadPagePutSize)GetProcAddress( ghLibInst, "CadPagePutSize" );
	  if (pfCadPagePutSize){
		(*pfCadPagePutSize)(hPage, Size);
	  }
	}


	//--------------
	UINT CADAPI CadPageGetOrient (VHANDLE hPage)
	{
	  tfCadPageGetOrient pfCadPageGetOrient;
	  pfCadPageGetOrient = (tfCadPageGetOrient)GetProcAddress( ghLibInst, "CadPageGetOrient" );
	  if (pfCadPageGetOrient){
		return (*pfCadPageGetOrient)(hPage);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPagePutOrient (VHANDLE hPage, UINT Orient)
	{
	  tfCadPagePutOrient pfCadPagePutOrient;
	  pfCadPagePutOrient = (tfCadPagePutOrient)GetProcAddress( ghLibInst, "CadPagePutOrient" );
	  if (pfCadPagePutOrient){
		(*pfCadPagePutOrient)(hPage, Orient);
	  }
	}


	//--------------
	UINT CADAPI CadPageGetWidth (VHANDLE hPage)
	{
	  tfCadPageGetWidth pfCadPageGetWidth;
	  pfCadPageGetWidth = (tfCadPageGetWidth)GetProcAddress( ghLibInst, "CadPageGetWidth" );
	  if (pfCadPageGetWidth){
		return (*pfCadPageGetWidth)(hPage);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPagePutWidth (VHANDLE hPage, UINT Width)
	{
	  tfCadPagePutWidth pfCadPagePutWidth;
	  pfCadPagePutWidth = (tfCadPagePutWidth)GetProcAddress( ghLibInst, "CadPagePutWidth" );
	  if (pfCadPagePutWidth){
		(*pfCadPagePutWidth)(hPage, Width);
	  }
	}


	//--------------
	UINT CADAPI CadPageGetHeight (VHANDLE hPage)
	{
	  tfCadPageGetHeight pfCadPageGetHeight;
	  pfCadPageGetHeight = (tfCadPageGetHeight)GetProcAddress( ghLibInst, "CadPageGetHeight" );
	  if (pfCadPageGetHeight){
		return (*pfCadPageGetHeight)(hPage);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPagePutHeight (VHANDLE hPage, UINT Height)
	{
	  tfCadPagePutHeight pfCadPagePutHeight;
	  pfCadPagePutHeight = (tfCadPagePutHeight)GetProcAddress( ghLibInst, "CadPagePutHeight" );
	  if (pfCadPagePutHeight){
		(*pfCadPagePutHeight)(hPage, Height);
	  }
	}


	//--------------
	BOOL CADAPI CadPageSave (VDWG hDwg, VHANDLE hPage, LPCTSTR szFileName)
	{
	  tfCadPageSave pfCadPageSave;
	  pfCadPageSave = (tfCadPageSave)GetProcAddress( ghLibInst, "CadPageSave" );
	  if (pfCadPageSave){
		return (*pfCadPageSave)(hDwg, hPage, szFileName);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPageCopy (VDWG hSrcDwg, VHANDLE hSrcPage, VDWG hDestDwg, VHANDLE hDestPage)
	{
	  tfCadPageCopy pfCadPageCopy;
	  pfCadPageCopy = (tfCadPageCopy)GetProcAddress( ghLibInst, "CadPageCopy" );
	  if (pfCadPageCopy){
		return (*pfCadPageCopy)(hSrcDwg, hSrcPage, hDestDwg, hDestPage);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddTStyle (VDWG hDwg, LPCTSTR szName, LPCTSTR szFontName)
	{
	  tfCadAddTStyle pfCadAddTStyle;
	  pfCadAddTStyle = (tfCadAddTStyle)GetProcAddress( ghLibInst, "CadAddTStyle" );
	  if (pfCadAddTStyle){
		return (*pfCadAddTStyle)(hDwg, szName, szFontName);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadDeleteTStyle (VDWG hDwg, VHANDLE hTStyle)
	{
	  tfCadDeleteTStyle pfCadDeleteTStyle;
	  pfCadDeleteTStyle = (tfCadDeleteTStyle)GetProcAddress( ghLibInst, "CadDeleteTStyle" );
	  if (pfCadDeleteTStyle){
		return (*pfCadDeleteTStyle)(hDwg, hTStyle);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadCountTStyles (VDWG hDwg)
	{
	  tfCadCountTStyles pfCadCountTStyles;
	  pfCadCountTStyles = (tfCadCountTStyles)GetProcAddress( ghLibInst, "CadCountTStyles" );
	  if (pfCadCountTStyles){
		return (*pfCadCountTStyles)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetCurTStyle (VDWG hDwg)
	{
	  tfCadGetCurTStyle pfCadGetCurTStyle;
	  pfCadGetCurTStyle = (tfCadGetCurTStyle)GetProcAddress( ghLibInst, "CadGetCurTStyle" );
	  if (pfCadGetCurTStyle){
		return (*pfCadGetCurTStyle)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurTStyle (VDWG hDwg, VHANDLE hTStyle)
	{
	  tfCadSetCurTStyle pfCadSetCurTStyle;
	  pfCadSetCurTStyle = (tfCadSetCurTStyle)GetProcAddress( ghLibInst, "CadSetCurTStyle" );
	  if (pfCadSetCurTStyle){
		return (*pfCadSetCurTStyle)(hDwg, hTStyle);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurTStyleByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadSetCurTStyleByID pfCadSetCurTStyleByID;
	  pfCadSetCurTStyleByID = (tfCadSetCurTStyleByID)GetProcAddress( ghLibInst, "CadSetCurTStyleByID" );
	  if (pfCadSetCurTStyleByID){
		return (*pfCadSetCurTStyleByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurTStyleByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadSetCurTStyleByName pfCadSetCurTStyleByName;
	  pfCadSetCurTStyleByName = (tfCadSetCurTStyleByName)GetProcAddress( ghLibInst, "CadSetCurTStyleByName" );
	  if (pfCadSetCurTStyleByName){
		return (*pfCadSetCurTStyleByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetFirstTStyle (VDWG hDwg)
	{
	  tfCadGetFirstTStyle pfCadGetFirstTStyle;
	  pfCadGetFirstTStyle = (tfCadGetFirstTStyle)GetProcAddress( ghLibInst, "CadGetFirstTStyle" );
	  if (pfCadGetFirstTStyle){
		return (*pfCadGetFirstTStyle)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetNextTStyle (VDWG hDwg, VHANDLE hTStyle)
	{
	  tfCadGetNextTStyle pfCadGetNextTStyle;
	  pfCadGetNextTStyle = (tfCadGetNextTStyle)GetProcAddress( ghLibInst, "CadGetNextTStyle" );
	  if (pfCadGetNextTStyle){
		return (*pfCadGetNextTStyle)(hDwg, hTStyle);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetTStyleByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadGetTStyleByID pfCadGetTStyleByID;
	  pfCadGetTStyleByID = (tfCadGetTStyleByID)GetProcAddress( ghLibInst, "CadGetTStyleByID" );
	  if (pfCadGetTStyleByID){
		return (*pfCadGetTStyleByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetTStyleByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadGetTStyleByName pfCadGetTStyleByName;
	  pfCadGetTStyleByName = (tfCadGetTStyleByName)GetProcAddress( ghLibInst, "CadGetTStyleByName" );
	  if (pfCadGetTStyleByName){
		return (*pfCadGetTStyleByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadTStyleGetID (VHANDLE hTStyle)
	{
	  tfCadTStyleGetID pfCadTStyleGetID;
	  pfCadTStyleGetID = (tfCadTStyleGetID)GetProcAddress( ghLibInst, "CadTStyleGetID" );
	  if (pfCadTStyleGetID){
		return (*pfCadTStyleGetID)(hTStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTStyleGetName (VHANDLE hTStyle, TCHAR* szName)
	{
	  tfCadTStyleGetName pfCadTStyleGetName;
	  pfCadTStyleGetName = (tfCadTStyleGetName)GetProcAddress( ghLibInst, "CadTStyleGetName" );
	  if (pfCadTStyleGetName){
		(*pfCadTStyleGetName)(hTStyle, szName);
	  }
	}


	//--------------
	void CADAPI CadTStylePutName (VHANDLE hTStyle, LPCTSTR szName)
	{
	  tfCadTStylePutName pfCadTStylePutName;
	  pfCadTStylePutName = (tfCadTStylePutName)GetProcAddress( ghLibInst, "CadTStylePutName" );
	  if (pfCadTStylePutName){
		(*pfCadTStylePutName)(hTStyle, szName);
	  }
	}


	//--------------
	double CADAPI CadTStyleGetOblique (VHANDLE hTStyle)
	{
	  tfCadTStyleGetOblique pfCadTStyleGetOblique;
	  pfCadTStyleGetOblique = (tfCadTStyleGetOblique)GetProcAddress( ghLibInst, "CadTStyleGetOblique" );
	  if (pfCadTStyleGetOblique){
		return (*pfCadTStyleGetOblique)(hTStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTStylePutOblique (VHANDLE hTStyle, double Angle)
	{
	  tfCadTStylePutOblique pfCadTStylePutOblique;
	  pfCadTStylePutOblique = (tfCadTStylePutOblique)GetProcAddress( ghLibInst, "CadTStylePutOblique" );
	  if (pfCadTStylePutOblique){
		(*pfCadTStylePutOblique)(hTStyle, Angle);
	  }
	}


	//--------------
	double CADAPI CadTStyleGetWidth (VHANDLE hTStyle)
	{
	  tfCadTStyleGetWidth pfCadTStyleGetWidth;
	  pfCadTStyleGetWidth = (tfCadTStyleGetWidth)GetProcAddress( ghLibInst, "CadTStyleGetWidth" );
	  if (pfCadTStyleGetWidth){
		return (*pfCadTStyleGetWidth)(hTStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTStylePutWidth (VHANDLE hTStyle, double Width)
	{
	  tfCadTStylePutWidth pfCadTStylePutWidth;
	  pfCadTStylePutWidth = (tfCadTStylePutWidth)GetProcAddress( ghLibInst, "CadTStylePutWidth" );
	  if (pfCadTStylePutWidth){
		(*pfCadTStylePutWidth)(hTStyle, Width);
	  }
	}


	//--------------
	double CADAPI CadTStyleGetHeight (VHANDLE hTStyle)
	{
	  tfCadTStyleGetHeight pfCadTStyleGetHeight;
	  pfCadTStyleGetHeight = (tfCadTStyleGetHeight)GetProcAddress( ghLibInst, "CadTStyleGetHeight" );
	  if (pfCadTStyleGetHeight){
		return (*pfCadTStyleGetHeight)(hTStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTStylePutHeight (VHANDLE hTStyle, double Height)
	{
	  tfCadTStylePutHeight pfCadTStylePutHeight;
	  pfCadTStylePutHeight = (tfCadTStylePutHeight)GetProcAddress( ghLibInst, "CadTStylePutHeight" );
	  if (pfCadTStylePutHeight){
		(*pfCadTStylePutHeight)(hTStyle, Height);
	  }
	}


	//--------------
	BOOL CADAPI CadTStyleGetUpsideDown (VHANDLE hTStyle)
	{
	  tfCadTStyleGetUpsideDown pfCadTStyleGetUpsideDown;
	  pfCadTStyleGetUpsideDown = (tfCadTStyleGetUpsideDown)GetProcAddress( ghLibInst, "CadTStyleGetUpsideDown" );
	  if (pfCadTStyleGetUpsideDown){
		return (*pfCadTStyleGetUpsideDown)(hTStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTStylePutUpsideDown (VHANDLE hTStyle, BOOL bUpsideDown)
	{
	  tfCadTStylePutUpsideDown pfCadTStylePutUpsideDown;
	  pfCadTStylePutUpsideDown = (tfCadTStylePutUpsideDown)GetProcAddress( ghLibInst, "CadTStylePutUpsideDown" );
	  if (pfCadTStylePutUpsideDown){
		(*pfCadTStylePutUpsideDown)(hTStyle, bUpsideDown);
	  }
	}


	//--------------
	BOOL CADAPI CadTStyleGetBackward (VHANDLE hTStyle)
	{
	  tfCadTStyleGetBackward pfCadTStyleGetBackward;
	  pfCadTStyleGetBackward = (tfCadTStyleGetBackward)GetProcAddress( ghLibInst, "CadTStyleGetBackward" );
	  if (pfCadTStyleGetBackward){
		return (*pfCadTStyleGetBackward)(hTStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTStylePutBackward (VHANDLE hTStyle, BOOL bBackward)
	{
	  tfCadTStylePutBackward pfCadTStylePutBackward;
	  pfCadTStylePutBackward = (tfCadTStylePutBackward)GetProcAddress( ghLibInst, "CadTStylePutBackward" );
	  if (pfCadTStylePutBackward){
		(*pfCadTStylePutBackward)(hTStyle, bBackward);
	  }
	}


	//--------------
	void CADAPI CadTStyleGetFont (VHANDLE hTStyle, TCHAR* szFontName)
	{
	  tfCadTStyleGetFont pfCadTStyleGetFont;
	  pfCadTStyleGetFont = (tfCadTStyleGetFont)GetProcAddress( ghLibInst, "CadTStyleGetFont" );
	  if (pfCadTStyleGetFont){
		(*pfCadTStyleGetFont)(hTStyle, szFontName);
	  }
	}


	//--------------
	void CADAPI CadTStylePutFont (VHANDLE hTStyle, LPCTSTR szFontName)
	{
	  tfCadTStylePutFont pfCadTStylePutFont;
	  pfCadTStylePutFont = (tfCadTStylePutFont)GetProcAddress( ghLibInst, "CadTStylePutFont" );
	  if (pfCadTStylePutFont){
		(*pfCadTStylePutFont)(hTStyle, szFontName);
	  }
	}


	//--------------
	void CADAPI CadTStyleGetTTFName (VHANDLE hTStyle, TCHAR* szTTFName)
	{
	  tfCadTStyleGetTTFName pfCadTStyleGetTTFName;
	  pfCadTStyleGetTTFName = (tfCadTStyleGetTTFName)GetProcAddress( ghLibInst, "CadTStyleGetTTFName" );
	  if (pfCadTStyleGetTTFName){
		(*pfCadTStyleGetTTFName)(hTStyle, szTTFName);
	  }
	}


	//--------------
	void CADAPI CadTStylePutTTFName (VHANDLE hTStyle, LPCTSTR szTTFName)
	{
	  tfCadTStylePutTTFName pfCadTStylePutTTFName;
	  pfCadTStylePutTTFName = (tfCadTStylePutTTFName)GetProcAddress( ghLibInst, "CadTStylePutTTFName" );
	  if (pfCadTStylePutTTFName){
		(*pfCadTStylePutTTFName)(hTStyle, szTTFName);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddBlock (VDWG hDwg, LPCTSTR szName, double X, double Y, double Z)
	{
	  tfCadAddBlock pfCadAddBlock;
	  pfCadAddBlock = (tfCadAddBlock)GetProcAddress( ghLibInst, "CadAddBlock" );
	  if (pfCadAddBlock){
		return (*pfCadAddBlock)(hDwg, szName, X, Y, Z);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddBlockFromFile (VDWG hDwg, LPCTSTR szFileName, LPCTSTR szName)
	{
	  tfCadAddBlockFromFile pfCadAddBlockFromFile;
	  pfCadAddBlockFromFile = (tfCadAddBlockFromFile)GetProcAddress( ghLibInst, "CadAddBlockFromFile" );
	  if (pfCadAddBlockFromFile){
		return (*pfCadAddBlockFromFile)(hDwg, szFileName, szName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddBlockFromDrw (VDWG hDwgDest, VDWG hDwgSrc, LPCTSTR szName)
	{
	  tfCadAddBlockFromDrw pfCadAddBlockFromDrw;
	  pfCadAddBlockFromDrw = (tfCadAddBlockFromDrw)GetProcAddress( ghLibInst, "CadAddBlockFromDrw" );
	  if (pfCadAddBlockFromDrw){
		return (*pfCadAddBlockFromDrw)(hDwgDest, hDwgSrc, szName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddBlockFile (VDWG hDwg, LPCTSTR szFileName)
	{
	  tfCadAddBlockFile pfCadAddBlockFile;
	  pfCadAddBlockFile = (tfCadAddBlockFile)GetProcAddress( ghLibInst, "CadAddBlockFile" );
	  if (pfCadAddBlockFile){
		return (*pfCadAddBlockFile)(hDwg, szFileName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddBlockXref (VDWG hDwg, LPCTSTR szFileName)
	{
	  tfCadAddBlockXref pfCadAddBlockXref;
	  pfCadAddBlockXref = (tfCadAddBlockXref)GetProcAddress( ghLibInst, "CadAddBlockXref" );
	  if (pfCadAddBlockXref){
		return (*pfCadAddBlockXref)(hDwg, szFileName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddBlockClip (VDWG hDwg, LPCTSTR szName, double Lef, double Bot, double W, double H)
	{
	  tfCadAddBlockClip pfCadAddBlockClip;
	  pfCadAddBlockClip = (tfCadAddBlockClip)GetProcAddress( ghLibInst, "CadAddBlockClip" );
	  if (pfCadAddBlockClip){
		return (*pfCadAddBlockClip)(hDwg, szName, Lef, Bot, W, H);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadDeleteBlock (VDWG hDwg, VHANDLE hBlock)
	{
	  tfCadDeleteBlock pfCadDeleteBlock;
	  pfCadDeleteBlock = (tfCadDeleteBlock)GetProcAddress( ghLibInst, "CadDeleteBlock" );
	  if (pfCadDeleteBlock){
		return (*pfCadDeleteBlock)(hDwg, hBlock);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadCountBlocks (VDWG hDwg)
	{
	  tfCadCountBlocks pfCadCountBlocks;
	  pfCadCountBlocks = (tfCadCountBlocks)GetProcAddress( ghLibInst, "CadCountBlocks" );
	  if (pfCadCountBlocks){
		return (*pfCadCountBlocks)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetFirstBlock (VDWG hDwg)
	{
	  tfCadGetFirstBlock pfCadGetFirstBlock;
	  pfCadGetFirstBlock = (tfCadGetFirstBlock)GetProcAddress( ghLibInst, "CadGetFirstBlock" );
	  if (pfCadGetFirstBlock){
		return (*pfCadGetFirstBlock)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetNextBlock (VDWG hDwg, VHANDLE hBlock)
	{
	  tfCadGetNextBlock pfCadGetNextBlock;
	  pfCadGetNextBlock = (tfCadGetNextBlock)GetProcAddress( ghLibInst, "CadGetNextBlock" );
	  if (pfCadGetNextBlock){
		return (*pfCadGetNextBlock)(hDwg, hBlock);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetBlockByID (VDWG hDwg, IDOBJ idBlock)
	{
	  tfCadGetBlockByID pfCadGetBlockByID;
	  pfCadGetBlockByID = (tfCadGetBlockByID)GetProcAddress( ghLibInst, "CadGetBlockByID" );
	  if (pfCadGetBlockByID){
		return (*pfCadGetBlockByID)(hDwg, idBlock);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetBlockByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadGetBlockByName pfCadGetBlockByName;
	  pfCadGetBlockByName = (tfCadGetBlockByName)GetProcAddress( ghLibInst, "CadGetBlockByName" );
	  if (pfCadGetBlockByName){
		return (*pfCadGetBlockByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetCurBlock (VDWG hDwg)
	{
	  tfCadGetCurBlock pfCadGetCurBlock;
	  pfCadGetCurBlock = (tfCadGetCurBlock)GetProcAddress( ghLibInst, "CadGetCurBlock" );
	  if (pfCadGetCurBlock){
		return (*pfCadGetCurBlock)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurBlock (VDWG hDwg, VHANDLE hBlock)
	{
	  tfCadSetCurBlock pfCadSetCurBlock;
	  pfCadSetCurBlock = (tfCadSetCurBlock)GetProcAddress( ghLibInst, "CadSetCurBlock" );
	  if (pfCadSetCurBlock){
		return (*pfCadSetCurBlock)(hDwg, hBlock);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadBlockGetID (VHANDLE hBlock)
	{
	  tfCadBlockGetID pfCadBlockGetID;
	  pfCadBlockGetID = (tfCadBlockGetID)GetProcAddress( ghLibInst, "CadBlockGetID" );
	  if (pfCadBlockGetID){
		return (*pfCadBlockGetID)(hBlock);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadBlockGetName (VHANDLE hBlock, TCHAR* szName)
	{
	  tfCadBlockGetName pfCadBlockGetName;
	  pfCadBlockGetName = (tfCadBlockGetName)GetProcAddress( ghLibInst, "CadBlockGetName" );
	  if (pfCadBlockGetName){
		(*pfCadBlockGetName)(hBlock, szName);
	  }
	}


	//--------------
	BOOL CADAPI CadBlockPutName (VHANDLE hBlock, LPCTSTR szName)
	{
	  tfCadBlockPutName pfCadBlockPutName;
	  pfCadBlockPutName = (tfCadBlockPutName)GetProcAddress( ghLibInst, "CadBlockPutName" );
	  if (pfCadBlockPutName){
		return (*pfCadBlockPutName)(hBlock, szName);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadBlockGetBaseX (VHANDLE hBlock)
	{
	  tfCadBlockGetBaseX pfCadBlockGetBaseX;
	  pfCadBlockGetBaseX = (tfCadBlockGetBaseX)GetProcAddress( ghLibInst, "CadBlockGetBaseX" );
	  if (pfCadBlockGetBaseX){
		return (*pfCadBlockGetBaseX)(hBlock);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadBlockPutBaseX (VHANDLE hBlock, double X)
	{
	  tfCadBlockPutBaseX pfCadBlockPutBaseX;
	  pfCadBlockPutBaseX = (tfCadBlockPutBaseX)GetProcAddress( ghLibInst, "CadBlockPutBaseX" );
	  if (pfCadBlockPutBaseX){
		(*pfCadBlockPutBaseX)(hBlock, X);
	  }
	}


	//--------------
	double CADAPI CadBlockGetBaseY (VHANDLE hBlock)
	{
	  tfCadBlockGetBaseY pfCadBlockGetBaseY;
	  pfCadBlockGetBaseY = (tfCadBlockGetBaseY)GetProcAddress( ghLibInst, "CadBlockGetBaseY" );
	  if (pfCadBlockGetBaseY){
		return (*pfCadBlockGetBaseY)(hBlock);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadBlockPutBaseY (VHANDLE hBlock, double Y)
	{
	  tfCadBlockPutBaseY pfCadBlockPutBaseY;
	  pfCadBlockPutBaseY = (tfCadBlockPutBaseY)GetProcAddress( ghLibInst, "CadBlockPutBaseY" );
	  if (pfCadBlockPutBaseY){
		(*pfCadBlockPutBaseY)(hBlock, Y);
	  }
	}


	//--------------
	double CADAPI CadBlockGetBaseZ (VHANDLE hBlock)
	{
	  tfCadBlockGetBaseZ pfCadBlockGetBaseZ;
	  pfCadBlockGetBaseZ = (tfCadBlockGetBaseZ)GetProcAddress( ghLibInst, "CadBlockGetBaseZ" );
	  if (pfCadBlockGetBaseZ){
		return (*pfCadBlockGetBaseZ)(hBlock);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadBlockPutBaseZ (VHANDLE hBlock, double Z)
	{
	  tfCadBlockPutBaseZ pfCadBlockPutBaseZ;
	  pfCadBlockPutBaseZ = (tfCadBlockPutBaseZ)GetProcAddress( ghLibInst, "CadBlockPutBaseZ" );
	  if (pfCadBlockPutBaseZ){
		(*pfCadBlockPutBaseZ)(hBlock, Z);
	  }
	}


	//--------------
	void CADAPI CadBlockGetBase (VHANDLE hBlock, double* pX, double* pY, double* pZ)
	{
	  tfCadBlockGetBase pfCadBlockGetBase;
	  pfCadBlockGetBase = (tfCadBlockGetBase)GetProcAddress( ghLibInst, "CadBlockGetBase" );
	  if (pfCadBlockGetBase){
		(*pfCadBlockGetBase)(hBlock, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadBlockPutBase (VHANDLE hBlock, double X, double Y, double Z)
	{
	  tfCadBlockPutBase pfCadBlockPutBase;
	  pfCadBlockPutBase = (tfCadBlockPutBase)GetProcAddress( ghLibInst, "CadBlockPutBase" );
	  if (pfCadBlockPutBase){
		(*pfCadBlockPutBase)(hBlock, X, Y, Z);
	  }
	}


	//--------------
	UINT CADAPI CadBlockCountEntities (VHANDLE hBlock)
	{
	  tfCadBlockCountEntities pfCadBlockCountEntities;
	  pfCadBlockCountEntities = (tfCadBlockCountEntities)GetProcAddress( ghLibInst, "CadBlockCountEntities" );
	  if (pfCadBlockCountEntities){
		return (*pfCadBlockCountEntities)(hBlock);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadBlockClear (VHANDLE hBlock)
	{
	  tfCadBlockClear pfCadBlockClear;
	  pfCadBlockClear = (tfCadBlockClear)GetProcAddress( ghLibInst, "CadBlockClear" );
	  if (pfCadBlockClear){
		(*pfCadBlockClear)(hBlock);
	  }
	}


	//--------------
	void CADAPI CadBlockAddEntity (VHANDLE hBlock, VHANDLE hEnt)
	{
	  tfCadBlockAddEntity pfCadBlockAddEntity;
	  pfCadBlockAddEntity = (tfCadBlockAddEntity)GetProcAddress( ghLibInst, "CadBlockAddEntity" );
	  if (pfCadBlockAddEntity){
		(*pfCadBlockAddEntity)(hBlock, hEnt);
	  }
	}


	//--------------
	VHANDLE CADAPI CadBlockGetFirstPtr (VHANDLE hBlock)
	{
	  tfCadBlockGetFirstPtr pfCadBlockGetFirstPtr;
	  pfCadBlockGetFirstPtr = (tfCadBlockGetFirstPtr)GetProcAddress( ghLibInst, "CadBlockGetFirstPtr" );
	  if (pfCadBlockGetFirstPtr){
		return (*pfCadBlockGetFirstPtr)(hBlock);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadBlockGetNextPtr (VHANDLE hBlock, VHANDLE hPtr)
	{
	  tfCadBlockGetNextPtr pfCadBlockGetNextPtr;
	  pfCadBlockGetNextPtr = (tfCadBlockGetNextPtr)GetProcAddress( ghLibInst, "CadBlockGetNextPtr" );
	  if (pfCadBlockGetNextPtr){
		return (*pfCadBlockGetNextPtr)(hBlock, hPtr);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadBlockHasAttribs (VHANDLE hBlock)
	{
	  tfCadBlockHasAttribs pfCadBlockHasAttribs;
	  pfCadBlockHasAttribs = (tfCadBlockHasAttribs)GetProcAddress( ghLibInst, "CadBlockHasAttribs" );
	  if (pfCadBlockHasAttribs){
		return (*pfCadBlockHasAttribs)(hBlock);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadBlockGetAttrib (VHANDLE hBlock, LPCTSTR szTag)
	{
	  tfCadBlockGetAttrib pfCadBlockGetAttrib;
	  pfCadBlockGetAttrib = (tfCadBlockGetAttrib)GetProcAddress( ghLibInst, "CadBlockGetAttrib" );
	  if (pfCadBlockGetAttrib){
		return (*pfCadBlockGetAttrib)(hBlock, szTag);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadBlockIsXref (VHANDLE hBlock)
	{
	  tfCadBlockIsXref pfCadBlockIsXref;
	  pfCadBlockIsXref = (tfCadBlockIsXref)GetProcAddress( ghLibInst, "CadBlockIsXref" );
	  if (pfCadBlockIsXref){
		return (*pfCadBlockIsXref)(hBlock);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadXrefGetPath (VHANDLE hBlock, TCHAR* szPathName)
	{
	  tfCadXrefGetPath pfCadXrefGetPath;
	  pfCadXrefGetPath = (tfCadXrefGetPath)GetProcAddress( ghLibInst, "CadXrefGetPath" );
	  if (pfCadXrefGetPath){
		(*pfCadXrefGetPath)(hBlock, szPathName);
	  }
	}


	//--------------
	BOOL CADAPI CadXrefPutPath (VHANDLE hBlock, LPCTSTR szPathName)
	{
	  tfCadXrefPutPath pfCadXrefPutPath;
	  pfCadXrefPutPath = (tfCadXrefPutPath)GetProcAddress( ghLibInst, "CadXrefPutPath" );
	  if (pfCadXrefPutPath){
		return (*pfCadXrefPutPath)(hBlock, szPathName);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadXrefReload (VHANDLE hBlock)
	{
	  tfCadXrefReload pfCadXrefReload;
	  pfCadXrefReload = (tfCadXrefReload)GetProcAddress( ghLibInst, "CadXrefReload" );
	  if (pfCadXrefReload){
		return (*pfCadXrefReload)(hBlock);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadXrefGetStatus (VHANDLE hBlock)
	{
	  tfCadXrefGetStatus pfCadXrefGetStatus;
	  pfCadXrefGetStatus = (tfCadXrefGetStatus)GetProcAddress( ghLibInst, "CadXrefGetStatus" );
	  if (pfCadXrefGetStatus){
		return (*pfCadXrefGetStatus)(hBlock);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadBlockPutExData (VHANDLE hBlock, void* pData, int nBytes)
	{
	  tfCadBlockPutExData pfCadBlockPutExData;
	  pfCadBlockPutExData = (tfCadBlockPutExData)GetProcAddress( ghLibInst, "CadBlockPutExData" );
	  if (pfCadBlockPutExData){
		(*pfCadBlockPutExData)(hBlock, pData, nBytes);
	  }
	}


	//--------------
	int CADAPI CadBlockGetExDataSize (VHANDLE hBlock)
	{
	  tfCadBlockGetExDataSize pfCadBlockGetExDataSize;
	  pfCadBlockGetExDataSize = (tfCadBlockGetExDataSize)GetProcAddress( ghLibInst, "CadBlockGetExDataSize" );
	  if (pfCadBlockGetExDataSize){
		return (*pfCadBlockGetExDataSize)(hBlock);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadBlockGetExData (VHANDLE hBlock, void* pData)
	{
	  tfCadBlockGetExData pfCadBlockGetExData;
	  pfCadBlockGetExData = (tfCadBlockGetExData)GetProcAddress( ghLibInst, "CadBlockGetExData" );
	  if (pfCadBlockGetExData){
		(*pfCadBlockGetExData)(hBlock, pData);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddPntStyle (VDWG hDwg, LPCTSTR szName, IDOBJ BlockId, double BlockScale, LPCTSTR szFontName, double TxtH, double TxtW)
	{
	  tfCadAddPntStyle pfCadAddPntStyle;
	  pfCadAddPntStyle = (tfCadAddPntStyle)GetProcAddress( ghLibInst, "CadAddPntStyle" );
	  if (pfCadAddPntStyle){
		return (*pfCadAddPntStyle)(hDwg, szName, BlockId, BlockScale, szFontName, TxtH, TxtW);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadDeletePntStyle (VDWG hDwg, VHANDLE hPntStyle)
	{
	  tfCadDeletePntStyle pfCadDeletePntStyle;
	  pfCadDeletePntStyle = (tfCadDeletePntStyle)GetProcAddress( ghLibInst, "CadDeletePntStyle" );
	  if (pfCadDeletePntStyle){
		return (*pfCadDeletePntStyle)(hDwg, hPntStyle);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadCountPntStyles (VDWG hDwg)
	{
	  tfCadCountPntStyles pfCadCountPntStyles;
	  pfCadCountPntStyles = (tfCadCountPntStyles)GetProcAddress( ghLibInst, "CadCountPntStyles" );
	  if (pfCadCountPntStyles){
		return (*pfCadCountPntStyles)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetCurPntStyle (VDWG hDwg)
	{
	  tfCadGetCurPntStyle pfCadGetCurPntStyle;
	  pfCadGetCurPntStyle = (tfCadGetCurPntStyle)GetProcAddress( ghLibInst, "CadGetCurPntStyle" );
	  if (pfCadGetCurPntStyle){
		return (*pfCadGetCurPntStyle)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurPntStyle (VDWG hDwg, VHANDLE hPntStyle)
	{
	  tfCadSetCurPntStyle pfCadSetCurPntStyle;
	  pfCadSetCurPntStyle = (tfCadSetCurPntStyle)GetProcAddress( ghLibInst, "CadSetCurPntStyle" );
	  if (pfCadSetCurPntStyle){
		return (*pfCadSetCurPntStyle)(hDwg, hPntStyle);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurPntStyleByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadSetCurPntStyleByID pfCadSetCurPntStyleByID;
	  pfCadSetCurPntStyleByID = (tfCadSetCurPntStyleByID)GetProcAddress( ghLibInst, "CadSetCurPntStyleByID" );
	  if (pfCadSetCurPntStyleByID){
		return (*pfCadSetCurPntStyleByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurPntStyleByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadSetCurPntStyleByName pfCadSetCurPntStyleByName;
	  pfCadSetCurPntStyleByName = (tfCadSetCurPntStyleByName)GetProcAddress( ghLibInst, "CadSetCurPntStyleByName" );
	  if (pfCadSetCurPntStyleByName){
		return (*pfCadSetCurPntStyleByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetFirstPntStyle (VDWG hDwg)
	{
	  tfCadGetFirstPntStyle pfCadGetFirstPntStyle;
	  pfCadGetFirstPntStyle = (tfCadGetFirstPntStyle)GetProcAddress( ghLibInst, "CadGetFirstPntStyle" );
	  if (pfCadGetFirstPntStyle){
		return (*pfCadGetFirstPntStyle)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetNextPntStyle (VDWG hDwg, VHANDLE hPntStyle)
	{
	  tfCadGetNextPntStyle pfCadGetNextPntStyle;
	  pfCadGetNextPntStyle = (tfCadGetNextPntStyle)GetProcAddress( ghLibInst, "CadGetNextPntStyle" );
	  if (pfCadGetNextPntStyle){
		return (*pfCadGetNextPntStyle)(hDwg, hPntStyle);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetPntStyleByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadGetPntStyleByID pfCadGetPntStyleByID;
	  pfCadGetPntStyleByID = (tfCadGetPntStyleByID)GetProcAddress( ghLibInst, "CadGetPntStyleByID" );
	  if (pfCadGetPntStyleByID){
		return (*pfCadGetPntStyleByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetPntStyleByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadGetPntStyleByName pfCadGetPntStyleByName;
	  pfCadGetPntStyleByName = (tfCadGetPntStyleByName)GetProcAddress( ghLibInst, "CadGetPntStyleByName" );
	  if (pfCadGetPntStyleByName){
		return (*pfCadGetPntStyleByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadPntStyleGetID (VHANDLE hPntStyle)
	{
	  tfCadPntStyleGetID pfCadPntStyleGetID;
	  pfCadPntStyleGetID = (tfCadPntStyleGetID)GetProcAddress( ghLibInst, "CadPntStyleGetID" );
	  if (pfCadPntStyleGetID){
		return (*pfCadPntStyleGetID)(hPntStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPntStyleGetName (VHANDLE hPntStyle, TCHAR* szName)
	{
	  tfCadPntStyleGetName pfCadPntStyleGetName;
	  pfCadPntStyleGetName = (tfCadPntStyleGetName)GetProcAddress( ghLibInst, "CadPntStyleGetName" );
	  if (pfCadPntStyleGetName){
		(*pfCadPntStyleGetName)(hPntStyle, szName);
	  }
	}


	//--------------
	void CADAPI CadPntStylePutName (VHANDLE hPntStyle, LPCTSTR szName)
	{
	  tfCadPntStylePutName pfCadPntStylePutName;
	  pfCadPntStylePutName = (tfCadPntStylePutName)GetProcAddress( ghLibInst, "CadPntStylePutName" );
	  if (pfCadPntStylePutName){
		(*pfCadPntStylePutName)(hPntStyle, szName);
	  }
	}


	//--------------
	IDOBJ CADAPI CadPntStyleGetBlockID (VHANDLE hPntStyle)
	{
	  tfCadPntStyleGetBlockID pfCadPntStyleGetBlockID;
	  pfCadPntStyleGetBlockID = (tfCadPntStyleGetBlockID)GetProcAddress( ghLibInst, "CadPntStyleGetBlockID" );
	  if (pfCadPntStyleGetBlockID){
		return (*pfCadPntStyleGetBlockID)(hPntStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPntStylePutBlockID (VHANDLE hPntStyle, IDOBJ IdBlock)
	{
	  tfCadPntStylePutBlockID pfCadPntStylePutBlockID;
	  pfCadPntStylePutBlockID = (tfCadPntStylePutBlockID)GetProcAddress( ghLibInst, "CadPntStylePutBlockID" );
	  if (pfCadPntStylePutBlockID){
		(*pfCadPntStylePutBlockID)(hPntStyle, IdBlock);
	  }
	}


	//--------------
	double CADAPI CadPntStyleGetBlockScale (VHANDLE hPntStyle)
	{
	  tfCadPntStyleGetBlockScale pfCadPntStyleGetBlockScale;
	  pfCadPntStyleGetBlockScale = (tfCadPntStyleGetBlockScale)GetProcAddress( ghLibInst, "CadPntStyleGetBlockScale" );
	  if (pfCadPntStyleGetBlockScale){
		return (*pfCadPntStyleGetBlockScale)(hPntStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPntStylePutBlockScale (VHANDLE hPntStyle, double Scal)
	{
	  tfCadPntStylePutBlockScale pfCadPntStylePutBlockScale;
	  pfCadPntStylePutBlockScale = (tfCadPntStylePutBlockScale)GetProcAddress( ghLibInst, "CadPntStylePutBlockScale" );
	  if (pfCadPntStylePutBlockScale){
		(*pfCadPntStylePutBlockScale)(hPntStyle, Scal);
	  }
	}


	//--------------
	void CADAPI CadPntStyleGetFont (VHANDLE hPntStyle, TCHAR* szFontName)
	{
	  tfCadPntStyleGetFont pfCadPntStyleGetFont;
	  pfCadPntStyleGetFont = (tfCadPntStyleGetFont)GetProcAddress( ghLibInst, "CadPntStyleGetFont" );
	  if (pfCadPntStyleGetFont){
		(*pfCadPntStyleGetFont)(hPntStyle, szFontName);
	  }
	}


	//--------------
	void CADAPI CadPntStylePutFont (VHANDLE hPntStyle, LPCTSTR szFontName)
	{
	  tfCadPntStylePutFont pfCadPntStylePutFont;
	  pfCadPntStylePutFont = (tfCadPntStylePutFont)GetProcAddress( ghLibInst, "CadPntStylePutFont" );
	  if (pfCadPntStylePutFont){
		(*pfCadPntStylePutFont)(hPntStyle, szFontName);
	  }
	}


	//--------------
	double CADAPI CadPntStyleGetTextHeight (VHANDLE hPntStyle)
	{
	  tfCadPntStyleGetTextHeight pfCadPntStyleGetTextHeight;
	  pfCadPntStyleGetTextHeight = (tfCadPntStyleGetTextHeight)GetProcAddress( ghLibInst, "CadPntStyleGetTextHeight" );
	  if (pfCadPntStyleGetTextHeight){
		return (*pfCadPntStyleGetTextHeight)(hPntStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPntStylePutTextHeight (VHANDLE hPntStyle, double TxtH)
	{
	  tfCadPntStylePutTextHeight pfCadPntStylePutTextHeight;
	  pfCadPntStylePutTextHeight = (tfCadPntStylePutTextHeight)GetProcAddress( ghLibInst, "CadPntStylePutTextHeight" );
	  if (pfCadPntStylePutTextHeight){
		(*pfCadPntStylePutTextHeight)(hPntStyle, TxtH);
	  }
	}


	//--------------
	double CADAPI CadPntStyleGetTextWidth (VHANDLE hPntStyle)
	{
	  tfCadPntStyleGetTextWidth pfCadPntStyleGetTextWidth;
	  pfCadPntStyleGetTextWidth = (tfCadPntStyleGetTextWidth)GetProcAddress( ghLibInst, "CadPntStyleGetTextWidth" );
	  if (pfCadPntStyleGetTextWidth){
		return (*pfCadPntStyleGetTextWidth)(hPntStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPntStylePutTextWidth (VHANDLE hPntStyle, double TxtW)
	{
	  tfCadPntStylePutTextWidth pfCadPntStylePutTextWidth;
	  pfCadPntStylePutTextWidth = (tfCadPntStylePutTextWidth)GetProcAddress( ghLibInst, "CadPntStylePutTextWidth" );
	  if (pfCadPntStylePutTextWidth){
		(*pfCadPntStylePutTextWidth)(hPntStyle, TxtW);
	  }
	}


	//--------------
	int CADAPI CadPntStyleGetDrawMode (VHANDLE hPntStyle)
	{
	  tfCadPntStyleGetDrawMode pfCadPntStyleGetDrawMode;
	  pfCadPntStyleGetDrawMode = (tfCadPntStyleGetDrawMode)GetProcAddress( ghLibInst, "CadPntStyleGetDrawMode" );
	  if (pfCadPntStyleGetDrawMode){
		return (*pfCadPntStyleGetDrawMode)(hPntStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPntStylePutDrawMode (VHANDLE hPntStyle, int Mode)
	{
	  tfCadPntStylePutDrawMode pfCadPntStylePutDrawMode;
	  pfCadPntStylePutDrawMode = (tfCadPntStylePutDrawMode)GetProcAddress( ghLibInst, "CadPntStylePutDrawMode" );
	  if (pfCadPntStylePutDrawMode){
		(*pfCadPntStylePutDrawMode)(hPntStyle, Mode);
	  }
	}


	//--------------
	BOOL CADAPI CadPntStyleGetSnap (VHANDLE hPntStyle)
	{
	  tfCadPntStyleGetSnap pfCadPntStyleGetSnap;
	  pfCadPntStyleGetSnap = (tfCadPntStyleGetSnap)GetProcAddress( ghLibInst, "CadPntStyleGetSnap" );
	  if (pfCadPntStyleGetSnap){
		return (*pfCadPntStyleGetSnap)(hPntStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPntStylePutSnap (VHANDLE hPntStyle, BOOL bSnap)
	{
	  tfCadPntStylePutSnap pfCadPntStylePutSnap;
	  pfCadPntStylePutSnap = (tfCadPntStylePutSnap)GetProcAddress( ghLibInst, "CadPntStylePutSnap" );
	  if (pfCadPntStylePutSnap){
		(*pfCadPntStylePutSnap)(hPntStyle, bSnap);
	  }
	}


	//--------------
	BOOL CADAPI CadPntStyleGetFixed (VHANDLE hPntStyle)
	{
	  tfCadPntStyleGetFixed pfCadPntStyleGetFixed;
	  pfCadPntStyleGetFixed = (tfCadPntStyleGetFixed)GetProcAddress( ghLibInst, "CadPntStyleGetFixed" );
	  if (pfCadPntStyleGetFixed){
		return (*pfCadPntStyleGetFixed)(hPntStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPntStylePutFixed (VHANDLE hPntStyle, BOOL bFixed)
	{
	  tfCadPntStylePutFixed pfCadPntStylePutFixed;
	  pfCadPntStylePutFixed = (tfCadPntStylePutFixed)GetProcAddress( ghLibInst, "CadPntStylePutFixed" );
	  if (pfCadPntStylePutFixed){
		(*pfCadPntStylePutFixed)(hPntStyle, bFixed);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddMlineStyle (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadAddMlineStyle pfCadAddMlineStyle;
	  pfCadAddMlineStyle = (tfCadAddMlineStyle)GetProcAddress( ghLibInst, "CadAddMlineStyle" );
	  if (pfCadAddMlineStyle){
		return (*pfCadAddMlineStyle)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadDeleteMlineStyle (VDWG hDwg, VHANDLE hMStyle)
	{
	  tfCadDeleteMlineStyle pfCadDeleteMlineStyle;
	  pfCadDeleteMlineStyle = (tfCadDeleteMlineStyle)GetProcAddress( ghLibInst, "CadDeleteMlineStyle" );
	  if (pfCadDeleteMlineStyle){
		return (*pfCadDeleteMlineStyle)(hDwg, hMStyle);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadCountMlineStyles (VDWG hDwg)
	{
	  tfCadCountMlineStyles pfCadCountMlineStyles;
	  pfCadCountMlineStyles = (tfCadCountMlineStyles)GetProcAddress( ghLibInst, "CadCountMlineStyles" );
	  if (pfCadCountMlineStyles){
		return (*pfCadCountMlineStyles)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetCurMlineStyle (VDWG hDwg)
	{
	  tfCadGetCurMlineStyle pfCadGetCurMlineStyle;
	  pfCadGetCurMlineStyle = (tfCadGetCurMlineStyle)GetProcAddress( ghLibInst, "CadGetCurMlineStyle" );
	  if (pfCadGetCurMlineStyle){
		return (*pfCadGetCurMlineStyle)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurMlineStyle (VDWG hDwg, VHANDLE hMStyle)
	{
	  tfCadSetCurMlineStyle pfCadSetCurMlineStyle;
	  pfCadSetCurMlineStyle = (tfCadSetCurMlineStyle)GetProcAddress( ghLibInst, "CadSetCurMlineStyle" );
	  if (pfCadSetCurMlineStyle){
		return (*pfCadSetCurMlineStyle)(hDwg, hMStyle);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurMlineStyleByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadSetCurMlineStyleByID pfCadSetCurMlineStyleByID;
	  pfCadSetCurMlineStyleByID = (tfCadSetCurMlineStyleByID)GetProcAddress( ghLibInst, "CadSetCurMlineStyleByID" );
	  if (pfCadSetCurMlineStyleByID){
		return (*pfCadSetCurMlineStyleByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurMlineStyleByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadSetCurMlineStyleByName pfCadSetCurMlineStyleByName;
	  pfCadSetCurMlineStyleByName = (tfCadSetCurMlineStyleByName)GetProcAddress( ghLibInst, "CadSetCurMlineStyleByName" );
	  if (pfCadSetCurMlineStyleByName){
		return (*pfCadSetCurMlineStyleByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetFirstMlineStyle (VDWG hDwg)
	{
	  tfCadGetFirstMlineStyle pfCadGetFirstMlineStyle;
	  pfCadGetFirstMlineStyle = (tfCadGetFirstMlineStyle)GetProcAddress( ghLibInst, "CadGetFirstMlineStyle" );
	  if (pfCadGetFirstMlineStyle){
		return (*pfCadGetFirstMlineStyle)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetNextMlineStyle (VDWG hDwg, VHANDLE hMStyle)
	{
	  tfCadGetNextMlineStyle pfCadGetNextMlineStyle;
	  pfCadGetNextMlineStyle = (tfCadGetNextMlineStyle)GetProcAddress( ghLibInst, "CadGetNextMlineStyle" );
	  if (pfCadGetNextMlineStyle){
		return (*pfCadGetNextMlineStyle)(hDwg, hMStyle);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetMlineStyleByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadGetMlineStyleByID pfCadGetMlineStyleByID;
	  pfCadGetMlineStyleByID = (tfCadGetMlineStyleByID)GetProcAddress( ghLibInst, "CadGetMlineStyleByID" );
	  if (pfCadGetMlineStyleByID){
		return (*pfCadGetMlineStyleByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetMlineStyleByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadGetMlineStyleByName pfCadGetMlineStyleByName;
	  pfCadGetMlineStyleByName = (tfCadGetMlineStyleByName)GetProcAddress( ghLibInst, "CadGetMlineStyleByName" );
	  if (pfCadGetMlineStyleByName){
		return (*pfCadGetMlineStyleByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadMlineStyleGetID (VHANDLE hMStyle)
	{
	  tfCadMlineStyleGetID pfCadMlineStyleGetID;
	  pfCadMlineStyleGetID = (tfCadMlineStyleGetID)GetProcAddress( ghLibInst, "CadMlineStyleGetID" );
	  if (pfCadMlineStyleGetID){
		return (*pfCadMlineStyleGetID)(hMStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMlineStyleGetName (VHANDLE hMStyle, TCHAR* szName)
	{
	  tfCadMlineStyleGetName pfCadMlineStyleGetName;
	  pfCadMlineStyleGetName = (tfCadMlineStyleGetName)GetProcAddress( ghLibInst, "CadMlineStyleGetName" );
	  if (pfCadMlineStyleGetName){
		(*pfCadMlineStyleGetName)(hMStyle, szName);
	  }
	}


	//--------------
	void CADAPI CadMlineStylePutName (VHANDLE hMStyle, LPCTSTR szName)
	{
	  tfCadMlineStylePutName pfCadMlineStylePutName;
	  pfCadMlineStylePutName = (tfCadMlineStylePutName)GetProcAddress( ghLibInst, "CadMlineStylePutName" );
	  if (pfCadMlineStylePutName){
		(*pfCadMlineStylePutName)(hMStyle, szName);
	  }
	}


	//--------------
	UINT CADAPI CadMlineStyleGetDrawMode (VHANDLE hMStyle)
	{
	  tfCadMlineStyleGetDrawMode pfCadMlineStyleGetDrawMode;
	  pfCadMlineStyleGetDrawMode = (tfCadMlineStyleGetDrawMode)GetProcAddress( ghLibInst, "CadMlineStyleGetDrawMode" );
	  if (pfCadMlineStyleGetDrawMode){
		return (*pfCadMlineStyleGetDrawMode)(hMStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMlineStylePutDrawMode (VHANDLE hMStyle, UINT Mode)
	{
	  tfCadMlineStylePutDrawMode pfCadMlineStylePutDrawMode;
	  pfCadMlineStylePutDrawMode = (tfCadMlineStylePutDrawMode)GetProcAddress( ghLibInst, "CadMlineStylePutDrawMode" );
	  if (pfCadMlineStylePutDrawMode){
		(*pfCadMlineStylePutDrawMode)(hMStyle, Mode);
	  }
	}


	//--------------
	UINT CADAPI CadMlineStyleGetNumLines (VHANDLE hMStyle)
	{
	  tfCadMlineStyleGetNumLines pfCadMlineStyleGetNumLines;
	  pfCadMlineStyleGetNumLines = (tfCadMlineStyleGetNumLines)GetProcAddress( ghLibInst, "CadMlineStyleGetNumLines" );
	  if (pfCadMlineStyleGetNumLines){
		return (*pfCadMlineStyleGetNumLines)(hMStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMlineStylePutNumLines (VHANDLE hMStyle, UINT nLines)
	{
	  tfCadMlineStylePutNumLines pfCadMlineStylePutNumLines;
	  pfCadMlineStylePutNumLines = (tfCadMlineStylePutNumLines)GetProcAddress( ghLibInst, "CadMlineStylePutNumLines" );
	  if (pfCadMlineStylePutNumLines){
		(*pfCadMlineStylePutNumLines)(hMStyle, nLines);
	  }
	}


	//--------------
	int CADAPI CadMlineStyleGetColor (VHANDLE hMStyle, UINT iLine)
	{
	  tfCadMlineStyleGetColor pfCadMlineStyleGetColor;
	  pfCadMlineStyleGetColor = (tfCadMlineStyleGetColor)GetProcAddress( ghLibInst, "CadMlineStyleGetColor" );
	  if (pfCadMlineStyleGetColor){
		return (*pfCadMlineStyleGetColor)(hMStyle, iLine);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMlineStylePutColor (VHANDLE hMStyle, UINT iLine, int Color)
	{
	  tfCadMlineStylePutColor pfCadMlineStylePutColor;
	  pfCadMlineStylePutColor = (tfCadMlineStylePutColor)GetProcAddress( ghLibInst, "CadMlineStylePutColor" );
	  if (pfCadMlineStylePutColor){
		(*pfCadMlineStylePutColor)(hMStyle, iLine, Color);
	  }
	}


	//--------------
	IDOBJ CADAPI CadMlineStyleGetLtypeID (VHANDLE hMStyle, UINT iLine)
	{
	  tfCadMlineStyleGetLtypeID pfCadMlineStyleGetLtypeID;
	  pfCadMlineStyleGetLtypeID = (tfCadMlineStyleGetLtypeID)GetProcAddress( ghLibInst, "CadMlineStyleGetLtypeID" );
	  if (pfCadMlineStyleGetLtypeID){
		return (*pfCadMlineStyleGetLtypeID)(hMStyle, iLine);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMlineStylePutLtypeID (VHANDLE hMStyle, UINT iLine, IDOBJ Id)
	{
	  tfCadMlineStylePutLtypeID pfCadMlineStylePutLtypeID;
	  pfCadMlineStylePutLtypeID = (tfCadMlineStylePutLtypeID)GetProcAddress( ghLibInst, "CadMlineStylePutLtypeID" );
	  if (pfCadMlineStylePutLtypeID){
		(*pfCadMlineStylePutLtypeID)(hMStyle, iLine, Id);
	  }
	}


	//--------------
	double CADAPI CadMlineStyleGetOffset (VHANDLE hMStyle, UINT iLine)
	{
	  tfCadMlineStyleGetOffset pfCadMlineStyleGetOffset;
	  pfCadMlineStyleGetOffset = (tfCadMlineStyleGetOffset)GetProcAddress( ghLibInst, "CadMlineStyleGetOffset" );
	  if (pfCadMlineStyleGetOffset){
		return (*pfCadMlineStyleGetOffset)(hMStyle, iLine);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMlineStylePutOffset (VHANDLE hMStyle, UINT iLine, double Offset)
	{
	  tfCadMlineStylePutOffset pfCadMlineStylePutOffset;
	  pfCadMlineStylePutOffset = (tfCadMlineStylePutOffset)GetProcAddress( ghLibInst, "CadMlineStylePutOffset" );
	  if (pfCadMlineStylePutOffset){
		(*pfCadMlineStylePutOffset)(hMStyle, iLine, Offset);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddDimStyle (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadAddDimStyle pfCadAddDimStyle;
	  pfCadAddDimStyle = (tfCadAddDimStyle)GetProcAddress( ghLibInst, "CadAddDimStyle" );
	  if (pfCadAddDimStyle){
		return (*pfCadAddDimStyle)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadDeleteDimStyle (VDWG hDwg, VHANDLE hStyle)
	{
	  tfCadDeleteDimStyle pfCadDeleteDimStyle;
	  pfCadDeleteDimStyle = (tfCadDeleteDimStyle)GetProcAddress( ghLibInst, "CadDeleteDimStyle" );
	  if (pfCadDeleteDimStyle){
		return (*pfCadDeleteDimStyle)(hDwg, hStyle);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadCountDimStyles (VDWG hDwg)
	{
	  tfCadCountDimStyles pfCadCountDimStyles;
	  pfCadCountDimStyles = (tfCadCountDimStyles)GetProcAddress( ghLibInst, "CadCountDimStyles" );
	  if (pfCadCountDimStyles){
		return (*pfCadCountDimStyles)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetCurDimStyle (VDWG hDwg)
	{
	  tfCadGetCurDimStyle pfCadGetCurDimStyle;
	  pfCadGetCurDimStyle = (tfCadGetCurDimStyle)GetProcAddress( ghLibInst, "CadGetCurDimStyle" );
	  if (pfCadGetCurDimStyle){
		return (*pfCadGetCurDimStyle)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurDimStyle (VDWG hDwg, VHANDLE hStyle)
	{
	  tfCadSetCurDimStyle pfCadSetCurDimStyle;
	  pfCadSetCurDimStyle = (tfCadSetCurDimStyle)GetProcAddress( ghLibInst, "CadSetCurDimStyle" );
	  if (pfCadSetCurDimStyle){
		return (*pfCadSetCurDimStyle)(hDwg, hStyle);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurDimStyleByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadSetCurDimStyleByID pfCadSetCurDimStyleByID;
	  pfCadSetCurDimStyleByID = (tfCadSetCurDimStyleByID)GetProcAddress( ghLibInst, "CadSetCurDimStyleByID" );
	  if (pfCadSetCurDimStyleByID){
		return (*pfCadSetCurDimStyleByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSetCurDimStyleByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadSetCurDimStyleByName pfCadSetCurDimStyleByName;
	  pfCadSetCurDimStyleByName = (tfCadSetCurDimStyleByName)GetProcAddress( ghLibInst, "CadSetCurDimStyleByName" );
	  if (pfCadSetCurDimStyleByName){
		return (*pfCadSetCurDimStyleByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetFirstDimStyle (VDWG hDwg)
	{
	  tfCadGetFirstDimStyle pfCadGetFirstDimStyle;
	  pfCadGetFirstDimStyle = (tfCadGetFirstDimStyle)GetProcAddress( ghLibInst, "CadGetFirstDimStyle" );
	  if (pfCadGetFirstDimStyle){
		return (*pfCadGetFirstDimStyle)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetNextDimStyle (VDWG hDwg, VHANDLE hStyle)
	{
	  tfCadGetNextDimStyle pfCadGetNextDimStyle;
	  pfCadGetNextDimStyle = (tfCadGetNextDimStyle)GetProcAddress( ghLibInst, "CadGetNextDimStyle" );
	  if (pfCadGetNextDimStyle){
		return (*pfCadGetNextDimStyle)(hDwg, hStyle);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetDimStyleByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadGetDimStyleByID pfCadGetDimStyleByID;
	  pfCadGetDimStyleByID = (tfCadGetDimStyleByID)GetProcAddress( ghLibInst, "CadGetDimStyleByID" );
	  if (pfCadGetDimStyleByID){
		return (*pfCadGetDimStyleByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetDimStyleByName (VDWG hDwg, LPCTSTR szName)
	{
	  tfCadGetDimStyleByName pfCadGetDimStyleByName;
	  pfCadGetDimStyleByName = (tfCadGetDimStyleByName)GetProcAddress( ghLibInst, "CadGetDimStyleByName" );
	  if (pfCadGetDimStyleByName){
		return (*pfCadGetDimStyleByName)(hDwg, szName);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadDimStyleGetID (VHANDLE hStyle)
	{
	  tfCadDimStyleGetID pfCadDimStyleGetID;
	  pfCadDimStyleGetID = (tfCadDimStyleGetID)GetProcAddress( ghLibInst, "CadDimStyleGetID" );
	  if (pfCadDimStyleGetID){
		return (*pfCadDimStyleGetID)(hStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStyleGetName (VHANDLE hStyle, TCHAR* szName)
	{
	  tfCadDimStyleGetName pfCadDimStyleGetName;
	  pfCadDimStyleGetName = (tfCadDimStyleGetName)GetProcAddress( ghLibInst, "CadDimStyleGetName" );
	  if (pfCadDimStyleGetName){
		(*pfCadDimStyleGetName)(hStyle, szName);
	  }
	}


	//--------------
	void CADAPI CadDimStylePutName (VHANDLE hStyle, LPCTSTR szName)
	{
	  tfCadDimStylePutName pfCadDimStylePutName;
	  pfCadDimStylePutName = (tfCadDimStylePutName)GetProcAddress( ghLibInst, "CadDimStylePutName" );
	  if (pfCadDimStylePutName){
		(*pfCadDimStylePutName)(hStyle, szName);
	  }
	}


	//--------------
	int CADAPI CadDimStyleGetColor (VHANDLE hStyle, int Item)
	{
	  tfCadDimStyleGetColor pfCadDimStyleGetColor;
	  pfCadDimStyleGetColor = (tfCadDimStyleGetColor)GetProcAddress( ghLibInst, "CadDimStyleGetColor" );
	  if (pfCadDimStyleGetColor){
		return (*pfCadDimStyleGetColor)(hStyle, Item);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutColor (VHANDLE hStyle, int Item, int Color)
	{
	  tfCadDimStylePutColor pfCadDimStylePutColor;
	  pfCadDimStylePutColor = (tfCadDimStylePutColor)GetProcAddress( ghLibInst, "CadDimStylePutColor" );
	  if (pfCadDimStylePutColor){
		(*pfCadDimStylePutColor)(hStyle, Item, Color);
	  }
	}


	//--------------
	int CADAPI CadDimStyleGetLweight (VHANDLE hStyle, int Item)
	{
	  tfCadDimStyleGetLweight pfCadDimStyleGetLweight;
	  pfCadDimStyleGetLweight = (tfCadDimStyleGetLweight)GetProcAddress( ghLibInst, "CadDimStyleGetLweight" );
	  if (pfCadDimStyleGetLweight){
		return (*pfCadDimStyleGetLweight)(hStyle, Item);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutLweight (VHANDLE hStyle, int Item, int Lweight)
	{
	  tfCadDimStylePutLweight pfCadDimStylePutLweight;
	  pfCadDimStylePutLweight = (tfCadDimStylePutLweight)GetProcAddress( ghLibInst, "CadDimStylePutLweight" );
	  if (pfCadDimStylePutLweight){
		(*pfCadDimStylePutLweight)(hStyle, Item, Lweight);
	  }
	}


	//--------------
	double CADAPI CadDimStyleGetExtBeyond (VHANDLE hStyle)
	{
	  tfCadDimStyleGetExtBeyond pfCadDimStyleGetExtBeyond;
	  pfCadDimStyleGetExtBeyond = (tfCadDimStyleGetExtBeyond)GetProcAddress( ghLibInst, "CadDimStyleGetExtBeyond" );
	  if (pfCadDimStyleGetExtBeyond){
		return (*pfCadDimStyleGetExtBeyond)(hStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutExtBeyond (VHANDLE hStyle, double val)
	{
	  tfCadDimStylePutExtBeyond pfCadDimStylePutExtBeyond;
	  pfCadDimStylePutExtBeyond = (tfCadDimStylePutExtBeyond)GetProcAddress( ghLibInst, "CadDimStylePutExtBeyond" );
	  if (pfCadDimStylePutExtBeyond){
		(*pfCadDimStylePutExtBeyond)(hStyle, val);
	  }
	}


	//--------------
	double CADAPI CadDimStyleGetExtOffset (VHANDLE hStyle)
	{
	  tfCadDimStyleGetExtOffset pfCadDimStyleGetExtOffset;
	  pfCadDimStyleGetExtOffset = (tfCadDimStyleGetExtOffset)GetProcAddress( ghLibInst, "CadDimStyleGetExtOffset" );
	  if (pfCadDimStyleGetExtOffset){
		return (*pfCadDimStyleGetExtOffset)(hStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutExtOffset (VHANDLE hStyle, double val)
	{
	  tfCadDimStylePutExtOffset pfCadDimStylePutExtOffset;
	  pfCadDimStylePutExtOffset = (tfCadDimStylePutExtOffset)GetProcAddress( ghLibInst, "CadDimStylePutExtOffset" );
	  if (pfCadDimStylePutExtOffset){
		(*pfCadDimStylePutExtOffset)(hStyle, val);
	  }
	}


	//--------------
	int CADAPI CadDimStyleGetArrow (VHANDLE hStyle, int Place)
	{
	  tfCadDimStyleGetArrow pfCadDimStyleGetArrow;
	  pfCadDimStyleGetArrow = (tfCadDimStyleGetArrow)GetProcAddress( ghLibInst, "CadDimStyleGetArrow" );
	  if (pfCadDimStyleGetArrow){
		return (*pfCadDimStyleGetArrow)(hStyle, Place);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutArrow (VHANDLE hStyle, int Place, int ArrType)
	{
	  tfCadDimStylePutArrow pfCadDimStylePutArrow;
	  pfCadDimStylePutArrow = (tfCadDimStylePutArrow)GetProcAddress( ghLibInst, "CadDimStylePutArrow" );
	  if (pfCadDimStylePutArrow){
		(*pfCadDimStylePutArrow)(hStyle, Place, ArrType);
	  }
	}


	//--------------
	double CADAPI CadDimStyleGetArrowSize (VHANDLE hStyle)
	{
	  tfCadDimStyleGetArrowSize pfCadDimStyleGetArrowSize;
	  pfCadDimStyleGetArrowSize = (tfCadDimStyleGetArrowSize)GetProcAddress( ghLibInst, "CadDimStyleGetArrowSize" );
	  if (pfCadDimStyleGetArrowSize){
		return (*pfCadDimStyleGetArrowSize)(hStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutArrowSize (VHANDLE hStyle, double Size)
	{
	  tfCadDimStylePutArrowSize pfCadDimStylePutArrowSize;
	  pfCadDimStylePutArrowSize = (tfCadDimStylePutArrowSize)GetProcAddress( ghLibInst, "CadDimStylePutArrowSize" );
	  if (pfCadDimStylePutArrowSize){
		(*pfCadDimStylePutArrowSize)(hStyle, Size);
	  }
	}


	//--------------
	double CADAPI CadDimStyleGetCenMark (VHANDLE hStyle)
	{
	  tfCadDimStyleGetCenMark pfCadDimStyleGetCenMark;
	  pfCadDimStyleGetCenMark = (tfCadDimStyleGetCenMark)GetProcAddress( ghLibInst, "CadDimStyleGetCenMark" );
	  if (pfCadDimStyleGetCenMark){
		return (*pfCadDimStyleGetCenMark)(hStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutCenMark (VHANDLE hStyle, double Size)
	{
	  tfCadDimStylePutCenMark pfCadDimStylePutCenMark;
	  pfCadDimStylePutCenMark = (tfCadDimStylePutCenMark)GetProcAddress( ghLibInst, "CadDimStylePutCenMark" );
	  if (pfCadDimStylePutCenMark){
		(*pfCadDimStylePutCenMark)(hStyle, Size);
	  }
	}


	//--------------
	double CADAPI CadDimStyleGetTextHeight (VHANDLE hStyle)
	{
	  tfCadDimStyleGetTextHeight pfCadDimStyleGetTextHeight;
	  pfCadDimStyleGetTextHeight = (tfCadDimStyleGetTextHeight)GetProcAddress( ghLibInst, "CadDimStyleGetTextHeight" );
	  if (pfCadDimStyleGetTextHeight){
		return (*pfCadDimStyleGetTextHeight)(hStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutTextHeight (VHANDLE hStyle, double Height)
	{
	  tfCadDimStylePutTextHeight pfCadDimStylePutTextHeight;
	  pfCadDimStylePutTextHeight = (tfCadDimStylePutTextHeight)GetProcAddress( ghLibInst, "CadDimStylePutTextHeight" );
	  if (pfCadDimStylePutTextHeight){
		(*pfCadDimStylePutTextHeight)(hStyle, Height);
	  }
	}


	//--------------
	double CADAPI CadDimStyleGetTextGap (VHANDLE hStyle)
	{
	  tfCadDimStyleGetTextGap pfCadDimStyleGetTextGap;
	  pfCadDimStyleGetTextGap = (tfCadDimStyleGetTextGap)GetProcAddress( ghLibInst, "CadDimStyleGetTextGap" );
	  if (pfCadDimStyleGetTextGap){
		return (*pfCadDimStyleGetTextGap)(hStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutTextGap (VHANDLE hStyle, double Gap)
	{
	  tfCadDimStylePutTextGap pfCadDimStylePutTextGap;
	  pfCadDimStylePutTextGap = (tfCadDimStylePutTextGap)GetProcAddress( ghLibInst, "CadDimStylePutTextGap" );
	  if (pfCadDimStylePutTextGap){
		(*pfCadDimStylePutTextGap)(hStyle, Gap);
	  }
	}


	//--------------
	IDOBJ CADAPI CadDimStyleGetTextStyleID (VHANDLE hStyle)
	{
	  tfCadDimStyleGetTextStyleID pfCadDimStyleGetTextStyleID;
	  pfCadDimStyleGetTextStyleID = (tfCadDimStyleGetTextStyleID)GetProcAddress( ghLibInst, "CadDimStyleGetTextStyleID" );
	  if (pfCadDimStyleGetTextStyleID){
		return (*pfCadDimStyleGetTextStyleID)(hStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutTextStyleID (VHANDLE hStyle, IDOBJ Id)
	{
	  tfCadDimStylePutTextStyleID pfCadDimStylePutTextStyleID;
	  pfCadDimStylePutTextStyleID = (tfCadDimStylePutTextStyleID)GetProcAddress( ghLibInst, "CadDimStylePutTextStyleID" );
	  if (pfCadDimStylePutTextStyleID){
		(*pfCadDimStylePutTextStyleID)(hStyle, Id);
	  }
	}


	//--------------
	UINT CADAPI CadDimStyleGetTextPlace (VHANDLE hStyle)
	{
	  tfCadDimStyleGetTextPlace pfCadDimStyleGetTextPlace;
	  pfCadDimStyleGetTextPlace = (tfCadDimStyleGetTextPlace)GetProcAddress( ghLibInst, "CadDimStyleGetTextPlace" );
	  if (pfCadDimStyleGetTextPlace){
		return (*pfCadDimStyleGetTextPlace)(hStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutTextPlace (VHANDLE hStyle, UINT Placement)
	{
	  tfCadDimStylePutTextPlace pfCadDimStylePutTextPlace;
	  pfCadDimStylePutTextPlace = (tfCadDimStylePutTextPlace)GetProcAddress( ghLibInst, "CadDimStylePutTextPlace" );
	  if (pfCadDimStylePutTextPlace){
		(*pfCadDimStylePutTextPlace)(hStyle, Placement);
	  }
	}


	//--------------
	double CADAPI CadDimStyleGetScale (VHANDLE hStyle)
	{
	  tfCadDimStyleGetScale pfCadDimStyleGetScale;
	  pfCadDimStyleGetScale = (tfCadDimStyleGetScale)GetProcAddress( ghLibInst, "CadDimStyleGetScale" );
	  if (pfCadDimStyleGetScale){
		return (*pfCadDimStyleGetScale)(hStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutScale (VHANDLE hStyle, double Scal)
	{
	  tfCadDimStylePutScale pfCadDimStylePutScale;
	  pfCadDimStylePutScale = (tfCadDimStylePutScale)GetProcAddress( ghLibInst, "CadDimStylePutScale" );
	  if (pfCadDimStylePutScale){
		(*pfCadDimStylePutScale)(hStyle, Scal);
	  }
	}


	//--------------
	double CADAPI CadDimStyleGetRound (VHANDLE hStyle)
	{
	  tfCadDimStyleGetRound pfCadDimStyleGetRound;
	  pfCadDimStyleGetRound = (tfCadDimStyleGetRound)GetProcAddress( ghLibInst, "CadDimStyleGetRound" );
	  if (pfCadDimStyleGetRound){
		return (*pfCadDimStyleGetRound)(hStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutRound (VHANDLE hStyle, double RoundOff)
	{
	  tfCadDimStylePutRound pfCadDimStylePutRound;
	  pfCadDimStylePutRound = (tfCadDimStylePutRound)GetProcAddress( ghLibInst, "CadDimStylePutRound" );
	  if (pfCadDimStylePutRound){
		(*pfCadDimStylePutRound)(hStyle, RoundOff);
	  }
	}


	//--------------
	int CADAPI CadDimStyleGetUnits (VHANDLE hStyle, BOOL bAngular)
	{
	  tfCadDimStyleGetUnits pfCadDimStyleGetUnits;
	  pfCadDimStyleGetUnits = (tfCadDimStyleGetUnits)GetProcAddress( ghLibInst, "CadDimStyleGetUnits" );
	  if (pfCadDimStyleGetUnits){
		return (*pfCadDimStyleGetUnits)(hStyle, bAngular);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutUnits (VHANDLE hStyle, BOOL bAngular, int UnitsType)
	{
	  tfCadDimStylePutUnits pfCadDimStylePutUnits;
	  pfCadDimStylePutUnits = (tfCadDimStylePutUnits)GetProcAddress( ghLibInst, "CadDimStylePutUnits" );
	  if (pfCadDimStylePutUnits){
		(*pfCadDimStylePutUnits)(hStyle, bAngular, UnitsType);
	  }
	}


	//--------------
	int CADAPI CadDimStyleGetPrecision (VHANDLE hStyle, BOOL bAngular)
	{
	  tfCadDimStyleGetPrecision pfCadDimStyleGetPrecision;
	  pfCadDimStyleGetPrecision = (tfCadDimStyleGetPrecision)GetProcAddress( ghLibInst, "CadDimStyleGetPrecision" );
	  if (pfCadDimStyleGetPrecision){
		return (*pfCadDimStyleGetPrecision)(hStyle, bAngular);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutPrecision (VHANDLE hStyle, BOOL bAngular, int Prec)
	{
	  tfCadDimStylePutPrecision pfCadDimStylePutPrecision;
	  pfCadDimStylePutPrecision = (tfCadDimStylePutPrecision)GetProcAddress( ghLibInst, "CadDimStylePutPrecision" );
	  if (pfCadDimStylePutPrecision){
		(*pfCadDimStylePutPrecision)(hStyle, bAngular, Prec);
	  }
	}


	//--------------
	BOOL CADAPI CadDimStyleGetZeroSup (VHANDLE hStyle, BOOL bAngular)
	{
	  tfCadDimStyleGetZeroSup pfCadDimStyleGetZeroSup;
	  pfCadDimStyleGetZeroSup = (tfCadDimStyleGetZeroSup)GetProcAddress( ghLibInst, "CadDimStyleGetZeroSup" );
	  if (pfCadDimStyleGetZeroSup){
		return (*pfCadDimStyleGetZeroSup)(hStyle, bAngular);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutZeroSup (VHANDLE hStyle, BOOL bAngular, BOOL bSuppress)
	{
	  tfCadDimStylePutZeroSup pfCadDimStylePutZeroSup;
	  pfCadDimStylePutZeroSup = (tfCadDimStylePutZeroSup)GetProcAddress( ghLibInst, "CadDimStylePutZeroSup" );
	  if (pfCadDimStylePutZeroSup){
		(*pfCadDimStylePutZeroSup)(hStyle, bAngular, bSuppress);
	  }
	}


	//--------------
	int CADAPI CadDimStyleGetSeparator (VHANDLE hStyle)
	{
	  tfCadDimStyleGetSeparator pfCadDimStyleGetSeparator;
	  pfCadDimStyleGetSeparator = (tfCadDimStyleGetSeparator)GetProcAddress( ghLibInst, "CadDimStyleGetSeparator" );
	  if (pfCadDimStyleGetSeparator){
		return (*pfCadDimStyleGetSeparator)(hStyle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimStylePutSeparator (VHANDLE hStyle, int DecSep)
	{
	  tfCadDimStylePutSeparator pfCadDimStylePutSeparator;
	  pfCadDimStylePutSeparator = (tfCadDimStylePutSeparator)GetProcAddress( ghLibInst, "CadDimStylePutSeparator" );
	  if (pfCadDimStylePutSeparator){
		(*pfCadDimStylePutSeparator)(hStyle, DecSep);
	  }
	}


	//--------------
	void CADAPI CadDimStyleGetPrefix (VHANDLE hStyle, TCHAR* szPrefix)
	{
	  tfCadDimStyleGetPrefix pfCadDimStyleGetPrefix;
	  pfCadDimStyleGetPrefix = (tfCadDimStyleGetPrefix)GetProcAddress( ghLibInst, "CadDimStyleGetPrefix" );
	  if (pfCadDimStyleGetPrefix){
		(*pfCadDimStyleGetPrefix)(hStyle, szPrefix);
	  }
	}


	//--------------
	void CADAPI CadDimStylePutPrefix (VHANDLE hStyle, LPCTSTR szPrefix)
	{
	  tfCadDimStylePutPrefix pfCadDimStylePutPrefix;
	  pfCadDimStylePutPrefix = (tfCadDimStylePutPrefix)GetProcAddress( ghLibInst, "CadDimStylePutPrefix" );
	  if (pfCadDimStylePutPrefix){
		(*pfCadDimStylePutPrefix)(hStyle, szPrefix);
	  }
	}


	//--------------
	void CADAPI CadDimStyleGetSuffix (VHANDLE hStyle, TCHAR* szSuffix)
	{
	  tfCadDimStyleGetSuffix pfCadDimStyleGetSuffix;
	  pfCadDimStyleGetSuffix = (tfCadDimStyleGetSuffix)GetProcAddress( ghLibInst, "CadDimStyleGetSuffix" );
	  if (pfCadDimStyleGetSuffix){
		(*pfCadDimStyleGetSuffix)(hStyle, szSuffix);
	  }
	}


	//--------------
	void CADAPI CadDimStylePutSuffix (VHANDLE hStyle, LPCTSTR szSuffix)
	{
	  tfCadDimStylePutSuffix pfCadDimStylePutSuffix;
	  pfCadDimStylePutSuffix = (tfCadDimStylePutSuffix)GetProcAddress( ghLibInst, "CadDimStylePutSuffix" );
	  if (pfCadDimStylePutSuffix){
		(*pfCadDimStylePutSuffix)(hStyle, szSuffix);
	  }
	}


	//--------------
	VHANDLE CADAPI CadGetEntityByCursor (VDWG hDwg)
	{
	  tfCadGetEntityByCursor pfCadGetEntityByCursor;
	  pfCadGetEntityByCursor = (tfCadGetEntityByCursor)GetProcAddress( ghLibInst, "CadGetEntityByCursor" );
	  if (pfCadGetEntityByCursor){
		return (*pfCadGetEntityByCursor)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGetEntitiesByPoint (VDWG hDwg, int Xwin, int Ywin, int* phEnt, int* pnEnts, int iMax)
	{
	  tfCadGetEntitiesByPoint pfCadGetEntitiesByPoint;
	  pfCadGetEntitiesByPoint = (tfCadGetEntitiesByPoint)GetProcAddress( ghLibInst, "CadGetEntitiesByPoint" );
	  if (pfCadGetEntitiesByPoint){
		(*pfCadGetEntitiesByPoint)(hDwg, Xwin, Ywin, phEnt, pnEnts, iMax);
	  }
	}


	//--------------
	void CADAPI CadGetEntitiesByRect (VDWG hDwg, int Lwin, int Twin, int Rwin, int Bwin, int* phEnt, int* pnEnts, int nMax)
	{
	  tfCadGetEntitiesByRect pfCadGetEntitiesByRect;
	  pfCadGetEntitiesByRect = (tfCadGetEntitiesByRect)GetProcAddress( ghLibInst, "CadGetEntitiesByRect" );
	  if (pfCadGetEntitiesByRect){
		(*pfCadGetEntitiesByRect)(hDwg, Lwin, Twin, Rwin, Bwin, phEnt, pnEnts, nMax);
	  }
	}


	//--------------
	VHANDLE CADAPI CadGetEntityByPoint (VDWG hDwg, int Xwin, int Ywin)
	{
	  tfCadGetEntityByPoint pfCadGetEntityByPoint;
	  pfCadGetEntityByPoint = (tfCadGetEntityByPoint)GetProcAddress( ghLibInst, "CadGetEntityByPoint" );
	  if (pfCadGetEntityByPoint){
		return (*pfCadGetEntityByPoint)(hDwg, Xwin, Ywin);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetEntityByPointIn (VDWG hDwg, double Xdisp, double Ydisp)
	{
	  tfCadGetEntityByPointIn pfCadGetEntityByPointIn;
	  pfCadGetEntityByPointIn = (tfCadGetEntityByPointIn)GetProcAddress( ghLibInst, "CadGetEntityByPointIn" );
	  if (pfCadGetEntityByPointIn){
		return (*pfCadGetEntityByPointIn)(hDwg, Xdisp, Ydisp);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetEntityByID (VDWG hDwg, IDOBJ Id)
	{
	  tfCadGetEntityByID pfCadGetEntityByID;
	  pfCadGetEntityByID = (tfCadGetEntityByID)GetProcAddress( ghLibInst, "CadGetEntityByID" );
	  if (pfCadGetEntityByID){
		return (*pfCadGetEntityByID)(hDwg, Id);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetEntityByUserData (VDWG hDwg, DWORD UserData)
	{
	  tfCadGetEntityByUserData pfCadGetEntityByUserData;
	  pfCadGetEntityByUserData = (tfCadGetEntityByUserData)GetProcAddress( ghLibInst, "CadGetEntityByUserData" );
	  if (pfCadGetEntityByUserData){
		return (*pfCadGetEntityByUserData)(hDwg, UserData);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetEntityByPtr (VHANDLE hPtr)
	{
	  tfCadGetEntityByPtr pfCadGetEntityByPtr;
	  pfCadGetEntityByPtr = (tfCadGetEntityByPtr)GetProcAddress( ghLibInst, "CadGetEntityByPtr" );
	  if (pfCadGetEntityByPtr){
		return (*pfCadGetEntityByPtr)(hPtr);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetFirstEntity (VDWG hDwg)
	{
	  tfCadGetFirstEntity pfCadGetFirstEntity;
	  pfCadGetFirstEntity = (tfCadGetFirstEntity)GetProcAddress( ghLibInst, "CadGetFirstEntity" );
	  if (pfCadGetFirstEntity){
		return (*pfCadGetFirstEntity)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetNextEntity (VDWG hDwg, VHANDLE hEnt)
	{
	  tfCadGetNextEntity pfCadGetNextEntity;
	  pfCadGetNextEntity = (tfCadGetNextEntity)GetProcAddress( ghLibInst, "CadGetNextEntity" );
	  if (pfCadGetNextEntity){
		return (*pfCadGetNextEntity)(hDwg, hEnt);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetPickEntity (VDWG hDwg)
	{
	  tfCadGetPickEntity pfCadGetPickEntity;
	  pfCadGetPickEntity = (tfCadGetPickEntity)GetProcAddress( ghLibInst, "CadGetPickEntity" );
	  if (pfCadGetPickEntity){
		return (*pfCadGetPickEntity)(hDwg);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadEntityGetID (VHANDLE hEnt)
	{
	  tfCadEntityGetID pfCadEntityGetID;
	  pfCadEntityGetID = (tfCadEntityGetID)GetProcAddress( ghLibInst, "CadEntityGetID" );
	  if (pfCadEntityGetID){
		return (*pfCadEntityGetID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	DWORD CADAPI CadEntityGetType (VHANDLE hEnt)
	{
	  tfCadEntityGetType pfCadEntityGetType;
	  pfCadEntityGetType = (tfCadEntityGetType)GetProcAddress( ghLibInst, "CadEntityGetType" );
	  if (pfCadEntityGetType){
		return (*pfCadEntityGetType)(hEnt);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadEntityGetLeft (VHANDLE hEnt)
	{
	  tfCadEntityGetLeft pfCadEntityGetLeft;
	  pfCadEntityGetLeft = (tfCadEntityGetLeft)GetProcAddress( ghLibInst, "CadEntityGetLeft" );
	  if (pfCadEntityGetLeft){
		return (*pfCadEntityGetLeft)(hEnt);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadEntityGetBottom (VHANDLE hEnt)
	{
	  tfCadEntityGetBottom pfCadEntityGetBottom;
	  pfCadEntityGetBottom = (tfCadEntityGetBottom)GetProcAddress( ghLibInst, "CadEntityGetBottom" );
	  if (pfCadEntityGetBottom){
		return (*pfCadEntityGetBottom)(hEnt);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadEntityGetRight (VHANDLE hEnt)
	{
	  tfCadEntityGetRight pfCadEntityGetRight;
	  pfCadEntityGetRight = (tfCadEntityGetRight)GetProcAddress( ghLibInst, "CadEntityGetRight" );
	  if (pfCadEntityGetRight){
		return (*pfCadEntityGetRight)(hEnt);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadEntityGetTop (VHANDLE hEnt)
	{
	  tfCadEntityGetTop pfCadEntityGetTop;
	  pfCadEntityGetTop = (tfCadEntityGetTop)GetProcAddress( ghLibInst, "CadEntityGetTop" );
	  if (pfCadEntityGetTop){
		return (*pfCadEntityGetTop)(hEnt);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadEntityGetNumPaths (VHANDLE hEnt)
	{
	  tfCadEntityGetNumPaths pfCadEntityGetNumPaths;
	  pfCadEntityGetNumPaths = (tfCadEntityGetNumPaths)GetProcAddress( ghLibInst, "CadEntityGetNumPaths" );
	  if (pfCadEntityGetNumPaths){
		return (*pfCadEntityGetNumPaths)(hEnt);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadEntityGetPathSize (VHANDLE hEnt, int iPath)
	{
	  tfCadEntityGetPathSize pfCadEntityGetPathSize;
	  pfCadEntityGetPathSize = (tfCadEntityGetPathSize)GetProcAddress( ghLibInst, "CadEntityGetPathSize" );
	  if (pfCadEntityGetPathSize){
		return (*pfCadEntityGetPathSize)(hEnt, iPath);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityGetVer (VHANDLE hEnt, int iVer, double* pX, double* pY)
	{
	  tfCadEntityGetVer pfCadEntityGetVer;
	  pfCadEntityGetVer = (tfCadEntityGetVer)GetProcAddress( ghLibInst, "CadEntityGetVer" );
	  if (pfCadEntityGetVer){
		(*pfCadEntityGetVer)(hEnt, iVer, pX, pY);
	  }
	}


	//--------------
	BOOL CADAPI CadEntityGetGrip (VHANDLE hEnt, int iGrip, double* pX, double* pY, double* pZ)
	{
	  tfCadEntityGetGrip pfCadEntityGetGrip;
	  pfCadEntityGetGrip = (tfCadEntityGetGrip)GetProcAddress( ghLibInst, "CadEntityGetGrip" );
	  if (pfCadEntityGetGrip){
		return (*pfCadEntityGetGrip)(hEnt, iGrip, pX, pY, pZ);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadEntityGetLayerID (VHANDLE hEnt)
	{
	  tfCadEntityGetLayerID pfCadEntityGetLayerID;
	  pfCadEntityGetLayerID = (tfCadEntityGetLayerID)GetProcAddress( ghLibInst, "CadEntityGetLayerID" );
	  if (pfCadEntityGetLayerID){
		return (*pfCadEntityGetLayerID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadEntityPutLayerID (VHANDLE hEnt, VDWG hDwg, IDOBJ LayerID)
	{
	  tfCadEntityPutLayerID pfCadEntityPutLayerID;
	  pfCadEntityPutLayerID = (tfCadEntityPutLayerID)GetProcAddress( ghLibInst, "CadEntityPutLayerID" );
	  if (pfCadEntityPutLayerID){
		return (*pfCadEntityPutLayerID)(hEnt, hDwg, LayerID);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadEntityGetPageID (VHANDLE hEnt)
	{
	  tfCadEntityGetPageID pfCadEntityGetPageID;
	  pfCadEntityGetPageID = (tfCadEntityGetPageID)GetProcAddress( ghLibInst, "CadEntityGetPageID" );
	  if (pfCadEntityGetPageID){
		return (*pfCadEntityGetPageID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutPageID (VHANDLE hEnt, IDOBJ PageID)
	{
	  tfCadEntityPutPageID pfCadEntityPutPageID;
	  pfCadEntityPutPageID = (tfCadEntityPutPageID)GetProcAddress( ghLibInst, "CadEntityPutPageID" );
	  if (pfCadEntityPutPageID){
		(*pfCadEntityPutPageID)(hEnt, PageID);
	  }
	}


	//--------------
	IDOBJ CADAPI CadEntityGetLinetypeID (VHANDLE hEnt)
	{
	  tfCadEntityGetLinetypeID pfCadEntityGetLinetypeID;
	  pfCadEntityGetLinetypeID = (tfCadEntityGetLinetypeID)GetProcAddress( ghLibInst, "CadEntityGetLinetypeID" );
	  if (pfCadEntityGetLinetypeID){
		return (*pfCadEntityGetLinetypeID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutLinetypeID (VHANDLE hEnt, IDOBJ Id)
	{
	  tfCadEntityPutLinetypeID pfCadEntityPutLinetypeID;
	  pfCadEntityPutLinetypeID = (tfCadEntityPutLinetypeID)GetProcAddress( ghLibInst, "CadEntityPutLinetypeID" );
	  if (pfCadEntityPutLinetypeID){
		(*pfCadEntityPutLinetypeID)(hEnt, Id);
	  }
	}


	//--------------
	double CADAPI CadEntityGetLtScale (VHANDLE hEnt)
	{
	  tfCadEntityGetLtScale pfCadEntityGetLtScale;
	  pfCadEntityGetLtScale = (tfCadEntityGetLtScale)GetProcAddress( ghLibInst, "CadEntityGetLtScale" );
	  if (pfCadEntityGetLtScale){
		return (*pfCadEntityGetLtScale)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutLtScale (VHANDLE hEnt, double lts)
	{
	  tfCadEntityPutLtScale pfCadEntityPutLtScale;
	  pfCadEntityPutLtScale = (tfCadEntityPutLtScale)GetProcAddress( ghLibInst, "CadEntityPutLtScale" );
	  if (pfCadEntityPutLtScale){
		(*pfCadEntityPutLtScale)(hEnt, lts);
	  }
	}


	//--------------
	int CADAPI CadEntityGetColor (VHANDLE hEnt)
	{
	  tfCadEntityGetColor pfCadEntityGetColor;
	  pfCadEntityGetColor = (tfCadEntityGetColor)GetProcAddress( ghLibInst, "CadEntityGetColor" );
	  if (pfCadEntityGetColor){
		return (*pfCadEntityGetColor)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutColor (VHANDLE hEnt, int Color)
	{
	  tfCadEntityPutColor pfCadEntityPutColor;
	  pfCadEntityPutColor = (tfCadEntityPutColor)GetProcAddress( ghLibInst, "CadEntityPutColor" );
	  if (pfCadEntityPutColor){
		(*pfCadEntityPutColor)(hEnt, Color);
	  }
	}


	//--------------
	DWORD CADAPI CadEntityGetLineweight (VHANDLE hEnt)
	{
	  tfCadEntityGetLineweight pfCadEntityGetLineweight;
	  pfCadEntityGetLineweight = (tfCadEntityGetLineweight)GetProcAddress( ghLibInst, "CadEntityGetLineweight" );
	  if (pfCadEntityGetLineweight){
		return (*pfCadEntityGetLineweight)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutLineweight (VHANDLE hEnt, int lw)
	{
	  tfCadEntityPutLineweight pfCadEntityPutLineweight;
	  pfCadEntityPutLineweight = (tfCadEntityPutLineweight)GetProcAddress( ghLibInst, "CadEntityPutLineweight" );
	  if (pfCadEntityPutLineweight){
		(*pfCadEntityPutLineweight)(hEnt, lw);
	  }
	}


	//--------------
	DWORD CADAPI CadEntityGetUserData (VHANDLE hEnt)
	{
	  tfCadEntityGetUserData pfCadEntityGetUserData;
	  pfCadEntityGetUserData = (tfCadEntityGetUserData)GetProcAddress( ghLibInst, "CadEntityGetUserData" );
	  if (pfCadEntityGetUserData){
		return (*pfCadEntityGetUserData)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutUserData (VHANDLE hEnt, DWORD val)
	{
	  tfCadEntityPutUserData pfCadEntityPutUserData;
	  pfCadEntityPutUserData = (tfCadEntityPutUserData)GetProcAddress( ghLibInst, "CadEntityPutUserData" );
	  if (pfCadEntityPutUserData){
		(*pfCadEntityPutUserData)(hEnt, val);
	  }
	}


	//--------------
	BOOL CADAPI CadEntityGetFilled (VHANDLE hEnt)
	{
	  tfCadEntityGetFilled pfCadEntityGetFilled;
	  pfCadEntityGetFilled = (tfCadEntityGetFilled)GetProcAddress( ghLibInst, "CadEntityGetFilled" );
	  if (pfCadEntityGetFilled){
		return (*pfCadEntityGetFilled)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutFilled (VHANDLE hEnt, BOOL bFilled)
	{
	  tfCadEntityPutFilled pfCadEntityPutFilled;
	  pfCadEntityPutFilled = (tfCadEntityPutFilled)GetProcAddress( ghLibInst, "CadEntityPutFilled" );
	  if (pfCadEntityPutFilled){
		(*pfCadEntityPutFilled)(hEnt, bFilled);
	  }
	}


	//--------------
	BOOL CADAPI CadEntityGetBorder (VHANDLE hEnt)
	{
	  tfCadEntityGetBorder pfCadEntityGetBorder;
	  pfCadEntityGetBorder = (tfCadEntityGetBorder)GetProcAddress( ghLibInst, "CadEntityGetBorder" );
	  if (pfCadEntityGetBorder){
		return (*pfCadEntityGetBorder)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutBorder (VHANDLE hEnt, BOOL bBorder)
	{
	  tfCadEntityPutBorder pfCadEntityPutBorder;
	  pfCadEntityPutBorder = (tfCadEntityPutBorder)GetProcAddress( ghLibInst, "CadEntityPutBorder" );
	  if (pfCadEntityPutBorder){
		(*pfCadEntityPutBorder)(hEnt, bBorder);
	  }
	}


	//--------------
	int CADAPI CadEntityGetBordColor (VHANDLE hEnt)
	{
	  tfCadEntityGetBordColor pfCadEntityGetBordColor;
	  pfCadEntityGetBordColor = (tfCadEntityGetBordColor)GetProcAddress( ghLibInst, "CadEntityGetBordColor" );
	  if (pfCadEntityGetBordColor){
		return (*pfCadEntityGetBordColor)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutBordColor (VHANDLE hEnt, int Color)
	{
	  tfCadEntityPutBordColor pfCadEntityPutBordColor;
	  pfCadEntityPutBordColor = (tfCadEntityPutBordColor)GetProcAddress( ghLibInst, "CadEntityPutBordColor" );
	  if (pfCadEntityPutBordColor){
		(*pfCadEntityPutBordColor)(hEnt, Color);
	  }
	}


	//--------------
	BOOL CADAPI CadEntityGetBlink (VHANDLE hEnt)
	{
	  tfCadEntityGetBlink pfCadEntityGetBlink;
	  pfCadEntityGetBlink = (tfCadEntityGetBlink)GetProcAddress( ghLibInst, "CadEntityGetBlink" );
	  if (pfCadEntityGetBlink){
		return (*pfCadEntityGetBlink)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutBlink (VHANDLE hEnt, BOOL bBlink)
	{
	  tfCadEntityPutBlink pfCadEntityPutBlink;
	  pfCadEntityPutBlink = (tfCadEntityPutBlink)GetProcAddress( ghLibInst, "CadEntityPutBlink" );
	  if (pfCadEntityPutBlink){
		(*pfCadEntityPutBlink)(hEnt, bBlink);
	  }
	}


	//--------------
	BOOL CADAPI CadEntityGetVisible (VHANDLE hEnt)
	{
	  tfCadEntityGetVisible pfCadEntityGetVisible;
	  pfCadEntityGetVisible = (tfCadEntityGetVisible)GetProcAddress( ghLibInst, "CadEntityGetVisible" );
	  if (pfCadEntityGetVisible){
		return (*pfCadEntityGetVisible)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutVisible (VHANDLE hEnt, BOOL bVisible)
	{
	  tfCadEntityPutVisible pfCadEntityPutVisible;
	  pfCadEntityPutVisible = (tfCadEntityPutVisible)GetProcAddress( ghLibInst, "CadEntityPutVisible" );
	  if (pfCadEntityPutVisible){
		(*pfCadEntityPutVisible)(hEnt, bVisible);
	  }
	}


	//--------------
	BOOL CADAPI CadEntityGetDeleted (VHANDLE hEnt)
	{
	  tfCadEntityGetDeleted pfCadEntityGetDeleted;
	  pfCadEntityGetDeleted = (tfCadEntityGetDeleted)GetProcAddress( ghLibInst, "CadEntityGetDeleted" );
	  if (pfCadEntityGetDeleted){
		return (*pfCadEntityGetDeleted)(hEnt);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadEntityGetSelected (VDWG hDwg, VHANDLE hEnt)
	{
	  tfCadEntityGetSelected pfCadEntityGetSelected;
	  pfCadEntityGetSelected = (tfCadEntityGetSelected)GetProcAddress( ghLibInst, "CadEntityGetSelected" );
	  if (pfCadEntityGetSelected){
		return (*pfCadEntityGetSelected)(hDwg, hEnt);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadEntityGetLocked (VHANDLE hEnt)
	{
	  tfCadEntityGetLocked pfCadEntityGetLocked;
	  pfCadEntityGetLocked = (tfCadEntityGetLocked)GetProcAddress( ghLibInst, "CadEntityGetLocked" );
	  if (pfCadEntityGetLocked){
		return (*pfCadEntityGetLocked)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutLocked (VHANDLE hEnt, BOOL bLock)
	{
	  tfCadEntityPutLocked pfCadEntityPutLocked;
	  pfCadEntityPutLocked = (tfCadEntityPutLocked)GetProcAddress( ghLibInst, "CadEntityPutLocked" );
	  if (pfCadEntityPutLocked){
		(*pfCadEntityPutLocked)(hEnt, bLock);
	  }
	}


	//--------------
	void CADAPI CadEntityPutExData (VHANDLE hEnt, void* pData, int nBytes)
	{
	  tfCadEntityPutExData pfCadEntityPutExData;
	  pfCadEntityPutExData = (tfCadEntityPutExData)GetProcAddress( ghLibInst, "CadEntityPutExData" );
	  if (pfCadEntityPutExData){
		(*pfCadEntityPutExData)(hEnt, pData, nBytes);
	  }
	}


	//--------------
	int CADAPI CadEntityGetExDataSize (VHANDLE hEnt)
	{
	  tfCadEntityGetExDataSize pfCadEntityGetExDataSize;
	  pfCadEntityGetExDataSize = (tfCadEntityGetExDataSize)GetProcAddress( ghLibInst, "CadEntityGetExDataSize" );
	  if (pfCadEntityGetExDataSize){
		return (*pfCadEntityGetExDataSize)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityGetExData (VHANDLE hEnt, void* pData)
	{
	  tfCadEntityGetExData pfCadEntityGetExData;
	  pfCadEntityGetExData = (tfCadEntityGetExData)GetProcAddress( ghLibInst, "CadEntityGetExData" );
	  if (pfCadEntityGetExData){
		(*pfCadEntityGetExData)(hEnt, pData);
	  }
	}


	//--------------
	VHANDLE CADAPI CadEntityGetExDataPtr (VHANDLE hEnt)
	{
	  tfCadEntityGetExDataPtr pfCadEntityGetExDataPtr;
	  pfCadEntityGetExDataPtr = (tfCadEntityGetExDataPtr)GetProcAddress( ghLibInst, "CadEntityGetExDataPtr" );
	  if (pfCadEntityGetExDataPtr){
		return (*pfCadEntityGetExDataPtr)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityPutParkData (VHANDLE hEnt, LPCTSTR szPark, LPCTSTR szWay)
	{
	  tfCadEntityPutParkData pfCadEntityPutParkData;
	  pfCadEntityPutParkData = (tfCadEntityPutParkData)GetProcAddress( ghLibInst, "CadEntityPutParkData" );
	  if (pfCadEntityPutParkData){
		(*pfCadEntityPutParkData)(hEnt, szPark, szWay);
	  }
	}


	//--------------
	BOOL CADAPI CadEntityGetParkData (VHANDLE hEnt, TCHAR* szPark, TCHAR* szWay)
	{
	  tfCadEntityGetParkData pfCadEntityGetParkData;
	  pfCadEntityGetParkData = (tfCadEntityGetParkData)GetProcAddress( ghLibInst, "CadEntityGetParkData" );
	  if (pfCadEntityGetParkData){
		return (*pfCadEntityGetParkData)(hEnt, szPark, szWay);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityErase (VHANDLE hEnt, BOOL bErase)
	{
	  tfCadEntityErase pfCadEntityErase;
	  pfCadEntityErase = (tfCadEntityErase)GetProcAddress( ghLibInst, "CadEntityErase" );
	  if (pfCadEntityErase){
		(*pfCadEntityErase)(hEnt, bErase);
	  }
	}


	//--------------
	VHANDLE CADAPI CadEntityCopy (VHANDLE hEnt)
	{
	  tfCadEntityCopy pfCadEntityCopy;
	  pfCadEntityCopy = (tfCadEntityCopy)GetProcAddress( ghLibInst, "CadEntityCopy" );
	  if (pfCadEntityCopy){
		return (*pfCadEntityCopy)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityMove (VHANDLE hEnt, double dx, double dy, double dz)
	{
	  tfCadEntityMove pfCadEntityMove;
	  pfCadEntityMove = (tfCadEntityMove)GetProcAddress( ghLibInst, "CadEntityMove" );
	  if (pfCadEntityMove){
		(*pfCadEntityMove)(hEnt, dx, dy, dz);
	  }
	}


	//--------------
	void CADAPI CadEntityMoveGrip (VHANDLE hEnt, int iGrip, double dx, double dy, double dz)
	{
	  tfCadEntityMoveGrip pfCadEntityMoveGrip;
	  pfCadEntityMoveGrip = (tfCadEntityMoveGrip)GetProcAddress( ghLibInst, "CadEntityMoveGrip" );
	  if (pfCadEntityMoveGrip){
		(*pfCadEntityMoveGrip)(hEnt, iGrip, dx, dy, dz);
	  }
	}


	//--------------
	void CADAPI CadEntityScale (VHANDLE hEnt, double x0, double y0, double z0, double Scal)
	{
	  tfCadEntityScale pfCadEntityScale;
	  pfCadEntityScale = (tfCadEntityScale)GetProcAddress( ghLibInst, "CadEntityScale" );
	  if (pfCadEntityScale){
		(*pfCadEntityScale)(hEnt, x0, y0, z0, Scal);
	  }
	}


	//--------------
	void CADAPI CadEntityRotate (VHANDLE hEnt, double x0, double y0, double z0, double Angle)
	{
	  tfCadEntityRotate pfCadEntityRotate;
	  pfCadEntityRotate = (tfCadEntityRotate)GetProcAddress( ghLibInst, "CadEntityRotate" );
	  if (pfCadEntityRotate){
		(*pfCadEntityRotate)(hEnt, x0, y0, z0, Angle);
	  }
	}


	//--------------
	void CADAPI CadEntityMirror (VHANDLE hEnt, double x0, double y0, double z0, double x1, double y1, double z1)
	{
	  tfCadEntityMirror pfCadEntityMirror;
	  pfCadEntityMirror = (tfCadEntityMirror)GetProcAddress( ghLibInst, "CadEntityMirror" );
	  if (pfCadEntityMirror){
		(*pfCadEntityMirror)(hEnt, x0, y0, z0, x1, y1, z1);
	  }
	}


	//--------------
	BOOL CADAPI CadEntityExplode (VHANDLE hEnt, long* pnOutEnts, long* pFirstID)
	{
	  tfCadEntityExplode pfCadEntityExplode;
	  pfCadEntityExplode = (tfCadEntityExplode)GetProcAddress( ghLibInst, "CadEntityExplode" );
	  if (pfCadEntityExplode){
		return (*pfCadEntityExplode)(hEnt, pnOutEnts, pFirstID);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadAddEdge (VHANDLE hEnt)
	{
	  tfCadAddEdge pfCadAddEdge;
	  pfCadAddEdge = (tfCadAddEdge)GetProcAddress( ghLibInst, "CadAddEdge" );
	  if (pfCadAddEdge){
		return (*pfCadAddEdge)(hEnt);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadEntityTrim (VHANDLE hEnt, double x, double y)
	{
	  tfCadEntityTrim pfCadEntityTrim;
	  pfCadEntityTrim = (tfCadEntityTrim)GetProcAddress( ghLibInst, "CadEntityTrim" );
	  if (pfCadEntityTrim){
		return (*pfCadEntityTrim)(hEnt, x, y);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadEntityExtend (VHANDLE hEnt, double x, double y)
	{
	  tfCadEntityExtend pfCadEntityExtend;
	  pfCadEntityExtend = (tfCadEntityExtend)GetProcAddress( ghLibInst, "CadEntityExtend" );
	  if (pfCadEntityExtend){
		return (*pfCadEntityExtend)(hEnt, x, y);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadEntityToTop (VHANDLE hEnt)
	{
	  tfCadEntityToTop pfCadEntityToTop;
	  pfCadEntityToTop = (tfCadEntityToTop)GetProcAddress( ghLibInst, "CadEntityToTop" );
	  if (pfCadEntityToTop){
		(*pfCadEntityToTop)(hEnt);
	  }
	}


	//--------------
	void CADAPI CadEntityToBottom (VHANDLE hEnt)
	{
	  tfCadEntityToBottom pfCadEntityToBottom;
	  pfCadEntityToBottom = (tfCadEntityToBottom)GetProcAddress( ghLibInst, "CadEntityToBottom" );
	  if (pfCadEntityToBottom){
		(*pfCadEntityToBottom)(hEnt);
	  }
	}


	//--------------
	void CADAPI CadEntitySwap (VHANDLE hEnt1, VHANDLE hEnt2)
	{
	  tfCadEntitySwap pfCadEntitySwap;
	  pfCadEntitySwap = (tfCadEntitySwap)GetProcAddress( ghLibInst, "CadEntitySwap" );
	  if (pfCadEntitySwap){
		(*pfCadEntitySwap)(hEnt1, hEnt2);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddPoint (VDWG hDwg, double X, double Y, double Z)
	{
	  tfCadAddPoint pfCadAddPoint;
	  pfCadAddPoint = (tfCadAddPoint)GetProcAddress( ghLibInst, "CadAddPoint" );
	  if (pfCadAddPoint){
		return (*pfCadAddPoint)(hDwg, X, Y, Z);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadPointGetStyleID (VHANDLE hEnt)
	{
	  tfCadPointGetStyleID pfCadPointGetStyleID;
	  pfCadPointGetStyleID = (tfCadPointGetStyleID)GetProcAddress( ghLibInst, "CadPointGetStyleID" );
	  if (pfCadPointGetStyleID){
		return (*pfCadPointGetStyleID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPointPutStyleID (VHANDLE hEnt, IDOBJ Id)
	{
	  tfCadPointPutStyleID pfCadPointPutStyleID;
	  pfCadPointPutStyleID = (tfCadPointPutStyleID)GetProcAddress( ghLibInst, "CadPointPutStyleID" );
	  if (pfCadPointPutStyleID){
		(*pfCadPointPutStyleID)(hEnt, Id);
	  }
	}


	//--------------
	double CADAPI CadPointGetX (VHANDLE hEnt)
	{
	  tfCadPointGetX pfCadPointGetX;
	  pfCadPointGetX = (tfCadPointGetX)GetProcAddress( ghLibInst, "CadPointGetX" );
	  if (pfCadPointGetX){
		return (*pfCadPointGetX)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPointPutX (VHANDLE hEnt, double X)
	{
	  tfCadPointPutX pfCadPointPutX;
	  pfCadPointPutX = (tfCadPointPutX)GetProcAddress( ghLibInst, "CadPointPutX" );
	  if (pfCadPointPutX){
		(*pfCadPointPutX)(hEnt, X);
	  }
	}


	//--------------
	double CADAPI CadPointGetY (VHANDLE hEnt)
	{
	  tfCadPointGetY pfCadPointGetY;
	  pfCadPointGetY = (tfCadPointGetY)GetProcAddress( ghLibInst, "CadPointGetY" );
	  if (pfCadPointGetY){
		return (*pfCadPointGetY)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPointPutY (VHANDLE hEnt, double Y)
	{
	  tfCadPointPutY pfCadPointPutY;
	  pfCadPointPutY = (tfCadPointPutY)GetProcAddress( ghLibInst, "CadPointPutY" );
	  if (pfCadPointPutY){
		(*pfCadPointPutY)(hEnt, Y);
	  }
	}


	//--------------
	double CADAPI CadPointGetZ (VHANDLE hEnt)
	{
	  tfCadPointGetZ pfCadPointGetZ;
	  pfCadPointGetZ = (tfCadPointGetZ)GetProcAddress( ghLibInst, "CadPointGetZ" );
	  if (pfCadPointGetZ){
		return (*pfCadPointGetZ)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPointPutZ (VHANDLE hEnt, double Z)
	{
	  tfCadPointPutZ pfCadPointPutZ;
	  pfCadPointPutZ = (tfCadPointPutZ)GetProcAddress( ghLibInst, "CadPointPutZ" );
	  if (pfCadPointPutZ){
		(*pfCadPointPutZ)(hEnt, Z);
	  }
	}


	//--------------
	void CADAPI CadPointGetCoord (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadPointGetCoord pfCadPointGetCoord;
	  pfCadPointGetCoord = (tfCadPointGetCoord)GetProcAddress( ghLibInst, "CadPointGetCoord" );
	  if (pfCadPointGetCoord){
		(*pfCadPointGetCoord)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadPointPutCoord (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadPointPutCoord pfCadPointPutCoord;
	  pfCadPointPutCoord = (tfCadPointPutCoord)GetProcAddress( ghLibInst, "CadPointPutCoord" );
	  if (pfCadPointPutCoord){
		(*pfCadPointPutCoord)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	void CADAPI CadPointGetTextOffset (VHANDLE hEnt, double* pDX, double* pDY, double* pDZ)
	{
	  tfCadPointGetTextOffset pfCadPointGetTextOffset;
	  pfCadPointGetTextOffset = (tfCadPointGetTextOffset)GetProcAddress( ghLibInst, "CadPointGetTextOffset" );
	  if (pfCadPointGetTextOffset){
		(*pfCadPointGetTextOffset)(hEnt, pDX, pDY, pDZ);
	  }
	}


	//--------------
	void CADAPI CadPointPutTextOffset (VHANDLE hEnt, double DX, double DY, double DZ)
	{
	  tfCadPointPutTextOffset pfCadPointPutTextOffset;
	  pfCadPointPutTextOffset = (tfCadPointPutTextOffset)GetProcAddress( ghLibInst, "CadPointPutTextOffset" );
	  if (pfCadPointPutTextOffset){
		(*pfCadPointPutTextOffset)(hEnt, DX, DY, DZ);
	  }
	}


	//--------------
	double CADAPI CadPointGetTextX (VHANDLE hEnt)
	{
	  tfCadPointGetTextX pfCadPointGetTextX;
	  pfCadPointGetTextX = (tfCadPointGetTextX)GetProcAddress( ghLibInst, "CadPointGetTextX" );
	  if (pfCadPointGetTextX){
		return (*pfCadPointGetTextX)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPointPutTextX (VHANDLE hEnt, double X)
	{
	  tfCadPointPutTextX pfCadPointPutTextX;
	  pfCadPointPutTextX = (tfCadPointPutTextX)GetProcAddress( ghLibInst, "CadPointPutTextX" );
	  if (pfCadPointPutTextX){
		(*pfCadPointPutTextX)(hEnt, X);
	  }
	}


	//--------------
	double CADAPI CadPointGetTextY (VHANDLE hEnt)
	{
	  tfCadPointGetTextY pfCadPointGetTextY;
	  pfCadPointGetTextY = (tfCadPointGetTextY)GetProcAddress( ghLibInst, "CadPointGetTextY" );
	  if (pfCadPointGetTextY){
		return (*pfCadPointGetTextY)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPointPutTextY (VHANDLE hEnt, double Y)
	{
	  tfCadPointPutTextY pfCadPointPutTextY;
	  pfCadPointPutTextY = (tfCadPointPutTextY)GetProcAddress( ghLibInst, "CadPointPutTextY" );
	  if (pfCadPointPutTextY){
		(*pfCadPointPutTextY)(hEnt, Y);
	  }
	}


	//--------------
	void CADAPI CadPointGetText (VHANDLE hEnt, TCHAR* szText)
	{
	  tfCadPointGetText pfCadPointGetText;
	  pfCadPointGetText = (tfCadPointGetText)GetProcAddress( ghLibInst, "CadPointGetText" );
	  if (pfCadPointGetText){
		(*pfCadPointGetText)(hEnt, szText);
	  }
	}


	//--------------
	void CADAPI CadPointPutText (VHANDLE hEnt, LPCTSTR szText)
	{
	  tfCadPointPutText pfCadPointPutText;
	  pfCadPointPutText = (tfCadPointPutText)GetProcAddress( ghLibInst, "CadPointPutText" );
	  if (pfCadPointPutText){
		(*pfCadPointPutText)(hEnt, szText);
	  }
	}


	//--------------
	double CADAPI CadPointGetTextAngle (VHANDLE hEnt)
	{
	  tfCadPointGetTextAngle pfCadPointGetTextAngle;
	  pfCadPointGetTextAngle = (tfCadPointGetTextAngle)GetProcAddress( ghLibInst, "CadPointGetTextAngle" );
	  if (pfCadPointGetTextAngle){
		return (*pfCadPointGetTextAngle)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPointPutTextAngle (VHANDLE hEnt, double Angle)
	{
	  tfCadPointPutTextAngle pfCadPointPutTextAngle;
	  pfCadPointPutTextAngle = (tfCadPointPutTextAngle)GetProcAddress( ghLibInst, "CadPointPutTextAngle" );
	  if (pfCadPointPutTextAngle){
		(*pfCadPointPutTextAngle)(hEnt, Angle);
	  }
	}


	//--------------
	double CADAPI CadPointGetBlockAngle (VHANDLE hEnt)
	{
	  tfCadPointGetBlockAngle pfCadPointGetBlockAngle;
	  pfCadPointGetBlockAngle = (tfCadPointGetBlockAngle)GetProcAddress( ghLibInst, "CadPointGetBlockAngle" );
	  if (pfCadPointGetBlockAngle){
		return (*pfCadPointGetBlockAngle)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPointPutBlockAngle (VHANDLE hEnt, double Angle)
	{
	  tfCadPointPutBlockAngle pfCadPointPutBlockAngle;
	  pfCadPointPutBlockAngle = (tfCadPointPutBlockAngle)GetProcAddress( ghLibInst, "CadPointPutBlockAngle" );
	  if (pfCadPointPutBlockAngle){
		(*pfCadPointPutBlockAngle)(hEnt, Angle);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddLine (VDWG hDwg, double x1, double y1, double z1, double x2, double y2, double z2)
	{
	  tfCadAddLine pfCadAddLine;
	  pfCadAddLine = (tfCadAddLine)GetProcAddress( ghLibInst, "CadAddLine" );
	  if (pfCadAddLine){
		return (*pfCadAddLine)(hDwg, x1, y1, z1, x2, y2, z2);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddXLine (VDWG hDwg, double x, double y, double z, double dx, double dy, double dz)
	{
	  tfCadAddXLine pfCadAddXLine;
	  pfCadAddXLine = (tfCadAddXLine)GetProcAddress( ghLibInst, "CadAddXLine" );
	  if (pfCadAddXLine){
		return (*pfCadAddXLine)(hDwg, x, y, z, dx, dy, dz);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddRay (VDWG hDwg, double x, double y, double z, double dx, double dy, double dz)
	{
	  tfCadAddRay pfCadAddRay;
	  pfCadAddRay = (tfCadAddRay)GetProcAddress( ghLibInst, "CadAddRay" );
	  if (pfCadAddRay){
		return (*pfCadAddRay)(hDwg, x, y, z, dx, dy, dz);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadLineGetX1 (VHANDLE hEnt)
	{
	  tfCadLineGetX1 pfCadLineGetX1;
	  pfCadLineGetX1 = (tfCadLineGetX1)GetProcAddress( ghLibInst, "CadLineGetX1" );
	  if (pfCadLineGetX1){
		return (*pfCadLineGetX1)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLinePutX1 (VHANDLE hEnt, double X)
	{
	  tfCadLinePutX1 pfCadLinePutX1;
	  pfCadLinePutX1 = (tfCadLinePutX1)GetProcAddress( ghLibInst, "CadLinePutX1" );
	  if (pfCadLinePutX1){
		(*pfCadLinePutX1)(hEnt, X);
	  }
	}


	//--------------
	double CADAPI CadLineGetY1 (VHANDLE hEnt)
	{
	  tfCadLineGetY1 pfCadLineGetY1;
	  pfCadLineGetY1 = (tfCadLineGetY1)GetProcAddress( ghLibInst, "CadLineGetY1" );
	  if (pfCadLineGetY1){
		return (*pfCadLineGetY1)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLinePutY1 (VHANDLE hEnt, double Y)
	{
	  tfCadLinePutY1 pfCadLinePutY1;
	  pfCadLinePutY1 = (tfCadLinePutY1)GetProcAddress( ghLibInst, "CadLinePutY1" );
	  if (pfCadLinePutY1){
		(*pfCadLinePutY1)(hEnt, Y);
	  }
	}


	//--------------
	double CADAPI CadLineGetZ1 (VHANDLE hEnt)
	{
	  tfCadLineGetZ1 pfCadLineGetZ1;
	  pfCadLineGetZ1 = (tfCadLineGetZ1)GetProcAddress( ghLibInst, "CadLineGetZ1" );
	  if (pfCadLineGetZ1){
		return (*pfCadLineGetZ1)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLinePutZ1 (VHANDLE hEnt, double Z)
	{
	  tfCadLinePutZ1 pfCadLinePutZ1;
	  pfCadLinePutZ1 = (tfCadLinePutZ1)GetProcAddress( ghLibInst, "CadLinePutZ1" );
	  if (pfCadLinePutZ1){
		(*pfCadLinePutZ1)(hEnt, Z);
	  }
	}


	//--------------
	double CADAPI CadLineGetX2 (VHANDLE hEnt)
	{
	  tfCadLineGetX2 pfCadLineGetX2;
	  pfCadLineGetX2 = (tfCadLineGetX2)GetProcAddress( ghLibInst, "CadLineGetX2" );
	  if (pfCadLineGetX2){
		return (*pfCadLineGetX2)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLinePutX2 (VHANDLE hEnt, double X)
	{
	  tfCadLinePutX2 pfCadLinePutX2;
	  pfCadLinePutX2 = (tfCadLinePutX2)GetProcAddress( ghLibInst, "CadLinePutX2" );
	  if (pfCadLinePutX2){
		(*pfCadLinePutX2)(hEnt, X);
	  }
	}


	//--------------
	double CADAPI CadLineGetY2 (VHANDLE hEnt)
	{
	  tfCadLineGetY2 pfCadLineGetY2;
	  pfCadLineGetY2 = (tfCadLineGetY2)GetProcAddress( ghLibInst, "CadLineGetY2" );
	  if (pfCadLineGetY2){
		return (*pfCadLineGetY2)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLinePutY2 (VHANDLE hEnt, double Y)
	{
	  tfCadLinePutY2 pfCadLinePutY2;
	  pfCadLinePutY2 = (tfCadLinePutY2)GetProcAddress( ghLibInst, "CadLinePutY2" );
	  if (pfCadLinePutY2){
		(*pfCadLinePutY2)(hEnt, Y);
	  }
	}


	//--------------
	double CADAPI CadLineGetZ2 (VHANDLE hEnt)
	{
	  tfCadLineGetZ2 pfCadLineGetZ2;
	  pfCadLineGetZ2 = (tfCadLineGetZ2)GetProcAddress( ghLibInst, "CadLineGetZ2" );
	  if (pfCadLineGetZ2){
		return (*pfCadLineGetZ2)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLinePutZ2 (VHANDLE hEnt, double Z)
	{
	  tfCadLinePutZ2 pfCadLinePutZ2;
	  pfCadLinePutZ2 = (tfCadLinePutZ2)GetProcAddress( ghLibInst, "CadLinePutZ2" );
	  if (pfCadLinePutZ2){
		(*pfCadLinePutZ2)(hEnt, Z);
	  }
	}


	//--------------
	void CADAPI CadLineGetPoint1 (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadLineGetPoint1 pfCadLineGetPoint1;
	  pfCadLineGetPoint1 = (tfCadLineGetPoint1)GetProcAddress( ghLibInst, "CadLineGetPoint1" );
	  if (pfCadLineGetPoint1){
		(*pfCadLineGetPoint1)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadLinePutPoint1 (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadLinePutPoint1 pfCadLinePutPoint1;
	  pfCadLinePutPoint1 = (tfCadLinePutPoint1)GetProcAddress( ghLibInst, "CadLinePutPoint1" );
	  if (pfCadLinePutPoint1){
		(*pfCadLinePutPoint1)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	void CADAPI CadLineGetPoint2 (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadLineGetPoint2 pfCadLineGetPoint2;
	  pfCadLineGetPoint2 = (tfCadLineGetPoint2)GetProcAddress( ghLibInst, "CadLineGetPoint2" );
	  if (pfCadLineGetPoint2){
		(*pfCadLineGetPoint2)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadLinePutPoint2 (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadLinePutPoint2 pfCadLinePutPoint2;
	  pfCadLinePutPoint2 = (tfCadLinePutPoint2)GetProcAddress( ghLibInst, "CadLinePutPoint2" );
	  if (pfCadLinePutPoint2){
		(*pfCadLinePutPoint2)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	BOOL CADAPI CadLineIsX (VHANDLE hEnt)
	{
	  tfCadLineIsX pfCadLineIsX;
	  pfCadLineIsX = (tfCadLineIsX)GetProcAddress( ghLibInst, "CadLineIsX" );
	  if (pfCadLineIsX){
		return (*pfCadLineIsX)(hEnt);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadLineIsRay (VHANDLE hEnt)
	{
	  tfCadLineIsRay pfCadLineIsRay;
	  pfCadLineIsRay = (tfCadLineIsRay)GetProcAddress( ghLibInst, "CadLineIsRay" );
	  if (pfCadLineIsRay){
		return (*pfCadLineIsRay)(hEnt);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddCircle (VDWG hDwg, double X, double Y, double Z, double Radius)
	{
	  tfCadAddCircle pfCadAddCircle;
	  pfCadAddCircle = (tfCadAddCircle)GetProcAddress( ghLibInst, "CadAddCircle" );
	  if (pfCadAddCircle){
		return (*pfCadAddCircle)(hDwg, X, Y, Z, Radius);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddCircle3P (VDWG hDwg, double X1, double Y1, double Z, double X2, double Y2, double X3, double Y3)
	{
	  tfCadAddCircle3P pfCadAddCircle3P;
	  pfCadAddCircle3P = (tfCadAddCircle3P)GetProcAddress( ghLibInst, "CadAddCircle3P" );
	  if (pfCadAddCircle3P){
		return (*pfCadAddCircle3P)(hDwg, X1, Y1, Z, X2, Y2, X3, Y3);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddArc (VDWG hDwg, double X, double Y, double Z, double Radius, double StartAngle, double ArcAngle)
	{
	  tfCadAddArc pfCadAddArc;
	  pfCadAddArc = (tfCadAddArc)GetProcAddress( ghLibInst, "CadAddArc" );
	  if (pfCadAddArc){
		return (*pfCadAddArc)(hDwg, X, Y, Z, Radius, StartAngle, ArcAngle);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddArc3P (VDWG hDwg, double X1, double Y1, double Z, double X2, double Y2, double X3, double Y3)
	{
	  tfCadAddArc3P pfCadAddArc3P;
	  pfCadAddArc3P = (tfCadAddArc3P)GetProcAddress( ghLibInst, "CadAddArc3P" );
	  if (pfCadAddArc3P){
		return (*pfCadAddArc3P)(hDwg, X1, Y1, Z, X2, Y2, X3, Y3);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddArcCSE (VDWG hDwg, double Xc, double Yc, double Z, double Xs, double Ys, double Xe, double Ye, BOOL bCCW)
	{
	  tfCadAddArcCSE pfCadAddArcCSE;
	  pfCadAddArcCSE = (tfCadAddArcCSE)GetProcAddress( ghLibInst, "CadAddArcCSE" );
	  if (pfCadAddArcCSE){
		return (*pfCadAddArcCSE)(hDwg, Xc, Yc, Z, Xs, Ys, Xe, Ye, bCCW);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddArcSED (VDWG hDwg, double Xs, double Ys, double Z, double Xe, double Ye, double DirAngle)
	{
	  tfCadAddArcSED pfCadAddArcSED;
	  pfCadAddArcSED = (tfCadAddArcSED)GetProcAddress( ghLibInst, "CadAddArcSED" );
	  if (pfCadAddArcSED){
		return (*pfCadAddArcSED)(hDwg, Xs, Ys, Z, Xe, Ye, DirAngle);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddArcContinue (VDWG hDwg, VHANDLE hEnt, double Xe, double Ye, double Z)
	{
	  tfCadAddArcContinue pfCadAddArcContinue;
	  pfCadAddArcContinue = (tfCadAddArcContinue)GetProcAddress( ghLibInst, "CadAddArcContinue" );
	  if (pfCadAddArcContinue){
		return (*pfCadAddArcContinue)(hDwg, hEnt, Xe, Ye, Z);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddEllipse (VDWG hDwg, double X, double Y, double Z, double RadH, double RadV, double RotAngle)
	{
	  tfCadAddEllipse pfCadAddEllipse;
	  pfCadAddEllipse = (tfCadAddEllipse)GetProcAddress( ghLibInst, "CadAddEllipse" );
	  if (pfCadAddEllipse){
		return (*pfCadAddEllipse)(hDwg, X, Y, Z, RadH, RadV, RotAngle);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadArcGetType (VHANDLE hEnt)
	{
	  tfCadArcGetType pfCadArcGetType;
	  pfCadArcGetType = (tfCadArcGetType)GetProcAddress( ghLibInst, "CadArcGetType" );
	  if (pfCadArcGetType){
		return (*pfCadArcGetType)(hEnt);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadArcGetCenterX (VHANDLE hEnt)
	{
	  tfCadArcGetCenterX pfCadArcGetCenterX;
	  pfCadArcGetCenterX = (tfCadArcGetCenterX)GetProcAddress( ghLibInst, "CadArcGetCenterX" );
	  if (pfCadArcGetCenterX){
		return (*pfCadArcGetCenterX)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcPutCenterX (VHANDLE hEnt, double X)
	{
	  tfCadArcPutCenterX pfCadArcPutCenterX;
	  pfCadArcPutCenterX = (tfCadArcPutCenterX)GetProcAddress( ghLibInst, "CadArcPutCenterX" );
	  if (pfCadArcPutCenterX){
		(*pfCadArcPutCenterX)(hEnt, X);
	  }
	}


	//--------------
	double CADAPI CadArcGetCenterY (VHANDLE hEnt)
	{
	  tfCadArcGetCenterY pfCadArcGetCenterY;
	  pfCadArcGetCenterY = (tfCadArcGetCenterY)GetProcAddress( ghLibInst, "CadArcGetCenterY" );
	  if (pfCadArcGetCenterY){
		return (*pfCadArcGetCenterY)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcPutCenterY (VHANDLE hEnt, double Y)
	{
	  tfCadArcPutCenterY pfCadArcPutCenterY;
	  pfCadArcPutCenterY = (tfCadArcPutCenterY)GetProcAddress( ghLibInst, "CadArcPutCenterY" );
	  if (pfCadArcPutCenterY){
		(*pfCadArcPutCenterY)(hEnt, Y);
	  }
	}


	//--------------
	double CADAPI CadArcGetCenterZ (VHANDLE hEnt)
	{
	  tfCadArcGetCenterZ pfCadArcGetCenterZ;
	  pfCadArcGetCenterZ = (tfCadArcGetCenterZ)GetProcAddress( ghLibInst, "CadArcGetCenterZ" );
	  if (pfCadArcGetCenterZ){
		return (*pfCadArcGetCenterZ)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcPutCenterZ (VHANDLE hEnt, double Z)
	{
	  tfCadArcPutCenterZ pfCadArcPutCenterZ;
	  pfCadArcPutCenterZ = (tfCadArcPutCenterZ)GetProcAddress( ghLibInst, "CadArcPutCenterZ" );
	  if (pfCadArcPutCenterZ){
		(*pfCadArcPutCenterZ)(hEnt, Z);
	  }
	}


	//--------------
	void CADAPI CadArcGetCenter (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadArcGetCenter pfCadArcGetCenter;
	  pfCadArcGetCenter = (tfCadArcGetCenter)GetProcAddress( ghLibInst, "CadArcGetCenter" );
	  if (pfCadArcGetCenter){
		(*pfCadArcGetCenter)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadArcPutCenter (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadArcPutCenter pfCadArcPutCenter;
	  pfCadArcPutCenter = (tfCadArcPutCenter)GetProcAddress( ghLibInst, "CadArcPutCenter" );
	  if (pfCadArcPutCenter){
		(*pfCadArcPutCenter)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	double CADAPI CadArcGetRadius (VHANDLE hEnt)
	{
	  tfCadArcGetRadius pfCadArcGetRadius;
	  pfCadArcGetRadius = (tfCadArcGetRadius)GetProcAddress( ghLibInst, "CadArcGetRadius" );
	  if (pfCadArcGetRadius){
		return (*pfCadArcGetRadius)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcPutRadius (VHANDLE hEnt, double R)
	{
	  tfCadArcPutRadius pfCadArcPutRadius;
	  pfCadArcPutRadius = (tfCadArcPutRadius)GetProcAddress( ghLibInst, "CadArcPutRadius" );
	  if (pfCadArcPutRadius){
		(*pfCadArcPutRadius)(hEnt, R);
	  }
	}


	//--------------
	double CADAPI CadArcGetRadHor (VHANDLE hEnt)
	{
	  tfCadArcGetRadHor pfCadArcGetRadHor;
	  pfCadArcGetRadHor = (tfCadArcGetRadHor)GetProcAddress( ghLibInst, "CadArcGetRadHor" );
	  if (pfCadArcGetRadHor){
		return (*pfCadArcGetRadHor)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcPutRadHor (VHANDLE hEnt, double R)
	{
	  tfCadArcPutRadHor pfCadArcPutRadHor;
	  pfCadArcPutRadHor = (tfCadArcPutRadHor)GetProcAddress( ghLibInst, "CadArcPutRadHor" );
	  if (pfCadArcPutRadHor){
		(*pfCadArcPutRadHor)(hEnt, R);
	  }
	}


	//--------------
	double CADAPI CadArcGetRadVer (VHANDLE hEnt)
	{
	  tfCadArcGetRadVer pfCadArcGetRadVer;
	  pfCadArcGetRadVer = (tfCadArcGetRadVer)GetProcAddress( ghLibInst, "CadArcGetRadVer" );
	  if (pfCadArcGetRadVer){
		return (*pfCadArcGetRadVer)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcPutRadVer (VHANDLE hEnt, double R)
	{
	  tfCadArcPutRadVer pfCadArcPutRadVer;
	  pfCadArcPutRadVer = (tfCadArcPutRadVer)GetProcAddress( ghLibInst, "CadArcPutRadVer" );
	  if (pfCadArcPutRadVer){
		(*pfCadArcPutRadVer)(hEnt, R);
	  }
	}


	//--------------
	double CADAPI CadArcGetStartAngle (VHANDLE hEnt)
	{
	  tfCadArcGetStartAngle pfCadArcGetStartAngle;
	  pfCadArcGetStartAngle = (tfCadArcGetStartAngle)GetProcAddress( ghLibInst, "CadArcGetStartAngle" );
	  if (pfCadArcGetStartAngle){
		return (*pfCadArcGetStartAngle)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcPutStartAngle (VHANDLE hEnt, double Ang)
	{
	  tfCadArcPutStartAngle pfCadArcPutStartAngle;
	  pfCadArcPutStartAngle = (tfCadArcPutStartAngle)GetProcAddress( ghLibInst, "CadArcPutStartAngle" );
	  if (pfCadArcPutStartAngle){
		(*pfCadArcPutStartAngle)(hEnt, Ang);
	  }
	}


	//--------------
	double CADAPI CadArcGetAngle (VHANDLE hEnt)
	{
	  tfCadArcGetAngle pfCadArcGetAngle;
	  pfCadArcGetAngle = (tfCadArcGetAngle)GetProcAddress( ghLibInst, "CadArcGetAngle" );
	  if (pfCadArcGetAngle){
		return (*pfCadArcGetAngle)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcPutAngle (VHANDLE hEnt, double Ang)
	{
	  tfCadArcPutAngle pfCadArcPutAngle;
	  pfCadArcPutAngle = (tfCadArcPutAngle)GetProcAddress( ghLibInst, "CadArcPutAngle" );
	  if (pfCadArcPutAngle){
		(*pfCadArcPutAngle)(hEnt, Ang);
	  }
	}


	//--------------
	double CADAPI CadArcGetRotAngle (VHANDLE hEnt)
	{
	  tfCadArcGetRotAngle pfCadArcGetRotAngle;
	  pfCadArcGetRotAngle = (tfCadArcGetRotAngle)GetProcAddress( ghLibInst, "CadArcGetRotAngle" );
	  if (pfCadArcGetRotAngle){
		return (*pfCadArcGetRotAngle)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcPutRotAngle (VHANDLE hEnt, double Ang)
	{
	  tfCadArcPutRotAngle pfCadArcPutRotAngle;
	  pfCadArcPutRotAngle = (tfCadArcPutRotAngle)GetProcAddress( ghLibInst, "CadArcPutRotAngle" );
	  if (pfCadArcPutRotAngle){
		(*pfCadArcPutRotAngle)(hEnt, Ang);
	  }
	}


	//--------------
	BOOL CADAPI CadArcGetSector (VHANDLE hEnt)
	{
	  tfCadArcGetSector pfCadArcGetSector;
	  pfCadArcGetSector = (tfCadArcGetSector)GetProcAddress( ghLibInst, "CadArcGetSector" );
	  if (pfCadArcGetSector){
		return (*pfCadArcGetSector)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcPutSector (VHANDLE hEnt, BOOL bSector)
	{
	  tfCadArcPutSector pfCadArcPutSector;
	  pfCadArcPutSector = (tfCadArcPutSector)GetProcAddress( ghLibInst, "CadArcPutSector" );
	  if (pfCadArcPutSector){
		(*pfCadArcPutSector)(hEnt, bSector);
	  }
	}


	//--------------
	void CADAPI CadArcGetStartPt (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadArcGetStartPt pfCadArcGetStartPt;
	  pfCadArcGetStartPt = (tfCadArcGetStartPt)GetProcAddress( ghLibInst, "CadArcGetStartPt" );
	  if (pfCadArcGetStartPt){
		(*pfCadArcGetStartPt)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	BOOL CADAPI CadArcPutStartPt (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadArcPutStartPt pfCadArcPutStartPt;
	  pfCadArcPutStartPt = (tfCadArcPutStartPt)GetProcAddress( ghLibInst, "CadArcPutStartPt" );
	  if (pfCadArcPutStartPt){
		return (*pfCadArcPutStartPt)(hEnt, X, Y, Z);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcGetEndPt (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadArcGetEndPt pfCadArcGetEndPt;
	  pfCadArcGetEndPt = (tfCadArcGetEndPt)GetProcAddress( ghLibInst, "CadArcGetEndPt" );
	  if (pfCadArcGetEndPt){
		(*pfCadArcGetEndPt)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	BOOL CADAPI CadArcPutEndPt (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadArcPutEndPt pfCadArcPutEndPt;
	  pfCadArcPutEndPt = (tfCadArcPutEndPt)GetProcAddress( ghLibInst, "CadArcPutEndPt" );
	  if (pfCadArcPutEndPt){
		return (*pfCadArcPutEndPt)(hEnt, X, Y, Z);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcGetMidPt (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadArcGetMidPt pfCadArcGetMidPt;
	  pfCadArcGetMidPt = (tfCadArcGetMidPt)GetProcAddress( ghLibInst, "CadArcGetMidPt" );
	  if (pfCadArcGetMidPt){
		(*pfCadArcGetMidPt)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	BOOL CADAPI CadArcPutMidPt (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadArcPutMidPt pfCadArcPutMidPt;
	  pfCadArcPutMidPt = (tfCadArcPutMidPt)GetProcAddress( ghLibInst, "CadArcPutMidPt" );
	  if (pfCadArcPutMidPt){
		return (*pfCadArcPutMidPt)(hEnt, X, Y, Z);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcGet3Pt (VHANDLE hEnt, double* pXsta, double* pYsta, double* pZ, double* pXmid, double* pYmid, double* pXend, double* pYend)
	{
	  tfCadArcGet3Pt pfCadArcGet3Pt;
	  pfCadArcGet3Pt = (tfCadArcGet3Pt)GetProcAddress( ghLibInst, "CadArcGet3Pt" );
	  if (pfCadArcGet3Pt){
		(*pfCadArcGet3Pt)(hEnt, pXsta, pYsta, pZ, pXmid, pYmid, pXend, pYend);
	  }
	}


	//--------------
	BOOL CADAPI CadArcPut3Pt (VHANDLE hEnt, double Xsta, double Ysta, double Z, double Xmid, double Ymid, double Xe, double Ye)
	{
	  tfCadArcPut3Pt pfCadArcPut3Pt;
	  pfCadArcPut3Pt = (tfCadArcPut3Pt)GetProcAddress( ghLibInst, "CadArcPut3Pt" );
	  if (pfCadArcPut3Pt){
		return (*pfCadArcPut3Pt)(hEnt, Xsta, Ysta, Z, Xmid, Ymid, Xe, Ye);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadArcDivide (VHANDLE hEnt, int nPoints, double* X, double* Y)
	{
	  tfCadArcDivide pfCadArcDivide;
	  pfCadArcDivide = (tfCadArcDivide)GetProcAddress( ghLibInst, "CadArcDivide" );
	  if (pfCadArcDivide){
		(*pfCadArcDivide)(hEnt, nPoints, X, Y);
	  }
	}


	//--------------
	void CADAPI CadClearVertices ()
	{
	  tfCadClearVertices pfCadClearVertices;
	  pfCadClearVertices = (tfCadClearVertices)GetProcAddress( ghLibInst, "CadClearVertices" );
	  if (pfCadClearVertices){
		(*pfCadClearVertices)();
	  }
	}


	//--------------
	void CADAPI CadAddVertex (double X, double Y, double Z)
	{
	  tfCadAddVertex pfCadAddVertex;
	  pfCadAddVertex = (tfCadAddVertex)GetProcAddress( ghLibInst, "CadAddVertex" );
	  if (pfCadAddVertex){
		(*pfCadAddVertex)(X, Y, Z);
	  }
	}


	//--------------
	void CADAPI CadAddVertex2 (double X, double Y, double Z, double Prm, double StartW, double EndW)
	{
	  tfCadAddVertex2 pfCadAddVertex2;
	  pfCadAddVertex2 = (tfCadAddVertex2)GetProcAddress( ghLibInst, "CadAddVertex2" );
	  if (pfCadAddVertex2){
		(*pfCadAddVertex2)(X, Y, Z, Prm, StartW, EndW);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddPolyline (VDWG hDwg, int FitType, BOOL bClosed)
	{
	  tfCadAddPolyline pfCadAddPolyline;
	  pfCadAddPolyline = (tfCadAddPolyline)GetProcAddress( ghLibInst, "CadAddPolyline" );
	  if (pfCadAddPolyline){
		return (*pfCadAddPolyline)(hDwg, FitType, bClosed);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddPolylineW (VDWG hDwg, int FitType, BOOL bClosed, double Width)
	{
	  tfCadAddPolylineW pfCadAddPolylineW;
	  pfCadAddPolylineW = (tfCadAddPolylineW)GetProcAddress( ghLibInst, "CadAddPolylineW" );
	  if (pfCadAddPolylineW){
		return (*pfCadAddPolylineW)(hDwg, FitType, bClosed, Width);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddPolygon (VDWG hDwg, int Color, BOOL bBorder)
	{
	  tfCadAddPolygon pfCadAddPolygon;
	  pfCadAddPolygon = (tfCadAddPolygon)GetProcAddress( ghLibInst, "CadAddPolygon" );
	  if (pfCadAddPolygon){
		return (*pfCadAddPolygon)(hDwg, Color, bBorder);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddBoundPolygon (VDWG hDwg, double X, double Y, double Z)
	{
	  tfCadAddBoundPolygon pfCadAddBoundPolygon;
	  pfCadAddBoundPolygon = (tfCadAddBoundPolygon)GetProcAddress( ghLibInst, "CadAddBoundPolygon" );
	  if (pfCadAddBoundPolygon){
		return (*pfCadAddBoundPolygon)(hDwg, X, Y, Z);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddBoundary (VDWG hDwg, double X, double Y, double Z)
	{
	  tfCadAddBoundary pfCadAddBoundary;
	  pfCadAddBoundary = (tfCadAddBoundary)GetProcAddress( ghLibInst, "CadAddBoundary" );
	  if (pfCadAddBoundary){
		return (*pfCadAddBoundary)(hDwg, X, Y, Z);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPlineInsertVer (VHANDLE hEnt, UINT iVer)
	{
	  tfCadPlineInsertVer pfCadPlineInsertVer;
	  pfCadPlineInsertVer = (tfCadPlineInsertVer)GetProcAddress( ghLibInst, "CadPlineInsertVer" );
	  if (pfCadPlineInsertVer){
		return (*pfCadPlineInsertVer)(hEnt, iVer);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPlineDeleteVer (VHANDLE hEnt, UINT iVer)
	{
	  tfCadPlineDeleteVer pfCadPlineDeleteVer;
	  pfCadPlineDeleteVer = (tfCadPlineDeleteVer)GetProcAddress( ghLibInst, "CadPlineDeleteVer" );
	  if (pfCadPlineDeleteVer){
		return (*pfCadPlineDeleteVer)(hEnt, iVer);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadPlineGetNumVers (VHANDLE hEnt)
	{
	  tfCadPlineGetNumVers pfCadPlineGetNumVers;
	  pfCadPlineGetNumVers = (tfCadPlineGetNumVers)GetProcAddress( ghLibInst, "CadPlineGetNumVers" );
	  if (pfCadPlineGetNumVers){
		return (*pfCadPlineGetNumVers)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPlinePutNumVers (VHANDLE hEnt, UINT nVers)
	{
	  tfCadPlinePutNumVers pfCadPlinePutNumVers;
	  pfCadPlinePutNumVers = (tfCadPlinePutNumVers)GetProcAddress( ghLibInst, "CadPlinePutNumVers" );
	  if (pfCadPlinePutNumVers){
		(*pfCadPlinePutNumVers)(hEnt, nVers);
	  }
	}


	//--------------
	double CADAPI CadPlineGetX (VHANDLE hEnt, UINT iVer)
	{
	  tfCadPlineGetX pfCadPlineGetX;
	  pfCadPlineGetX = (tfCadPlineGetX)GetProcAddress( ghLibInst, "CadPlineGetX" );
	  if (pfCadPlineGetX){
		return (*pfCadPlineGetX)(hEnt, iVer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPlinePutX (VHANDLE hEnt, UINT iVer, double X)
	{
	  tfCadPlinePutX pfCadPlinePutX;
	  pfCadPlinePutX = (tfCadPlinePutX)GetProcAddress( ghLibInst, "CadPlinePutX" );
	  if (pfCadPlinePutX){
		(*pfCadPlinePutX)(hEnt, iVer, X);
	  }
	}


	//--------------
	double CADAPI CadPlineGetY (VHANDLE hEnt, UINT iVer)
	{
	  tfCadPlineGetY pfCadPlineGetY;
	  pfCadPlineGetY = (tfCadPlineGetY)GetProcAddress( ghLibInst, "CadPlineGetY" );
	  if (pfCadPlineGetY){
		return (*pfCadPlineGetY)(hEnt, iVer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPlinePutY (VHANDLE hEnt, UINT iVer, double Y)
	{
	  tfCadPlinePutY pfCadPlinePutY;
	  pfCadPlinePutY = (tfCadPlinePutY)GetProcAddress( ghLibInst, "CadPlinePutY" );
	  if (pfCadPlinePutY){
		(*pfCadPlinePutY)(hEnt, iVer, Y);
	  }
	}


	//--------------
	double CADAPI CadPlineGetZ (VHANDLE hEnt, UINT iVer)
	{
	  tfCadPlineGetZ pfCadPlineGetZ;
	  pfCadPlineGetZ = (tfCadPlineGetZ)GetProcAddress( ghLibInst, "CadPlineGetZ" );
	  if (pfCadPlineGetZ){
		return (*pfCadPlineGetZ)(hEnt, iVer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPlinePutZ (VHANDLE hEnt, UINT iVer, double Z)
	{
	  tfCadPlinePutZ pfCadPlinePutZ;
	  pfCadPlinePutZ = (tfCadPlinePutZ)GetProcAddress( ghLibInst, "CadPlinePutZ" );
	  if (pfCadPlinePutZ){
		(*pfCadPlinePutZ)(hEnt, iVer, Z);
	  }
	}


	//--------------
	void CADAPI CadPlineGetVer (VHANDLE hEnt, UINT iVer, double* pX, double* pY, double* pZ)
	{
	  tfCadPlineGetVer pfCadPlineGetVer;
	  pfCadPlineGetVer = (tfCadPlineGetVer)GetProcAddress( ghLibInst, "CadPlineGetVer" );
	  if (pfCadPlineGetVer){
		(*pfCadPlineGetVer)(hEnt, iVer, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadPlinePutVer (VHANDLE hEnt, UINT iVer, double X, double Y, double Z)
	{
	  tfCadPlinePutVer pfCadPlinePutVer;
	  pfCadPlinePutVer = (tfCadPlinePutVer)GetProcAddress( ghLibInst, "CadPlinePutVer" );
	  if (pfCadPlinePutVer){
		(*pfCadPlinePutVer)(hEnt, iVer, X, Y, Z);
	  }
	}


	//--------------
	double CADAPI CadPlineGetPrm (VHANDLE hEnt, UINT iVer)
	{
	  tfCadPlineGetPrm pfCadPlineGetPrm;
	  pfCadPlineGetPrm = (tfCadPlineGetPrm)GetProcAddress( ghLibInst, "CadPlineGetPrm" );
	  if (pfCadPlineGetPrm){
		return (*pfCadPlineGetPrm)(hEnt, iVer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPlinePutPrm (VHANDLE hEnt, UINT iVer, double Prm)
	{
	  tfCadPlinePutPrm pfCadPlinePutPrm;
	  pfCadPlinePutPrm = (tfCadPlinePutPrm)GetProcAddress( ghLibInst, "CadPlinePutPrm" );
	  if (pfCadPlinePutPrm){
		(*pfCadPlinePutPrm)(hEnt, iVer, Prm);
	  }
	}


	//--------------
	double CADAPI CadPlineGetStartW (VHANDLE hEnt, UINT iVer)
	{
	  tfCadPlineGetStartW pfCadPlineGetStartW;
	  pfCadPlineGetStartW = (tfCadPlineGetStartW)GetProcAddress( ghLibInst, "CadPlineGetStartW" );
	  if (pfCadPlineGetStartW){
		return (*pfCadPlineGetStartW)(hEnt, iVer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPlinePutStartW (VHANDLE hEnt, UINT iVer, double Width)
	{
	  tfCadPlinePutStartW pfCadPlinePutStartW;
	  pfCadPlinePutStartW = (tfCadPlinePutStartW)GetProcAddress( ghLibInst, "CadPlinePutStartW" );
	  if (pfCadPlinePutStartW){
		(*pfCadPlinePutStartW)(hEnt, iVer, Width);
	  }
	}


	//--------------
	double CADAPI CadPlineGetEndW (VHANDLE hEnt, UINT iVer)
	{
	  tfCadPlineGetEndW pfCadPlineGetEndW;
	  pfCadPlineGetEndW = (tfCadPlineGetEndW)GetProcAddress( ghLibInst, "CadPlineGetEndW" );
	  if (pfCadPlineGetEndW){
		return (*pfCadPlineGetEndW)(hEnt, iVer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPlinePutEndW (VHANDLE hEnt, UINT iVer, double Width)
	{
	  tfCadPlinePutEndW pfCadPlinePutEndW;
	  pfCadPlinePutEndW = (tfCadPlinePutEndW)GetProcAddress( ghLibInst, "CadPlinePutEndW" );
	  if (pfCadPlinePutEndW){
		(*pfCadPlinePutEndW)(hEnt, iVer, Width);
	  }
	}


	//--------------
	void CADAPI CadPlinePutZ1 (VHANDLE hEnt, double Z)
	{
	  tfCadPlinePutZ1 pfCadPlinePutZ1;
	  pfCadPlinePutZ1 = (tfCadPlinePutZ1)GetProcAddress( ghLibInst, "CadPlinePutZ1" );
	  if (pfCadPlinePutZ1){
		(*pfCadPlinePutZ1)(hEnt, Z);
	  }
	}


	//--------------
	double CADAPI CadPlineGetRadius (VHANDLE hEnt)
	{
	  tfCadPlineGetRadius pfCadPlineGetRadius;
	  pfCadPlineGetRadius = (tfCadPlineGetRadius)GetProcAddress( ghLibInst, "CadPlineGetRadius" );
	  if (pfCadPlineGetRadius){
		return (*pfCadPlineGetRadius)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPlinePutRadius (VHANDLE hEnt, double Rad)
	{
	  tfCadPlinePutRadius pfCadPlinePutRadius;
	  pfCadPlinePutRadius = (tfCadPlinePutRadius)GetProcAddress( ghLibInst, "CadPlinePutRadius" );
	  if (pfCadPlinePutRadius){
		(*pfCadPlinePutRadius)(hEnt, Rad);
	  }
	}


	//--------------
	double CADAPI CadPlineGetWidth (VHANDLE hEnt)
	{
	  tfCadPlineGetWidth pfCadPlineGetWidth;
	  pfCadPlineGetWidth = (tfCadPlineGetWidth)GetProcAddress( ghLibInst, "CadPlineGetWidth" );
	  if (pfCadPlineGetWidth){
		return (*pfCadPlineGetWidth)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPlinePutWidth (VHANDLE hEnt, double Width)
	{
	  tfCadPlinePutWidth pfCadPlinePutWidth;
	  pfCadPlinePutWidth = (tfCadPlinePutWidth)GetProcAddress( ghLibInst, "CadPlinePutWidth" );
	  if (pfCadPlinePutWidth){
		(*pfCadPlinePutWidth)(hEnt, Width);
	  }
	}


	//--------------
	BOOL CADAPI CadPlineGetClosed (VHANDLE hEnt)
	{
	  tfCadPlineGetClosed pfCadPlineGetClosed;
	  pfCadPlineGetClosed = (tfCadPlineGetClosed)GetProcAddress( ghLibInst, "CadPlineGetClosed" );
	  if (pfCadPlineGetClosed){
		return (*pfCadPlineGetClosed)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPlinePutClosed (VHANDLE hEnt, BOOL bClosed)
	{
	  tfCadPlinePutClosed pfCadPlinePutClosed;
	  pfCadPlinePutClosed = (tfCadPlinePutClosed)GetProcAddress( ghLibInst, "CadPlinePutClosed" );
	  if (pfCadPlinePutClosed){
		(*pfCadPlinePutClosed)(hEnt, bClosed);
	  }
	}


	//--------------
	int CADAPI CadPlineGetFit (VHANDLE hEnt)
	{
	  tfCadPlineGetFit pfCadPlineGetFit;
	  pfCadPlineGetFit = (tfCadPlineGetFit)GetProcAddress( ghLibInst, "CadPlineGetFit" );
	  if (pfCadPlineGetFit){
		return (*pfCadPlineGetFit)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPlinePutFit (VHANDLE hEnt, int FitType)
	{
	  tfCadPlinePutFit pfCadPlinePutFit;
	  pfCadPlinePutFit = (tfCadPlinePutFit)GetProcAddress( ghLibInst, "CadPlinePutFit" );
	  if (pfCadPlinePutFit){
		(*pfCadPlinePutFit)(hEnt, FitType);
	  }
	}


	//--------------
	void CADAPI CadPlineGetStartTan (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadPlineGetStartTan pfCadPlineGetStartTan;
	  pfCadPlineGetStartTan = (tfCadPlineGetStartTan)GetProcAddress( ghLibInst, "CadPlineGetStartTan" );
	  if (pfCadPlineGetStartTan){
		(*pfCadPlineGetStartTan)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadPlinePutStartTan (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadPlinePutStartTan pfCadPlinePutStartTan;
	  pfCadPlinePutStartTan = (tfCadPlinePutStartTan)GetProcAddress( ghLibInst, "CadPlinePutStartTan" );
	  if (pfCadPlinePutStartTan){
		(*pfCadPlinePutStartTan)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	void CADAPI CadPlineGetEndTan (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadPlineGetEndTan pfCadPlineGetEndTan;
	  pfCadPlineGetEndTan = (tfCadPlineGetEndTan)GetProcAddress( ghLibInst, "CadPlineGetEndTan" );
	  if (pfCadPlineGetEndTan){
		(*pfCadPlineGetEndTan)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadPlinePutEndTan (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadPlinePutEndTan pfCadPlinePutEndTan;
	  pfCadPlinePutEndTan = (tfCadPlinePutEndTan)GetProcAddress( ghLibInst, "CadPlinePutEndTan" );
	  if (pfCadPlinePutEndTan){
		(*pfCadPlinePutEndTan)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	double CADAPI CadPlineGetLength (VHANDLE hEnt)
	{
	  tfCadPlineGetLength pfCadPlineGetLength;
	  pfCadPlineGetLength = (tfCadPlineGetLength)GetProcAddress( ghLibInst, "CadPlineGetLength" );
	  if (pfCadPlineGetLength){
		return (*pfCadPlineGetLength)(hEnt);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadPlineGetArea (VHANDLE hEnt)
	{
	  tfCadPlineGetArea pfCadPlineGetArea;
	  pfCadPlineGetArea = (tfCadPlineGetArea)GetProcAddress( ghLibInst, "CadPlineGetArea" );
	  if (pfCadPlineGetArea){
		return (*pfCadPlineGetArea)(hEnt);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPlineContainPoint (VHANDLE hEnt, double X, double Y)
	{
	  tfCadPlineContainPoint pfCadPlineContainPoint;
	  pfCadPlineContainPoint = (tfCadPlineContainPoint)GetProcAddress( ghLibInst, "CadPlineContainPoint" );
	  if (pfCadPlineContainPoint){
		return (*pfCadPlineContainPoint)(hEnt, X, Y);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadPlineGetNearPoint (VHANDLE hEnt, double X, double Y, double Z, double* pX, double* pY, double* pZ, double* pDist)
	{
	  tfCadPlineGetNearPoint pfCadPlineGetNearPoint;
	  pfCadPlineGetNearPoint = (tfCadPlineGetNearPoint)GetProcAddress( ghLibInst, "CadPlineGetNearPoint" );
	  if (pfCadPlineGetNearPoint){
		return (*pfCadPlineGetNearPoint)(hEnt, X, Y, Z, pX, pY, pZ, pDist);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPlineGetDistPoint (VHANDLE hEnt, double Dist, double* pX, double* pY, double* pZ, double* pDirAngle)
	{
	  tfCadPlineGetDistPoint pfCadPlineGetDistPoint;
	  pfCadPlineGetDistPoint = (tfCadPlineGetDistPoint)GetProcAddress( ghLibInst, "CadPlineGetDistPoint" );
	  if (pfCadPlineGetDistPoint){
		return (*pfCadPlineGetDistPoint)(hEnt, Dist, pX, pY, pZ, pDirAngle);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPlineGetInterPoint (VHANDLE hEnt, double x1, double y1, double x2, double y2, double* pX, double* pY, double* pDist)
	{
	  tfCadPlineGetInterPoint pfCadPlineGetInterPoint;
	  pfCadPlineGetInterPoint = (tfCadPlineGetInterPoint)GetProcAddress( ghLibInst, "CadPlineGetInterPoint" );
	  if (pfCadPlineGetInterPoint){
		return (*pfCadPlineGetInterPoint)(hEnt, x1, y1, x2, y2, pX, pY, pDist);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddRect (VDWG hDwg, double X, double Y, double Z, double Width, double Height, double Angle)
	{
	  tfCadAddRect pfCadAddRect;
	  pfCadAddRect = (tfCadAddRect)GetProcAddress( ghLibInst, "CadAddRect" );
	  if (pfCadAddRect){
		return (*pfCadAddRect)(hDwg, X, Y, Z, Width, Height, Angle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRectGetCenter (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadRectGetCenter pfCadRectGetCenter;
	  pfCadRectGetCenter = (tfCadRectGetCenter)GetProcAddress( ghLibInst, "CadRectGetCenter" );
	  if (pfCadRectGetCenter){
		(*pfCadRectGetCenter)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadRectPutCenter (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadRectPutCenter pfCadRectPutCenter;
	  pfCadRectPutCenter = (tfCadRectPutCenter)GetProcAddress( ghLibInst, "CadRectPutCenter" );
	  if (pfCadRectPutCenter){
		(*pfCadRectPutCenter)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	double CADAPI CadRectGetWidth (VHANDLE hEnt)
	{
	  tfCadRectGetWidth pfCadRectGetWidth;
	  pfCadRectGetWidth = (tfCadRectGetWidth)GetProcAddress( ghLibInst, "CadRectGetWidth" );
	  if (pfCadRectGetWidth){
		return (*pfCadRectGetWidth)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRectPutWidth (VHANDLE hEnt, double Width)
	{
	  tfCadRectPutWidth pfCadRectPutWidth;
	  pfCadRectPutWidth = (tfCadRectPutWidth)GetProcAddress( ghLibInst, "CadRectPutWidth" );
	  if (pfCadRectPutWidth){
		(*pfCadRectPutWidth)(hEnt, Width);
	  }
	}


	//--------------
	double CADAPI CadRectGetHeight (VHANDLE hEnt)
	{
	  tfCadRectGetHeight pfCadRectGetHeight;
	  pfCadRectGetHeight = (tfCadRectGetHeight)GetProcAddress( ghLibInst, "CadRectGetHeight" );
	  if (pfCadRectGetHeight){
		return (*pfCadRectGetHeight)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRectPutHeight (VHANDLE hEnt, double Height)
	{
	  tfCadRectPutHeight pfCadRectPutHeight;
	  pfCadRectPutHeight = (tfCadRectPutHeight)GetProcAddress( ghLibInst, "CadRectPutHeight" );
	  if (pfCadRectPutHeight){
		(*pfCadRectPutHeight)(hEnt, Height);
	  }
	}


	//--------------
	double CADAPI CadRectGetAngle (VHANDLE hEnt)
	{
	  tfCadRectGetAngle pfCadRectGetAngle;
	  pfCadRectGetAngle = (tfCadRectGetAngle)GetProcAddress( ghLibInst, "CadRectGetAngle" );
	  if (pfCadRectGetAngle){
		return (*pfCadRectGetAngle)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRectPutAngle (VHANDLE hEnt, double Angle)
	{
	  tfCadRectPutAngle pfCadRectPutAngle;
	  pfCadRectPutAngle = (tfCadRectPutAngle)GetProcAddress( ghLibInst, "CadRectPutAngle" );
	  if (pfCadRectPutAngle){
		(*pfCadRectPutAngle)(hEnt, Angle);
	  }
	}


	//--------------
	double CADAPI CadRectGetRadius (VHANDLE hEnt)
	{
	  tfCadRectGetRadius pfCadRectGetRadius;
	  pfCadRectGetRadius = (tfCadRectGetRadius)GetProcAddress( ghLibInst, "CadRectGetRadius" );
	  if (pfCadRectGetRadius){
		return (*pfCadRectGetRadius)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRectPutRadius (VHANDLE hEnt, double Radius)
	{
	  tfCadRectPutRadius pfCadRectPutRadius;
	  pfCadRectPutRadius = (tfCadRectPutRadius)GetProcAddress( ghLibInst, "CadRectPutRadius" );
	  if (pfCadRectPutRadius){
		(*pfCadRectPutRadius)(hEnt, Radius);
	  }
	}


	//--------------
	BOOL CADAPI CadRectGetPrint (VHANDLE hEnt)
	{
	  tfCadRectGetPrint pfCadRectGetPrint;
	  pfCadRectGetPrint = (tfCadRectGetPrint)GetProcAddress( ghLibInst, "CadRectGetPrint" );
	  if (pfCadRectGetPrint){
		return (*pfCadRectGetPrint)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRectPutPrint (VHANDLE hEnt, BOOL bPrnRect)
	{
	  tfCadRectPutPrint pfCadRectPutPrint;
	  pfCadRectPutPrint = (tfCadRectPutPrint)GetProcAddress( ghLibInst, "CadRectPutPrint" );
	  if (pfCadRectPutPrint){
		(*pfCadRectPutPrint)(hEnt, bPrnRect);
	  }
	}


	//--------------
	void CADAPI CadRectGetName (VHANDLE hEnt, TCHAR* szName)
	{
	  tfCadRectGetName pfCadRectGetName;
	  pfCadRectGetName = (tfCadRectGetName)GetProcAddress( ghLibInst, "CadRectGetName" );
	  if (pfCadRectGetName){
		(*pfCadRectGetName)(hEnt, szName);
	  }
	}


	//--------------
	void CADAPI CadRectPutName (VHANDLE hEnt, LPCTSTR szName)
	{
	  tfCadRectPutName pfCadRectPutName;
	  pfCadRectPutName = (tfCadRectPutName)GetProcAddress( ghLibInst, "CadRectPutName" );
	  if (pfCadRectPutName){
		(*pfCadRectPutName)(hEnt, szName);
	  }
	}


	//--------------
	BOOL CADAPI CadRectPrint (VDWG hDwg, VHANDLE hEnt, HDC hDC)
	{
	  tfCadRectPrint pfCadRectPrint;
	  pfCadRectPrint = (tfCadRectPrint)GetProcAddress( ghLibInst, "CadRectPrint" );
	  if (pfCadRectPrint){
		return (*pfCadRectPrint)(hDwg, hEnt, hDC);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddMline (VDWG hDwg, BOOL bClosed)
	{
	  tfCadAddMline pfCadAddMline;
	  pfCadAddMline = (tfCadAddMline)GetProcAddress( ghLibInst, "CadAddMline" );
	  if (pfCadAddMline){
		return (*pfCadAddMline)(hDwg, bClosed);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadMlineInsertVer (VHANDLE hEnt, UINT iVer)
	{
	  tfCadMlineInsertVer pfCadMlineInsertVer;
	  pfCadMlineInsertVer = (tfCadMlineInsertVer)GetProcAddress( ghLibInst, "CadMlineInsertVer" );
	  if (pfCadMlineInsertVer){
		return (*pfCadMlineInsertVer)(hEnt, iVer);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadMlineDeleteVer (VHANDLE hEnt, UINT iVer)
	{
	  tfCadMlineDeleteVer pfCadMlineDeleteVer;
	  pfCadMlineDeleteVer = (tfCadMlineDeleteVer)GetProcAddress( ghLibInst, "CadMlineDeleteVer" );
	  if (pfCadMlineDeleteVer){
		return (*pfCadMlineDeleteVer)(hEnt, iVer);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadMlineGetNumVers (VHANDLE hEnt)
	{
	  tfCadMlineGetNumVers pfCadMlineGetNumVers;
	  pfCadMlineGetNumVers = (tfCadMlineGetNumVers)GetProcAddress( ghLibInst, "CadMlineGetNumVers" );
	  if (pfCadMlineGetNumVers){
		return (*pfCadMlineGetNumVers)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMlinePutNumVers (VHANDLE hEnt, UINT nVers)
	{
	  tfCadMlinePutNumVers pfCadMlinePutNumVers;
	  pfCadMlinePutNumVers = (tfCadMlinePutNumVers)GetProcAddress( ghLibInst, "CadMlinePutNumVers" );
	  if (pfCadMlinePutNumVers){
		(*pfCadMlinePutNumVers)(hEnt, nVers);
	  }
	}


	//--------------
	void CADAPI CadMlineGetVer (VHANDLE hEnt, UINT iVer, double* pX, double* pY, double* pZ)
	{
	  tfCadMlineGetVer pfCadMlineGetVer;
	  pfCadMlineGetVer = (tfCadMlineGetVer)GetProcAddress( ghLibInst, "CadMlineGetVer" );
	  if (pfCadMlineGetVer){
		(*pfCadMlineGetVer)(hEnt, iVer, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadMlinePutVer (VHANDLE hEnt, UINT iVer, double X, double Y, double Z)
	{
	  tfCadMlinePutVer pfCadMlinePutVer;
	  pfCadMlinePutVer = (tfCadMlinePutVer)GetProcAddress( ghLibInst, "CadMlinePutVer" );
	  if (pfCadMlinePutVer){
		(*pfCadMlinePutVer)(hEnt, iVer, X, Y, Z);
	  }
	}


	//--------------
	void CADAPI CadMlinePutZ1 (VHANDLE hEnt, double Z)
	{
	  tfCadMlinePutZ1 pfCadMlinePutZ1;
	  pfCadMlinePutZ1 = (tfCadMlinePutZ1)GetProcAddress( ghLibInst, "CadMlinePutZ1" );
	  if (pfCadMlinePutZ1){
		(*pfCadMlinePutZ1)(hEnt, Z);
	  }
	}


	//--------------
	BOOL CADAPI CadMlineGetClosed (VHANDLE hEnt)
	{
	  tfCadMlineGetClosed pfCadMlineGetClosed;
	  pfCadMlineGetClosed = (tfCadMlineGetClosed)GetProcAddress( ghLibInst, "CadMlineGetClosed" );
	  if (pfCadMlineGetClosed){
		return (*pfCadMlineGetClosed)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMlinePutClosed (VHANDLE hEnt, BOOL bClosed)
	{
	  tfCadMlinePutClosed pfCadMlinePutClosed;
	  pfCadMlinePutClosed = (tfCadMlinePutClosed)GetProcAddress( ghLibInst, "CadMlinePutClosed" );
	  if (pfCadMlinePutClosed){
		(*pfCadMlinePutClosed)(hEnt, bClosed);
	  }
	}


	//--------------
	void CADAPI CadMlinePutScale (VHANDLE hEnt, double Scal)
	{
	  tfCadMlinePutScale pfCadMlinePutScale;
	  pfCadMlinePutScale = (tfCadMlinePutScale)GetProcAddress( ghLibInst, "CadMlinePutScale" );
	  if (pfCadMlinePutScale){
		(*pfCadMlinePutScale)(hEnt, Scal);
	  }
	}


	//--------------
	double CADAPI CadMlineGetScale (VHANDLE hEnt)
	{
	  tfCadMlineGetScale pfCadMlineGetScale;
	  pfCadMlineGetScale = (tfCadMlineGetScale)GetProcAddress( ghLibInst, "CadMlineGetScale" );
	  if (pfCadMlineGetScale){
		return (*pfCadMlineGetScale)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMlinePutJust (VHANDLE hEnt, int Just)
	{
	  tfCadMlinePutJust pfCadMlinePutJust;
	  pfCadMlinePutJust = (tfCadMlinePutJust)GetProcAddress( ghLibInst, "CadMlinePutJust" );
	  if (pfCadMlinePutJust){
		(*pfCadMlinePutJust)(hEnt, Just);
	  }
	}


	//--------------
	int CADAPI CadMlineGetJust (VHANDLE hEnt)
	{
	  tfCadMlineGetJust pfCadMlineGetJust;
	  pfCadMlineGetJust = (tfCadMlineGetJust)GetProcAddress( ghLibInst, "CadMlineGetJust" );
	  if (pfCadMlineGetJust){
		return (*pfCadMlineGetJust)(hEnt);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadMlineGetLength (VHANDLE hEnt)
	{
	  tfCadMlineGetLength pfCadMlineGetLength;
	  pfCadMlineGetLength = (tfCadMlineGetLength)GetProcAddress( ghLibInst, "CadMlineGetLength" );
	  if (pfCadMlineGetLength){
		return (*pfCadMlineGetLength)(hEnt);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadMlineGetStyleID (VHANDLE hEnt)
	{
	  tfCadMlineGetStyleID pfCadMlineGetStyleID;
	  pfCadMlineGetStyleID = (tfCadMlineGetStyleID)GetProcAddress( ghLibInst, "CadMlineGetStyleID" );
	  if (pfCadMlineGetStyleID){
		return (*pfCadMlineGetStyleID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMlinePutStyleID (VHANDLE hEnt, IDOBJ Id)
	{
	  tfCadMlinePutStyleID pfCadMlinePutStyleID;
	  pfCadMlinePutStyleID = (tfCadMlinePutStyleID)GetProcAddress( ghLibInst, "CadMlinePutStyleID" );
	  if (pfCadMlinePutStyleID){
		(*pfCadMlinePutStyleID)(hEnt, Id);
	  }
	}


	//--------------
	int CADAPI CadSetTextAlign (VDWG hDwg, int Align)
	{
	  tfCadSetTextAlign pfCadSetTextAlign;
	  pfCadSetTextAlign = (tfCadSetTextAlign)GetProcAddress( ghLibInst, "CadSetTextAlign" );
	  if (pfCadSetTextAlign){
		return (*pfCadSetTextAlign)(hDwg, Align);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadSetTextHeight (VDWG hDwg, double Height)
	{
	  tfCadSetTextHeight pfCadSetTextHeight;
	  pfCadSetTextHeight = (tfCadSetTextHeight)GetProcAddress( ghLibInst, "CadSetTextHeight" );
	  if (pfCadSetTextHeight){
		return (*pfCadSetTextHeight)(hDwg, Height);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadSetTextWidth (VDWG hDwg, double Width)
	{
	  tfCadSetTextWidth pfCadSetTextWidth;
	  pfCadSetTextWidth = (tfCadSetTextWidth)GetProcAddress( ghLibInst, "CadSetTextWidth" );
	  if (pfCadSetTextWidth){
		return (*pfCadSetTextWidth)(hDwg, Width);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadSetTextRotAngle (VDWG hDwg, double Angle)
	{
	  tfCadSetTextRotAngle pfCadSetTextRotAngle;
	  pfCadSetTextRotAngle = (tfCadSetTextRotAngle)GetProcAddress( ghLibInst, "CadSetTextRotAngle" );
	  if (pfCadSetTextRotAngle){
		return (*pfCadSetTextRotAngle)(hDwg, Angle);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadSetTextOblique (VDWG hDwg, double Angle)
	{
	  tfCadSetTextOblique pfCadSetTextOblique;
	  pfCadSetTextOblique = (tfCadSetTextOblique)GetProcAddress( ghLibInst, "CadSetTextOblique" );
	  if (pfCadSetTextOblique){
		return (*pfCadSetTextOblique)(hDwg, Angle);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadSetTextUpsideDown (VDWG hDwg, BOOL bUpDown)
	{
	  tfCadSetTextUpsideDown pfCadSetTextUpsideDown;
	  pfCadSetTextUpsideDown = (tfCadSetTextUpsideDown)GetProcAddress( ghLibInst, "CadSetTextUpsideDown" );
	  if (pfCadSetTextUpsideDown){
		return (*pfCadSetTextUpsideDown)(hDwg, bUpDown);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadSetTextBackward (VDWG hDwg, BOOL bBack)
	{
	  tfCadSetTextBackward pfCadSetTextBackward;
	  pfCadSetTextBackward = (tfCadSetTextBackward)GetProcAddress( ghLibInst, "CadSetTextBackward" );
	  if (pfCadSetTextBackward){
		return (*pfCadSetTextBackward)(hDwg, bBack);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddText (VDWG hDwg, LPCTSTR szText, double X, double Y, double Z)
	{
	  tfCadAddText pfCadAddText;
	  pfCadAddText = (tfCadAddText)GetProcAddress( ghLibInst, "CadAddText" );
	  if (pfCadAddText){
		return (*pfCadAddText)(hDwg, szText, X, Y, Z);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddText2 (VDWG hDwg, LPCTSTR szText, double X, double Y, double Z, int Align, double H, double W, double RotAngle, double Oblique)
	{
	  tfCadAddText2 pfCadAddText2;
	  pfCadAddText2 = (tfCadAddText2)GetProcAddress( ghLibInst, "CadAddText2" );
	  if (pfCadAddText2){
		return (*pfCadAddText2)(hDwg, szText, X, Y, Z, Align, H, W, RotAngle, Oblique);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadTextGetStyleID (VHANDLE hEnt)
	{
	  tfCadTextGetStyleID pfCadTextGetStyleID;
	  pfCadTextGetStyleID = (tfCadTextGetStyleID)GetProcAddress( ghLibInst, "CadTextGetStyleID" );
	  if (pfCadTextGetStyleID){
		return (*pfCadTextGetStyleID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextPutStyleID (VHANDLE hEnt, IDOBJ Id)
	{
	  tfCadTextPutStyleID pfCadTextPutStyleID;
	  pfCadTextPutStyleID = (tfCadTextPutStyleID)GetProcAddress( ghLibInst, "CadTextPutStyleID" );
	  if (pfCadTextPutStyleID){
		(*pfCadTextPutStyleID)(hEnt, Id);
	  }
	}


	//--------------
	double CADAPI CadTextGetX (VHANDLE hEnt)
	{
	  tfCadTextGetX pfCadTextGetX;
	  pfCadTextGetX = (tfCadTextGetX)GetProcAddress( ghLibInst, "CadTextGetX" );
	  if (pfCadTextGetX){
		return (*pfCadTextGetX)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextPutX (VHANDLE hEnt, double X)
	{
	  tfCadTextPutX pfCadTextPutX;
	  pfCadTextPutX = (tfCadTextPutX)GetProcAddress( ghLibInst, "CadTextPutX" );
	  if (pfCadTextPutX){
		(*pfCadTextPutX)(hEnt, X);
	  }
	}


	//--------------
	double CADAPI CadTextGetY (VHANDLE hEnt)
	{
	  tfCadTextGetY pfCadTextGetY;
	  pfCadTextGetY = (tfCadTextGetY)GetProcAddress( ghLibInst, "CadTextGetY" );
	  if (pfCadTextGetY){
		return (*pfCadTextGetY)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextPutY (VHANDLE hEnt, double Y)
	{
	  tfCadTextPutY pfCadTextPutY;
	  pfCadTextPutY = (tfCadTextPutY)GetProcAddress( ghLibInst, "CadTextPutY" );
	  if (pfCadTextPutY){
		(*pfCadTextPutY)(hEnt, Y);
	  }
	}


	//--------------
	double CADAPI CadTextGetZ (VHANDLE hEnt)
	{
	  tfCadTextGetZ pfCadTextGetZ;
	  pfCadTextGetZ = (tfCadTextGetZ)GetProcAddress( ghLibInst, "CadTextGetZ" );
	  if (pfCadTextGetZ){
		return (*pfCadTextGetZ)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextPutZ (VHANDLE hEnt, double Z)
	{
	  tfCadTextPutZ pfCadTextPutZ;
	  pfCadTextPutZ = (tfCadTextPutZ)GetProcAddress( ghLibInst, "CadTextPutZ" );
	  if (pfCadTextPutZ){
		(*pfCadTextPutZ)(hEnt, Z);
	  }
	}


	//--------------
	void CADAPI CadTextGetPoint (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadTextGetPoint pfCadTextGetPoint;
	  pfCadTextGetPoint = (tfCadTextGetPoint)GetProcAddress( ghLibInst, "CadTextGetPoint" );
	  if (pfCadTextGetPoint){
		(*pfCadTextGetPoint)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadTextPutPoint (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadTextPutPoint pfCadTextPutPoint;
	  pfCadTextPutPoint = (tfCadTextPutPoint)GetProcAddress( ghLibInst, "CadTextPutPoint" );
	  if (pfCadTextPutPoint){
		(*pfCadTextPutPoint)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	UINT CADAPI CadTextGetLen (VHANDLE hEnt)
	{
	  tfCadTextGetLen pfCadTextGetLen;
	  pfCadTextGetLen = (tfCadTextGetLen)GetProcAddress( ghLibInst, "CadTextGetLen" );
	  if (pfCadTextGetLen){
		return (*pfCadTextGetLen)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextGetText (VHANDLE hEnt, TCHAR* szText, UINT MaxChars)
	{
	  tfCadTextGetText pfCadTextGetText;
	  pfCadTextGetText = (tfCadTextGetText)GetProcAddress( ghLibInst, "CadTextGetText" );
	  if (pfCadTextGetText){
		(*pfCadTextGetText)(hEnt, szText, MaxChars);
	  }
	}


	//--------------
	void CADAPI CadTextPutText (VHANDLE hEnt, LPCTSTR szText)
	{
	  tfCadTextPutText pfCadTextPutText;
	  pfCadTextPutText = (tfCadTextPutText)GetProcAddress( ghLibInst, "CadTextPutText" );
	  if (pfCadTextPutText){
		(*pfCadTextPutText)(hEnt, szText);
	  }
	}


	//--------------
	double CADAPI CadTextGetAngle (VHANDLE hEnt)
	{
	  tfCadTextGetAngle pfCadTextGetAngle;
	  pfCadTextGetAngle = (tfCadTextGetAngle)GetProcAddress( ghLibInst, "CadTextGetAngle" );
	  if (pfCadTextGetAngle){
		return (*pfCadTextGetAngle)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextPutAngle (VHANDLE hEnt, double Angle)
	{
	  tfCadTextPutAngle pfCadTextPutAngle;
	  pfCadTextPutAngle = (tfCadTextPutAngle)GetProcAddress( ghLibInst, "CadTextPutAngle" );
	  if (pfCadTextPutAngle){
		(*pfCadTextPutAngle)(hEnt, Angle);
	  }
	}


	//--------------
	double CADAPI CadTextGetHeight (VHANDLE hEnt)
	{
	  tfCadTextGetHeight pfCadTextGetHeight;
	  pfCadTextGetHeight = (tfCadTextGetHeight)GetProcAddress( ghLibInst, "CadTextGetHeight" );
	  if (pfCadTextGetHeight){
		return (*pfCadTextGetHeight)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextPutHeight (VHANDLE hEnt, double Height)
	{
	  tfCadTextPutHeight pfCadTextPutHeight;
	  pfCadTextPutHeight = (tfCadTextPutHeight)GetProcAddress( ghLibInst, "CadTextPutHeight" );
	  if (pfCadTextPutHeight){
		(*pfCadTextPutHeight)(hEnt, Height);
	  }
	}


	//--------------
	double CADAPI CadTextGetWidth (VHANDLE hEnt)
	{
	  tfCadTextGetWidth pfCadTextGetWidth;
	  pfCadTextGetWidth = (tfCadTextGetWidth)GetProcAddress( ghLibInst, "CadTextGetWidth" );
	  if (pfCadTextGetWidth){
		return (*pfCadTextGetWidth)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextPutWidth (VHANDLE hEnt, double Width)
	{
	  tfCadTextPutWidth pfCadTextPutWidth;
	  pfCadTextPutWidth = (tfCadTextPutWidth)GetProcAddress( ghLibInst, "CadTextPutWidth" );
	  if (pfCadTextPutWidth){
		(*pfCadTextPutWidth)(hEnt, Width);
	  }
	}


	//--------------
	double CADAPI CadTextGetOblique (VHANDLE hEnt)
	{
	  tfCadTextGetOblique pfCadTextGetOblique;
	  pfCadTextGetOblique = (tfCadTextGetOblique)GetProcAddress( ghLibInst, "CadTextGetOblique" );
	  if (pfCadTextGetOblique){
		return (*pfCadTextGetOblique)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextPutOblique (VHANDLE hEnt, double Angle)
	{
	  tfCadTextPutOblique pfCadTextPutOblique;
	  pfCadTextPutOblique = (tfCadTextPutOblique)GetProcAddress( ghLibInst, "CadTextPutOblique" );
	  if (pfCadTextPutOblique){
		(*pfCadTextPutOblique)(hEnt, Angle);
	  }
	}


	//--------------
	int CADAPI CadTextGetAlign (VHANDLE hEnt)
	{
	  tfCadTextGetAlign pfCadTextGetAlign;
	  pfCadTextGetAlign = (tfCadTextGetAlign)GetProcAddress( ghLibInst, "CadTextGetAlign" );
	  if (pfCadTextGetAlign){
		return (*pfCadTextGetAlign)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextPutAlign (VHANDLE hEnt, int Align)
	{
	  tfCadTextPutAlign pfCadTextPutAlign;
	  pfCadTextPutAlign = (tfCadTextPutAlign)GetProcAddress( ghLibInst, "CadTextPutAlign" );
	  if (pfCadTextPutAlign){
		(*pfCadTextPutAlign)(hEnt, Align);
	  }
	}


	//--------------
	BOOL CADAPI CadTextGetBackward (VHANDLE hEnt)
	{
	  tfCadTextGetBackward pfCadTextGetBackward;
	  pfCadTextGetBackward = (tfCadTextGetBackward)GetProcAddress( ghLibInst, "CadTextGetBackward" );
	  if (pfCadTextGetBackward){
		return (*pfCadTextGetBackward)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextPutBackward (VHANDLE hEnt, BOOL bBackward)
	{
	  tfCadTextPutBackward pfCadTextPutBackward;
	  pfCadTextPutBackward = (tfCadTextPutBackward)GetProcAddress( ghLibInst, "CadTextPutBackward" );
	  if (pfCadTextPutBackward){
		(*pfCadTextPutBackward)(hEnt, bBackward);
	  }
	}


	//--------------
	BOOL CADAPI CadTextGetUpsideDown (VHANDLE hEnt)
	{
	  tfCadTextGetUpsideDown pfCadTextGetUpsideDown;
	  pfCadTextGetUpsideDown = (tfCadTextGetUpsideDown)GetProcAddress( ghLibInst, "CadTextGetUpsideDown" );
	  if (pfCadTextGetUpsideDown){
		return (*pfCadTextGetUpsideDown)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextPutUpsideDown (VHANDLE hEnt, BOOL bUpsideDown)
	{
	  tfCadTextPutUpsideDown pfCadTextPutUpsideDown;
	  pfCadTextPutUpsideDown = (tfCadTextPutUpsideDown)GetProcAddress( ghLibInst, "CadTextPutUpsideDown" );
	  if (pfCadTextPutUpsideDown){
		(*pfCadTextPutUpsideDown)(hEnt, bUpsideDown);
	  }
	}


	//--------------
	double CADAPI CadTextGetBoxWidth (VHANDLE hEnt)
	{
	  tfCadTextGetBoxWidth pfCadTextGetBoxWidth;
	  pfCadTextGetBoxWidth = (tfCadTextGetBoxWidth)GetProcAddress( ghLibInst, "CadTextGetBoxWidth" );
	  if (pfCadTextGetBoxWidth){
		return (*pfCadTextGetBoxWidth)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTextGetPoint0 (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadTextGetPoint0 pfCadTextGetPoint0;
	  pfCadTextGetPoint0 = (tfCadTextGetPoint0)GetProcAddress( ghLibInst, "CadTextGetPoint0" );
	  if (pfCadTextGetPoint0){
		(*pfCadTextGetPoint0)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddMText (VDWG hDwg, LPCTSTR szText, double RectWidth, double X, double Y, double Z, int Align, double RotAngle)
	{
	  tfCadAddMText pfCadAddMText;
	  pfCadAddMText = (tfCadAddMText)GetProcAddress( ghLibInst, "CadAddMText" );
	  if (pfCadAddMText){
		return (*pfCadAddMText)(hDwg, szText, RectWidth, X, Y, Z, Align, RotAngle);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadMTextGetStyleID (VHANDLE hEnt)
	{
	  tfCadMTextGetStyleID pfCadMTextGetStyleID;
	  pfCadMTextGetStyleID = (tfCadMTextGetStyleID)GetProcAddress( ghLibInst, "CadMTextGetStyleID" );
	  if (pfCadMTextGetStyleID){
		return (*pfCadMTextGetStyleID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMTextPutStyleID (VHANDLE hEnt, IDOBJ Id)
	{
	  tfCadMTextPutStyleID pfCadMTextPutStyleID;
	  pfCadMTextPutStyleID = (tfCadMTextPutStyleID)GetProcAddress( ghLibInst, "CadMTextPutStyleID" );
	  if (pfCadMTextPutStyleID){
		(*pfCadMTextPutStyleID)(hEnt, Id);
	  }
	}


	//--------------
	void CADAPI CadMTextGetPoint (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadMTextGetPoint pfCadMTextGetPoint;
	  pfCadMTextGetPoint = (tfCadMTextGetPoint)GetProcAddress( ghLibInst, "CadMTextGetPoint" );
	  if (pfCadMTextGetPoint){
		(*pfCadMTextGetPoint)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadMTextPutPoint (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadMTextPutPoint pfCadMTextPutPoint;
	  pfCadMTextPutPoint = (tfCadMTextPutPoint)GetProcAddress( ghLibInst, "CadMTextPutPoint" );
	  if (pfCadMTextPutPoint){
		(*pfCadMTextPutPoint)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	UINT CADAPI CadMTextGetLen (VHANDLE hEnt)
	{
	  tfCadMTextGetLen pfCadMTextGetLen;
	  pfCadMTextGetLen = (tfCadMTextGetLen)GetProcAddress( ghLibInst, "CadMTextGetLen" );
	  if (pfCadMTextGetLen){
		return (*pfCadMTextGetLen)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMTextGetText (VHANDLE hEnt, TCHAR* szText, UINT MaxChars)
	{
	  tfCadMTextGetText pfCadMTextGetText;
	  pfCadMTextGetText = (tfCadMTextGetText)GetProcAddress( ghLibInst, "CadMTextGetText" );
	  if (pfCadMTextGetText){
		(*pfCadMTextGetText)(hEnt, szText, MaxChars);
	  }
	}


	//--------------
	void CADAPI CadMTextPutText (VHANDLE hEnt, LPCTSTR szText)
	{
	  tfCadMTextPutText pfCadMTextPutText;
	  pfCadMTextPutText = (tfCadMTextPutText)GetProcAddress( ghLibInst, "CadMTextPutText" );
	  if (pfCadMTextPutText){
		(*pfCadMTextPutText)(hEnt, szText);
	  }
	}


	//--------------
	double CADAPI CadMTextGetRectWidth (VHANDLE hEnt)
	{
	  tfCadMTextGetRectWidth pfCadMTextGetRectWidth;
	  pfCadMTextGetRectWidth = (tfCadMTextGetRectWidth)GetProcAddress( ghLibInst, "CadMTextGetRectWidth" );
	  if (pfCadMTextGetRectWidth){
		return (*pfCadMTextGetRectWidth)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMTextPutRectWidth (VHANDLE hEnt, double RectWidth)
	{
	  tfCadMTextPutRectWidth pfCadMTextPutRectWidth;
	  pfCadMTextPutRectWidth = (tfCadMTextPutRectWidth)GetProcAddress( ghLibInst, "CadMTextPutRectWidth" );
	  if (pfCadMTextPutRectWidth){
		(*pfCadMTextPutRectWidth)(hEnt, RectWidth);
	  }
	}


	//--------------
	int CADAPI CadMTextGetAlign (VHANDLE hEnt)
	{
	  tfCadMTextGetAlign pfCadMTextGetAlign;
	  pfCadMTextGetAlign = (tfCadMTextGetAlign)GetProcAddress( ghLibInst, "CadMTextGetAlign" );
	  if (pfCadMTextGetAlign){
		return (*pfCadMTextGetAlign)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMTextPutAlign (VHANDLE hEnt, int Align)
	{
	  tfCadMTextPutAlign pfCadMTextPutAlign;
	  pfCadMTextPutAlign = (tfCadMTextPutAlign)GetProcAddress( ghLibInst, "CadMTextPutAlign" );
	  if (pfCadMTextPutAlign){
		(*pfCadMTextPutAlign)(hEnt, Align);
	  }
	}


	//--------------
	double CADAPI CadMTextGetHeight (VHANDLE hEnt)
	{
	  tfCadMTextGetHeight pfCadMTextGetHeight;
	  pfCadMTextGetHeight = (tfCadMTextGetHeight)GetProcAddress( ghLibInst, "CadMTextGetHeight" );
	  if (pfCadMTextGetHeight){
		return (*pfCadMTextGetHeight)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMTextPutHeight (VHANDLE hEnt, double Height)
	{
	  tfCadMTextPutHeight pfCadMTextPutHeight;
	  pfCadMTextPutHeight = (tfCadMTextPutHeight)GetProcAddress( ghLibInst, "CadMTextPutHeight" );
	  if (pfCadMTextPutHeight){
		(*pfCadMTextPutHeight)(hEnt, Height);
	  }
	}


	//--------------
	double CADAPI CadMTextGetAngle (VHANDLE hEnt)
	{
	  tfCadMTextGetAngle pfCadMTextGetAngle;
	  pfCadMTextGetAngle = (tfCadMTextGetAngle)GetProcAddress( ghLibInst, "CadMTextGetAngle" );
	  if (pfCadMTextGetAngle){
		return (*pfCadMTextGetAngle)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMTextPutAngle (VHANDLE hEnt, double Angle)
	{
	  tfCadMTextPutAngle pfCadMTextPutAngle;
	  pfCadMTextPutAngle = (tfCadMTextPutAngle)GetProcAddress( ghLibInst, "CadMTextPutAngle" );
	  if (pfCadMTextPutAngle){
		(*pfCadMTextPutAngle)(hEnt, Angle);
	  }
	}


	//--------------
	double CADAPI CadMTextGetWidth (VHANDLE hEnt)
	{
	  tfCadMTextGetWidth pfCadMTextGetWidth;
	  pfCadMTextGetWidth = (tfCadMTextGetWidth)GetProcAddress( ghLibInst, "CadMTextGetWidth" );
	  if (pfCadMTextGetWidth){
		return (*pfCadMTextGetWidth)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMTextPutWidth (VHANDLE hEnt, double Width)
	{
	  tfCadMTextPutWidth pfCadMTextPutWidth;
	  pfCadMTextPutWidth = (tfCadMTextPutWidth)GetProcAddress( ghLibInst, "CadMTextPutWidth" );
	  if (pfCadMTextPutWidth){
		(*pfCadMTextPutWidth)(hEnt, Width);
	  }
	}


	//--------------
	double CADAPI CadMTextGetLineSpace (VHANDLE hEnt)
	{
	  tfCadMTextGetLineSpace pfCadMTextGetLineSpace;
	  pfCadMTextGetLineSpace = (tfCadMTextGetLineSpace)GetProcAddress( ghLibInst, "CadMTextGetLineSpace" );
	  if (pfCadMTextGetLineSpace){
		return (*pfCadMTextGetLineSpace)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMTextPutLineSpace (VHANDLE hEnt, double LineSpace)
	{
	  tfCadMTextPutLineSpace pfCadMTextPutLineSpace;
	  pfCadMTextPutLineSpace = (tfCadMTextPutLineSpace)GetProcAddress( ghLibInst, "CadMTextPutLineSpace" );
	  if (pfCadMTextPutLineSpace){
		(*pfCadMTextPutLineSpace)(hEnt, LineSpace);
	  }
	}


	//--------------
	double CADAPI CadMTextGetAW (VHANDLE hEnt)
	{
	  tfCadMTextGetAW pfCadMTextGetAW;
	  pfCadMTextGetAW = (tfCadMTextGetAW)GetProcAddress( ghLibInst, "CadMTextGetAW" );
	  if (pfCadMTextGetAW){
		return (*pfCadMTextGetAW)(hEnt);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadMTextGetAH (VHANDLE hEnt)
	{
	  tfCadMTextGetAH pfCadMTextGetAH;
	  pfCadMTextGetAH = (tfCadMTextGetAH)GetProcAddress( ghLibInst, "CadMTextGetAH" );
	  if (pfCadMTextGetAH){
		return (*pfCadMTextGetAH)(hEnt);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddWText (VDWG hDwg, LPCTSTR szText, double X, double Y, double Z)
	{
	  tfCadAddWText pfCadAddWText;
	  pfCadAddWText = (tfCadAddWText)GetProcAddress( ghLibInst, "CadAddWText" );
	  if (pfCadAddWText){
		return (*pfCadAddWText)(hDwg, szText, X, Y, Z);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddWText2 (VDWG hDwg, LPCTSTR szText, double X, double Y, double Z, int Align, double H, double RotAngle, bool bItalic, bool bUnderline, bool bStrikeout)
	{
	  tfCadAddWText2 pfCadAddWText2;
	  pfCadAddWText2 = (tfCadAddWText2)GetProcAddress( ghLibInst, "CadAddWText2" );
	  if (pfCadAddWText2){
		return (*pfCadAddWText2)(hDwg, szText, X, Y, Z, Align, H, RotAngle, bItalic, bUnderline, bStrikeout);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadWTextGetStyleID (VHANDLE hEnt)
	{
	  tfCadWTextGetStyleID pfCadWTextGetStyleID;
	  pfCadWTextGetStyleID = (tfCadWTextGetStyleID)GetProcAddress( ghLibInst, "CadWTextGetStyleID" );
	  if (pfCadWTextGetStyleID){
		return (*pfCadWTextGetStyleID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadWTextPutStyleID (VHANDLE hEnt, IDOBJ Id)
	{
	  tfCadWTextPutStyleID pfCadWTextPutStyleID;
	  pfCadWTextPutStyleID = (tfCadWTextPutStyleID)GetProcAddress( ghLibInst, "CadWTextPutStyleID" );
	  if (pfCadWTextPutStyleID){
		(*pfCadWTextPutStyleID)(hEnt, Id);
	  }
	}


	//--------------
	void CADAPI CadWTextGetPoint (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadWTextGetPoint pfCadWTextGetPoint;
	  pfCadWTextGetPoint = (tfCadWTextGetPoint)GetProcAddress( ghLibInst, "CadWTextGetPoint" );
	  if (pfCadWTextGetPoint){
		(*pfCadWTextGetPoint)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadWTextPutPoint (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadWTextPutPoint pfCadWTextPutPoint;
	  pfCadWTextPutPoint = (tfCadWTextPutPoint)GetProcAddress( ghLibInst, "CadWTextPutPoint" );
	  if (pfCadWTextPutPoint){
		(*pfCadWTextPutPoint)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	UINT CADAPI CadWTextGetLen (VHANDLE hEnt)
	{
	  tfCadWTextGetLen pfCadWTextGetLen;
	  pfCadWTextGetLen = (tfCadWTextGetLen)GetProcAddress( ghLibInst, "CadWTextGetLen" );
	  if (pfCadWTextGetLen){
		return (*pfCadWTextGetLen)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadWTextGetText (VHANDLE hEnt, TCHAR* szText, UINT MaxChars)
	{
	  tfCadWTextGetText pfCadWTextGetText;
	  pfCadWTextGetText = (tfCadWTextGetText)GetProcAddress( ghLibInst, "CadWTextGetText" );
	  if (pfCadWTextGetText){
		(*pfCadWTextGetText)(hEnt, szText, MaxChars);
	  }
	}


	//--------------
	void CADAPI CadWTextPutText (VHANDLE hEnt, LPCTSTR szText)
	{
	  tfCadWTextPutText pfCadWTextPutText;
	  pfCadWTextPutText = (tfCadWTextPutText)GetProcAddress( ghLibInst, "CadWTextPutText" );
	  if (pfCadWTextPutText){
		(*pfCadWTextPutText)(hEnt, szText);
	  }
	}


	//--------------
	double CADAPI CadWTextGetAngle (VHANDLE hEnt)
	{
	  tfCadWTextGetAngle pfCadWTextGetAngle;
	  pfCadWTextGetAngle = (tfCadWTextGetAngle)GetProcAddress( ghLibInst, "CadWTextGetAngle" );
	  if (pfCadWTextGetAngle){
		return (*pfCadWTextGetAngle)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadWTextPutAngle (VHANDLE hEnt, double Angle)
	{
	  tfCadWTextPutAngle pfCadWTextPutAngle;
	  pfCadWTextPutAngle = (tfCadWTextPutAngle)GetProcAddress( ghLibInst, "CadWTextPutAngle" );
	  if (pfCadWTextPutAngle){
		(*pfCadWTextPutAngle)(hEnt, Angle);
	  }
	}


	//--------------
	double CADAPI CadWTextGetHeight (VHANDLE hEnt)
	{
	  tfCadWTextGetHeight pfCadWTextGetHeight;
	  pfCadWTextGetHeight = (tfCadWTextGetHeight)GetProcAddress( ghLibInst, "CadWTextGetHeight" );
	  if (pfCadWTextGetHeight){
		return (*pfCadWTextGetHeight)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadWTextPutHeight (VHANDLE hEnt, double Height)
	{
	  tfCadWTextPutHeight pfCadWTextPutHeight;
	  pfCadWTextPutHeight = (tfCadWTextPutHeight)GetProcAddress( ghLibInst, "CadWTextPutHeight" );
	  if (pfCadWTextPutHeight){
		(*pfCadWTextPutHeight)(hEnt, Height);
	  }
	}


	//--------------
	int CADAPI CadWTextGetAlign (VHANDLE hEnt)
	{
	  tfCadWTextGetAlign pfCadWTextGetAlign;
	  pfCadWTextGetAlign = (tfCadWTextGetAlign)GetProcAddress( ghLibInst, "CadWTextGetAlign" );
	  if (pfCadWTextGetAlign){
		return (*pfCadWTextGetAlign)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadWTextPutAlign (VHANDLE hEnt, int Align)
	{
	  tfCadWTextPutAlign pfCadWTextPutAlign;
	  pfCadWTextPutAlign = (tfCadWTextPutAlign)GetProcAddress( ghLibInst, "CadWTextPutAlign" );
	  if (pfCadWTextPutAlign){
		(*pfCadWTextPutAlign)(hEnt, Align);
	  }
	}


	//--------------
	BOOL CADAPI CadWTextGetItalic (VHANDLE hEnt)
	{
	  tfCadWTextGetItalic pfCadWTextGetItalic;
	  pfCadWTextGetItalic = (tfCadWTextGetItalic)GetProcAddress( ghLibInst, "CadWTextGetItalic" );
	  if (pfCadWTextGetItalic){
		return (*pfCadWTextGetItalic)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadWTextPutItalic (VHANDLE hEnt, BOOL bItalic)
	{
	  tfCadWTextPutItalic pfCadWTextPutItalic;
	  pfCadWTextPutItalic = (tfCadWTextPutItalic)GetProcAddress( ghLibInst, "CadWTextPutItalic" );
	  if (pfCadWTextPutItalic){
		(*pfCadWTextPutItalic)(hEnt, bItalic);
	  }
	}


	//--------------
	BOOL CADAPI CadWTextGetStrikeout (VHANDLE hEnt)
	{
	  tfCadWTextGetStrikeout pfCadWTextGetStrikeout;
	  pfCadWTextGetStrikeout = (tfCadWTextGetStrikeout)GetProcAddress( ghLibInst, "CadWTextGetStrikeout" );
	  if (pfCadWTextGetStrikeout){
		return (*pfCadWTextGetStrikeout)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadWTextPutStrikeout (VHANDLE hEnt, BOOL bStrikeout)
	{
	  tfCadWTextPutStrikeout pfCadWTextPutStrikeout;
	  pfCadWTextPutStrikeout = (tfCadWTextPutStrikeout)GetProcAddress( ghLibInst, "CadWTextPutStrikeout" );
	  if (pfCadWTextPutStrikeout){
		(*pfCadWTextPutStrikeout)(hEnt, bStrikeout);
	  }
	}


	//--------------
	BOOL CADAPI CadWTextGetUnderline (VHANDLE hEnt)
	{
	  tfCadWTextGetUnderline pfCadWTextGetUnderline;
	  pfCadWTextGetUnderline = (tfCadWTextGetUnderline)GetProcAddress( ghLibInst, "CadWTextGetUnderline" );
	  if (pfCadWTextGetUnderline){
		return (*pfCadWTextGetUnderline)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadWTextPutUnderline (VHANDLE hEnt, BOOL bUnderline)
	{
	  tfCadWTextPutUnderline pfCadWTextPutUnderline;
	  pfCadWTextPutUnderline = (tfCadWTextPutUnderline)GetProcAddress( ghLibInst, "CadWTextPutUnderline" );
	  if (pfCadWTextPutUnderline){
		(*pfCadWTextPutUnderline)(hEnt, bUnderline);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddInsBlock (VDWG hDwg, IDOBJ idBlock, double X, double Y, double Z, double Scal, double Angle)
	{
	  tfCadAddInsBlock pfCadAddInsBlock;
	  pfCadAddInsBlock = (tfCadAddInsBlock)GetProcAddress( ghLibInst, "CadAddInsBlock" );
	  if (pfCadAddInsBlock){
		return (*pfCadAddInsBlock)(hDwg, idBlock, X, Y, Z, Scal, Angle);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddInsBlockM (VDWG hDwg, IDOBJ idBlock, double X, double Y, double Z, double Scal, double Angle, int NumCols, int NumRows, double ColDist, double RowDist)
	{
	  tfCadAddInsBlockM pfCadAddInsBlockM;
	  pfCadAddInsBlockM = (tfCadAddInsBlockM)GetProcAddress( ghLibInst, "CadAddInsBlockM" );
	  if (pfCadAddInsBlockM){
		return (*pfCadAddInsBlockM)(hDwg, idBlock, X, Y, Z, Scal, Angle, NumCols, NumRows, ColDist, RowDist);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadInsBlockGetBlockID (VHANDLE hEnt)
	{
	  tfCadInsBlockGetBlockID pfCadInsBlockGetBlockID;
	  pfCadInsBlockGetBlockID = (tfCadInsBlockGetBlockID)GetProcAddress( ghLibInst, "CadInsBlockGetBlockID" );
	  if (pfCadInsBlockGetBlockID){
		return (*pfCadInsBlockGetBlockID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutBlockID (VHANDLE hEnt, IDOBJ Id)
	{
	  tfCadInsBlockPutBlockID pfCadInsBlockPutBlockID;
	  pfCadInsBlockPutBlockID = (tfCadInsBlockPutBlockID)GetProcAddress( ghLibInst, "CadInsBlockPutBlockID" );
	  if (pfCadInsBlockPutBlockID){
		(*pfCadInsBlockPutBlockID)(hEnt, Id);
	  }
	}


	//--------------
	double CADAPI CadInsBlockGetX (VHANDLE hEnt)
	{
	  tfCadInsBlockGetX pfCadInsBlockGetX;
	  pfCadInsBlockGetX = (tfCadInsBlockGetX)GetProcAddress( ghLibInst, "CadInsBlockGetX" );
	  if (pfCadInsBlockGetX){
		return (*pfCadInsBlockGetX)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutX (VHANDLE hEnt, double X)
	{
	  tfCadInsBlockPutX pfCadInsBlockPutX;
	  pfCadInsBlockPutX = (tfCadInsBlockPutX)GetProcAddress( ghLibInst, "CadInsBlockPutX" );
	  if (pfCadInsBlockPutX){
		(*pfCadInsBlockPutX)(hEnt, X);
	  }
	}


	//--------------
	double CADAPI CadInsBlockGetY (VHANDLE hEnt)
	{
	  tfCadInsBlockGetY pfCadInsBlockGetY;
	  pfCadInsBlockGetY = (tfCadInsBlockGetY)GetProcAddress( ghLibInst, "CadInsBlockGetY" );
	  if (pfCadInsBlockGetY){
		return (*pfCadInsBlockGetY)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutY (VHANDLE hEnt, double Y)
	{
	  tfCadInsBlockPutY pfCadInsBlockPutY;
	  pfCadInsBlockPutY = (tfCadInsBlockPutY)GetProcAddress( ghLibInst, "CadInsBlockPutY" );
	  if (pfCadInsBlockPutY){
		(*pfCadInsBlockPutY)(hEnt, Y);
	  }
	}


	//--------------
	double CADAPI CadInsBlockGetZ (VHANDLE hEnt)
	{
	  tfCadInsBlockGetZ pfCadInsBlockGetZ;
	  pfCadInsBlockGetZ = (tfCadInsBlockGetZ)GetProcAddress( ghLibInst, "CadInsBlockGetZ" );
	  if (pfCadInsBlockGetZ){
		return (*pfCadInsBlockGetZ)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutZ (VHANDLE hEnt, double Z)
	{
	  tfCadInsBlockPutZ pfCadInsBlockPutZ;
	  pfCadInsBlockPutZ = (tfCadInsBlockPutZ)GetProcAddress( ghLibInst, "CadInsBlockPutZ" );
	  if (pfCadInsBlockPutZ){
		(*pfCadInsBlockPutZ)(hEnt, Z);
	  }
	}


	//--------------
	void CADAPI CadInsBlockGetPoint (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadInsBlockGetPoint pfCadInsBlockGetPoint;
	  pfCadInsBlockGetPoint = (tfCadInsBlockGetPoint)GetProcAddress( ghLibInst, "CadInsBlockGetPoint" );
	  if (pfCadInsBlockGetPoint){
		(*pfCadInsBlockGetPoint)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadInsBlockPutPoint (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadInsBlockPutPoint pfCadInsBlockPutPoint;
	  pfCadInsBlockPutPoint = (tfCadInsBlockPutPoint)GetProcAddress( ghLibInst, "CadInsBlockPutPoint" );
	  if (pfCadInsBlockPutPoint){
		(*pfCadInsBlockPutPoint)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	double CADAPI CadInsBlockGetScale (VHANDLE hEnt)
	{
	  tfCadInsBlockGetScale pfCadInsBlockGetScale;
	  pfCadInsBlockGetScale = (tfCadInsBlockGetScale)GetProcAddress( ghLibInst, "CadInsBlockGetScale" );
	  if (pfCadInsBlockGetScale){
		return (*pfCadInsBlockGetScale)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutScale (VHANDLE hEnt, double Scal)
	{
	  tfCadInsBlockPutScale pfCadInsBlockPutScale;
	  pfCadInsBlockPutScale = (tfCadInsBlockPutScale)GetProcAddress( ghLibInst, "CadInsBlockPutScale" );
	  if (pfCadInsBlockPutScale){
		(*pfCadInsBlockPutScale)(hEnt, Scal);
	  }
	}


	//--------------
	double CADAPI CadInsBlockGetScaleX (VHANDLE hEnt)
	{
	  tfCadInsBlockGetScaleX pfCadInsBlockGetScaleX;
	  pfCadInsBlockGetScaleX = (tfCadInsBlockGetScaleX)GetProcAddress( ghLibInst, "CadInsBlockGetScaleX" );
	  if (pfCadInsBlockGetScaleX){
		return (*pfCadInsBlockGetScaleX)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutScaleX (VHANDLE hEnt, double Sx)
	{
	  tfCadInsBlockPutScaleX pfCadInsBlockPutScaleX;
	  pfCadInsBlockPutScaleX = (tfCadInsBlockPutScaleX)GetProcAddress( ghLibInst, "CadInsBlockPutScaleX" );
	  if (pfCadInsBlockPutScaleX){
		(*pfCadInsBlockPutScaleX)(hEnt, Sx);
	  }
	}


	//--------------
	double CADAPI CadInsBlockGetScaleY (VHANDLE hEnt)
	{
	  tfCadInsBlockGetScaleY pfCadInsBlockGetScaleY;
	  pfCadInsBlockGetScaleY = (tfCadInsBlockGetScaleY)GetProcAddress( ghLibInst, "CadInsBlockGetScaleY" );
	  if (pfCadInsBlockGetScaleY){
		return (*pfCadInsBlockGetScaleY)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutScaleY (VHANDLE hEnt, double Sy)
	{
	  tfCadInsBlockPutScaleY pfCadInsBlockPutScaleY;
	  pfCadInsBlockPutScaleY = (tfCadInsBlockPutScaleY)GetProcAddress( ghLibInst, "CadInsBlockPutScaleY" );
	  if (pfCadInsBlockPutScaleY){
		(*pfCadInsBlockPutScaleY)(hEnt, Sy);
	  }
	}


	//--------------
	double CADAPI CadInsBlockGetScaleZ (VHANDLE hEnt)
	{
	  tfCadInsBlockGetScaleZ pfCadInsBlockGetScaleZ;
	  pfCadInsBlockGetScaleZ = (tfCadInsBlockGetScaleZ)GetProcAddress( ghLibInst, "CadInsBlockGetScaleZ" );
	  if (pfCadInsBlockGetScaleZ){
		return (*pfCadInsBlockGetScaleZ)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutScaleZ (VHANDLE hEnt, double Sz)
	{
	  tfCadInsBlockPutScaleZ pfCadInsBlockPutScaleZ;
	  pfCadInsBlockPutScaleZ = (tfCadInsBlockPutScaleZ)GetProcAddress( ghLibInst, "CadInsBlockPutScaleZ" );
	  if (pfCadInsBlockPutScaleZ){
		(*pfCadInsBlockPutScaleZ)(hEnt, Sz);
	  }
	}


	//--------------
	double CADAPI CadInsBlockGetAngle (VHANDLE hEnt)
	{
	  tfCadInsBlockGetAngle pfCadInsBlockGetAngle;
	  pfCadInsBlockGetAngle = (tfCadInsBlockGetAngle)GetProcAddress( ghLibInst, "CadInsBlockGetAngle" );
	  if (pfCadInsBlockGetAngle){
		return (*pfCadInsBlockGetAngle)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutAngle (VHANDLE hEnt, double Angle)
	{
	  tfCadInsBlockPutAngle pfCadInsBlockPutAngle;
	  pfCadInsBlockPutAngle = (tfCadInsBlockPutAngle)GetProcAddress( ghLibInst, "CadInsBlockPutAngle" );
	  if (pfCadInsBlockPutAngle){
		(*pfCadInsBlockPutAngle)(hEnt, Angle);
	  }
	}


	//--------------
	UINT CADAPI CadInsBlockGetNumRows (VHANDLE hEnt)
	{
	  tfCadInsBlockGetNumRows pfCadInsBlockGetNumRows;
	  pfCadInsBlockGetNumRows = (tfCadInsBlockGetNumRows)GetProcAddress( ghLibInst, "CadInsBlockGetNumRows" );
	  if (pfCadInsBlockGetNumRows){
		return (*pfCadInsBlockGetNumRows)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutNumRows (VHANDLE hEnt, UINT NumRows)
	{
	  tfCadInsBlockPutNumRows pfCadInsBlockPutNumRows;
	  pfCadInsBlockPutNumRows = (tfCadInsBlockPutNumRows)GetProcAddress( ghLibInst, "CadInsBlockPutNumRows" );
	  if (pfCadInsBlockPutNumRows){
		(*pfCadInsBlockPutNumRows)(hEnt, NumRows);
	  }
	}


	//--------------
	UINT CADAPI CadInsBlockGetNumCols (VHANDLE hEnt)
	{
	  tfCadInsBlockGetNumCols pfCadInsBlockGetNumCols;
	  pfCadInsBlockGetNumCols = (tfCadInsBlockGetNumCols)GetProcAddress( ghLibInst, "CadInsBlockGetNumCols" );
	  if (pfCadInsBlockGetNumCols){
		return (*pfCadInsBlockGetNumCols)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutNumCols (VHANDLE hEnt, UINT NumCols)
	{
	  tfCadInsBlockPutNumCols pfCadInsBlockPutNumCols;
	  pfCadInsBlockPutNumCols = (tfCadInsBlockPutNumCols)GetProcAddress( ghLibInst, "CadInsBlockPutNumCols" );
	  if (pfCadInsBlockPutNumCols){
		(*pfCadInsBlockPutNumCols)(hEnt, NumCols);
	  }
	}


	//--------------
	double CADAPI CadInsBlockGetRowDist (VHANDLE hEnt)
	{
	  tfCadInsBlockGetRowDist pfCadInsBlockGetRowDist;
	  pfCadInsBlockGetRowDist = (tfCadInsBlockGetRowDist)GetProcAddress( ghLibInst, "CadInsBlockGetRowDist" );
	  if (pfCadInsBlockGetRowDist){
		return (*pfCadInsBlockGetRowDist)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutRowDist (VHANDLE hEnt, double RowDist)
	{
	  tfCadInsBlockPutRowDist pfCadInsBlockPutRowDist;
	  pfCadInsBlockPutRowDist = (tfCadInsBlockPutRowDist)GetProcAddress( ghLibInst, "CadInsBlockPutRowDist" );
	  if (pfCadInsBlockPutRowDist){
		(*pfCadInsBlockPutRowDist)(hEnt, RowDist);
	  }
	}


	//--------------
	double CADAPI CadInsBlockGetColDist (VHANDLE hEnt)
	{
	  tfCadInsBlockGetColDist pfCadInsBlockGetColDist;
	  pfCadInsBlockGetColDist = (tfCadInsBlockGetColDist)GetProcAddress( ghLibInst, "CadInsBlockGetColDist" );
	  if (pfCadInsBlockGetColDist){
		return (*pfCadInsBlockGetColDist)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadInsBlockPutColDist (VHANDLE hEnt, double ColDist)
	{
	  tfCadInsBlockPutColDist pfCadInsBlockPutColDist;
	  pfCadInsBlockPutColDist = (tfCadInsBlockPutColDist)GetProcAddress( ghLibInst, "CadInsBlockPutColDist" );
	  if (pfCadInsBlockPutColDist){
		(*pfCadInsBlockPutColDist)(hEnt, ColDist);
	  }
	}


	//--------------
	BOOL CADAPI CadInsBlockHasAttribs (VHANDLE hEnt)
	{
	  tfCadInsBlockHasAttribs pfCadInsBlockHasAttribs;
	  pfCadInsBlockHasAttribs = (tfCadInsBlockHasAttribs)GetProcAddress( ghLibInst, "CadInsBlockHasAttribs" );
	  if (pfCadInsBlockHasAttribs){
		return (*pfCadInsBlockHasAttribs)(hEnt);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadInsBlockGetFirstAtt (VHANDLE hEnt)
	{
	  tfCadInsBlockGetFirstAtt pfCadInsBlockGetFirstAtt;
	  pfCadInsBlockGetFirstAtt = (tfCadInsBlockGetFirstAtt)GetProcAddress( ghLibInst, "CadInsBlockGetFirstAtt" );
	  if (pfCadInsBlockGetFirstAtt){
		return (*pfCadInsBlockGetFirstAtt)(hEnt);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadInsBlockGetNextAtt (VHANDLE hEnt, VHANDLE hAtt)
	{
	  tfCadInsBlockGetNextAtt pfCadInsBlockGetNextAtt;
	  pfCadInsBlockGetNextAtt = (tfCadInsBlockGetNextAtt)GetProcAddress( ghLibInst, "CadInsBlockGetNextAtt" );
	  if (pfCadInsBlockGetNextAtt){
		return (*pfCadInsBlockGetNextAtt)(hEnt, hAtt);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddAttrib (VDWG hDwg, LPCTSTR szTag, LPCTSTR szDefValue, double X, double Y, double Z)
	{
	  tfCadAddAttrib pfCadAddAttrib;
	  pfCadAddAttrib = (tfCadAddAttrib)GetProcAddress( ghLibInst, "CadAddAttrib" );
	  if (pfCadAddAttrib){
		return (*pfCadAddAttrib)(hDwg, szTag, szDefValue, X, Y, Z);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadAttGetStyleID (VHANDLE hEnt)
	{
	  tfCadAttGetStyleID pfCadAttGetStyleID;
	  pfCadAttGetStyleID = (tfCadAttGetStyleID)GetProcAddress( ghLibInst, "CadAttGetStyleID" );
	  if (pfCadAttGetStyleID){
		return (*pfCadAttGetStyleID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadAttPutStyleID (VHANDLE hEnt, IDOBJ Id)
	{
	  tfCadAttPutStyleID pfCadAttPutStyleID;
	  pfCadAttPutStyleID = (tfCadAttPutStyleID)GetProcAddress( ghLibInst, "CadAttPutStyleID" );
	  if (pfCadAttPutStyleID){
		(*pfCadAttPutStyleID)(hEnt, Id);
	  }
	}


	//--------------
	void CADAPI CadAttGetPoint (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadAttGetPoint pfCadAttGetPoint;
	  pfCadAttGetPoint = (tfCadAttGetPoint)GetProcAddress( ghLibInst, "CadAttGetPoint" );
	  if (pfCadAttGetPoint){
		(*pfCadAttGetPoint)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadAttPutPoint (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadAttPutPoint pfCadAttPutPoint;
	  pfCadAttPutPoint = (tfCadAttPutPoint)GetProcAddress( ghLibInst, "CadAttPutPoint" );
	  if (pfCadAttPutPoint){
		(*pfCadAttPutPoint)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	void CADAPI CadAttGetTag (VHANDLE hEnt, TCHAR* szText, UINT MaxChars)
	{
	  tfCadAttGetTag pfCadAttGetTag;
	  pfCadAttGetTag = (tfCadAttGetTag)GetProcAddress( ghLibInst, "CadAttGetTag" );
	  if (pfCadAttGetTag){
		(*pfCadAttGetTag)(hEnt, szText, MaxChars);
	  }
	}


	//--------------
	void CADAPI CadAttPutTag (VHANDLE hEnt, LPCTSTR szText)
	{
	  tfCadAttPutTag pfCadAttPutTag;
	  pfCadAttPutTag = (tfCadAttPutTag)GetProcAddress( ghLibInst, "CadAttPutTag" );
	  if (pfCadAttPutTag){
		(*pfCadAttPutTag)(hEnt, szText);
	  }
	}


	//--------------
	void CADAPI CadAttGetPrompt (VHANDLE hEnt, TCHAR* szText, UINT MaxChars)
	{
	  tfCadAttGetPrompt pfCadAttGetPrompt;
	  pfCadAttGetPrompt = (tfCadAttGetPrompt)GetProcAddress( ghLibInst, "CadAttGetPrompt" );
	  if (pfCadAttGetPrompt){
		(*pfCadAttGetPrompt)(hEnt, szText, MaxChars);
	  }
	}


	//--------------
	void CADAPI CadAttPutPrompt (VHANDLE hEnt, LPCTSTR szText)
	{
	  tfCadAttPutPrompt pfCadAttPutPrompt;
	  pfCadAttPutPrompt = (tfCadAttPutPrompt)GetProcAddress( ghLibInst, "CadAttPutPrompt" );
	  if (pfCadAttPutPrompt){
		(*pfCadAttPutPrompt)(hEnt, szText);
	  }
	}


	//--------------
	void CADAPI CadAttGetDefValue (VHANDLE hEnt, TCHAR* szText, UINT MaxChars)
	{
	  tfCadAttGetDefValue pfCadAttGetDefValue;
	  pfCadAttGetDefValue = (tfCadAttGetDefValue)GetProcAddress( ghLibInst, "CadAttGetDefValue" );
	  if (pfCadAttGetDefValue){
		(*pfCadAttGetDefValue)(hEnt, szText, MaxChars);
	  }
	}


	//--------------
	void CADAPI CadAttPutDefValue (VHANDLE hEnt, LPCTSTR szText)
	{
	  tfCadAttPutDefValue pfCadAttPutDefValue;
	  pfCadAttPutDefValue = (tfCadAttPutDefValue)GetProcAddress( ghLibInst, "CadAttPutDefValue" );
	  if (pfCadAttPutDefValue){
		(*pfCadAttPutDefValue)(hEnt, szText);
	  }
	}


	//--------------
	void CADAPI CadAttGetValue (VHANDLE hEnt, TCHAR* szText, UINT MaxChars)
	{
	  tfCadAttGetValue pfCadAttGetValue;
	  pfCadAttGetValue = (tfCadAttGetValue)GetProcAddress( ghLibInst, "CadAttGetValue" );
	  if (pfCadAttGetValue){
		(*pfCadAttGetValue)(hEnt, szText, MaxChars);
	  }
	}


	//--------------
	void CADAPI CadAttPutValue (VHANDLE hEnt, LPCTSTR szText)
	{
	  tfCadAttPutValue pfCadAttPutValue;
	  pfCadAttPutValue = (tfCadAttPutValue)GetProcAddress( ghLibInst, "CadAttPutValue" );
	  if (pfCadAttPutValue){
		(*pfCadAttPutValue)(hEnt, szText);
	  }
	}


	//--------------
	double CADAPI CadAttGetAngle (VHANDLE hEnt)
	{
	  tfCadAttGetAngle pfCadAttGetAngle;
	  pfCadAttGetAngle = (tfCadAttGetAngle)GetProcAddress( ghLibInst, "CadAttGetAngle" );
	  if (pfCadAttGetAngle){
		return (*pfCadAttGetAngle)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadAttPutAngle (VHANDLE hEnt, double Angle)
	{
	  tfCadAttPutAngle pfCadAttPutAngle;
	  pfCadAttPutAngle = (tfCadAttPutAngle)GetProcAddress( ghLibInst, "CadAttPutAngle" );
	  if (pfCadAttPutAngle){
		(*pfCadAttPutAngle)(hEnt, Angle);
	  }
	}


	//--------------
	double CADAPI CadAttGetHeight (VHANDLE hEnt)
	{
	  tfCadAttGetHeight pfCadAttGetHeight;
	  pfCadAttGetHeight = (tfCadAttGetHeight)GetProcAddress( ghLibInst, "CadAttGetHeight" );
	  if (pfCadAttGetHeight){
		return (*pfCadAttGetHeight)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadAttPutHeight (VHANDLE hEnt, double Height)
	{
	  tfCadAttPutHeight pfCadAttPutHeight;
	  pfCadAttPutHeight = (tfCadAttPutHeight)GetProcAddress( ghLibInst, "CadAttPutHeight" );
	  if (pfCadAttPutHeight){
		(*pfCadAttPutHeight)(hEnt, Height);
	  }
	}


	//--------------
	double CADAPI CadAttGetWidth (VHANDLE hEnt)
	{
	  tfCadAttGetWidth pfCadAttGetWidth;
	  pfCadAttGetWidth = (tfCadAttGetWidth)GetProcAddress( ghLibInst, "CadAttGetWidth" );
	  if (pfCadAttGetWidth){
		return (*pfCadAttGetWidth)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadAttPutWidth (VHANDLE hEnt, double Width)
	{
	  tfCadAttPutWidth pfCadAttPutWidth;
	  pfCadAttPutWidth = (tfCadAttPutWidth)GetProcAddress( ghLibInst, "CadAttPutWidth" );
	  if (pfCadAttPutWidth){
		(*pfCadAttPutWidth)(hEnt, Width);
	  }
	}


	//--------------
	double CADAPI CadAttGetOblique (VHANDLE hEnt)
	{
	  tfCadAttGetOblique pfCadAttGetOblique;
	  pfCadAttGetOblique = (tfCadAttGetOblique)GetProcAddress( ghLibInst, "CadAttGetOblique" );
	  if (pfCadAttGetOblique){
		return (*pfCadAttGetOblique)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadAttPutOblique (VHANDLE hEnt, double Angle)
	{
	  tfCadAttPutOblique pfCadAttPutOblique;
	  pfCadAttPutOblique = (tfCadAttPutOblique)GetProcAddress( ghLibInst, "CadAttPutOblique" );
	  if (pfCadAttPutOblique){
		(*pfCadAttPutOblique)(hEnt, Angle);
	  }
	}


	//--------------
	int CADAPI CadAttGetAlign (VHANDLE hEnt)
	{
	  tfCadAttGetAlign pfCadAttGetAlign;
	  pfCadAttGetAlign = (tfCadAttGetAlign)GetProcAddress( ghLibInst, "CadAttGetAlign" );
	  if (pfCadAttGetAlign){
		return (*pfCadAttGetAlign)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadAttPutAlign (VHANDLE hEnt, int Align)
	{
	  tfCadAttPutAlign pfCadAttPutAlign;
	  pfCadAttPutAlign = (tfCadAttPutAlign)GetProcAddress( ghLibInst, "CadAttPutAlign" );
	  if (pfCadAttPutAlign){
		(*pfCadAttPutAlign)(hEnt, Align);
	  }
	}


	//--------------
	BOOL CADAPI CadAttGetBackward (VHANDLE hEnt)
	{
	  tfCadAttGetBackward pfCadAttGetBackward;
	  pfCadAttGetBackward = (tfCadAttGetBackward)GetProcAddress( ghLibInst, "CadAttGetBackward" );
	  if (pfCadAttGetBackward){
		return (*pfCadAttGetBackward)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadAttPutBackward (VHANDLE hEnt, BOOL bBackward)
	{
	  tfCadAttPutBackward pfCadAttPutBackward;
	  pfCadAttPutBackward = (tfCadAttPutBackward)GetProcAddress( ghLibInst, "CadAttPutBackward" );
	  if (pfCadAttPutBackward){
		(*pfCadAttPutBackward)(hEnt, bBackward);
	  }
	}


	//--------------
	BOOL CADAPI CadAttGetUpsideDown (VHANDLE hEnt)
	{
	  tfCadAttGetUpsideDown pfCadAttGetUpsideDown;
	  pfCadAttGetUpsideDown = (tfCadAttGetUpsideDown)GetProcAddress( ghLibInst, "CadAttGetUpsideDown" );
	  if (pfCadAttGetUpsideDown){
		return (*pfCadAttGetUpsideDown)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadAttPutUpsideDown (VHANDLE hEnt, BOOL bUpsideDown)
	{
	  tfCadAttPutUpsideDown pfCadAttPutUpsideDown;
	  pfCadAttPutUpsideDown = (tfCadAttPutUpsideDown)GetProcAddress( ghLibInst, "CadAttPutUpsideDown" );
	  if (pfCadAttPutUpsideDown){
		(*pfCadAttPutUpsideDown)(hEnt, bUpsideDown);
	  }
	}


	//--------------
	int CADAPI CadAttGetMode (VHANDLE hEnt)
	{
	  tfCadAttGetMode pfCadAttGetMode;
	  pfCadAttGetMode = (tfCadAttGetMode)GetProcAddress( ghLibInst, "CadAttGetMode" );
	  if (pfCadAttGetMode){
		return (*pfCadAttGetMode)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadAttPutMode (VHANDLE hEnt, int Mode)
	{
	  tfCadAttPutMode pfCadAttPutMode;
	  pfCadAttPutMode = (tfCadAttPutMode)GetProcAddress( ghLibInst, "CadAttPutMode" );
	  if (pfCadAttPutMode){
		(*pfCadAttPutMode)(hEnt, Mode);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddImage (VDWG hDwg, LPCTSTR szFileName, double X, double Y, double Z, double Scal)
	{
	  tfCadAddImage pfCadAddImage;
	  pfCadAddImage = (tfCadAddImage)GetProcAddress( ghLibInst, "CadAddImage" );
	  if (pfCadAddImage){
		return (*pfCadAddImage)(hDwg, szFileName, X, Y, Z, Scal);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddImagePlace (VDWG hDwg, int Id, int Width, int Height, double X, double Y, double Z, double Scal)
	{
	  tfCadAddImagePlace pfCadAddImagePlace;
	  pfCadAddImagePlace = (tfCadAddImagePlace)GetProcAddress( ghLibInst, "CadAddImagePlace" );
	  if (pfCadAddImagePlace){
		return (*pfCadAddImagePlace)(hDwg, Id, Width, Height, X, Y, Z, Scal);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadImageGetFile (VHANDLE hEnt, TCHAR* szFileName)
	{
	  tfCadImageGetFile pfCadImageGetFile;
	  pfCadImageGetFile = (tfCadImageGetFile)GetProcAddress( ghLibInst, "CadImageGetFile" );
	  if (pfCadImageGetFile){
		(*pfCadImageGetFile)(hEnt, szFileName);
	  }
	}


	//--------------
	void CADAPI CadImagePutFile (VHANDLE hEnt, LPCTSTR szFileName)
	{
	  tfCadImagePutFile pfCadImagePutFile;
	  pfCadImagePutFile = (tfCadImagePutFile)GetProcAddress( ghLibInst, "CadImagePutFile" );
	  if (pfCadImagePutFile){
		(*pfCadImagePutFile)(hEnt, szFileName);
	  }
	}


	//--------------
	double CADAPI CadImageGetX (VHANDLE hEnt)
	{
	  tfCadImageGetX pfCadImageGetX;
	  pfCadImageGetX = (tfCadImageGetX)GetProcAddress( ghLibInst, "CadImageGetX" );
	  if (pfCadImageGetX){
		return (*pfCadImageGetX)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadImagePutX (VHANDLE hEnt, double X)
	{
	  tfCadImagePutX pfCadImagePutX;
	  pfCadImagePutX = (tfCadImagePutX)GetProcAddress( ghLibInst, "CadImagePutX" );
	  if (pfCadImagePutX){
		(*pfCadImagePutX)(hEnt, X);
	  }
	}


	//--------------
	double CADAPI CadImageGetY (VHANDLE hEnt)
	{
	  tfCadImageGetY pfCadImageGetY;
	  pfCadImageGetY = (tfCadImageGetY)GetProcAddress( ghLibInst, "CadImageGetY" );
	  if (pfCadImageGetY){
		return (*pfCadImageGetY)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadImagePutY (VHANDLE hEnt, double Y)
	{
	  tfCadImagePutY pfCadImagePutY;
	  pfCadImagePutY = (tfCadImagePutY)GetProcAddress( ghLibInst, "CadImagePutY" );
	  if (pfCadImagePutY){
		(*pfCadImagePutY)(hEnt, Y);
	  }
	}


	//--------------
	double CADAPI CadImageGetZ (VHANDLE hEnt)
	{
	  tfCadImageGetZ pfCadImageGetZ;
	  pfCadImageGetZ = (tfCadImageGetZ)GetProcAddress( ghLibInst, "CadImageGetZ" );
	  if (pfCadImageGetZ){
		return (*pfCadImageGetZ)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadImagePutZ (VHANDLE hEnt, double Z)
	{
	  tfCadImagePutZ pfCadImagePutZ;
	  pfCadImagePutZ = (tfCadImagePutZ)GetProcAddress( ghLibInst, "CadImagePutZ" );
	  if (pfCadImagePutZ){
		(*pfCadImagePutZ)(hEnt, Z);
	  }
	}


	//--------------
	void CADAPI CadImageGetPoint (VHANDLE hEnt, double* pX, double* pY, double* pZ)
	{
	  tfCadImageGetPoint pfCadImageGetPoint;
	  pfCadImageGetPoint = (tfCadImageGetPoint)GetProcAddress( ghLibInst, "CadImageGetPoint" );
	  if (pfCadImageGetPoint){
		(*pfCadImageGetPoint)(hEnt, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadImagePutPoint (VHANDLE hEnt, double X, double Y, double Z)
	{
	  tfCadImagePutPoint pfCadImagePutPoint;
	  pfCadImagePutPoint = (tfCadImagePutPoint)GetProcAddress( ghLibInst, "CadImagePutPoint" );
	  if (pfCadImagePutPoint){
		(*pfCadImagePutPoint)(hEnt, X, Y, Z);
	  }
	}


	//--------------
	double CADAPI CadImageGetScale (VHANDLE hEnt)
	{
	  tfCadImageGetScale pfCadImageGetScale;
	  pfCadImageGetScale = (tfCadImageGetScale)GetProcAddress( ghLibInst, "CadImageGetScale" );
	  if (pfCadImageGetScale){
		return (*pfCadImageGetScale)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadImagePutScale (VHANDLE hEnt, double Scal)
	{
	  tfCadImagePutScale pfCadImagePutScale;
	  pfCadImagePutScale = (tfCadImagePutScale)GetProcAddress( ghLibInst, "CadImagePutScale" );
	  if (pfCadImagePutScale){
		(*pfCadImagePutScale)(hEnt, Scal);
	  }
	}


	//--------------
	double CADAPI CadImageGetScaleX (VHANDLE hEnt)
	{
	  tfCadImageGetScaleX pfCadImageGetScaleX;
	  pfCadImageGetScaleX = (tfCadImageGetScaleX)GetProcAddress( ghLibInst, "CadImageGetScaleX" );
	  if (pfCadImageGetScaleX){
		return (*pfCadImageGetScaleX)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadImagePutScaleX (VHANDLE hEnt, double Sx)
	{
	  tfCadImagePutScaleX pfCadImagePutScaleX;
	  pfCadImagePutScaleX = (tfCadImagePutScaleX)GetProcAddress( ghLibInst, "CadImagePutScaleX" );
	  if (pfCadImagePutScaleX){
		(*pfCadImagePutScaleX)(hEnt, Sx);
	  }
	}


	//--------------
	double CADAPI CadImageGetScaleY (VHANDLE hEnt)
	{
	  tfCadImageGetScaleY pfCadImageGetScaleY;
	  pfCadImageGetScaleY = (tfCadImageGetScaleY)GetProcAddress( ghLibInst, "CadImageGetScaleY" );
	  if (pfCadImageGetScaleY){
		return (*pfCadImageGetScaleY)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadImagePutScaleY (VHANDLE hEnt, double Sy)
	{
	  tfCadImagePutScaleY pfCadImagePutScaleY;
	  pfCadImagePutScaleY = (tfCadImagePutScaleY)GetProcAddress( ghLibInst, "CadImagePutScaleY" );
	  if (pfCadImagePutScaleY){
		(*pfCadImagePutScaleY)(hEnt, Sy);
	  }
	}


	//--------------
	void CADAPI CadImagePutSize (VHANDLE hEnt, int Width, int Height)
	{
	  tfCadImagePutSize pfCadImagePutSize;
	  pfCadImagePutSize = (tfCadImagePutSize)GetProcAddress( ghLibInst, "CadImagePutSize" );
	  if (pfCadImagePutSize){
		(*pfCadImagePutSize)(hEnt, Width, Height);
	  }
	}


	//--------------
	BOOL CADAPI CadImageGetTransparent (VHANDLE hEnt)
	{
	  tfCadImageGetTransparent pfCadImageGetTransparent;
	  pfCadImageGetTransparent = (tfCadImageGetTransparent)GetProcAddress( ghLibInst, "CadImageGetTransparent" );
	  if (pfCadImageGetTransparent){
		return (*pfCadImageGetTransparent)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadImagePutTransparent (VHANDLE hEnt, BOOL bTransp)
	{
	  tfCadImagePutTransparent pfCadImagePutTransparent;
	  pfCadImagePutTransparent = (tfCadImagePutTransparent)GetProcAddress( ghLibInst, "CadImagePutTransparent" );
	  if (pfCadImagePutTransparent){
		(*pfCadImagePutTransparent)(hEnt, bTransp);
	  }
	}


	//--------------
	COLORREF CADAPI CadImageGetTColor (VHANDLE hEnt)
	{
	  tfCadImageGetTColor pfCadImageGetTColor;
	  pfCadImageGetTColor = (tfCadImageGetTColor)GetProcAddress( ghLibInst, "CadImageGetTColor" );
	  if (pfCadImageGetTColor){
		return (*pfCadImageGetTColor)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadImagePutTColor (VHANDLE hEnt, COLORREF ColorRGB)
	{
	  tfCadImagePutTColor pfCadImagePutTColor;
	  pfCadImagePutTColor = (tfCadImagePutTColor)GetProcAddress( ghLibInst, "CadImagePutTColor" );
	  if (pfCadImagePutTColor){
		(*pfCadImagePutTColor)(hEnt, ColorRGB);
	  }
	}


	//--------------
	BOOL CADAPI CadAddHatchPoint (VDWG hDwg, double X, double Y)
	{
	  tfCadAddHatchPoint pfCadAddHatchPoint;
	  pfCadAddHatchPoint = (tfCadAddHatchPoint)GetProcAddress( ghLibInst, "CadAddHatchPoint" );
	  if (pfCadAddHatchPoint){
		return (*pfCadAddHatchPoint)(hDwg, X, Y);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadAddHatchPath (VDWG hDwg, VHANDLE hEnt)
	{
	  tfCadAddHatchPath pfCadAddHatchPath;
	  pfCadAddHatchPath = (tfCadAddHatchPath)GetProcAddress( ghLibInst, "CadAddHatchPath" );
	  if (pfCadAddHatchPath){
		return (*pfCadAddHatchPath)(hDwg, hEnt);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddHatch (VDWG hDwg, LPCTSTR szFileName, LPCTSTR szPatName, double Scal, double Angle)
	{
	  tfCadAddHatch pfCadAddHatch;
	  pfCadAddHatch = (tfCadAddHatch)GetProcAddress( ghLibInst, "CadAddHatch" );
	  if (pfCadAddHatch){
		return (*pfCadAddHatch)(hDwg, szFileName, szPatName, Scal, Angle);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadEngrave (VDWG hDwg, BOOL bSelected, LPCTSTR szBlockName, double Step, double Angle)
	{
	  tfCadEngrave pfCadEngrave;
	  pfCadEngrave = (tfCadEngrave)GetProcAddress( ghLibInst, "CadEngrave" );
	  if (pfCadEngrave){
		return (*pfCadEngrave)(hDwg, bSelected, szBlockName, Step, Angle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadHatchPutPattern (VHANDLE hEnt, LPCTSTR szFileName, LPCTSTR szPatName)
	{
	  tfCadHatchPutPattern pfCadHatchPutPattern;
	  pfCadHatchPutPattern = (tfCadHatchPutPattern)GetProcAddress( ghLibInst, "CadHatchPutPattern" );
	  if (pfCadHatchPutPattern){
		(*pfCadHatchPutPattern)(hEnt, szFileName, szPatName);
	  }
	}


	//--------------
	void CADAPI CadHatchGetName (VHANDLE hEnt, TCHAR* szName)
	{
	  tfCadHatchGetName pfCadHatchGetName;
	  pfCadHatchGetName = (tfCadHatchGetName)GetProcAddress( ghLibInst, "CadHatchGetName" );
	  if (pfCadHatchGetName){
		(*pfCadHatchGetName)(hEnt, szName);
	  }
	}


	//--------------
	UINT CADAPI CadHatchGetPattern (VHANDLE hEnt, TCHAR* szPattern)
	{
	  tfCadHatchGetPattern pfCadHatchGetPattern;
	  pfCadHatchGetPattern = (tfCadHatchGetPattern)GetProcAddress( ghLibInst, "CadHatchGetPattern" );
	  if (pfCadHatchGetPattern){
		return (*pfCadHatchGetPattern)(hEnt, szPattern);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadHatchPutScale (VHANDLE hEnt, double Scal)
	{
	  tfCadHatchPutScale pfCadHatchPutScale;
	  pfCadHatchPutScale = (tfCadHatchPutScale)GetProcAddress( ghLibInst, "CadHatchPutScale" );
	  if (pfCadHatchPutScale){
		(*pfCadHatchPutScale)(hEnt, Scal);
	  }
	}


	//--------------
	double CADAPI CadHatchGetScale (VHANDLE hEnt)
	{
	  tfCadHatchGetScale pfCadHatchGetScale;
	  pfCadHatchGetScale = (tfCadHatchGetScale)GetProcAddress( ghLibInst, "CadHatchGetScale" );
	  if (pfCadHatchGetScale){
		return (*pfCadHatchGetScale)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadHatchPutAngle (VHANDLE hEnt, double Angle)
	{
	  tfCadHatchPutAngle pfCadHatchPutAngle;
	  pfCadHatchPutAngle = (tfCadHatchPutAngle)GetProcAddress( ghLibInst, "CadHatchPutAngle" );
	  if (pfCadHatchPutAngle){
		(*pfCadHatchPutAngle)(hEnt, Angle);
	  }
	}


	//--------------
	double CADAPI CadHatchGetAngle (VHANDLE hEnt)
	{
	  tfCadHatchGetAngle pfCadHatchGetAngle;
	  pfCadHatchGetAngle = (tfCadHatchGetAngle)GetProcAddress( ghLibInst, "CadHatchGetAngle" );
	  if (pfCadHatchGetAngle){
		return (*pfCadHatchGetAngle)(hEnt);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadHatchGetSize (VHANDLE hEnt)
	{
	  tfCadHatchGetSize pfCadHatchGetSize;
	  pfCadHatchGetSize = (tfCadHatchGetSize)GetProcAddress( ghLibInst, "CadHatchGetSize" );
	  if (pfCadHatchGetSize){
		return (*pfCadHatchGetSize)(hEnt);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadAddDimPoint (UINT Index, double X, double Y, double Z)
	{
	  tfCadAddDimPoint pfCadAddDimPoint;
	  pfCadAddDimPoint = (tfCadAddDimPoint)GetProcAddress( ghLibInst, "CadAddDimPoint" );
	  if (pfCadAddDimPoint){
		return (*pfCadAddDimPoint)(Index, X, Y, Z);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddDim (VDWG hDwg, int DimType)
	{
	  tfCadAddDim pfCadAddDim;
	  pfCadAddDim = (tfCadAddDim)GetProcAddress( ghLibInst, "CadAddDim" );
	  if (pfCadAddDim){
		return (*pfCadAddDim)(hDwg, DimType);
	  }
	  return 0;
	}


	//--------------
	IDOBJ CADAPI CadDimGetStyleID (VHANDLE hEnt)
	{
	  tfCadDimGetStyleID pfCadDimGetStyleID;
	  pfCadDimGetStyleID = (tfCadDimGetStyleID)GetProcAddress( ghLibInst, "CadDimGetStyleID" );
	  if (pfCadDimGetStyleID){
		return (*pfCadDimGetStyleID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDimPutStyleID (VHANDLE hEnt, IDOBJ Id)
	{
	  tfCadDimPutStyleID pfCadDimPutStyleID;
	  pfCadDimPutStyleID = (tfCadDimPutStyleID)GetProcAddress( ghLibInst, "CadDimPutStyleID" );
	  if (pfCadDimPutStyleID){
		(*pfCadDimPutStyleID)(hEnt, Id);
	  }
	}


	//--------------
	void CADAPI CadDimPutText (VHANDLE hEnt, LPCTSTR szText)
	{
	  tfCadDimPutText pfCadDimPutText;
	  pfCadDimPutText = (tfCadDimPutText)GetProcAddress( ghLibInst, "CadDimPutText" );
	  if (pfCadDimPutText){
		(*pfCadDimPutText)(hEnt, szText);
	  }
	}


	//--------------
	void CADAPI CadDimGetText (VHANDLE hEnt, TCHAR* szText)
	{
	  tfCadDimGetText pfCadDimGetText;
	  pfCadDimGetText = (tfCadDimGetText)GetProcAddress( ghLibInst, "CadDimGetText" );
	  if (pfCadDimGetText){
		(*pfCadDimGetText)(hEnt, szText);
	  }
	}


	//--------------
	void CADAPI CadDimGetPoint (VHANDLE hEnt, int Index, double* pX, double* pY, double* pZ)
	{
	  tfCadDimGetPoint pfCadDimGetPoint;
	  pfCadDimGetPoint = (tfCadDimGetPoint)GetProcAddress( ghLibInst, "CadDimGetPoint" );
	  if (pfCadDimGetPoint){
		(*pfCadDimGetPoint)(hEnt, Index, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadDimPutPoint (VHANDLE hEnt, int Index, double X, double Y, double Z)
	{
	  tfCadDimPutPoint pfCadDimPutPoint;
	  pfCadDimPutPoint = (tfCadDimPutPoint)GetProcAddress( ghLibInst, "CadDimPutPoint" );
	  if (pfCadDimPutPoint){
		(*pfCadDimPutPoint)(hEnt, Index, X, Y, Z);
	  }
	}


	//--------------
	int CADAPI CadDimGetType (VHANDLE hEnt)
	{
	  tfCadDimGetType pfCadDimGetType;
	  pfCadDimGetType = (tfCadDimGetType)GetProcAddress( ghLibInst, "CadDimGetType" );
	  if (pfCadDimGetType){
		return (*pfCadDimGetType)(hEnt);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadDimGetValue (VHANDLE hEnt)
	{
	  tfCadDimGetValue pfCadDimGetValue;
	  pfCadDimGetValue = (tfCadDimGetValue)GetProcAddress( ghLibInst, "CadDimGetValue" );
	  if (pfCadDimGetValue){
		return (*pfCadDimGetValue)(hEnt);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddLeader (VDWG hDwg, LPCTSTR szText)
	{
	  tfCadAddLeader pfCadAddLeader;
	  pfCadAddLeader = (tfCadAddLeader)GetProcAddress( ghLibInst, "CadAddLeader" );
	  if (pfCadAddLeader){
		return (*pfCadAddLeader)(hDwg, szText);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadLeaderGetNumVers (VHANDLE hEnt)
	{
	  tfCadLeaderGetNumVers pfCadLeaderGetNumVers;
	  pfCadLeaderGetNumVers = (tfCadLeaderGetNumVers)GetProcAddress( ghLibInst, "CadLeaderGetNumVers" );
	  if (pfCadLeaderGetNumVers){
		return (*pfCadLeaderGetNumVers)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLeaderPutNumVers (VHANDLE hEnt, UINT nVers)
	{
	  tfCadLeaderPutNumVers pfCadLeaderPutNumVers;
	  pfCadLeaderPutNumVers = (tfCadLeaderPutNumVers)GetProcAddress( ghLibInst, "CadLeaderPutNumVers" );
	  if (pfCadLeaderPutNumVers){
		(*pfCadLeaderPutNumVers)(hEnt, nVers);
	  }
	}


	//--------------
	void CADAPI CadLeaderGetVer (VHANDLE hEnt, UINT iVer, double* pX, double* pY, double* pZ)
	{
	  tfCadLeaderGetVer pfCadLeaderGetVer;
	  pfCadLeaderGetVer = (tfCadLeaderGetVer)GetProcAddress( ghLibInst, "CadLeaderGetVer" );
	  if (pfCadLeaderGetVer){
		(*pfCadLeaderGetVer)(hEnt, iVer, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadLeaderPutVer (VHANDLE hEnt, UINT iVer, double X, double Y, double Z)
	{
	  tfCadLeaderPutVer pfCadLeaderPutVer;
	  pfCadLeaderPutVer = (tfCadLeaderPutVer)GetProcAddress( ghLibInst, "CadLeaderPutVer" );
	  if (pfCadLeaderPutVer){
		(*pfCadLeaderPutVer)(hEnt, iVer, X, Y, Z);
	  }
	}


	//--------------
	BOOL CADAPI CadLeaderGetSpline (VHANDLE hEnt)
	{
	  tfCadLeaderGetSpline pfCadLeaderGetSpline;
	  pfCadLeaderGetSpline = (tfCadLeaderGetSpline)GetProcAddress( ghLibInst, "CadLeaderGetSpline" );
	  if (pfCadLeaderGetSpline){
		return (*pfCadLeaderGetSpline)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLeaderPutSpline (VHANDLE hEnt, BOOL bSpline)
	{
	  tfCadLeaderPutSpline pfCadLeaderPutSpline;
	  pfCadLeaderPutSpline = (tfCadLeaderPutSpline)GetProcAddress( ghLibInst, "CadLeaderPutSpline" );
	  if (pfCadLeaderPutSpline){
		(*pfCadLeaderPutSpline)(hEnt, bSpline);
	  }
	}


	//--------------
	UINT CADAPI CadLeaderGetTextLen (VHANDLE hEnt)
	{
	  tfCadLeaderGetTextLen pfCadLeaderGetTextLen;
	  pfCadLeaderGetTextLen = (tfCadLeaderGetTextLen)GetProcAddress( ghLibInst, "CadLeaderGetTextLen" );
	  if (pfCadLeaderGetTextLen){
		return (*pfCadLeaderGetTextLen)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLeaderGetText (VHANDLE hEnt, TCHAR* szText, UINT MaxChars)
	{
	  tfCadLeaderGetText pfCadLeaderGetText;
	  pfCadLeaderGetText = (tfCadLeaderGetText)GetProcAddress( ghLibInst, "CadLeaderGetText" );
	  if (pfCadLeaderGetText){
		(*pfCadLeaderGetText)(hEnt, szText, MaxChars);
	  }
	}


	//--------------
	void CADAPI CadLeaderPutText (VHANDLE hEnt, LPCTSTR szText)
	{
	  tfCadLeaderPutText pfCadLeaderPutText;
	  pfCadLeaderPutText = (tfCadLeaderPutText)GetProcAddress( ghLibInst, "CadLeaderPutText" );
	  if (pfCadLeaderPutText){
		(*pfCadLeaderPutText)(hEnt, szText);
	  }
	}


	//--------------
	double CADAPI CadLeaderGetTextH (VHANDLE hEnt)
	{
	  tfCadLeaderGetTextH pfCadLeaderGetTextH;
	  pfCadLeaderGetTextH = (tfCadLeaderGetTextH)GetProcAddress( ghLibInst, "CadLeaderGetTextH" );
	  if (pfCadLeaderGetTextH){
		return (*pfCadLeaderGetTextH)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLeaderPutTextH (VHANDLE hEnt, double Height)
	{
	  tfCadLeaderPutTextH pfCadLeaderPutTextH;
	  pfCadLeaderPutTextH = (tfCadLeaderPutTextH)GetProcAddress( ghLibInst, "CadLeaderPutTextH" );
	  if (pfCadLeaderPutTextH){
		(*pfCadLeaderPutTextH)(hEnt, Height);
	  }
	}


	//--------------
	double CADAPI CadLeaderGetArrSize (VHANDLE hEnt)
	{
	  tfCadLeaderGetArrSize pfCadLeaderGetArrSize;
	  pfCadLeaderGetArrSize = (tfCadLeaderGetArrSize)GetProcAddress( ghLibInst, "CadLeaderGetArrSize" );
	  if (pfCadLeaderGetArrSize){
		return (*pfCadLeaderGetArrSize)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLeaderPutArrSize (VHANDLE hEnt, double Size)
	{
	  tfCadLeaderPutArrSize pfCadLeaderPutArrSize;
	  pfCadLeaderPutArrSize = (tfCadLeaderPutArrSize)GetProcAddress( ghLibInst, "CadLeaderPutArrSize" );
	  if (pfCadLeaderPutArrSize){
		(*pfCadLeaderPutArrSize)(hEnt, Size);
	  }
	}


	//--------------
	IDOBJ CADAPI CadLeaderGetTextStyleID (VHANDLE hEnt)
	{
	  tfCadLeaderGetTextStyleID pfCadLeaderGetTextStyleID;
	  pfCadLeaderGetTextStyleID = (tfCadLeaderGetTextStyleID)GetProcAddress( ghLibInst, "CadLeaderGetTextStyleID" );
	  if (pfCadLeaderGetTextStyleID){
		return (*pfCadLeaderGetTextStyleID)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadLeaderPutTextStyleID (VHANDLE hEnt, IDOBJ Id)
	{
	  tfCadLeaderPutTextStyleID pfCadLeaderPutTextStyleID;
	  pfCadLeaderPutTextStyleID = (tfCadLeaderPutTextStyleID)GetProcAddress( ghLibInst, "CadLeaderPutTextStyleID" );
	  if (pfCadLeaderPutTextStyleID){
		(*pfCadLeaderPutTextStyleID)(hEnt, Id);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddFace (VDWG hDwg)
	{
	  tfCadAddFace pfCadAddFace;
	  pfCadAddFace = (tfCadAddFace)GetProcAddress( ghLibInst, "CadAddFace" );
	  if (pfCadAddFace){
		return (*pfCadAddFace)(hDwg);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadFaceGetNumVers (VHANDLE hEnt)
	{
	  tfCadFaceGetNumVers pfCadFaceGetNumVers;
	  pfCadFaceGetNumVers = (tfCadFaceGetNumVers)GetProcAddress( ghLibInst, "CadFaceGetNumVers" );
	  if (pfCadFaceGetNumVers){
		return (*pfCadFaceGetNumVers)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadFaceGetVer (VHANDLE hEnt, UINT iVer, double* pX, double* pY, double* pZ)
	{
	  tfCadFaceGetVer pfCadFaceGetVer;
	  pfCadFaceGetVer = (tfCadFaceGetVer)GetProcAddress( ghLibInst, "CadFaceGetVer" );
	  if (pfCadFaceGetVer){
		(*pfCadFaceGetVer)(hEnt, iVer, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadFacePutVer (VHANDLE hEnt, UINT iVer, double X, double Y, double Z)
	{
	  tfCadFacePutVer pfCadFacePutVer;
	  pfCadFacePutVer = (tfCadFacePutVer)GetProcAddress( ghLibInst, "CadFacePutVer" );
	  if (pfCadFacePutVer){
		(*pfCadFacePutVer)(hEnt, iVer, X, Y, Z);
	  }
	}


	//--------------
	BOOL CADAPI CadFaceGetEdge (VHANDLE hEnt, UINT iEdge)
	{
	  tfCadFaceGetEdge pfCadFaceGetEdge;
	  pfCadFaceGetEdge = (tfCadFaceGetEdge)GetProcAddress( ghLibInst, "CadFaceGetEdge" );
	  if (pfCadFaceGetEdge){
		return (*pfCadFaceGetEdge)(hEnt, iEdge);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadFacePutEdge (VHANDLE hEnt, UINT iEdge, BOOL bVisible)
	{
	  tfCadFacePutEdge pfCadFacePutEdge;
	  pfCadFacePutEdge = (tfCadFacePutEdge)GetProcAddress( ghLibInst, "CadFacePutEdge" );
	  if (pfCadFacePutEdge){
		(*pfCadFacePutEdge)(hEnt, iEdge, bVisible);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddVport (VDWG hDwg, double X, double Y, double W, double H)
	{
	  tfCadAddVport pfCadAddVport;
	  pfCadAddVport = (tfCadAddVport)GetProcAddress( ghLibInst, "CadAddVport" );
	  if (pfCadAddVport){
		return (*pfCadAddVport)(hDwg, X, Y, W, H);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddCustom (VDWG hDwg, int CustType, void* pData, int nBytes)
	{
	  tfCadAddCustom pfCadAddCustom;
	  pfCadAddCustom = (tfCadAddCustom)GetProcAddress( ghLibInst, "CadAddCustom" );
	  if (pfCadAddCustom){
		return (*pfCadAddCustom)(hDwg, CustType, pData, nBytes);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadCustomPutOwner (VHANDLE hEnt, void* pObject)
	{
	  tfCadCustomPutOwner pfCadCustomPutOwner;
	  pfCadCustomPutOwner = (tfCadCustomPutOwner)GetProcAddress( ghLibInst, "CadCustomPutOwner" );
	  if (pfCadCustomPutOwner){
		(*pfCadCustomPutOwner)(hEnt, pObject);
	  }
	}


	//--------------
	DWORD CADAPI CadCustomGetOwner (VHANDLE hEnt)
	{
	  tfCadCustomGetOwner pfCadCustomGetOwner;
	  pfCadCustomGetOwner = (tfCadCustomGetOwner)GetProcAddress( ghLibInst, "CadCustomGetOwner" );
	  if (pfCadCustomGetOwner){
		return (*pfCadCustomGetOwner)(hEnt);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadCustomGetType (VHANDLE hEnt)
	{
	  tfCadCustomGetType pfCadCustomGetType;
	  pfCadCustomGetType = (tfCadCustomGetType)GetProcAddress( ghLibInst, "CadCustomGetType" );
	  if (pfCadCustomGetType){
		return (*pfCadCustomGetType)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadCustomPutData (VHANDLE hEnt, void* pData, int nBytes)
	{
	  tfCadCustomPutData pfCadCustomPutData;
	  pfCadCustomPutData = (tfCadCustomPutData)GetProcAddress( ghLibInst, "CadCustomPutData" );
	  if (pfCadCustomPutData){
		(*pfCadCustomPutData)(hEnt, pData, nBytes);
	  }
	}


	//--------------
	void CADAPI CadCustomGetData (VHANDLE hEnt, void* pData)
	{
	  tfCadCustomGetData pfCadCustomGetData;
	  pfCadCustomGetData = (tfCadCustomGetData)GetProcAddress( ghLibInst, "CadCustomGetData" );
	  if (pfCadCustomGetData){
		(*pfCadCustomGetData)(hEnt, pData);
	  }
	}


	//--------------
	int CADAPI CadCustomGetSize (VHANDLE hEnt)
	{
	  tfCadCustomGetSize pfCadCustomGetSize;
	  pfCadCustomGetSize = (tfCadCustomGetSize)GetProcAddress( ghLibInst, "CadCustomGetSize" );
	  if (pfCadCustomGetSize){
		return (*pfCadCustomGetSize)(hEnt);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadCustomGetDataPtr (VHANDLE hEnt)
	{
	  tfCadCustomGetDataPtr pfCadCustomGetDataPtr;
	  pfCadCustomGetDataPtr = (tfCadCustomGetDataPtr)GetProcAddress( ghLibInst, "CadCustomGetDataPtr" );
	  if (pfCadCustomGetDataPtr){
		return (*pfCadCustomGetDataPtr)(hEnt);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDrawSet (int Mode, int Value)
	{
	  tfCadDrawSet pfCadDrawSet;
	  pfCadDrawSet = (tfCadDrawSet)GetProcAddress( ghLibInst, "CadDrawSet" );
	  if (pfCadDrawSet){
		(*pfCadDrawSet)(Mode, Value);
	  }
	}


	//--------------
	HDC CADAPI CadDrawGetDC ()
	{
	  tfCadDrawGetDC pfCadDrawGetDC;
	  pfCadDrawGetDC = (tfCadDrawGetDC)GetProcAddress( ghLibInst, "CadDrawGetDC" );
	  if (pfCadDrawGetDC){
		return (*pfCadDrawGetDC)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDrawAddVertex (double X, double Y, double Z)
	{
	  tfCadDrawAddVertex pfCadDrawAddVertex;
	  pfCadDrawAddVertex = (tfCadDrawAddVertex)GetProcAddress( ghLibInst, "CadDrawAddVertex" );
	  if (pfCadDrawAddVertex){
		(*pfCadDrawAddVertex)(X, Y, Z);
	  }
	}


	//--------------
	int CADAPI CadDrawGenArc (double Xcen, double Ycen, double Zcen, double Radius, double AngStart, double AngArc, int nVers)
	{
	  tfCadDrawGenArc pfCadDrawGenArc;
	  pfCadDrawGenArc = (tfCadDrawGenArc)GetProcAddress( ghLibInst, "CadDrawGenArc" );
	  if (pfCadDrawGenArc){
		return (*pfCadDrawGenArc)(Xcen, Ycen, Zcen, Radius, AngStart, AngArc, nVers);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadDrawGenCircle (double X, double Y, double Z, double Radius, int nVers)
	{
	  tfCadDrawGenCircle pfCadDrawGenCircle;
	  pfCadDrawGenCircle = (tfCadDrawGenCircle)GetProcAddress( ghLibInst, "CadDrawGenCircle" );
	  if (pfCadDrawGenCircle){
		return (*pfCadDrawGenCircle)(X, Y, Z, Radius, nVers);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadDrawGenChar (double X, double Y, double Z, double Height, double Angle, double ScaleW, UINT UCode, LPCTSTR szFont, int nVers)
	{
	  tfCadDrawGenChar pfCadDrawGenChar;
	  pfCadDrawGenChar = (tfCadDrawGenChar)GetProcAddress( ghLibInst, "CadDrawGenChar" );
	  if (pfCadDrawGenChar){
		return (*pfCadDrawGenChar)(X, Y, Z, Height, Angle, ScaleW, UCode, szFont, nVers);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadDrawPolyline ()
	{
	  tfCadDrawPolyline pfCadDrawPolyline;
	  pfCadDrawPolyline = (tfCadDrawPolyline)GetProcAddress( ghLibInst, "CadDrawPolyline" );
	  if (pfCadDrawPolyline){
		(*pfCadDrawPolyline)();
	  }
	}


	//--------------
	void CADAPI CadDrawPolygon ()
	{
	  tfCadDrawPolygon pfCadDrawPolygon;
	  pfCadDrawPolygon = (tfCadDrawPolygon)GetProcAddress( ghLibInst, "CadDrawPolygon" );
	  if (pfCadDrawPolygon){
		(*pfCadDrawPolygon)();
	  }
	}


	//--------------
	void CADAPI CadDrawPolyPolygon (int* PlineSize, int nPline)
	{
	  tfCadDrawPolyPolygon pfCadDrawPolyPolygon;
	  pfCadDrawPolyPolygon = (tfCadDrawPolyPolygon)GetProcAddress( ghLibInst, "CadDrawPolyPolygon" );
	  if (pfCadDrawPolyPolygon){
		(*pfCadDrawPolyPolygon)(PlineSize, nPline);
	  }
	}


	//--------------
	void CADAPI CadDrawLine (double X1, double Y1, double Z1, double X2, double Y2, double Z2)
	{
	  tfCadDrawLine pfCadDrawLine;
	  pfCadDrawLine = (tfCadDrawLine)GetProcAddress( ghLibInst, "CadDrawLine" );
	  if (pfCadDrawLine){
		(*pfCadDrawLine)(X1, Y1, Z1, X2, Y2, Z2);
	  }
	}


	//--------------
	void CADAPI CadDrawPoint (double X, double Y, double Z, int PtMode, double PtSize)
	{
	  tfCadDrawPoint pfCadDrawPoint;
	  pfCadDrawPoint = (tfCadDrawPoint)GetProcAddress( ghLibInst, "CadDrawPoint" );
	  if (pfCadDrawPoint){
		(*pfCadDrawPoint)(X, Y, Z, PtMode, PtSize);
	  }
	}


	//--------------
	void CADAPI CadDrawText (VDWG hDwg, LPCTSTR szText, double X, double Y, double Z)
	{
	  tfCadDrawText pfCadDrawText;
	  pfCadDrawText = (tfCadDrawText)GetProcAddress( ghLibInst, "CadDrawText" );
	  if (pfCadDrawText){
		(*pfCadDrawText)(hDwg, szText, X, Y, Z);
	  }
	}


	//--------------
	void CADAPI CadDrawBlock (VDWG hDwg, VHANDLE hBlock, double X, double Y, double Z, double ScaleX, double ScaleY, double ScaleZ, double RotAngle)
	{
	  tfCadDrawBlock pfCadDrawBlock;
	  pfCadDrawBlock = (tfCadDrawBlock)GetProcAddress( ghLibInst, "CadDrawBlock" );
	  if (pfCadDrawBlock){
		(*pfCadDrawBlock)(hDwg, hBlock, X, Y, Z, ScaleX, ScaleY, ScaleZ, RotAngle);
	  }
	}


	//--------------
	void CADAPI CadDrawObject (double Xcen, double Ycen, double Zcen, double W, double H, F_DISPOWNERDRAW fnDraw, void* ptr)
	{
	  tfCadDrawObject pfCadDrawObject;
	  pfCadDrawObject = (tfCadDrawObject)GetProcAddress( ghLibInst, "CadDrawObject" );
	  if (pfCadDrawObject){
		(*pfCadDrawObject)(Xcen, Ycen, Zcen, W, H, fnDraw, ptr);
	  }
	}


	//--------------
	BOOL CADAPI CadAddCustProp (int IdProp, LPCTSTR szName, LPCTSTR szValue, int ValType)
	{
	  tfCadAddCustProp pfCadAddCustProp;
	  pfCadAddCustProp = (tfCadAddCustProp)GetProcAddress( ghLibInst, "CadAddCustProp" );
	  if (pfCadAddCustProp){
		return (*pfCadAddCustProp)(IdProp, szName, szValue, ValType);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadSetCustProp (int IdProp, LPCTSTR szValue)
	{
	  tfCadSetCustProp pfCadSetCustProp;
	  pfCadSetCustProp = (tfCadSetCustProp)GetProcAddress( ghLibInst, "CadSetCustProp" );
	  if (pfCadSetCustProp){
		return (*pfCadSetCustProp)(IdProp, szValue);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadSetCustPropMode (int IdProp, BOOL bReadOnly)
	{
	  tfCadSetCustPropMode pfCadSetCustPropMode;
	  pfCadSetCustPropMode = (tfCadSetCustPropMode)GetProcAddress( ghLibInst, "CadSetCustPropMode" );
	  if (pfCadSetCustPropMode){
		return (*pfCadSetCustPropMode)(IdProp, bReadOnly);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadAddCommand (VDWG hDwg, int Id, LPCTSTR szCmdName, LPCTSTR szAlias, HCURSOR hCurs, F_CCMD pFunc1, F_CDRAG pFunc2)
	{
	  tfCadAddCommand pfCadAddCommand;
	  pfCadAddCommand = (tfCadAddCommand)GetProcAddress( ghLibInst, "CadAddCommand" );
	  if (pfCadAddCommand){
		return (*pfCadAddCommand)(hDwg, Id, szCmdName, szAlias, hCurs, pFunc1, pFunc2);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadCmdPutData (VDWG hDwg, void* pData, int nBytes)
	{
	  tfCadCmdPutData pfCadCmdPutData;
	  pfCadCmdPutData = (tfCadCmdPutData)GetProcAddress( ghLibInst, "CadCmdPutData" );
	  if (pfCadCmdPutData){
		(*pfCadCmdPutData)(hDwg, pData, nBytes);
	  }
	}


	//--------------
	void CADAPI CadCmdGetData (VDWG hDwg, void* pData)
	{
	  tfCadCmdGetData pfCadCmdGetData;
	  pfCadCmdGetData = (tfCadCmdGetData)GetProcAddress( ghLibInst, "CadCmdGetData" );
	  if (pfCadCmdGetData){
		(*pfCadCmdGetData)(hDwg, pData);
	  }
	}


	//--------------
	int CADAPI CadCmdGetSize (VDWG hDwg)
	{
	  tfCadCmdGetSize pfCadCmdGetSize;
	  pfCadCmdGetSize = (tfCadCmdGetSize)GetProcAddress( ghLibInst, "CadCmdGetSize" );
	  if (pfCadCmdGetSize){
		return (*pfCadCmdGetSize)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadCmdPrompt (VDWG hDwg, LPCTSTR szText, LPCTSTR szDefaultVal)
	{
	  tfCadCmdPrompt pfCadCmdPrompt;
	  pfCadCmdPrompt = (tfCadCmdPrompt)GetProcAddress( ghLibInst, "CadCmdPrompt" );
	  if (pfCadCmdPrompt){
		(*pfCadCmdPrompt)(hDwg, szText, szDefaultVal);
	  }
	}


	//--------------
	void CADAPI CadCmdPromptAdd (VDWG hDwg, LPCTSTR szValue)
	{
	  tfCadCmdPromptAdd pfCadCmdPromptAdd;
	  pfCadCmdPromptAdd = (tfCadCmdPromptAdd)GetProcAddress( ghLibInst, "CadCmdPromptAdd" );
	  if (pfCadCmdPromptAdd){
		(*pfCadCmdPromptAdd)(hDwg, szValue);
	  }
	}


	//--------------
	int CADAPI CadCmdUserSelect (VDWG hDwg)
	{
	  tfCadCmdUserSelect pfCadCmdUserSelect;
	  pfCadCmdUserSelect = (tfCadCmdUserSelect)GetProcAddress( ghLibInst, "CadCmdUserSelect" );
	  if (pfCadCmdUserSelect){
		return (*pfCadCmdUserSelect)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadCmdUserGetEntity (VDWG hDwg)
	{
	  tfCadCmdUserGetEntity pfCadCmdUserGetEntity;
	  pfCadCmdUserGetEntity = (tfCadCmdUserGetEntity)GetProcAddress( ghLibInst, "CadCmdUserGetEntity" );
	  if (pfCadCmdUserGetEntity){
		return (*pfCadCmdUserGetEntity)(hDwg);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadCmdUserInput (VDWG hDwg)
	{
	  tfCadCmdUserInput pfCadCmdUserInput;
	  pfCadCmdUserInput = (tfCadCmdUserInput)GetProcAddress( ghLibInst, "CadCmdUserInput" );
	  if (pfCadCmdUserInput){
		return (*pfCadCmdUserInput)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadCmdGetInputPoint (VDWG hDwg, double* pX, double* pY, double* pZ)
	{
	  tfCadCmdGetInputPoint pfCadCmdGetInputPoint;
	  pfCadCmdGetInputPoint = (tfCadCmdGetInputPoint)GetProcAddress( ghLibInst, "CadCmdGetInputPoint" );
	  if (pfCadCmdGetInputPoint){
		(*pfCadCmdGetInputPoint)(hDwg, pX, pY, pZ);
	  }
	}


	//--------------
	void CADAPI CadCmdGetInputStr (VDWG hDwg, TCHAR* szText)
	{
	  tfCadCmdGetInputStr pfCadCmdGetInputStr;
	  pfCadCmdGetInputStr = (tfCadCmdGetInputStr)GetProcAddress( ghLibInst, "CadCmdGetInputStr" );
	  if (pfCadCmdGetInputStr){
		(*pfCadCmdGetInputStr)(hDwg, szText);
	  }
	}


	//--------------
	BOOL CADAPI CadCmdStrToPoint (VDWG hDwg, LPCTSTR szValue, double* pX, double* pY, double* pZ)
	{
	  tfCadCmdStrToPoint pfCadCmdStrToPoint;
	  pfCadCmdStrToPoint = (tfCadCmdStrToPoint)GetProcAddress( ghLibInst, "CadCmdStrToPoint" );
	  if (pfCadCmdStrToPoint){
		return (*pfCadCmdStrToPoint)(hDwg, szValue, pX, pY, pZ);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadCmdSetBasePoint (VDWG hDwg, double X, double Y, double Z)
	{
	  tfCadCmdSetBasePoint pfCadCmdSetBasePoint;
	  pfCadCmdSetBasePoint = (tfCadCmdSetBasePoint)GetProcAddress( ghLibInst, "CadCmdSetBasePoint" );
	  if (pfCadCmdSetBasePoint){
		(*pfCadCmdSetBasePoint)(hDwg, X, Y, Z);
	  }
	}


	//--------------
	BOOL CADAPI CadCmdAddPoint (VDWG hDwg, double X, double Y, double Z)
	{
	  tfCadCmdAddPoint pfCadCmdAddPoint;
	  pfCadCmdAddPoint = (tfCadCmdAddPoint)GetProcAddress( ghLibInst, "CadCmdAddPoint" );
	  if (pfCadCmdAddPoint){
		return (*pfCadCmdAddPoint)(hDwg, X, Y, Z);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadCmdGetPoint (VDWG hDwg, int iPoint, double* pX, double* pY, double* pZ)
	{
	  tfCadCmdGetPoint pfCadCmdGetPoint;
	  pfCadCmdGetPoint = (tfCadCmdGetPoint)GetProcAddress( ghLibInst, "CadCmdGetPoint" );
	  if (pfCadCmdGetPoint){
		return (*pfCadCmdGetPoint)(hDwg, iPoint, pX, pY, pZ);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadCmdCountPoints (VDWG hDwg)
	{
	  tfCadCmdCountPoints pfCadCmdCountPoints;
	  pfCadCmdCountPoints = (tfCadCmdCountPoints)GetProcAddress( ghLibInst, "CadCmdCountPoints" );
	  if (pfCadCmdCountPoints){
		return (*pfCadCmdCountPoints)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSelClear (VDWG hDwg)
	{
	  tfCadSelClear pfCadSelClear;
	  pfCadSelClear = (tfCadSelClear)GetProcAddress( ghLibInst, "CadSelClear" );
	  if (pfCadSelClear){
		(*pfCadSelClear)(hDwg);
	  }
	}


	//--------------
	void CADAPI CadSelectEntity (VDWG hDwg, VHANDLE hEnt, BOOL bSelect)
	{
	  tfCadSelectEntity pfCadSelectEntity;
	  pfCadSelectEntity = (tfCadSelectEntity)GetProcAddress( ghLibInst, "CadSelectEntity" );
	  if (pfCadSelectEntity){
		(*pfCadSelectEntity)(hDwg, hEnt, bSelect);
	  }
	}


	//--------------
	UINT CADAPI CadSelectByLayer (VDWG hDwg, BOOL bSelect)
	{
	  tfCadSelectByLayer pfCadSelectByLayer;
	  pfCadSelectByLayer = (tfCadSelectByLayer)GetProcAddress( ghLibInst, "CadSelectByLayer" );
	  if (pfCadSelectByLayer){
		return (*pfCadSelectByLayer)(hDwg, bSelect);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadSelectByPage (VDWG hDwg, BOOL bSelect)
	{
	  tfCadSelectByPage pfCadSelectByPage;
	  pfCadSelectByPage = (tfCadSelectByPage)GetProcAddress( ghLibInst, "CadSelectByPage" );
	  if (pfCadSelectByPage){
		return (*pfCadSelectByPage)(hDwg, bSelect);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadSelectByPolyline (VDWG hDwg, VHANDLE hEnt, BOOL bSelect)
	{
	  tfCadSelectByPolyline pfCadSelectByPolyline;
	  pfCadSelectByPolyline = (tfCadSelectByPolyline)GetProcAddress( ghLibInst, "CadSelectByPolyline" );
	  if (pfCadSelectByPolyline){
		return (*pfCadSelectByPolyline)(hDwg, hEnt, bSelect);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadSelectByPolygon (VDWG hDwg, VHANDLE hEnt, BOOL bCross, BOOL bSelect)
	{
	  tfCadSelectByPolygon pfCadSelectByPolygon;
	  pfCadSelectByPolygon = (tfCadSelectByPolygon)GetProcAddress( ghLibInst, "CadSelectByPolygon" );
	  if (pfCadSelectByPolygon){
		return (*pfCadSelectByPolygon)(hDwg, hEnt, bCross, bSelect);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadSelectByDist (VDWG hDwg, double X, double Y, double Z, double Dist, BOOL bCross, BOOL bSelect)
	{
	  tfCadSelectByDist pfCadSelectByDist;
	  pfCadSelectByDist = (tfCadSelectByDist)GetProcAddress( ghLibInst, "CadSelectByDist" );
	  if (pfCadSelectByDist){
		return (*pfCadSelectByDist)(hDwg, X, Y, Z, Dist, bCross, bSelect);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadSelCount (VDWG hDwg)
	{
	  tfCadSelCount pfCadSelCount;
	  pfCadSelCount = (tfCadSelCount)GetProcAddress( ghLibInst, "CadSelCount" );
	  if (pfCadSelCount){
		return (*pfCadSelCount)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSelGetFirstPtr (VDWG hDwg)
	{
	  tfCadSelGetFirstPtr pfCadSelGetFirstPtr;
	  pfCadSelGetFirstPtr = (tfCadSelGetFirstPtr)GetProcAddress( ghLibInst, "CadSelGetFirstPtr" );
	  if (pfCadSelGetFirstPtr){
		return (*pfCadSelGetFirstPtr)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadSelGetNextPtr (VDWG hDwg, VHANDLE hPtr)
	{
	  tfCadSelGetNextPtr pfCadSelGetNextPtr;
	  pfCadSelGetNextPtr = (tfCadSelGetNextPtr)GetProcAddress( ghLibInst, "CadSelGetNextPtr" );
	  if (pfCadSelGetNextPtr){
		return (*pfCadSelGetNextPtr)(hDwg, hPtr);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSelErase (VDWG hDwg)
	{
	  tfCadSelErase pfCadSelErase;
	  pfCadSelErase = (tfCadSelErase)GetProcAddress( ghLibInst, "CadSelErase" );
	  if (pfCadSelErase){
		(*pfCadSelErase)(hDwg);
	  }
	}


	//--------------
	void CADAPI CadSelCopy (VDWG hDwg)
	{
	  tfCadSelCopy pfCadSelCopy;
	  pfCadSelCopy = (tfCadSelCopy)GetProcAddress( ghLibInst, "CadSelCopy" );
	  if (pfCadSelCopy){
		(*pfCadSelCopy)(hDwg);
	  }
	}


	//--------------
	void CADAPI CadSelMove (VDWG hDwg, double dx, double dy, double dz)
	{
	  tfCadSelMove pfCadSelMove;
	  pfCadSelMove = (tfCadSelMove)GetProcAddress( ghLibInst, "CadSelMove" );
	  if (pfCadSelMove){
		(*pfCadSelMove)(hDwg, dx, dy, dz);
	  }
	}


	//--------------
	void CADAPI CadSelScale (VDWG hDwg, double x0, double y0, double z0, double Scal)
	{
	  tfCadSelScale pfCadSelScale;
	  pfCadSelScale = (tfCadSelScale)GetProcAddress( ghLibInst, "CadSelScale" );
	  if (pfCadSelScale){
		(*pfCadSelScale)(hDwg, x0, y0, z0, Scal);
	  }
	}


	//--------------
	void CADAPI CadSelRotate (VDWG hDwg, double x0, double y0, double z0, double Angle)
	{
	  tfCadSelRotate pfCadSelRotate;
	  pfCadSelRotate = (tfCadSelRotate)GetProcAddress( ghLibInst, "CadSelRotate" );
	  if (pfCadSelRotate){
		(*pfCadSelRotate)(hDwg, x0, y0, z0, Angle);
	  }
	}


	//--------------
	void CADAPI CadSelMirror (VDWG hDwg, double x0, double y0, double z0, double x1, double y1, double z1)
	{
	  tfCadSelMirror pfCadSelMirror;
	  pfCadSelMirror = (tfCadSelMirror)GetProcAddress( ghLibInst, "CadSelMirror" );
	  if (pfCadSelMirror){
		(*pfCadSelMirror)(hDwg, x0, y0, z0, x1, y1, z1);
	  }
	}


	//--------------
	void CADAPI CadSelExplode (VDWG hDwg)
	{
	  tfCadSelExplode pfCadSelExplode;
	  pfCadSelExplode = (tfCadSelExplode)GetProcAddress( ghLibInst, "CadSelExplode" );
	  if (pfCadSelExplode){
		(*pfCadSelExplode)(hDwg);
	  }
	}


	//--------------
	VHANDLE CADAPI CadSelJoin (VDWG hDwg, double Delta)
	{
	  tfCadSelJoin pfCadSelJoin;
	  pfCadSelJoin = (tfCadSelJoin)GetProcAddress( ghLibInst, "CadSelJoin" );
	  if (pfCadSelJoin){
		return (*pfCadSelJoin)(hDwg, Delta);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadSelColor (VDWG hDwg, int Color)
	{
	  tfCadSelColor pfCadSelColor;
	  pfCadSelColor = (tfCadSelColor)GetProcAddress( ghLibInst, "CadSelColor" );
	  if (pfCadSelColor){
		(*pfCadSelColor)(hDwg, Color);
	  }
	}


	//--------------
	void CADAPI CadSelDraw (VDWG hDwg, HDC hDC, int WinLef, int WinBot, int WinW, int WinH, double ViewLef, double ViewBot, double ViewW, double ViewH, DWORD idPage, COLORREF FillColor, COLORREF BordColor, double LwScale)
	{
	  tfCadSelDraw pfCadSelDraw;
	  pfCadSelDraw = (tfCadSelDraw)GetProcAddress( ghLibInst, "CadSelDraw" );
	  if (pfCadSelDraw){
		(*pfCadSelDraw)(hDwg, hDC, WinLef, WinBot, WinW, WinH, ViewLef, ViewBot, ViewW, ViewH, idPage, FillColor, BordColor, LwScale);
	  }
	}


	//--------------
	void CADAPI CadSelMakeGrips (VDWG hDwg)
	{
	  tfCadSelMakeGrips pfCadSelMakeGrips;
	  pfCadSelMakeGrips = (tfCadSelMakeGrips)GetProcAddress( ghLibInst, "CadSelMakeGrips" );
	  if (pfCadSelMakeGrips){
		(*pfCadSelMakeGrips)(hDwg);
	  }
	}


	//--------------
	BOOL CADAPI CadCbPaste (VDWG hDwg, HWND hWnd, double dx, double dy, double dz)
	{
	  tfCadCbPaste pfCadCbPaste;
	  pfCadCbPaste = (tfCadCbPaste)GetProcAddress( ghLibInst, "CadCbPaste" );
	  if (pfCadCbPaste){
		return (*pfCadCbPaste)(hDwg, hWnd, dx, dy, dz);
	  }
	  return 0;
	}


	//--------------
	DWORD CADAPI CadCountEntities (VDWG hDwg)
	{
	  tfCadCountEntities pfCadCountEntities;
	  pfCadCountEntities = (tfCadCountEntities)GetProcAddress( ghLibInst, "CadCountEntities" );
	  if (pfCadCountEntities){
		return (*pfCadCountEntities)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadViewPutPoint (VDWG hDwg, HWND hWin, double X, double Y, double Z)
	{
	  tfCadViewPutPoint pfCadViewPutPoint;
	  pfCadViewPutPoint = (tfCadViewPutPoint)GetProcAddress( ghLibInst, "CadViewPutPoint" );
	  if (pfCadViewPutPoint){
		(*pfCadViewPutPoint)(hDwg, hWin, X, Y, Z);
	  }
	}


	//--------------
	void CADAPI CadViewGetPoint (VDWG hDwg, HWND hWin, double* pX, double* pY, double* pZ)
	{
	  tfCadViewGetPoint pfCadViewGetPoint;
	  pfCadViewGetPoint = (tfCadViewGetPoint)GetProcAddress( ghLibInst, "CadViewGetPoint" );
	  if (pfCadViewGetPoint){
		(*pfCadViewGetPoint)(hDwg, hWin, pX, pY, pZ);
	  }
	}


	//--------------
	double CADAPI CadViewGetPointX (VDWG hDwg)
	{
	  tfCadViewGetPointX pfCadViewGetPointX;
	  pfCadViewGetPointX = (tfCadViewGetPointX)GetProcAddress( ghLibInst, "CadViewGetPointX" );
	  if (pfCadViewGetPointX){
		return (*pfCadViewGetPointX)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadViewGetPointY (VDWG hDwg)
	{
	  tfCadViewGetPointY pfCadViewGetPointY;
	  pfCadViewGetPointY = (tfCadViewGetPointY)GetProcAddress( ghLibInst, "CadViewGetPointY" );
	  if (pfCadViewGetPointY){
		return (*pfCadViewGetPointY)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadViewGetPointZ (VDWG hDwg)
	{
	  tfCadViewGetPointZ pfCadViewGetPointZ;
	  pfCadViewGetPointZ = (tfCadViewGetPointZ)GetProcAddress( ghLibInst, "CadViewGetPointZ" );
	  if (pfCadViewGetPointZ){
		return (*pfCadViewGetPointZ)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadViewPutAngles (VDWG hDwg, HWND hWin, double AngHor, double AngVer)
	{
	  tfCadViewPutAngles pfCadViewPutAngles;
	  pfCadViewPutAngles = (tfCadViewPutAngles)GetProcAddress( ghLibInst, "CadViewPutAngles" );
	  if (pfCadViewPutAngles){
		(*pfCadViewPutAngles)(hDwg, hWin, AngHor, AngVer);
	  }
	}


	//--------------
	double CADAPI CadViewGetAngleHor (VDWG hDwg)
	{
	  tfCadViewGetAngleHor pfCadViewGetAngleHor;
	  pfCadViewGetAngleHor = (tfCadViewGetAngleHor)GetProcAddress( ghLibInst, "CadViewGetAngleHor" );
	  if (pfCadViewGetAngleHor){
		return (*pfCadViewGetAngleHor)(hDwg);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadViewGetAngleVer (VDWG hDwg)
	{
	  tfCadViewGetAngleVer pfCadViewGetAngleVer;
	  pfCadViewGetAngleVer = (tfCadViewGetAngleVer)GetProcAddress( ghLibInst, "CadViewGetAngleVer" );
	  if (pfCadViewGetAngleVer){
		return (*pfCadViewGetAngleVer)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadViewRect (VDWG hDwg, HWND hWin, double Xmin, double Ymin, double Xmax, double Ymax)
	{
	  tfCadViewRect pfCadViewRect;
	  pfCadViewRect = (tfCadViewRect)GetProcAddress( ghLibInst, "CadViewRect" );
	  if (pfCadViewRect){
		(*pfCadViewRect)(hDwg, hWin, Xmin, Ymin, Xmax, Ymax);
	  }
	}


	//--------------
	void CADAPI CadViewScale (VDWG hDwg, HWND hWin, double Scal, int Xcen, int Ycen)
	{
	  tfCadViewScale pfCadViewScale;
	  pfCadViewScale = (tfCadViewScale)GetProcAddress( ghLibInst, "CadViewScale" );
	  if (pfCadViewScale){
		(*pfCadViewScale)(hDwg, hWin, Scal, Xcen, Ycen);
	  }
	}


	//--------------
	void CADAPI CadCoordModelToDisp (VDWG hDwg, double Xm, double Ym, double Zm, double* pXd, double* pYd)
	{
	  tfCadCoordModelToDisp pfCadCoordModelToDisp;
	  pfCadCoordModelToDisp = (tfCadCoordModelToDisp)GetProcAddress( ghLibInst, "CadCoordModelToDisp" );
	  if (pfCadCoordModelToDisp){
		(*pfCadCoordModelToDisp)(hDwg, Xm, Ym, Zm, pXd, pYd);
	  }
	}


	//--------------
	void CADAPI CadCoordModelToWin (VDWG hDwg, double Xm, double Ym, double Zm, long* pXw, long* pYw)
	{
	  tfCadCoordModelToWin pfCadCoordModelToWin;
	  pfCadCoordModelToWin = (tfCadCoordModelToWin)GetProcAddress( ghLibInst, "CadCoordModelToWin" );
	  if (pfCadCoordModelToWin){
		(*pfCadCoordModelToWin)(hDwg, Xm, Ym, Zm, pXw, pYw);
	  }
	}


	//--------------
	void CADAPI CadCoordDispToModel (VDWG hDwg, double Xd, double Yd, double* pXm, double* pYm, double* pZm)
	{
	  tfCadCoordDispToModel pfCadCoordDispToModel;
	  pfCadCoordDispToModel = (tfCadCoordDispToModel)GetProcAddress( ghLibInst, "CadCoordDispToModel" );
	  if (pfCadCoordDispToModel){
		(*pfCadCoordDispToModel)(hDwg, Xd, Yd, pXm, pYm, pZm);
	  }
	}


	//--------------
	void CADAPI CadCoordDispToWin (VDWG hDwg, double Xd, double Yd, long* pXw, long* pYw)
	{
	  tfCadCoordDispToWin pfCadCoordDispToWin;
	  pfCadCoordDispToWin = (tfCadCoordDispToWin)GetProcAddress( ghLibInst, "CadCoordDispToWin" );
	  if (pfCadCoordDispToWin){
		(*pfCadCoordDispToWin)(hDwg, Xd, Yd, pXw, pYw);
	  }
	}


	//--------------
	void CADAPI CadCoordWinToModel (VDWG hDwg, int Xw, int Yw, double* pXm, double* pYm, double* pZm)
	{
	  tfCadCoordWinToModel pfCadCoordWinToModel;
	  pfCadCoordWinToModel = (tfCadCoordWinToModel)GetProcAddress( ghLibInst, "CadCoordWinToModel" );
	  if (pfCadCoordWinToModel){
		(*pfCadCoordWinToModel)(hDwg, Xw, Yw, pXm, pYm, pZm);
	  }
	}


	//--------------
	void CADAPI CadCoordWinToDisp (VDWG hDwg, int Xw, int Yw, double* pXd, double* pYd)
	{
	  tfCadCoordWinToDisp pfCadCoordWinToDisp;
	  pfCadCoordWinToDisp = (tfCadCoordWinToDisp)GetProcAddress( ghLibInst, "CadCoordWinToDisp" );
	  if (pfCadCoordWinToDisp){
		(*pfCadCoordWinToDisp)(hDwg, Xw, Yw, pXd, pYd);
	  }
	}


	//--------------
	double CADAPI CadDistWinToModel (VDWG hDwg, int Dwin)
	{
	  tfCadDistWinToModel pfCadDistWinToModel;
	  pfCadDistWinToModel = (tfCadDistWinToModel)GetProcAddress( ghLibInst, "CadDistWinToModel" );
	  if (pfCadDistWinToModel){
		return (*pfCadDistWinToModel)(hDwg, Dwin);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadDistModelToWin (VDWG hDwg, double Dmod)
	{
	  tfCadDistModelToWin pfCadDistModelToWin;
	  pfCadDistModelToWin = (tfCadDistModelToWin)GetProcAddress( ghLibInst, "CadDistModelToWin" );
	  if (pfCadDistModelToWin){
		return (*pfCadDistModelToWin)(hDwg, Dmod);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPrintGetRect (double* pLeft, double* pBottom, double* pRight, double* pTop)
	{
	  tfCadPrintGetRect pfCadPrintGetRect;
	  pfCadPrintGetRect = (tfCadPrintGetRect)GetProcAddress( ghLibInst, "CadPrintGetRect" );
	  if (pfCadPrintGetRect){
		(*pfCadPrintGetRect)(pLeft, pBottom, pRight, pTop);
	  }
	}


	//--------------
	void CADAPI CadPrintPutRect (double Left, double Bottom, double Right, double Top)
	{
	  tfCadPrintPutRect pfCadPrintPutRect;
	  pfCadPrintPutRect = (tfCadPrintPutRect)GetProcAddress( ghLibInst, "CadPrintPutRect" );
	  if (pfCadPrintPutRect){
		(*pfCadPrintPutRect)(Left, Bottom, Right, Top);
	  }
	}


	//--------------
	void CADAPI CadPrintPutScale (double Scal)
	{
	  tfCadPrintPutScale pfCadPrintPutScale;
	  pfCadPrintPutScale = (tfCadPrintPutScale)GetProcAddress( ghLibInst, "CadPrintPutScale" );
	  if (pfCadPrintPutScale){
		(*pfCadPrintPutScale)(Scal);
	  }
	}


	//--------------
	double CADAPI CadPrintGetScale ()
	{
	  tfCadPrintGetScale pfCadPrintGetScale;
	  pfCadPrintGetScale = (tfCadPrintGetScale)GetProcAddress( ghLibInst, "CadPrintGetScale" );
	  if (pfCadPrintGetScale){
		return (*pfCadPrintGetScale)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPrintPutScaleLW (BOOL bScaleLW)
	{
	  tfCadPrintPutScaleLW pfCadPrintPutScaleLW;
	  pfCadPrintPutScaleLW = (tfCadPrintPutScaleLW)GetProcAddress( ghLibInst, "CadPrintPutScaleLW" );
	  if (pfCadPrintPutScaleLW){
		(*pfCadPrintPutScaleLW)(bScaleLW);
	  }
	}


	//--------------
	BOOL CADAPI CadPrintGetScaleLW ()
	{
	  tfCadPrintGetScaleLW pfCadPrintGetScaleLW;
	  pfCadPrintGetScaleLW = (tfCadPrintGetScaleLW)GetProcAddress( ghLibInst, "CadPrintGetScaleLW" );
	  if (pfCadPrintGetScaleLW){
		return (*pfCadPrintGetScaleLW)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPrintPutOffset (double DX, double DY)
	{
	  tfCadPrintPutOffset pfCadPrintPutOffset;
	  pfCadPrintPutOffset = (tfCadPrintPutOffset)GetProcAddress( ghLibInst, "CadPrintPutOffset" );
	  if (pfCadPrintPutOffset){
		(*pfCadPrintPutOffset)(DX, DY);
	  }
	}


	//--------------
	void CADAPI CadPrintGetOffset (double* pDX, double* pDY)
	{
	  tfCadPrintGetOffset pfCadPrintGetOffset;
	  pfCadPrintGetOffset = (tfCadPrintGetOffset)GetProcAddress( ghLibInst, "CadPrintGetOffset" );
	  if (pfCadPrintGetOffset){
		(*pfCadPrintGetOffset)(pDX, pDY);
	  }
	}


	//--------------
	void CADAPI CadPrintPutColor (BOOL bColor)
	{
	  tfCadPrintPutColor pfCadPrintPutColor;
	  pfCadPrintPutColor = (tfCadPrintPutColor)GetProcAddress( ghLibInst, "CadPrintPutColor" );
	  if (pfCadPrintPutColor){
		(*pfCadPrintPutColor)(bColor);
	  }
	}


	//--------------
	BOOL CADAPI CadPrintGetColor ()
	{
	  tfCadPrintGetColor pfCadPrintGetColor;
	  pfCadPrintGetColor = (tfCadPrintGetColor)GetProcAddress( ghLibInst, "CadPrintGetColor" );
	  if (pfCadPrintGetColor){
		return (*pfCadPrintGetColor)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPrintPutCopies (UINT Ncopy)
	{
	  tfCadPrintPutCopies pfCadPrintPutCopies;
	  pfCadPrintPutCopies = (tfCadPrintPutCopies)GetProcAddress( ghLibInst, "CadPrintPutCopies" );
	  if (pfCadPrintPutCopies){
		(*pfCadPrintPutCopies)(Ncopy);
	  }
	}


	//--------------
	UINT CADAPI CadPrintGetCopies ()
	{
	  tfCadPrintGetCopies pfCadPrintGetCopies;
	  pfCadPrintGetCopies = (tfCadPrintGetCopies)GetProcAddress( ghLibInst, "CadPrintGetCopies" );
	  if (pfCadPrintGetCopies){
		return (*pfCadPrintGetCopies)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPrintPutOrient (UINT Orient)
	{
	  tfCadPrintPutOrient pfCadPrintPutOrient;
	  pfCadPrintPutOrient = (tfCadPrintPutOrient)GetProcAddress( ghLibInst, "CadPrintPutOrient" );
	  if (pfCadPrintPutOrient){
		(*pfCadPrintPutOrient)(Orient);
	  }
	}


	//--------------
	UINT CADAPI CadPrintGetOrient ()
	{
	  tfCadPrintGetOrient pfCadPrintGetOrient;
	  pfCadPrintGetOrient = (tfCadPrintGetOrient)GetProcAddress( ghLibInst, "CadPrintGetOrient" );
	  if (pfCadPrintGetOrient){
		return (*pfCadPrintGetOrient)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPrintPutStampPos (UINT Pos)
	{
	  tfCadPrintPutStampPos pfCadPrintPutStampPos;
	  pfCadPrintPutStampPos = (tfCadPrintPutStampPos)GetProcAddress( ghLibInst, "CadPrintPutStampPos" );
	  if (pfCadPrintPutStampPos){
		(*pfCadPrintPutStampPos)(Pos);
	  }
	}


	//--------------
	UINT CADAPI CadPrintGetStampPos ()
	{
	  tfCadPrintGetStampPos pfCadPrintGetStampPos;
	  pfCadPrintGetStampPos = (tfCadPrintGetStampPos)GetProcAddress( ghLibInst, "CadPrintGetStampPos" );
	  if (pfCadPrintGetStampPos){
		return (*pfCadPrintGetStampPos)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPrintPutStampSize (double TextHeight)
	{
	  tfCadPrintPutStampSize pfCadPrintPutStampSize;
	  pfCadPrintPutStampSize = (tfCadPrintPutStampSize)GetProcAddress( ghLibInst, "CadPrintPutStampSize" );
	  if (pfCadPrintPutStampSize){
		(*pfCadPrintPutStampSize)(TextHeight);
	  }
	}


	//--------------
	double CADAPI CadPrintGetStampSize ()
	{
	  tfCadPrintGetStampSize pfCadPrintGetStampSize;
	  pfCadPrintGetStampSize = (tfCadPrintGetStampSize)GetProcAddress( ghLibInst, "CadPrintGetStampSize" );
	  if (pfCadPrintGetStampSize){
		return (*pfCadPrintGetStampSize)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPrintPutStampColor (DWORD Color)
	{
	  tfCadPrintPutStampColor pfCadPrintPutStampColor;
	  pfCadPrintPutStampColor = (tfCadPrintPutStampColor)GetProcAddress( ghLibInst, "CadPrintPutStampColor" );
	  if (pfCadPrintPutStampColor){
		(*pfCadPrintPutStampColor)(Color);
	  }
	}


	//--------------
	DWORD CADAPI CadPrintGetStampColor ()
	{
	  tfCadPrintGetStampColor pfCadPrintGetStampColor;
	  pfCadPrintGetStampColor = (tfCadPrintGetStampColor)GetProcAddress( ghLibInst, "CadPrintGetStampColor" );
	  if (pfCadPrintGetStampColor){
		return (*pfCadPrintGetStampColor)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPrintPutStampText (LPCTSTR szText1, LPCTSTR szText2)
	{
	  tfCadPrintPutStampText pfCadPrintPutStampText;
	  pfCadPrintPutStampText = (tfCadPrintPutStampText)GetProcAddress( ghLibInst, "CadPrintPutStampText" );
	  if (pfCadPrintPutStampText){
		(*pfCadPrintPutStampText)(szText1, szText2);
	  }
	}


	//--------------
	void CADAPI CadPrintGetStampText (TCHAR* szText1, TCHAR* szText2)
	{
	  tfCadPrintGetStampText pfCadPrintGetStampText;
	  pfCadPrintGetStampText = (tfCadPrintGetStampText)GetProcAddress( ghLibInst, "CadPrintGetStampText" );
	  if (pfCadPrintGetStampText){
		(*pfCadPrintGetStampText)(szText1, szText2);
	  }
	}


	//--------------
	void CADAPI CadPrintAtCenter (BOOL bCenter)
	{
	  tfCadPrintAtCenter pfCadPrintAtCenter;
	  pfCadPrintAtCenter = (tfCadPrintAtCenter)GetProcAddress( ghLibInst, "CadPrintAtCenter" );
	  if (pfCadPrintAtCenter){
		(*pfCadPrintAtCenter)(bCenter);
	  }
	}


	//--------------
	BOOL CADAPI CadPrint (VDWG hDwg, BOOL bPrintStamp, HDC hDC)
	{
	  tfCadPrint pfCadPrint;
	  pfCadPrint = (tfCadPrint)GetProcAddress( ghLibInst, "CadPrint" );
	  if (pfCadPrint){
		return (*pfCadPrint)(hDwg, bPrintStamp, hDC);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPrintSetup (HWND hwParent)
	{
	  tfCadPrintSetup pfCadPrintSetup;
	  pfCadPrintSetup = (tfCadPrintSetup)GetProcAddress( ghLibInst, "CadPrintSetup" );
	  if (pfCadPrintSetup){
		return (*pfCadPrintSetup)(hwParent);
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadPrintGetPaperW ()
	{
	  tfCadPrintGetPaperW pfCadPrintGetPaperW;
	  pfCadPrintGetPaperW = (tfCadPrintGetPaperW)GetProcAddress( ghLibInst, "CadPrintGetPaperW" );
	  if (pfCadPrintGetPaperW){
		return (*pfCadPrintGetPaperW)();
	  }
	  return 0;
	}


	//--------------
	double CADAPI CadPrintGetPaperH ()
	{
	  tfCadPrintGetPaperH pfCadPrintGetPaperH;
	  pfCadPrintGetPaperH = (tfCadPrintGetPaperH)GetProcAddress( ghLibInst, "CadPrintGetPaperH" );
	  if (pfCadPrintGetPaperH){
		return (*pfCadPrintGetPaperH)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPrintGetPaperSize (double* pWidth, double* pHeight)
	{
	  tfCadPrintGetPaperSize pfCadPrintGetPaperSize;
	  pfCadPrintGetPaperSize = (tfCadPrintGetPaperSize)GetProcAddress( ghLibInst, "CadPrintGetPaperSize" );
	  if (pfCadPrintGetPaperSize){
		(*pfCadPrintGetPaperSize)(pWidth, pHeight);
	  }
	}


	//--------------
	int CADAPI CadPrnRectAdd (VDWG hDwg, LPCTSTR szName, double Xcen, double Ycen, double W, double H, double Angle)
	{
	  tfCadPrnRectAdd pfCadPrnRectAdd;
	  pfCadPrnRectAdd = (tfCadPrnRectAdd)GetProcAddress( ghLibInst, "CadPrnRectAdd" );
	  if (pfCadPrnRectAdd){
		return (*pfCadPrnRectAdd)(hDwg, szName, Xcen, Ycen, W, H, Angle);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPrnRectDelete (VDWG hDwg, int iRect)
	{
	  tfCadPrnRectDelete pfCadPrnRectDelete;
	  pfCadPrnRectDelete = (tfCadPrnRectDelete)GetProcAddress( ghLibInst, "CadPrnRectDelete" );
	  if (pfCadPrnRectDelete){
		return (*pfCadPrnRectDelete)(hDwg, iRect);
	  }
	  return 0;
	}


	//--------------
	int CADAPI CadPrnRectCount (VDWG hDwg)
	{
	  tfCadPrnRectCount pfCadPrnRectCount;
	  pfCadPrnRectCount = (tfCadPrnRectCount)GetProcAddress( ghLibInst, "CadPrnRectCount" );
	  if (pfCadPrnRectCount){
		return (*pfCadPrnRectCount)(hDwg);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPrnRectGet (VDWG hDwg, int iRect, TCHAR* szName, double* pXcen, double* pYcen, double* pW, double* pH, double* pAngle)
	{
	  tfCadPrnRectGet pfCadPrnRectGet;
	  pfCadPrnRectGet = (tfCadPrnRectGet)GetProcAddress( ghLibInst, "CadPrnRectGet" );
	  if (pfCadPrnRectGet){
		return (*pfCadPrnRectGet)(hDwg, iRect, szName, pXcen, pYcen, pW, pH, pAngle);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPrnRectPut (VDWG hDwg, int iRect, LPCTSTR szName, double Xcen, double Ycen, double W, double H, double Angle)
	{
	  tfCadPrnRectPut pfCadPrnRectPut;
	  pfCadPrnRectPut = (tfCadPrnRectPut)GetProcAddress( ghLibInst, "CadPrnRectPut" );
	  if (pfCadPrnRectPut){
		return (*pfCadPrnRectPut)(hDwg, iRect, szName, Xcen, Ycen, W, H, Angle);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadPrnRectPrint (VDWG hDwg, int iRect, HDC hDC)
	{
	  tfCadPrnRectPrint pfCadPrnRectPrint;
	  pfCadPrnRectPrint = (tfCadPrnRectPrint)GetProcAddress( ghLibInst, "CadPrnRectPrint" );
	  if (pfCadPrnRectPrint){
		return (*pfCadPrnRectPrint)(hDwg, iRect, hDC);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadPrnRectPutShow (VDWG hDwg, BOOL bShow)
	{
	  tfCadPrnRectPutShow pfCadPrnRectPutShow;
	  pfCadPrnRectPutShow = (tfCadPrnRectPutShow)GetProcAddress( ghLibInst, "CadPrnRectPutShow" );
	  if (pfCadPrnRectPutShow){
		(*pfCadPrnRectPutShow)(hDwg, bShow);
	  }
	}


	//--------------
	BOOL CADAPI CadPrnRectGetShow (VDWG hDwg)
	{
	  tfCadPrnRectGetShow pfCadPrnRectGetShow;
	  pfCadPrnRectGetShow = (tfCadPrnRectGetShow)GetProcAddress( ghLibInst, "CadPrnRectGetShow" );
	  if (pfCadPrnRectGetShow){
		return (*pfCadPrnRectGetShow)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRegen (VDWG hDwg)
	{
	  tfCadRegen pfCadRegen;
	  pfCadRegen = (tfCadRegen)GetProcAddress( ghLibInst, "CadRegen" );
	  if (pfCadRegen){
		(*pfCadRegen)(hDwg);
	  }
	}


	//--------------
	void CADAPI CadUpdate (VDWG hDwg)
	{
	  tfCadUpdate pfCadUpdate;
	  pfCadUpdate = (tfCadUpdate)GetProcAddress( ghLibInst, "CadUpdate" );
	  if (pfCadUpdate){
		(*pfCadUpdate)(hDwg);
	  }
	}


	//--------------
	HWND CADAPI CadWndCreate (VDWG hDwg, HWND hWndParent, int CadStyle, int X, int Y, int W, int H)
	{
	  tfCadWndCreate pfCadWndCreate;
	  pfCadWndCreate = (tfCadWndCreate)GetProcAddress( ghLibInst, "CadWndCreate" );
	  if (pfCadWndCreate){
		return (*pfCadWndCreate)(hDwg, hWndParent, CadStyle, X, Y, W, H);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadWndResize (HWND hWin, int X, int Y, int W, int H)
	{
	  tfCadWndResize pfCadWndResize;
	  pfCadWndResize = (tfCadWndResize)GetProcAddress( ghLibInst, "CadWndResize" );
	  if (pfCadWndResize){
		return (*pfCadWndResize)(hWin, X, Y, W, H);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadWndRedraw (HWND hWin)
	{
	  tfCadWndRedraw pfCadWndRedraw;
	  pfCadWndRedraw = (tfCadWndRedraw)GetProcAddress( ghLibInst, "CadWndRedraw" );
	  if (pfCadWndRedraw){
		return (*pfCadWndRedraw)(hWin);
	  }
	  return 0;
	}


	//--------------
	HWND CADAPI CadWndSetFocus (HWND hWin)
	{
	  tfCadWndSetFocus pfCadWndSetFocus;
	  pfCadWndSetFocus = (tfCadWndSetFocus)GetProcAddress( ghLibInst, "CadWndSetFocus" );
	  if (pfCadWndSetFocus){
		return (*pfCadWndSetFocus)(hWin);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadAccelSetKey (int Command, int VirtKey, int Flags)
	{
	  tfCadAccelSetKey pfCadAccelSetKey;
	  pfCadAccelSetKey = (tfCadAccelSetKey)GetProcAddress( ghLibInst, "CadAccelSetKey" );
	  if (pfCadAccelSetKey){
		(*pfCadAccelSetKey)(Command, VirtKey, Flags);
	  }
	}


	//--------------
	void CADAPI CadAccelSetDefault ()
	{
	  tfCadAccelSetDefault pfCadAccelSetDefault;
	  pfCadAccelSetDefault = (tfCadAccelSetDefault)GetProcAddress( ghLibInst, "CadAccelSetDefault" );
	  if (pfCadAccelSetDefault){
		(*pfCadAccelSetDefault)();
	  }
	}


	//--------------
	HWND CADAPI CadCWCreate (HWND hwParent, int Left, int Top, int Width, int Height)
	{
	  tfCadCWCreate pfCadCWCreate;
	  pfCadCWCreate = (tfCadCWCreate)GetProcAddress( ghLibInst, "CadCWCreate" );
	  if (pfCadCWCreate){
		return (*pfCadCWCreate)(hwParent, Left, Top, Width, Height);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadCWDelete ()
	{
	  tfCadCWDelete pfCadCWDelete;
	  pfCadCWDelete = (tfCadCWDelete)GetProcAddress( ghLibInst, "CadCWDelete" );
	  if (pfCadCWDelete){
		(*pfCadCWDelete)();
	  }
	}


	//--------------
	BOOL CADAPI CadCWResize (int Left, int Top, int Width, int Height)
	{
	  tfCadCWResize pfCadCWResize;
	  pfCadCWResize = (tfCadCWResize)GetProcAddress( ghLibInst, "CadCWResize" );
	  if (pfCadCWResize){
		return (*pfCadCWResize)(Left, Top, Width, Height);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadCWPutText (VDWG hDwg, LPCTSTR szText)
	{
	  tfCadCWPutText pfCadCWPutText;
	  pfCadCWPutText = (tfCadCWPutText)GetProcAddress( ghLibInst, "CadCWPutText" );
	  if (pfCadCWPutText){
		(*pfCadCWPutText)(hDwg, szText);
	  }
	}


	//--------------
	void CADAPI CadMagPutSize (int Size)
	{
	  tfCadMagPutSize pfCadMagPutSize;
	  pfCadMagPutSize = (tfCadMagPutSize)GetProcAddress( ghLibInst, "CadMagPutSize" );
	  if (pfCadMagPutSize){
		(*pfCadMagPutSize)(Size);
	  }
	}


	//--------------
	int CADAPI CadMagGetSize ()
	{
	  tfCadMagGetSize pfCadMagGetSize;
	  pfCadMagGetSize = (tfCadMagGetSize)GetProcAddress( ghLibInst, "CadMagGetSize" );
	  if (pfCadMagGetSize){
		return (*pfCadMagGetSize)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMagPutScale (int Scal)
	{
	  tfCadMagPutScale pfCadMagPutScale;
	  pfCadMagPutScale = (tfCadMagPutScale)GetProcAddress( ghLibInst, "CadMagPutScale" );
	  if (pfCadMagPutScale){
		(*pfCadMagPutScale)(Scal);
	  }
	}


	//--------------
	int CADAPI CadMagGetScale ()
	{
	  tfCadMagGetScale pfCadMagGetScale;
	  pfCadMagGetScale = (tfCadMagGetScale)GetProcAddress( ghLibInst, "CadMagGetScale" );
	  if (pfCadMagGetScale){
		return (*pfCadMagGetScale)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMagPutPos (int Pos)
	{
	  tfCadMagPutPos pfCadMagPutPos;
	  pfCadMagPutPos = (tfCadMagPutPos)GetProcAddress( ghLibInst, "CadMagPutPos" );
	  if (pfCadMagPutPos){
		(*pfCadMagPutPos)(Pos);
	  }
	}


	//--------------
	int CADAPI CadMagGetPos ()
	{
	  tfCadMagGetPos pfCadMagGetPos;
	  pfCadMagGetPos = (tfCadMagGetPos)GetProcAddress( ghLibInst, "CadMagGetPos" );
	  if (pfCadMagGetPos){
		return (*pfCadMagGetPos)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadMagPutShow (BOOL bShow)
	{
	  tfCadMagPutShow pfCadMagPutShow;
	  pfCadMagPutShow = (tfCadMagPutShow)GetProcAddress( ghLibInst, "CadMagPutShow" );
	  if (pfCadMagPutShow){
		(*pfCadMagPutShow)(bShow);
	  }
	}


	//--------------
	BOOL CADAPI CadMagGetShow ()
	{
	  tfCadMagGetShow pfCadMagGetShow;
	  pfCadMagGetShow = (tfCadMagGetShow)GetProcAddress( ghLibInst, "CadMagGetShow" );
	  if (pfCadMagGetShow){
		return (*pfCadMagGetShow)();
	  }
	  return 0;
	}


	//--------------
	HWND CADAPI CadNavCreate (HWND hWndParent, int X, int Y, int W, int H, int Flags)
	{
	  tfCadNavCreate pfCadNavCreate;
	  pfCadNavCreate = (tfCadNavCreate)GetProcAddress( ghLibInst, "CadNavCreate" );
	  if (pfCadNavCreate){
		return (*pfCadNavCreate)(hWndParent, X, Y, W, H, Flags);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadNavResize (int X, int Y, int W, int H)
	{
	  tfCadNavResize pfCadNavResize;
	  pfCadNavResize = (tfCadNavResize)GetProcAddress( ghLibInst, "CadNavResize" );
	  if (pfCadNavResize){
		(*pfCadNavResize)(X, Y, W, H);
	  }
	}


	//--------------
	int CADAPI CadNavGetParam (int Prm)
	{
	  tfCadNavGetParam pfCadNavGetParam;
	  pfCadNavGetParam = (tfCadNavGetParam)GetProcAddress( ghLibInst, "CadNavGetParam" );
	  if (pfCadNavGetParam){
		return (*pfCadNavGetParam)(Prm);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadNavReturnFocus (BOOL bReturn, HWND hWnd)
	{
	  tfCadNavReturnFocus pfCadNavReturnFocus;
	  pfCadNavReturnFocus = (tfCadNavReturnFocus)GetProcAddress( ghLibInst, "CadNavReturnFocus" );
	  if (pfCadNavReturnFocus){
		(*pfCadNavReturnFocus)(bReturn, hWnd);
	  }
	}


	//--------------
	void CADAPI CadNavSetLink (HWND hVecWnd)
	{
	  tfCadNavSetLink pfCadNavSetLink;
	  pfCadNavSetLink = (tfCadNavSetLink)GetProcAddress( ghLibInst, "CadNavSetLink" );
	  if (pfCadNavSetLink){
		(*pfCadNavSetLink)(hVecWnd);
	  }
	}


	//--------------
	HWND CADAPI CadCboxCreate (int CbType, HWND hwParent, int Left, int Top, int Width, int Height, int Hdown)
	{
	  tfCadCboxCreate pfCadCboxCreate;
	  pfCadCboxCreate = (tfCadCboxCreate)GetProcAddress( ghLibInst, "CadCboxCreate" );
	  if (pfCadCboxCreate){
		return (*pfCadCboxCreate)(CbType, hwParent, Left, Top, Width, Height, Hdown);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadCboxSetActive (int CbType, HWND hwCbox)
	{
	  tfCadCboxSetActive pfCadCboxSetActive;
	  pfCadCboxSetActive = (tfCadCboxSetActive)GetProcAddress( ghLibInst, "CadCboxSetActive" );
	  if (pfCadCboxSetActive){
		(*pfCadCboxSetActive)(CbType, hwCbox);
	  }
	}


	//--------------
	void CADAPI CadMenuClear (int MenuId)
	{
	  tfCadMenuClear pfCadMenuClear;
	  pfCadMenuClear = (tfCadMenuClear)GetProcAddress( ghLibInst, "CadMenuClear" );
	  if (pfCadMenuClear){
		(*pfCadMenuClear)(MenuId);
	  }
	}


	//--------------
	void CADAPI CadMenuAdd (int MenuId, LPCTSTR szItemText, int ItemCmd)
	{
	  tfCadMenuAdd pfCadMenuAdd;
	  pfCadMenuAdd = (tfCadMenuAdd)GetProcAddress( ghLibInst, "CadMenuAdd" );
	  if (pfCadMenuAdd){
		(*pfCadMenuAdd)(MenuId, szItemText, ItemCmd);
	  }
	}


	//--------------
	BOOL CADAPI CadRecentLoad (LPCTSTR szFileName)
	{
	  tfCadRecentLoad pfCadRecentLoad;
	  pfCadRecentLoad = (tfCadRecentLoad)GetProcAddress( ghLibInst, "CadRecentLoad" );
	  if (pfCadRecentLoad){
		return (*pfCadRecentLoad)(szFileName);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRecentSave ()
	{
	  tfCadRecentSave pfCadRecentSave;
	  pfCadRecentSave = (tfCadRecentSave)GetProcAddress( ghLibInst, "CadRecentSave" );
	  if (pfCadRecentSave){
		return (*pfCadRecentSave)();
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRecentDialog (HWND hWin, TCHAR* szOutFileName, int* pbShowAtStartup)
	{
	  tfCadRecentDialog pfCadRecentDialog;
	  pfCadRecentDialog = (tfCadRecentDialog)GetProcAddress( ghLibInst, "CadRecentDialog" );
	  if (pfCadRecentDialog){
		return (*pfCadRecentDialog)(hWin, szOutFileName, pbShowAtStartup);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRecentAdd (LPCTSTR szFileName)
	{
	  tfCadRecentAdd pfCadRecentAdd;
	  pfCadRecentAdd = (tfCadRecentAdd)GetProcAddress( ghLibInst, "CadRecentAdd" );
	  if (pfCadRecentAdd){
		return (*pfCadRecentAdd)(szFileName);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadDialogOpenFile (HWND hwParent, TCHAR* szOutFileName)
	{
	  tfCadDialogOpenFile pfCadDialogOpenFile;
	  pfCadDialogOpenFile = (tfCadDialogOpenFile)GetProcAddress( ghLibInst, "CadDialogOpenFile" );
	  if (pfCadDialogOpenFile){
		return (*pfCadDialogOpenFile)(hwParent, szOutFileName);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadDialogSaveFile (HWND hwParent, TCHAR* szOutFileName)
	{
	  tfCadDialogSaveFile pfCadDialogSaveFile;
	  pfCadDialogSaveFile = (tfCadDialogSaveFile)GetProcAddress( ghLibInst, "CadDialogSaveFile" );
	  if (pfCadDialogSaveFile){
		return (*pfCadDialogSaveFile)(hwParent, szOutFileName);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadTipOfTheDay (HWND hwParent, LPCTSTR szFileName, int* pbShowOnStartup, int* pTipIndex)
	{
	  tfCadTipOfTheDay pfCadTipOfTheDay;
	  pfCadTipOfTheDay = (tfCadTipOfTheDay)GetProcAddress( ghLibInst, "CadTipOfTheDay" );
	  if (pfCadTipOfTheDay){
		(*pfCadTipOfTheDay)(hwParent, szFileName, pbShowOnStartup, pTipIndex);
	  }
	}


	//--------------
	void CADAPI CadHelp (HWND hWin, LPCTSTR szTopic)
	{
	  tfCadHelp pfCadHelp;
	  pfCadHelp = (tfCadHelp)GetProcAddress( ghLibInst, "CadHelp" );
	  if (pfCadHelp){
		(*pfCadHelp)(hWin, szTopic);
	  }
	}


	//--------------
	void CADAPI CadTTF2VCF (HWND hwParent)
	{
	  tfCadTTF2VCF pfCadTTF2VCF;
	  pfCadTTF2VCF = (tfCadTTF2VCF)GetProcAddress( ghLibInst, "CadTTF2VCF" );
	  if (pfCadTTF2VCF){
		(*pfCadTTF2VCF)(hwParent);
	  }
	}


	//--------------
	void CADAPI CadSHX2VCF (HWND hwParent)
	{
	  tfCadSHX2VCF pfCadSHX2VCF;
	  pfCadSHX2VCF = (tfCadSHX2VCF)GetProcAddress( ghLibInst, "CadSHX2VCF" );
	  if (pfCadSHX2VCF){
		(*pfCadSHX2VCF)(hwParent);
	  }
	}


	//--------------
	void CADAPI CadFontsList (HWND hwParent)
	{
	  tfCadFontsList pfCadFontsList;
	  pfCadFontsList = (tfCadFontsList)GetProcAddress( ghLibInst, "CadFontsList" );
	  if (pfCadFontsList){
		(*pfCadFontsList)(hwParent);
	  }
	}


	//--------------
	void CADAPI CadPluginsDlg (HWND hwParent)
	{
	  tfCadPluginsDlg pfCadPluginsDlg;
	  pfCadPluginsDlg = (tfCadPluginsDlg)GetProcAddress( ghLibInst, "CadPluginsDlg" );
	  if (pfCadPluginsDlg){
		(*pfCadPluginsDlg)(hwParent);
	  }
	}


	//--------------
	int CADAPI CadGetError ()
	{
	  tfCadGetError pfCadGetError;
	  pfCadGetError = (tfCadGetError)GetProcAddress( ghLibInst, "CadGetError" );
	  if (pfCadGetError){
		return (*pfCadGetError)();
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGetErrorStr (int ErrCode, TCHAR* szStr)
	{
	  tfCadGetErrorStr pfCadGetErrorStr;
	  pfCadGetErrorStr = (tfCadGetErrorStr)GetProcAddress( ghLibInst, "CadGetErrorStr" );
	  if (pfCadGetErrorStr){
		(*pfCadGetErrorStr)(ErrCode, szStr);
	  }
	}


	//--------------
	void CADAPI CadSetString (int IdStr, LPCTSTR szStr)
	{
	  tfCadSetString pfCadSetString;
	  pfCadSetString = (tfCadSetString)GetProcAddress( ghLibInst, "CadSetString" );
	  if (pfCadSetString){
		(*pfCadSetString)(IdStr, szStr);
	  }
	}


	//--------------
	BOOL CADAPI CadPluginImageRead (LPCTSTR szExt, LPCTSTR szLibName, LPCTSTR szFuncName, int Mode)
	{
	  tfCadPluginImageRead pfCadPluginImageRead;
	  pfCadPluginImageRead = (tfCadPluginImageRead)GetProcAddress( ghLibInst, "CadPluginImageRead" );
	  if (pfCadPluginImageRead){
		return (*pfCadPluginImageRead)(szExt, szLibName, szFuncName, Mode);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadConvertAcadFile (LPCTSTR szInFile, LPCTSTR szOutFile)
	{
	  tfCadConvertAcadFile pfCadConvertAcadFile;
	  pfCadConvertAcadFile = (tfCadConvertAcadFile)GetProcAddress( ghLibInst, "CadConvertAcadFile" );
	  if (pfCadConvertAcadFile){
		return (*pfCadConvertAcadFile)(szInFile, szOutFile);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadExtractImage (LPCTSTR szFileName, BYTE* Buffer)
	{
	  tfCadExtractImage pfCadExtractImage;
	  pfCadExtractImage = (tfCadExtractImage)GetProcAddress( ghLibInst, "CadExtractImage" );
	  if (pfCadExtractImage){
		return (*pfCadExtractImage)(szFileName, Buffer);
	  }
	  return 0;
	}


	//--------------
	UINT CADAPI CadExtractImageMem (void* pMem, BYTE* Buffer)
	{
	  tfCadExtractImageMem pfCadExtractImageMem;
	  pfCadExtractImageMem = (tfCadExtractImageMem)GetProcAddress( ghLibInst, "CadExtractImageMem" );
	  if (pfCadExtractImageMem){
		return (*pfCadExtractImageMem)(pMem, Buffer);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGetVBString (int Val, TCHAR* szStr)
	{
	  tfCadGetVBString pfCadGetVBString;
	  pfCadGetVBString = (tfCadGetVBString)GetProcAddress( ghLibInst, "CadGetVBString" );
	  if (pfCadGetVBString){
		(*pfCadGetVBString)(Val, szStr);
	  }
	}


	//--------------
	BOOL CADAPI vuGetWindowSize (HWND hWin, int* pW, int* pH)
	{
	  tfvuGetWindowSize pfvuGetWindowSize;
	  pfvuGetWindowSize = (tfvuGetWindowSize)GetProcAddress( ghLibInst, "vuGetWindowSize" );
	  if (pfvuGetWindowSize){
		return (*pfvuGetWindowSize)(hWin, pW, pH);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadGetWindowSize (HWND hWin, int* pW, int* pH)
	{
	  tfCadGetWindowSize pfCadGetWindowSize;
	  pfCadGetWindowSize = (tfCadGetWindowSize)GetProcAddress( ghLibInst, "CadGetWindowSize" );
	  if (pfCadGetWindowSize){
		return (*pfCadGetWindowSize)(hWin, pW, pH);
	  }
	  return 0;
	}


	//--------------
	int CADAPI vuCompress (BYTE* Dest, UINT DestMaxLen, CBYTE* Source, UINT SourceLen, int Level)
	{
	  tfvuCompress pfvuCompress;
	  pfvuCompress = (tfvuCompress)GetProcAddress( ghLibInst, "vuCompress" );
	  if (pfvuCompress){
		return (*pfvuCompress)(Dest, DestMaxLen, Source, SourceLen, Level);
	  }
	  return 0;
	}


	//--------------
	int CADAPI vuExpand (BYTE* Dest, UINT DestMaxLen, CBYTE* Source, UINT SourceLen)
	{
	  tfvuExpand pfvuExpand;
	  pfvuExpand = (tfvuExpand)GetProcAddress( ghLibInst, "vuExpand" );
	  if (pfvuExpand){
		return (*pfvuExpand)(Dest, DestMaxLen, Source, SourceLen);
	  }
	  return 0;
	}


	//--------------
	void CADAPI vuRotatePoint (double* pX, double* pY, double* pZ, double Xcen, double Ycen, double Zcen, double Angle, int Plane)
	{
	  tfvuRotatePoint pfvuRotatePoint;
	  pfvuRotatePoint = (tfvuRotatePoint)GetProcAddress( ghLibInst, "vuRotatePoint" );
	  if (pfvuRotatePoint){
		(*pfvuRotatePoint)(pX, pY, pZ, Xcen, Ycen, Zcen, Angle, Plane);
	  }
	}


	//--------------
	void CADAPI vuPolarPoint (double* pX, double* pY, double* pZ, double Angle, double Dist, int Plane)
	{
	  tfvuPolarPoint pfvuPolarPoint;
	  pfvuPolarPoint = (tfvuPolarPoint)GetProcAddress( ghLibInst, "vuPolarPoint" );
	  if (pfvuPolarPoint){
		(*pfvuPolarPoint)(pX, pY, pZ, Angle, Dist, Plane);
	  }
	}


	//--------------
	void CADAPI vuScalePoint (double* pX, double* pY, double* pZ, double Xcen, double Ycen, double Zcen, double ScaleX, double ScaleY, double ScaleZ)
	{
	  tfvuScalePoint pfvuScalePoint;
	  pfvuScalePoint = (tfvuScalePoint)GetProcAddress( ghLibInst, "vuScalePoint" );
	  if (pfvuScalePoint){
		(*pfvuScalePoint)(pX, pY, pZ, Xcen, Ycen, Zcen, ScaleX, ScaleY, ScaleZ);
	  }
	}


	//--------------
	void CADAPI vuMirrorPoint (double* pX, double* pY, double* pZ, double A1, double B1, int Plane)
	{
	  tfvuMirrorPoint pfvuMirrorPoint;
	  pfvuMirrorPoint = (tfvuMirrorPoint)GetProcAddress( ghLibInst, "vuMirrorPoint" );
	  if (pfvuMirrorPoint){
		(*pfvuMirrorPoint)(pX, pY, pZ, A1, B1, Plane);
	  }
	}


	//--------------
	double CADAPI vuGetAngle (double x1, double y1, double z1, double x2, double y2, double z2, int Plane)
	{
	  tfvuGetAngle pfvuGetAngle;
	  pfvuGetAngle = (tfvuGetAngle)GetProcAddress( ghLibInst, "vuGetAngle" );
	  if (pfvuGetAngle){
		return (*pfvuGetAngle)(x1, y1, z1, x2, y2, z2, Plane);
	  }
	  return 0;
	}


	//--------------
	double CADAPI vuGetDist (double x1, double y1, double z1, double x2, double y2, double z2, int Plane)
	{
	  tfvuGetDist pfvuGetDist;
	  pfvuGetDist = (tfvuGetDist)GetProcAddress( ghLibInst, "vuGetDist" );
	  if (pfvuGetDist){
		return (*pfvuGetDist)(x1, y1, z1, x2, y2, z2, Plane);
	  }
	  return 0;
	}


	//--------------
	double CADAPI vuNormalizeAngle (double Angle)
	{
	  tfvuNormalizeAngle pfvuNormalizeAngle;
	  pfvuNormalizeAngle = (tfvuNormalizeAngle)GetProcAddress( ghLibInst, "vuNormalizeAngle" );
	  if (pfvuNormalizeAngle){
		return (*pfvuNormalizeAngle)(Angle);
	  }
	  return 0;
	}


	//--------------
	void CADAPI vuNumToStr (double Val, TCHAR* szOutStr, DWORD MaxDec, BOOL bTrimZero, BOOL bRemainPoint)
	{
	  tfvuNumToStr pfvuNumToStr;
	  pfvuNumToStr = (tfvuNumToStr)GetProcAddress( ghLibInst, "vuNumToStr" );
	  if (pfvuNumToStr){
		(*pfvuNumToStr)(Val, szOutStr, MaxDec, bTrimZero, bRemainPoint);
	  }
	}


	//--------------
	VHANDLE CADAPI CadAddRPlan (VDWG hDwg)
	{
	  tfCadAddRPlan pfCadAddRPlan;
	  pfCadAddRPlan = (tfCadAddRPlan)GetProcAddress( ghLibInst, "CadAddRPlan" );
	  if (pfCadAddRPlan){
		return (*pfCadAddRPlan)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetRPlan (VDWG hDwg)
	{
	  tfCadGetRPlan pfCadGetRPlan;
	  pfCadGetRPlan = (tfCadGetRPlan)GetProcAddress( ghLibInst, "CadGetRPlan" );
	  if (pfCadGetRPlan){
		return (*pfCadGetRPlan)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRPlanClear (VHANDLE hRPlan)
	{
	  tfCadRPlanClear pfCadRPlanClear;
	  pfCadRPlanClear = (tfCadRPlanClear)GetProcAddress( ghLibInst, "CadRPlanClear" );
	  if (pfCadRPlanClear){
		(*pfCadRPlanClear)(hRPlan);
	  }
	}


	//--------------
	void CADAPI CadRPlanSetStart (VHANDLE hRPlan, double X, double Y, double Dist, double DirAngle)
	{
	  tfCadRPlanSetStart pfCadRPlanSetStart;
	  pfCadRPlanSetStart = (tfCadRPlanSetStart)GetProcAddress( ghLibInst, "CadRPlanSetStart" );
	  if (pfCadRPlanSetStart){
		(*pfCadRPlanSetStart)(hRPlan, X, Y, Dist, DirAngle);
	  }
	}


	//--------------
	BOOL CADAPI CadRPlanAddCurve (VHANDLE hRPlan, double Dist, double RotAngle, int Turn, double Rad, double Len1, double Len2)
	{
	  tfCadRPlanAddCurve pfCadRPlanAddCurve;
	  pfCadRPlanAddCurve = (tfCadRPlanAddCurve)GetProcAddress( ghLibInst, "CadRPlanAddCurve" );
	  if (pfCadRPlanAddCurve){
		return (*pfCadRPlanAddCurve)(hRPlan, Dist, RotAngle, Turn, Rad, Len1, Len2);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRPlanSetEnd (VHANDLE hRPlan, double Dist)
	{
	  tfCadRPlanSetEnd pfCadRPlanSetEnd;
	  pfCadRPlanSetEnd = (tfCadRPlanSetEnd)GetProcAddress( ghLibInst, "CadRPlanSetEnd" );
	  if (pfCadRPlanSetEnd){
		(*pfCadRPlanSetEnd)(hRPlan, Dist);
	  }
	}


	//--------------
	void CADAPI CadRPlanUpdate (VHANDLE hRPlan)
	{
	  tfCadRPlanUpdate pfCadRPlanUpdate;
	  pfCadRPlanUpdate = (tfCadRPlanUpdate)GetProcAddress( ghLibInst, "CadRPlanUpdate" );
	  if (pfCadRPlanUpdate){
		(*pfCadRPlanUpdate)(hRPlan);
	  }
	}


	//--------------
	void CADAPI CadRPlanSetScale (VHANDLE hRPlan, double Scal)
	{
	  tfCadRPlanSetScale pfCadRPlanSetScale;
	  pfCadRPlanSetScale = (tfCadRPlanSetScale)GetProcAddress( ghLibInst, "CadRPlanSetScale" );
	  if (pfCadRPlanSetScale){
		(*pfCadRPlanSetScale)(hRPlan, Scal);
	  }
	}


	//--------------
	UINT CADAPI CadRPlanGetNumRecs (VHANDLE hRPlan)
	{
	  tfCadRPlanGetNumRecs pfCadRPlanGetNumRecs;
	  pfCadRPlanGetNumRecs = (tfCadRPlanGetNumRecs)GetProcAddress( ghLibInst, "CadRPlanGetNumRecs" );
	  if (pfCadRPlanGetNumRecs){
		return (*pfCadRPlanGetNumRecs)(hRPlan);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRPlanGetCurveVertex (VHANDLE hRPlan, UINT iRec, double* pX, double* pY)
	{
	  tfCadRPlanGetCurveVertex pfCadRPlanGetCurveVertex;
	  pfCadRPlanGetCurveVertex = (tfCadRPlanGetCurveVertex)GetProcAddress( ghLibInst, "CadRPlanGetCurveVertex" );
	  if (pfCadRPlanGetCurveVertex){
		return (*pfCadRPlanGetCurveVertex)(hRPlan, iRec, pX, pY);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRPlanGetCurveCenter (VHANDLE hRPlan, UINT iRec, double* pX, double* pY)
	{
	  tfCadRPlanGetCurveCenter pfCadRPlanGetCurveCenter;
	  pfCadRPlanGetCurveCenter = (tfCadRPlanGetCurveCenter)GetProcAddress( ghLibInst, "CadRPlanGetCurveCenter" );
	  if (pfCadRPlanGetCurveCenter){
		return (*pfCadRPlanGetCurveCenter)(hRPlan, iRec, pX, pY);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRPlanGetCurveStart (VHANDLE hRPlan, UINT iRec, double* pX, double* pY, double* pDirAngle)
	{
	  tfCadRPlanGetCurveStart pfCadRPlanGetCurveStart;
	  pfCadRPlanGetCurveStart = (tfCadRPlanGetCurveStart)GetProcAddress( ghLibInst, "CadRPlanGetCurveStart" );
	  if (pfCadRPlanGetCurveStart){
		return (*pfCadRPlanGetCurveStart)(hRPlan, iRec, pX, pY, pDirAngle);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRPlanGetCurveEnd (VHANDLE hRPlan, UINT iRec, double* pX, double* pY, double* pDirAngle)
	{
	  tfCadRPlanGetCurveEnd pfCadRPlanGetCurveEnd;
	  pfCadRPlanGetCurveEnd = (tfCadRPlanGetCurveEnd)GetProcAddress( ghLibInst, "CadRPlanGetCurveEnd" );
	  if (pfCadRPlanGetCurveEnd){
		return (*pfCadRPlanGetCurveEnd)(hRPlan, iRec, pX, pY, pDirAngle);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRPlanAddGrPoint (double Offset, double Z)
	{
	  tfCadRPlanAddGrPoint pfCadRPlanAddGrPoint;
	  pfCadRPlanAddGrPoint = (tfCadRPlanAddGrPoint)GetProcAddress( ghLibInst, "CadRPlanAddGrPoint" );
	  if (pfCadRPlanAddGrPoint){
		return (*pfCadRPlanAddGrPoint)(Offset, Z);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRPlanAddGrSection (VHANDLE hRPlan, double Dist, double Zcen)
	{
	  tfCadRPlanAddGrSection pfCadRPlanAddGrSection;
	  pfCadRPlanAddGrSection = (tfCadRPlanAddGrSection)GetProcAddress( ghLibInst, "CadRPlanAddGrSection" );
	  if (pfCadRPlanAddGrSection){
		return (*pfCadRPlanAddGrSection)(hRPlan, Dist, Zcen);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRPlanGenLevels (VHANDLE hRPlan, double Precision, double ZStep, double ZStepBold, F_PROGRESS pFunc)
	{
	  tfCadRPlanGenLevels pfCadRPlanGenLevels;
	  pfCadRPlanGenLevels = (tfCadRPlanGenLevels)GetProcAddress( ghLibInst, "CadRPlanGenLevels" );
	  if (pfCadRPlanGenLevels){
		(*pfCadRPlanGenLevels)(hRPlan, Precision, ZStep, ZStepBold, pFunc);
	  }
	}


	//--------------
	BOOL CADAPI CadRPlanGetPoint (VHANDLE hRPlan, double Dist, double* pX, double* pY, double* pZ, double* pDirAngle)
	{
	  tfCadRPlanGetPoint pfCadRPlanGetPoint;
	  pfCadRPlanGetPoint = (tfCadRPlanGetPoint)GetProcAddress( ghLibInst, "CadRPlanGetPoint" );
	  if (pfCadRPlanGetPoint){
		return (*pfCadRPlanGetPoint)(hRPlan, Dist, pX, pY, pZ, pDirAngle);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRPlanGetGrPoint (VHANDLE hRPlan, double Dist, double Offset, double* pX, double* pY, double* pZ)
	{
	  tfCadRPlanGetGrPoint pfCadRPlanGetGrPoint;
	  pfCadRPlanGetGrPoint = (tfCadRPlanGetGrPoint)GetProcAddress( ghLibInst, "CadRPlanGetGrPoint" );
	  if (pfCadRPlanGetGrPoint){
		return (*pfCadRPlanGetGrPoint)(hRPlan, Dist, Offset, pX, pY, pZ);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRPlanGetDist (VHANDLE hRPlan, double X, double Y, double* pDist, double* pOffset)
	{
	  tfCadRPlanGetDist pfCadRPlanGetDist;
	  pfCadRPlanGetDist = (tfCadRPlanGetDist)GetProcAddress( ghLibInst, "CadRPlanGetDist" );
	  if (pfCadRPlanGetDist){
		return (*pfCadRPlanGetDist)(hRPlan, X, Y, pDist, pOffset);
	  }
	  return 0;
	}


	//--------------
	BOOL CADAPI CadRPlanGetZ (VHANDLE hRPlan, double X, double Y, double* pZ)
	{
	  tfCadRPlanGetZ pfCadRPlanGetZ;
	  pfCadRPlanGetZ = (tfCadRPlanGetZ)GetProcAddress( ghLibInst, "CadRPlanGetZ" );
	  if (pfCadRPlanGetZ){
		return (*pfCadRPlanGetZ)(hRPlan, X, Y, pZ);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRPlanPutVisible (VHANDLE hRPlan, int Mode, BOOL bVisible)
	{
	  tfCadRPlanPutVisible pfCadRPlanPutVisible;
	  pfCadRPlanPutVisible = (tfCadRPlanPutVisible)GetProcAddress( ghLibInst, "CadRPlanPutVisible" );
	  if (pfCadRPlanPutVisible){
		(*pfCadRPlanPutVisible)(hRPlan, Mode, bVisible);
	  }
	}


	//--------------
	BOOL CADAPI CadRPlanGetVisible (VHANDLE hRPlan, int Mode)
	{
	  tfCadRPlanGetVisible pfCadRPlanGetVisible;
	  pfCadRPlanGetVisible = (tfCadRPlanGetVisible)GetProcAddress( ghLibInst, "CadRPlanGetVisible" );
	  if (pfCadRPlanGetVisible){
		return (*pfCadRPlanGetVisible)(hRPlan, Mode);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRPlanPutColor (VHANDLE hRPlan, int Mode, int Color)
	{
	  tfCadRPlanPutColor pfCadRPlanPutColor;
	  pfCadRPlanPutColor = (tfCadRPlanPutColor)GetProcAddress( ghLibInst, "CadRPlanPutColor" );
	  if (pfCadRPlanPutColor){
		(*pfCadRPlanPutColor)(hRPlan, Mode, Color);
	  }
	}


	//--------------
	int CADAPI CadRPlanGetColor (VHANDLE hRPlan, int Mode)
	{
	  tfCadRPlanGetColor pfCadRPlanGetColor;
	  pfCadRPlanGetColor = (tfCadRPlanGetColor)GetProcAddress( ghLibInst, "CadRPlanGetColor" );
	  if (pfCadRPlanGetColor){
		return (*pfCadRPlanGetColor)(hRPlan, Mode);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRPlanPutLineweight (VHANDLE hRPlan, int Mode, int lw)
	{
	  tfCadRPlanPutLineweight pfCadRPlanPutLineweight;
	  pfCadRPlanPutLineweight = (tfCadRPlanPutLineweight)GetProcAddress( ghLibInst, "CadRPlanPutLineweight" );
	  if (pfCadRPlanPutLineweight){
		(*pfCadRPlanPutLineweight)(hRPlan, Mode, lw);
	  }
	}


	//--------------
	int CADAPI CadRPlanGetLineweight (VHANDLE hRPlan, int Mode)
	{
	  tfCadRPlanGetLineweight pfCadRPlanGetLineweight;
	  pfCadRPlanGetLineweight = (tfCadRPlanGetLineweight)GetProcAddress( ghLibInst, "CadRPlanGetLineweight" );
	  if (pfCadRPlanGetLineweight){
		return (*pfCadRPlanGetLineweight)(hRPlan, Mode);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadAddRProf (VDWG hDwg)
	{
	  tfCadAddRProf pfCadAddRProf;
	  pfCadAddRProf = (tfCadAddRProf)GetProcAddress( ghLibInst, "CadAddRProf" );
	  if (pfCadAddRProf){
		return (*pfCadAddRProf)(hDwg);
	  }
	  return 0;
	}


	//--------------
	VHANDLE CADAPI CadGetRProf (VDWG hDwg)
	{
	  tfCadGetRProf pfCadGetRProf;
	  pfCadGetRProf = (tfCadGetRProf)GetProcAddress( ghLibInst, "CadGetRProf" );
	  if (pfCadGetRProf){
		return (*pfCadGetRProf)(hDwg);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRProfClear (VHANDLE hRProf)
	{
	  tfCadRProfClear pfCadRProfClear;
	  pfCadRProfClear = (tfCadRProfClear)GetProcAddress( ghLibInst, "CadRProfClear" );
	  if (pfCadRProfClear){
		(*pfCadRProfClear)(hRProf);
	  }
	}


	//--------------
	void CADAPI CadRProfAddVer (VHANDLE hRProf, double Dist, double Y)
	{
	  tfCadRProfAddVer pfCadRProfAddVer;
	  pfCadRProfAddVer = (tfCadRProfAddVer)GetProcAddress( ghLibInst, "CadRProfAddVer" );
	  if (pfCadRProfAddVer){
		(*pfCadRProfAddVer)(hRProf, Dist, Y);
	  }
	}


	//--------------
	void CADAPI CadRProfDelVer (VHANDLE hRProf, int iVer)
	{
	  tfCadRProfDelVer pfCadRProfDelVer;
	  pfCadRProfDelVer = (tfCadRProfDelVer)GetProcAddress( ghLibInst, "CadRProfDelVer" );
	  if (pfCadRProfDelVer){
		(*pfCadRProfDelVer)(hRProf, iVer);
	  }
	}


	//--------------
	void CADAPI CadRProfPutVer (VHANDLE hRProf, int iVer, double Dist, double Y)
	{
	  tfCadRProfPutVer pfCadRProfPutVer;
	  pfCadRProfPutVer = (tfCadRProfPutVer)GetProcAddress( ghLibInst, "CadRProfPutVer" );
	  if (pfCadRProfPutVer){
		(*pfCadRProfPutVer)(hRProf, iVer, Dist, Y);
	  }
	}


	//--------------
	void CADAPI CadRProfPutCurveLen (VHANDLE hRProf, int iVer, double Length)
	{
	  tfCadRProfPutCurveLen pfCadRProfPutCurveLen;
	  pfCadRProfPutCurveLen = (tfCadRProfPutCurveLen)GetProcAddress( ghLibInst, "CadRProfPutCurveLen" );
	  if (pfCadRProfPutCurveLen){
		(*pfCadRProfPutCurveLen)(hRProf, iVer, Length);
	  }
	}


	//--------------
	void CADAPI CadRProfUpdate (VHANDLE hRProf)
	{
	  tfCadRProfUpdate pfCadRProfUpdate;
	  pfCadRProfUpdate = (tfCadRProfUpdate)GetProcAddress( ghLibInst, "CadRProfUpdate" );
	  if (pfCadRProfUpdate){
		(*pfCadRProfUpdate)(hRProf);
	  }
	}


	//--------------
	UINT CADAPI CadRProfGetNumVers (VHANDLE hRProf)
	{
	  tfCadRProfGetNumVers pfCadRProfGetNumVers;
	  pfCadRProfGetNumVers = (tfCadRProfGetNumVers)GetProcAddress( ghLibInst, "CadRProfGetNumVers" );
	  if (pfCadRProfGetNumVers){
		return (*pfCadRProfGetNumVers)(hRProf);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRProfGetVer (VHANDLE hRProf, int iVer, double* pDist, double* pY)
	{
	  tfCadRProfGetVer pfCadRProfGetVer;
	  pfCadRProfGetVer = (tfCadRProfGetVer)GetProcAddress( ghLibInst, "CadRProfGetVer" );
	  if (pfCadRProfGetVer){
		(*pfCadRProfGetVer)(hRProf, iVer, pDist, pY);
	  }
	}


	//--------------
	void CADAPI CadRProfGetCurvePrm (VHANDLE hRProf, int iVer, double* pRad, double* pBVC, double* pEVC, double* pLen)
	{
	  tfCadRProfGetCurvePrm pfCadRProfGetCurvePrm;
	  pfCadRProfGetCurvePrm = (tfCadRProfGetCurvePrm)GetProcAddress( ghLibInst, "CadRProfGetCurvePrm" );
	  if (pfCadRProfGetCurvePrm){
		(*pfCadRProfGetCurvePrm)(hRProf, iVer, pRad, pBVC, pEVC, pLen);
	  }
	}


	//--------------
	void CADAPI CadRProfGetY (VHANDLE hRProf, double Dist, double* pYold, double* pYnew)
	{
	  tfCadRProfGetY pfCadRProfGetY;
	  pfCadRProfGetY = (tfCadRProfGetY)GetProcAddress( ghLibInst, "CadRProfGetY" );
	  if (pfCadRProfGetY){
		(*pfCadRProfGetY)(hRProf, Dist, pYold, pYnew);
	  }
	}


	//--------------
	void CADAPI CadRProfGetInterX (VHANDLE hRProf, double Y, double* pX, int* pNumX, int MaxNumX)
	{
	  tfCadRProfGetInterX pfCadRProfGetInterX;
	  pfCadRProfGetInterX = (tfCadRProfGetInterX)GetProcAddress( ghLibInst, "CadRProfGetInterX" );
	  if (pfCadRProfGetInterX){
		(*pfCadRProfGetInterX)(hRProf, Y, pX, pNumX, MaxNumX);
	  }
	}


	//--------------
	void CADAPI CadRProfPutScale (VHANDLE hRProf, double HorScale, double VerScale)
	{
	  tfCadRProfPutScale pfCadRProfPutScale;
	  pfCadRProfPutScale = (tfCadRProfPutScale)GetProcAddress( ghLibInst, "CadRProfPutScale" );
	  if (pfCadRProfPutScale){
		(*pfCadRProfPutScale)(hRProf, HorScale, VerScale);
	  }
	}


	//--------------
	void CADAPI CadRProfPutVisible (VHANDLE hRProf, int Mode, BOOL bVisible)
	{
	  tfCadRProfPutVisible pfCadRProfPutVisible;
	  pfCadRProfPutVisible = (tfCadRProfPutVisible)GetProcAddress( ghLibInst, "CadRProfPutVisible" );
	  if (pfCadRProfPutVisible){
		(*pfCadRProfPutVisible)(hRProf, Mode, bVisible);
	  }
	}


	//--------------
	BOOL CADAPI CadRProfGetVisible (VHANDLE hRProf, int Mode)
	{
	  tfCadRProfGetVisible pfCadRProfGetVisible;
	  pfCadRProfGetVisible = (tfCadRProfGetVisible)GetProcAddress( ghLibInst, "CadRProfGetVisible" );
	  if (pfCadRProfGetVisible){
		return (*pfCadRProfGetVisible)(hRProf, Mode);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRProfPutColor (VHANDLE hRProf, int Mode, int Color)
	{
	  tfCadRProfPutColor pfCadRProfPutColor;
	  pfCadRProfPutColor = (tfCadRProfPutColor)GetProcAddress( ghLibInst, "CadRProfPutColor" );
	  if (pfCadRProfPutColor){
		(*pfCadRProfPutColor)(hRProf, Mode, Color);
	  }
	}


	//--------------
	int CADAPI CadRProfGetColor (VHANDLE hRProf, int Mode)
	{
	  tfCadRProfGetColor pfCadRProfGetColor;
	  pfCadRProfGetColor = (tfCadRProfGetColor)GetProcAddress( ghLibInst, "CadRProfGetColor" );
	  if (pfCadRProfGetColor){
		return (*pfCadRProfGetColor)(hRProf, Mode);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadRProfPutLineweight (VHANDLE hRProf, int Mode, int lw)
	{
	  tfCadRProfPutLineweight pfCadRProfPutLineweight;
	  pfCadRProfPutLineweight = (tfCadRProfPutLineweight)GetProcAddress( ghLibInst, "CadRProfPutLineweight" );
	  if (pfCadRProfPutLineweight){
		(*pfCadRProfPutLineweight)(hRProf, Mode, lw);
	  }
	}


	//--------------
	int CADAPI CadRProfGetLineweight (VHANDLE hRProf, int Mode)
	{
	  tfCadRProfGetLineweight pfCadRProfGetLineweight;
	  pfCadRProfGetLineweight = (tfCadRProfGetLineweight)GetProcAddress( ghLibInst, "CadRProfGetLineweight" );
	  if (pfCadRProfGetLineweight){
		return (*pfCadRProfGetLineweight)(hRProf, Mode);
	  }
	  return 0;
	}


	//--------------
	void CADAPI CadGetInterPoints (VDWG hDwg, VHANDLE hEnt1, VHANDLE hEnt2, double* pX, double* pY, int* pNumPt, int MaxNumPt)
	{
	  tfCadGetInterPoints pfCadGetInterPoints;
	  pfCadGetInterPoints = (tfCadGetInterPoints)GetProcAddress( ghLibInst, "CadGetInterPoints" );
	  if (pfCadGetInterPoints){
		(*pfCadGetInterPoints)(hDwg, hEnt1, hEnt2, pX, pY, pNumPt, MaxNumPt);
	  }
	}
};
