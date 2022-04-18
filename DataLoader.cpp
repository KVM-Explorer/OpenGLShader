#include "pch.h"
#include "DataLoader.h"
#include <io.h>
#include <filesystem>
#include <iostream>


DataLoader::DataLoader()
{
    dataPtr = -1;
}

DataLoader::~DataLoader()
{
    
}

void DataLoader::getFiles(string directory)
{
    using namespace std::filesystem;
    if (!exists(directory))
    {
        TRACE("No Directory\n");
    }

    directory_iterator list(directory);	        
    for (auto& it : list)
    {
        if (it.is_directory()) continue;
        string file = it.path().filename().string();
        TRACE("%s\n", file.c_str());
        files.emplace_back(file);
    }
    dirname = directory;
}

void DataLoader::initFiles()
{
    using namespace std;
    using DS = DataLoader::DataStructure;
    // read .xyz
    string file="";
    for (auto x : files)
    {
        if (x.find(".xyz") != string::npos)
        {
            file = x;
            break;
        }
    }
    if (file == "")
    {
        throw "file is empty";
        return;
    }

    string path = dirname + "/" + file;
    ifstream input;
    string x, y, z;
    input.open(path);

    input >> x >> y >> z;
    dataStructure = DS(stoi(x),stoi( y), stoi(z));

    auto buffer = std::shared_ptr<float[]>(new float[dataStructure.num * 8 * 3]);

    
    int index = 0;
    for (int i = 0; i < dataStructure.z; i++)
    {
        for (int j = 0; j < dataStructure.y; j++)
        {
            for (int k = 0; k < dataStructure.x; k++)
            {
                for (int p = 0; p < 8 * 3; p++)
                {
                    string data;
                    input >> data;
                    buffer[index++] = stof(data);
                }
                
            }
        }
    }
    dataStructure.buffer = buffer;
}

DataLoader::DataStructure DataLoader::getDataStructure() const
{
    return dataStructure;
}

bool DataLoader::isExistBinary(string property)
{
    auto filename = property + ".bin";
    for (auto x : files)
    {
        if (filename == x)
        {
            return true;
        }
    }
    return false; 
}



DataLoader::PropertyStructure DataLoader::getPropertyDataBinary(string property)
{
    using namespace std;
    if (!isExistBinary(property))    Text2Binary(property);
    
    currentProperty = property;
    string data_path = dirname + "/" + property + ".bin";
    string meta_path = dirname + "/" + property + ".meta";
    std::ifstream data_file;
    std::ifstream meta_file;
    auto buffer = std::shared_ptr<float[]>(new float[dataStructure.num]);
    data_file.open(data_path, std::ios::in | std::ios::binary);
    meta_file.open(meta_path, std::ios::in | std::ios::binary);

    meta_file.read(reinterpret_cast<char*>(&propertyStructure), sizeof(propertyStructure));
    data_file.read(reinterpret_cast<char*>(buffer.get()),sizeof(float)*(long long)dataStructure.num);
    propertyStructure.buffer = buffer;
    dataPtr = data_file.tellg();

    data_file.close();
    meta_file.close();
    return propertyStructure;
}
DataLoader::PropertyStructure DataLoader::getPropertyStructure() const
{
    return propertyStructure;
}
DataLoader::PropertyStructure DataLoader::getPropertyDataByIndex(int index)
{
    propertyStructure.index = index;
    dataPtr = sizeof(float) * (long long)index*(long long)dataStructure.num;
	using namespace std;
	string path = dirname + "/" + currentProperty + ".bin";
	std::ifstream file;
	auto buffer = std::shared_ptr<float[]>(new float[dataStructure.num]);
	file.open(path, std::ios::in | std::ios::binary);

	file.seekg(dataPtr, ios::beg);
	file.read(reinterpret_cast<char*>(buffer.get()), sizeof(float) * (long long)dataStructure.num);
	propertyStructure.buffer = buffer;
	dataPtr = file.tellg();

	file.close();

    return propertyStructure;
}
/**
 * @brief 文本文件转二进制文件 
 * @param name 属性名称无扩展名
*/
void DataLoader::Text2Binary(string name)
{
    using namespace std;
    auto buffer = std::shared_ptr<float[]>(new float[dataStructure.num]);
    
    string tmp, id, time;
    float min_val, max_val;
    min_val = 0x7ffff;
    max_val = 0;
    int index = 0,tot = 0;
    string src = dirname + "/" + name + ".pro";
    string dst = dirname + "/" + name + ".bin";
    string meta = dirname + "/" + name + ".meta";
    ifstream src_file;
    ofstream dst_file;
    ofstream meta_file;
    src_file.open(src,ios::in);
    dst_file.open(dst,ios::out|ios::binary);  
    meta_file.open(meta, ios::out | ios::binary);
    src_file >> currentProperty;
    while (src_file >> tmp >> id >> tmp >> time)
    {
        for (int i = 0; i < dataStructure.num; i++)
        {
            string value;
            src_file >> value;
            buffer[index++] = stof(value);
            min_val = min(min_val, stof(value));
            max_val = max(max_val, stof(value));
        }
        dst_file.write(reinterpret_cast<const char*>(buffer.get()),sizeof(float)*(long long)dataStructure.num);
        tot++;   // 累计序号
        index = 0;
    }
    
    propertyStructure.maxVal = max_val;
    propertyStructure.minVal = min_val;
    propertyStructure.index = 0;
    propertyStructure.tot = tot;
    propertyStructure.buffer = nullptr;
    meta_file.write(reinterpret_cast<const char*>(&propertyStructure), sizeof(propertyStructure));

    meta_file.close();
    src_file.close();
    dst_file.close();
}

