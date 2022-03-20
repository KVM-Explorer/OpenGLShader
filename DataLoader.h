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
	struct DataOrganization
	{
		int x, y, z;
		int num;
		std::shared_ptr<float[]> buffer =nullptr;
		DataOrganization(int x, int y, int z)
		{
			this->num = x * y * z;
			this->x = x;
			this->y = y;
			this->z = z;
		};
		DataOrganization() :x(0),y(0),z(0),num(0){};
	};
protected:
	std::vector<string> files;
	string dirname;
	DataOrganization organization;
	string currentProperty;
	std::pair<int, int> fileRange;
	int dataPtr;
	
public:
	DataLoader();
	~DataLoader();

	void getFiles(string directory);
	void initFiles();
	DataOrganization getDataOrganization()const;	// 获得数据的组织形式
	bool isExistBinary(string property);
	void getPropertyDataNext();	//仅用于binary
	void getPropertyDataPre();	//仅用于binary
	void getPropertyDataText(string filename,std::shared_ptr<float[]> &buffer);	// 用于开发测试和转换生成二进制文件
	void getPropertyDataBinary(string property);	// 更新成员首次打开binary文件
	void Text2Binary(string name);	// 将文本转化为二进制文件

};

