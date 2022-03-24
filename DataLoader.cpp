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
    for (int i = 0; i < dataStructure.num; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                string data;
                input >> data;
                buffer[index++] = stof(data);
            }
        }
    }
    
    dataStructure.buffer = buffer;
    auto count = buffer.use_count();
}

DataLoader::DataStructure DataLoader::getDataStructure() const
{
    return dataStructure;
}

bool DataLoader::isExistBinary(string property)
{
    auto filename = property + ".binary";
    for (auto x : files)
    {
        if (filename == x)
        {
            return true;
        }
    }
    return false;
}



void DataLoader::getPropertyDataBinary(string property)
{
    using namespace std;
    if (!isExistBinary(property))    Text2Binary(property);
    
    currentProperty = property;
    string path = dirname + "/" + property + ".binary";
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);
    // Todo read files
    dataPtr = file.tellg();
    file.close();
}

void DataLoader::Text2Binary(string name)
{
    //Todo
}


void DataLoader::getPropertyDataNext()
{
    using namespace std;
    string path = dirname + "/" + currentProperty + ".binary";
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);
    file.seekg(dataPtr, ios::beg);
    //todo read
    dataPtr = file.tellg();
    file.close();
}

void DataLoader::getPropertyDataPre()
{
    using namespace std;
    string path = dirname + "/" + currentProperty + ".binary";
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);
    file.seekg(dataPtr, ios::beg); // - 2* sizeof(data) 并提供检查
    //todo read
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
    return propertyStructure;
    

}



