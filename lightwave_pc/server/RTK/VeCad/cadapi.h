/********************************************************************
* Project: VeCAD DLL
* Copyright (c) 1999-2005, Oleg Kolbaskin.
* All rights reserved.
*
* VeCAD API functions and constants
********************************************************************/
#ifndef CADAPI_H
#define CADAPI_H

namespace CadApi
{
	#define CAD_FALSE     0
	#define CAD_TRUE      1

	// VeCAD global parameters (CadGetParam/CadSetParam)
	#define CAD_GL_SHOWSYSCURSOR  1
	#define CAD_GL_CROSSSIZE      2
	#define CAD_GL_SHOWCROSS      3
	#define CAD_GL_CURVEQUALITY   4
	#define CAD_GL_CHARQUALITY    5
	#define CAD_GL_MINCHARSIZE    6
	#define CAD_GL_MINCHARFSIZE   7
	#define CAD_GL_MINENTSIZE     8
	#define CAD_GL_DRAWSTEP       9
	#define CAD_GL_MITERLIMIT     10
	#define CAD_GL_AUTOSEL        11
	#define CAD_GL_AUTOSELRECT    12
	#define CAD_GL_SELSHIFTADD    13
	#define CAD_GL_SELINSIDE      14
	#define CAD_GL_SELBYLAYER     15
	#define CAD_GL_UNSELAFTEREDIT 16
	#define CAD_GL_SELLINE        17
	#define CAD_GL_PICKBOXSIZE    18
	#define CAD_GL_USEGRIPS       19
	#define CAD_GL_GRIPSIZE       20
	#define CAD_GL_IMAGEBORDER    21
	#define CAD_GL_DXFDECPREC     22
	#define CAD_GL_DXFVER         23
	#define CAD_GL_DWGVER         24
	#define CAD_GL_ANGUNITS       25
	#define CAD_GL_FILEEXT        26
	#define CAD_GL_SHOWEMPTY      27
	#define CAD_GL_BLINKTIME      28
	#define CAD_GL_NAVRTIME       29
	#define CAD_GL_ENUMDELENTS    30
	#define CAD_GL_ACADCONVERT    31
	#define CAD_GL_FASTCURSOR     32
	#define CAD_GL_DELSCROLLBARS  33
	#define CAD_GL_SHOWEMPTYBLKS  34
	#define CAD_GL_GETINVISIBLE   35
	#define CAD_GL_SELINPLINE     36
	#define CAD_GL_SELDRAWHATCH   37
	#define CAD_GL_SNAPSHOWAPER   38
	#define CAD_GL_SNAPSHOWMARK   39
	#define CAD_GL_SNAPAPERSIZE   40
	#define CAD_GL_SNAPMARKSIZE   41
	#define CAD_GL_SMOOTHSCROLL   42
	#define CAD_GL_SHOWCOMPASS    43
	#define CAD_GL_EXTMARGIN      44
	#define CAD_GL_MBUTTONPAN     45
	#define CAD_GL_IMPDIMASBLOCK    46
	#define CAD_GL_IMPHATCHEXPLODE  47
	#define CAD_GL_NOACADWARNING    48
	#define CAD_GL_HIDESOMEPROPS  51
	#define CAD_GL_PRNUSEDOC      52

	// types of VeCAD objects
	#define CAD_ENT_POINT      1   // Point
	#define CAD_ENT_LINE       2   // Line
	#define CAD_ENT_POLYLINE   3   // Polyline
	#define CAD_ENT_ARC        4   // Circle, Arc, Ellipse
	#define CAD_ENT_TEXT       5   // Text
	#define CAD_ENT_INSBLOCK   6   // Insertion of a block
	#define CAD_ENT_SHAPE      7   // shape
	#define CAD_ENT_3DFACE     8   // 3DFace
	#define CAD_ENT_SOLID      9
	#define CAD_ENT_IMAGE     10   // Raster image
	#define CAD_ENT_DIM       11   // Dimension
	#define CAD_ENT_HATCH     12   // Hatch
	#define CAD_ENT_LEADER    13   // Leader
	#define CAD_ENT_MLINE     14   // Multiline
	#define CAD_ENT_VPORT     15   // viewport at paper space
	//#define CAD_ENT_XREF      16   // Insertion of a block (XREF)
	#define CAD_ENT_ATTRIB    17   // attribute
	#define CAD_ENT_RECT      18   // rectangle
	#define CAD_ENT_MTEXT     19   // Multiline Text
	#define CAD_ENT_WINTEXT   20   // Text
	#define CAD_ENT_CUSTOM    77   // Custom object

	#ifdef _DASAN_
	#define CAD_ENT_RPLAN     81
	#define CAD_ENT_RPROF     82
	#endif 


	// subtypes for VL_ENT_ARC type
	#define CAD_CIRCLE   1
	#define CAD_ARC      2  // circular arc
	#define CAD_ELLIPSE  3  // ellipse or elliptical arc

	// subtypes for CAD_ENT_DIM (types of dimension objects)
	#define CAD_DIM_HOR        1
	#define CAD_DIM_VER        2
	#define CAD_DIM_ALIGNED    3
	#define CAD_DIM_ORDX       4
	#define CAD_DIM_ORDY       5
	#define CAD_DIM_ANGULAR    6
	#define CAD_DIM_ANG3P      7
	#define CAD_DIM_RADIUS     8
	#define CAD_DIM_DIAMETER   9

	// smooth types for polyline (must be the same as in "entities.h" (PLINE_FITTYPE_...)
	#define CAD_PLINE_LINEAR       0
	#define CAD_PLINE_QUAD         5
	#define CAD_PLINE_CUBIC        6
	#define CAD_PLINE_BEZIER       8
	#define CAD_PLINE_SPLINE      99
	#define CAD_PLINE_ROUND      201   // rounded vertices
	#define CAD_PLINE_LINQUAD    202   // mixed linear and quadratic segments

	// attribute flags, values for CAttrib::Flag (must be the same as AD_ATTRIB_.. in "..\odt\ad2.h")
	#define CAD_ATTRIB_INVIS   1
	#define CAD_ATTRIB_CONST   2
	#define CAD_ATTRIB_VERIFY  4
	#define CAD_ATTRIB_PRESET  8

	// page paper size
	#define CAD_PAPER_UNLIMITED  0
	#define CAD_PAPER_A0         1
	#define CAD_PAPER_A1         2
	#define CAD_PAPER_A2         3
	#define CAD_PAPER_A3         4
	#define CAD_PAPER_A4         5
	#define CAD_PAPER_A5         6
	#define CAD_PAPER_A6         7
	#define CAD_PAPER_B0         11
	#define CAD_PAPER_B1         12
	#define CAD_PAPER_B2         13
	#define CAD_PAPER_B3         14
	#define CAD_PAPER_B4         15
	#define CAD_PAPER_B5         16
	#define CAD_PAPER_B6         17
	#define CAD_PAPER_C0         21
	#define CAD_PAPER_C1         22
	#define CAD_PAPER_C2         23
	#define CAD_PAPER_C3         24
	#define CAD_PAPER_C4         25
	#define CAD_PAPER_C5         26
	#define CAD_PAPER_C6         27
	#define CAD_PAPER_ANSI_A     31
	#define CAD_PAPER_ANSI_B     32
	#define CAD_PAPER_ANSI_C     33
	#define CAD_PAPER_ANSI_D     34
	#define CAD_PAPER_ANSI_E     35
	#define CAD_PAPER_LETTER     36
	#define CAD_PAPER_LEGAL      37
	#define CAD_PAPER_EXECUTIVE  38
	#define CAD_PAPER_LEDGER     39
	#define CAD_PAPER_USER       255


	// paper orientation 
	#define CAD_PAPER_PORTRAIT     1
	#define CAD_PAPER_BOOK         1
	#define CAD_PAPER_LANDSCAPE    2
	#define CAD_PAPER_ALBUM        2


	// text alignment types
	#define CAD_TA_BOTLEFT      0
	#define CAD_TA_LEFBOT       0
	#define CAD_TA_BOTCENTER    1
	#define CAD_TA_CENBOT       1
	#define CAD_TA_BOTRIGHT     2
	#define CAD_TA_RIGBOT       2
	#define CAD_TA_MIDLEFT      3
	#define CAD_TA_LEFCEN       3
	#define CAD_TA_MIDCENTER    4
	#define CAD_TA_CENCEN       4
	#define CAD_TA_MIDRIGHT     5
	#define CAD_TA_RIGCEN       5
	#define CAD_TA_TOPLEFT      6
	#define CAD_TA_LEFTOP       6
	#define CAD_TA_TOPCENTER    7
	#define CAD_TA_CENTOP       7
	#define CAD_TA_TOPRIGHT     8
	#define CAD_TA_RIGTOP       8


	// Colors (palette indices)
	// indices from 1 to 255 are used for entities
	#define CAD_COLOR_RED        1
	#define CAD_COLOR_YELLOW     2
	#define CAD_COLOR_GREEN      3
	#define CAD_COLOR_CYAN       4
	#define CAD_COLOR_BLUE       5
	#define CAD_COLOR_MAGENTA    6
	#define CAD_COLOR_WHITE      7   // inversed to background color
	#define CAD_COLOR_GRAY       8
	#define CAD_COLOR_LTGRAY     9
	#define CAD_COLOR_BROWN      32
	#define CAD_COLOR_SALAD      60
	#define CAD_COLOR_WHITE2     247  // always white
	#define CAD_COLOR_BLACK      248
	#define CAD_COLOR_LTBLACK    249
	#define CAD_COLOR_GRAY0      250
	#define CAD_COLOR_GRAY1      251
	#define CAD_COLOR_GRAY2      252
	#define CAD_COLOR_GRAY3      253
	#define CAD_COLOR_GRAY4      254
	#define CAD_COLOR_GRAY5      255
	// logical colors for entities
	#define CAD_COLOR_BYBLOCK    0     // entity's color by block
	#define CAD_COLOR_BYLAYER    256   // entity's color by layer

	#define CAD_COLOR_WINBKG     0     // window background (Model space)
	#define CAD_COLOR_CURSOR     256   // cursor (Model space)
	// for paper space and print preview
	#define CAD_COLOR_PP_WINBKG  257   // window background
	#define CAD_COLOR_PP_PAPER   258   // paper sheet
	#define CAD_COLOR_PP_WHITE   259   // "White" color
	#define CAD_COLOR_PP_CURSOR  260   // cursor

	#define CAD_COLOR_SELECT     261   // Selected entities
	#define CAD_COLOR_GRIPS      262   // grips
	#define CAD_COLOR_SNAPMARK   263   // AutoSnap marker

	#define CAD_COLOR_NAVBKG     264   // Navigator window background
	#define CAD_COLOR_NAVRECT    265   // Navigator view rectangle
	#define CAD_COLOR_NAVBOT     266   // Navigator bottom area
	#define CAD_COLOR_NAVLINE    267   // Navigator lines
	#define CAD_COLOR_NAVTEXT    268   // Navigator text

	#define CAD_COLOR_AREAIN     269   // Area inside hatch
	#define CAD_COLOR_AREAOUT    270   // Area boundary

	// can be used in CadSelDraw function
	#define CAD_COLOR_TRANSPARENT  1687050 // 0x19be0a (for RGB value)


	// Identifiers for standard non-graphic objects
	#define MAX_TABID            4000032760
	#define CAD_LT_BYLAYER       4000032767
	#define CAD_LT_BYBLOCK       4000032766
	#define CAD_LT_CONTINUOUS    4000032765
	#define CAD_LAYER_0          4000032767
	#define CAD_TSTYLE_STANDARD  4000032767
	#define CAD_MLS_STANDARD     4000032767
	#define CAD_DIMS_STANDARD    4000032767
	#define CAD_PAGE_MODEL       4000032767
							  // 2147483648


	// Lineweights
	#define CAD_LWEIGHT_DEFAULT  -3
	#define CAD_LWEIGHT_BYBLOCK  -2
	#define CAD_LWEIGHT_BYLAYER  -1
	#define CAD_LWEIGHT_000       0     // 0.00 mm
	#define CAD_LWEIGHT_005       5     // 0.05 mm
	#define CAD_LWEIGHT_009       9     // 0.09 mm
	#define CAD_LWEIGHT_013       13    // 0.13 mm
	#define CAD_LWEIGHT_015       15    // 0.15 mm
	#define CAD_LWEIGHT_018       18    // 0.18 mm
	#define CAD_LWEIGHT_020       20    // 0.20 mm
	#define CAD_LWEIGHT_025       25    // 0.25 mm
	#define CAD_LWEIGHT_030       30    // 0.30 mm
	#define CAD_LWEIGHT_035       35    // 0.35 mm
	#define CAD_LWEIGHT_040       40    // 0.40 mm
	#define CAD_LWEIGHT_050       50    // 0.50 mm
	#define CAD_LWEIGHT_053       53    // 0.53 mm
	#define CAD_LWEIGHT_060       60    // 0.60 mm
	#define CAD_LWEIGHT_070       70    // 0.70 mm
	#define CAD_LWEIGHT_080       80    // 0.80 mm
	#define CAD_LWEIGHT_090       90    // 0.90 mm
	#define CAD_LWEIGHT_100       100   // 1.00 mm
	#define CAD_LWEIGHT_106       106   // 1.06 mm
	#define CAD_LWEIGHT_120       120   // 1.20 mm
	#define CAD_LWEIGHT_140       140   // 1.40 mm
	#define CAD_LWEIGHT_158       158   // 1.58 mm
	#define CAD_LWEIGHT_200       200   // 2.00 mm
	#define CAD_LWEIGHT_211       211   // 2.11 mm

	#define CAD_DS_DIMLINE     1
	#define CAD_DS_EXTLINE     2
	#define CAD_DS_TEXT        3
	#define CAD_DS_ARROW1      4
	#define CAD_DS_ARROW2      5
	#define CAD_DS_ARRLEADER   6

	#define CAD_DS_TEXT_CEN    1   // Centered between extension lines.
	#define CAD_DS_TEXT_ABOVE  2   // above dimension line,
	#define CAD_DS_TEXT_ALIGN  4   // text aligned with dimension line
	#define CAD_DS_TEXT_HOR    8   // text drawn horizontally

	#define CAD_DS_UNIT_SCIENTIFIC  1   // Scientific
	#define CAD_DS_UNIT_DECIMAL     2   // Decimal
	#define CAD_DS_UNIT_ENGINEER    3   // Engineering
	#define CAD_DS_UNIT_DEGREE      10  // Decimal Degrees
	#define CAD_DS_UNIT_DEGMINSEC   11  // Degrees Minutes Seconds
	#define CAD_DS_UNIT_GRAD        12  // Gradians
	#define CAD_DS_UNIT_RADIAN      13  // Radians

	// decimal separator types
	#define CAD_DECSEP_POINT      0
	#define CAD_DECSEP_COMMA      1
	#define CAD_DECSEP_NONE       2

	// arrowhead types
	#define CAD_ARROW_CLOSEDF     0    // Closed filled
	#define CAD_ARROW_CLOSEDB     1    // Closed blank
	#define CAD_ARROW_CLOSED      2    // Closed
	#define CAD_ARROW_DOT         3    // Dot
	#define CAD_ARROW_ARCHTICK    4    // Architectural tick
	#define CAD_ARROW_OBLIQUE     5    // Oblique
	#define CAD_ARROW_OPEN        6    // Open
	#define CAD_ARROW_ORIGIN      7    // Origin indicator
	#define CAD_ARROW_ORIGIN2     8    // Origin indicator 2
	#define CAD_ARROW_OPEN90      9    // Right angle
	#define CAD_ARROW_OPEN30      10   // Open 30
	#define CAD_ARROW_DOTSMALL    11   // Dot small
	#define CAD_ARROW_DOTB        12   // Dot blank
	#define CAD_ARROW_DOTSMALLB   13   // Dot small blank
	#define CAD_ARROW_BOX         14   // Box
	#define CAD_ARROW_BOXF        15   // Box filled
	#define CAD_ARROW_DATUM       16   // Datum triangle
	#define CAD_ARROW_DATUMF      17   // Datum triangle filled
	#define CAD_ARROW_INTEGRAL    18   // Integral
	#define CAD_ARROW_NONE        19   // None

	// system cursor types
	#define CAD_CURSOR_ARROW      2000777001
	#define CAD_CURSOR_HELP       2000777002
	#define CAD_CURSOR_WAIT       2000777003
	#define CAD_CURSOR_APPSTART   2000777004
	#define CAD_CURSOR_UPARROW    2000777005
	#define CAD_CURSOR_NO         2000777006
	#define CAD_CURSOR_CROSS      2000777007
	#define CAD_CURSOR_HAND       2000777008


	/********************************************************************
	* CAD commands identifiers
	* for the CadExecute() function
	********************************************************************/
	// view 
	#define CAD_CMD_ZOOM_EXT          102
	#define CAD_CMD_ZOOM_IN           103
	#define CAD_CMD_ZOOM_OUT          104
	#define CAD_CMD_ZOOM_PREV         105
	#define CAD_CMD_ZOOM_WIN          106
	#define CAD_CMD_ZOOM_RTIME        107
	#define CAD_CMD_ZOOM_SEL          108
	#define CAD_CMD_PAN_RTIME         111
	#define CAD_CMD_PAN_POINT         112
	#define CAD_CMD_PAN_LEFT          113
	#define CAD_CMD_PAN_RIGHT         114
	#define CAD_CMD_PAN_UP            115
	#define CAD_CMD_PAN_DOWN          116
	#define CAD_CMD_PAGE_NEXT         121
	#define CAD_CMD_PAGE_PREV         122
	#define CAD_CMD_PAGE_FIRST        123
	#define CAD_CMD_PAGE_LAST         124
	#define CAD_CMD_PAGE_SELECT       125
	#define CAD_CMD_VIEW_TOP          131
	#define CAD_CMD_VIEW_BOTTOM       132
	#define CAD_CMD_VIEW_LEFT         133
	#define CAD_CMD_VIEW_RIGHT        134
	#define CAD_CMD_VIEW_FRONT        135
	#define CAD_CMD_VIEW_BACK         136
	#define CAD_CMD_VIEW_SW           137
	#define CAD_CMD_VIEW_SE           138
	#define CAD_CMD_VIEW_NE           139
	#define CAD_CMD_VIEW_NW           130
	#define CAD_CMD_VIEW_VPOINT       141
	#define CAD_CMD_SW_VIEW_CURLAYER  142
	#define CAD_CMD_SW_MAGNIFIER      143
	#define CAD_CMD_MBUTTONPAN        144
	#define CAD_CMD_IDFIX             145

	// draw entities
	#define CAD_CMD_DRAW_POINT        201
	#define CAD_CMD_DRAW_LINE         205
	#define CAD_CMD_DRAW_RAY          206
	#define CAD_CMD_DRAW_XLINE        207
	#define CAD_CMD_DRAW_MLINE        208
	#define CAD_CMD_DRAW_POLYLINE     209
	#define CAD_CMD_DRAW_POLYGON      210
	#define CAD_CMD_DRAW_ELLIPSE      211
	#define CAD_CMD_DRAW_RECT         212
	#define CAD_CMD_DRAW_CIRCLE       220
	#define CAD_CMD_DRAW_CIRC_CR      221
	#define CAD_CMD_DRAW_CIRC_CD      222
	#define CAD_CMD_DRAW_CIRC_2P      223
	#define CAD_CMD_DRAW_CIRC_3P      224
	#define CAD_CMD_DRAW_ARC3P        227
	#define CAD_CMD_DRAW_ARC          228
	#define CAD_CMD_DRAW_ARC_3P       229
	#define CAD_CMD_DRAW_ARC_SCE      230
	#define CAD_CMD_DRAW_ARC_SCA      231
	#define CAD_CMD_DRAW_ARC_SCL      232
	#define CAD_CMD_DRAW_ARC_SEA      233
	#define CAD_CMD_DRAW_ARC_SED      234
	#define CAD_CMD_DRAW_ARC_SER      235
	#define CAD_CMD_DRAW_ARC_CSE      236
	#define CAD_CMD_DRAW_ARC_CSA      237
	#define CAD_CMD_DRAW_ARC_CSL      238
	#define CAD_CMD_DRAW_ARC_CONT     239
	#define CAD_CMD_DRAW_SPLINE       242
	#define CAD_CMD_DRAW_TEXT         245
	#define CAD_CMD_DRAW_HATCH        246
	#define CAD_CMD_DRAW_LEADER       247
	#define CAD_CMD_DRAW_CENMARK      248
	#define CAD_CMD_DRAW_MTEXT        249
	#define CAD_CMD_DRAW_WTEXT        250
	#define CAD_CMD_INSERT_BLOCK      252
	#define CAD_CMD_INSERT_IMAGE      253
	#define CAD_CMD_INSERT_XREF       254
	#define CAD_CMD_IMAGE_MANAGER     255
	#define CAD_CMD_XREF_MANAGER      256
	#define CAD_CMD_CREATE_BLOCK      257
	#define CAD_CMD_CREATE_ATTRIB     258
	#define CAD_CMD_PLINE_ENTER       261
	#define CAD_CMD_PLINE_CLOSE       262
	#define CAD_CMD_PLINE_POLYGON     263
	#define CAD_CMD_PLINE_CANCEL      264
	#define CAD_CMD_PLINE_UNDO        265
	#define CAD_CMD_PLINE_ARC         266
	#define CAD_CMD_PLINE_LINE        267
	#define CAD_CMD_SPLINE_ENTER      271
	#define CAD_CMD_SPLINE_CLOSE      272
	#define CAD_CMD_SPLINE_POLYGON    273
	#define CAD_CMD_SPLINE_CANCEL     274
	#define CAD_CMD_SPLINE_UNDO       275
	#define CAD_CMD_MLINE_ENTER       281
	#define CAD_CMD_MLINE_CLOSE       282
	#define CAD_CMD_MLINE_CANCEL      283
	#define CAD_CMD_MLINE_UNDO        284
	#define CAD_CMD_DRAW_DIM_LIN      290
	#define CAD_CMD_DRAW_DIM_ALIGN    291
	#define CAD_CMD_DRAW_DIM_ORD      292
	#define CAD_CMD_DRAW_DIM_RAD      293
	#define CAD_CMD_DRAW_DIM_DIAM     294
	#define CAD_CMD_DRAW_DIM_ANG      295

	// edit entities
	#define CAD_CMD_UNDO              301
	#define CAD_CMD_REDO              302
	#define CAD_CMD_CBCUT             303
	#define CAD_CMD_CBCOPY            304
	#define CAD_CMD_CBPASTE           305
	#define CAD_CMD_ENTPROP           306
	#define CAD_CMD_ERASE             311
	#define CAD_CMD_COPY              312
	#define CAD_CMD_MOVE              313
	#define CAD_CMD_ROTATE            314
	#define CAD_CMD_SCALE             315
	#define CAD_CMD_MIRROR            316
	#define CAD_CMD_EXPLODE           317
	#define CAD_CMD_JOIN              318
	#define CAD_CMD_TRIM              319
	#define CAD_CMD_EXTEND            320
	#define CAD_CMD_ATTEDIT           321
	#define CAD_CMD_ATTMAN            322
	#define CAD_CMD_DEP               323
	#define CAD_CMD_PLINE_INSVER      331
	#define CAD_CMD_PLINE_DELVER      332
	#define CAD_CMD_PLINE_EDITVER     333
	#define CAD_CMD_PLINE_CONTINUE    334
	#ifdef _DASAN_
	#define CAD_CMD_PROF_INSVER      341
	#define CAD_CMD_PROF_DELVER      342
	#define CAD_CMD_PROF_EDITVER     343
	#endif 

	// object snap 
	#define CAD_CMD_SNAP_POINT        401
	#define CAD_CMD_SNAP_NODE         401
	#define CAD_CMD_SNAP_ENDPOINT     402
	#define CAD_CMD_SNAP_MIDPOINT     403
	#define CAD_CMD_SNAP_CENTER       404
	#define CAD_CMD_SNAP_NEAREST      405
	#define CAD_CMD_SNAP_INTER        406
	#define CAD_CMD_SNAP_PERPEND      407
	#define CAD_CMD_SNAP_TANGENT      408
	#define CAD_CMD_SNAP_GRIP         409
	#define CAD_CMD_SNAP_NONE         410
	#define CAD_CMD_SNAP_DLG          411
	#define CAD_CMD_SW_SHOWGRID       421
	#define CAD_CMD_SW_SNAPGRID       422
	#define CAD_CMD_SW_OSNAPON        423
	#define CAD_CMD_GRID_DLG          425
	#define CAD_CMD_POLAR_DLG         426
	#define CAD_CMD_SW_POLARON        427

	// select objects
	#define CAD_CMD_SEL_BYPOINT       501
	#define CAD_CMD_SEL_BYRECT        502
	#define CAD_CMD_SEL_BYPOLYGON     503
	#define CAD_CMD_SEL_BYPOLYLINE    504
	#define CAD_CMD_SEL_BYDIST        505  
	//#define CAD_CMD_SEL_BYDISTANCE    505  // same as .._BYDIST
	#define CAD_CMD_SEL_BYID          507
	#define CAD_CMD_SEL_BYHANDLER     507  // same as .._BYID, for compatibility with older versions
	#define CAD_CMD_SEL_BYLAYER       508
	#define CAD_CMD_SEL_BYTEXT        509
	#define CAD_CMD_SEL_BYKEY         510 
	#define CAD_CMD_SEL_BYUSERDATA    510  // same as .._BYKEY, for compatibility with older versions

	// format
	#define CAD_CMD_LAYER             801
	#define CAD_CMD_LAYERS_ORDER      802
	#define CAD_CMD_COLOR             803
	#define CAD_CMD_LINETYPE          804
	#define CAD_CMD_LINEWEIGHT        805
	#define CAD_CMD_TEXTSTYLE         806
	#define CAD_CMD_DIMSTYLE          807
	#define CAD_CMD_PNTSTYLE          808
	#define CAD_CMD_MLINESTYLE        809
	#define CAD_CMD_PAGE              810
	#define CAD_CMD_BLOCK             811
	#define CAD_CMD_SW_LINEWEIGHT     812       // switch "Display lineweights"
	#define CAD_CMD_SW_RASTER         813       // switch rasters/vectors visibility

	// misc
	#define CAD_CMD_PRINT             901
	#define CAD_CMD_PRINT_NODIALOG    902
	#define CAD_CMD_PRINTPREVIEW      903
	#define CAD_CMD_PRINTPREVIEW_END  904
	#define CAD_CMD_RESET             911
	#define CAD_CMD_REGEN             912
	#define CAD_CMD_REPEAT            913
	#define CAD_CMD_SETFOCUS          914
	#define CAD_CMD_SETVAR            915
	#define CAD_CMD_HELP              918
	#define CAD_CMD_F3                921
	#define CAD_CMD_EXPORT_AVSHP      931
	#define CAD_CMD_IMPORT_AVSHP      941
	#define CAD_CMD_RASTERIZE         942

	// tools
	#define CAD_CMD_OPTIONS           951
	#define CAD_CMD_DISTANCE          952
	#define CAD_CMD_AREA              953
	#define CAD_CMD_CALIBRATE         954
	#define CAD_CMD_DWGINFO           955
	#define CAD_CMD_DRAFT_AIDS        956
	#define CAD_CMD_LATLONG           962
	#define CAD_CMD_AREAIP            963  // get polygon area by picking an inner point
	#define CAD_CMD_DISTPLINE         964

	#define CAD_CMD_CUSTOM          11000    // base for custom commands Id's

	// custom command status
	#define CAD_CCS_LBUTTON         1    // left mouse button was clicked
	#define CAD_CCS_RBUTTON         2    // right mouse button was clicked
	#define CAD_CCS_STRING          3    // text was entered in command line
	#define CAD_CCS_ESCAPE          4    // <Esc> button is pressed

	//*** End of CAD commands *****************************************************

	// parameters for the CAD_CMD_INSERT_BLOCK command
	struct CMDPRM_INSERT_BLOCK {
	  int      bShowDialog; // if TRUE - "Insert Block" dialog will be shown, if FALSE - no
	  int      idBlock;     // identifier of block
	  int      bCoord;      // if TRUE - InsPnt is used, if FALSE - specify coords on-screen
	  double   InsPntX;     // insertion point
	  double   InsPntY;     //
	  double   InsPntZ;     //
	  int      bScale;      // if TRUE - Scale is used, if FALSE - specify scale on-screen
	  int      bUniScale;   // same scale as X for Y, Z
	  double   ScaleX;      // scale 
	  double   ScaleY;      // 
	  double   ScaleZ;      // 
	  int      bAngle;      // if TRUE - Angle is used, if FALSE - specify angle on-screen
	  double   Angle;       // rotation angle
	  int      bExplode;    // if TRUE - explode block after insertion
	  double   RowDist;     // distance between rows. (0 for no array)
	  double   ColDist;     // distance between columns. (0 for no array)
	  int      NumRows;     // number of rows. (1 for no array)
	  int      NumCols;     // number of columns. (1 for no array)
	};


	// CAD shortcut popup menus
	#define CAD_MENU_PRINTPREVIEW    1
	#define CAD_MENU_EDIT            2
	#define CAD_MENU_DEFAULT         3
	#define CAD_MENU_POLYLINE        4
	#define CAD_MENU_SPLINE          5
	#define CAD_MENU_MLINE           6
	#define CAD_MENU_PLINEEDIT       7
	#define CAD_MENU_SNAP            8
	#ifdef _DASAN_
	#define CAD_MENU_PROFEDIT        9
	#endif

	// Raster modes
	#define CAD_RM_BOTH      0  // show raster and vector objects
	#define CAD_RM_VECTOR    1  // show only vector objects
	#define CAD_RM_RASTER    2  // show only raster objects
	#define CAD_RM_MAX       2

	// Point style draw modes
	#define CAD_PS_DRAW_NONE    0   // Don't Draw
	#define CAD_PS_DRAW_BLOCK   1   // Draw Symbol Only
	#define CAD_PS_DRAW_TEXT    2   // Draw Text Only
	#define CAD_PS_DRAW_ALL     3   // Draw Symbol and Text

	// point modes (for CadDrawPoint and CadPutPointMode )
	#define CAD_PNT_PIXEL     0    // pixel
	#define CAD_PNT_NONE      1    // none
	#define CAD_PNT_PLUS      2    // plus sign through the point.
	#define CAD_PNT_X         3    // an X through the point
	#define CAD_PNT_TICK      4    // a vertical tick mark upward from the point.
	// additional elements
	#define CAD_PNT_CIRCLE    32   // circle 
	#define CAD_PNT_SQUARE    64   // square

	// Projection planes
	#define CAD_PLANE_XY     0   // top view
	#define CAD_PLANE_TOP    0 
	#define CAD_PLANE_XZ     1   // front view
	#define CAD_PLANE_FRONT  1
	#define CAD_PLANE_YZ     2   // right view
	#define CAD_PLANE_RIGHT  2

	// mouse buttons
	#define CAD_LBUTTON  1   // left button 
	#define CAD_RBUTTON  2   // right button 
	#define CAD_MBUTTON  4   // middle button 

	// key state
	#define CAD_SHIFT  1   // SHIFT key is pressed
	#define CAD_CTRL   2   // CTRL key is pressed
	#define CAD_ALT    4   // ALT key is pressed
	// Keys state for CadAccelSetKey() function
	//#define CAD_KEY_CTRL     1
	//#define CAD_KEY_SHIFT    2

	// AutoCAD version  
	#define CAD_ACAD25    0  /* ac1002 */
	#define CAD_ACAD26    1  /* ac1003 */
	#define CAD_ACAD9     2  /* ac1004 */
	#define CAD_ACAD10    3  /* ac1006 */
	#define CAD_ACAD11    4  /* ac1009 */
	#define CAD_ACAD13    5  /* ac1012 */
	#define CAD_ACAD14    6
	#define CAD_ACAD2000  7
	#define CAD_ACAD2004  8
	#define CAD_ACAD2007  9
	#define CAD_ACADMAX   9

	// Default file extention for "Open File" & "Save File" dialogs
	#define CAD_FILTER_VEC      0
	#define CAD_FILTER_DWGDXF   1
	#define CAD_FILTER_DWG      2
	#define CAD_FILTER_DXF      3
	#define CAD_FILTER_SFP      4

	// Clearing mode for CadPurge()
	#define CAD_CLEAR_ALL       0
	#define CAD_CLEAR_ENTITIES  1
	#define CAD_CLEAR_LAYER     2
	#define CAD_CLEAR_DELETED   3
	#define CAD_CLEAR_SELECTED  4
	#define CAD_CLEAR_PAGE      5
 
	// VeCAD window styles
	#define CAD_WS_HSCROLL   1
	#define CAD_WS_VSCROLL   2
	#define CAD_WS_BORDER    4
	#define CAD_WS_SUNKEN    8
	#define CAD_WS_DEFAULT   3

	// Print Stamp position (must be the same as in "DispApi.h")
	#define CAD_PST_LEFTOP     0
	#define CAD_PST_CENTOP     1
	#define CAD_PST_RIGTOP     2
	#define CAD_PST_LEFBOT     3
	#define CAD_PST_CENBOT     4
	#define CAD_PST_RIGBOT     5
	#define CAD_PST_LEFTOP90   6
	#define CAD_PST_LEFCEN90   7
	#define CAD_PST_LEFBOT90   8
	#define CAD_PST_RIGTOP90   9
	#define CAD_PST_RIGCEN90   10
	#define CAD_PST_RIGBOT90   11

