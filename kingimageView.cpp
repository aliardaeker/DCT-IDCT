// kingimageView.cpp : implementation of the CKingimageView class
//

#include "stdafx.h"
#include "kingimage.h"
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip> 
#include <fstream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <algorithm>
using namespace std;

#define PI 3.14159265358979323846

#include "kingimageDoc.h"
#include "kingimageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKingimageView

IMPLEMENT_DYNCREATE(CKingimageView, CScrollView)

BEGIN_MESSAGE_MAP(CKingimageView, CScrollView)
	//{{AFX_MSG_MAP(CKingimageView)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_PROCESS, OnProcess)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_PROCESS_COMPRESSION, &CKingimageView::Compression)
	ON_COMMAND(ID_PROCESS_COMPRESSION2, &CKingimageView::Compression2)
	ON_COMMAND(ID_PROCESS_ROI, &CKingimageView::ROI)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKingimageView construction/destruction

CKingimageView::CKingimageView()
{
	// TODO: add construction code here

}

CKingimageView::~CKingimageView()
{
}

BOOL CKingimageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView drawing

void CKingimageView::OnDraw(CDC* pDC)
{
	CKingimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	pDC->SetStretchBltMode(COLORONCOLOR);
//	int x,y,bytes;
	if (pDoc->imagetype==PCX)
		(pDoc->_pcx)->draw(pDC);
	if (pDoc->imagetype==BMP)
		(pDoc->_bmp)->draw(pDC);
	if (pDoc->imagetype==GIF)
		(pDoc->_gif)->draw(pDC);
	if (pDoc->imagetype==JPG)
		(pDoc->_jpg)->draw(pDC);
/*	if (pDoc->imagetype==BMP)
	{
	
	x=((KINGBMP*)(pDoc->_ppicture))->bmpinfo.bmiHeader.biWidth;
	y=((KINGBMP*)(pDoc->_ppicture))->bmpinfo.bmiHeader.biHeight;
	bytes=(pDoc->_ppicture)->needbyte;
	int place=0;
	for (int j=0;j<y;j++)
		for (int i=0;i<x;i++){
//			int color= (pDoc->_bmp)->point[place++] ;
			pDC->SetPixel(i,j,RGB( (pDoc->_picture)->pixel[place+2], (pDoc->_picture)->pixel[place+1] ,(pDoc->_picture)->pixel[place]));
			place+=3;
		}

  /*	if ( (pDoc->_bmp)->bitsperpixel!=24 ){
		CPalette *palette=new CPalette();
		LOGPALETTE palet;
		palet.palVersion=0x300;
		palet.palNumEntries=(pDoc->_bmp)->usedcolor;
		for (int i=0;i<palet.palNumEntries;i++){
			palet.palPalEntry[i].peRed=( (pDoc->_bmp) -> bmpinfo) .bmiColors[i].rgbRed;
			palet.palPalEntry[i].peBlue=( (pDoc->_bmp) -> bmpinfo) .bmiColors[i].rgbBlue;
			palet.palPalEntry[i].peGreen=( (pDoc->_bmp) -> bmpinfo) .bmiColors[i].rgbGreen;
			palet.palPalEntry[i].peFlags=0;//( (pDoc->_bmp) -> bmpinfo) .bmiColors[0].rgbRed;
		}
		BOOL re=palette->CreatePalette(&palet);
		CPalette *pp;
		pp=pDC->SelectPalette(palette,TRUE);
	}
*/
//	::SetDIBitsToDevice(pDC->m_hDC,0,0,x,y,0,0,0,y,(pDoc->_ppicture)->point,&(((KINGBMP*)(pDoc->_ppicture))->bmpinfo),DIB_RGB_COLORS);
	
//	}
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView printing

BOOL CKingimageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKingimageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKingimageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView diagnostics

#ifdef _DEBUG
void CKingimageView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CKingimageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CKingimageDoc* CKingimageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKingimageDoc)));
	return (CKingimageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKingimageView message handlers



void CKingimageView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CSize totalSize=CSize(::GetSystemMetrics(SM_CXSCREEN),
		                  ::GetSystemMetrics(SM_CYSCREEN));
	CSize pageSize=CSize(totalSize.cx/2,totalSize.cy/2);
	CSize lineSize=CSize(totalSize.cx/10,totalSize.cy/10);

	SetScrollSizes(MM_TEXT,totalSize,pageSize,lineSize);
}

