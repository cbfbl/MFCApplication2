#pragma once

#include "GraphicModel.h"
#include <vector>
using std::vector;

// ObjectSelectionDialog dialog

class ObjectSelectionDialog : public CDialog
{
	DECLARE_DYNAMIC(ObjectSelectionDialog)

public:
	ObjectSelectionDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ObjectSelectionDialog();
    void setIndex(int newObjIdx);
    void setMaxIndex(int newMaxObjIdx);
    void setModels(vector<GraphicModel>& models);
    int getIndex() const;

private:
    int objIdx;
    int maxObjIdx;
    CComboBox comboObjIdx;
    vector<GraphicModel> models;
    
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
