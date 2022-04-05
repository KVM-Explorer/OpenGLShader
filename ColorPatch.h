#pragma once
#include "ToolBase.h"
#include<glm/glm.hpp>
#include<memory>

using vec3 = glm::vec3;
using mat4 = glm::mat4;
using RenderMode = Unit::Mode;

class ColorPatch :
    public ToolBase
{
public:
    enum class ColorType
    {
        hsv, rgb
    };
    struct Range
    {
        float minValue, maxValue;
        vec3 minColor, maxColor;
        Range(float min_value, float max_value, vec3 min_color, vec3 max_color)
            :minValue(min_value), maxValue(max_value),
            minColor(min_color), maxColor(max_color)
        {};
        Range() 
        {
            minValue = maxValue = 0.f;
            minColor = maxColor = vec3(0.f, 0.f, 0.f);
        };
    };
protected:
    int blockNum;   // 色标块个数
    Range range;
    mat4 projectionMat;
    mat4 viewMat;
    mat4 modelMat;
    unsigned int vboHandle[2];
    unsigned int vaoHandle;

public:
    ColorPatch();
    ~ColorPatch();

    void init();   // 初始化色标 block
    
    void setBlockNum(int num);
    void setProjection(mat4 project);
    void render();
    
    void setRange(float min_value, float max_value, vec3 min_color, vec3 max_color);
    void setRange(float min_val, float max_val);
    /**
     * @brief 
     * @param color hsv 
    */
    void setColorMin(vec3 color);
    /**
     * @brief 
     * @param color hsv 
    */
    void setColorMax(vec3 color);
    Range getRange() const;
    vec3 getMinColor() const;
    vec3 getMaxColor() const;
    /**
     * @brief 更新色块颜色
    */
    void updateBlockValue(RenderMode mode);

    void genBlocks(std::shared_ptr<float[]> dst,int &vindex);
    void genSingleColor(std::shared_ptr<float[]> dst, int& cindex);
    void genSmoothColor(std::shared_ptr<float[]> dst, int& cindex);

};

