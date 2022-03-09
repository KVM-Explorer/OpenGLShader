// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// 1907010308YWH_3View.cpp: CMy1907010308YWH3View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "1907010308YWH_3.h"
#endif

#include "1907010308YWH_3Doc.h"
#include "1907010308YWH_3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <glm/ext/matrix_clip_space.hpp>
#include "cgTriangle.h"
#include "cgPentagram.h"



// CMy1907010308YWH3View

IMPLEMENT_DYNCREATE(CMy1907010308YWH3View, CView)

BEGIN_MESSAGE_MAP(CMy1907010308YWH3View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy1907010308YWH3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_GE_TRIANGLE, &CMy1907010308YWH3View::OnGeTriangle)
	ON_COMMAND(ID_GE_PENTAGRAM, &CMy1907010308YWH3View::OnGePentagram)
	ON_COMMAND(ID_COLLISION_PENTAGRAM, &CMy1907010308YWH3View::OnCollisionPentagram)
	ON_WM_TIMER()
	ON_COMMAND(ID_CG_3DSCENE, &CMy1907010308YWH3View::OnCg3DScene)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy1907010308YWH3View 构造/析构

CMy1907010308YWH3View::CMy1907010308YWH3View() noexcept
{
	// TODO: 在此处添加构造代码

}

CMy1907010308YWH3View::~CMy1907010308YWH3View()
{
}

BOOL CMy1907010308YWH3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy1907010308YWH3View 绘图

BOOL CMy1907010308YWH3View::InitializeOpenGL()
{
	//Get a DC for the Client Area
	m_pDC = new CClientDC(this);
	//Failure to Get DC
	if (m_pDC == NULL) return FALSE;
	//Failure to set the pixel format
	if (!SetupPixelFormat())
	{
		return FALSE;
	}
	//Create Rendering Context
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//Failure to Create Rendering Context
	if (m_hRC == 0) return FALSE;
	//Make the RC Current
	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE) return FALSE;
	//Specify Black as the clear color
	glClearColor(0.5f, 1.0f, 1.0f, 0.50f);
	//Specify the back of the buffer as clear depth
	glClearDepth(1.0f);
	//Enable Depth Testing
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glewInit();
	//openGL 生产商及版本
	const char* vendorName = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
	return TRUE;
}

BOOL CMy1907010308YWH3View::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
	sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd
	1, // version number
	PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER ,
	 PFD_TYPE_RGBA, // RGBA type
	24, // 24-bit color depth
	0, 0, 0, 0, 0, 0, // color bits ignored
	0, 0, // no alpha buffer // shift bit ignored
	0, // no accumulation buffer
	0, 0, 0, 0, // accum bits ignored
	16, 0, // 16-bit z-buffer // no stencil buffer
	0, PFD_MAIN_PLANE, 0, // no auxiliary buffer // main layer// reserved
	0, 0, 0 // layer masks ignored
	};
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (m_nPixelFormat == 0)
		return FALSE;
	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
		return FALSE;
	return true;
}

void CMy1907010308YWH3View::OnDraw(CDC* pDC)
{
	CMy1907010308YWH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(scene!=nullptr)scene->Render();

	SwapBuffers(m_pDC->GetSafeHdc());
	wglMakeCurrent(0, 0);

}


// CMy1907010308YWH3View 打印


void CMy1907010308YWH3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy1907010308YWH3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy1907010308YWH3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy1907010308YWH3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMy1907010308YWH3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy1907010308YWH3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy1907010308YWH3View 诊断

#ifdef _DEBUG
void CMy1907010308YWH3View::AssertValid() const
{
	CView::AssertValid();
}

void CMy1907010308YWH3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy1907010308YWH3Doc* CMy1907010308YWH3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy1907010308YWH3Doc)));
	return (CMy1907010308YWH3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy1907010308YWH3View 消息处理程序


void CMy1907010308YWH3View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);// 设定 OpenGL 当前线程的渲染环境
	glViewport(0, 0, cx, cy);
	m_screenWidth = cx;
	m_screenHeight = cy;
	wglMakeCurrent(0, 0);
}


int CMy1907010308YWH3View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitializeOpenGL();
	scene =nullptr;
	
	
	return 0;
}


