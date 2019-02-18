#pragma once
#define READ_FRAME_TIMER		9
#define READ_FRAME_PERIOD		1000

#define RELEASE_TIMER				10
#define RELEASE_PERIOD				1000

#define READ_FRAME_TIMER_EN		11
#define READ_FRAME_PERIOD_EN		100

#define RELEASE_TIMER_EN		12
#define RELEASE_PERIOD_EN			100

#define MAX_LOG_LEN	1024*50

// datatype
#define MAX_BUF_LEN		0xFFFF

// GPSDataConstants
#define MAX_NUM_CHANNEL	12 //per constellation
#define MAX_GPS_PRN		32
#define NUM_FREQUENCY	2

// UserDefine 
#define UDP_MODE			0
#define SERIAL_MODE			1
#define TCP_MODE			2

#define MAX_BUF_SIZE		0xFFF

// Length
#define MAX_REALBUFFPATH 256

// Timer ID
#define __TID_TIMERSTART__								0x0F00
#define __TID_SATELLITESTATECHECK_FOR_STATEBAR__		__TID_TIMERSTART__ + 1
#define __TID_LED_ONOFF__								__TID_TIMERSTART__ + 2
#define __TID_GPSMAINPANELSTATEUPDATE__					__TID_TIMERSTART__ + 3

#define __LOG_DATA_SAVE_FILENAME__						"Log.txt"

// ���
#define	_PI		3.1415926

namespace DataType
{
	// ��������
	enum ESatelliteType
	{
		EST_GPS,
		EST_GLONASS
	};
};

// =====================================================
// CCadManager�� ����� �ݹ� �Լ���
typedef void (*FnMouseClickCallback)(double fX, double fY);		// Cadȭ�鿡 ���콺 Ŭ���� ȣ��� �ݹ��Լ�

