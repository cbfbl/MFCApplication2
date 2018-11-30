#pragma once


// ObjectSelectionDialog dialog

class ObjectSelectionDialog : public CDialog
{
	DECLARE_DYNAMIC(ObjectSelectionDialog)

public:
	ObjectSelectionDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ObjectSelectionDialog();
    void setIndex(int newObjIdx);
    void setMaxIndex(int newMaxObjIdx);
    int getIndex() const;

private:
    int objIdx;
    int maxObjIdx;
    CComboBox comboObjIdx;

    
public:
    virtual BOOL OnInitDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ObjectSelectionDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
    public:
        afx_msg void OnCbnSelchangeCombo1();
};