void CMy1907010308YWH3View::OnDestroy()
{
	CView::OnDestroy();

	wglMakeCurrent(m_pDC->m_hDC, NULL); //释放与 m_hDC 对应的 RC
	wglDeleteContext(m_hRC); //删除 RC if (m_pDC)
	delete m_pDC; //删除当前 View 拥有的 DC
}


BOOL CMy1907010308YWH3View::OnEraseBkgnd(CDC* pDC)
{
	return true;//return CView::OnEraseBkgnd(pDC);
}

          
void CMy1907010308YWH3View::OnGeTriangle()
{
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);//调用 OpenGL 函数前必须调用

	//cgBasicSceane* BasicSceane = new cgBasicSceane;
	auto basic_scene = std::make_shared<cgBasicSceneBase>();
	auto projection = glm::ortho(0.0f, (float)600, 0.0f, (float)600);//用户坐标范围（三维裁剪空间）
	glClearColor(0.5, 0.5, 0.5, 1);
	basic_scene->Init();
	basic_scene->SetProjection(projection);

	auto pTriagnle = std::make_shared<cgTriangle>();
	pTriagnle->Init();
	pTriagnle->CalculateModelMatrix();
	
	basic_scene->AddElement(pTriagnle);
	scene = basic_scene;

	wglMakeCurrent(0, 0);
	Invalidate(FALSE);//发送重绘消息，触发执行 OnDraws 函数。
}


void CMy1907010308YWH3View::OnGePentagram()
{


	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);//调用 OpenGL 函数前必须调用
	//cgBasicSceane* BasicSceane = new cgBasicSceane;
	auto basic_scene = std::make_shared<cgBasicSceneBase>();
	auto projection = glm::ortho(0.0f, (float)600, 0.0f, (float)600);//用户坐标范围（三维裁剪空间）
	glClearColor(0.5, 0.5, 0.5, 1);

	basic_scene->Init();
	basic_scene->SetProjection(projection);

	auto pentagram_ptr = std::make_shared<cgPentagram>(0, vec3(300, 400, 0));
	pentagram_ptr->SetType(0);
	pentagram_ptr->Init();
	pentagram_ptr->CalculateModelMatrix();
	basic_scene->AddElement(pentagram_ptr);
	
	pentagram_ptr = std::make_shared<cgPentagram>(0, vec3(150, 200, 0));
	pentagram_ptr->SetType(1);
	pentagram_ptr->Init();
	pentagram_ptr->CalculateModelMatrix();
	basic_scene->AddElement(pentagram_ptr);
	
	pentagram_ptr = std::make_shared<cgPentagram>(0, vec3(450, 200, 0));
	pentagram_ptr->SetType(2);
	pentagram_ptr->Init();
	pentagram_ptr->CalculateModelMatrix();
	basic_scene->AddElement(pentagram_ptr);
	scene = basic_scene;

	wglMakeCurrent(0, 0);
	Invalidate(FALSE);//发送重绘消息，触发执行 OnDraws 函数。
}


void CMy1907010308YWH3View::OnCollisionPentagram()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, 100, NULL);
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);//调用 OpenGL 函数前必须调用
	auto collosoon_bounce_ptr = std::make_shared<cgCollisionBounce>();
	auto projection = glm::ortho(0.0f, (float)600, 0.0f, (float)600);//用户坐标范围（三维裁剪空间）
	collosoon_bounce_ptr->Init();
	collosoon_bounce_ptr->SetProjection(projection);
	scene = collosoon_bounce_ptr;
	wglMakeCurrent(0, 0);
	Invalidate(FALSE);//发送重绘消息，触发执行 OnDraws 函数。
}


void CMy1907010308YWH3View::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		if (scene)
		{
			wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);//调用 OpenGL 函数前必须调用

			scene->Update();

			wglMakeCurrent(0, 0);
			Invalidate(FALSE);
		}

	}
	CView::OnTimer(nIDEvent);
}


void CMy1907010308YWH3View::OnCg3DScene()
{
	
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);//调用 OpenGL 函数前必须调用
	
	auto scene3d_ptr = std::make_shared<cg3DScene>();
	scene3d_ptr->Init();
	scene = scene3d_ptr;


	wglMakeCurrent(0, 0);
	Invalidate(FALSE);//发送重绘消息，触发执行 OnDraws 函数
}


void CMy1907010308YWH3View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (scene != nullptr)
	{
		scene->Input(nChar);
		Invalidate(FALSE);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

}
