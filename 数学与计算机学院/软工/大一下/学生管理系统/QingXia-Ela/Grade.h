#pragma once
#include <string>
using namespace std;
const char spliter = '\t';

class Grade
{
public:
	/** ѧ�� */
	long long id;
	/** �γ̺� */
	string course;
	/** �ɼ� */
	string grade;

	Grade(string data);
	Grade(long long id, string course, string grade) : id(id), grade(grade), course(course){};

	string ToString();
};