	// Codepages for AutoCAD drawing
	// must be the same as CP_... (Utilit.h)
	#define CAD_CP_1250  1    // Central Europe (Latin 2)
	#define CAD_CP_1251  2    // Cyrillic
	#define CAD_CP_1252  3    // Latin 1
	#define CAD_CP_1253  4    // Greek
	#define CAD_CP_1254  5    // Turkish
	#define CAD_CP_1255  6    // Hebrew
	#define CAD_CP_1256  7    // Arabic
	#define CAD_CP_1257  8    // Windows Baltic
	#define CAD_CP_874   9    // Thai
	#define CAD_CP_932   101  // JIS/Japan
	#define CAD_CP_936   102  // Chinese: Simplified chars - PRC and Singapore
	#define CAD_CP_949   103  // Korean Extended Wansung
	#define CAD_CP_950   104  // Chinese: Traditional chars - Taiwan, Hong Kong

	// "Draw Modes" for multiline style (same as MLSTYLE_...)
	#define CAD_MLS_SHOW_MITERS         2    
	#define CAD_MLS_START_SQUARE        16   
	#define CAD_MLS_START_ROUND         64   
	#define CAD_MLS_END_SQUARE          256  
	#define CAD_MLS_END_ROUND           1024 

	// Juctification values (must be the same as in "..\odt\ad2.h") (also MLINE_JUST_...)
	#define CAD_MLINE_JUST_TOP          0  // justified from top
	#define CAD_MLINE_JUST_ZERO         1  // justified from center
	#define CAD_MLINE_JUST_BOTTOM       2  // justified from bottom

	// Error codes (CadGetError())
	#define CAD_ERROR_INVALID_ID        1      // invalid identifier
	#define CAD_ERROR_ONE_PAGE          101    // can't delete page - only one remains
	#define CAD_ERROR_PAGE_NOT_EMPTY    102    // can't delete page - not empty
	#define CAD_ERROR_DEL_LAYER0        111    // can't delete layer 0
	#define CAD_ERROR_DEL_CURLAYER      112    // can't delete current layer
	#define CAD_ERROR_LAYER_NOT_EMPTY   113    // can't delete layer - not empty
	#define CAD_ERROR_DEL_DIMSSTD       121    // can't delete "standard" dim. style
	#define CAD_ERROR_DEL_DIMSREF       122    // can't delete dim. style which has references
	#define CAD_ERROR_DEL_LTYPESTD      131    //
	#define CAD_ERROR_DEL_LTYPEREF      132    //
	#define CAD_ERROR_DEL_TXTSSTD       141
	#define CAD_ERROR_DEL_TXTSREF       142
	#define CAD_ERROR_DEL_PNTSSTD       151
	#define CAD_ERROR_DEL_PNTSREF       152
	#define CAD_ERROR_DEL_MLSSTD        161
	#define CAD_ERROR_DEL_MLSREF        162
	#define CAD_ERROR_DEL_BLKREF        163

	// error codes
	//#define CAD_ERR_CANT_OPEN_FILE  1

	// Type of grid's elements
	#define CAD_GRID_POINT     0
	#define CAD_GRID_LINE      1
	#define CAD_GRID_DOTLINE   2
	// Grid's level
	#define CAD_GRID_BELOW     0
	#define CAD_GRID_ABOVE     1

	// Snap modes
	#define CAD_SNAP_POINT       1       // to "Point" entity
	#define CAD_SNAP_NODE        1       // to "Point" entity
	#define CAD_SNAP_ENDPOINT    2       // to endpoint of Line, Polyline, Arc
	#define CAD_SNAP_MIDPOINT    4       // to middle of Line, Polyline segment, Arc
	#define CAD_SNAP_CENTER      8       // to center of Circle, Arc, Ellipce
	#define CAD_SNAP_NEAREST    16       // to nearest point on line of any object
	#define CAD_SNAP_INTER      32       // to intersection of any lines of any objects
	#define CAD_SNAP_PERPEND    64       // to perpendicular (also apparent)
	#define CAD_SNAP_TANGENT   128       // to tangent point on Circle, Arc, Ellipse
	#define CAD_SNAP_GRIP      256       // to grips poisitions on Entities
	#define CAD_SNAP_ALL       511       // all modes
	#define CAD_SNAP_POLAR    1000       // for inner use
	#define CAD_SNAP_IPOLAR   1001       // for inner use
 
	// Increment angles for Polar Tracking
	#define CAD_POLAR_90   0
	#define CAD_POLAR_45   1
	#define CAD_POLAR_30   2
	#define CAD_POLAR_23   3
	#define CAD_POLAR_18   4
	#define CAD_POLAR_15   5
	#define CAD_POLAR_10   6
	#define CAD_POLAR_5    7

	// angular units for API functions
	#define CAD_ANGLE_DEGREE  0   // decimal degree
	#define CAD_ANGLE_RADIAN  3   // radian
	#define CAD_ANGLE_GRAD    4   // grad

	// type of combobox control
	#define CAD_CBOX_LAYER     101
	#define CAD_CBOX_COLOR     102
	#define CAD_CBOX_LINETYPE  103
	#define CAD_CBOX_LWEIGHT   104
	#define CAD_CBOX_DIMSTYLE  105

	// position of Magnifier window on the VeCAD window
	#define CAD_MAG_LEFBOT     0
	#define CAD_MAG_LEFTOP     1
	#define CAD_MAG_RIGBOT     2
	#define CAD_MAG_RIGTOP     3

	// Navigatir parameters
	#define CAD_NAV_LEFT       0
	#define CAD_NAV_TOP        1
	#define CAD_NAV_WIDTH      2
	#define CAD_NAV_HEIGHT     3
	#define CAD_NAV_EXIST      4
	#define CAD_NAV_CHILD      256
	#define CAD_NAV_SUNKEN     512
	#define CAD_NAV_CPANEL     1024

	// parameters for CadDrawSet()
	#define CAD_CE_CLEARVERS    0
	#define CAD_CE_KEEPVERS     1
	#define CAD_CE_BRUSH        2
	#define CAD_CE_COLOR        3

	// parameters for CadAddCustProp()
	#define CAD_PROP_VALUE      1
	#define CAD_PROP_YESNO      2
	#define CAD_PROP_LIST       3
	#define CAD_PROP_SEPARATOR  4
	#define CAD_PROP_READONLY   256

	// possible return values of the CadXrefGetStatus()
	#define CAD_XREF_NOXREF       0
	#define CAD_XREF_LOADED       1
	#define CAD_XREF_NOTLOADED    2
	#define CAD_XREF_NOTFOUND     3



	//*******************************************************************
	// Strings Identifiers
	//*******************************************************************
	#define STR_VECAD               1
	#define STR_VECAD_PRINT         3
	#define STR_FILTER_VDFILE       9
	#define STR_VEC_EXT             10
	#define STR_FILTER_VEC          11
	#define STR_OLD_VEC_FORMAT      101
	#define STR_UNKNOWN_VEC_FORMAT  102
	#define STR_NEWER_VEC_FORMAT    103
	#define STR_NEWFILENAME         104
	#define STR_SAVE_CHANGES        105
	#define STR_SAVE_AS             106
	#define STR_UNDO_EMPTY          107
	#define STR_REDO_EMPTY          108
	#define STR_DID_YOU_KNOW        109
	#define STR_NO_TIP_FILE         110
	#define STR_NO_TIPS             111
	#define STR_REGEN               112
	#define STR_YES                 113
	#define STR_NO                  114
	#define STR_REWRITE_FILE        115
	#define STR_NO_BLOCKS           116
	#define STR_INVALID_LATITUDE    117
	#define STR_INVALID_LONGITUDE   118
	#define STR_BULGE_TITLE         121
	#define STR_BULGE_PROMPT        122
	#define STR_SELECT_OBJECT       123
	#define STR_N_ENT_SELECTED      124
	#define STR_ENTER_HANDLER       125
	#define STR_ENTER_USERDATA      126
	#define STR_ENTER_TEXT          127
	#define STR_LAYERS_ORDER        128
	#define STR_CANT_OPEN_FILE      131
	#define STR_CANT_LOAD_FILE      132
	#define STR_IS_BIGFONT          133
	#define STR_ISNOT_BIGFONT       134
	#define STR_UNDEFINED           135
	#define STR_UNKNOWN             136
	#define STR_SHX_UNDEFINED       137
	#define STR_VCF_FILEEXIST       138
	#define STR_VCF_CREATED         139
	#define STR_VCF_REPLFONT1       140
	#define STR_VCF_REPLFONT2       141
	#define STR_VCF_REPL_TSTYLE     142
	#define STR_VCF_REPL_PSTYLE     143
	#define STR_UNITS_METERS        151
	#define STR_UNITS_DEGREES       152
	#define STR_UNITS_FEET          153

	#define STR_SELECT_ENTITIES     301
	#define STR_SELECTION           302
	#define STR_PICK_ENTITY         303
	#define STR_NOT_LATLONG_ENTITY  304

	#define STR_MENU_EXIT           401
	#define STR_MENU_PRINT          402
	#define STR_MENU_ZOOMEXT        403
	#define STR_MENU_ZOOMRT         404
	#define STR_MENU_PANRT          405
	#define STR_MENU_UNSELALL       406
	#define STR_MENU_PROPS          407
	#define STR_MENU_COPY           408
	#define STR_MENU_MOVE           409
	#define STR_MENU_ROTATE         410
	#define STR_MENU_SCALE          411
	#define STR_MENU_MIRROR         412
	#define STR_MENU_EXPLODE        413
	#define STR_MENU_JOIN           414
	#define STR_MENU_ERASE          415
	#define STR_MENU_CREBLOCK       416
	#define STR_MENU_REPEAT         417
	#define STR_MENU_ZOOMWIN        418
	#define STR_MENU_ZOOMPREV       419
	#define STR_MENU_UNDO           420
	#define STR_MENU_REDO           421
	#define STR_MENU_AIDS           422
	#define STR_MENU_OPTIONS        423
	#define STR_MENU_ENTER          424
	#define STR_MENU_CLOSED         425
	#define STR_MENU_POLYGON        426
	#define STR_MENU_LINE           427
	#define STR_MENU_ARC            428
	#define STR_MENU_CANCEL         430
	#define STR_MENU_INSVER         431
	#define STR_MENU_DELVER         432
	#define STR_MENU_EDITVER        433
	#define STR_MENU_MAGNIFIER      434
	#define STR_MENU_CONTINUE       435
	#define STR_MENU_SNAP_ENDPOINT  441
	#define STR_MENU_SNAP_MIDPOINT  442
	#define STR_MENU_SNAP_CENTER    443
	#define STR_MENU_SNAP_NEAREST   444
	#define STR_MENU_SNAP_INTER     445
	#define STR_MENU_SNAP_PERPEND   446
	#define STR_MENU_SNAP_TANGENT   447
	#define STR_MENU_SNAP_GRIP      448
	#define STR_MENU_SNAP_POINT     449
	#define STR_MENU_SNAP_DLG       451
	#define STR_MENU_POLAR_DLG      452

	#define STR_NAV_TITLE           501
	#define STR_NAV_IN              502
	#define STR_NAV_OUT             503

	#define STR_PRINT_ALBUM       27151
	#define STR_PRINT_BOOK        27152
	#define STR_PRINT_INCH        27153
	#define STR_PRINT_MM          27154
	#define STR_PRINT_PREVIEW     27155

	#define STR_PST_LEFTOP        27161
	#define STR_PST_CENTOP        27162
	#define STR_PST_RIGTOP        27163
	#define STR_PST_LEFBOT        27164
	#define STR_PST_CENBOT        27165
	#define STR_PST_RIGBOT        27166
	#define STR_PST_LEFTOP90      27167
	#define STR_PST_LEFCEN90      27168
	#define STR_PST_LEFBOT90      27169
	#define STR_PST_RIGTOP90      27170
	#define STR_PST_RIGCEN90      27171
	#define STR_PST_RIGBOT90      27172
	#define STR_NO_EFF_RECT       27182
	#define STR_CREATE_PREVIEW    27183
	#define STR_PAPERSIZE         27184
	#define STR_SCALE             27185

	#define STR_BYLAYER           27203
	#define STR_BYBLOCK           27204
	#define STR_DEFAULT           27205

	#define STR_WARNING           27207

	#define STR_DELETE_TEXT_STYLE  27210
	#define STR_NEW_TEXT_STYLE     27211
	#define STR_RENAME_TEXT_STYLE  27212
	#define STR_STYLE_NAME         27213
	#define STR_STYLE_NAME_EXIST   27214

	#define STR_OPT_TITLE         27301
	#define STR_OPT_DISPLAY       27302
	#define STR_OPT_EXPORT        27303
	#define STR_OPT_SELECTION     27304 
	#define STR_OPT_USERPREF      27305
	#define STR_OPT_PROFILES      27306
	#define STR_OPT_DRAFTING      27307
	#define STR_OPT_PLUGINS       27308
	#define STR_OPT_ACADVER2007   27319
	#define STR_OPT_ACADVER2004   27320
	#define STR_OPT_ACADVER2000   27321
	#define STR_OPT_ACADVER14     27322
	#define STR_OPT_ACADVER13     27323
	#define STR_OPT_ACADVER11     27324
	#define STR_OPT_ACADVER10     27325
	#define STR_OPT_ACADVER9      27326
	#define STR_OPT_ACADVER26     27327
	#define STR_OPT_ACADVER25     27328
	#define STR_PRF_ADD           27331
	#define STR_PRF_RENAME        27332
	#define STR_PRF_NAMEEXIST     27333
	#define STR_SEL_SOLID         27341
	#define STR_SEL_DASH          27342
	#define STR_SEL_DOT           27343

	#define STR_LAYER_0           27400
	#define STR_LAY_HDRNAME       27401
	#define STR_LAY_HDRON         27402
	#define STR_LAY_HDRLOCK       27403
	#define STR_LAY_HDRCOLOR      27404
	#define STR_LAY_HDRLTYPE      27405
	#define STR_LAY_HDRLWEIGHT    27406
	#define STR_LAY_HDRPRINT      27407
	#define STR_LAY_CURRENT       27411
	#define STR_LAY_STATUS        27412
	#define STR_LAY_SHOW_ALL      27415
	#define STR_LAY_SHOW_USED     27416
	#define STR_LAY_SHOW_UNUSED   27417

	#define STR_LT_HDRNAME        27431
	#define STR_LT_HDRAPPEAR      27432
	#define STR_LT_HDRDESC        27433
	#define STR_LT_CURRENT        27434
	#define STR_LT_SHOW_ALL       27435
	#define STR_LT_SHOW_USED      27436
	#define STR_LT_SHOW_UNUSED    27437
	#define STR_LT_EXIST          27438
	#define STR_LT_CONTINUOUS     27441

	#define STR_IMG_HDRNAME       27451
	#define STR_IMG_HDRSTATUS     27452
	#define STR_IMG_HDRREF        27453
	#define STR_IMG_HDRSIZE       27454
	#define STR_IMG_HDRTYPE       27455
	#define STR_IMG_HDRDATE       27456
	#define STR_IMG_HDRPATH       27457
	#define STR_IMG_LOADED        27458
	#define STR_IMG_UNREF         27459
	#define STR_IMG_NOTFOUND      27460
	#define STR_IMG_UNLOADED      27461

	#define STR_BLK_NSEL          27465
	#define STR_BLK_NSEL0         27466
	#define STR_BLK_NONAME        27468
	#define STR_BLK_NOTHING       27469
	#define STR_BLK_EXIST         27470
	#define STR_BLK_SELFREF       27471
	#define STR_BLK_DRAWING       27475
	#define STR_BLK_RENAME        27476
	#define STR_BLK_NEWNAME       27477
	#define STR_BLK_DUPNAME       27478
	#define STR_BLK_NUMDELETED    27479

	#define STR_PS_HDR_NAME       27481
	#define STR_PS_HDR_STATE      27482
	#define STR_PS_HDR_BLOCK      27483
	#define STR_PS_HDR_SCALE      27484
	#define STR_PS_HDR_FONT       27485
	#define STR_PS_HDR_HEIGHT     27486
	#define STR_PS_HDR_WIDTH      27487
	#define STR_PS_HDR_SNAP       27488
	#define STR_PS_HDR_MOVE       27489
	#define STR_PS_SHOW_ALL       27491
	#define STR_PS_SHOW_USED      27492
	#define STR_PS_SHOW_UNUSED    27493
	#define STR_PS_CURRENT        27495
	#define STR_PS_DRAW_NONE      27501
	#define STR_PS_DRAW_SYMBOL    27502
	#define STR_PS_DRAW_TEXT      27503
	#define STR_PS_DRAW_ALL       27504
	#define STR_PS_SIMPLE         27511
	#define STR_PS_PDMODE_POINT   27514
	#define STR_PS_PDMODE_PLUS    27515
	#define STR_PS_PDMODE_X       27516
	#define STR_PS_PDMODE_TICK    27517
	#define STR_PS_PDMODE_CIRCLE  27518
	#define STR_PS_PDMODE_RECT    27519

	#define STR_TSTYLE_STANDARD   27531

	#define STR_PAGE_MODEL        27535

	#define STR_MLS_STANDARD      27541
	#define STR_MLS_TOP           27543
	#define STR_MLS_CENTER        27544
	#define STR_MLS_BOTTOM        27545
	#define STR_MLS_OFF_TITLE     27546
	#define STR_MLS_OFF_PROMPT    27547

	#define STR_DIMS_STANDARD     27561
	#define STR_DIMS_NONE         27562
	#define STR_DIMS_MARK         27563
	#define STR_DIMS_LINE         27564
	#define STR_DIMS_ARR_0        27570
	#define STR_DIMS_ARR_1        27571
	#define STR_DIMS_ARR_2        27572
	#define STR_DIMS_ARR_3        27573
	#define STR_DIMS_ARR_4        27574
	#define STR_DIMS_ARR_5        27575
	#define STR_DIMS_ARR_6        27576
	#define STR_DIMS_ARR_7        27577
	#define STR_DIMS_ARR_8        27578
	#define STR_DIMS_ARR_9        27579
	#define STR_DIMS_ARR_10       27580
	#define STR_DIMS_ARR_11       27581
	#define STR_DIMS_ARR_12       27582
	#define STR_DIMS_ARR_13       27583
	#define STR_DIMS_ARR_14       27584
	#define STR_DIMS_ARR_15       27585
	#define STR_DIMS_ARR_16       27586
	#define STR_DIMS_ARR_17       27587
	#define STR_DIMS_ARR_18       27588
	#define STR_DIMS_ARR_19       27589
	#define STR_DIMS_SCIENTIFIC   27600
	#define STR_DIMS_DECIMAL      27601
	#define STR_DIMS_ENGINEER     27602
	#define STR_DIMS_ARCHITEC     27603
	#define STR_DIMS_FRACTION     27604
	#define STR_DIMS_DECDEGREE    27610
	#define STR_DIMS_DEGMINSEC    27611
	#define STR_DIMS_GRAD         27612
	#define STR_DIMS_RADIAN       27613
	#define STR_DIMS_CENTERED     27615
	#define STR_DIMS_ABOVE        27616
	#define STR_DIMS_HORIZ        27621
	#define STR_DIMS_ALIGNED      27622
	#define STR_DIMS_ISOSTD       27623
	#define STR_DIMS_PERIOD       27631
	#define STR_DIMS_COMMA        27632
	#define STR_DIMS_SPACE        27633

	#define STR_PROP_TITLE        28481
	#define STR_PROP_NOFILE       28482
	#define STR_PROP_NOSEL        28483
	#define STR_PROP_ALL          28485

	#define STR_PROP_POINT        28501
	#define STR_PROP_LINE         28502
	#define STR_PROP_POLYLINE     28503
	#define STR_PROP_CIRCLE       28504
	#define STR_PROP_ARC          28505
	#define STR_PROP_ELLIPSE      28506
	#define STR_PROP_TEXT         28507
	#define STR_PROP_INSBLOCK     28508
	#define STR_PROP_SHAPE        28509
	#define STR_PROP_3DFACE       28510
	#define STR_PROP_SOLID        28511
	#define STR_PROP_IMAGE        28512
	#define STR_PROP_DIM          28513
	#define STR_PROP_HATCH        28514
	#define STR_PROP_LEADER       28515
	#define STR_PROP_MLINE        28516
	#define STR_PROP_3DMESH       28517
	#define STR_PROP_POLYFACE     28518
	#define STR_PROP_XLINE        28519
	#define STR_PROP_RAY          28520
	#define STR_PROP_XREF         28521
	#define STR_PROP_VPORT        28522
	#define STR_PROP_ATTRIB       28523
	#define STR_PROP_RECT         28524
	#define STR_PROP_MTEXT        28525
	#define STR_PROP_WINTEXT      28526
	#define STR_PROP_CUSTOM       28529
	#define STR_PROP_EXTENTS      28531
	#define STR_PROP_XMIN         28532
	#define STR_PROP_YMIN         28533
	#define STR_PROP_ZMIN         28534
	#define STR_PROP_XMAX         28535
	#define STR_PROP_YMAX         28536
	#define STR_PROP_ZMAX         28537
	#define STR_PROP_VIEW         28538
	#define STR_PROP_XCEN         28539
	#define STR_PROP_YCEN         28540
	#define STR_PROP_ZCEN         28541
	#define STR_PROP_WIDTH        28542
	#define STR_PROP_HEIGHT       28543
	#define STR_PROP_GENERAL      28601
	#define STR_PROP_HANDLER      28602
	#define STR_PROP_COLOR        28603
	#define STR_PROP_LAYER        28604
	#define STR_PROP_LINETYPE     28605
	#define STR_PROP_LTSCALE      28606
	#define STR_PROP_LWEIGHT      28607
	#define STR_PROP_TEXTSTYLE    28608
	#define STR_PROP_PNTSTYLE     28609
	#define STR_PROP_MLINESTYLE   28610
	#define STR_PROP_DIMSTYLE     28611
	#define STR_PROP_FILLED       28615
	#define STR_PROP_BORDER       28616
	#define STR_PROP_USERDATA     28617
	#define STR_PROP_BCOLOR       28618
	#define STR_PROP_GEOMETRY     28651
	#define STR_PROP_STARTX       28652
	#define STR_PROP_STARTY       28653
	#define STR_PROP_STARTZ       28654
	#define STR_PROP_ENDX         28655
	#define STR_PROP_ENDY         28656
	#define STR_PROP_ENDZ         28657
	#define STR_PROP_DX           28658
	#define STR_PROP_DY           28659
	#define STR_PROP_DZ           28660
	#define STR_PROP_LENGTH       28661
	#define STR_PROP_AREA         28662
	#define STR_PROP_ANGLE        28663
	#define STR_PROP_RADIUS       28664
	#define STR_PROP_RAD_H        28665
	#define STR_PROP_RAD_V        28666
	#define STR_PROP_ANG_START    28667
	#define STR_PROP_ANG_ARC      28668
	#define STR_PROP_ANG_ROT      28669
	#define STR_PROP_SECTOR       28670
	#define STR_PROP_CONTENTS     28677
	#define STR_PROP_STYLE        28678
	#define STR_PROP_ALIGNMENT    28679
	#define STR_PROP_ROTANG       28681
	#define STR_PROP_WIDFACTOR    28682
	#define STR_PROP_OBLIQUE      28683
	#define STR_PROP_POSX         28684
	#define STR_PROP_POSY         28685
	#define STR_PROP_POSZ         28686
	#define STR_PROP_UPSIDEDOWN   28687
	#define STR_PROP_BACKWARD     28688
	#define STR_PROP_HOLLOW       28689
	#define STR_PROP_SCALE        28690
	#define STR_PROP_SCALEX       28691
	#define STR_PROP_SCALEY       28692
	#define STR_PROP_SCALEZ       28693
	#define STR_PROP_IMGSCALEX    28694
	#define STR_PROP_IMGSCALEY    28695
	#define STR_PROP_IMGSCALEX2   28696
	#define STR_PROP_IMGSCALEY2   28697
	#define STR_PROP_NAME         28698
	#define STR_PROP_PATH         28699
	#define STR_PROP_BLKANGLE     28701
	#define STR_PROP_TEXTANGLE    28702
	#define STR_PROP_TEXTDX       28703
	#define STR_PROP_TEXTDY       28704
	#define STR_PROP_FIXED        28705
	#define STR_PROP_DUPLICATE    28708
	#define STR_PROP_BLOCKNAME    28709
	#define STR_PROP_COLUMNS      28710
	#define STR_PROP_COLDIST      28711
	#define STR_PROP_ROWS         28712
	#define STR_PROP_ROWDIST      28713
	#define STR_PROP_CLOSED       28714
	#define STR_PROP_NVERS        28715
	#define STR_PROP_FITTYPE      28716
	#define STR_PROP_STARTVECX    28717
	#define STR_PROP_STARTVECY    28718
	#define STR_PROP_STARTVECZ    28719
	#define STR_PROP_ENDVECX      28720
	#define STR_PROP_ENDVECY      28721
	#define STR_PROP_ENDVECZ      28722
	#define STR_PROP_GWIDTH       28723
	#define STR_PROP_GZ           28724
	#define STR_PROP_BASEX        28725
	#define STR_PROP_BASEY        28726
	#define STR_PROP_BASEZ        28727
	#define STR_PROP_DIRX         28728
	#define STR_PROP_DIRY         28729
	#define STR_PROP_DIRZ         28730
	#define STR_PROP_JUST         28731
	#define STR_PROP_PATNAME      28732
	#define STR_PROP_POSLEF       28735
	#define STR_PROP_POSTOP       28736
	#define STR_PROP_POSRIG       28737
	#define STR_PROP_POSBOT       28738
	#define STR_PROP_PIXW         28739
	#define STR_PROP_PIXH         28740
	#define STR_PROP_COMPRATE     28741
	#define STR_PROP_NBANDS       28742
	#define STR_PROP_DATUM        28743
	#define STR_PROP_PROJECTION   28744
	#define STR_PROP_UNITS        28745
	#define STR_PROP_MEASUREMENT  28751
	#define STR_PROP_TEXTOVER     28752
	#define STR_PROP_SPLINE       28753
	#define STR_PROP_ANNOTATION   28754
	#define STR_PROP_TAG          28761
	#define STR_PROP_PROMPT       28762
	#define STR_PROP_DEFVALUE     28763
	#define STR_PROP_ATTRIBUTES   28764
	#define STR_PROP_TEXTDZ       28771
	#define STR_PROP_LINESPACE    28772
	#define STR_PROP_MIDX         28781
	#define STR_PROP_MIDY         28782
	#define STR_PROP_MIDZ         28783
	#define STR_PROP_ARC3P        28785
	#define STR_PROP_DSTYLE       28786
	#define STR_PROP_TSTYLE       28787
	#define STR_PROP_DCOLOR       28788
	#define STR_PROP_ARSIZE       28789
	#define STR_PROP_DIMGAP       28790
	#define STR_PROP_THEIGHT      28791
	#define STR_PROP_VISIBLE      28792
	#define STR_PROP_ITALIC       28793
	#define STR_PROP_STRIKEOUT    28794
	#define STR_PROP_UNDERLINE    28795
	#define STR_PROP_TTFONT       28796
	#define STR_PROP_TRANSP       28797
	#define STR_PROP_RGBCOLOR     28798
	#define STR_PROP_CODE         28801

	#define STR_PROP_RPLAN_AREA     28901
	#define STR_PROP_RPLAN_IZO      28902
	#define STR_PROP_RPLAN_IZB      28903
	#define STR_PROP_RPLAN_ROAD     28904
	#define STR_PROP_RPLAN_GPT      28905

	#define STR_PROP_RPROF_HSCALE    28911
	#define STR_PROP_RPROF_VSCALE    28912
	#define STR_PROP_RPROF_DRAWLINE  28913
	#define STR_PROP_RPROF_DRAWCURVE 28914
	#define STR_PROP_RPROF_LINECOLOR 28915
	#define STR_PROP_RPROF_LINELW    28916

	#define STR_AID_TITLE           29001
	#define STR_GRID_TITLE          29002
	#define STR_SNAP_TITLE          29003
	#define STR_POLAR_TITLE         29004
	#define STR_POLAR_ADD_ANGLE     29005
	#define STR_POLAR_ENTER_ANGLE   29006
	#define STR_POLAR_ANGLE_EXIST   29007
	#define STR_POLAR_ANGLES_FULL   29008
	#define STR_POLAR_ANGLE_OUTRANGE 29009

	#define STR_LEADER_CREATE       29011
	#define STR_LEADER_ENTER_TEXT   29012

	#define STR_COMMAND           29052
	#define STR_UNKNOWN_COMMAND   29053
	#define STR_INVALID_VALUE     29054

	// command name
	#define STR_CMD_ZOOMWIN       29101
	#define STR_CMD_ZOOMPAN       29102
	#define STR_CMD_ZOOMRT        29103
	#define STR_CMD_PANRT         29104
	#define STR_CMD_PRINT         29105
	#define STR_CMD_DIST          29106
	#define STR_CMD_AREA          29107
	#define STR_CMD_CALIBRATE     29108
	#define STR_CMD_EXPBMP        29109
	#define STR_CMD_LINE          29111
	#define STR_CMD_CIRCLE        29112
	/*
	#define STR_CMD_CIRC_CR       29112
	#define STR_CMD_CIRC_CD       29113
	#define STR_CMD_CIRC_2P       29114
	#define STR_CMD_CIRC_3P       29115
	*/
	#define STR_CMD_ARC           29117
	#define STR_CMD_ATTDEF        29118
	#define STR_CMD_ATTEDIT       29119
	#define STR_CMD_ATTMAN        29120
	#define STR_CMD_ELLIPSE       29123
	#define STR_CMD_POLYLINE      29125
	#define STR_CMD_SPLINE        29128
	#define STR_CMD_IMAGES        29129
	#define STR_CMD_IMAGE_ATTACH  29130
	#define STR_CMD_TEXT          29131
	#define STR_CMD_BLOCK         29132
	#define STR_CMD_INSERT        29133
	#define STR_CMD_POINT         29134
	#define STR_CMD_RAY           29135
	#define STR_CMD_XLINE         29136
	#define STR_CMD_MLINE         29137
	#define STR_CMD_POLYGON       29138
	#define STR_CMD_RECT          29139
	#define STR_CMD_XREFS         29140
	#define STR_CMD_XREF_ATTACH   29141
	#define STR_CMD_HATCH         29142
	#define STR_CMD_DIMLIN        29143
	#define STR_CMD_DIMALI        29144
	#define STR_CMD_DIMORD        29145
	#define STR_CMD_DIMRAD        29146
	#define STR_CMD_DIMDIA        29147
	#define STR_CMD_DIMANG        29148
	#define STR_CMD_CENMARK       29149
	#define STR_CMD_LEADER        29150
	#define STR_CMD_ERASE         29151
	#define STR_CMD_COPY          29152
	#define STR_CMD_MOVE          29153
	#define STR_CMD_ROTATE        29154
	#define STR_CMD_SCALE         29155
	#define STR_CMD_MIRROR        29156
	#define STR_CMD_ENTPROP       29157
	#define STR_CMD_CONVERT       29161
	#define STR_CMD_EXPLODE       29162
	#define STR_CMD_JOIN          29163
	#define STR_CMD_CBCUT         29164
	#define STR_CMD_CBCOPY        29165
	#define STR_CMD_CBPASTE       29166
	#define STR_CMD_SELBYPOINT    29171
	#define STR_CMD_SELBYRECT     29172
	#define STR_CMD_SELBYPGON     29173
	#define STR_CMD_SELBYPLINE    29174
	#define STR_CMD_SELBYDIST     29175
	#define STR_CMD_TRIM          29181
	#define STR_CMD_EXTEND        29182
	#define STR_CMD_DEP           29183
	#define STR_CMD_MTEXT         29190
	#define STR_CMD_WTEXT         29191
	#define STR_CMD_REPEAT        29199

	// prompts for commands
	#define STR_PNT_POINT         29201
	#define STR_LINE_FIRST        29202
	#define STR_LINE_NEXT         29203
	#define STR_LINE_START        29204
	#define STR_LINE_BASE         29205
	#define STR_LINE_TROUGH       29206
	#define STR_MLINE_NEXT        29207
	#define STR_PLINE_FIRST       29211
	#define STR_PLINE_NEXT        29212
	#define STR_SPLINE_NEXT       29213
	#define STR_SPLINE_STARTTAN   29214
	#define STR_SPLINE_ENDTAN     29215
	#define STR_PGON_CENTER       29216
	#define STR_PGON_START        29217
	#define STR_RECT_CORNER1      29218
	#define STR_RECT_CORNER2      29219
	#define STR_CIRC_CENTER       29221
	#define STR_CIRC_RADIUS       29222
	#define STR_CIRC_DIAMETER     29223
	#define STR_CIRC_D1           29224
	#define STR_CIRC_D2           29225
	#define STR_CIRC_P1           29226
	#define STR_CIRC_P2           29227
	#define STR_CIRC_P3           29228
	#define STR_ARC_START         29231
	#define STR_ARC_SECOND        29232
	#define STR_ARC_END           29233
	#define STR_ARC_CENTER        29271
	#define STR_ARC_CENTER2       29272
	#define STR_ARC_START2        29273
	#define STR_ARC_END2          29274
	#define STR_ARC_ANGLE         29275
	#define STR_ARC_DIRANG        29276
	#define STR_ARC_RADIUS        29277
	#define STR_ARC3_START        29281
	#define STR_ARC3_SECOND       29282

