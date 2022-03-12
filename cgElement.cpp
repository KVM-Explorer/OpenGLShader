#include "pch.h"
#include "cgElement.h"

void cgElement::Render()
{
}

mat4 cgElement::GetModelMatrix()
{
	return model;
}

void cgElement::SetName(std::string name)
{
	this->name = name;
}

std::string cgElement::GetName()
{
	return name;
}