void CKingimageView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CScrollView::OnMouseMove(nFlags, point);
}


//******************************************************
//  Image Processing Sample Program for CS555
//  Image origin: lower-left point
//  Image info:
//		int width;
//		int height;
//		int bitsperpixel;
//		int needbyte;
//		int usedcolor;
//		int usedbyte;
//		BYTE *pixel;	//maybe serval point in one BYTE
//		BYTE *point;
//
//  
//******************************************************
void CKingimageView::OnProcess()
{
	// TODO: Add your command handler code here
	CKingimageDoc* pDoc = GetDocument();


	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;

	int Wp = iWidth;
	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		int r = iWidth % 4;
		int p = (4-r)%4;
		Wp = iWidth + p;
	}
	else if (iBitPerPixel == 24)	// RGB image
	{
		int r = (3*iWidth) % 4;
		int p = (4-r)%4;
		Wp = 3*iWidth + p;
	}

	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
			pImg[i*Wp+j] = 255;
		}
	}
	else if(iBitPerPixel == 24)  ////True color 24bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
			pImg[i*Wp+j*3]   = 0;      //B
			// pImg[i*Wp+j*3+1] = 0;      //G
			pImg[i*Wp+j*3+2] = 0;      //R 
		}
	}

	////redraw the screen
	OnDraw(GetDC());
}

void CKingimageView::ROI()
{
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;
	int R, G, B, xValue, yValue, result;
	vector <vector <int>> intensityImage(iHeight, vector <int>(iWidth, 0));
	vector <vector <int>> sobelyValues(iHeight, vector <int>(iWidth, 0));
	vector <vector <int>> sobelxValues(iHeight, vector <int>(iWidth, 0));

	for (int i = 0; i < iHeight; i++)
	{
		for (int j = 0; j < iWidth; j++)
		{
			R = pImg[i * iWidth * 3 + j * 3];
			G = pImg[i * iWidth * 3 + j * 3 + 1];
			B = pImg[i * iWidth * 3 + j * 3 + 2];

			intensityImage.at(i).at(j) = intensity(R, G, B);
		}
	}

	vector <vector <int>> sobelY{ { -1, -2, -1 },
	{ 0, 0, 0 },
	{ 1, 2, 1 } };

	vector <vector <int>> sobelX{ { -1, 0, 1 },
	{ -2, 0, 2 },
	{ -1, 0, 1 } };

	sobelyValues = convolution(intensityImage, sobelY, false);
	sobelxValues = convolution(intensityImage, sobelX, false);

	for (int i = 0; i < iHeight; i++)
	{
		for (int j = 0; j < iWidth; j++)
		{
			xValue = sobelxValues.at(i).at(j) * sobelxValues.at(i).at(j);
			yValue = sobelyValues.at(i).at(j) * sobelyValues.at(i).at(j);
			result = (int) sqrt(xValue + yValue);

			pImg[i * iWidth * 3 + j * 3] = result;
			pImg[i * iWidth * 3 + j * 3 + 1] = result;
			pImg[i * iWidth * 3 + j * 3 + 2] = result;
		}
	}

	OnDraw(GetDC());

	chrono::duration<int, std::milli> timespan(4000);
	this_thread::sleep_for(timespan);

	for (int i = 0; i < iHeight; i++)
	{
		for (int j = 0; j < iWidth; j++)
		{
			if (pImg[i * iWidth * 3 + j * 3] > 100)
			{
				pImg[i * iWidth * 3 + j * 3] = 255;
				pImg[i * iWidth * 3 + j * 3 + 1] = 255;
				pImg[i * iWidth * 3 + j * 3 + 2] = 255;
			}
			else
			{
				pImg[i * iWidth * 3 + j * 3] = 0;
				pImg[i * iWidth * 3 + j * 3 + 1] = 0;
				pImg[i * iWidth * 3 + j * 3 + 2] = 0;
			}
		}
	}

	OnDraw(GetDC());
}