	#define STR_ELLIP_CENTER      29234
	#define STR_ELLIP_RAD1ANG     29235
	#define STR_ELLIP_RAD2        29236
	#define STR_IMAGE_INSPNT      29241
	#define STR_IMAGE_SCALE       29242
	#define STR_TEXT_INSPNT       29243
	#define STR_TEXT_HEIGHT       29244
	#define STR_TEXT_ANGLE        29245
	#define STR_TEXT_TEXT         29246 
	#define STR_MTEXT_CORNER1     29247
	#define STR_MTEXT_CORNER2     29248
	#define STR_BLK_BASE          29250
	#define STR_INS_INSPNT        29251
	#define STR_INS_SCALE         29252
	#define STR_INS_ANGLE         29253
	#define STR_XREF_INSPNT       29258
	#define STR_XREF_SCALE        29259
	#define STR_HAT_PICKPOINT     29263
	#define STR_HAT_NOBOUNDARY    29264
	#define STR_HAT_PICKENT       29265
	#define STR_MOVE_1            29301
	#define STR_MOVE_2            29302
	#define STR_MOVE_3            29303
	#define STR_ROTATE_BASE       29304
	#define STR_ROTATE_ANGLE      29305
	#define STR_SCALE_BASE        29306
	#define STR_SCALE_SCALE       29307
	#define STR_MIRROR_1          29308
	#define STR_MIRROR_2          29309
	#define STR_TRIM_1            29311
	#define STR_TRIM_2            29312
	#define STR_EXTEND_1          29313
	#define STR_EXTEND_2          29314
	#define STR_DEP_DELTA         29321
	#define STR_ZOOM_CORNER1      29401
	#define STR_ZOOM_CORNER2      29402
	#define STR_ZOOM_RT           29403
	#define STR_PAN_BASE          29405
	#define STR_PAN_DISP          29406
	#define STR_PAN_RT            29407
	#define STR_PRINT_CORNER1     29410
	#define STR_PRINT_CORNER2     29411
	#define STR_DIM_EXT1          29420
	#define STR_DIM_EXT2          29421
	#define STR_DIM_LINE          29422
	#define STR_DIM_ORD1          29423
	#define STR_DIM_ORD2          29424
	#define STR_DIM_SELARC        29425
	#define STR_DIM_SELALINE      29426
	#define STR_DIM_ANGEND        29427
	#define STR_DIM_LINE2         29428
	#define STR_DIM_ARC           29429
	#define STR_LEADER_FIRST      29430
	#define STR_LEADER_NEXT       29431
	#define STR_LEADER_ANNTEXT    29432
	#define STR_ATT_SELBLOCK      29441
	#define STR_ATT_NOATTBLOCK    29442
	#define STR_ATT_NOATTBLOCK2   29443
	#define STR_ATT_NOBLOCK       29444
	#define STR_ATT_NOENT         29445
	#define STR_AREA_INPNT        29451
	#define STR_AREA_RESULT       29452
	#define STR_AREA_PT1          29453
	#define STR_AREA_PT2          29454
	#define STR_AREA_PT3          29455
	#define STR_DIST_PT1          29456
	#define STR_DIST_PT2          29457
	#define STR_DIST_RESULT       29458
	#define STR_DIST_PLINE        29459

	// text alignments
	#define STR_TA_BOTLEFT        29601
	#define STR_TA_BOTCENTER      29602
	#define STR_TA_BOTRIGHT       29603
	#define STR_TA_MIDLEFT        29604
	#define STR_TA_MIDCENTER      29605
	#define STR_TA_MIDRIGHT       29606
	#define STR_TA_TOPLEFT        29607
	#define STR_TA_TOPCENTER      29608
	#define STR_TA_TOPRIGHT       29609

	// polyline smoothing types
	#define STR_FITTYPE_NONE      29611
	#define STR_FITTYPE_QUAD      29612
	#define STR_FITTYPE_CUBIC     29613
	#define STR_FITTYPE_BEZIER    29614
	#define STR_FITTYPE_SPLINE    29615
	#define STR_FITTYPE_ROUND     29616
	#define STR_FITTYPE_LINQUAD   29617

	// printer paper size
	#define STR_PAPER_UNLIMITED   29621
	#define STR_PAPER_A0          29622
	#define STR_PAPER_A1          29623
	#define STR_PAPER_A2          29624
	#define STR_PAPER_A3          29625
	#define STR_PAPER_A4          29626
	#define STR_PAPER_A5          29627
	#define STR_PAPER_A6          29628
	#define STR_PAPER_B0          29629
	#define STR_PAPER_B1          29630
	#define STR_PAPER_B2          29631
	#define STR_PAPER_B3          29632
	#define STR_PAPER_B4          29633
	#define STR_PAPER_B5          29634
	#define STR_PAPER_B6          29635
	#define STR_PAPER_C0          29636
	#define STR_PAPER_C1          29637
	#define STR_PAPER_C2          29638
	#define STR_PAPER_C3          29639
	#define STR_PAPER_C4          29640
	#define STR_PAPER_C5          29641
	#define STR_PAPER_C6          29642
	#define STR_PAPER_ANSI_A      29643
	#define STR_PAPER_ANSI_B      29644
	#define STR_PAPER_ANSI_C      29645
	#define STR_PAPER_ANSI_D      29646
	#define STR_PAPER_ANSI_E      29647
	#define STR_PAPER_LETTER      29648
	#define STR_PAPER_LEGAL       29649
	#define STR_PAPER_EXECUTIVE   29650
	#define STR_PAPER_LEDGER      29651
	#define STR_PAPER_USER        29652

	// errors descriptions
	#define STR_ERROR_INVALID_ID      1001
	#define STR_ERROR_ONE_PAGE        1002
	#define STR_ERROR_PAGE_NOT_EMPTY  1003
	#define STR_ERROR_DEL_LAYER0      1011
	#define STR_ERROR_DEL_CURLAYER    1012
	#define STR_ERROR_LAYER_NOT_EMPTY 1013
	#define STR_ERROR_DEL_LTYPESTD    1014
	#define STR_ERROR_DEL_LTYPEREF    1015
	#define STR_ERROR_DEL_DIMSSTD     1016
	#define STR_ERROR_DEL_DIMSREF     1017
	#define STR_ERROR_DEL_TXTSSTD     1018
	#define STR_ERROR_DEL_TXTSREF     1019
	#define STR_ERROR_DEL_PNTSSTD     1020
	#define STR_ERROR_DEL_PNTSREF     1021
	#define STR_ERROR_DEL_MLSSTD      1022
	#define STR_ERROR_DEL_MLSREF      1023


	//-----------------------------------------------
	// Strings for dialogs controls
	//-----------------------------------------------
	// common controls in dialogs
	#define STR_DG_OK             3001   // "OK"
	#define STR_DG_CANCEL         3002   // "Cancel"
	#define STR_DG_HELP           3003   // "Help"
	#define STR_DG_NEW            3004   // "New"
	#define STR_DG_DELETE         3005   // "Delete"
	#define STR_DG_EXIT           3006   // "Exit"
	#define STR_DG_CLOSE          3007   // "Close"

	// Dialog "Open file"
	#define STR_DG_OPENFILE       3051   // "Select File"
	#define STR_DG_OF_PREVIEW     3052   // "Preview"

	// Dialog "Create block"
	#define STR_DG_CREBLOCK       3101   // "Block definition"
	#define STR_DG_BLK_NAME       3102   // "Name:"
	#define STR_DG_BLK_BASEPNT    3103   // "Base point"
	#define STR_DG_BLK_PICKBASE   3104   // "Pick point"
	#define STR_DG_BLK_OBJECTS    3105   // "Objects"
	#define STR_DG_BLK_SELECT     3106   // "Select objects"
	#define STR_DG_BLK_RETAIN     3107   // "Retain"
	#define STR_DG_BLK_CONVERT    3108   // "Convert to block"
	#define STR_DG_BLK_DELETE     3109   // "Delete"
	#define STR_DG_BLK_DESCR      3110   // "Description:"
	#define STR_DG_BLK_PREVIEW    3111   // "Preview"

	// Dialog "List of Blocks"
	#define STR_DG_BLOCKS         3121   // "Blocks"
	#define STR_DG_BLK_NAME2      3122   // "Name"
	#define STR_DG_BLK_OBJREF     3123   // "Obj     Ref"
	#define STR_DG_BLK_NREFS      3124   // "References:"
	#define STR_DG_BLK_NENTS      3125   // "Objects:"
	#define STR_DG_BLK_VIEW       3126   // "View"
	#define STR_DG_BLK_SHOWBASE   3127   // "Display base point"
	#define STR_DG_BLK_RENAME     3128   // "Rename"
	#define STR_DG_BLK_EDIT       3129   // "Edit"
	#define STR_DG_BLK_ADD        3130   // "Add from file"
	#define STR_DG_BLK_INSERT     3131   // "Insert"
	#define STR_DG_BLK_PATHNAME   3132   // "PathName :"  
	#define STR_DG_BLK_STATUS     3133   // "Status :"
	#define STR_DG_BLK_XREF       3134   // "Add XREF"
	#define STR_DG_BLK_RELOAD     3135   // "Reload"
	#define STR_DG_BLK_LOADED     3136   // "Loaded"
	#define STR_DG_BLK_NOTLOADED  3137   // "Not Loaded"
	#define STR_DG_BLK_NOTFOUND   3138   // "Not Found"
 
	// Dialog "Delete Block"
	#define STR_DG_DELBLOCK       3141   // "Delete Block"
	#define STR_DG_BLK_ASKDELETE  3142   // "Are you sure to delete block with name"
	#define STR_DG_BLK_DELUNUSED  3145   // "Delete all unused blocks"

	// Dialog "Add blocks(s) from other file"
	#define STR_DG_ADDBLOCKF      3151   // "Add blocks from file:"
	#define STR_DG_BLF_NSEL       3152   // "Selected:"
	#define STR_DG_BLF_SELALL     3153   // "Select All"
	#define STR_DG_BLF_UNSELALL   3154   // "Unselect All"
	#define STR_DG_BLF_FILEBLOCK  3155   // "Add the whole drawing as one block"

	// Dialog "Drafting Aids / Grid"
	#define STR_DG_GRID_SIZE      3201   // "Size"
	#define STR_DG_GRID_BOLDSTEP  3202   // "Bold Step"
	#define STR_DG_GRID_SNAP      3203   // "Snap to Grid Nodes (F9)"
	#define STR_DG_GRID_SHOW      3204   // "Show Grid (F7)"
	#define STR_DG_GRID_LEVEL     3210   // "Level"
	#define STR_DG_GRID_ABOVE     3211   // "Above a drawing"
	#define STR_DG_GRID_BELOW     3212   // "Below a drawing"
	#define STR_DG_GRID_COLOR     3213   // "Color :"
	#define STR_DG_GRID_BCOLOR    3214   // "Bold Color :"
	#define STR_DG_GRID_TYPE      3215   // "Type :"
	#define STR_DG_GRID_BTYPE     3216   // "Bold Type :"
	#define STR_DG_GRID_POINT     3221   // "Points"
	#define STR_DG_GRID_LINE      3222   // "Lines"
	#define STR_DG_GRID_DOTLINE   3223   // "Dot-lines"

	// Dialog "Drafting Aids / Object Snap"
	#define STR_DG_SNAP_ON        3231   // "Object Snap On (F3)"
	#define STR_DG_SNAP_MODES     3235   // "Object Snap modes"
	#define STR_DG_SNAP_END       3236   // "Endpoint"
	#define STR_DG_SNAP_MID       3237   // "Midpoint"
	#define STR_DG_SNAP_CENTER    3238   // "Center"
	#define STR_DG_SNAP_POINT     3239   // "Node"
	#define STR_DG_SNAP_INTER     3240   // "Intersection"
	#define STR_DG_SNAP_NEAR      3241   // "Nearest"
	#define STR_DG_SNAP_GRIP      3242   // "Grip"
	#define STR_DG_SNAP_PERP      3243   // "Perpendicular"
	#define STR_DG_SNAP_TANG      3244   // "Tangent"
	#define STR_DG_SNAP_SELALL    3251   // "Select All"
	#define STR_DG_SNAP_CLEAR     3252   // "Clear All"

	// Dialog "Drafting Aids / Polar Tracking"
	#define STR_DG_POLAR_ON       3271   // "Polar Tracking On (F8)"
	#define STR_DG_POLAR_SETTINGS 3272   // "Polar Angle Settings"
	#define STR_DG_POLAR_ANGLE    3273   // "Increment angle :"
	#define STR_DG_POLAR_ADDANG   3274   // "Additional angles"
	#define STR_DG_POLAR_NEW      3275   // "New"
	#define STR_DG_POLAR_DELETE   3276   // "Delete"
	#define STR_DG_POLAR_MEASURE  3277   // "Polar Angle measurement"
	#define STR_DG_POLAR_ABS      3278   // "Absolute"
	#define STR_DG_POLAR_REL      3279   // "Relative to last segment"
	#define STR_DG_POLAR_DIST     3280   // "Polar Distance Step"
	#define STR_DG_POLAR_DISTON   3281   // "Enable Distance Step"

	// Dialog "Options / Display"
	#define STR_DG_DIS_CURSOR        3301   // "Cursor"
	#define STR_DG_DIS_SHOWSYSCUR    3302   // "Show system cursor"
	#define STR_DG_DIS_SHOWCROSS     3303   // "Show crosshair cursor"
	#define STR_DG_DIS_CROSSSIZE     3304   // "Crosshair size :"
	#define STR_DG_DIS_CROSSCOLOR    3305   // "Crosshair color :"
	//#define STR_DG_DIS_MODELSPACE    3306   // "Model space"
	//#define STR_DG_DIS_WINCOLOR      3307   // "Window"
	//#define STR_DG_DIS_WHITECOLOR    3308   // "'White' color"
	//#define STR_DG_DIS_CROSSCOLOR    3309   // "Crosshair"
	#define STR_DG_DIS_PERFORM       3310   // "Performance"
	#define STR_DG_DIS_SEGCURVE      3311   // "Segments per curve :"
	#define STR_DG_DIS_SEGTEXT       3312   // "Text quality :"
	#define STR_DG_DIS_CHARFRAME     3313   // "Char / frame threshold :"
	#define STR_DG_DIS_ENTMINSIZE    3314   // "Entity appearance threshold :"
	#define STR_DG_DIS_REDRAWSTEP    3315   // "Redraw step :"
	#define STR_DG_DIS_MITERLIMIT    3316   // "Miter limit :"
	#define STR_DG_DIS_IMGBORDER     3317   // "Draw images borders"
	#define STR_DG_DIS_MAG           3318   // "Magnifier"
	#define STR_DG_DIS_MAGSIZE       3319   // "Size :"
	#define STR_DG_DIS_MAGSCALE      3320   // "Scale :"
	#define STR_DG_DIS_MAGPOS        3321   // "Position :"
	#define STR_DG_DIS_MAGLEFBOT     3322   // "Left Bottom"
	#define STR_DG_DIS_MAGLEFTOP     3323   // "Left Top"
	#define STR_DG_DIS_MAGRIGBOT     3324   // "Right Bottom"
	#define STR_DG_DIS_MAGRIGTOP     3325   // "Right Top"
	#define STR_DG_DIS_COLORS        3326   // "Color Palette"
	#define STR_DG_DIS_NAVRTIME      3327   // "Realtime view by Navigator"
	#define STR_DG_DIS_FASTCROSS     3328   // "Fast crosshair cursor"
	#define STR_DG_DIS_DELSCROLLBARS 3329   // "Always display window scrollbars"
	#define STR_DG_DIS_EMPTYBLKS     3330   // "Show empty blocks"
	#define STR_DG_DIS_SMOOTHSCROLL  3306   // "Smooth pan by scrollbars"

	// Dialog "Options / Selection"
	#define STR_DG_SEL_MODES         3331   // "Selection Modes"
	#define STR_DG_SEL_POINT         3332   // "AutoSelect by Point"
	#define STR_DG_SEL_RECT          3333   // "AutoSelect by Rectangle"
	#define STR_DG_SEL_SHIFT         3334   // "Use Shift to add to selection"
	#define STR_DG_SEL_CURLAYER      3335   // "Select only on current layer"
	#define STR_DG_SEL_INNER         3336   // "Select polygons by inner area"
	#define STR_DG_SEL_UNSELECT      3337   // "Unselect entities after edit"
	#define STR_DG_SEL_ENTS          3338   // "Selected entities"
	#define STR_DG_SEL_COLOR         3339   // "Color :"
	#define STR_DG_SEL_PENSTYLE      3340   // "Pen style :"
	#define STR_DG_SEL_BOXSIZE       3341   // "Pickbox Size"
	#define STR_DG_SEL_GRIPS         3342   // "Grips"
	#define STR_DG_SEL_SHOWGRIPS     3343   // "Enable grips"
	#define STR_DG_SEL_GRIPSIZE      3345   // "Grip Size"
	#define STR_DG_SEL_INPLINE       3346   // "Closed polylines as polygons"
	#define STR_DG_SEL_HATCHPGON     3347   // "Draw hatch on selected polygons"

	// Dialog "Options / Drafting"
	#define STR_DG_DRAF_SNAPSET      3351   // "AutoSnap Settings"
	#define STR_DG_DRAF_MARKER       3352   // "Marker"
	#define STR_DG_DRAF_MAGNET       3353   // "Magnet"
	#define STR_DG_DRAF_SNAPBOX      3354   // "Display AutoSnap aperture box"
	#define STR_DG_DRAF_MARKCOLOR    3355   // "AutoSnap marker color :"
	#define STR_DG_DRAF_TRACKSET     3356   // "Tracking Settings"
	#define STR_DG_DRAF_TRACKVECTOR  3357   // "Display polar tracking vector"
	#define STR_DG_DRAF_TRACKTTIP    3358   // "Display Tracking tooltip"
	#define STR_DG_DRAF_MARKSIZE     3359   // "AutoSnap marker size"
	#define STR_DG_DRAF_APERSIZE     3360   // "Aperture size"

	// Dialog "Options / Export"
	#define STR_DG_EXP_DWGVER        3371   // "DWG version :"
	#define STR_DG_EXP_DXFVER        3372   // "DXF version :"
	#define STR_DG_EXP_DXFDEC        3373   // "DXF decimal precision :"
	#define STR_DG_EXP_EXPORT        3374   // "Export"
	#define STR_DG_EXP_IMPORT        3375   // "Import"
	#define STR_DG_EXP_DIMASBLOCK    3376   // "Dimensions as blocks"
	#define STR_DG_EXP_HATCHEXPL     3377   // "Explode hatches"

	// Dialog "Options / Profiles"
	#define STR_DG_PRF_CURRENT       3381   // "Current profile :"
	#define STR_DG_PRF_LIST          3382   // "Available profiles :"
	#define STR_DG_PRF_SETCUR        3383   // "Set Current"
	#define STR_DG_PRF_ADD           3384   // "Add..."
	#define STR_DG_PRF_RENAME        3385   // "Rename..."
	#define STR_DG_PRF_DELETE        3386   // "Delete"
	#define STR_DG_PRF_RESET         3387   // "Reset"
	#define STR_DG_PRF_NAME          3391   // "Profile name:"
	#define STR_DG_PRF_DESC          3392   // "Description:"


	// Dialog "Calibrate"
	#define STR_DG_CALIBRATE         3401   // "Calibrate"
	#define STR_DG_CAL_SCALE         3402   // "Scale for meausrements :"
	#define STR_DG_CAL_INTERACT      3403   // "Interactive Calibrate"
	#define STR_DG_CAL_PICK          3404   // "Pick Points"
	#define STR_DG_CAL_MDIST         3405   // "Measured Distance :"
	#define STR_DG_CAL_RDIST         3406   // "Real Distance :"

	// Dialog "Select Color"
	#define STR_DG_COLOR             3501   // "Select Color"
	#define STR_DG_COL_STANDARD      3502   // "Standard Colors"
	#define STR_DG_COL_GRAY          3503   // "Gray Shades"
	#define STR_DG_COL_LOGICAL       3504   // "Logical Colors"
	#define STR_DG_COL_BYLAYER       3505   // "ByLayer"
	#define STR_DG_COL_BYBLOCK       3506   // "ByBlock"
	#define STR_DG_COL_PALETTE       3507   // "Full Color Palette"
	#define STR_DG_COL_COLOR         3508   // "Color :"

	// Dialog "Color Palette"
	#define STR_DG_PALETTE           3521   // "Color Palette"
	#define STR_DG_PAL_FILE          3522   // "Palette File :"
	#define STR_DG_PAL_LIST          3523   // "Colors list"
	#define STR_DG_PAL_COLOR         3524   // "Color"
	#define STR_DG_PAL_INDEX         3525   // "Index :"
	#define STR_DG_PAL_RED           3526   // "Red :"
	#define STR_DG_PAL_GREEN         3527   // "Green :"
	#define STR_DG_PAL_BLUE          3528   // "Blue :"
	#define STR_DG_PAL_NAME          3529   // "Name :"
	#define STR_DG_PAL_SAVE          3530   // "Save"
	#define STR_DG_PAL_SETCOLOR      3531   // "Change Color"
	#define STR_DG_PAL_SAVEQUEST     3532   // "Do you want to save current palette to file\n%s ?"

	// Dialog "Edit vertex"
	#define STR_DG_PLVERTEX          3601   // "Edit polyline vertex %d / %d"
	#define STR_DG_PLV_VERTEX        3602   // "Vertex"
	#define STR_DG_PLV_RAD           3603   // "Radius :"
	#define STR_DG_PLV_ONCURVE       3604   // "Vertex on-curve"
	#define STR_DG_PLV_SEGMENT       3605   // "Segment"
	#define STR_DG_PLV_BULGE         3606   // "Bulge :"
	#define STR_DG_PLV_WIDTH1        3607   // "Start width :"
	#define STR_DG_PLV_WIDTH2        3608   // "End width :"
	#define STR_DT_PLV_BEZIER        3609   // "Bezier control points"
	#define STR_DT_PLV_BEZOFF1       3610   // "Offset 1 :"
	#define STR_DT_PLV_BEZOFF2       3611   // "Offset 2 :"
	#define STR_DT_PLV_BEZANG1       3612   // "Angle 1 :"
	#define STR_DT_PLV_BEZANG2       3613   // "Angle 2 :"
 
	// Dialog "Draw Polygon"
	#define STR_DG_POLYGON           3701   // "Draw Polygon"
	#define STR_DG_PGON_NVERS        3702   // "Number of vertices :"
	#define STR_DG_PGON_IN           3703   // "Inscribed to circle"
	#define STR_DG_PGON_ABOUT        3704   // "Circumscribed about circle"
	#define STR_DG_PGON_CENTER       3705   // "Center point"
	#define STR_DG_PGON_ONSCR        3706   // "Specify on-screen"
	#define STR_DG_PGON_RADIUSGR     3707   // "Radius"
	#define STR_DG_PGON_RADIUS       3709   // "Radius :"
	#define STR_DG_PGON_ROTATION     3710   // "Rotation"
	#define STR_DG_PGON_ANGLE        3712   // "Angle :"

	// Dialog "Export to Raster Image"
	#define STR_DG_BMPEXPORT         3801   // "Export to Raster Image"
	#define STR_DG_BMP_FILE          3802   // "File :"
	#define STR_DG_BMP_AREA          3803   // "Output region:"
	#define STR_DG_BMP_ALL           3804   // "Extents"
	#define STR_DG_BMP_DISP          3805   // "Display"
	#define STR_DG_BMP_WIN           3806   // "Window"
	#define STR_DG_BMP_PICK          3807   // "< Pick"
	#define STR_DG_BMP_RES           3808   // "Resolution (dpi):"
	#define STR_DG_BMP_SIZE          3809   // "Size = %d x %d pixels"

	// Dialog "Installed VeCAD Fonts"
	#define STR_DG_VCFONTS           3901   // "Installed VeCAD Fonts"
	#define STR_DG_VCF_FONT          3902   // "Font :"
	#define STR_DG_VCF_FILENAME      3903   // "Filename :"
	#define STR_DG_VCF_SYMBOLS       3904   // "Symbols :"
	#define STR_DG_VCF_VIEW          3905   // "Symbols  View"
	#define STR_DG_VCF_UNICODE       3906   // "Unicode :"
	#define STR_DG_VCF_SUBSET        3907   // "Subset :"

	// Dialog "Windows TTF to VeCAD Font Convertor"
	#define STR_DG_TTF2VCF           4001   // "Windows TTF to VeCAD Font Convertor"
	#define STR_DG_T2V_FONT          4002   // "Font :"
	#define STR_DG_T2V_SYMBOLS       4003   // "Symbols :"
	#define STR_DG_T2V_LOAD          4004   // "Load Font..."
	#define STR_DG_T2V_VIEW          4005   // "Symbols  View"
	#define STR_DG_T2V_UNICODE       4006   // "Unicode :"
	#define STR_DG_T2V_SUBSET        4007   // "Subset :"
	#define STR_DG_T2V_VCFONT        4008   // "VeCAD Font"
	#define STR_DG_T2V_VCFONTNAME    4009   // "Font Name"
	#define STR_DG_T2V_VCFILENAME    4010   // "Filename :"
	#define STR_DG_T2V_VCFSAVE       4011   // "Save"

	// Dialog "AutoCAD SHX to VeCAD Font Convertor"
	#define STR_DG_SHX2VCF           4101   // "AutoCAD SHX to VeCAD Font Convertor"
	#define STR_DG_S2V_FONT          4102   // "SHX Font"
	#define STR_DG_S2V_FILE          4103   // "File :"
	#define STR_DG_S2V_SHAPES        4104   // "Shapes :"
	#define STR_DG_S2V_VIEW          4105   // "View"
	#define STR_DG_S2V_BIG           4106   // "SHX Big Font"
	#define STR_DG_S2V_USEBIG        4107   // "Use Big Font"
	#define STR_DG_S2V_VCFONT        4110   // "VeCAD Font"
	#define STR_DG_S2V_VCFONTNAME    4111   // "Font Name"
	#define STR_DG_S2V_VCFILENAME    4112   // "Filename :"
	#define STR_DG_S2V_SAVE          4113   // "Save"

	// Dialog "View AutoCAD shapefile"
	#define STR_DG_SHXVIEW           4151   // "View AutoCAD shapefile"
	#define STR_DG_SHX_FILE          4152   // "File :"
	#define STR_DG_SHX_SYMBOLS       4153   // "Symbols :"
	#define STR_DG_SHX_VIEW          4154   // "Symbols  View"
	#define STR_DG_SHX_CODE          4155   // "Code :"

	// Dialog "Font Replacement"
	#define STR_DG_FONTREPLACE       4201   // "Font Replacement"
	#define STR_DG_FREP_NOTFOUND     4202   // "Font is not found, select replacement from the list :"
	#define STR_DG_FREP_LIST         4203   // "Available Fonts"
	#define STR_DG_FREP_FILE         4204   // "File :"

	// Dialog "Hatch"
	#define STR_DG_HATCH             4301   // "Hatch"
	#define STR_DG_HAT_FILE          4302   // "File :"
	#define STR_DG_HAT_PATTERN       4303   // "Pattern :"
	#define STR_DG_HAT_VIEW          4304   // "Preview"
	#define STR_DG_HAT_ANGLE         4305   // "Angle :"
	#define STR_DG_HAT_SCALE         4306   // "Scale :"
	#define STR_DG_HAT_PICK          4307   // "Pick Points"
	#define STR_DG_HAT_PICKENT       4308   // "Pick Entities"

	// Dialog "Insert Image"
	#define STR_DG_IMAGE             4401   // "Insert Image"
	#define STR_DG_IMG_NAME          4402   // "Name:"
	#define STR_DG_IMG_PATH          4403   // "Path:"
	#define STR_DG_IMG_INSPNT        4404   // "Insertion point"
	#define STR_DG_IMG_ONSCR         4405   // "Specify on-screen"
	#define STR_DG_IMG_SCALE         4406   // "Scale (pixel / unit)"
	#define STR_DG_IMG_NEW           4407   // "New..."
	#define STR_DG_IMG_MANAGER       4408   // "Manager..."
	#define STR_DG_IMG_INSERT        4409   // "Insert"
	#define STR_DG_IMG_CB            4420   // "The clipboard contains an image.\nDo you want to insert it instead of loading from a file?"
	#define STR_DG_IMG_CB_FAIL       4421   // "Can not load the image from the clipboard"
 
	// Dialog "Image Manager"
	#define STR_DG_IMAGEMAN          4451   // "Image Manager"
	#define STR_DG_IMM_NAME          4452   // "Name :"
	#define STR_DG_IMM_PATH          4453   // "Path :"
	#define STR_DG_IMM_REFS          4454   // "References :"
	#define STR_DG_IMM_STATUS        4455   // "Status :"
	#define STR_DG_IMM_DATE          4456   // "File date :"
	#define STR_DG_IMM_FILESIZE      4457   // "File size :"
	#define STR_DG_IMM_IMGSIZE       4458   // "Image size :"
	#define STR_DG_IMM_COLORS        4459   // "Color depth :"
	#define STR_DG_IMM_EDIT          4460   // "Edit"
	#define STR_DG_IMM_RELOAD        4461   // "Reload"
	#define STR_DG_IMM_REPLACE       4462   // "Replace..."
	#define STR_DG_IMM_INSERT        4463   // "Insert"

	// Dialog "Create Text object"
	#define STR_DG_TEXT              4501   // "Create Text object"
	#define STR_DG_TXT_ENTER         4502   // "Enter Text:"
	#define STR_DG_TXT_ALIGN         4503   // "Alignment :"
	#define STR_DG_TXT_STYLE         4504   // "Style :"
	#define STR_DG_TXT_HEIGHT        4505   // "Height :"
	#define STR_DG_TXT_ROTANG        4506   // "Rotation :"
	#define STR_DG_TXT_WIDTH         4507   // "Width factor :"
	#define STR_DG_TXT_OBLIQ         4508   // "Obliquing :"
	#define STR_DG_TXT_INSPNT        4509   // "Insertion point"
	#define STR_DG_TXT_UPDOWN        4510   // "Upside down"
	#define STR_DG_TXT_BACKWARD      4511   // "Backward"
	#define STR_DG_TXT_ITALIC        4512   // "Italic"
	#define STR_DG_TXT_UNDER         4513   // "Underline"
	#define STR_DG_TXT_STRIKE        4514   // "Strikeout"

	// Dialog "Insert Block"
	#define STR_DG_INSBLOCK          4601   // "Insert Block"
	#define STR_DG_INS_NAME          4602   // "Name:"
	#define STR_DG_INS_BROWSE        4603   // "Blocks..."
	#define STR_DG_INS_INSPNT        4604   // "Insertion point"
	#define STR_DG_INS_ONSCR         4605   // "Specify on-screen"
	#define STR_DG_INS_SCALE         4606   // "Scale"
	#define STR_DG_INS_UNISCALE      4607   // "Uniform scale"
	#define STR_DG_INS_ROT           4608   // "Rotation"
	#define STR_DG_INS_ANGLE         4609   // "Angle:"
	#define STR_DG_INS_EXPLODE       4610   // "Explode"
	#define STR_DG_INS_MULTI         4611   // "Multiply"
	#define STR_DG_INS_NCOLS         4612   // "Columns:"
	#define STR_DG_INS_NROWS         4613   // "Rows:"

	// Dialog "Layers" 
	#define STR_DG_LAYER             4701   // "Layers"
	#define STR_DG_LAY_NEW           4702   // "New"
	#define STR_DG_LAY_DELETE        4703   // "Delete"
	#define STR_DG_LAY_CURRENT       4704   // "Current"
	#define STR_DG_LAY_DETAILS       4705   // "Details"
	#define STR_DG_LAY_NAME          4706   // "Name :"
	#define STR_DG_LAY_COLOR         4707   // "Color :"
	#define STR_DG_LAY_LWEIGHT       4708   // "Lineweight :"
	#define STR_DG_LAY_LTYPE         4709   // "Linetype"
	#define STR_DG_LAY_OFF           4710   // "Invisible"
	#define STR_DG_LAY_LOCK          4711   // "Lock for editing"
	#define STR_DG_LAY_NOPRINT       4712   // "Do not print"
	#define STR_DG_LAY_NENTS         4713   // "Contains %d entities"

	// Dialog "Linetypes"
	#define STR_DG_LINETYPE          4801   // "Linetypes"
	#define STR_DG_LT_LOAD           4802   // "Add from file..."
	#define STR_DG_LT_DELETE         4803   // "Delete"
	#define STR_DG_LT_CURRENT        4804   // "Current"
	#define STR_DG_LT_DETAILS        4805   // "Details"
	#define STR_DG_LT_NAME           4807   // "Name :"
	#define STR_DG_LT_DESC           4808   // "Description :"
	#define STR_DG_LT_FORMAT         4809   // "Format :"
	#define STR_DG_LT_SCALE          4810   // "Scale factor :"
	#define STR_DG_LT_PREVIEW        4811   // "Preview :"
	#define STR_DG_LT_NEW            4812   // "New"

	// Dialog "Load or Reload Linetypes" 
	#define STR_DG_LTLOAD            4831   // "Load or Reload Linetypes"
	#define STR_DG_LT_FILE           4832   // "File..."
	#define STR_DG_LT_AVAILABLE      4833   // "Available Linetypes"
	#define STR_DG_LT_NSEL           4834   // "Selected Linetypes:   %d"
	#define STR_DG_LT_SELALL         4835   // "Select All"
	#define STR_DG_LT_UNSELALL       4836   // "Unselect All"

	// Dialog "Select Linetype"
	#define STR_DG_LTSELECT          4851   // "Select Linetype"

