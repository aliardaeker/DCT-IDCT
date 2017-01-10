// kingimageView.h : interface of the CKingimageView class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_KINGIMAGEVIEW_H__358E35BF_08DB_11D3_AA68_00E0CCDDAE2D__INCLUDED_)
#define AFX_KINGIMAGEVIEW_H__358E35BF_08DB_11D3_AA68_00E0CCDDAE2D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <vector>
using namespace std;

class CKingimageView : public CScrollView
{
protected: // create from serialization only
	CKingimageView();
	DECLARE_DYNCREATE(CKingimageView)

// Attributes
public:
	CKingimageDoc* GetDocument();
	vector <vector <int>> convolution(vector <vector <int>> img, vector <vector <int>> mask, bool logFlag);
	int convolve(vector <vector <int>> &img, int h, int w, vector <vector <int>> &mask, bool logFlag);
	void printFile(vector <vector <double>> vector2D);
	void printFile(vector <vector <int>> vector2D);
	void printFile(vector <int> f);
	void printMessage(double m);
	void printMessage(int m);
	void ROI();
	void Point8DCT();
	void Point16DCT();
	void Compression();
	void Compression2();
	void convertRGBtoHSI();
	int hue(int r, int g, int b);
	int saturation(int r, int g, int b);
	int intensity(int r, int g, int b);
	vector <int> DCT1d(vector <int> f);
	vector < vector <int>> DCT2d(vector <vector <int>> img, int h, int w);
	vector <vector <int>> IDCT2d(vector <vector <int>> f, int h, int w);
	vector <vector <int>> DCcomponents(vector <vector <int>> img, int h, int w);
	vector <vector <int>> DCcomponents9(vector <vector <int>> img, int h, int w);
//	void Processing();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKingimageView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CKingimageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CKingimageView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnProcess();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

};

#ifndef _DEBUG  // debug version in kingimageView.cpp
inline CKingimageDoc* CKingimageView::GetDocument()
   { return (CKingimageDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KINGIMAGEVIEW_H__358E35BF_08DB_11D3_AA68_00E0CCDDAE2D__INCLUDED_)
