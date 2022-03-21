#pragma once
#include "pch.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>

using glm::vec3;
using glm::mat4;
using glm::radians;

class Unit
{
public:
	enum class Mode
	{
		single,		// ��ɫ	
		smooth,		// �⻬
		isopleth	// ��ֵ��
	};
protected:
	Mode drawMode;
	const int elementNum = 6*2 ;
	unsigned int vboHandle[3];
	unsigned int vaoHandle;

public:
	void render();
	void setDrawMode(Mode mode);
	/// <summary>
	/// ���뵥��unit���ײ�ָ��
	/// </summary>
	/// <param name="data">x y z ��ʽ���μ�¼6������</param>
	void init(std::shared_ptr<float[]> data);
	void genElement(std::shared_ptr<float[]> dst,std::shared_ptr<float[]> src,
					int &vindex,int a,int b,int c,int d);
	void genColor(std::shared_ptr<float[]> dst, std::shared_ptr<float[]> src,
		int& cindex, int a, int b, int c, int d);
};

