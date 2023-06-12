#include "Utils.h"
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * �ַ����ָ�
 * @param str �ַ���
 * @param ch �ָ��
 * @return �ָ����ַ���������һ���ַ���������
 */
vector<string> Utils::StringSplit(const string str, const char ch)
{
	vector<string> res;

	stringstream ss(str);
	string temp;
	while (getline(ss, temp, ch))
	{
		res.push_back(temp);
	}

	return res;
}

string Utils::ReadFile(const char *filename)
{
	ifstream ifile(filename);
	stringstream ss;
	ss << ifile.rdbuf();
	ifile.close();
	return ss.str();
}

void Utils::WriteFile(const char *filename, string data)
{
	ofstream ofile(filename);
	// https://blog.csdn.net/xw20084898/article/details/21374433
	ofile << data;
	ofile.close();
}

/**
 * ���ڻ�ȡ�û�����ѡ��
 * @param title ����
 * @return true:ȷ��  false:�ܾ�
 */
bool Utils::JudgeChoose(const char *title)
{
	cout << title << "(y/n): ";
	char c;
	cin >> c;
	return c == 'y' || c == 'Y';
}

/**
 * ��ͣ����������Ļ
 */
void Utils::PauseAndCls()
{
	system("pause");
	system("cls");
}

string Utils::GetValidInput(const char *title, bool (*p)(string))
{
	string res;
	cout << title;
	cin >> res;
	do
	{
		if (p(res))
			return res;
		cout << "��������,����������: ";
		cin >> res;
	} while (true);
	return res;
}