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

// 1907010308YWH_3View.h: CMy1907010308YWH3View 类的接口
//

#pragma once
#include <GL/glew.h>
#include "cgCylinder.h"
#include "cgBasicSceneBase.h"
#include "cgCollisionBounce.h"
#include "cg3DScene.h"
#include "cgLightScene.h"
#include "cgModelScene.h"
#include "SceneManager.h"
#include "MainFrm.h"
class CMy1907010308YWH3View : public CView
{
protected: // 仅从序列化创建
	CMy1907010308YWH3View() noexcept;
	DECLARE_DYNCREATE(CMy1907010308YWH3View)

// 特性
public:
	CMy1907010308YWH3Doc* GetDocument() const;
	HGLRC m_hRC; //Rendering Context
	CDC* m_pDC; //Device Context
	int m_screenWidth;
	int m_screenHeight;
	CPoint cursor_position;
	std::shared_ptr<cgSceneBase> scene;
	std::shared_ptr<SceneManager> sceneManager;

// 操作
public:
	BOOL InitializeOpenGL();
	BOOL SetupPixelFormat();
	void AddDataSelectorContent(int num);
	void UIinit();
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy1907010308YWH3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGeTriangle();
	afx_msg void OnGePentagram();
	afx_msg void OnCollisionPentagram();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCg3DScene();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCgTexture();
	afx_msg void OnCgPointlight();
	afx_msg void OnCgLight2Texture();
	afx_msg void OnModelRabbit();
	afx_msg void OnProjectOpenDir();
	afx_msg void UISelectProperty();
	afx_msg void UISelectViewMode();
	afx_msg void UISelectRange();
	afx_msg void UISelectRenderMode();
	afx_msg void UISelectColorMin();
	afx_msg void UISelectColorMax();
	afx_msg void UIPlayData();
	afx_msg void UIPlayReverseData();
	afx_msg void UIPlayPause();
	afx_msg void UIPlayNextData();
	afx_msg void UIPlayPreData();
	afx_msg void UITimeSelector();
	afx_msg void UISelectDimension();
};

#ifndef _DEBUG  // 1907010308YWH_3View.cpp 中的调试版本
inline CMy1907010308YWH3Doc* CMy1907010308YWH3View::GetDocument() const
   { return reinterpret_cast<CMy1907010308YWH3Doc*>(m_pDocument); }
#endif

