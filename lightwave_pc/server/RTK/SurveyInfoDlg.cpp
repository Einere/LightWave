// SurveyInfoDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "SurveyInfoDlg.h"
#include "time.h"
#include "SurveyImageViewDlg.h"
#include "path.h"
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
	DDX_Control(pDX, IDC_LIST_IMAGES, m_listImages);
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
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_IMAGES, &SurveyInfoDlg::OnLvnItemActivateListImages)
END_MESSAGE_MAP()


// SurveyInfoDlg 메시지 처리기

BOOL SurveyInfoDlg::OnInitDialog()
{
	m_updatedTime = m_survey.HasBeenSurveyed() ? TimeUtil::ConvertTime2StrFormatted(m_survey.GetUpdatedTime()) : "";

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


	m_images = m_survey.GetImages();
	const int imagesCount = m_images.size();

	CRect listRect;
	m_listImages.GetWindowRect(&listRect);
	const int width = listRect.Width();

	m_listImages.InsertColumn(1, _T("파일 이름"), LVCFMT_LEFT, (int)(width*0.3), 2);
	m_listImages.InsertColumn(2, _T("위도"), LVCFMT_LEFT, (int)(width*0.23), 2);
	m_listImages.InsertColumn(3, _T("경도"), LVCFMT_LEFT, (int)(width*0.23), 2);
	m_listImages.InsertColumn(4, _T("방위"), LVCFMT_LEFT, (int)(width*0.23), 2);

	for (int i = 0; i < imagesCount; ++i) {
		const int itemIndex = m_listImages.GetItemCount();
		int result = m_listImages.InsertItem(itemIndex, Path::GetFileName(m_images[i].path));

		CString latInStr, lonInStr, aziInStr;
		latInStr.Format("%f", m_images[i].geometry.latitude);
		lonInStr.Format("%f", m_images[i].geometry.longitude);
		aziInStr.Format("%f", m_images[i].geometry.azimuth);
		m_listImages.SetItemText(itemIndex, 1, latInStr);
		m_listImages.SetItemText(itemIndex, 2, lonInStr);
		m_listImages.SetItemText(itemIndex, 3, aziInStr);
	}

	return 0;
}

BEGIN_MESSAGE_MAP(ImageContainer, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()


ImageContainer::ImageContainer()
{
}

ImageContainer::ImageContainer(CString imagePath)
{
	m_imagePath = imagePath;
}

void ImageContainer::SetImage(CString imagePath)
{
	m_imagePath = imagePath;
}

void ImageContainer::OnLButtonDown(UINT nFlags, CPoint point)
{
	SurveyImageViewDlg dlg(m_imagePath);
	dlg.DoModal();
	CStatic::OnLButtonDown(nFlags, point);
}

void ImageContainer::OnPaint()
{
	CPaintDC dc(this);
}

void SurveyInfoDlg::OnLvnItemActivateListImages(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	SurveyImageViewDlg dlg(m_images[pNMIA->iItem].path);
	dlg.DoModal();

	*pResult = 0;
}