	// Dialog "Lineweight Settings"
	#define STR_DG_LWEIGHT           4901   // "Lineweight Settings"
	#define STR_DG_LW_LIST           4902   // "Lineweights"
	#define STR_DG_LW_UNITS          4903   // "Units for Listing"
	#define STR_DG_LW_MM             4904   // "Millimeters (mm)"
	#define STR_DG_LW_INCH           4905   // "Inches (in)"
	#define STR_DG_LW_DISPLAY        4906   // "Display Lineweight"
	#define STR_DG_LW_DEFAULT        4907   // "Default :"
	#define STR_DG_LW_SCALE          4908   // "Adjust Display Scale"
	#define STR_DG_LW_MIN            4909   // "Min"
	#define STR_DG_LW_MAX            4910   // "Max"
	#define STR_DG_LW_APPLY          4911   // "Apply"
	#define STR_DG_LW_CURRENT        4912   // "Current Lineweight: %s"

	// Dialog "Select Lineweight"
	#define STR_DG_LWSELECT          4951   // "Select Lineweight"

	// Dialog "Multiline Styles"
	#define STR_DG_MLSTYLE           5001   // "Multiline Styles"
	#define STR_DG_MLS_CURRENT       5002   // "Current Style:  %s"
	#define STR_DG_MLS_CSCALE        5003   // "Current scale :"
	#define STR_DG_MLS_CJUST         5004   // "Current justification :"
	#define STR_DG_MLS_NAME          5005   // "Name :"
	#define STR_DG_MLS_JOINTS        5006   // "Display joints"
	#define STR_DG_MLS_CAPS          5007   // "Caps"
	#define STR_DG_MLS_START         5008   // "Start"
	#define STR_DG_MLS_END           5009   // "End"
	#define STR_DG_MLS_LINE          5010   // "Line"
	#define STR_DG_MLS_OUTARC        5011   // "Outer arc"
	#define STR_DG_MLS_ADD           5012   // "New"
	#define STR_DG_MLS_DELETE        5013   // "Delete"
	#define STR_DG_MLS_BTNCUR        5014   // "Current"
	#define STR_DG_MLS_PREVIEW       5015   // "Preview"
	#define STR_DG_MLS_ELEMENTS      5016   // "Elements"
	#define STR_DG_MLS_OFFSET        5017   // "Offset"
	#define STR_DG_MLS_COLOR         5018   // "Color"
	#define STR_DG_MLS_LINETYPE      5019   // "Linetype"
	#define STR_DG_MLS_ADDLINE       5020   // "Add line"
	#define STR_DG_MLS_DELLINE       5021   // "Delete line"

	// Dialog "Pages"
	#define STR_DG_PAGE              5101   // "Pages"
	#define STR_DG_PG_CURRENT        5102   // "Current Page :"
	#define STR_DG_PG_NEW            5103   // "New"
	#define STR_DG_PG_DELETE         5104   // "Delete"
	#define STR_DG_PG_BTNCUR         5105   // "Current"
	#define STR_DG_PG_NAME           5106   // "Name:"
	#define STR_DG_PG_SIZE           5107   // "Paper Size:"
	#define STR_DG_PG_WIDTH          5108   // "Width, mm :"
	#define STR_DG_PG_HEIGHT         5109   // "Height, mm :"
	#define STR_DG_PG_ORIENT         5110   // "Paper Orientation:"
	#define STR_DG_PG_BOOK           5111   // "Book"
	#define STR_DG_PG_ALBUM          5112   // "Album"

	// Dialog "Select Page"
	#define STR_DG_PAGESELECT        5151   // "Select Page"

	// Dialog "Point Style"
	#define STR_DG_PNTSTYLE          5201   // "Point Style"
	#define STR_DG_PS_NEW            5202   // "New"
	#define STR_DG_PS_DELETE         5203   // "Delete"
	#define STR_DG_PS_CURRENT        5204   // "Current"
	#define STR_DG_PS_DETAILS        5205   // "Details"
	#define STR_DG_PS_NAME           5207   // "Name :"
	#define STR_DG_PS_PDMODE         5208   // "Mode :"
	#define STR_DG_PS_STATE          5209   // "State :"
	#define STR_DG_PS_PDSIZE         5210   // "Size :"
	#define STR_DG_PS_BLOCK          5211   // "Block :"
	#define STR_DG_PS_SCALE          5212   // "Scale :"
	#define STR_DG_PS_FONT           5213   // "Font :"
	#define STR_DG_PS_HEIGHT         5214   // "Height :"
	#define STR_DG_PS_WIDTH          5215   // "Width :"
	#define STR_DG_PS_PREVIEW        5216   // "Preview"
	#define STR_DG_PS_SNAP           5217   // "Enable Snap to Point"
	#define STR_DG_PS_FIXED          5218   // "Non-movable"

	// Dialog "Dimension Styles"
	#define STR_DG_DIMSTYLE          5231   // "Dimension Styles"
	#define STR_DG_DIMSTYLE2         5232   // "Modify Dimension Style:"
	#define STR_DG_DS_CAPLIST        5233   // "List"
	#define STR_DG_DS_CAPGEOM        5234   // "Geometry"
	#define STR_DG_DS_CAPTEXT        5235   // "Text"
	#define STR_DG_DS_CAPUNIT        5236   // "Units"
	#define STR_DG_DS_STYLES         5241   // "Styles:"
	#define STR_DG_DS_NAME           5242   // "Edit Name :"
	#define STR_DG_DS_CURRENT        5243   // "Current Dimstyle:"
	#define STR_DG_DS_PREVIEW        5244   // "Preview"
	#define STR_DG_DS_SETCUR         5245   // "Set Current"
	#define STR_DG_DS_DIMLINE        5251   // "Dimension Lines"
	#define STR_DG_DS_DIMCOLOR       5252   // "Color :"
	#define STR_DG_DS_DIMLW          5253   // "Lineweight :"
	#define STR_DG_DS_EXT            5254   // "Extention Lines"
	#define STR_DG_DS_EXTCOLOR       5255   // "Color :"
	#define STR_DG_DS_EXTLW          5256   // "Lineweight :"
	#define STR_DG_DS_EXTEXT         5257   // "Extend beyond dim lines :"
	#define STR_DG_DS_EXTOFF         5258   // "Offset from origin :"
	#define STR_DG_DS_CMARK          5259   // "Center Marks for Circles"
	#define STR_DG_DS_CMARKTYPE      5261   // "Type :"
	#define STR_DG_DS_CMARKSIZE      5262   // "Size :"
	#define STR_DG_DS_ARROW          5263   // "Arrowheads"
	#define STR_DG_DS_ARR1           5264   // "1st :"
	#define STR_DG_DS_ARR2           5265   // "2nd :"
	#define STR_DG_DS_ARRLEADER      5266   // "Leader :"
	#define STR_DG_DS_ARRSIZE        5267   // "Arrow size :"
	#define STR_DG_DS_TEXT           5271   // "Text Appearance"
	#define STR_DG_DS_TSTYLE         5272   // "Text style :"
	#define STR_DG_DS_TCOLOR         5273   // "Text color :"
	#define STR_DG_DS_TH             5274   // "Text height :"
	#define STR_DG_DS_TRECT          5275   // "Draw frame around text"
	#define STR_DG_DS_TPLACE         5276   // "Text Placement"
	#define STR_DG_DS_TVERT          5277   // "Vertical :"
	#define STR_DG_DS_TALIGN         5278   // "Alignment :"
	#define STR_DG_DS_TOFF           5279   // "Offset from dim line :"
	#define STR_DG_DS_LUNIT          5285   // "Linear Dimensions"
	#define STR_DG_DS_LUFMT          5286   // "Unit format :"
	#define STR_DG_DS_LUPREC         5287   // "Precision :"
	#define STR_DG_DS_LUDEC          5288   // "Decimal separator :"
	#define STR_DG_DS_ROUND          5289   // "Round off :"
	#define STR_DG_DS_PREFIX         5291   // "Prefix :"
	#define STR_DG_DS_SUFFIX         5292   // "Suffix :"
	#define STR_DG_DS_MSCALE         5293   // "Measurement Scale :"
	#define STR_DG_DS_SUPZERO        5294   // "Supress trailing zeros"
	#define STR_DG_DS_AUNITS         5295   // "Angular Dimensions"
	#define STR_DG_DS_AUFMT          5296   // "Unit format :"
	#define STR_DG_DS_AUPREC         5297   // "Precision :"
	#define STR_DG_DS_SCALE          5298   // "Overall scale for dim. features :"


	// Dialog "Print"
	#define STR_DG_PRINT             5301   // "Print"
	#define STR_DG_PRN_DEVICE        5302   // "Printer Device"
	#define STR_DG_PRN_NAME          5303   // "Name :"
	#define STR_DG_PRN_RES           5304   // "Resolution :"
	#define STR_DG_PRN_PAPERSIZE     5305   // "Paper size :"
	#define STR_DG_PRN_PRINTABLE     5306   // "Printable area :"
	#define STR_DG_PRN_INCH          5307   // "inches"
	#define STR_DG_PRN_MM            5308   // "mm"
	#define STR_DG_PRN_CHANGE        5309   // "Change..."
	#define STR_DG_PRN_AREA          5310   // "Print Area"
	#define STR_DG_PRN_EXTENTS       5311   // "Extents"
	#define STR_DG_PRN_DISPLAY       5312   // "Display"
	#define STR_DG_PRN_PAPER         5313   // "Paper"
	#define STR_DG_PRN_WINDOW        5314   // "Window"
	#define STR_DG_PRN_PICK          5315   // "<Pick"
	#define STR_DG_PRN_SCALE         5316   // "Print Scale"
	#define STR_DG_PRN_DRWUNITS      5317   // "drawing units"
	#define STR_DG_PRN_SCALEFIT      5318   // "Scaled to Fit"
	#define STR_DG_PRN_SCALELW       5319   // "Scale lineweights"
	#define STR_DG_PRN_OFFSET        5320   // "Print Offset"
	#define STR_DG_PRN_CENTER        5321   // "Center the print"
	#define STR_DG_PRN_NCOPIES       5322   // "Number of copies :"
	#define STR_DG_PRN_NOCOLOR       5323   // "Force all colors to black"
	#define STR_DG_PRN_PREVIEW       5324   // "Preview..."
	#define STR_DG_PRN_STAMP         5325   // "Stamp..."

	// Dialog "Print Stamp"
	#define STR_DG_PRINTSTAMP        5351   // "Print Stamp"
	#define STR_DG_PST_POSITION      5352   // "Position"
	#define STR_DG_PST_ON            5353   // "On"
	#define STR_DG_PST_FIELDS        5354   // "Stamp fields"
	#define STR_DG_PST_DWGNAME       5355   // "Drawing name"
	#define STR_DG_PST_DATE          5356   // "Date and Time"
	#define STR_DG_PST_DEVNAME       5357   // "Device name"
	#define STR_DG_PST_PAPER         5358   // "Paper size"
	#define STR_DG_PST_SCALE         5359   // "Print Scale"
	#define STR_DG_PST_PREVIEW       5360   // "Preview"
	#define STR_DG_PST_USERTEXT      5361   // "User defined field"
	#define STR_DG_PST_HEIGHT        5362   // "Font Height :"

	// Dialog "Recent Files List"
	#define STR_DG_RECENT            5401   // "Recent Files List"
	#define STR_DG_MRU_FILE          5402   // "File"
	#define STR_DG_MRU_PATH          5403   // "Path"
	#define STR_DG_MRU_SIZE          5404   // "Size :"
	#define STR_DG_MRU_DATE          5405   // "Last Modified :"
	#define STR_DG_MRU_SHOW          5406   // "Show at startup"
	#define STR_DG_MRU_BROWSE        5407   // "Browse..."
	#define STR_DG_MRU_NEW           5408   // "New"
	#define STR_DG_MRU_PREVIEW       5409   // "Preview"

	// Dialog "Select CodePage"
	#define STR_DG_CODEPAGE          5501   // "Select CodePage"
	#define STR_DG_CP_UNDEF          5502   // "Drawing's codepage is undefined"
	#define STR_DG_CP_SELECT         5503   // "Select codepage from the list:"

	// Dialog "Text Style"
	#define STR_DG_TXTSTYLE          5601   // "Text Style"
	#define STR_DG_TS_CURRENT        5602   // "Current Style :"
	#define STR_DG_TS_NEW            5603   // "New..."
	#define STR_DG_TS_RENAME         5604   // "Rename..."
	#define STR_DG_TS_DELETE         5605   // "Delete"
	#define STR_DG_TS_FONT           5606   // "Font"
	#define STR_DG_TS_NAME           5607   // "Name :"
	#define STR_DG_TS_HEIGHT         5608   // "Height :"
	#define STR_DG_TS_FONTS          5609   // "Fonts"
	#define STR_DG_TS_VIEW           5610   // "Preview"
	#define STR_DG_TS_BTNVIEW        5611   // "Preview"
	#define STR_DG_TS_EFFECT         5612   // "Effects"
	#define STR_DG_TS_UPDOWN         5613   // "Upside down"
	#define STR_DG_TS_BACK           5614   // "Backwards"
	#define STR_DG_TS_WIDTH          5615   // "Width Factor :"
	#define STR_DG_TS_ANGLE          5616   // "Oblique Angle :"
	#define STR_DG_TS_TTF            5617   // "TrueType :"

	// Dialog "Tip of the Day"
	#define STR_DG_TIPDAY            5701   // "Tip of the Day"
	#define STR_DG_TIP_SHOW          5702   // "Show tips at startup"
	#define STR_DG_TIP_NEXT          5703   // "Next Tip"

	// Dialog "Viewpoint Presets"
	#define STR_DG_VIEWPOINT         5801   // "Viewpoint Presets"
	#define STR_DG_VP_ANGHOR         5802   // "Horizontal angle :"
	#define STR_DG_VP_ANGVER         5803   // "Vertical angle :"
	#define STR_DG_VP_STDPOS         5804   // "Standard Positions"
	#define STR_DG_VP_PLAN           5805   // "Top"
	#define STR_DG_VP_BOTTOM         5806   // "Bottom"
	#define STR_DG_VP_BACK           5807   // "Back"
	#define STR_DG_VP_LEFT           5808   // "Left"
	#define STR_DG_VP_RIGHT          5809   // "Right"
	#define STR_DG_VP_FRONT          5810   // "Front"
	#define STR_DG_VP_NW             5811   // "North West"
	#define STR_DG_VP_NE             5812   // "North East"
	#define STR_DG_VP_SW             5813   // "South West"
	#define STR_DG_VP_SE             5814   // "South East"
	#define STR_DG_VP_APPLY          5815   // "Apply"

	// Dialog "External Reference"
	#define STR_DG_XREF              5901   // "External Reference"
	#define STR_DG_XREF_NAME         5902   // "Name :"
	#define STR_DG_XREF_PATH         5903   // "Path :"
	#define STR_DG_XREF_INSPNT       5904   // "Insertion point"
	#define STR_DG_XREF_ONSCR        5905   // "Specify on-screen"
	#define STR_DG_XREF_SCALE        5906   // "Scale"
	#define STR_DG_XREF_ROT          5907   // "Rotation"
	#define STR_DG_XREF_ANGLE        5908   // "Angle :"

	// Dialog "Xref Manager"
	#define STR_DG_XREFMAN           5951  // "Xref Manager"
	#define STR_DG_XREF_FOUND        5952  // "Xref found at"
	#define STR_DG_XREF_BROWSE       5953  // "Browse..."
	#define STR_DG_XREF_ATTACH       5954  // "Attach..."
	#define STR_DG_XREF_DETACH       5955  // "Detach"
	#define STR_DG_XREF_RELOAD       5956  // "Reload"
	#define STR_DG_XREF_UNLOAD       5957  // "Unload"

	// Dialog "Drawing's Info"
	#define STR_DG_DWGINFO           6001  // "Drawing's Information"
	#define STR_DG_INF_FILENAME      6002  // "Drawing Name: \t"
	#define STR_DG_INF_FILEDIR       6003  // "Directory:    \t"
	#define STR_DG_INF_ACADVER       6004  // "AutoCAD Version: \t"
	#define STR_DG_INF_VECVER        6005  // "VEC file format: \t"
	#define STR_DG_INF_FILESIZE      6006  // "File Size:      \t"
	#define STR_DG_INF_CODEPAGE      6007  // "Codepage:      \t"
	#define STR_DG_INF_DATECRE       6008  // "Date Created: \t"
	#define STR_DG_INF_DATEMOD       6009  // "Date Last Modified: \t"
	#define STR_DG_INF_EDITTIME      6010  // "Time in Editor: \t"
	#define STR_DG_INF_MAXEXT        6011  // "Upper Extents:  \t"
	#define STR_DG_INF_MINEXT        6012  // "Lower Extents:  \t"
	#define STR_DG_INF_ENTS          6013  // "Entities:      \t"
	#define STR_DG_INF_BLOCKS        6014  // "Blocks:        \t"
	#define STR_DG_INF_LAYERS        6015  // "Layers:        \t"
	#define STR_DG_INF_LTYPES        6016  // "Linetypes:   \t"
	#define STR_DG_INF_TSTYLES       6017  // "Text styles: \t"
	#define STR_DG_INF_PAGES         6018  // "Pages: \t"
	#define STR_DG_INF_PLUGINS       6019  // "Plug-ins for reading raster images"
	#define STR_DG_INF_IMGEDIT       6020  // "Raster images editor:"
	#define STR_DG_INF_RDTIME        6021  // "Redraw time:  "

	// Dialog "Create Attribute Definition"
	#define STR_DG_ATTDEF            6201   // "Attribute Definition"
	// Dialog "Edit Block Attributes"
	#define STR_DG_ATTEDIT           6202   // "Edit Block Attributes"
	// Dialog "Edit Block Attributes"
	#define STR_DG_ATTMAN            6203   // "Block Attribute Manager"
	// Dialog "Synchronize Attributes"
	#define STR_DG_ATTSYNC           6204   // "Synchronize Attributes"
	#define STR_DG_ATT_MODE          6211   // "Mode"
	#define STR_DG_ATT_INVIS         6212   // "Invisible"
	#define STR_DG_ATT_CONST         6213   // "Constant"  
	#define STR_DG_ATT_PRESET        6214   // "Preset"  
	#define STR_DG_ATT_ATTRIB        6215   // "Attribute"   
	#define STR_DG_ATT_ATTRIBS       6216   // "Attributes"   
	#define STR_DG_ATT_DATA          6217   // "Data"   
	#define STR_DG_ATT_TAG           6218   // "Tag :"   
	#define STR_DG_ATT_TAG2          6219   // "Tag"   
	#define STR_DG_ATT_PROMPT        6220   // "Prompt :"   
	#define STR_DG_ATT_VALUE         6221   // "Value :"   
	#define STR_DG_ATT_VALUE2        6222   // "Value"   
	#define STR_DG_ATT_DEFAULT       6223   // "Default :"   
	#define STR_DG_ATT_INSPNT        6231   // "Insertion Point"   
	#define STR_DG_ATT_PICKPNT       6232   // "Pick Point <"   
	#define STR_DG_ATT_TEXTOPTS      6241   // "Text Options"   
	#define STR_DG_ATT_JUST          6242   // "Justification :"   
	#define STR_DG_ATT_TSTYLE        6243   // "Text Style"   
	#define STR_DG_ATT_HEIGHT        6244   // "Height :"  
	#define STR_DG_ATT_ROTANG        6245   // "Rotation :"  
	#define STR_DG_ATT_PICKHEIGHT    6246   // "Height <"  
	#define STR_DG_ATT_PICKROTANG    6247   // "Rotation <"  
	#define STR_DG_ATT_WIDTH         6248   // "Width factor :"
	#define STR_DG_ATT_OBLIQ         6249   // "Oblique Angle :"
	#define STR_DG_ATT_UPSIDEDOWN    6250   // "Upside down"
	#define STR_DG_ATT_BACKWARD      6251   // "Backward"
	#define STR_DG_ATT_PROPS         6261   // "Properties"
	#define STR_DG_ATT_LAYER         6262   // "Layer :"
	#define STR_DG_ATT_LTYPE         6263   // "Linetype :"
	#define STR_DG_ATT_COLOR         6264   // "Color :"
	#define STR_DG_ATT_LW            6265   // "Lineweight :"
	#define STR_DG_ATT_BLOCKNAME     6267   // "Block:"
	#define STR_DG_ATT_SELBLOCK      6268   // "Select Block <"
	#define STR_DG_ATT_DISPOFF       6271   // "OFF: all attributes are invisible"
	#define STR_DG_ATT_DISPNORM      6272   // "Normal: depends of attribute property"
	#define STR_DG_ATT_DISPON        6273   // "ON: all attributes are visible"
	#define STR_DG_ATT_FOUND         6281   // "Found in drawing : %d"
	#define STR_DG_ATT_GLOBVIS       6282   // "Global Visibility :"
	#define STR_DG_ATT_SYNC          6283   // "Sync"
	#define STR_DG_ATT_SYNCTAG       6291   // "Attribute with Tag:  %s"
	#define STR_DG_ATT_APPLY         6292   // "Apply the attribute parameters to existing references"
	#define STR_DG_ATT_PARAMS        6293   // "Parameters"
	#define STR_DG_ATT_SELALL        6294   // "Select All"
	#define STR_DG_ATT_UNSELALL      6295   // "Unselect All"

	// Dialog "Plugins"
	#define STR_DG_PLUGINS           6401   // "Plugins" 
	#define STR_DG_PLG_HFUNC         6402   // "Function"
	#define STR_DG_PLG_HVER          6403   // "Version"
	#define STR_DG_PLG_HFILENAME     6404   // "Filename"
	#define STR_DG_PLG_HFILESIZE     6405   // "Filesize"
	#define STR_DG_PLG_DETAILS       6411   // "Details"
	#define STR_DG_PLG_FILENAME      6412   // "Filename :"
	#define STR_DG_PLG_VER           6413   // "Version :"
	#define STR_DG_PLG_TIME          6414   // "Timestamp :"
	#define STR_DG_PLG_DESC          6415   // "Description :"
	#define STR_DG_PLG_AUTHOR        6416   // "Author :"
	#define STR_DG_PLG_COPYRIGHT     6417   // "Copyright :"
	#define STR_DG_PLG_OPTIONS       6421   // "Options..."
	#define STR_DG_PLG_DISABLE       6422   // "Disable Plugin"
	#define STR_DG_PLG_ENABLE        6423   // "Enable Plugin"
	#define STR_DG_PLG_IMGEDITOR     6430   // "Enter editor's filename:"

	//*** end of strings identifiers ************************************

	#ifdef _DASAN_
	#define RPLAN_TURN_LEFT   0
	#define RPLAN_TURN_RIGHT  1

	#define RPLAN_AREA        1
	#define RPLAN_IZOLINE     2
	#define RPLAN_IZOLINEB    3
	#define RPLAN_ROAD        4
	#define RPLAN_GRPNT       5

	#define RPROF_PLINE       1
	#define RPROF_CURVE       2
	#endif  //_DASAN_



	typedef unsigned long VHANDLE;    // pointer to VeCAD object
	typedef unsigned long VDWG;       // pointer to VeCAD drawing
	typedef unsigned long IDOBJ;      // identifier of VeCAD object
	typedef const BYTE CBYTE;      


	/******************************************************************************
	* Functions to handle VeCAD events
	* 
	* Client application can define special functions that VeCAD will call
	* when the defined event will happen during user's work with drawing.
	* This functions are called "event handlers" and client application
	* must provide it to VeCAD by CadOnEvent... functions
	* You don't need to define all event handlers, just those you want to use
	*
	* Below follows the definitions of syntax of event functions
	* Client application must provide exactly the same syntax 
	*******************************************************************************/


	//-----------------------------------------------
	// Called when user moved mouse over a drawing in a window
	// pDwg - handle of the drawing
	// Flags - some flags
	// Xwin, Ywin - pixel coordinates of cursor on a window
	// Xdwg, Ydwg, Zdwg - drawing coordinates of the cursor
	//-----------------------------------------------
	typedef void (CALLBACK* F_MOUSEMOVE)  (VDWG hDwg, int Button, int Flags, int Xwin, int Ywin, double Xdwg, double Ydwg, double Zdwg);
	typedef void (CALLBACK* F_MOUSEDOWN)  (VDWG hDwg, int Button, int Flags, int Xwin, int Ywin, double Xdwg, double Ydwg, double Zdwg);
	typedef void (CALLBACK* F_MOUSEUP)    (VDWG hDwg, int Button, int Flags, int Xwin, int Ywin, double Xdwg, double Ydwg, double Zdwg);
	typedef void (CALLBACK* F_MOUSEDBLCLK)(VDWG hDwg, int Button, int Flags, int Xwin, int Ywin, double Xdwg, double Ydwg, double Zdwg);
	typedef void (CALLBACK* F_MOUSEWHEEL) (VDWG hDwg, int Flags, int Delta);
	typedef void (CALLBACK* F_MOUSESNAP)  (VDWG hDwg, double Delta, double* pXdwg, double* pYdwg, double* pZdwg);

	//-----------------------------------------------
	// Called when user pressed key and a focus is on VeCAD window
	// VirtKey - virtual key kode (wParam from WM_KEYDOWN)
	// Flags   - lParam from WM_KEYDOWN
	// bCtrl   - TRUE if <Ctrl> key is currently down
	// bShift  - TRUE if <Shift> key is currently down
	//-----------------------------------------------
	typedef void (CALLBACK* F_KEYDOWN) (VDWG hDwg, UINT VirtKey, UINT Flags, BOOL bCtrl, BOOL bShift);


	//-----------------------------------------------
	// Called during a drawing's regeneration to display list
	// the event are produced with 5% step
	// pDwg - handle of the drawing
	// Step - can have the next values 
	//    0 - start of the regeneration
	//    1 - regeneration is going, called each 5%
	//    2 - end of the regeneration
	// Percent - used only for Step=1, means percent of completion
	// iEnt - if Step=0 means number of entities to be redrawn
	//        if Step=1 means counter of already regenerated entities
	//-----------------------------------------------
	typedef void (CALLBACK* F_REGEN) (VDWG hDwg, int Step, int Percent, int iEnt);


	//-----------------------------------------------
	// Called during a drawing's load/save process
	// the event are produced with 5% step
	// pDwg - handle of the drawing
	// Mode - can have the next values 
	//    0 - load
	//    1 - save
	// Step - can have the next values 
	//    0 - start of the load/save
	//    1 - load/save is going, called each 5%
	//    2 - end of the load/save
	// Percent - used only for Step=1, means percent of completion
	// szFileName - name of the file
	//-----------------------------------------------
	typedef void (CALLBACK* F_LOADSAVE) (VDWG hDwg, int Mode, int Step, int Percent);

	//-----------------------------------------------
	// Called during an user measure distance on a drawing
	// by CadExecute( CAD_CMD_DISTANCE ) function that start "Measure 
	// Distance" tool. At this tool user click cursor on multiply points 
	// on a drawing to receive sum distance between that points. The measure
	// process is stopped by pressing right mouse button.
	//  pDwg - handle of the drawing
	//  Step - can have the next values 
	//     0 - user started "Distance" tool
	//     1 - user pressed left mouse button
	//     2 - user is dragging measure line 
	//     3 - user finish "Distance" tool
	//  Perim - distance between start click point and last cursor position
	//          along all clicked points
	//  Dist - distance between last clicked point and last cursor position
	//  X0, Y0, Z0 - start coordinates of last measured line
	//  X1, Y1, Z1 - end coordinates of last measured line
	//-----------------------------------------------
	typedef void (CALLBACK* F_DISTANCE) (VDWG hDwg, int Step, double Perim, double Dist, double X0, double Y0, double Z0, double X1, double Y1, double Z1);

	//-----------------------------------------------
	// Called during an user measure areas on a drawing
	// by CadExecute( CAD_CMD_AREA ) function that start "Measure Area" 
	// tool. At this tool user click cursor on multiply points 
	// on a drawing to receive area of result polygon. To finish measure
	// polygon user must click on start point of the polygon. After this
	// VeCAD automatically goes to measure next polygon. An user has
	// possibility to know area of last polygon and sum of areas of all
	// measured polygons during "Measure Area" tool's session.
	// The measure process is stopped by pressing right mouse button.
	//  pDwg - handle of the drawing
	//  AreaLast - area of last measured polygon 
	//  AreaTotal - sum of areas of all measured polygons
	//-----------------------------------------------
	typedef void (CALLBACK* F_AREA) (VDWG hDwg, int Step, double AreaLast, double AreaTotal);

	//-----------------------------------------------
	// This message suggested for client aplication's status bar.
	// VeCAD post some prompt messages during user works with drawing
	// that intended for user to better understand what to do next.
	//  szText - prompt text
	//-----------------------------------------------
	typedef void (CALLBACK* F_PROMPT) (VDWG hDwg, LPCTSTR szText);

	//-----------------------------------------------
	// This message are sent when active page is changed
	//  szPageName - name of active page
	//-----------------------------------------------
	typedef void (CALLBACK* F_SELPAGE) (VDWG hDwg, LPCTSTR szPageName);


	//-----------------------------------------------
	// This message are sent when VeCAD loads a drawing
	// that have not codepage information.
	// In order to set desired codepage use CadSetReturnInt( CAD_CP_... );
	// If return value is not set or 0 (zero) then VeCAD will call
	// "Select Codepage" dialog
	//-----------------------------------------------
	typedef void (CALLBACK* F_SELCODEPAGE) (VDWG hDwg);

	//-----------------------------------------------
	// This message are sent when VeCAD don't find a font specified
	// in a loaded drawing.
	// In order to set desired font use CadSetReturnStr( font name );
	// If return value is not set or 0 (zero) then VeCAD will call
	// "Font Replacement" dialog
	//-----------------------------------------------
	typedef void (CALLBACK* F_FONTREPLACE) (VDWG hDwg, LPCTSTR szOrigFont, int bBigFont);

	//-----------------------------------------------
	// are sent when VeCAD repaint drawing in a window
	//-----------------------------------------------
	typedef void (CALLBACK* F_PAINT) (VDWG hDwg, HDC hDrawDC, int Mode, int WinW, int WinH, double DwgLeft, double DwgBottom, double DwgRight, double DwgTop, double UnitsPerPixel);

	//-----------------------------------------------
	// are sent when view rectangle is changed
	//-----------------------------------------------
	typedef void (CALLBACK* F_VIEW) (VDWG hDwg, int WinW, int WinH, double DwgLeft, double DwgBottom, double DwgRight, double DwgTop, double UnitsPerPixel);

	//-----------------------------------------------
	// This message are sent when VeCAD draws an image entity that was
	// added by 'CadAddImagePlace' function
	//-----------------------------------------------
	typedef void (CALLBACK* F_DRAWIMAGE) (VDWG hDwg, HDC hDrawDC, int WinLeft, int WinTop, int WinRight, int WinBottom, int ImgID, int ImgLeft, int ImgBottom, int ImgWidth, int ImgHeight);

	//-----------------------------------------------
	// This message is sent before VeCAD save DIB of rasterized drawing
	// see 'CadRasterize' function
	//-----------------------------------------------
	typedef void (CALLBACK* F_SAVEDIB) (VDWG hDwg, LPCTSTR szFileName, BITMAPFILEHEADER* pFileHdr, BITMAPINFO* pInfo, BYTE* pBits);

	//-----------------------------------------------
	// This message is sent after an entity is created by user
	//-----------------------------------------------
	typedef void (CALLBACK* F_ENTCREATE) (VDWG hDwg, VHANDLE hEnt);

	//-----------------------------------------------
	// This message is sent after an entity is loaded from a file
	//-----------------------------------------------
	typedef void (CALLBACK* F_ENTLOAD) (VDWG hDwg, VHANDLE hEnt);

	//-----------------------------------------------
	// This message is sent after an entity is copied
	//-----------------------------------------------
	typedef void (CALLBACK* F_ENTCOPY) (VDWG hDwg, VHANDLE hEntNew, VHANDLE hEntSrc);

	//-----------------------------------------------
	// This message are sent after an entity is modified
	//-----------------------------------------------
	typedef void (CALLBACK* F_ENTCHANGE) (VDWG hDwg, VHANDLE hEnt);

	//-----------------------------------------------
	// This message are sent before entity to be erased
	//-----------------------------------------------
	typedef void (CALLBACK* F_ENTERASE) (VDWG hDwg, VHANDLE hEnt);

	//-----------------------------------------------
	// This message are sent before entity to be moved
	//-----------------------------------------------
	typedef void (CALLBACK* F_ENTMOVE) (VDWG hDwg, VHANDLE hEnt, double* pDX, double* pDY, double* pDZ);
	typedef void (CALLBACK* F_ENTROTATE) (VDWG hDwg, VHANDLE hEnt, double Xcen, double Ycen, double Zcen, double Angle);
	typedef void (CALLBACK* F_ENTSCALE) (VDWG hDwg, VHANDLE hEnt, double Xcen, double Ycen, double Zcen, double ScaleX, double ScaleY, double ScaleZ);

	// after user insert a polyline vertex
	typedef void (CALLBACK* F_PLINEINSVER)(VDWG hDwg, VHANDLE hPline, int iVer);
	// before user delete a polyline vertex
	typedef void (CALLBACK* F_PLINEDELVER)(VDWG hDwg, VHANDLE hPline, int iVer);
	// before user edit a polyline vertex in the dialog
	typedef void (CALLBACK* F_PLINEEDITVER)(VDWG hDwg, VHANDLE hPline, int iVer);

	//-----------------------------------------------
	// This message are sent before an entity to be selected
	//-----------------------------------------------
	typedef void (CALLBACK* F_ENTSELECT) (VDWG hDwg, VHANDLE hEnt, BOOL bSelect, BOOL bFinal);

	//-----------------------------------------------
	// This message are sent from the CadExecute function
	//-----------------------------------------------
	typedef void (CALLBACK* F_EXECUTE) (VDWG hDwg, int Cmd);

