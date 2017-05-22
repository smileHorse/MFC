#include "stdafx.h"
#include "GridDemo.h"
#include "MyToolTipCtrl.h"
#include "SettingsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSettingDialog::CSettingDialog( CWnd* parent /*= NULL*/ )
	: CDialog(CSettingDialog::IDD, parent)
{
	m_cx = 0;
	m_cy = 0;
}

void CSettingDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SPINVERT, m_wndSpinVert);
	DDX_Control(pDX, IDC_SPINHORZ, m_wndSpinHorz);
	DDX_Control(pDX, IDC_SLIDER, m_wndSlider);
	DDX_Text(pDX, IDC_EDITHORZ, m_cx);
	DDX_Text(pDX, IDC_EDITVERT, m_cy);
}

BEGIN_MESSAGE_MAP(CSettingDialog, CDialog)
	//{{AFX_MSG_MAP(CSettingsDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSettingDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Initialize the slider control
	m_wndSlider.SetRange(0, 8);
	m_wndSlider.SetPos(m_nWeight);

	// Initialize the spin button controls
	m_wndSpinHorz.SetRange(2, 64);
	m_wndSpinVert.SetRange(2, 64);

	// Create and initialize a tooltip control
	m_ctlTT.Create(this);
	m_ctlTT.AddWindowTool(GetDlgItem(IDC_SLIDER), MAKEINTRESOURCE(IDS_SLIDER));
	m_ctlTT.AddWindowTool(GetDlgItem(IDC_EDITHORZ), MAKEINTRESOURCE(IDS_EDITHORZ));
	m_ctlTT.AddWindowTool(GetDlgItem(IDC_EDITVERT), MAKEINTRESOURCE(IDS_EDITVERT));

	return TRUE;
}

void CSettingDialog::OnOk()
{
	// Read the slider control's thumb position before dismissing the dialog
	m_nWeight = m_wndSlider.GetPos();
	CDialog::OnOK();
}
