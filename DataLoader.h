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
	DataStructure getDataStructure()const;	// ������ݵ���֯��ʽ
	
	bool isExistBinary(string property);
	PropertyStructure getPropertyDataNext();	//������binary
	PropertyStructure getPropertyDataPre();	//������binary
	PropertyStructure getPropertyDataText(string filename);	// ���ڿ������Ժ�ת�����ɶ������ļ�
	PropertyStructure getPropertyDataBinary(string property);	// ���³�Ա�״δ�binary�ļ�
	PropertyStructure getPropertyStructure() const;
	PropertyStructure getPropertyDataByIndex(int index);
	void Text2Binary(string name);	// ���ı�ת��Ϊ�������ļ�

	

};

