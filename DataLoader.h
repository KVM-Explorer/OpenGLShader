#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <istream>
#include <fstream>

using std::string;

class DataLoader
{
public:
	struct DataStructure
	{
		int x, y, z;
		int num;
		std::shared_ptr<float[]> buffer =nullptr;
		DataStructure(int x, int y, int z)
		{
			this->num = x * y * z;
			this->x = x;
			this->y = y;
			this->z = z;
		};
		DataStructure() :x(0),y(0),z(0),num(0){};
	};
	struct PropertyStructure
	{
		int index;
		int tot;
		float maxVal;
		float minVal;
		std::shared_ptr<float[]> buffer;
	};
protected:
	std::vector<string> files;
	string dirname;
	DataStructure dataStructure;
	PropertyStructure propertyStructure;
	string currentProperty;
	std::pair<int, int> fileRange;
	std::streamoff	 dataPtr;
	
public:
	DataLoader();
	~DataLoader();

	void getFiles(string directory);
	void initFiles();
	DataStructure getDataStructure()const;	// 获得数据的组织形式
	
	bool isExistBinary(string property);
	PropertyStructure getPropertyDataNext();	//仅用于binary
	PropertyStructure getPropertyDataPre();	//仅用于binary
	PropertyStructure getPropertyDataText(string filename);	// 用于开发测试和转换生成二进制文件
	PropertyStructure getPropertyDataBinary(string property);	// 更新成员首次打开binary文件
	PropertyStructure getPropertyStructure() const;
	PropertyStructure getPropertyDataByIndex(int index);
	void Text2Binary(string name);	// 将文本转化为二进制文件

	

};

