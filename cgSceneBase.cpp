#include "pch.h"
#include"cgSceneBase.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>


cgSceneBase::cgSceneBase()
{
}

cgSceneBase::~cgSceneBase()
{
}



void cgSceneBase::AddElement(std::shared_ptr<cgElement> pElement)
{
	elementsArray.push_back(pElement);
}

void cgSceneBase::Input(const unsigned int& key)
{
}

void cgSceneBase::SetProjection(int width, int height)
{
}
