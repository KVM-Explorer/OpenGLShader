#include "pch.h"
#include"cgSceneBase.h"



cgSceneBase::cgSceneBase()
{
}

cgSceneBase::~cgSceneBase()
{
}


void cgSceneBase::SetProjection(mat4 projection)
{
	projectionMat = projection;
}

void cgSceneBase::AddElement(std::shared_ptr<cgElement> pElement)
{
	elementsArray.push_back(pElement);
}

void cgSceneBase::Input(const unsigned int& key)
{
}
