#pragma once
#include "cgSceneBase.h"
class cgRayTraceScene :
    public cgSceneBase
{
public:
	cgRayTraceScene();
	~cgRayTraceScene();

	void Init();
	void Render();
	void Update();
	void SetProjection(mat4 projection);
	void SetProjection(int width, int height);
	void AddElement(std::shared_ptr<cgElement> element);
	void SetSize(int w, int h) { W = w, H = h; }
	inline GLuint GetTextureID() { return tex; };

private:
	cgProgram computerShader;
	GLuint tex;
	int W{512};
	int H{256};
};