	//-----------------------------------------------
	// This message are sent for each generated line when CadEngrave function is working
	//-----------------------------------------------
	typedef void (CALLBACK* F_ENGRAVE) (VDWG hDwg, int Stage, double Percent, double x0, double y0, double x1, double y1);

	//-----------------------------------------------
	// This messages are sent when polygon have to be filled
	//-----------------------------------------------
	//typedef void (CALLBACK* F_POLYGON)     (VDWG hDwg, VHANDLE hEnt, HDC hDrawDC, const POINT* pPoints, int nCount, COLORREF Color);
	typedef void (CALLBACK* F_POLYFILL) (VDWG hDwg, VHANDLE hEnt, HDC hDrawDC, const POINT* pPoints, const int* pPolyCounts, int nCount, COLORREF Color, BOOL bSelect);


	//-----------------------------------------------
	// This message is sent after a blockis created by user
	//-----------------------------------------------
	typedef void (CALLBACK* F_BLOCKCREATE) (VDWG hDwg, VHANDLE hBlock);


	typedef void (CALLBACK* F_GRIPDRAG) (VDWG hDwg, VHANDLE hEnt, int iGrip, double* pDX, double* pDY, double* pDZ);
	typedef void (CALLBACK* F_GRIPMOVE) (VDWG hDwg, VHANDLE hEnt, int iGrip, double* pDX, double* pDY, double* pDZ);
	typedef void (CALLBACK* F_CMDSTART) (VDWG hDwg, int Cmd, int nSteps);
	typedef void (CALLBACK* F_CMDLBDOWN) (VDWG hDwg, int Cmd, int Step, double* pX, double* pY, double* pZ);
	typedef void (CALLBACK* F_CMDFINISH) (VDWG hDwg, int Cmd);

	// custom entity events
	typedef void (CALLBACK* F_CE_GETNAME )(VDWG hDwg, VHANDLE hEnt);
	typedef void (CALLBACK* F_CE_GETPROPS)(VDWG hDwg, VHANDLE hEnt);
	typedef void (CALLBACK* F_CE_PUTPROP )(VDWG hDwg, VHANDLE hEnt, int PropId, LPCTSTR szValue);
	typedef void (CALLBACK* F_CE_GETEXTS )(VDWG hDwg, VHANDLE hEnt, double* pXmin, double* pYmin, double* pZmin, double* pXmax, double* pYmax, double* pZmax);
	typedef void (CALLBACK* F_CE_NGRIPS  )(VDWG hDwg, VHANDLE hEnt, int* pN);
	typedef void (CALLBACK* F_CE_GETGRIP )(VDWG hDwg, VHANDLE hEnt, UINT iGrip, double* pX, double* pY, double* pZ );
	typedef void (CALLBACK* F_CE_MOVEGRIP)(VDWG hDwg, VHANDLE hEnt, UINT iGrip, double dx, double dy, double dz );
	typedef void (CALLBACK* F_CE_MOVE    )(VDWG hDwg, VHANDLE hEnt, double dx, double dy, double dz );
	typedef void (CALLBACK* F_CE_ROTATE  )(VDWG hDwg, VHANDLE hEnt, double x0, double y0, double z0, double Angle, int Plane);
	typedef void (CALLBACK* F_CE_SCALE   )(VDWG hDwg, VHANDLE hEnt, double x0, double y0, double z0, double ScaleX, double ScaleY, double ScaleZ);
	typedef void (CALLBACK* F_CE_MIRROR  )(VDWG hDwg, VHANDLE hEnt, double A1, double B1, int Plane);
	typedef void (CALLBACK* F_CE_DISPLAY )(VDWG hDwg, VHANDLE hEnt);

	// custom commands
	typedef void (CALLBACK* F_CC_START    )(VDWG hDwg, int Id);
	typedef void (CALLBACK* F_CC_FINISH   )(VDWG hDwg, int Id);
	typedef void (CALLBACK* F_CC_LBDOWN   )(VDWG hDwg, int Id, double x, double y, double z, BOOL bShift, BOOL bCtrl);
	typedef void (CALLBACK* F_CC_LBUP     )(VDWG hDwg, int Id, double x, double y, double z, BOOL bShift, BOOL bCtrl);
	typedef void (CALLBACK* F_CC_RBDOWN   )(VDWG hDwg, int Id, double x, double y, double z);
	typedef void (CALLBACK* F_CC_MOUSEMOVE)(VDWG hDwg, int Id, double x, double y, double z);
	typedef void (CALLBACK* F_CC_REDRAW   )(VDWG hDwg, int Id);
	typedef void (CALLBACK* F_CC_PUTVALUE )(VDWG hDwg, int Id, LPCTSTR szValue, BOOL bDefault);

	typedef void (CALLBACK* F_CC_EXECUTE )(VDWG hDwg, int Id);
	typedef void (CALLBACK* F_CC_DRAG    )(VDWG hDwg, int Id, int nPoints, double x, double y, double z);

	typedef void (CALLBACK* F_CCMD )(VDWG hDwg);
	typedef void (CALLBACK* F_CDRAG)(VDWG hDwg, int nPoints, double x, double y, double z);

	typedef void (CALLBACK* F_DISPOWNERDRAW) (const void* pObj, HDC hDC);



	//*****************************************************************************
	//*****************************************************************************

	//                        VECAD FUNCTIONS

	//*****************************************************************************
	//*****************************************************************************
	#define CADAPI _stdcall 