void CKingimageView::Point8DCT()
{
	vector <int> f = {10, 11, 12, 11, 12, 13, 12, 11};
	vector <int> t = DCT1d(f);

	vector <int> f2 = {10, -10, 8, -7, 8, -8, 7, -7};
	vector <int> t2 = DCT1d(f2);

	t.insert(t.end(), t2.begin(), t2.end());
	printFile(t);
}

void CKingimageView::Point16DCT()
{
	vector <int> f = {10, 11, 12, 11, 12, 13, 12, 11, 10, -10, 8, -7, 8, -8, 7, -7};
	vector <int> t = DCT1d(f);
	printFile(t);
}

void CKingimageView::Compression()
{
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;
	int R, G, B;
	vector <vector <int>> intensityImage(iHeight, vector <int>(iWidth, 0));

	for (int i = 0; i < iHeight; i++)
	{
		for (int j = 0; j < iWidth; j++)
		{
			R = pImg[i * iWidth * 3 + j * 3];
			G = pImg[i * iWidth * 3 + j * 3 + 1];
			B = pImg[i * iWidth * 3 + j * 3 + 2];

			intensityImage.at(i).at(j) = intensity(R, G, B);
		}
	}

	vector <vector <int>> F;
	F = DCT2d(intensityImage, iHeight, iWidth);
	//printFile(F);

	vector <vector <int>> D1 = DCcomponents(F, iHeight, iWidth);
	//printFile(D1);

	vector <vector <int>> R1 = IDCT2d(D1, iHeight, iWidth);
	//printFile(R1);

	for (int i = 0; i < iHeight; i++)
	{
		for (int j = 0; j < iWidth; j++)
		{
			pImg[i * iWidth * 3 + j * 3] = R1.at(i).at(j);
			pImg[i * iWidth * 3 + j * 3 + 1] = R1.at(i).at(j);
			pImg[i * iWidth * 3 + j * 3 + 2] = R1.at(i).at(j);
		}
	}
	OnDraw(GetDC());
}

void CKingimageView::Compression2()
{
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;
	int R, G, B;
	vector <vector <int>> intensityImage(iHeight, vector <int>(iWidth, 0));

	for (int i = 0; i < iHeight; i++)
	{
		for (int j = 0; j < iWidth; j++)
		{
			R = pImg[i * iWidth * 3 + j * 3];
			G = pImg[i * iWidth * 3 + j * 3 + 1];
			B = pImg[i * iWidth * 3 + j * 3 + 2];

			intensityImage.at(i).at(j) = intensity(R, G, B);
		}
	}

	vector <vector <int>> F;
	F = DCT2d(intensityImage, iHeight, iWidth);
	//printFile(F);

	vector <vector <int>> D2 = DCcomponents9(F, iHeight, iWidth);
	//printFile(D2);

	vector <vector <int>> R2 = IDCT2d(D2, iHeight, iWidth);
	//printFile(R2);

	for (int i = 0; i < iHeight; i++)
	{
		for (int j = 0; j < iWidth; j++)
		{
			pImg[i * iWidth * 3 + j * 3] = R2.at(i).at(j);
			pImg[i * iWidth * 3 + j * 3 + 1] = R2.at(i).at(j);
			pImg[i * iWidth * 3 + j * 3 + 2] = R2.at(i).at(j);
		}
	}
	OnDraw(GetDC());
}

vector <vector <int>> CKingimageView::IDCT2d(vector <vector <int>> F, int h, int w)
{
	double total = 0.0, a_u, a_v, c1, c2, pixcelValue;
	vector <vector <int>> f(h, vector <int>(w, 0));
	int numberOfRowBlocks = (int) floor(w / 8.0);
	int numberOfColumnBlocks = (int) floor(h / 8.0);
	int x, y;

	for (int i = 0; i < numberOfColumnBlocks; i++)
	{
		for (int j = 0; j < numberOfRowBlocks; j++)
		{
			for (x = 0; x < 8; x++)
			{ 
				for (y = 0; y < 8; y++)
				{
					for (int u = 0; u < 8; u++)
					{
						for (int v = 0; v < 8; v++)
						{
							if (u == 0) a_u = sqrt(1 / 8.0);
							else a_u = sqrt(2 / 8.0);

							if (v == 0) a_v = sqrt(1 / 8.0);
							else a_v = sqrt(2 / 8.0);

							c1 = cos(((2 * x + 1) * u * PI) / (2 * 8));
							c2 = cos(((2 * y + 1) * v * PI) / (2 * 8));

							pixcelValue = F.at(i * 8 + u).at(j * 8 + v);
							total = total + pixcelValue * c1 * c2 * a_u * a_v;
						}
					}

					f.at(i * 8 + x).at(j * 8 + y) = (int) roundl(total);
					total = 0;
				}
			}
		}
	}

	return f;
}

