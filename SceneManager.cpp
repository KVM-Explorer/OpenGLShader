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

	unsigned int testVBO[2];
	glGenBuffers(2, testVBO);
	auto status = glGetError();

	auto shader_ptr = std::make_unique<cgProgram>();
	status = glGetError();
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
	colorPatch.setRange(data_property.minVal, data_property.maxVal, vec3(0, 1.f, 1.f), vec3(240.f, 1.f, 1.f));
	colorPatch.setBlockNum(10);
	colorPatch.init();
	colorPatch.updateBlockValue(meshManager.getRenderMode());
}

void SceneManager::render()
{
	using ColorType = ColorPatch::ColorType;
	auto tmp = colorPatch.getRange();

	auto min_color = colorPatch.getMinColor();	
	auto max_color = colorPatch.getMaxColor();	
	
	auto model_mat = meshManager.getModelMat();
	auto mode = meshManager.getRenderMode();

	shaderFromType[mode]->Use();
	
	shaderFromType[mode]->SetUniform("ProjectionMatrix",projectMatrix);
	shaderFromType[mode]->SetUniform("ViewMatrix",camera.getViewMatrix());
	shaderFromType[mode]->SetUniform("ModelMatrix", model_mat);
	shaderFromType[mode]->SetUniform("minValue", colorPatch.getRange().minValue);
	shaderFromType[mode]->SetUniform("maxValue", colorPatch.getRange().maxValue);
	shaderFromType[mode]->SetUniform("minColor", vec4(min_color, 1.f));
	shaderFromType[mode]->SetUniform("maxColor", vec4(max_color, 1.f));
	if (colorPatch.getColorType() == ColorType::hsv)shaderFromType[mode]->SetUniform("colorType", 0);
	if (colorPatch.getColorType() == ColorType::rgb)shaderFromType[mode]->SetUniform("colorType", 1);
	if(mode==ModeType::single) shaderFromType[mode]->SetUniform("blockNum", colorPatch.getBlockNum());

	meshManager.render();

	//  viewPos  viewHead -> Model
	model_mat = colorPatch.CalculateModelMaxtrix(camera.getPosition(), camera.getDirection());
	shaderFromType[mode]->SetUniform("ModelMatrix", model_mat);
	shaderFromType[mode]->SetUniform("ProjectionMatrix", orthoMatrix);
	colorPatch.render();

	shaderFromType[mode]->Unuse();

}

void SceneManager::setProjection(int width, int height)
{
	projectMatrix = glm::perspective(glm::radians(60.f), float(width) / float(height), 1.0f, 6000.f);
	// Todo 更新ToolBase 补偿
	orthoMatrix = glm::ortho(-width/2.f, width/2.f, -height/2.f, height/2.f,1.f,6000.f);
	colorPatch.setOffset(vec3(width/2.f-100.f,0.f,0.f));

}

void SceneManager::setInputSignal(const unsigned char& key, InputType type,int value)
{
	if (camera.getViewMode() == ViewMode::XYZ)
	{
		if (type == InputType::Keyboard) camera.inputKeyboard(key);
		if (type == InputType::Mouse) camera.inputMouse(key, value);
	}
}

void SceneManager::setColorType(int type)
{
	using ColorType = ColorPatch::ColorType;
	switch (type)
	{
	case 0:
		colorPatch.setColorType(ColorType::hsv);
		break;
	case 1:
		colorPatch.setColorType(ColorType::rgb);
		break;
	default:

		break;
	}
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
	colorPatch.updateBlockValue(render_mode);
}

void SceneManager::selectShowData(int index)
{
	auto render_mode = meshManager.getRenderMode();
	auto data_property = dataLoader.getPropertyDataByIndex(index);
	meshManager.setProperty(data_property);


}

void SceneManager::setProperty(string property_name)
{
	propertyName = property_name;
	auto render_mode = meshManager.getRenderMode();
	auto data_property = dataLoader.getPropertyDataBinary(propertyName);
	colorPatch.setRange(data_property.minVal, data_property.maxVal);
	meshManager.setProperty(data_property);
	colorPatch.updateBlockValue(render_mode);
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

int SceneManager::getFrameNum() const
{
	return dataLoader.getPropertyStructure().tot;
}

void SceneManager::setShowRange(int dimension, int st)
{
	meshManager.selectViewRange(dimension, st);
}

int SceneManager::getStRange(int x) const
{
	auto p = dataLoader.getDataStructure();
	switch (x)
	{
	case 0:
		return p.x;
		break;
	case 1:
		return p.y;
		break;
	case 2:
		return p.z;
		break;
	default:
		break;
	}
}

void SceneManager::setViewMode(int type)
{
	switch (type)
	{
	case 0:	
		camera.setViewMode(ViewMode::XY);
		break;
	case 1:
		camera.setViewMode(ViewMode::XZ);
		break;
	case 2:
		camera.setViewMode(ViewMode::YZ);
		break;
	case 3:
		camera.setViewMode(ViewMode::XYZ);
		break;
	default:
		break;
	}
}

void SceneManager::setBlockNum(int num)
{
	colorPatch.setBlockNum(num);
	colorPatch.init();
	colorPatch.updateBlockValue(meshManager.getRenderMode());
}
