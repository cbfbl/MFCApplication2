#pragma once


// MouseSensitivityDialog dialog

class MouseSensitivityDialog : public CDialog
{
	DECLARE_DYNAMIC(MouseSensitivityDialog)

public:
	MouseSensitivityDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MouseSensitivityDialog();
    int MouseSensitivityDialog::getSensitivity() const;
    void MouseSensitivityDialog::setSensitivity(int sensitivity);


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MouseSensitivityDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
    public:
        CSliderCtrl sliderMouseSensitivity;
        CStatic textMouseSensitivity;
        afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    private:
        int sensitivity;
        void updateStaticText();

    public:
        virtual BOOL OnInitDialog();
};