/**
 * @brief 获取下一帧的数据
 * @return 
*/
DataLoader::PropertyStructure DataLoader::getPropertyDataNext()
{
    if (propertyStructure.index == propertyStructure.tot - 1) return propertyStructure;
    using namespace std;
    string path = dirname + "/" + currentProperty + ".bin";
    std::ifstream file;
    auto buffer = std::shared_ptr<float[]>(new float[dataStructure.num]);
    file.open(path, std::ios::in | std::ios::binary);
    file.seekg(dataPtr, ios::beg);
    file.read(reinterpret_cast<char*>(buffer.get()),sizeof(float)*(long long)dataStructure.num);
    propertyStructure.buffer = buffer;
    dataPtr = file.tellg();
    propertyStructure.index++;
    file.close();

    return propertyStructure;
}

/**
 * @brief 获取上一帧的数据，其安全性由外部模块保证
 * @return
*/
DataLoader::PropertyStructure DataLoader::getPropertyDataPre()
{
    if (propertyStructure.index == 0) return propertyStructure;
    using namespace std;
    string path = dirname + "/" + currentProperty + ".bin";
    std::ifstream file;
    auto buffer = std::shared_ptr<float[]>(new float[dataStructure.num]);

    file.open(path, std::ios::in | std::ios::binary);
    dataPtr = dataPtr - sizeof(float)*2*(long long)dataStructure.num;
    file.seekg(dataPtr, ios::beg); // - 2* sizeof(data) 并提供检查
    file.read(reinterpret_cast<char*>(buffer.get()),sizeof(float)*(long long)dataStructure.num);

    propertyStructure.buffer = buffer;
    dataPtr = file.tellg() ;        
    propertyStructure.index--;
    file.close();
    return propertyStructure;
}

DataLoader::PropertyStructure DataLoader::getPropertyDataText(string filename)
{
    using namespace std;
    propertyStructure.buffer = std::shared_ptr<float[]>(new float[dataStructure.num]);
    
    string tmp, id, time;
    int index = 0;
    string path = dirname + "/" + filename;
    ifstream file;
    file.open(path, ios::in);
    file >> currentProperty;
    while (file >> tmp >> id >> tmp >> time)
    {
        propertyStructure.index = stoi(id);
        for (int i = 0; i < dataStructure.num; i++)
        {
            string value;
            file >> value;
            propertyStructure.buffer[index++] = stof(value);
        }
        // Todo 限定范围
        break;
    }
    file.close();
    return propertyStructure;
    

}



