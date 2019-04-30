// SurveyInfoDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "SurveyInfoDlg.h"
#include "time.h"
#include "afxdialogex.h"


// SurveyInfoDlg 대화 상자

IMPLEMENT_DYNAMIC(SurveyInfoDlg, CDialogEx)

SurveyInfoDlg::SurveyInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_SURVEY_INFO, pParent)
	, m_memo(_T(""))
	, m_updatedTime(_T(""))
	, m_workerName(_T(""))
{

}

SurveyInfoDlg::SurveyInfoDlg(SurveyTask::Survey & survey, CWnd * pParent /*=nullptr*/)
	:SurveyInfoDlg(pParent)
{
	m_survey = survey;
}

SurveyInfoDlg::~SurveyInfoDlg()
{
	destroyImageContainers();
}

void SurveyInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MEMO, m_memo);
	DDX_Text(pDX, IDC_STRING_UPDATED_TIME, m_updatedTime);
	DDX_Text(pDX, IDC_STRING_WORKER_NAME, m_workerName);
}

void SurveyInfoDlg::destroyImageContainers()
{
	for (auto& container : m_imageContainers) {
		delete container;
	}

	m_imageContainers.clear();
}


BEGIN_MESSAGE_MAP(SurveyInfoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// SurveyInfoDlg 메시지 처리기


void SurveyInfoDlg::OnPaint()
{
	CPaintDC dc(this);

	auto& imagesPaths = m_survey.GetImagesPaths();
	const int imagesCount = imagesPaths.size();
	for (int i = 0; i < imagesCount; ++i) {
		CRect rect;
		
		m_imageContainers[i]->GetClientRect(&rect);

		CImage image;
		image.Load(imagesPaths[i]);

		CBitmap* pBitmap;
		pBitmap = CBitmap::FromHandle(image);
		m_imageContainers[i]->SetBitmap(*pBitmap);
		HBITMAP result = m_imageContainers[i]->SetBitmap(image);
		

		// Now it would be supposed to fit the control:
		CDC *pDC = m_imageContainers[i]->GetDC();
		CDC m_DC;

		m_DC.CreateCompatibleDC(pDC);
		m_DC.SelectObject(pBitmap);
		pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &m_DC, 0, 0, image.GetWidth(), image.GetHeight(), SRCCOPY);
		
		ReleaseDC(pDC);
		ReleaseDC(&m_DC);
	}
}

BOOL SurveyInfoDlg::OnInitDialog()
{
	m_updatedTime = TimeUtil::ConvertTime2StrFormatted(m_survey.GetUpdatedTime());

	auto worker = m_survey.GetWorker();
	m_workerName = worker.name;

	m_memo = m_survey.GetMemo();
	UpdateData(FALSE);

	const int CONTAINER_WIDTH = 300;
	const int CONTAINER_HEIGHT = 100;

	destroyImageContainers();

	CRect labelRect;
	CStatic* pLabel = (CStatic*)GetDlgItem(IDC_LABEL_PICTURES);
	pLabel->GetWindowRect(&labelRect);
	ScreenToClient(&labelRect);
	const int baseTop = labelRect.bottom;
	const int baseLeft = labelRect.left;

	auto& imagesPaths = m_survey.GetImagesPaths();
	const int imagesCount = imagesPaths.size();

	for (int i = 0; i < imagesCount; ++i) {
		/*double width = (double)m_images[i].GetWidth();
		double height = (double)m_images[i].GetHeight();*/
		
		int l = baseLeft;
		int t = baseTop + (CONTAINER_HEIGHT + 5)*i;
		CRect containerRect(l, t, l+CONTAINER_WIDTH, t+CONTAINER_HEIGHT);

		m_imageContainers.push_back(new CStatic);
		BOOL result = m_imageContainers[i]->Create(
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | SS_BITMAP | SS_CENTERIMAGE,
			containerRect,
			this, i);
		assert(result);

		m_imageContainers[i]->ShowWindow(SW_SHOW);
	}

	return 0;
}

int SurveyInfoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	return 0;
}
