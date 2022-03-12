#pragma once
#include<GL/glew.h>
#include<SOIL/SOIL.h>
#include <string>
using std::string;
class cgTexture
{
public:
	cgTexture();
	~cgTexture();

	void SetName(string name);
	string GetName();
	bool LoadTexture(const char* path);
	unsigned int GetID();
private:
	string name;
	unsigned int id;
};