vector <vector <int>> CKingimageView::DCT2d(vector <vector <int>> img, int h, int w)
{
	double total = 0.0, a_u, a_v, c1, c2, pixcelValue;
	vector <vector <int>> F(h, vector <int>(w, 0));
	int numberOfRowBlocks = (int)floor(w / 8.0);
	int numberOfColumnBlocks = (int)floor(h / 8.0);

	for (int i = 0; i < numberOfColumnBlocks; i++)
	{
		for (int j = 0; j < numberOfRowBlocks; j++)
		{
			for (int u = 0; u < 8; u++)
			{
				for (int v = 0; v < 8; v++)
				{
					if (u == 0) a_u = sqrt(1 / 8.0);
					else a_u = sqrt(2 / 8.0);

					if (v == 0) a_v = sqrt(1 / 8.0);
					else a_v = sqrt(2 / 8.0);

					for (int x = 0; x < 8; x++)
					{
						for (int y = 0; y < 8; y++)
						{
							c1 = cos(((2 * x + 1) * u * PI) / (2 * 8));
							c2 = cos(((2 * y + 1) * v * PI) / (2 * 8));

							pixcelValue = img.at(x + i * 8).at(y + j * 8);
							total = total + pixcelValue * c1 * c2;
						}
					}

					total = total * a_u * a_v;
					F.at(u + i * 8).at(v + j * 8) = (int)roundl(total);
					total = 0;
				}
			}
		}
	}

	return F;
}

vector <vector <int>> CKingimageView::DCcomponents9(vector <vector <int>> img, int h, int w)
{
	int RowBlocks = (int) floor(w / 8.0);
	int ColumnBlocks = (int) floor(h / 8.0);
	int value = 0;
	vector <vector <int>> D2(h, vector <int>(w, 0));

	for (int i = 0; i < ColumnBlocks; i++)
	{
		for (int j = 0; j < RowBlocks; j++)
		{
			for (int x = 0; x < 3; x++)
			{
				for (int y = 0; y < 3; y++)
				{
					value = img.at(i * 8 + x).at(j * 8 + y);
					D2.at(i * 8 + x).at(j * 8 + y) = value;
				}
			}
		}
	}

	return D2;
}

vector <vector <int>> CKingimageView::DCcomponents(vector <vector <int>> img, int h, int w)
{
	int RowBlocks = (int) floor(w / 8.0);
	int ColumnBlocks = (int) floor(h / 8.0);
	int value = 0;
	vector <vector <int>> D1(h, vector <int>(w, 0));

	for (int i = 0; i < ColumnBlocks; i++)
	{
		for (int j = 0; j < RowBlocks; j++)
		{
			value = img.at(i * 8).at(j * 8);
			D1.at(i * 8).at(j * 8) = value;
		}
	}

	return D1;
}

void CKingimageView::convertRGBtoHSI()
{
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;
	int R, G, B;

	for (int i = 0; i < iHeight; i++)
	{
		for (int j = 0; j < iWidth; j++)
		{
			R = pImg[i * iWidth * 3 + j * 3];
			G = pImg[i * iWidth * 3 + j * 3 + 1];
			B = pImg[i * iWidth * 3 + j * 3 + 2];

			pImg[i * iWidth * 3 + j * 3] = hue(R, G, B);
			pImg[i * iWidth * 3 + j * 3 + 1] = saturation(R, G, B);
			pImg[i * iWidth * 3 + j * 3 + 2] = intensity(R, G, B);
		}
	}

	OnDraw(GetDC());
}

