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
	shader_ptr->CompileShader("Shader/project/single.vert");
	shader_ptr->CompileShader("Shader/project/single.frag");
	shader_ptr->Link();
	shaders.emplace_back(shader_ptr.release());

	keyFromString["isopleth"] = ModeType::isopleth;
	keyFromString["single"] = ModeType::single;
	keyFromString["smooth"] = ModeType::smooth;
	keyFromString["mesh"] = ModeType::mesh;

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
	auto data_property = dataLoader.getPropertyDataText("pressure.pro");
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
	shaders[0]->Use();
	auto model_mat = glm::scale(vec3(0.33f,0.33f,1.f));
	shaders[0]->SetUniform("ProjectionMatrix",projectMatrix);
	shaders[0]->SetUniform("ViewMatrix",camera.getViewMatrix());
	shaders[0]->SetUniform("ModelMatrix", model_mat);
	shaders[0]->SetUniform("minValue", 3000.f);
	shaders[0]->SetUniform("maxValue", 5000.f);
	shaders[0]->SetUniform("minColor", vec4(min_color, 1.f));
	shaders[0]->SetUniform("maxColor", vec4(max_color, 1.f));
	shaders[0]->SetUniform("blockNum", 10);

	meshManager.render();
	shaders[0]->Unuse();

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
}
