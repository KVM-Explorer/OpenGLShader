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
    string path = dirname + "/" + property + ".bin";
    std::ifstream file;
    auto buffer = std::shared_ptr<float[]>(new float[dataStructure.num]);
    file.open(path, std::ios::in | std::ios::binary);
    file.read(reinterpret_cast<char*>(buffer.get()),sizeof(float)*(long long)dataStructure.num);
    propertyStructure.buffer = buffer;
    propertyStructure.index = 0;
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
    int index = 0;
    string src = dirname + "/" + name + ".pro";
    string dst = dirname + "/" + name + ".bin";
    ifstream src_file;
    ofstream dst_file;
    src_file.open(src,ios::in);
    dst_file.open(dst,ios::out|ios::binary);  
    src_file >> currentProperty;
    while (src_file >> tmp >> id >> tmp >> time)
    {
        for (int i = 0; i < dataStructure.num; i++)
        {
            string value;
            src_file >> value;
            buffer[index++] = stof(value);
        }
        dst_file.write(reinterpret_cast<const char*>(buffer.get()),sizeof(float)*dataStructure.num);
        propertyStructure.tot++;    // 累计序号
        index = 0;
    }
    src_file.close();
    dst_file.close();
}


DataLoader::PropertyStructure DataLoader::getPropertyDataNext()
{
    using namespace std;
    string path = dirname + "/" + currentProperty + ".bin";\
    std::ifstream file;
    auto buffer = std::shared_ptr<float[]>(new float[dataStructure.num]);
    file.open(path, std::ios::in | std::ios::binary);
    file.seekg(dataPtr, ios::beg);
    file.read(reinterpret_cast<char*>(buffer.get()),sizeof(float)*(long long)dataStructure.num);
    propertyStructure.buffer = buffer;
    propertyStructure.index++;
    dataPtr = file.tellg();
    file.close();

    return propertyStructure;
}

DataLoader::PropertyStructure DataLoader::getPropertyDataPre()
{
    using namespace std;
    string path = dirname + "/" + currentProperty + ".bin";
    std::ifstream file;
    auto buffer = std::shared_ptr<float[]>(new float[dataStructure.num]);
    file.open(path, std::ios::in | std::ios::binary);
    // Todo 检查是否越界
    dataPtr = dataPtr - sizeof(float)*2*(long long)dataStructure.num;
    file.seekg(dataPtr, ios::beg); // - 2* sizeof(data) 并提供检查
    file.read(reinterpret_cast<char*>(buffer.get()),sizeof(float)*(long long)dataStructure.num);
    propertyStructure.buffer = buffer;
    propertyStructure.index--;
    dataPtr = file.tellg() ;        
    file.close();
}

DataLoader::PropertyStructure DataLoader::getPropertyDataText(string filename)
{
    //Todo
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