int CKingimageView::hue(int r, int g, int b)
{
	double teta = acos(((2 * r - g - b) / 2) / sqrt((pow(r - g, 2) + (r - b) * (g - b))));
	teta = teta * 180 / PI;

	if (b <= g) return (int) round(teta);
	else return (360 - (int) round(teta));
}

int CKingimageView::saturation(int r, int g, int b)
{
	int min;
	if (r < g && r < b) min = r;
	else if (g < r && g < b) min = g;
	else if (b < r && b < g) min = b;

	int total = r + g + b;
	if (total == 0) total = 1;

	double s = 1 - (3 / total) * min;
	return (int) round(s);
}

int CKingimageView::intensity(int r, int g, int b)
{
	return (r + g + b) / 3;
}

vector <int> CKingimageView::DCT1d(vector <int> f)
{
	int size = f.size();
	vector <int> t (size, 0);
	double a = 0, c = 0, total = 0;

	for (int u = 0; u < size; u++)
	{
		for (int i = 0; i < size; i++)
		{
			if (u == 0) a = sqrt(1 / (double) size);
			else a = sqrt(2 / (double) size);

			c = cos(((2 * i + 1) * u * PI) / (2 * size));
			total = total + f.at(i) * a * c;
		}

		t.at(u) = (int) round(total);
		total = 0;
	}

	return t;
}

void CKingimageView::printMessage(double m)
{
	stringstream ss;
	string str;
	char* cchar;
	ss << m;
	str = ss.str();
	cchar = (char*)str.c_str();
	AfxMessageBox(cchar);
}

void CKingimageView::printMessage(int m)
{
	stringstream ss;
	string str;
	char* cchar;
	ss << m;
	str = ss.str();
	cchar = (char*)str.c_str();
	AfxMessageBox(cchar);
}

void CKingimageView::printFile(vector <vector <double>> vector2D)
{
	int height = vector2D.size();
	int width = vector2D.at(0).size();
	ofstream myfile;
	myfile.open("test.txt");
	int i, j;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			myfile << setw(30) << vector2D.at(i).at(j) << "  ";
		}
		myfile << "\n";
	}

	myfile.close();
}

void CKingimageView::printFile(vector <vector <int>> vector2D)
{
	int height = vector2D.size();
	int width = vector2D.at(0).size();
	ofstream myfile;
	myfile.open("test.txt");
	int i, j;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			myfile << setw(30) << vector2D.at(i).at(j);
		}
		myfile << "\n";
	}

	myfile.close();
}

void CKingimageView::printFile(vector <int> f)
{
	int size = f.size();
	ofstream myfile;
	myfile.open("test.txt");

	for (int j = 0; j < size; j++)
	{
		myfile << f.at(j) << "  ";
	}

	myfile.close();
}

vector <vector <int>> CKingimageView::convolution(vector <vector <int>> img, vector <vector <int>> mask, bool logFlag)
{
	int imageWidth = img.at(0).size();
	int imageHeight = img.size();

	int i, j;
	vector <vector <int>> newImage(imageHeight, vector <int>(imageWidth, 0));

	for (i = 1; i < imageHeight - 1; i++)
	{
		for (j = 1; j < imageWidth - 1; j++)
		{
			newImage.at(i).at(j) = abs(convolve(img, i, j, mask, logFlag));
		}
	}

	return newImage;
}

int CKingimageView::convolve(vector <vector <int>> &img, int h, int w, vector <vector <int>> &mask, bool logFlag)
{
	int maskHeight = mask.size();
	int maskWidth = mask.at(0).size();

	if (maskHeight != maskWidth) AfxMessageBox("incorrect mask");
	int i, j, shift = maskHeight / 2;
	int total = 0, maskCoefficient = 0;

	for (i = 0; i < maskHeight; i++)
	{
		for (j = 0; j < maskWidth; j++)
		{
			int a = img.at(h - shift + i).at(w - shift + j);
			int b = mask.at(i).at(j);
			total = total + img.at(h - shift + i).at(w - shift + j) * mask.at(i).at(j);

			maskCoefficient = maskCoefficient + mask.at(i).at(j);
		}
	}

	if (maskCoefficient == 0) maskCoefficient = 1;

	return (int) round(total / maskCoefficient);
}