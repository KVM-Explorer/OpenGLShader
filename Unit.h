#pragma once
#include "pch.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

using glm::vec3;
using glm::mat4;
using glm::radians;

class Unit
{
public:
	enum class Mode
	{
		single,		// 单色	
		smooth,		// 光滑
		isopleth,	// 等值线
		mesh
	};
protected:
	Mode drawMode;
	const int elementNum = 6*2 ;
	unsigned int vboHandle[4];		// vertex single smooth isopleth
	unsigned int vaoHandle;

public:
	void render();
	void setDrawMode(Mode mode);
	/// <summary>
	/// 输入单个unit的首部指针
	/// </summary>
	/// <param name="data">x y z 形式依次记录6个顶点</param>
	void init(std::shared_ptr<float[]> data, int st);
	void setValue(float data);
	void setValue(std::vector<float> data);
	void genElement(std::shared_ptr<float[]> dst,std::shared_ptr<float[]> src, 
					int st,int &vindex,int a,int b,int c, int d);
	void genSingleColor(std::shared_ptr<float[]> dst,float src,int &cindex);

	void genSmooth(std::shared_ptr<float[]> dst, std::vector<float> &src, int& cindex, int a, int b, int c, int d);

	void genIsopleth(std::shared_ptr<float[]> dst, std::shared_ptr<float[]> src,
					int st, int& cindex, int a, int b, int c, int d);
};

