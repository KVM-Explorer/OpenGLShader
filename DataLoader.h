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
	DataOrganization getDataOrganization()const;	// ������ݵ���֯��ʽ
	bool isExistBinary(string property);
	void getPropertyDataNext();	//������binary
	void getPropertyDataPre();	//������binary
	void getPropertyDataText(string filename,std::shared_ptr<float[]> &buffer);	// ���ڿ������Ժ�ת�����ɶ������ļ�
	void getPropertyDataBinary(string property);	// ���³�Ա�״δ�binary�ļ�
	void Text2Binary(string name);	// ���ı�ת��Ϊ�������ļ�

};

