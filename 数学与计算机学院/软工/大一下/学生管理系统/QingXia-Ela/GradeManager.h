#pragma once
#include <string>
#include <vector>
#include "Grade.h"
#include "CourseManager.h"
#include "StudentManager.h"
using namespace std;

class GradeManager
{
private:
  vector<Grade> grades;
  CourseManager courseManager;
  StudentManager studentManager;

  string ReadDB();
  void WriteDB(string str);

  string ParseVector2DBString(vector<Grade> grades);
  vector<Grade> ParseString2Vector(string data);

  bool JudgeExist(long long id, string courseId);
  bool JudgeGrade(string grade);
  bool JudgeStudentIdExist(long long id);
  bool JudgeCourseIdExist(string courseId);

  void AddGrade(long long id, string courseId, string grade);
  void DeleteGrade(long long id, string courseId);
  void ModifyGrade(long long id, string courseId, string grade);
  void PrintGradeInfo(long long id, string courseId);

public:
  GradeManager(CourseManager &C, StudentManager &S);

  void add();

  void del();

  void modify();

  void query();

  /** ����ѧ�Ų�ѯĳ��ѧ���ĸ��ſγ̵ĳɼ� */
  void queryByStudentId();

  /** ���ݿγ̺Ų�ѯĳ�ſγ̵ĳɼ���� */
  void queryByCourseId();

  /** ͳ��ĳ�༶���������� */
  void queryClassFailStudent();

  /** ͳ��ĳ�ſγ̸��ɼ�����������ٷֱ� */
  void queryGradeStudentCountByCourseId();

  vector<Grade> QueryGrade(long long id, string courseId);
  vector<Grade> QueryGrade(long long id);
  vector<Grade> QueryGrade(string courseId);
  vector<Grade> QueryFailStudentByClassName(string name);
};
