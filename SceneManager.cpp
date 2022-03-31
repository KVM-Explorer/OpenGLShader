#include "pch.h"
#include "SceneManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/color_space.hpp>

SceneManager::SceneManager()
{
	camera.init();

	projectMatrix = glm::perspective(glm::radians(60.f), 1.f, 1.f, 300.f);

	auto shader_ptr = std::make_unique<cgProgram>();
	shader_ptr->CompileShader("Shader/project/basic.vert");
	shader_ptr->CompileShader("Shader/project/basic.frag");
	shader_ptr->Link();
	shaderFromType[ModeType::mesh].reset(shader_ptr.release());

	shader_ptr = std::make_unique<cgProgram>();
	shader_ptr->CompileShader("Shader/project/smooth.vert");
	shader_ptr->CompileShader("Shader/project/smooth.frag");
	shader_ptr->Link();
	shaderFromType[ModeType::smooth].reset(shader_ptr.release());

	shader_ptr = std::make_unique<cgProgram>();
	shader_ptr->CompileShader("Shader/project/single.vert");
	shader_ptr->CompileShader("Shader/project/single.frag");
	shader_ptr->Link();
	shaderFromType[ModeType::single].reset(shader_ptr.release());


	keyFromString["isopleth"] = ModeType::isopleth;
	keyFromString["single"] = ModeType::single;
	keyFromString["smooth"] = ModeType::smooth;
	keyFromString["mesh"] = ModeType::mesh;

	propertyName = "pressure";
}

SceneManager::~SceneManager()
{
}

void SceneManager::setFileDirectory(string dir)
{
	// Files
	dataLoader.getFiles(dir);
	dataLoader.initFiles();

	// MeshManager
	meshManager.init(dataLoader.getDataStructure());
	auto data_property = dataLoader.getPropertyDataBinary(propertyName);
	meshManager.setProperty(data_property);
	
	
	// ColorPatch
	//colorPatch.setRange();
	//colorPatch.init();
}

void SceneManager::render()
{
	auto tmp = colorPatch.getRange();

	/// Todo Mesh  Important fix cube
	//meshManager.setViewMatrix(camera.getViewMatrix());
	//meshManager.setProjection(projectMatrix);
	//meshManager.render();

	/// Color Patch
	// Todo update the content
	//colorPatch.setPosition(camera.getPosition());
	colorPatch.setProjection(projectMatrix);
	colorPatch.setViewMatrix(camera.getViewMatrix());
	colorPatch.render();

	auto min_color = colorPatch.getMinColor();	min_color.x = min_color.x / 360.f;
	auto max_color = colorPatch.getMaxColor();	max_color.x = max_color.x / 360.f;
	
	auto model_mat = glm::scale(vec3(0.33f, 0.33f, 1.f));

	auto mode = meshManager.getRenderMode();
	auto ps = dataLoader.getPropertyStructure();	// 属性数据结构
	shaderFromType[mode]->Use();
	
	shaderFromType[mode]->SetUniform("ProjectionMatrix",projectMatrix);
	shaderFromType[mode]->SetUniform("ViewMatrix",camera.getViewMatrix());
	shaderFromType[mode]->SetUniform("ModelMatrix", model_mat);
	shaderFromType[mode]->SetUniform("minValue", ps.minVal);
	shaderFromType[mode]->SetUniform("maxValue", ps.maxVal);
	shaderFromType[mode]->SetUniform("minColor", vec4(min_color, 1.f));
	shaderFromType[mode]->SetUniform("maxColor", vec4(max_color, 1.f));
	
	if(mode==ModeType::single) shaderFromType[mode]->SetUniform("blockNum", 10);

	meshManager.render();
	shaderFromType[mode]->Unuse();

}

void SceneManager::setProjection(int width, int height)
{
	projectMatrix = glm::perspective(glm::radians(60.f), float(width) / float(height), 1.0f, 3000.f);
}

void SceneManager::setInputSignal(const unsigned char& key, InputType type,int value)
{
	if (type == InputType::Keyboard) camera.inputKeyboard(key);
	if (type == InputType::Mouse) camera.inputMouse(key, value);

}

void SceneManager::setColorMin(unsigned char r, unsigned char g, unsigned char b)
{
	auto hsv = glm::hsvColor(vec3(r/255.f,g/255.f,b/255.f));
	colorPatch.setColorMin(hsv);
}

/**
 * @brief 设置颜色上界
 * @param r 0-255
 * @param g 0-255
 * @param b 0-255
 * @detail hsv 0-360 0-1 0-255
*/
void SceneManager::setColorMax(unsigned char r, unsigned char g, unsigned char b)
{
	auto hsv = glm::hsvColor(vec3(r/255.f,g/255.f,b/255.f));
	auto rgb = glm::rgbColor(hsv);
	colorPatch.setColorMax(hsv);
}

void SceneManager::setRenderMode(std::string mode)
{
	auto render_mode = keyFromString[mode];
	meshManager.setRenderMode(render_mode);
	auto data_property = dataLoader.getPropertyDataBinary(propertyName);
	meshManager.setProperty(data_property);
}

void SceneManager::setProperty(string property_name)
{
	propertyName = property_name;

	auto data_property = dataLoader.getPropertyDataBinary(propertyName);
	meshManager.setProperty(data_property);
}

bool SceneManager::showNext()
{
	auto data_property = dataLoader.getPropertyDataNext();
	meshManager.setProperty(data_property);
	if (data_property.index == data_property.tot - 1) return false;
	return true;
}

bool SceneManager::showPre()
{
	auto data_property = dataLoader.getPropertyDataPre();
	meshManager.setProperty(data_property);
	if (data_property.index == 0) return false;
	return true;
}