	#ifdef _VECAD_LIB
	  extern "C" {

	BOOL CADAPI VecadInitLib (HINSTANCE hInst);
	void CADAPI VecadFreeLib ();

	#else

	// The next 2 functions are used by those C++ applications 
	// that can't use 'Cad.lib'. At this case the 'CadApi.cpp'
	// file must be included to the project, in order to
	// resolve all VeCAD API functions
	BOOL CadLoadLibrary ();
	void CadFreeLibrary ();

	#endif



	BOOL CADAPI CadRegistration (int RegCode);

	//-----------------------------------------------
	// Returns current version numver of the DLL
	// format: aabbccc
	// aa - major version
	// bb - minor version
	// ccc - build number
	// For example: return value of 102035 mean version 1.02.035
	// szVer - buffer to receive version text, can be NULL
	//-----------------------------------------------
	int CADAPI CadGetVersion (TCHAR* szVer);

	/******************************************************************************
	* Group of functions to set EVENT HANDLERS.
	* Client application must call this functions at the beginning
	* of execution in order to pass for VeCAD addresses of the
	* application-defined functions that will be called on
	* some VeCAD events. There is no need to use all this
	* functions, just set for those events you want to catch. 
	*******************************************************************************/
	void CADAPI CadOnEventMouseMove   (F_MOUSEMOVE   pFunc);
	void CADAPI CadOnEventMouseDown   (F_MOUSEDOWN   pFunc);
	void CADAPI CadOnEventMouseUp     (F_MOUSEUP     pFunc);
	void CADAPI CadOnEventMouseDblClk (F_MOUSEDBLCLK pFunc);
	void CADAPI CadOnEventMouseWheel  (F_MOUSEWHEEL  pFunc);
	void CADAPI CadOnEventMouseSnap   (F_MOUSESNAP   pFunc);
	void CADAPI CadOnEventKeyDown     (F_KEYDOWN     pFunc);
	void CADAPI CadOnEventRegen       (F_REGEN       pFunc);
	void CADAPI CadOnEventLoadSave    (F_LOADSAVE    pFunc);
	void CADAPI CadOnEventDistance    (F_DISTANCE    pFunc);
	void CADAPI CadOnEventArea        (F_AREA        pFunc);
	void CADAPI CadOnEventPrompt      (F_PROMPT      pFunc);
	void CADAPI CadOnEventSelPage     (F_SELPAGE     pFunc);
	void CADAPI CadOnEventSelCodepage (F_SELCODEPAGE pFunc);
	void CADAPI CadOnEventFontReplace (F_FONTREPLACE pFunc);
	void CADAPI CadOnEventPaint       (F_PAINT       pFunc);
	void CADAPI CadOnEventView        (F_VIEW        pFunc);
	void CADAPI CadOnEventDrawImage   (F_DRAWIMAGE   pFunc);
	void CADAPI CadOnEventSaveDib     (F_SAVEDIB     pFunc);
	void CADAPI CadOnEventEntCreate   (F_ENTCREATE   pFunc);
	void CADAPI CadOnEventEntLoad     (F_ENTLOAD     pFunc);
	void CADAPI CadOnEventEntCopy     (F_ENTCOPY     pFunc);
	void CADAPI CadOnEventEntErase    (F_ENTERASE    pFunc);
	void CADAPI CadOnEventEntMove     (F_ENTMOVE     pFunc);
	void CADAPI CadOnEventEntRotate   (F_ENTROTATE   pFunc);
	void CADAPI CadOnEventEntScale    (F_ENTSCALE    pFunc);
	void CADAPI CadOnEventEntChange   (F_ENTCHANGE   pFunc);
	void CADAPI CadOnEventEntSelect   (F_ENTSELECT   pFunc);
	void CADAPI CadOnEventPlineInsVer (F_PLINEINSVER  pFunc);
	void CADAPI CadOnEventPlineDelVer (F_PLINEDELVER  pFunc);
	void CADAPI CadOnEventPlineEditVer(F_PLINEEDITVER pFunc);

	void CADAPI CadOnEventExecute     (F_EXECUTE     pFunc);
	void CADAPI CadOnEventGripDrag    (F_GRIPDRAG    pFunc);
	void CADAPI CadOnEventGripMove    (F_GRIPMOVE    pFunc);
	void CADAPI CadOnEventCmdStart    (F_CMDSTART    pFunc);
	void CADAPI CadOnEventCmdLBDown   (F_CMDLBDOWN   pFunc);
	void CADAPI CadOnEventCmdFinish   (F_CMDFINISH   pFunc);
	void CADAPI CadOnEventEngrave     (F_ENGRAVE     pFunc);
	void CADAPI CadOnEventPolyFill    (F_POLYFILL    pFunc, BOOL bText);

	void CADAPI CadOnEventBlockCreate (F_BLOCKCREATE  pFunc);

	// custom entity events
	void CADAPI CadOnEventCEntGetName  (F_CE_GETNAME  pFunc);
	void CADAPI CadOnEventCEntGetProps (F_CE_GETPROPS pFunc);
	void CADAPI CadOnEventCEntPutProp  (F_CE_PUTPROP  pFunc);
	void CADAPI CadOnEventCEntGetExts  (F_CE_GETEXTS  pFunc);
	void CADAPI CadOnEventCEntNumGrips (F_CE_NGRIPS   pFunc);
	void CADAPI CadOnEventCEntGetGrip  (F_CE_GETGRIP  pFunc);
	void CADAPI CadOnEventCEntMoveGrip (F_CE_MOVEGRIP pFunc);
	void CADAPI CadOnEventCEntMove     (F_CE_MOVE     pFunc);
	void CADAPI CadOnEventCEntRotate   (F_CE_ROTATE   pFunc);
	void CADAPI CadOnEventCEntScale    (F_CE_SCALE    pFunc);
	void CADAPI CadOnEventCEntMirror   (F_CE_MIRROR   pFunc);
	void CADAPI CadOnEventCEntDisplay  (F_CE_DISPLAY  pFunc);

	void CADAPI CadOnEventCCmdExecute   (F_CC_EXECUTE pFunc);
	void CADAPI CadOnEventCCmdDrag      (F_CC_DRAG    pFunc);

	// custom commands
	//void CADAPI CadOnEventCCmdStart     (F_CC_START     pFunc);
	//void CADAPI CadOnEventCCmdFinish    (F_CC_FINISH    pFunc);
	//void CADAPI CadOnEventCCmdLBDown    (F_CC_LBDOWN    pFunc);
	//void CADAPI CadOnEventCCmdLBUp      (F_CC_LBUP      pFunc);
	//void CADAPI CadOnEventCCmdRBDown    (F_CC_RBDOWN    pFunc);
	//void CADAPI CadOnEventCCmdMouseMove (F_CC_MOUSEMOVE pFunc);
	//void CADAPI CadOnEventCCmdRedraw    (F_CC_REDRAW    pFunc);
	//void CADAPI CadOnEventCCmdPutValue  (F_CC_PUTVALUE  pFunc);


	// next 3 functions are used inside of Event handler functions
	// to set return value
	// string 
	void CADAPI CadSetReturnStr (LPCTSTR szText);
	// integer
	void CADAPI CadSetReturnInt (int val);
	// double float
	void CADAPI CadSetReturnDbl (double val);

	// instead of using pointers for retrieving a value
	// for example:
	// CadPointGetCoord( hEnt, 0,0,0 );
	// x = CadGetReturnX();
	// y = CadGetReturnY();
	// z = CadGetReturnZ();
	double CADAPI CadGetReturnX ();
	double CADAPI CadGetReturnY ();
	double CADAPI CadGetReturnZ ();
	double CADAPI CadGetReturnVar ();

	// disable default processing after user process VeCAD event
	//void     CADAPI CadDisableDefProc ();

	// used in OCX after VeCAD control have been created
	void CadOnCreateControl (VDWG hDwg, void* pObject, HWND hWnd );


	/******************************************************************************
	* GLOBAL PROPERTIES parameters for all CAD objects
	*******************************************************************************/

	int      CADAPI CadSetParam (int Param, int Value);  // returns previous value
	int      CADAPI CadGetParam (int Param);

	// default linetypes file
	//void     CADAPI CadSetLinetypesFile (LPCTSTR szFileName);
	//void     CADAPI CadGetLinetypesFile (TCHAR* szFileName);

	// set default directory for file open/save dialogs and filesearch
	void     CADAPI CadSetDefaultDir (LPCTSTR szDir);
	void     CADAPI CadGetDefaultDir (TCHAR* szDir);

	// set default font
	BOOL     CADAPI CadSetDefaultFont (LPCTSTR szFontFile);
	void     CADAPI CadGetDefaultFont (TCHAR* szFontFile);

	// title for messages, "VeCAD" by default
	void     CADAPI CadSetMsgTitle (LPCTSTR szTitle);

	// zoom/pan coefficients
	void     CADAPI CadSetViewCoefs (double ZoomVal, double PanHor, double PanVer);
	void     CADAPI CadGetViewCoefs (double* pZoomVal, double* pPanHor, double* pPanVer);

	// profile
	BOOL     CADAPI CadProfileLoad (LPCTSTR szName);
	BOOL     CADAPI CadProfileSave (LPCTSTR szName);
	void     CADAPI CadProfileGetName (TCHAR* szName);

	// colors (iColor is value in 0..255 range, can be used CAD_COLOR_... constants)
	COLORREF CADAPI CadSetColor    (UINT iColor, COLORREF ColorRGB);
	COLORREF CADAPI CadGetColor    (UINT iColor);
	UINT     CADAPI CadSeekColor   (COLORREF ColorRGB);
	BOOL     CADAPI CadLoadColors  (LPCTSTR szFileName);
	BOOL     CADAPI CadSaveColors  (LPCTSTR szFileName);
	//--- colors obsolete functions
	COLORREF CADAPI CadColorPutRGB (UINT iColor, COLORREF ColorRGB);
	COLORREF CADAPI CadColorGetRGB (UINT iColor);
	UINT     CADAPI CadColorSeek   (COLORREF ColorRGB);
	//---
	HBRUSH   CADAPI CadGetBrush    (UINT iColor);
	HPEN     CADAPI CadGetPen      (UINT iColor, int Width);


	// if the window "Layers order" currently visible
	BOOL     CADAPI CadGetLayerWndVisible ();

	//------- obsolete start -------
	// "Show system cursor" flag
	void     CADAPI CadSetShowSysCursor (BOOL bShow);
	BOOL     CADAPI CadGetShowSysCursor ();
	// haircross size
	void     CADAPI CadSetCrossSize (UINT Size);
	UINT     CADAPI CadGetCrossSize ();
	// "Show haircross" flag
	void     CADAPI CadSetShowCross (BOOL bShow);
	BOOL     CADAPI CadGetShowCross ();
	// curves quality
	void     CADAPI CadSetCurveQuality (UINT Quality);
	UINT     CADAPI CadGetCurveQuality ();
	// text character quality
	void     CADAPI CadSetCharQuality (UINT Quality);
	UINT     CADAPI CadGetCharQuality ();
	// num of GDI command to be done between check for events during redraw
	void     CADAPI CadSetDrawCheckStep (UINT Step);
	UINT     CADAPI CadGetDrawCheckStep ();
	// min size of char to be drawn, pixels
	void     CADAPI CadSetMinCharSize (int Size);
	int      CADAPI CadGetMinCharSize ();
	// min size of char filling to be drawn, pixels
	void     CADAPI CadSetMinCharFSize (int Size);
	int      CADAPI CadGetMinCharFSize ();
	// min size of entity to be drawn, pixels
	void     CADAPI CadSetMinEntSize (int Size);
	int      CADAPI CadGetMinEntSize ();
	// miter limit for multilines and wide polylines
	void     CADAPI CadSetMiterLimit (int MLimit);
	int      CADAPI CadGetMiterLimit ();
	// Auto select by point 
	void     CADAPI CadSetAutoSel (BOOL bAutoSel);
	BOOL     CADAPI CadGetAutoSel ();
	// Auto select by rectangle 
	void     CADAPI CadSetAutoSelRect (BOOL bAutoSelRect);
	int      CADAPI CadGetAutoSelRect ();
	// use Shift to add entities to selection 
	void     CADAPI CadSetSelShiftAdd (BOOL bSelShiftAdd);
	BOOL     CADAPI CadGetSelShiftAdd ();
	// select polygons by pick on inner area
	void     CADAPI CadSetSelInside (BOOL bSelInside);
	BOOL     CADAPI CadGetSelInside ();
	// select entities only on current layer 
	void     CADAPI CadSetSelByLayer (BOOL bSelByLayer);
	BOOL     CADAPI CadGetSelByLayer ();
	// unselect entities after edit operation 
	void     CADAPI CadSetUnselAfterEdit (BOOL bUnselAfterEdit);
	BOOL     CADAPI CadGetUnselAfterEdit ();
	// Color for selected entities 
	COLORREF CADAPI CadSetSelColor (COLORREF SelColor);
	COLORREF CADAPI CadGetSelColor ();
	// Line style for selected entities, 0-solid, 1-dash, 2-dot 
	void     CADAPI CadSetSelLine (int SelLine);
	int      CADAPI CadGetSelLine ();
	// size of selecting square, pixels 
	void     CADAPI CadSetPickboxSize (int PickboxSize);
	int      CADAPI CadGetPickboxSize ();
	// if true - draw grips on selected entities 
	void     CADAPI CadSetUseGrips (BOOL bUseGrips);
	BOOL     CADAPI CadGetUseGrips ();
	// color of grip squares 
	COLORREF CADAPI CadSetGripColor (COLORREF GripColor);
	COLORREF CADAPI CadGetGripColor ();
	// size of grip square, pixels 
	void     CADAPI CadSetGripSize (int GripSize);
	int      CADAPI CadGetGripSize ();
	// if true - draw borders for image entities
	void     CADAPI CadSetImageBorder (BOOL bImgBorder);
	BOOL     CADAPI CadGetImageBorder ();
	// decimal precision of the DXF file (for export)
	void     CADAPI CadSetDxfDecPrec (UINT dec);
	UINT     CADAPI CadGetDxfDecPrec ();
	// version of DXF file (for export)
	void     CADAPI CadSetDxfVersion (UINT ver);
	UINT     CADAPI CadGetDxfVersion ();
	// version of DWG file (for export)
	void     CADAPI CadSetDwgVersion (UINT ver);
	UINT     CADAPI CadGetDwgVersion ();
	// angle units, CAD_ANGLE_...
	void     CADAPI CadSetAngleUnit (int uang);
	int      CADAPI CadGetAngleUnit ();
	// default file extention,  0-vec, 1-dwg/dxf
	void     CADAPI CadSetFileFilter  (int ExtType);
	int      CADAPI CadGetFileFilter  ();
	// show EMPTY rect for empty drawings
	void     CADAPI CadShowEmptyRect (BOOL bShow);
	// blink time
	void     CADAPI CadSetBlinkTime (int nMSec);
	//void     CADAPI CadSetBlinkColors (COLORREF BlinkColor, COLORREF BkColor);
	//------- obsolete end -------




	/******************************************************************************
	* Functions to CREATE/OPEN/SAVE/DELETE DRAWING OBJECT
	* 
	* In order a client application can show load/save progress
	* you need to set load/save event handler by the 
	* CadOnEventLoadSave() function
	*******************************************************************************/

	//-----------------------------------------------
	// Creates empty drawing object
	// Returns: drawing's handle or 0 if fail
	//-----------------------------------------------
	VDWG CADAPI CadCreate ();

	//-----------------------------------------------
	// Deletes drawing object
	//-----------------------------------------------
	void CADAPI CadDelete (VDWG hDwg);

	//-----------------------------------------------
	// Clears drawing object
	//-----------------------------------------------
	void CADAPI CadPurge (VDWG hDwg, int Mode);

	//-----------------------------------------------
	// Clears drawing object
	//-----------------------------------------------
	void CADAPI CadFileNew (VDWG hDwg, HWND hWin);

	//-----------------------------------------------
	// Loads drawing from exist file
	//   szFileName - name of input file, 
	// the filename extention defines format of the drawing
	// Returns: drawing's handle or 0 if fail
	//-----------------------------------------------
	BOOL CADAPI CadFileOpen (VDWG hDwg, HWND hWin, LPCTSTR szFileName);

	//-----------------------------------------------
	// Creates drawing from memory source, 
	//   pMem - pointer to memory
	//   szFileName will used when save drawing to file
	// the filename extention defines format of the drawing
	// If you will not save drawing to file then only extention can be
	// defined. For example:  
	//   hDwg = VDWGOpenMem( pMem, "*.dxf");
	// Returns: drawing's handle or 0 if fail
	//-----------------------------------------------
	BOOL CADAPI CadFileOpenMem (VDWG hDwg, HWND hWin, void* pMem);

	//-----------------------------------------------
	// Saves drawing with the 'hDwg' handle to file with filename
	// that was defined at the creation of drawing
	// Returns: TRUE if succeed, FALSE if fail
	//-----------------------------------------------
	BOOL CADAPI CadFileSave (VDWG hDwg, HWND hWin);

	//-----------------------------------------------
	// Saves drawing with the 'hDwg' handle to file with filename 'szFileName'
	// the filename extention defines format of the drawing to be save
	// Returns: TRUE if succeed, FALSE if fail
	//-----------------------------------------------
	BOOL CADAPI CadFileSaveAs (VDWG hDwg, HWND hWin, LPCTSTR szFileName);

	//-----------------------------------------------
	// Saves drawing with the 'hDwg' handle to memory.
	//   pMem - pointer memory block, if NULL then function don't write
	// to memory but return number of bytes  needed to store drawing.
	//   MaxSize - number of bytes allocated in pMem. If not enough
	// to store drawing then the function will return 0.
	// the filename extention defines format of the drawing to be save
	// Returns: number of bytes written to memory or 0 if fail
	// Example:
	//   UINT nb = CadFileSaveMem( hDwg, 0, 0 );
	//   BYTE* mem = new BYTE[nb];
	//   if (CadFileSaveMem( hDwg, mem, nb ) > 0) {
	//     // OK
	//-----------------------------------------------
	UINT CADAPI CadFileSaveMem (VDWG hDwg, HWND hWin, void* pMem, UINT MaxSize);


	//-----------------------------------------------
	BOOL CADAPI CadRasterize (VDWG hDwg, LPCTSTR szFileName, double Left, double Bottom, double Right, double Top, double Res);

	//-----------------------------------------------
	void CADAPI CadFireLoadSaveEvent (VDWG hDwg, int Mode, int Step, int Percent);


	/******************************************************************************
	* DRAWING PROPERTIES
	* Next group of functions are used to access properties of drawing 'hDwg'
	*******************************************************************************/
	// object that own drawing (hDwg)
	void   CADAPI CadPutOwner (VDWG hDwg, void* pObject); //, HWND hWnd);
	DWORD  CADAPI CadGetOwner (VDWG hDwg);
	// return a handle to window linked with VeCAD object
	HWND   CADAPI CadGetWindow (VDWG hDwg);
	// set a handle to window linked with VeCAD object
	void   CADAPI CadPutWindow (VDWG hDwg, HWND hWnd);
	// filename (current path is added if not specified)
	void   CADAPI CadPutFileName (VDWG hDwg, LPCTSTR szFileName);
	void   CADAPI CadGetFileName (VDWG hDwg, TCHAR* szFileName);
	// filename without path
	void   CADAPI CadGetShortFileName (VDWG hDwg, TCHAR* szFileName);

	// drawing's extents
	double CADAPI CadGetExtentXmin (VDWG hDwg);
	double CADAPI CadGetExtentYmin (VDWG hDwg);
	double CADAPI CadGetExtentZmin (VDWG hDwg);
	double CADAPI CadGetExtentXmax (VDWG hDwg);
	double CADAPI CadGetExtentYmax (VDWG hDwg);
	double CADAPI CadGetExtentZmax (VDWG hDwg);
	// drawing's extents at current 2D projection
	double CADAPI CadGetExtentLeft  (VDWG hDwg);
	double CADAPI CadGetExtentRight (VDWG hDwg);
	double CADAPI CadGetExtentTop   (VDWG hDwg);
	double CADAPI CadGetExtentBottom(VDWG hDwg);
	void   CADAPI CadGetExtentRect  (VDWG hDwg, double* pLeft, double* pBottom, double* pRight, double* pTop);
	// drawing's rectangle that fit to Vecad window
	double CADAPI CadGetWinLeft    (VDWG hDwg);
	double CADAPI CadGetWinRight   (VDWG hDwg);
	double CADAPI CadGetWinTop     (VDWG hDwg);
	double CADAPI CadGetWinBottom  (VDWG hDwg);
	void   CADAPI CadGetWinRect    (VDWG hDwg, double* pLeft, double* pBottom, double* pRight, double* pTop);
	// flag "Draw only current layer"
	void   CADAPI CadPutDrawOnlyCurLayer (VDWG hDwg, BOOL b);
	BOOL   CADAPI CadGetDrawOnlyCurLayer (VDWG hDwg);
	// flag "Drawing is readonly"
	void   CADAPI CadPutReadOnly (VDWG hDwg, BOOL b);
	BOOL   CADAPI CadGetReadOnly (VDWG hDwg);
	// flag "Drawing is changed"
	void   CADAPI CadPutDirty (VDWG hDwg, BOOL b);
	BOOL   CADAPI CadGetDirty (VDWG hDwg);
	// drawing's extended data
	void    CADAPI CadPutExData     (VDWG hDwg, void* pData, int nBytes);
	int     CADAPI CadGetExDataSize (VDWG hDwg);
	void    CADAPI CadGetExData     (VDWG hDwg, void* pData);
	VHANDLE CADAPI CadGetExDataPtr  (VDWG hDwg);
	// drawing's text info
	void   CADAPI CadPutDescr     (VDWG hDwg, LPCTSTR Str, int nChars);
	int    CADAPI CadGetDescrLen  (VDWG hDwg);
	void   CADAPI CadGetDescr     (VDWG hDwg, TCHAR* pStr);
	// flag "Show painting marker on a left top corner of a window"
	void   CADAPI CadPutPaintMark (VDWG hDwg, BOOL b);
	// point mode (for "simple" style)
	void   CADAPI CadPutPointMode (VDWG hDwg, int mode);
	int    CADAPI CadGetPointMode (VDWG hDwg);
	// point size (for "simple" style)
	void   CADAPI CadPutPointSize (VDWG hDwg, double size);
	double CADAPI CadGetPointSize (VDWG hDwg);
	// measure scale
	void   CADAPI CadPutDistScale (VDWG hDwg, double Scal);
	double CADAPI CadGetDistScale (VDWG hDwg);

	// number of entities
	int CADAPI CadGetNumEntities (VDWG hDwg);

	// grid
	void     CADAPI CadGridPutShow      (VDWG hDwg, BOOL bShow);
	BOOL     CADAPI CadGridGetShow      (VDWG hDwg);
	void     CADAPI CadGridPutSnap      (VDWG hDwg, BOOL bSnap);
	BOOL     CADAPI CadGridGetSnap      (VDWG hDwg);
	void     CADAPI CadGridPutSize      (VDWG hDwg, double dx, double dy, double dz);
	void     CADAPI CadGridGetSize      (VDWG hDwg, double* pdx, double* pdy, double* pdz);
	void     CADAPI CadGridPutBoldStep  (VDWG hDwg, int cx, int cy, int cz);
	void     CADAPI CadGridGetBoldStep  (VDWG hDwg, int* pcx, int* pcy, int* pcz);
	void     CADAPI CadGridPutColor     (VDWG hDwg, BOOL bBold, COLORREF Color);
	COLORREF CADAPI CadGridGetColor     (VDWG hDwg, BOOL bBold);
	void     CADAPI CadGridPutType      (VDWG hDwg, BOOL bBold, int Typ);
	int      CADAPI CadGridGetType      (VDWG hDwg, BOOL bBold);
	void     CADAPI CadGridPutLevel     (VDWG hDwg, int Level);
	int      CADAPI CadGridGetLevel     (VDWG hDwg);


	// Default Lineweight  
	void  CADAPI CadPutLwDefault (VDWG hDwg, int Lweight);
	int   CADAPI CadGetLwDefault (VDWG hDwg);
	// Appropriate Scale of Lineweights display 
	void  CADAPI CadPutLwScale   (VDWG hDwg, int Scal);
	int   CADAPI CadGetLwScale   (VDWG hDwg);
	// "Display Lineweights" mode
	void  CADAPI CadPutLwDisplay (VDWG hDwg, BOOL bDisplay);
	BOOL  CADAPI CadGetLwDisplay (VDWG hDwg);

	// current Lineweight used to create entities
	void  CADAPI CadSetCurLweight (VDWG hDwg, int Lweight);
	int   CADAPI CadGetCurLweight (VDWG hDwg);

	// current Color used to create entities
	void  CADAPI CadSetCurColor   (VDWG hDwg, int Color);
	int   CADAPI CadGetCurColor   (VDWG hDwg);

	// set system cursor instead of default one (arrow)
	void  CADAPI CadSetSystemCursor (VDWG hDwg, HCURSOR hCurs);

	// Polar Tracking
	// Turns on/off a polar tracking
	void     CADAPI CadPolarPutOn     (VDWG hDwg, BOOL bOn);
	BOOL     CADAPI CadPolarGetOn     (VDWG hDwg);
	// Increment angle
	void     CADAPI CadPolarPutInc    (VDWG hDwg, int Angle);
	int      CADAPI CadPolarGetInc    (VDWG hDwg);
	// Add additional angle
	BOOL     CADAPI CadPolarAddAngle  (VDWG hDwg, double Angle);
	// Delete additional angle
	BOOL     CADAPI CadPolarDelAngle  (VDWG hDwg, int iAngle);
	// Value of additional angle
	double   CADAPI CadPolarGetAngle  (VDWG hDwg, int iAngle);
	// Number of additional angles
	int      CADAPI CadPolarGetNumAng (VDWG hDwg);
	// Absolute or Relative measurement
	void     CADAPI CadPolarPutAbs    (VDWG hDwg, BOOL bAbs);
	BOOL     CADAPI CadPolarGetAbs    (VDWG hDwg);
	// Snap distance along polar vector
	void     CADAPI CadPolarPutDist   (VDWG hDwg, double Dist);
	double   CADAPI CadPolarGetDist   (VDWG hDwg);
	// Turns on/off a snap distance
	void     CADAPI CadPolarPutDistOn (VDWG hDwg, BOOL bDist);
	BOOL     CADAPI CadPolarGetDistOn (VDWG hDwg);

	// Object Snap
	// Turns on/off an object snap
	void     CADAPI CadSnapPutOn      (VDWG hDwg, BOOL bOn);
	BOOL     CADAPI CadSnapGetOn      (VDWG hDwg);
	// Object snap settings
	void     CADAPI CadSnapPutMode    (VDWG hDwg, int Mode);
	int      CADAPI CadSnapGetMode    (VDWG hDwg);
	int      CADAPI CadSnapGetIndMode (VDWG hDwg);

	// Polyline mark
	BOOL     CADAPI CadSetPlineMark   (VDWG hDwg, int Id, VHANDLE hEnt, double Start, double Length, COLORREF Color, int Width, BOOL bBlink);
	VHANDLE  CADAPI CadAddPlineMark   (VDWG hDwg, VHANDLE hEnt, double Start, double Length);


	/******************************************************************************
	* WINDOW EVENTS
	* This functions are used to notify CAD object about window events
	* hWin - handle to window used to display drawing 'hDwg' (CAD object)
	*******************************************************************************/
	// on WM_CREATE
	void CADAPI CadWinCreate        (VDWG hDwg, HWND hWin);
	// on WM_PAINT
	void CADAPI CadWinPaint         (VDWG hDwg, HWND hWin);
	// Used in VECAD_OCX, CVecadCtrl::OnDraw()
	void CADAPI CadWinDraw          (VDWG hDwg, HWND hWin, HDC dc, int Left, int Top, int Right, int Bottom);
	// on WM_KEYDOWN
	void CADAPI CadWinKeyDown       (VDWG hDwg, HWND hWin, UINT Char, UINT Flags);
	// on WM_KEYUP
	void CADAPI CadWinKeyUp         (VDWG hDwg, HWND hWin, UINT Char, UINT Flags);
	// on WM_MOUSEMOVE
	void CADAPI CadWinMouseMove     (VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	// on WM_MOUSELEAVE
	void CADAPI CadWinMouseLeave    (VDWG hDwg, HWND hWnd);
	// on WM_MOUSEWHEEL
	void CADAPI CadWinMouseWheel    (VDWG hDwg, HWND hWin, UINT Flags, int zDelta, int x, int y);
	// on WM_LBUTTONDOWN
	void CADAPI CadWinLButtonDown   (VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	// on WM_LBUTTONUP
	void CADAPI CadWinLButtonUp     (VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	// on WM_LBUTTONDBLCLK
	void CADAPI CadWinLButtonDblClk (VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	// on WM_RBUTTONDOWN
	void CADAPI CadWinRButtonDown   (VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	// on WM_RBUTTONUP
	void CADAPI CadWinRButtonUp     (VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	// on WM_MBUTTONDOWN
	void CADAPI CadWinMButtonDown   (VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	// on WM_MBUTTONUP
	void CADAPI CadWinMButtonUp     (VDWG hDwg, HWND hWin, UINT Flags, int x, int y);
	// on WM_HSCROLL
	void CADAPI CadWinHScroll       (VDWG hDwg, HWND hWin, UINT SBCode, UINT Pos);
	// on WM_VSCROLL
	void CADAPI CadWinVScroll       (VDWG hDwg, HWND hWin, UINT SBCode, UINT Pos);
	// on WM_SIZE
	void CADAPI CadWinSize          (VDWG hDwg, HWND hWin, UINT SizeType, int cx, int cy);
	// on WM_SETFOCUS
	void CADAPI CadWinSetFocus      (VDWG hDwg, HWND hWin);
	// on WM_KILLFOCUS
	void CADAPI CadWinKillFocus     (VDWG hDwg, HWND hWin);
	// on WM_DESTROY
	void CADAPI CadWinDestroy       (VDWG hDwg, HWND hWin);
	// on WM_CLOSE
	BOOL CADAPI CadWinClose         (VDWG hDwg, HWND hWin);
	// on WM_TIMER
	BOOL CADAPI CadWinTimer         (VDWG hDwg, HWND hWin, int Id);



	/******************************************************************************
	* EXECUTE COMMAND
	* Implements many CAD commands. These function is specially
	* designed to use with an application's menus, buttons and accelerator keys.
	* Command - identifier of a command, one of the CAD_CMD_... constants
	*******************************************************************************/
	void CADAPI CadExecute (VDWG hDwg, HWND hWin, int Command);
	void CADAPI CadSetCmdParam (VDWG hDwg, int Command, void* pData);
	void CADAPI CadGetCmdParam (VDWG hDwg, int Command, void* pData);
	void CADAPI CadSetCmdPoint (VDWG hDwg, double X, double Y, double Z);


	/******************************************************************************
	* LAYER FUNCTIONS
	*
	* VeCAD drawing can contain many layers. Layer is a logical grouping of data,
	* similar to transparent acetate overlays on a paper drawing.
	* After using the CadFileNew() function a drawing already have one layer "0"
	*******************************************************************************/
	VHANDLE CADAPI CadAddLayer           (VDWG hDwg, LPCTSTR szName, int Color, IDOBJ IdLtype, int Lweight);
	BOOL    CADAPI CadDeleteLayer        (VDWG hDwg, VHANDLE hLayer);
	UINT    CADAPI CadCountLayers        (VDWG hDwg);
	VHANDLE CADAPI CadGetCurLayer        (VDWG hDwg);
	VHANDLE CADAPI CadSetCurLayer        (VDWG hDwg, VHANDLE hLayer);
	VHANDLE CADAPI CadSetCurLayerByID    (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadSetCurLayerByName  (VDWG hDwg, LPCTSTR szLayerName);
	VHANDLE CADAPI CadGetFirstLayer      (VDWG hDwg);
	VHANDLE CADAPI CadGetNextLayer       (VDWG hDwg, VHANDLE hLayer);
	VHANDLE CADAPI CadGetLayerByID       (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadGetLayerByName     (VDWG hDwg, LPCTSTR szName);
	void    CADAPI CadSortLayers         (VDWG hDwg);
	/********************************************************************
	*  LAYER PROPERTIES
	*********************************************************************/
	IDOBJ   CADAPI CadLayerGetID         (VHANDLE hLayer);
	void    CADAPI CadLayerGetName       (VHANDLE hLayer, TCHAR* szName);
	void    CADAPI CadLayerPutName       (VHANDLE hLayer, LPCTSTR szName);
	int     CADAPI CadLayerGetColor      (VHANDLE hLayer);
	void    CADAPI CadLayerPutColor      (VHANDLE hLayer, int Color);
	int     CADAPI CadLayerGetLineweight (VHANDLE hLayer);
	void    CADAPI CadLayerPutLineweight (VHANDLE hLayer, int lw);
	IDOBJ   CADAPI CadLayerGetLinetypeID (VHANDLE hLayer);
	void    CADAPI CadLayerPutLinetypeID (VHANDLE hLayer, IDOBJ Id);
	int     CADAPI CadLayerGetLevel      (VHANDLE hLayer);
	void    CADAPI CadLayerPutLevel      (VHANDLE hLayer, int Level);
	DWORD   CADAPI CadLayerGetUserData   (VHANDLE hLayer);
	void    CADAPI CadLayerPutUserData   (VHANDLE hLayer, DWORD Val);
	BOOL    CADAPI CadLayerGetLock       (VHANDLE hLayer);
	void    CADAPI CadLayerPutLock       (VHANDLE hLayer, BOOL bLock);
	BOOL    CADAPI CadLayerGetVisible    (VHANDLE hLayer);
	void    CADAPI CadLayerPutVisible    (VHANDLE hLayer, BOOL bVisible);
	BOOL    CADAPI CadLayerGetPrintable  (VHANDLE hLayer);
	void    CADAPI CadLayerPutPrintable  (VHANDLE hLayer, BOOL bPrintable);
	UINT    CADAPI CadLayerCountEntities (VHANDLE hLayer);
	VHANDLE CADAPI CadLayerGetFirstEntity(VHANDLE hLayer);
	VHANDLE CADAPI CadLayerGetNextEntity (VHANDLE hLayer, VHANDLE hEnt);
	void    CADAPI CadLayerPutDescr      (VHANDLE hLayer, LPCTSTR Str, int nChars);
	int     CADAPI CadLayerGetDescrLen   (VHANDLE hLayer);
	void    CADAPI CadLayerGetDescr      (VHANDLE hLayer, TCHAR* pStr);
	BOOL    CADAPI CadLayerGetDeleted    (VHANDLE hLayer);
	void    CADAPI CadLayerPurge         (VHANDLE hLayer);


	/********************************************************************
	* LINETYPE FUNCTIONS
	*
	* VeCAD drawing can contain many linetypes
	* A linetype is a repeating pattern of dashes, dots, and blank spaces. 
	* The pattern is described by text string, for example "3,-1,0,-1" for dash-dot line
	* After using the CadFileNew() function a drawing already have 3 linetypes
	* "ByLayer", "ByBlock", "Continuous"
	*********************************************************************/
	VHANDLE CADAPI CadAddLinetype          (VDWG hDwg, LPCTSTR szName, LPCTSTR szFormat, LPCTSTR szPict);
	VHANDLE CADAPI CadAddLinetypeF         (VDWG hDwg, LPCTSTR szName, LPCTSTR szFileName);
	BOOL    CADAPI CadDeleteLinetype       (VDWG hDwg, VHANDLE hLtype);
	UINT    CADAPI CadCountLinetypes       (VDWG hDwg);
	VHANDLE CADAPI CadGetCurLinetype       (VDWG hDwg);
	VHANDLE CADAPI CadSetCurLinetype       (VDWG hDwg, VHANDLE hLtype);
	VHANDLE CADAPI CadSetCurLinetypeByID   (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadSetCurLinetypeByName (VDWG hDwg, LPCTSTR szLtypeName);
	VHANDLE CADAPI CadGetFirstLinetype     (VDWG hDwg);
	VHANDLE CADAPI CadGetNextLinetype      (VDWG hDwg, VHANDLE hLtype);
	VHANDLE CADAPI CadGetLinetypeByID      (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadGetLinetypeByName    (VDWG hDwg, LPCTSTR szName);
	VHANDLE CADAPI CadGetLinetypeByLayer   (VDWG hDwg);
	VHANDLE CADAPI CadGetLinetypeByBlock   (VDWG hDwg);
	VHANDLE CADAPI CadGetLinetypeContinuous(VDWG hDwg);
	/********************************************************************
	*  LINETYPE PROPERTIES
	*********************************************************************/
	IDOBJ   CADAPI CadLinetypeGetID        (VHANDLE hLtype);
	void    CADAPI CadLinetypeGetName      (VHANDLE hLtype, TCHAR* szName);
	void    CADAPI CadLinetypePutName      (VHANDLE hLtype, LPCTSTR szName);
	void    CADAPI CadLinetypeGetData      (VHANDLE hLtype, TCHAR* szData);
	void    CADAPI CadLinetypePutData      (VHANDLE hLtype, LPCTSTR szData);
	BOOL    CADAPI CadLinetypePutDataF     (VHANDLE hLtype, LPCTSTR szFileName);
	void    CADAPI CadLinetypeGetDescr     (VHANDLE hLtype, TCHAR* szDescr);
	void    CADAPI CadLinetypePutDescr     (VHANDLE hLtype, LPCTSTR szDescr);
	double  CADAPI CadLinetypeGetScale     (VHANDLE hLtype);
	void    CADAPI CadLinetypePutScale     (VHANDLE hLtype, double Scal);
	BOOL    CADAPI CadLinetypeIsByLayer    (VHANDLE hLtype);
	BOOL    CADAPI CadLinetypeIsByBlock    (VHANDLE hLtype);
	BOOL    CADAPI CadLinetypeIsContinuous (VHANDLE hLtype);

	/******************************************************************************
	* PAGE FUNCTIONS
	*
	* VeCAD drawing can contain many pages
	* The first page is represent "Model Space" and always has unlimites size
	* After using the CadFileNew() function a drawing already have the first page.
	*******************************************************************************/
	VHANDLE CADAPI CadAddPage         (VDWG hDwg, LPCTSTR szName, int Size, int Orient, UINT Width, UINT Height);
	BOOL    CADAPI CadDeletePage      (VDWG hDwg, VHANDLE hPage);
	UINT    CADAPI CadCountPages      (VDWG hDwg);
	VHANDLE CADAPI CadGetCurPage      (VDWG hDwg);
	VHANDLE CADAPI CadSetCurPage      (VDWG hDwg, VHANDLE hPage);
	VHANDLE CADAPI CadSetCurPageByID  (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadSetCurPageByName(VDWG hDwg, LPCTSTR szName);
	VHANDLE CADAPI CadGetFirstPage    (VDWG hDwg);
	VHANDLE CADAPI CadGetNextPage     (VDWG hDwg, VHANDLE hPage);
	VHANDLE CADAPI CadGetPageByID     (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadGetPageByName   (VDWG hDwg, LPCTSTR szName);
	/********************************************************************
	*  PAGE PROPERTIES
	*********************************************************************/
	IDOBJ   CADAPI CadPageGetID       (VHANDLE hPage);
	void    CADAPI CadPageGetName     (VHANDLE hPage, TCHAR* szName);
	void    CADAPI CadPagePutName     (VHANDLE hPage, LPCTSTR szName);
	UINT    CADAPI CadPageGetSize     (VHANDLE hPage);
	void    CADAPI CadPagePutSize     (VHANDLE hPage, UINT Size);
	UINT    CADAPI CadPageGetOrient   (VHANDLE hPage);
	void    CADAPI CadPagePutOrient   (VHANDLE hPage, UINT Orient);
	UINT    CADAPI CadPageGetWidth    (VHANDLE hPage);
	void    CADAPI CadPagePutWidth    (VHANDLE hPage, UINT Width);
	UINT    CADAPI CadPageGetHeight   (VHANDLE hPage);
	void    CADAPI CadPagePutHeight   (VHANDLE hPage, UINT Height);
	BOOL    CADAPI CadPageSave        (VDWG hDwg, VHANDLE hPage, LPCTSTR szFileName);
	BOOL    CADAPI CadPageCopy        (VDWG hSrcDwg, VHANDLE hSrcPage, VDWG hDestDwg, VHANDLE hDestPage);


	/********************************************************************
	*
	*  TEXT STYLES FUNCTIONS
	*
	*********************************************************************/
	VHANDLE CADAPI CadAddTStyle           (VDWG hDwg, LPCTSTR szName, LPCTSTR szFontName);
	BOOL    CADAPI CadDeleteTStyle        (VDWG hDwg, VHANDLE hTStyle);
	UINT    CADAPI CadCountTStyles        (VDWG hDwg);
	VHANDLE CADAPI CadGetCurTStyle        (VDWG hDwg);
	VHANDLE CADAPI CadSetCurTStyle        (VDWG hDwg, VHANDLE hTStyle);
	VHANDLE CADAPI CadSetCurTStyleByID    (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadSetCurTStyleByName  (VDWG hDwg, LPCTSTR szName);
	VHANDLE CADAPI CadGetFirstTStyle      (VDWG hDwg);
	VHANDLE CADAPI CadGetNextTStyle       (VDWG hDwg, VHANDLE hTStyle);
	VHANDLE CADAPI CadGetTStyleByID       (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadGetTStyleByName     (VDWG hDwg, LPCTSTR szName);
	/********************************************************************
	*  TEXT STYLE PROPERTIES 
	*********************************************************************/
	IDOBJ   CADAPI CadTStyleGetID         (VHANDLE hTStyle);
	void    CADAPI CadTStyleGetName       (VHANDLE hTStyle, TCHAR* szName);
	void    CADAPI CadTStylePutName       (VHANDLE hTStyle, LPCTSTR szName);
	double  CADAPI CadTStyleGetOblique    (VHANDLE hTStyle);
	void    CADAPI CadTStylePutOblique    (VHANDLE hTStyle, double Angle);
	double  CADAPI CadTStyleGetWidth      (VHANDLE hTStyle);
	void    CADAPI CadTStylePutWidth      (VHANDLE hTStyle, double Width);
	double  CADAPI CadTStyleGetHeight     (VHANDLE hTStyle);
	void    CADAPI CadTStylePutHeight     (VHANDLE hTStyle, double Height);
	BOOL    CADAPI CadTStyleGetUpsideDown (VHANDLE hTStyle);
	void    CADAPI CadTStylePutUpsideDown (VHANDLE hTStyle, BOOL bUpsideDown);
	BOOL    CADAPI CadTStyleGetBackward   (VHANDLE hTStyle);
	void    CADAPI CadTStylePutBackward   (VHANDLE hTStyle, BOOL bBackward);
	void    CADAPI CadTStyleGetFont       (VHANDLE hTStyle, TCHAR* szFontName);
	void    CADAPI CadTStylePutFont       (VHANDLE hTStyle, LPCTSTR szFontName);
	void    CADAPI CadTStyleGetTTFName    (VHANDLE hTStyle, TCHAR* szTTFName);
	void    CADAPI CadTStylePutTTFName    (VHANDLE hTStyle, LPCTSTR szTTFName);


	/********************************************************************
	*
	*  BLOCKS IN DRAWING
	*
	*********************************************************************/
	VHANDLE CADAPI CadAddBlock          (VDWG hDwg, LPCTSTR szName, double X, double Y, double Z);
	VHANDLE CADAPI CadAddBlockFromFile  (VDWG hDwg, LPCTSTR szFileName, LPCTSTR szName);
	VHANDLE CADAPI CadAddBlockFromDrw   (VDWG hDwgDest, VDWG hDwgSrc, LPCTSTR szName);
	VHANDLE CADAPI CadAddBlockFile      (VDWG hDwg, LPCTSTR szFileName);
	VHANDLE CADAPI CadAddBlockXref      (VDWG hDwg, LPCTSTR szFileName);
	VHANDLE CADAPI CadAddBlockClip      (VDWG hDwg, LPCTSTR szName, double Lef, double Bot, double W, double H);
	BOOL    CADAPI CadDeleteBlock       (VDWG hDwg, VHANDLE hBlock);
	UINT    CADAPI CadCountBlocks       (VDWG hDwg);
	VHANDLE CADAPI CadGetFirstBlock     (VDWG hDwg);
	VHANDLE CADAPI CadGetNextBlock      (VDWG hDwg, VHANDLE hBlock);
	VHANDLE CADAPI CadGetBlockByID      (VDWG hDwg, IDOBJ idBlock);
	VHANDLE CADAPI CadGetBlockByName    (VDWG hDwg, LPCTSTR szName);
	VHANDLE CADAPI CadGetCurBlock       (VDWG hDwg);
	VHANDLE CADAPI CadSetCurBlock       (VDWG hDwg, VHANDLE hBlock);
	/********************************************************************
	*  BLOCK PROPERTIES
	*********************************************************************/
	IDOBJ   CADAPI CadBlockGetID        (VHANDLE hBlock);
	void    CADAPI CadBlockGetName      (VHANDLE hBlock, TCHAR* szName);
	BOOL    CADAPI CadBlockPutName      (VHANDLE hBlock, LPCTSTR szName);
	double  CADAPI CadBlockGetBaseX     (VHANDLE hBlock);
	void    CADAPI CadBlockPutBaseX     (VHANDLE hBlock, double X);
	double  CADAPI CadBlockGetBaseY     (VHANDLE hBlock);
	void    CADAPI CadBlockPutBaseY     (VHANDLE hBlock, double Y);
	double  CADAPI CadBlockGetBaseZ     (VHANDLE hBlock);
	void    CADAPI CadBlockPutBaseZ     (VHANDLE hBlock, double Z);
	void    CADAPI CadBlockGetBase      (VHANDLE hBlock, double* pX, double* pY, double* pZ);
	void    CADAPI CadBlockPutBase      (VHANDLE hBlock, double X, double Y, double Z);
	UINT    CADAPI CadBlockCountEntities(VHANDLE hBlock);
	void    CADAPI CadBlockClear        (VHANDLE hBlock);
	void    CADAPI CadBlockAddEntity    (VHANDLE hBlock, VHANDLE hEnt);
	VHANDLE CADAPI CadBlockGetFirstPtr  (VHANDLE hBlock);
	VHANDLE CADAPI CadBlockGetNextPtr   (VHANDLE hBlock, VHANDLE hPtr);
	// Attributes
	BOOL    CADAPI CadBlockHasAttribs   (VHANDLE hBlock);
	VHANDLE CADAPI CadBlockGetAttrib    (VHANDLE hBlock, LPCTSTR szTag);
	// XREF 
	BOOL    CADAPI CadBlockIsXref   (VHANDLE hBlock);
	void    CADAPI CadXrefGetPath   (VHANDLE hBlock, TCHAR* szPathName);
	BOOL    CADAPI CadXrefPutPath   (VHANDLE hBlock, LPCTSTR szPathName);
	BOOL    CADAPI CadXrefReload    (VHANDLE hBlock);
	int     CADAPI CadXrefGetStatus (VHANDLE hBlock);
	// block's extended data
	void    CADAPI CadBlockPutExData     (VHANDLE hBlock, void* pData, int nBytes);
	int     CADAPI CadBlockGetExDataSize (VHANDLE hBlock);
	void    CADAPI CadBlockGetExData     (VHANDLE hBlock, void* pData);



	/********************************************************************
	*
	*  POINT STYLES IN DRAWING
	*
	*********************************************************************/
	VHANDLE CADAPI CadAddPntStyle           (VDWG hDwg, LPCTSTR szName, IDOBJ BlockId, double BlockScale, LPCTSTR szFontName, double TxtH, double TxtW);
	BOOL    CADAPI CadDeletePntStyle        (VDWG hDwg, VHANDLE hPntStyle);
	UINT    CADAPI CadCountPntStyles        (VDWG hDwg);
	VHANDLE CADAPI CadGetCurPntStyle        (VDWG hDwg);
	VHANDLE CADAPI CadSetCurPntStyle        (VDWG hDwg, VHANDLE hPntStyle);
	VHANDLE CADAPI CadSetCurPntStyleByID    (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadSetCurPntStyleByName  (VDWG hDwg, LPCTSTR szName);
	VHANDLE CADAPI CadGetFirstPntStyle      (VDWG hDwg);
	VHANDLE CADAPI CadGetNextPntStyle       (VDWG hDwg, VHANDLE hPntStyle);
	VHANDLE CADAPI CadGetPntStyleByID       (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadGetPntStyleByName     (VDWG hDwg, LPCTSTR szName);
	/********************************************************************
	*  POINT STYLE PROPERTIES
	*********************************************************************/
	IDOBJ   CADAPI CadPntStyleGetID         (VHANDLE hPntStyle);
	void    CADAPI CadPntStyleGetName       (VHANDLE hPntStyle, TCHAR* szName);
	void    CADAPI CadPntStylePutName       (VHANDLE hPntStyle, LPCTSTR szName);
	IDOBJ   CADAPI CadPntStyleGetBlockID    (VHANDLE hPntStyle);
	void    CADAPI CadPntStylePutBlockID    (VHANDLE hPntStyle, IDOBJ IdBlock);
	double  CADAPI CadPntStyleGetBlockScale (VHANDLE hPntStyle);
	void    CADAPI CadPntStylePutBlockScale (VHANDLE hPntStyle, double Scal);
	void    CADAPI CadPntStyleGetFont       (VHANDLE hPntStyle, TCHAR* szFontName);
	void    CADAPI CadPntStylePutFont       (VHANDLE hPntStyle, LPCTSTR szFontName);
	double  CADAPI CadPntStyleGetTextHeight (VHANDLE hPntStyle);
	void    CADAPI CadPntStylePutTextHeight (VHANDLE hPntStyle, double TxtH);
	double  CADAPI CadPntStyleGetTextWidth  (VHANDLE hPntStyle);
	void    CADAPI CadPntStylePutTextWidth  (VHANDLE hPntStyle, double TxtW);
	int     CADAPI CadPntStyleGetDrawMode   (VHANDLE hPntStyle);
	void    CADAPI CadPntStylePutDrawMode   (VHANDLE hPntStyle, int Mode);
	BOOL    CADAPI CadPntStyleGetSnap       (VHANDLE hPntStyle);
	void    CADAPI CadPntStylePutSnap       (VHANDLE hPntStyle, BOOL bSnap);
	BOOL    CADAPI CadPntStyleGetFixed      (VHANDLE hPntStyle);
	void    CADAPI CadPntStylePutFixed      (VHANDLE hPntStyle, BOOL bFixed);


	/********************************************************************
	*
	*  MULTILINE STYLES IN DRAWING
	*
	*********************************************************************/
	VHANDLE CADAPI CadAddMlineStyle         (VDWG hDwg, LPCTSTR szName);
	BOOL    CADAPI CadDeleteMlineStyle      (VDWG hDwg, VHANDLE hMStyle);
	UINT    CADAPI CadCountMlineStyles      (VDWG hDwg);
	VHANDLE CADAPI CadGetCurMlineStyle      (VDWG hDwg);
	VHANDLE CADAPI CadSetCurMlineStyle      (VDWG hDwg, VHANDLE hMStyle);
	VHANDLE CADAPI CadSetCurMlineStyleByID  (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadSetCurMlineStyleByName(VDWG hDwg, LPCTSTR szName);
	VHANDLE CADAPI CadGetFirstMlineStyle    (VDWG hDwg);
	VHANDLE CADAPI CadGetNextMlineStyle     (VDWG hDwg, VHANDLE hMStyle);
	VHANDLE CADAPI CadGetMlineStyleByID     (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadGetMlineStyleByName   (VDWG hDwg, LPCTSTR szName);
	/********************************************************************
	*  MULTILINE STYLE PROPERTIES
	*********************************************************************/
	IDOBJ   CADAPI CadMlineStyleGetID       (VHANDLE hMStyle);
	void    CADAPI CadMlineStyleGetName     (VHANDLE hMStyle, TCHAR* szName);
	void    CADAPI CadMlineStylePutName     (VHANDLE hMStyle, LPCTSTR szName);
	UINT    CADAPI CadMlineStyleGetDrawMode (VHANDLE hMStyle);
	void    CADAPI CadMlineStylePutDrawMode (VHANDLE hMStyle, UINT Mode);
	UINT    CADAPI CadMlineStyleGetNumLines (VHANDLE hMStyle);
	void    CADAPI CadMlineStylePutNumLines (VHANDLE hMStyle, UINT nLines);
	int     CADAPI CadMlineStyleGetColor    (VHANDLE hMStyle, UINT iLine);
	void    CADAPI CadMlineStylePutColor    (VHANDLE hMStyle, UINT iLine, int Color);
	IDOBJ   CADAPI CadMlineStyleGetLtypeID  (VHANDLE hMStyle, UINT iLine);
	void    CADAPI CadMlineStylePutLtypeID  (VHANDLE hMStyle, UINT iLine, IDOBJ Id);
	double  CADAPI CadMlineStyleGetOffset   (VHANDLE hMStyle, UINT iLine);
	void    CADAPI CadMlineStylePutOffset   (VHANDLE hMStyle, UINT iLine, double Offset);


	/********************************************************************
	*
	*  DIMENSION STYLES IN DRAWING
	*
	*********************************************************************/
	VHANDLE CADAPI CadAddDimStyle         (VDWG hDwg, LPCTSTR szName);
	BOOL    CADAPI CadDeleteDimStyle      (VDWG hDwg, VHANDLE hStyle);
	UINT    CADAPI CadCountDimStyles      (VDWG hDwg);
	VHANDLE CADAPI CadGetCurDimStyle      (VDWG hDwg);
	VHANDLE CADAPI CadSetCurDimStyle      (VDWG hDwg, VHANDLE hStyle);
	VHANDLE CADAPI CadSetCurDimStyleByID  (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadSetCurDimStyleByName(VDWG hDwg, LPCTSTR szName);
	VHANDLE CADAPI CadGetFirstDimStyle    (VDWG hDwg);
	VHANDLE CADAPI CadGetNextDimStyle     (VDWG hDwg, VHANDLE hStyle);
	VHANDLE CADAPI CadGetDimStyleByID     (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadGetDimStyleByName   (VDWG hDwg, LPCTSTR szName);
	/********************************************************************
	*  DIMENSION STYLE PROPERTIES
	*********************************************************************/
	IDOBJ   CADAPI CadDimStyleGetID          (VHANDLE hStyle);
	void    CADAPI CadDimStyleGetName        (VHANDLE hStyle, TCHAR* szName);
	void    CADAPI CadDimStylePutName        (VHANDLE hStyle, LPCTSTR szName);
	int     CADAPI CadDimStyleGetColor       (VHANDLE hStyle, int Item);
	void    CADAPI CadDimStylePutColor       (VHANDLE hStyle, int Item, int Color);
	int     CADAPI CadDimStyleGetLweight     (VHANDLE hStyle, int Item);
	void    CADAPI CadDimStylePutLweight     (VHANDLE hStyle, int Item, int Lweight);
	double  CADAPI CadDimStyleGetExtBeyond   (VHANDLE hStyle);
	void    CADAPI CadDimStylePutExtBeyond   (VHANDLE hStyle, double val);
	double  CADAPI CadDimStyleGetExtOffset   (VHANDLE hStyle);
	void    CADAPI CadDimStylePutExtOffset   (VHANDLE hStyle, double val);
	int     CADAPI CadDimStyleGetArrow       (VHANDLE hStyle, int Place);
	void    CADAPI CadDimStylePutArrow       (VHANDLE hStyle, int Place, int ArrType);
	double  CADAPI CadDimStyleGetArrowSize   (VHANDLE hStyle);
	void    CADAPI CadDimStylePutArrowSize   (VHANDLE hStyle, double Size);
	double  CADAPI CadDimStyleGetCenMark     (VHANDLE hStyle);
	void    CADAPI CadDimStylePutCenMark     (VHANDLE hStyle, double Size);
	double  CADAPI CadDimStyleGetTextHeight  (VHANDLE hStyle);
	void    CADAPI CadDimStylePutTextHeight  (VHANDLE hStyle, double Height);
	double  CADAPI CadDimStyleGetTextGap     (VHANDLE hStyle);
	void    CADAPI CadDimStylePutTextGap     (VHANDLE hStyle, double Gap);
	IDOBJ   CADAPI CadDimStyleGetTextStyleID (VHANDLE hStyle);
	void    CADAPI CadDimStylePutTextStyleID (VHANDLE hStyle, IDOBJ Id);
	UINT    CADAPI CadDimStyleGetTextPlace   (VHANDLE hStyle);
	void    CADAPI CadDimStylePutTextPlace   (VHANDLE hStyle, UINT Placement);
	double  CADAPI CadDimStyleGetScale       (VHANDLE hStyle);
	void    CADAPI CadDimStylePutScale       (VHANDLE hStyle, double Scal);
	double  CADAPI CadDimStyleGetRound       (VHANDLE hStyle);
	void    CADAPI CadDimStylePutRound       (VHANDLE hStyle, double RoundOff);
	int     CADAPI CadDimStyleGetUnits       (VHANDLE hStyle, BOOL bAngular);
	void    CADAPI CadDimStylePutUnits       (VHANDLE hStyle, BOOL bAngular, int UnitsType);
	int     CADAPI CadDimStyleGetPrecision   (VHANDLE hStyle, BOOL bAngular);
	void    CADAPI CadDimStylePutPrecision   (VHANDLE hStyle, BOOL bAngular, int Prec);
	BOOL    CADAPI CadDimStyleGetZeroSup     (VHANDLE hStyle, BOOL bAngular);
	void    CADAPI CadDimStylePutZeroSup     (VHANDLE hStyle, BOOL bAngular, BOOL bSuppress);
	int     CADAPI CadDimStyleGetSeparator   (VHANDLE hStyle);
	void    CADAPI CadDimStylePutSeparator   (VHANDLE hStyle, int DecSep);
	void    CADAPI CadDimStyleGetPrefix      (VHANDLE hStyle, TCHAR* szPrefix);
	void    CADAPI CadDimStylePutPrefix      (VHANDLE hStyle, LPCTSTR szPrefix);
	void    CADAPI CadDimStyleGetSuffix      (VHANDLE hStyle, TCHAR* szSuffix);
	void    CADAPI CadDimStylePutSuffix      (VHANDLE hStyle, LPCTSTR szSuffix);



	/******************************************************************************
	* LOCATE ENTITY
	*******************************************************************************/
	VHANDLE CADAPI CadGetEntityByCursor   (VDWG hDwg);
	void    CADAPI CadGetEntitiesByPoint  (VDWG hDwg, int Xwin, int Ywin, int* phEnt, int* pnEnts, int iMax);
	void    CADAPI CadGetEntitiesByRect   (VDWG hDwg, int Lwin, int Twin, int Rwin, int Bwin, int* phEnt, int* pnEnts, int nMax);
	VHANDLE CADAPI CadGetEntityByPoint    (VDWG hDwg, int Xwin, int Ywin);
	VHANDLE CADAPI CadGetEntityByPointIn  (VDWG hDwg, double Xdisp, double Ydisp);
	VHANDLE CADAPI CadGetEntityByID       (VDWG hDwg, IDOBJ Id);
	VHANDLE CADAPI CadGetEntityByUserData (VDWG hDwg, DWORD UserData);
	VHANDLE CADAPI CadGetEntityByPtr      (VHANDLE hPtr);
	VHANDLE CADAPI CadGetFirstEntity      (VDWG hDwg);
	VHANDLE CADAPI CadGetNextEntity       (VDWG hDwg, VHANDLE hEnt);
	VHANDLE CADAPI CadGetPickEntity       (VDWG hDwg);

	/******************************************************************************
	* ENTITY PROPERTIES
	*******************************************************************************/
	IDOBJ   CADAPI CadEntityGetID         (VHANDLE hEnt);
	DWORD   CADAPI CadEntityGetType       (VHANDLE hEnt);
	double  CADAPI CadEntityGetLeft       (VHANDLE hEnt);
	double  CADAPI CadEntityGetBottom     (VHANDLE hEnt);
	double  CADAPI CadEntityGetRight      (VHANDLE hEnt);
	double  CADAPI CadEntityGetTop        (VHANDLE hEnt);
	int     CADAPI CadEntityGetNumPaths   (VHANDLE hEnt);
	int     CADAPI CadEntityGetPathSize   (VHANDLE hEnt, int iPath);
	void    CADAPI CadEntityGetVer        (VHANDLE hEnt, int iVer, double* pX, double* pY);
	BOOL    CADAPI CadEntityGetGrip       (VHANDLE hEnt, int iGrip, double* pX, double* pY, double* pZ);
	IDOBJ   CADAPI CadEntityGetLayerID    (VHANDLE hEnt);
	BOOL    CADAPI CadEntityPutLayerID    (VHANDLE hEnt, VDWG hDwg, IDOBJ LayerID);
	IDOBJ   CADAPI CadEntityGetPageID     (VHANDLE hEnt);
	void    CADAPI CadEntityPutPageID     (VHANDLE hEnt, IDOBJ PageID);
	IDOBJ   CADAPI CadEntityGetLinetypeID (VHANDLE hEnt);
	void    CADAPI CadEntityPutLinetypeID (VHANDLE hEnt, IDOBJ Id);
	double  CADAPI CadEntityGetLtScale    (VHANDLE hEnt);
	void    CADAPI CadEntityPutLtScale    (VHANDLE hEnt, double lts);
	int     CADAPI CadEntityGetColor      (VHANDLE hEnt);
	void    CADAPI CadEntityPutColor      (VHANDLE hEnt, int Color);
	DWORD   CADAPI CadEntityGetLineweight (VHANDLE hEnt);
	void    CADAPI CadEntityPutLineweight (VHANDLE hEnt, int lw);
	DWORD   CADAPI CadEntityGetUserData   (VHANDLE hEnt);
	void    CADAPI CadEntityPutUserData   (VHANDLE hEnt, DWORD val);
	BOOL    CADAPI CadEntityGetFilled     (VHANDLE hEnt);
	void    CADAPI CadEntityPutFilled     (VHANDLE hEnt, BOOL bFilled);
	BOOL    CADAPI CadEntityGetBorder     (VHANDLE hEnt);
	void    CADAPI CadEntityPutBorder     (VHANDLE hEnt, BOOL bBorder);
	int     CADAPI CadEntityGetBordColor  (VHANDLE hEnt);
	void    CADAPI CadEntityPutBordColor  (VHANDLE hEnt, int Color);
	BOOL    CADAPI CadEntityGetBlink      (VHANDLE hEnt);
	void    CADAPI CadEntityPutBlink      (VHANDLE hEnt, BOOL bBlink);
	BOOL    CADAPI CadEntityGetVisible    (VHANDLE hEnt);
	void    CADAPI CadEntityPutVisible    (VHANDLE hEnt, BOOL bVisible);
	BOOL    CADAPI CadEntityGetDeleted    (VHANDLE hEnt);
	BOOL    CADAPI CadEntityGetSelected   (VDWG hDwg, VHANDLE hEnt);
	BOOL    CADAPI CadEntityGetLocked     (VHANDLE hEnt);
	void    CADAPI CadEntityPutLocked     (VHANDLE hEnt, BOOL bLock);
	// entity's extended data
	void    CADAPI CadEntityPutExData     (VHANDLE hEnt, void* pData, int nBytes);
	int     CADAPI CadEntityGetExDataSize (VHANDLE hEnt);
	void    CADAPI CadEntityGetExData     (VHANDLE hEnt, void* pData);
	VHANDLE CADAPI CadEntityGetExDataPtr  (VHANDLE hEnt);

	void    CADAPI CadEntityPutParkData   (VHANDLE hEnt, LPCTSTR szPark, LPCTSTR szWay);
	BOOL    CADAPI CadEntityGetParkData   (VHANDLE hEnt, TCHAR* szPark, TCHAR* szWay);


	/******************************************************************************
	* ENTITY EDIT FUNCTIONS
	*******************************************************************************/
	void    CADAPI CadEntityErase         (VHANDLE hEnt, BOOL bErase);
	VHANDLE CADAPI CadEntityCopy          (VHANDLE hEnt);
	void    CADAPI CadEntityMove          (VHANDLE hEnt, double dx, double dy, double dz);
	void    CADAPI CadEntityMoveGrip      (VHANDLE hEnt, int iGrip, double dx, double dy, double dz);
	void    CADAPI CadEntityScale         (VHANDLE hEnt, double x0, double y0, double z0, double Scal);
	void    CADAPI CadEntityRotate        (VHANDLE hEnt, double x0, double y0, double z0, double Angle);
	void    CADAPI CadEntityMirror        (VHANDLE hEnt, double x0, double y0, double z0, double x1, double y1, double z1);
	BOOL    CADAPI CadEntityExplode       (VHANDLE hEnt, long* pnOutEnts, long* pFirstID);
	BOOL    CADAPI CadAddEdge             (VHANDLE hEnt);
	BOOL    CADAPI CadEntityTrim          (VHANDLE hEnt, double x, double y);
	BOOL    CADAPI CadEntityExtend        (VHANDLE hEnt, double x, double y);
	void    CADAPI CadEntityToTop         (VHANDLE hEnt);
	void    CADAPI CadEntityToBottom      (VHANDLE hEnt);
	void    CADAPI CadEntitySwap          (VHANDLE hEnt1, VHANDLE hEnt2);


	/******************************************************************************
	* POINT
	*******************************************************************************/
	VHANDLE CADAPI CadAddPoint           (VDWG hDwg, double X, double Y, double Z);
	IDOBJ   CADAPI CadPointGetStyleID    (VHANDLE hEnt);
	void    CADAPI CadPointPutStyleID    (VHANDLE hEnt, IDOBJ Id);
	double  CADAPI CadPointGetX          (VHANDLE hEnt);
	void    CADAPI CadPointPutX          (VHANDLE hEnt, double X);
	double  CADAPI CadPointGetY          (VHANDLE hEnt);
	void    CADAPI CadPointPutY          (VHANDLE hEnt, double Y);
	double  CADAPI CadPointGetZ          (VHANDLE hEnt);
	void    CADAPI CadPointPutZ          (VHANDLE hEnt, double Z);
	void    CADAPI CadPointGetCoord      (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void    CADAPI CadPointPutCoord      (VHANDLE hEnt, double X, double Y, double Z);
	void    CADAPI CadPointGetTextOffset (VHANDLE hEnt, double* pDX, double* pDY, double* pDZ);
	void    CADAPI CadPointPutTextOffset (VHANDLE hEnt, double DX, double DY, double DZ);
	double  CADAPI CadPointGetTextX      (VHANDLE hEnt);
	void    CADAPI CadPointPutTextX      (VHANDLE hEnt, double X);
	double  CADAPI CadPointGetTextY      (VHANDLE hEnt);
	void    CADAPI CadPointPutTextY      (VHANDLE hEnt, double Y);
	void    CADAPI CadPointGetText       (VHANDLE hEnt, TCHAR* szText);
	void    CADAPI CadPointPutText       (VHANDLE hEnt, LPCTSTR szText);
	double  CADAPI CadPointGetTextAngle  (VHANDLE hEnt);
	void    CADAPI CadPointPutTextAngle  (VHANDLE hEnt, double Angle);
	double  CADAPI CadPointGetBlockAngle (VHANDLE hEnt);
	void    CADAPI CadPointPutBlockAngle (VHANDLE hEnt, double Angle);

	/******************************************************************************
	* LINE
	*******************************************************************************/
	VHANDLE CADAPI CadAddLine       (VDWG hDwg, double x1, double y1, double z1, double x2, double y2, double z2);
	VHANDLE CADAPI CadAddXLine      (VDWG hDwg, double x, double y, double z, double dx, double dy, double dz);
	VHANDLE CADAPI CadAddRay        (VDWG hDwg, double x, double y, double z, double dx, double dy, double dz);
	double  CADAPI CadLineGetX1     (VHANDLE hEnt);
	void    CADAPI CadLinePutX1     (VHANDLE hEnt, double X);
	double  CADAPI CadLineGetY1     (VHANDLE hEnt);
	void    CADAPI CadLinePutY1     (VHANDLE hEnt, double Y);
	double  CADAPI CadLineGetZ1     (VHANDLE hEnt);
	void    CADAPI CadLinePutZ1     (VHANDLE hEnt, double Z);
	double  CADAPI CadLineGetX2     (VHANDLE hEnt);
	void    CADAPI CadLinePutX2     (VHANDLE hEnt, double X);
	double  CADAPI CadLineGetY2     (VHANDLE hEnt);
	void    CADAPI CadLinePutY2     (VHANDLE hEnt, double Y);
	double  CADAPI CadLineGetZ2     (VHANDLE hEnt);
	void    CADAPI CadLinePutZ2     (VHANDLE hEnt, double Z);
	void    CADAPI CadLineGetPoint1 (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void    CADAPI CadLinePutPoint1 (VHANDLE hEnt, double X, double Y, double Z);
	void    CADAPI CadLineGetPoint2 (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void    CADAPI CadLinePutPoint2 (VHANDLE hEnt, double X, double Y, double Z);
	BOOL    CADAPI CadLineIsX       (VHANDLE hEnt);
	BOOL    CADAPI CadLineIsRay     (VHANDLE hEnt);


	/******************************************************************************
	* CIRCLE, ARC, ELLIPSE
	*******************************************************************************/
	VHANDLE CADAPI CadAddCircle        (VDWG hDwg, double X, double Y, double Z, double Radius);
	VHANDLE CADAPI CadAddCircle3P      (VDWG hDwg, double X1, double Y1, double Z, double X2, double Y2, double X3, double Y3);
	VHANDLE CADAPI CadAddArc           (VDWG hDwg, double X, double Y, double Z, double Radius, double StartAngle, double ArcAngle);
	VHANDLE CADAPI CadAddArc3P         (VDWG hDwg, double X1, double Y1, double Z, double X2, double Y2, double X3, double Y3);
	VHANDLE CADAPI CadAddArcCSE        (VDWG hDwg, double Xc, double Yc, double Z, double Xs, double Ys, double Xe, double Ye, BOOL bCCW);
	VHANDLE CADAPI CadAddArcSED        (VDWG hDwg, double Xs, double Ys, double Z, double Xe, double Ye, double DirAngle);
	VHANDLE CADAPI CadAddArcContinue   (VDWG hDwg, VHANDLE hEnt, double Xe, double Ye, double Z);
	VHANDLE CADAPI CadAddEllipse       (VDWG hDwg, double X, double Y, double Z, double RadH, double RadV, double RotAngle);
	int     CADAPI CadArcGetType       (VHANDLE hEnt);
	double  CADAPI CadArcGetCenterX    (VHANDLE hEnt);
	void    CADAPI CadArcPutCenterX    (VHANDLE hEnt, double X);
	double  CADAPI CadArcGetCenterY    (VHANDLE hEnt);
	void    CADAPI CadArcPutCenterY    (VHANDLE hEnt, double Y);
	double  CADAPI CadArcGetCenterZ    (VHANDLE hEnt);
	void    CADAPI CadArcPutCenterZ    (VHANDLE hEnt, double Z);
	void    CADAPI CadArcGetCenter     (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void    CADAPI CadArcPutCenter     (VHANDLE hEnt, double X, double Y, double Z);
	double  CADAPI CadArcGetRadius     (VHANDLE hEnt);
	void    CADAPI CadArcPutRadius     (VHANDLE hEnt, double R);
	double  CADAPI CadArcGetRadHor     (VHANDLE hEnt);
	void    CADAPI CadArcPutRadHor     (VHANDLE hEnt, double R);
	double  CADAPI CadArcGetRadVer     (VHANDLE hEnt);
	void    CADAPI CadArcPutRadVer     (VHANDLE hEnt, double R);
	double  CADAPI CadArcGetStartAngle (VHANDLE hEnt);
	void    CADAPI CadArcPutStartAngle (VHANDLE hEnt, double Ang);
	double  CADAPI CadArcGetAngle      (VHANDLE hEnt);
	void    CADAPI CadArcPutAngle      (VHANDLE hEnt, double Ang);
	double  CADAPI CadArcGetRotAngle   (VHANDLE hEnt);
	void    CADAPI CadArcPutRotAngle   (VHANDLE hEnt, double Ang);
	BOOL    CADAPI CadArcGetSector     (VHANDLE hEnt);
	void    CADAPI CadArcPutSector     (VHANDLE hEnt, BOOL bSector);
	void    CADAPI CadArcGetStartPt    (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	BOOL    CADAPI CadArcPutStartPt    (VHANDLE hEnt, double X, double Y, double Z);
	void    CADAPI CadArcGetEndPt      (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	BOOL    CADAPI CadArcPutEndPt      (VHANDLE hEnt, double X, double Y, double Z);
	void    CADAPI CadArcGetMidPt      (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	BOOL    CADAPI CadArcPutMidPt      (VHANDLE hEnt, double X, double Y, double Z);
	void    CADAPI CadArcGet3Pt        (VHANDLE hEnt, double* pXsta, double* pYsta, double* pZ, double* pXmid, double* pYmid, double* pXend, double* pYend);
	BOOL    CADAPI CadArcPut3Pt        (VHANDLE hEnt, double Xsta, double Ysta, double Z, double Xmid, double Ymid, double Xe, double Ye);
	void    CADAPI CadArcDivide        (VHANDLE hEnt, int nPoints, double* X, double* Y);


	/******************************************************************************
	* POLYLINE
	*******************************************************************************/
	void    CADAPI CadClearVertices   ();
	void    CADAPI CadAddVertex       (double X, double Y, double Z);
	void    CADAPI CadAddVertex2      (double X, double Y, double Z, double Prm, double StartW, double EndW);
	VHANDLE CADAPI CadAddPolyline     (VDWG hDwg, int FitType, BOOL bClosed);
	VHANDLE CADAPI CadAddPolylineW    (VDWG hDwg, int FitType, BOOL bClosed, double Width);
	VHANDLE CADAPI CadAddPolygon      (VDWG hDwg, int Color, BOOL bBorder);
	VHANDLE CADAPI CadAddBoundPolygon (VDWG hDwg, double X, double Y, double Z);
	VHANDLE CADAPI CadAddBoundary     (VDWG hDwg, double X, double Y, double Z);
	BOOL    CADAPI CadPlineInsertVer  (VHANDLE hEnt, UINT iVer);
	BOOL    CADAPI CadPlineDeleteVer  (VHANDLE hEnt, UINT iVer);
	UINT    CADAPI CadPlineGetNumVers (VHANDLE hEnt);
	void    CADAPI CadPlinePutNumVers (VHANDLE hEnt, UINT nVers);
	double  CADAPI CadPlineGetX       (VHANDLE hEnt, UINT iVer);
	void    CADAPI CadPlinePutX       (VHANDLE hEnt, UINT iVer, double X);
	double  CADAPI CadPlineGetY       (VHANDLE hEnt, UINT iVer);
	void    CADAPI CadPlinePutY       (VHANDLE hEnt, UINT iVer, double Y);
	double  CADAPI CadPlineGetZ       (VHANDLE hEnt, UINT iVer);
	void    CADAPI CadPlinePutZ       (VHANDLE hEnt, UINT iVer, double Z);
	void    CADAPI CadPlineGetVer     (VHANDLE hEnt, UINT iVer, double* pX, double* pY, double* pZ);
	void    CADAPI CadPlinePutVer     (VHANDLE hEnt, UINT iVer, double X, double Y, double Z);
	double  CADAPI CadPlineGetPrm     (VHANDLE hEnt, UINT iVer);
	void    CADAPI CadPlinePutPrm     (VHANDLE hEnt, UINT iVer, double Prm);
	double  CADAPI CadPlineGetStartW  (VHANDLE hEnt, UINT iVer);
	void    CADAPI CadPlinePutStartW  (VHANDLE hEnt, UINT iVer, double Width);
	double  CADAPI CadPlineGetEndW    (VHANDLE hEnt, UINT iVer);
	void    CADAPI CadPlinePutEndW    (VHANDLE hEnt, UINT iVer, double Width);
	void    CADAPI CadPlinePutZ1      (VHANDLE hEnt, double Z);
	double  CADAPI CadPlineGetRadius  (VHANDLE hEnt);
	void    CADAPI CadPlinePutRadius  (VHANDLE hEnt, double Rad);
	double  CADAPI CadPlineGetWidth   (VHANDLE hEnt);
	void    CADAPI CadPlinePutWidth   (VHANDLE hEnt, double Width);
	BOOL    CADAPI CadPlineGetClosed  (VHANDLE hEnt);
	void    CADAPI CadPlinePutClosed  (VHANDLE hEnt, BOOL bClosed);
	int     CADAPI CadPlineGetFit     (VHANDLE hEnt);
	void    CADAPI CadPlinePutFit     (VHANDLE hEnt, int FitType);
	void    CADAPI CadPlineGetStartTan(VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void    CADAPI CadPlinePutStartTan(VHANDLE hEnt, double X, double Y, double Z);
	void    CADAPI CadPlineGetEndTan  (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void    CADAPI CadPlinePutEndTan  (VHANDLE hEnt, double X, double Y, double Z);
	double  CADAPI CadPlineGetLength  (VHANDLE hEnt);
	double  CADAPI CadPlineGetArea    (VHANDLE hEnt);
	BOOL    CADAPI CadPlineContainPoint (VHANDLE hEnt, double X, double Y);
	double  CADAPI CadPlineGetNearPoint (VHANDLE hEnt, double X, double Y, double Z, double* pX, double* pY, double* pZ, double* pDist);
	BOOL    CADAPI CadPlineGetDistPoint (VHANDLE hEnt, double Dist, double* pX, double* pY, double* pZ, double* pDirAngle);
	BOOL    CADAPI CadPlineGetInterPoint (VHANDLE hEnt, double x1, double y1, double x2, double y2, double* pX, double* pY, double* pDist);


	/******************************************************************************
	* RECTANGLE
	*******************************************************************************/
	VHANDLE CADAPI CadAddRect       (VDWG hDwg, double X, double Y, double Z, double Width, double Height, double Angle);
	void    CADAPI CadRectGetCenter (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void    CADAPI CadRectPutCenter (VHANDLE hEnt, double X, double Y, double Z);
	double  CADAPI CadRectGetWidth  (VHANDLE hEnt);
	void    CADAPI CadRectPutWidth  (VHANDLE hEnt, double Width);
	double  CADAPI CadRectGetHeight (VHANDLE hEnt);
	void    CADAPI CadRectPutHeight (VHANDLE hEnt, double Height);
	double  CADAPI CadRectGetAngle  (VHANDLE hEnt);
	void    CADAPI CadRectPutAngle  (VHANDLE hEnt, double Angle);
	double  CADAPI CadRectGetRadius (VHANDLE hEnt);
	void    CADAPI CadRectPutRadius (VHANDLE hEnt, double Radius);

	BOOL    CADAPI CadRectGetPrint  (VHANDLE hEnt);
	void    CADAPI CadRectPutPrint  (VHANDLE hEnt, BOOL bPrnRect);
	void    CADAPI CadRectGetName   (VHANDLE hEnt, TCHAR* szName);
	void    CADAPI CadRectPutName   (VHANDLE hEnt, LPCTSTR szName);
	BOOL    CADAPI CadRectPrint     (VDWG hDwg, VHANDLE hEnt, HDC hDC);


	/******************************************************************************
	* MULTILINE
	*******************************************************************************/
	VHANDLE CADAPI CadAddMline        (VDWG hDwg, BOOL bClosed);
	BOOL    CADAPI CadMlineInsertVer  (VHANDLE hEnt, UINT iVer);
	BOOL    CADAPI CadMlineDeleteVer  (VHANDLE hEnt, UINT iVer);
	UINT    CADAPI CadMlineGetNumVers (VHANDLE hEnt);
	void    CADAPI CadMlinePutNumVers (VHANDLE hEnt, UINT nVers);
	void    CADAPI CadMlineGetVer     (VHANDLE hEnt, UINT iVer, double* pX, double* pY, double* pZ);
	void    CADAPI CadMlinePutVer     (VHANDLE hEnt, UINT iVer, double X, double Y, double Z);
	void    CADAPI CadMlinePutZ1      (VHANDLE hEnt, double Z);
	BOOL    CADAPI CadMlineGetClosed  (VHANDLE hEnt);
	void    CADAPI CadMlinePutClosed  (VHANDLE hEnt, BOOL bClosed);
	void    CADAPI CadMlinePutScale   (VHANDLE hEnt, double Scal);
	double  CADAPI CadMlineGetScale   (VHANDLE hEnt);
	void    CADAPI CadMlinePutJust    (VHANDLE hEnt, int Just);
	int     CADAPI CadMlineGetJust    (VHANDLE hEnt);
	double  CADAPI CadMlineGetLength  (VHANDLE hEnt);
	IDOBJ   CADAPI CadMlineGetStyleID (VHANDLE hEnt);
	void    CADAPI CadMlinePutStyleID (VHANDLE hEnt, IDOBJ Id);


	/******************************************************************************
	* TEXT
	*******************************************************************************/
	int     CADAPI CadSetTextAlign     (VDWG hDwg, int Align);
	double  CADAPI CadSetTextHeight    (VDWG hDwg, double Height);
	double  CADAPI CadSetTextWidth     (VDWG hDwg, double Width);
	double  CADAPI CadSetTextRotAngle  (VDWG hDwg, double Angle);
	double  CADAPI CadSetTextOblique   (VDWG hDwg, double Angle);
	BOOL    CADAPI CadSetTextUpsideDown(VDWG hDwg, BOOL bUpDown);
	BOOL    CADAPI CadSetTextBackward  (VDWG hDwg, BOOL bBack);
	VHANDLE CADAPI CadAddText          (VDWG hDwg, LPCTSTR szText, double X, double Y, double Z);
	VHANDLE CADAPI CadAddText2         (VDWG hDwg, LPCTSTR szText, double X, double Y, double Z, int Align, double H, double W, double RotAngle, double Oblique);
	IDOBJ   CADAPI CadTextGetStyleID   (VHANDLE hEnt);
	void    CADAPI CadTextPutStyleID   (VHANDLE hEnt, IDOBJ Id);
	double  CADAPI CadTextGetX         (VHANDLE hEnt);
	void    CADAPI CadTextPutX         (VHANDLE hEnt, double X);
	double  CADAPI CadTextGetY         (VHANDLE hEnt);
	void    CADAPI CadTextPutY         (VHANDLE hEnt, double Y);
	double  CADAPI CadTextGetZ         (VHANDLE hEnt);
	void    CADAPI CadTextPutZ         (VHANDLE hEnt, double Z);
	void    CADAPI CadTextGetPoint     (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void    CADAPI CadTextPutPoint     (VHANDLE hEnt, double X, double Y, double Z);
	UINT    CADAPI CadTextGetLen       (VHANDLE hEnt);
	void    CADAPI CadTextGetText      (VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	void    CADAPI CadTextPutText      (VHANDLE hEnt, LPCTSTR szText);
	double  CADAPI CadTextGetAngle     (VHANDLE hEnt);
	void    CADAPI CadTextPutAngle     (VHANDLE hEnt, double Angle);
	double  CADAPI CadTextGetHeight    (VHANDLE hEnt);
	void    CADAPI CadTextPutHeight    (VHANDLE hEnt, double Height);
	double  CADAPI CadTextGetWidth     (VHANDLE hEnt);
	void    CADAPI CadTextPutWidth     (VHANDLE hEnt, double Width);
	double  CADAPI CadTextGetOblique   (VHANDLE hEnt);
	void    CADAPI CadTextPutOblique   (VHANDLE hEnt, double Angle);
	int     CADAPI CadTextGetAlign     (VHANDLE hEnt);
	void    CADAPI CadTextPutAlign     (VHANDLE hEnt, int Align);
	BOOL    CADAPI CadTextGetBackward  (VHANDLE hEnt);
	void    CADAPI CadTextPutBackward  (VHANDLE hEnt, BOOL bBackward);
	BOOL    CADAPI CadTextGetUpsideDown(VHANDLE hEnt);
	void    CADAPI CadTextPutUpsideDown(VHANDLE hEnt, BOOL bUpsideDown);
	double  CADAPI CadTextGetBoxWidth  (VHANDLE hEnt);
	void    CADAPI CadTextGetPoint0    (VHANDLE hEnt, double* pX, double* pY, double* pZ);


	/******************************************************************************
	* MULTILINE TEXT
	*******************************************************************************/
	VHANDLE CADAPI CadAddMText          (VDWG hDwg, LPCTSTR szText, double RectWidth, double X, double Y, double Z, int Align, double RotAngle);
	IDOBJ   CADAPI CadMTextGetStyleID   (VHANDLE hEnt);
	void    CADAPI CadMTextPutStyleID   (VHANDLE hEnt, IDOBJ Id);
	void    CADAPI CadMTextGetPoint     (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void    CADAPI CadMTextPutPoint     (VHANDLE hEnt, double X, double Y, double Z);
	UINT    CADAPI CadMTextGetLen       (VHANDLE hEnt);
	void    CADAPI CadMTextGetText      (VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	void    CADAPI CadMTextPutText      (VHANDLE hEnt, LPCTSTR szText);
	double  CADAPI CadMTextGetRectWidth (VHANDLE hEnt);
	void    CADAPI CadMTextPutRectWidth (VHANDLE hEnt, double RectWidth);
	int     CADAPI CadMTextGetAlign     (VHANDLE hEnt);
	void    CADAPI CadMTextPutAlign     (VHANDLE hEnt, int Align);
	double  CADAPI CadMTextGetHeight    (VHANDLE hEnt);
	void    CADAPI CadMTextPutHeight    (VHANDLE hEnt, double Height);
	double  CADAPI CadMTextGetAngle     (VHANDLE hEnt);
	void    CADAPI CadMTextPutAngle     (VHANDLE hEnt, double Angle);
	double  CADAPI CadMTextGetWidth     (VHANDLE hEnt);
	void    CADAPI CadMTextPutWidth     (VHANDLE hEnt, double Width);
	double  CADAPI CadMTextGetLineSpace (VHANDLE hEnt);
	void    CADAPI CadMTextPutLineSpace (VHANDLE hEnt, double LineSpace);
	double  CADAPI CadMTextGetAW        (VHANDLE hEnt);
	double  CADAPI CadMTextGetAH        (VHANDLE hEnt);


	/******************************************************************************
	* WINDOWS TEXT
	*******************************************************************************/
	VHANDLE CADAPI CadAddWText          (VDWG hDwg, LPCTSTR szText, double X, double Y, double Z);
	VHANDLE CADAPI CadAddWText2         (VDWG hDwg, LPCTSTR szText, double X, double Y, double Z, int Align, double H, double RotAngle, bool bItalic, bool bUnderline, bool bStrikeout);
	IDOBJ   CADAPI CadWTextGetStyleID   (VHANDLE hEnt);
	void    CADAPI CadWTextPutStyleID   (VHANDLE hEnt, IDOBJ Id);
	void    CADAPI CadWTextGetPoint     (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void    CADAPI CadWTextPutPoint     (VHANDLE hEnt, double X, double Y, double Z);
	UINT    CADAPI CadWTextGetLen       (VHANDLE hEnt);
	void    CADAPI CadWTextGetText      (VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	void    CADAPI CadWTextPutText      (VHANDLE hEnt, LPCTSTR szText);
	double  CADAPI CadWTextGetAngle     (VHANDLE hEnt);
	void    CADAPI CadWTextPutAngle     (VHANDLE hEnt, double Angle);
	double  CADAPI CadWTextGetHeight    (VHANDLE hEnt);
	void    CADAPI CadWTextPutHeight    (VHANDLE hEnt, double Height);
	int     CADAPI CadWTextGetAlign     (VHANDLE hEnt);
	void    CADAPI CadWTextPutAlign     (VHANDLE hEnt, int Align);
	BOOL    CADAPI CadWTextGetItalic    (VHANDLE hEnt);
	void    CADAPI CadWTextPutItalic    (VHANDLE hEnt, BOOL bItalic);
	BOOL    CADAPI CadWTextGetStrikeout (VHANDLE hEnt);
	void    CADAPI CadWTextPutStrikeout (VHANDLE hEnt, BOOL bStrikeout);
	BOOL    CADAPI CadWTextGetUnderline (VHANDLE hEnt);
	void    CADAPI CadWTextPutUnderline (VHANDLE hEnt, BOOL bUnderline);


	/******************************************************************************
	* BLOCK INSERTION
	*******************************************************************************/
	VHANDLE CADAPI CadAddInsBlock        (VDWG hDwg, IDOBJ idBlock, double X, double Y, double Z, double Scal, double Angle);
	VHANDLE CADAPI CadAddInsBlockM       (VDWG hDwg, IDOBJ idBlock, double X, double Y, double Z, double Scal, double Angle, int NumCols, int NumRows, double ColDist, double RowDist);
	IDOBJ   CADAPI CadInsBlockGetBlockID (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutBlockID (VHANDLE hEnt, IDOBJ Id);
	double  CADAPI CadInsBlockGetX       (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutX       (VHANDLE hEnt, double X);
	double  CADAPI CadInsBlockGetY       (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutY       (VHANDLE hEnt, double Y);
	double  CADAPI CadInsBlockGetZ       (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutZ       (VHANDLE hEnt, double Z);
	void    CADAPI CadInsBlockGetPoint   (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void    CADAPI CadInsBlockPutPoint   (VHANDLE hEnt, double X, double Y, double Z);
	double  CADAPI CadInsBlockGetScale   (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutScale   (VHANDLE hEnt, double Scal);
	double  CADAPI CadInsBlockGetScaleX  (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutScaleX  (VHANDLE hEnt, double Sx);
	double  CADAPI CadInsBlockGetScaleY  (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutScaleY  (VHANDLE hEnt, double Sy);
	double  CADAPI CadInsBlockGetScaleZ  (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutScaleZ  (VHANDLE hEnt, double Sz);
	double  CADAPI CadInsBlockGetAngle   (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutAngle   (VHANDLE hEnt, double Angle);
	UINT    CADAPI CadInsBlockGetNumRows (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutNumRows (VHANDLE hEnt, UINT NumRows);
	UINT    CADAPI CadInsBlockGetNumCols (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutNumCols (VHANDLE hEnt, UINT NumCols);
	double  CADAPI CadInsBlockGetRowDist (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutRowDist (VHANDLE hEnt, double RowDist);
	double  CADAPI CadInsBlockGetColDist (VHANDLE hEnt);
	void    CADAPI CadInsBlockPutColDist (VHANDLE hEnt, double ColDist);
	// Attributes
	BOOL    CADAPI CadInsBlockHasAttribs  (VHANDLE hEnt);
	VHANDLE CADAPI CadInsBlockGetFirstAtt (VHANDLE hEnt);
	VHANDLE CADAPI CadInsBlockGetNextAtt  (VHANDLE hEnt, VHANDLE hAtt);


	/******************************************************************************
	* ATTRIBUTE
	*******************************************************************************/
	VHANDLE CADAPI CadAddAttrib         (VDWG hDwg, LPCTSTR szTag, LPCTSTR szDefValue, double X, double Y, double Z);
	IDOBJ   CADAPI CadAttGetStyleID     (VHANDLE hEnt);
	void    CADAPI CadAttPutStyleID     (VHANDLE hEnt, IDOBJ Id);
	void    CADAPI CadAttGetPoint       (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void    CADAPI CadAttPutPoint       (VHANDLE hEnt, double X, double Y, double Z);
	void    CADAPI CadAttGetTag         (VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	void    CADAPI CadAttPutTag         (VHANDLE hEnt, LPCTSTR szText);
	void    CADAPI CadAttGetPrompt      (VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	void    CADAPI CadAttPutPrompt      (VHANDLE hEnt, LPCTSTR szText);
	void    CADAPI CadAttGetDefValue    (VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	void    CADAPI CadAttPutDefValue    (VHANDLE hEnt, LPCTSTR szText);
	void    CADAPI CadAttGetValue       (VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	void    CADAPI CadAttPutValue       (VHANDLE hEnt, LPCTSTR szText);
	double  CADAPI CadAttGetAngle       (VHANDLE hEnt);
	void    CADAPI CadAttPutAngle       (VHANDLE hEnt, double Angle);
	double  CADAPI CadAttGetHeight      (VHANDLE hEnt);
	void    CADAPI CadAttPutHeight      (VHANDLE hEnt, double Height);
	double  CADAPI CadAttGetWidth       (VHANDLE hEnt);
	void    CADAPI CadAttPutWidth       (VHANDLE hEnt, double Width);
	double  CADAPI CadAttGetOblique     (VHANDLE hEnt);
	void    CADAPI CadAttPutOblique     (VHANDLE hEnt, double Angle);
	int     CADAPI CadAttGetAlign       (VHANDLE hEnt);
	void    CADAPI CadAttPutAlign       (VHANDLE hEnt, int Align);
	BOOL    CADAPI CadAttGetBackward    (VHANDLE hEnt);
	void    CADAPI CadAttPutBackward    (VHANDLE hEnt, BOOL bBackward);
	BOOL    CADAPI CadAttGetUpsideDown  (VHANDLE hEnt);
	void    CADAPI CadAttPutUpsideDown  (VHANDLE hEnt, BOOL bUpsideDown);
	int     CADAPI CadAttGetMode        (VHANDLE hEnt);
	void    CADAPI CadAttPutMode        (VHANDLE hEnt, int Mode);
	//BOOL    CADAPI CadAttGetConst       (VHANDLE hEnt);
	//void    CADAPI CadAttPutConst       (VHANDLE hEnt, BOOL bConst);


	/******************************************************************************
	* XREF
	*******************************************************************************/
	//VHANDLE CADAPI CadAddXref       (VDWG hDwg, LPCTSTR szFileName, double X, double Y, double Z, double Scal, double Angle);
	//void    CADAPI CadXrefGetFile   (VHANDLE hEnt, TCHAR* szFileName);
	//void    CADAPI CadXrefPutFile   (VHANDLE hEnt, LPCTSTR szFileName);
	//void    CADAPI CadXrefGetPoint  (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	//void    CADAPI CadXrefPutPoint  (VHANDLE hEnt, double X, double Y, double Z);
	//double  CADAPI CadXrefGetScale  (VHANDLE hEnt);
	//void    CADAPI CadXrefPutScale  (VHANDLE hEnt, double Scal);
	//double  CADAPI CadXrefGetScaleX (VHANDLE hEnt);
	//void    CADAPI CadXrefPutScaleX (VHANDLE hEnt, double Sx);
	//double  CADAPI CadXrefGetScaleY (VHANDLE hEnt);
	//void    CADAPI CadXrefPutScaleY (VHANDLE hEnt, double Sy);
	//double  CADAPI CadXrefGetScaleZ (VHANDLE hEnt);
	//void    CADAPI CadXrefPutScaleZ (VHANDLE hEnt, double Sz);
	//double  CADAPI CadXrefGetAngle  (VHANDLE hEnt);
	//void    CADAPI CadXrefPutAngle  (VHANDLE hEnt, double Angle);


	/******************************************************************************
	* IMAGE
	*******************************************************************************/
	VHANDLE  CADAPI CadAddImage       (VDWG hDwg, LPCTSTR szFileName, double X, double Y, double Z, double Scal);
	VHANDLE  CADAPI CadAddImagePlace  (VDWG hDwg, int Id, int Width, int Height, double X, double Y, double Z, double Scal);
	void     CADAPI CadImageGetFile   (VHANDLE hEnt, TCHAR* szFileName);
	void     CADAPI CadImagePutFile   (VHANDLE hEnt, LPCTSTR szFileName);
	double   CADAPI CadImageGetX      (VHANDLE hEnt);
	void     CADAPI CadImagePutX      (VHANDLE hEnt, double X);
	double   CADAPI CadImageGetY      (VHANDLE hEnt);
	void     CADAPI CadImagePutY      (VHANDLE hEnt, double Y);
	double   CADAPI CadImageGetZ      (VHANDLE hEnt);
	void     CADAPI CadImagePutZ      (VHANDLE hEnt, double Z);
	void     CADAPI CadImageGetPoint  (VHANDLE hEnt, double* pX, double* pY, double* pZ);
	void     CADAPI CadImagePutPoint  (VHANDLE hEnt, double X, double Y, double Z);
	double   CADAPI CadImageGetScale  (VHANDLE hEnt);
	void     CADAPI CadImagePutScale  (VHANDLE hEnt, double Scal);
	double   CADAPI CadImageGetScaleX (VHANDLE hEnt);
	void     CADAPI CadImagePutScaleX (VHANDLE hEnt, double Sx);
	double   CADAPI CadImageGetScaleY (VHANDLE hEnt);
	void     CADAPI CadImagePutScaleY (VHANDLE hEnt, double Sy);
	void     CADAPI CadImagePutSize   (VHANDLE hEnt, int Width, int Height);
	BOOL     CADAPI CadImageGetTransparent (VHANDLE hEnt);
	void     CADAPI CadImagePutTransparent (VHANDLE hEnt, BOOL bTransp);
	COLORREF CADAPI CadImageGetTColor      (VHANDLE hEnt);
	void     CADAPI CadImagePutTColor      (VHANDLE hEnt, COLORREF ColorRGB);


	/******************************************************************************
	* HATCH
	*******************************************************************************/
	BOOL    CADAPI CadAddHatchPoint   (VDWG hDwg, double X, double Y);
	BOOL    CADAPI CadAddHatchPath    (VDWG hDwg, VHANDLE hEnt);
	VHANDLE CADAPI CadAddHatch        (VDWG hDwg, LPCTSTR szFileName, LPCTSTR szPatName, double Scal, double Angle);
	UINT    CADAPI CadEngrave         (VDWG hDwg, BOOL bSelected, LPCTSTR szBlockName, double Step, double Angle);
	void    CADAPI CadHatchPutPattern (VHANDLE hEnt, LPCTSTR szFileName, LPCTSTR szPatName);
	void    CADAPI CadHatchGetName    (VHANDLE hEnt, TCHAR* szName);
	UINT    CADAPI CadHatchGetPattern (VHANDLE hEnt, TCHAR* szPattern);
	void    CADAPI CadHatchPutScale   (VHANDLE hEnt, double Scal);
	double  CADAPI CadHatchGetScale   (VHANDLE hEnt);
	void    CADAPI CadHatchPutAngle   (VHANDLE hEnt, double Angle);
	double  CADAPI CadHatchGetAngle   (VHANDLE hEnt);
	double  CADAPI CadHatchGetSize    (VHANDLE hEnt);


	/******************************************************************************
	* DIMENSION
	*******************************************************************************/
	BOOL    CADAPI CadAddDimPoint   (UINT Index, double X, double Y, double Z);
	VHANDLE CADAPI CadAddDim        (VDWG hDwg, int DimType);
	IDOBJ   CADAPI CadDimGetStyleID (VHANDLE hEnt);
	void    CADAPI CadDimPutStyleID (VHANDLE hEnt, IDOBJ Id);
	void    CADAPI CadDimPutText    (VHANDLE hEnt, LPCTSTR szText);
	void    CADAPI CadDimGetText    (VHANDLE hEnt, TCHAR* szText);
	void    CADAPI CadDimGetPoint   (VHANDLE hEnt, int Index, double* pX, double* pY, double* pZ);
	void    CADAPI CadDimPutPoint   (VHANDLE hEnt, int Index, double X, double Y, double Z);
	int     CADAPI CadDimGetType    (VHANDLE hEnt);
	double  CADAPI CadDimGetValue   (VHANDLE hEnt);


	/******************************************************************************
	* LEADER
	*******************************************************************************/
	VHANDLE CADAPI CadAddLeader        (VDWG hDwg, LPCTSTR szText);
	UINT    CADAPI CadLeaderGetNumVers (VHANDLE hEnt);
	void    CADAPI CadLeaderPutNumVers (VHANDLE hEnt, UINT nVers);
	void    CADAPI CadLeaderGetVer     (VHANDLE hEnt, UINT iVer, double* pX, double* pY, double* pZ);
	void    CADAPI CadLeaderPutVer     (VHANDLE hEnt, UINT iVer, double X, double Y, double Z);
	BOOL    CADAPI CadLeaderGetSpline  (VHANDLE hEnt);
	void    CADAPI CadLeaderPutSpline  (VHANDLE hEnt, BOOL bSpline);
	UINT    CADAPI CadLeaderGetTextLen (VHANDLE hEnt);
	void    CADAPI CadLeaderGetText    (VHANDLE hEnt, TCHAR* szText, UINT MaxChars);
	void    CADAPI CadLeaderPutText    (VHANDLE hEnt, LPCTSTR szText);
	double  CADAPI CadLeaderGetTextH   (VHANDLE hEnt);
	void    CADAPI CadLeaderPutTextH   (VHANDLE hEnt, double Height);
	double  CADAPI CadLeaderGetArrSize (VHANDLE hEnt);
	void    CADAPI CadLeaderPutArrSize (VHANDLE hEnt, double Size);
	IDOBJ   CADAPI CadLeaderGetTextStyleID (VHANDLE hEnt);
	void    CADAPI CadLeaderPutTextStyleID (VHANDLE hEnt, IDOBJ Id);


	/******************************************************************************
	* 3DFACE
	*******************************************************************************/
	VHANDLE CADAPI CadAddFace        (VDWG hDwg);
	UINT    CADAPI CadFaceGetNumVers (VHANDLE hEnt);
	void    CADAPI CadFaceGetVer     (VHANDLE hEnt, UINT iVer, double* pX, double* pY, double* pZ);
	void    CADAPI CadFacePutVer     (VHANDLE hEnt, UINT iVer, double X, double Y, double Z);
	BOOL    CADAPI CadFaceGetEdge    (VHANDLE hEnt, UINT iEdge);
	void    CADAPI CadFacePutEdge    (VHANDLE hEnt, UINT iEdge, BOOL bVisible);



	/******************************************************************************
	* VIEWPORT
	*******************************************************************************/
	VHANDLE CADAPI CadAddVport    (VDWG hDwg, double X, double Y, double W, double H);



	/******************************************************************************
	* CUSTOM ENTITY
	*******************************************************************************/
	VHANDLE CADAPI CadAddCustom      (VDWG hDwg, int CustType, void* pData, int nBytes);
	void    CADAPI CadCustomPutOwner (VHANDLE hEnt, void* pObject);
	DWORD   CADAPI CadCustomGetOwner (VHANDLE hEnt);
	int     CADAPI CadCustomGetType  (VHANDLE hEnt);
	void    CADAPI CadCustomPutData  (VHANDLE hEnt, void* pData, int nBytes);
	void    CADAPI CadCustomGetData  (VHANDLE hEnt, void* pData);
	int     CADAPI CadCustomGetSize  (VHANDLE hEnt);
	VHANDLE CADAPI CadCustomGetDataPtr (VHANDLE hEnt);

	void  CADAPI CadDrawSet          (int Mode, int Value);
	HDC   CADAPI CadDrawGetDC        ();
	void  CADAPI CadDrawAddVertex    (double X, double Y, double Z);
	int   CADAPI CadDrawGenArc       (double Xcen, double Ycen, double Zcen, double Radius, double AngStart, double AngArc, int nVers);
	int   CADAPI CadDrawGenCircle    (double X, double Y, double Z, double Radius, int nVers);
	int   CADAPI CadDrawGenChar      (double X, double Y, double Z, double Height, double Angle, double ScaleW, UINT UCode, LPCTSTR szFont, int nVers);
	void  CADAPI CadDrawPolyline     ();
	void  CADAPI CadDrawPolygon      ();
	void  CADAPI CadDrawPolyPolygon  (int* PlineSize, int nPline);
	void  CADAPI CadDrawLine         (double X1, double Y1, double Z1, double X2, double Y2, double Z2);
	void  CADAPI CadDrawPoint        (double X, double Y, double Z, int PtMode, double PtSize);
	void  CADAPI CadDrawText         (VDWG hDwg, LPCTSTR szText, double X, double Y, double Z);
	void  CADAPI CadDrawBlock        (VDWG hDwg, VHANDLE hBlock, double X, double Y, double Z, double ScaleX, double ScaleY, double ScaleZ, double RotAngle);
	void  CADAPI CadDrawObject       (double Xcen, double Ycen, double Zcen, double W, double H, F_DISPOWNERDRAW fnDraw, void* ptr);

	BOOL  CADAPI CadAddCustProp      (int IdProp, LPCTSTR szName, LPCTSTR szValue, int ValType);
	BOOL  CADAPI CadSetCustProp      (int IdProp, LPCTSTR szValue);
	BOOL  CADAPI CadSetCustPropMode  (int IdProp, BOOL bReadOnly);

	/******************************************************************************
	* CUSTOM COMMAND
	*******************************************************************************/
	BOOL    CADAPI CadAddCommand       (VDWG hDwg, int Id, LPCTSTR szCmdName, LPCTSTR szAlias, HCURSOR hCurs, F_CCMD pFunc1, F_CDRAG pFunc2); 
	void    CADAPI CadCmdPutData       (VDWG hDwg, void* pData, int nBytes);
	void    CADAPI CadCmdGetData       (VDWG hDwg, void* pData);
	int     CADAPI CadCmdGetSize       (VDWG hDwg);
	void    CADAPI CadCmdPrompt        (VDWG hDwg, LPCTSTR szText, LPCTSTR szDefaultVal); 
	void    CADAPI CadCmdPromptAdd     (VDWG hDwg, LPCTSTR szValue); 
	int     CADAPI CadCmdUserSelect    (VDWG hDwg);
	VHANDLE CADAPI CadCmdUserGetEntity (VDWG hDwg);
	int     CADAPI CadCmdUserInput     (VDWG hDwg);
	void    CADAPI CadCmdGetInputPoint (VDWG hDwg, double* pX, double* pY, double* pZ);
	void    CADAPI CadCmdGetInputStr   (VDWG hDwg, TCHAR* szText);
	BOOL    CADAPI CadCmdStrToPoint    (VDWG hDwg, LPCTSTR szValue, double* pX, double* pY, double* pZ);
	void    CADAPI CadCmdSetBasePoint  (VDWG hDwg, double X, double Y, double Z);
	BOOL    CADAPI CadCmdAddPoint      (VDWG hDwg, double X, double Y, double Z);
	BOOL    CADAPI CadCmdGetPoint      (VDWG hDwg, int iPoint, double* pX, double* pY, double* pZ);
	int     CADAPI CadCmdCountPoints   (VDWG hDwg);


	/********************************************************************
	*
	*  SELECTION SET
	*
	*********************************************************************/
	void    CADAPI CadSelClear        (VDWG hDwg);
	void    CADAPI CadSelectEntity    (VDWG hDwg, VHANDLE hEnt, BOOL bSelect);
	UINT    CADAPI CadSelectByLayer   (VDWG hDwg, BOOL bSelect);
	UINT    CADAPI CadSelectByPage    (VDWG hDwg, BOOL bSelect);
	UINT    CADAPI CadSelectByPolyline(VDWG hDwg, VHANDLE hEnt, BOOL bSelect);
	UINT    CADAPI CadSelectByPolygon (VDWG hDwg, VHANDLE hEnt, BOOL bCross, BOOL bSelect);
	UINT    CADAPI CadSelectByDist    (VDWG hDwg, double X, double Y, double Z, double Dist, BOOL bCross, BOOL bSelect);
	UINT    CADAPI CadSelCount        (VDWG hDwg);
	VHANDLE CADAPI CadSelGetFirstPtr  (VDWG hDwg);
	VHANDLE CADAPI CadSelGetNextPtr   (VDWG hDwg, VHANDLE hPtr);
	void    CADAPI CadSelErase        (VDWG hDwg);
	void    CADAPI CadSelCopy         (VDWG hDwg);
	void    CADAPI CadSelMove         (VDWG hDwg, double dx, double dy, double dz);
	void    CADAPI CadSelScale        (VDWG hDwg, double x0, double y0, double z0, double Scal);
	void    CADAPI CadSelRotate       (VDWG hDwg, double x0, double y0, double z0, double Angle);
	void    CADAPI CadSelMirror       (VDWG hDwg, double x0, double y0, double z0, double x1, double y1, double z1);
	void    CADAPI CadSelExplode      (VDWG hDwg);
	VHANDLE CADAPI CadSelJoin         (VDWG hDwg, double Delta);
	void    CADAPI CadSelColor        (VDWG hDwg, int Color);

	void    CADAPI CadSelDraw         (VDWG hDwg, HDC hDC, int WinLef, int WinBot, int WinW, int WinH, double ViewLef, double ViewBot, double ViewW, double ViewH, DWORD idPage, COLORREF FillColor, COLORREF BordColor, double LwScale);
	void    CADAPI CadSelMakeGrips    (VDWG hDwg);

	//void    CADAPI CadCbCopy  (VDWG hDwg, HWND hWnd); 
	//void    CADAPI CadCbCut   (VDWG hDwg, HWND hWnd); 
	BOOL    CADAPI CadCbPaste (VDWG hDwg, HWND hWnd, double dx, double dy, double dz);

	DWORD CADAPI CadCountEntities (VDWG hDwg);



	/******************************************************************************
	* VIEWPOINT
	* This functions make projection from 3D model coordinates to 2D display
	* It changes appearance of model in a window
	* Standard viewpoint positions can be set by CadExecute() and 
	* CAD_CMD_VIEW_... commands
	*******************************************************************************/
	// Set isometric projection by XYZ of view (camera) point
	// Viewpoint for plan view is 0,0,1
	void   CADAPI CadViewPutPoint    (VDWG hDwg, HWND hWin, double X, double Y, double Z);
	void   CADAPI CadViewGetPoint    (VDWG hDwg, HWND hWin, double* pX, double* pY, double* pZ);
	// Get coordinates of current view point, model units
	double CADAPI CadViewGetPointX   (VDWG hDwg);
	double CADAPI CadViewGetPointY   (VDWG hDwg);
	double CADAPI CadViewGetPointZ   (VDWG hDwg);
	// Set isometric projection by horizontal and vertical view angles (radians)
	// The angles for plan view are 0, pi/2 
	void   CADAPI CadViewPutAngles   (VDWG hDwg,  HWND hWin, double AngHor, double AngVer);
	// Get angles of current viewpoint, radians
	double CADAPI CadViewGetAngleHor (VDWG hDwg);
	double CADAPI CadViewGetAngleVer (VDWG hDwg);
	// zoom rect
	void   CADAPI CadViewRect        (VDWG hDwg, HWND hWin, double Xmin, double Ymin, double Xmax, double Ymax);
	// scale view in/out
	void   CADAPI CadViewScale       (VDWG hDwg, HWND hWin, double Scal, int Xcen, int Ycen);


	/******************************************************************************
	* COORDINATES CONVERTIONS
	* between model space, display projection, window
	*******************************************************************************/
	void   CADAPI CadCoordModelToDisp (VDWG hDwg, double Xm, double Ym, double Zm, double* pXd, double* pYd);
	void   CADAPI CadCoordModelToWin  (VDWG hDwg, double Xm, double Ym, double Zm, long* pXw, long* pYw);
	void   CADAPI CadCoordDispToModel (VDWG hDwg, double Xd, double Yd, double* pXm, double* pYm, double* pZm);
	void   CADAPI CadCoordDispToWin   (VDWG hDwg, double Xd, double Yd, long* pXw, long* pYw);
	void   CADAPI CadCoordWinToModel  (VDWG hDwg, int Xw, int Yw, double* pXm, double* pYm, double* pZm);
	void   CADAPI CadCoordWinToDisp   (VDWG hDwg, int Xw, int Yw, double* pXd, double* pYd);
	double CADAPI CadDistWinToModel   (VDWG hDwg, int Dwin);
	int    CADAPI CadDistModelToWin   (VDWG hDwg, double Dmod);

	/******************************************************************************
	*   PRINTING
	*******************************************************************************/
	void   CADAPI CadPrintGetRect       (double* pLeft, double* pBottom, double* pRight, double* pTop);
	void   CADAPI CadPrintPutRect       (double Left, double Bottom, double Right, double Top);
	void   CADAPI CadPrintPutScale      (double Scal);
	double CADAPI CadPrintGetScale      ();
	void   CADAPI CadPrintPutScaleLW    (BOOL bScaleLW);
	BOOL   CADAPI CadPrintGetScaleLW    ();
	void   CADAPI CadPrintPutOffset     (double DX, double DY);
	void   CADAPI CadPrintGetOffset     (double* pDX, double* pDY);
	void   CADAPI CadPrintPutColor      (BOOL bColor);
	BOOL   CADAPI CadPrintGetColor      ();
	void   CADAPI CadPrintPutCopies     (UINT Ncopy);
	UINT   CADAPI CadPrintGetCopies     ();
	void   CADAPI CadPrintPutOrient     (UINT Orient);
	UINT   CADAPI CadPrintGetOrient     ();
	void   CADAPI CadPrintPutStampPos   (UINT Pos);
	UINT   CADAPI CadPrintGetStampPos   ();
	void   CADAPI CadPrintPutStampSize  (double TextHeight);
	double CADAPI CadPrintGetStampSize  ();
	void   CADAPI CadPrintPutStampColor (DWORD Color);
	DWORD  CADAPI CadPrintGetStampColor ();
	void   CADAPI CadPrintPutStampText  (LPCTSTR szText1, LPCTSTR szText2);
	void   CADAPI CadPrintGetStampText  (TCHAR* szText1, TCHAR* szText2);
	void   CADAPI CadPrintAtCenter      (BOOL bCenter);

	BOOL   CADAPI CadPrint              (VDWG hDwg, BOOL bPrintStamp, HDC hDC);
	BOOL   CADAPI CadPrintSetup         (HWND hwParent);

	// parameters of default printer
	double CADAPI CadPrintGetPaperW    ();
	double CADAPI CadPrintGetPaperH    ();
	void   CADAPI CadPrintGetPaperSize (double* pWidth, double* pHeight);

	/******************************************************************************
	* PRINT RECT
	*******************************************************************************/
	/*
	int  CADAPI CadPrnRectAdd     (VDWG hDwg, LPCTSTR szName, double Xcen, double Ycen, double W, double H, double Angle);
	BOOL CADAPI CadPrnRectDelete  (VDWG hDwg, int iRect);
	int  CADAPI CadPrnRectCount   (VDWG hDwg);
	BOOL CADAPI CadPrnRectGet     (VDWG hDwg, int iRect, TCHAR* szName, double* pXcen, double* pYcen, double* pW, double* pH, double* pAngle);
	BOOL CADAPI CadPrnRectPut     (VDWG hDwg, int iRect, LPCTSTR szName, double Xcen, double Ycen, double W, double H, double Angle);
	BOOL CADAPI CadPrnRectPrint   (VDWG hDwg, int iRect, HDC hDC);
	void CADAPI CadPrnRectPutShow (VDWG hDwg, BOOL bShow);
	BOOL CADAPI CadPrnRectGetShow (VDWG hDwg);
	*/


	/******************************************************************************
	*   REGENERATE DRAWING
	*******************************************************************************/
	void CADAPI CadRegen  (VDWG hDwg);
	void CADAPI CadUpdate (VDWG hDwg);

	/******************************************************************************
	*   VECAD WINDOW
	*******************************************************************************/
	HWND CADAPI CadWndCreate   (VDWG hDwg, HWND hWndParent, int CadStyle, int X, int Y, int W, int H);
	BOOL CADAPI CadWndResize   (HWND hWin, int X, int Y, int W, int H);
	BOOL CADAPI CadWndRedraw   (HWND hWin);
	HWND CADAPI CadWndSetFocus (HWND hWin);


	/******************************************************************************
	* ACCELERATOR KEYS
	* Links key that comes to VeCAD by the CadWinKeyUp() function
	* with any CAD_CMD_... command
	* Command - identifier of a command, one of the CAD_CMD_... constants
	* VirtKey - virtual key code, Windows VK_... constant or ASCII character
	* Flags - defines if <Ctrl> or <Shift> key is pressed
	*         can be 0 or combination of CAD_KEY_CTRL and CAD_KEY_SHIFT
	*
	* Example of usage:
	* CadAccelSetKey( CAD_CMD_ZOOM_EXT,  'E', CAD_KEY_CTRL );  // Ctrl+E
	* CadAccelSetKey( CAD_CMD_ZOOM_IN,   VK_ADD, 0 );  // "Plus" key
	* CadAccelSetKey( CAD_CMD_SNAP_GRID, VK_F9, 0 );   // F9
	*******************************************************************************/
	void CADAPI CadAccelSetKey (int Command, int VirtKey, int Flags);
	// set default assignment for accelerator keys
	void CADAPI CadAccelSetDefault ();


	/******************************************************************************
	*
	*  VeCAD controls
	*
	*******************************************************************************/
	// Command window (disabled if hw==0)
	HWND CADAPI CadCWCreate  (HWND hwParent, int Left, int Top, int Width, int Height);
	void CADAPI CadCWDelete  ();
	BOOL CADAPI CadCWResize  (int Left, int Top, int Width, int Height);
	void CADAPI CadCWPutText (VDWG hDwg, LPCTSTR szText);

	// Magnifier
	void CADAPI CadMagPutSize  (int Size);
	int  CADAPI CadMagGetSize  ();
	void CADAPI CadMagPutScale (int Scal);
	int  CADAPI CadMagGetScale ();
	void CADAPI CadMagPutPos   (int Pos);
	int  CADAPI CadMagGetPos   ();
	void CADAPI CadMagPutShow  (BOOL bShow);
	BOOL CADAPI CadMagGetShow  ();

	// Navigator (Aerial view)
	HWND CADAPI CadNavCreate   (HWND hWndParent, int X, int Y, int W, int H, int Flags);
	void CADAPI CadNavResize   (int X, int Y, int W, int H);
	int  CADAPI CadNavGetParam (int Prm);
	void CADAPI CadNavReturnFocus (BOOL bReturn, HWND hWnd);
	void CADAPI CadNavSetLink  (HWND hVecWnd);


	// comboboxes
	HWND CADAPI CadCboxCreate (int CbType, HWND hwParent, int Left, int Top, int Width, int Height, int Hdown);
	void CADAPI CadCboxSetActive (int CbType, HWND hwCbox);


	/******************************************************************************
	* Group of menu functions.
	* Used to adjust CAD shortcut popup menus
	*******************************************************************************/
	// clear menu
	void CADAPI CadMenuClear (int MenuId);
	// add new item to menu
	void CADAPI CadMenuAdd (int MenuId, LPCTSTR szItemText, int ItemCmd);


	/******************************************************************************
	* RECENT FILES LIST
	* This functions are not linked with any CAD object
	*******************************************************************************/

	// Load recent files list from the file 'szFileName' 
	BOOL CADAPI CadRecentLoad (LPCTSTR szFileName);

	// Save recent files list
	BOOL CADAPI CadRecentSave ();

	// Call dialog "Recent files list" to allow an user 
	// to select the filename from Recent Files List
	// pbShowAtStartup - pointer to variable that keep a state of the checkbox
	//     if NULL then the checkbox will be invisible     
	//     The variable value can be 0 or 1 (1=checked, 0=unchecked)
	// When function exit, the 'bShowAtStartup' variable contains state of
	// the "Show at startup" checkbox (0/1)
	BOOL CADAPI CadRecentDialog (HWND hWin, TCHAR* szOutFileName, int* pbShowAtStartup);

	// Add filename to recent files list
	BOOL CADAPI CadRecentAdd (LPCTSTR szFileName);



	/******************************************************************************
	* UTILITE FUNCTIONS (not linked with any CAD object)
	*******************************************************************************/
	// Call dialog "Open File" to allow an user to select the filename
	BOOL CADAPI CadDialogOpenFile (HWND hwParent, TCHAR* szOutFileName);

	// Call dialog "Save File" to allow an user to select the filename
	BOOL CADAPI CadDialogSaveFile (HWND hwParent, TCHAR* szOutFileName);

	// Call dialog "Tip of the Day"
	// szFileName - name of the file that contains the tips
	// pbShowAtStartup - pointer to variable that keep a state of the checkbox
	//   The variable value can be 0 or 1 (1=checked, 0=unchecked)
	//   When function exit, the 'bShowAtStartup' variable contains state of
	//   the "Show at startup" checkbox (0/1)
	// pTipIndex - pointer to variable that keep index of current tip
	// implemented in "DgTip.cpp"
	void CADAPI CadTipOfTheDay (HWND hwParent, LPCTSTR szFileName, int* pbShowOnStartup, int* pTipIndex);

	// Show Help Info
	void CADAPI CadHelp (HWND hWin, LPCTSTR szTopic);

	// Dialog "Convert Windows TTF to VeCAD Font"
	void CADAPI CadTTF2VCF (HWND hwParent);

	// Dialog "Convert AutoCAD SHX font to VeCAD font"
	void CADAPI CadSHX2VCF (HWND hwParent);

	// Dialog "VeCAD fonts"
	void CADAPI CadFontsList (HWND hwParent);

	// Dialog "Plugins"
	void CADAPI CadPluginsDlg (HWND hwParent);

	// Get error code of last operation
	int  CADAPI CadGetError ();
	void CADAPI CadGetErrorStr (int ErrCode, TCHAR* szStr);

	// Replace VeCAD string (fo localization)
	void CADAPI CadSetString (int IdStr, LPCTSTR szStr);

	// Define plugin for reading image format
	BOOL CADAPI CadPluginImageRead (LPCTSTR szExt, LPCTSTR szLibName, LPCTSTR szFuncName, int Mode);

	// convert AutoCAD file dxf<->dwg
	BOOL CADAPI CadConvertAcadFile (LPCTSTR szInFile, LPCTSTR szOutFile);

	// extract image from drawing's file
	UINT CADAPI CadExtractImage (LPCTSTR szFileName, BYTE* Buffer);
	UINT CADAPI CadExtractImageMem (void* pMem, BYTE* Buffer);

	void CADAPI CadGetVBString (int Val, TCHAR* szStr);

	BOOL CADAPI vuGetWindowSize (HWND hWin, int* pW, int* pH);
	BOOL CADAPI CadGetWindowSize (HWND hWin, int* pW, int* pH);

	// Compresses the source buffer into the destination buffer. 
	int CADAPI vuCompress (BYTE* Dest, UINT DestMaxLen, CBYTE* Source, UINT SourceLen, int Level);

	// Decompresses the source buffer into the destination buffer
	int CADAPI vuExpand (BYTE* Dest, UINT DestMaxLen, CBYTE* Source, UINT SourceLen);

	void CADAPI vuRotatePoint (double* pX, double* pY, double* pZ, double Xcen, double Ycen, double Zcen, double Angle, int Plane);
	void CADAPI vuPolarPoint  (double* pX, double* pY, double* pZ, double Angle, double Dist, int Plane);
	void CADAPI vuScalePoint  (double* pX, double* pY, double* pZ, double Xcen, double Ycen, double Zcen, double ScaleX, double ScaleY, double ScaleZ);
	void CADAPI vuMirrorPoint (double* pX, double* pY, double* pZ, double A1, double B1, int Plane);

	double CADAPI vuGetAngle       (double x1, double y1, double z1, double x2, double y2, double z2, int Plane);
	double CADAPI vuGetDist        (double x1, double y1, double z1, double x2, double y2, double z2, int Plane);
	double CADAPI vuNormalizeAngle (double Angle);
	void   CADAPI vuNumToStr       (double Val, TCHAR* szOutStr, DWORD MaxDec, BOOL bTrimZero, BOOL bRemainPoint);



	// Step
	// 1 - generate 3D relief matrix
	// 2 - generate raw izolines
	// 3 - join izolines to izopolylines
	// 4 - reduce amount of points in the izopolylines
	// 5 - finish
	typedef void (CALLBACK* F_PROGRESS)(VDWG hDwg, int hRPlan, int Step, int Percent);

	VHANDLE CADAPI CadAddRPlan  (VDWG hDwg);
	VHANDLE CADAPI CadGetRPlan  (VDWG hDwg);

	void    CADAPI CadRPlanClear      (VHANDLE hRPlan);
	void    CADAPI CadRPlanSetStart   (VHANDLE hRPlan, double X, double Y, double Dist, double DirAngle);
	BOOL    CADAPI CadRPlanAddCurve   (VHANDLE hRPlan, double Dist, double RotAngle, int Turn, double Rad, double Len1, double Len2);
	void    CADAPI CadRPlanSetEnd     (VHANDLE hRPlan, double Dist);
	void    CADAPI CadRPlanUpdate     (VHANDLE hRPlan);

	void    CADAPI CadRPlanSetScale (VHANDLE hRPlan, double Scal);

	UINT    CADAPI CadRPlanGetNumRecs     (VHANDLE hRPlan);
	BOOL    CADAPI CadRPlanGetCurveVertex (VHANDLE hRPlan, UINT iRec, double* pX, double* pY);
	BOOL    CADAPI CadRPlanGetCurveCenter (VHANDLE hRPlan, UINT iRec, double* pX, double* pY);
	BOOL    CADAPI CadRPlanGetCurveStart  (VHANDLE hRPlan, UINT iRec, double* pX, double* pY, double* pDirAngle);
	BOOL    CADAPI CadRPlanGetCurveEnd    (VHANDLE hRPlan, UINT iRec, double* pX, double* pY, double* pDirAngle);

	BOOL    CADAPI CadRPlanAddGrPoint    (double Offset, double Z);
	BOOL    CADAPI CadRPlanAddGrSection  (VHANDLE hRPlan, double Dist, double Zcen);

	void    CADAPI CadRPlanGenLevels     (VHANDLE hRPlan, double Precision, double ZStep, double ZStepBold, F_PROGRESS pFunc);

	BOOL    CADAPI CadRPlanGetPoint      (VHANDLE hRPlan, double Dist, double* pX, double* pY, double* pZ, double* pDirAngle);
	BOOL    CADAPI CadRPlanGetGrPoint    (VHANDLE hRPlan, double Dist, double Offset, double* pX, double* pY, double* pZ);
	BOOL    CADAPI CadRPlanGetDist       (VHANDLE hRPlan, double X, double Y, double* pDist, double* pOffset);
	BOOL    CADAPI CadRPlanGetZ          (VHANDLE hRPlan, double X, double Y, double* pZ);

	void    CADAPI CadRPlanPutVisible    (VHANDLE hRPlan, int Mode, BOOL bVisible);
	BOOL    CADAPI CadRPlanGetVisible    (VHANDLE hRPlan, int Mode);
	void    CADAPI CadRPlanPutColor      (VHANDLE hRPlan, int Mode, int Color);
	int     CADAPI CadRPlanGetColor      (VHANDLE hRPlan, int Mode);
	void    CADAPI CadRPlanPutLineweight (VHANDLE hRPlan, int Mode, int lw);
	int     CADAPI CadRPlanGetLineweight (VHANDLE hRPlan, int Mode);

	VHANDLE CADAPI CadAddRProf         (VDWG hDwg);
	VHANDLE CADAPI CadGetRProf         (VDWG hDwg);

	void    CADAPI CadRProfClear         (VHANDLE hRProf);
	void    CADAPI CadRProfAddVer        (VHANDLE hRProf, double Dist, double Y);
	void    CADAPI CadRProfDelVer        (VHANDLE hRProf, int iVer);
	void    CADAPI CadRProfPutVer        (VHANDLE hRProf, int iVer, double Dist, double Y);
	void    CADAPI CadRProfPutCurveLen   (VHANDLE hRProf, int iVer, double Length);
	void    CADAPI CadRProfUpdate        (VHANDLE hRProf);

	UINT    CADAPI CadRProfGetNumVers    (VHANDLE hRProf);
	void    CADAPI CadRProfGetVer        (VHANDLE hRProf, int iVer, double* pDist, double* pY);
	void    CADAPI CadRProfGetCurvePrm   (VHANDLE hRProf, int iVer, double* pRad, double* pBVC, double* pEVC, double* pLen);
	void    CADAPI CadRProfGetY          (VHANDLE hRProf, double Dist, double* pYold, double* pYnew);
	void    CADAPI CadRProfGetInterX     (VHANDLE hRProf, double Y, double* pX, int* pNumX, int MaxNumX); 

	void    CADAPI CadRProfPutScale      (VHANDLE hRProf, double HorScale, double VerScale);
	void    CADAPI CadRProfPutVisible    (VHANDLE hRProf, int Mode, BOOL bVisible);
	BOOL    CADAPI CadRProfGetVisible    (VHANDLE hRProf, int Mode);
	void    CADAPI CadRProfPutColor      (VHANDLE hRProf, int Mode, int Color);
	int     CADAPI CadRProfGetColor      (VHANDLE hRProf, int Mode);
	void    CADAPI CadRProfPutLineweight (VHANDLE hRProf, int Mode, int lw);
	int     CADAPI CadRProfGetLineweight (VHANDLE hRProf, int Mode);

	void    CADAPI CadGetInterPoints     (VDWG hDwg, VHANDLE hEnt1, VHANDLE hEnt2, double* pX, double* pY, int* pNumPt, int MaxNumPt); 




	#ifdef _VECAD_LIB
	  }
	#endif
};

using namespace CadApi;

#endif  // CADAPI_H


