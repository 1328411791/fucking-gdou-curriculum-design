#include "GradeManager.h"
#include "Utils.h"
#include <iostream>

string GradeManager::ReadDB()
{
  return Utils::ReadFile("Grade.txt");
}

void GradeManager::WriteDB(string str)
{
  Utils::WriteFile("Grade.txt", str);
}

string GradeManager::ParseVector2DBString(vector<Grade> grades)
{
  string str = "";
  for (Grade grade : grades)
  {
    str += grade.ToString() + "\n";
  }
  return str;
}

vector<Grade> GradeManager::ParseString2Vector(string data)
{
  vector<Grade> grades;
  vector<string> arr = Utils::StringSplit(data, '\n');
  for (string str : arr)
  {
    Grade grade(str);
    grades.push_back(grade);
  }
  return grades;
}

bool GradeManager::JudgeExist(long long id, string courseId)
{
  for (Grade grade : this->grades)
    if (grade.id == id && grade.course == courseId)
      return true;
  return false;
}

bool GradeManager::JudgeGrade(string grade)
{
  vector<string> arr({"����", "����", "�е�", "����", "������"});
  for (string str : arr)
  {
    if (grade == str)
    {
      return true;
    }
  }
  try
  {
    int gradeNum = stoi(grade.c_str());
    return gradeNum >= 0 && gradeNum <= 100;
  }
  catch (const std::exception &e)
  {
    return false;
  }
  return false;
}

vector<Grade> GradeManager::QueryGrade(long long id, string courseId)
{
  vector<Grade> grades;
  for (Grade grade : this->grades)
  {
    if (grade.id == id && grade.course == courseId)
    {
      grades.push_back(grade);
      break;
    }
  }
  return grades;
}

vector<Grade> GradeManager::QueryGrade(long long id)
{
  vector<Grade> grades;
  for (Grade grade : this->grades)
  {
    if (grade.id == id)
    {
      grades.push_back(grade);
    }
  }
  return grades;
}

/**
 * ��ѯ�ÿγ������гɼ�
 */
vector<Grade> GradeManager::QueryGrade(string courseId)
{
  vector<Grade> grades;
  for (Grade grade : this->grades)
  {
    if (grade.course == courseId)
    {
      grades.push_back(grade);
    }
  }
  return grades;
}

vector<Grade> GradeManager::QueryFailStudentByClassName(string name)
{
  vector<Grade> grades;
  for (Grade grade : this->grades)
  {
    try
    {
      if (grade.grade == "������" || stoi(grade.grade) < 60)
      {
        Student *stu = this->studentManager.query(grade.id);
        if (stu != nullptr && stu->major == name)
          grades.push_back(grade);
      }
    }
    catch (const std::exception &e)
    {
      continue;
    }
  }
  return grades;
}

bool GradeManager::JudgeCourseIdExist(string courseId)
{
  return this->courseManager.QueryCourse(courseId) != nullptr;
}

bool GradeManager::JudgeStudentIdExist(long long id)
{
  Student *stu = this->studentManager.query(id);

  return stu != nullptr;
}

/**
 * ��ӳɼ����������飬����ʾ�Ƿ���ڣ�
 */
void GradeManager::AddGrade(long long id, string courseId, string grade)
{
  if (!JudgeGrade(grade))
    return;
  Grade gradeObj(id, courseId, grade);
  this->grades.push_back(gradeObj);
  this->WriteDB(this->ParseVector2DBString(this->grades));
}

void GradeManager::DeleteGrade(long long id, string courseId)
{
  for (Grade &grade : this->grades)
  {
    if (grade.id == id && grade.course == courseId)
    {
      this->grades.erase(this->grades.begin() + this->grades.size() - 1);
      this->WriteDB(this->ParseVector2DBString(this->grades));
      return;
    }
  }
}

void GradeManager::ModifyGrade(long long id, string courseId, string grade)
{
  for (Grade &gradeObj : this->grades)
  {
    if (gradeObj.id == id && gradeObj.course == courseId)
    {
      if (!JudgeGrade(grade))
      {
        cout << "�ɼ����Ϸ�" << endl;
        return;
      }
      gradeObj.grade = grade;
      this->WriteDB(this->ParseVector2DBString(this->grades));
      return;
    }
  }
}

void GradeManager::PrintGradeInfo(long long id, string courseId)
{
  vector<Grade> grades = this->QueryGrade(id, courseId);

  if (grades.empty())
  {
    cout << "û�и�ѧ�������Ӧ�γ̺ŵĳɼ�" << endl;
    return;
  }
  cout << "����ѯ��" << grades.size() << "���ɼ�:" << endl;
  cout << "ѧ��\t\t�γ̺�\t\t�ɼ�" << endl;

  for (Grade &grade : grades)
  {
    cout << grade.ToString() << endl;
  }
}

/**
 * Visual Utils
 */

/** ��ӳɼ� */
void GradeManager::add()
{
  long long id;
  string courseId;
  string grade;
  cout << "------��ӳɼ�------" << endl;
  cout << "������ѧ��ID:";
  cin >> id;
  if (!JudgeStudentIdExist(id))
  {
    cout << "��ѧ��������" << endl;
    Utils::PauseAndCls();
    return;
  }
  cout << "������γ�ID:";
  cin >> courseId;
  if (!JudgeCourseIdExist(courseId))
  {
    cout << "�ÿγ̲�����" << endl;
    Utils::PauseAndCls();
    return;
  }

  /**
   * ����Ƿ����и�ѧ����ÿγ̵ĳɼ�������ɼ����߼����и���
   */

  bool exist = JudgeExist(id, courseId);

  if (exist)
  {
    this->PrintGradeInfo(id, courseId);
    if (!Utils::JudgeChoose("�ò����������������ݣ��Ƿ����?"))
      return;
  }

  cout << "������ɼ�:";
  cin >> grade;
  if (JudgeGrade(grade))
  {
    exist ? this->ModifyGrade(id, courseId, grade) : this->AddGrade(id, courseId, grade);
    cout << (exist ? "�޸ĳɹ�" : "��ӳɹ�") << endl;
  }
  else
    cout << "��������ȷ�ĳɼ�" << endl;

  Utils::PauseAndCls();
}

/** ɾ���ɼ� */
void GradeManager::del()
{
  cout << "------ɾ���ɼ�------" << endl;
  long long id;
  string courseId;
  cout << "������ѧ��ID:";
  cin >> id;
  cout << "������γ�ID:";
  cin >> courseId;
  if (JudgeExist(id, courseId))
  {
    cout << endl;
    this->PrintGradeInfo(id, courseId);
    if (Utils::JudgeChoose("�ò�����ɾ���������ݣ��Ƿ����?"))
    {
      this->DeleteGrade(id, courseId);
      cout << "ɾ���ɹ�" << endl;
    }
    else
      cout << "��ȡ��ɾ������" << endl;
  }
  else
    cout << "��������û�в�ѯ���κγɼ�" << endl;

  Utils::PauseAndCls();
}

void GradeManager::modify()
{
  long long id;
  string courseId;
  string grade;
  cout << "------�޸ĳɼ�------" << endl;
  cout << "������ѧ��ID:";
  cin >> id;
  cout << "������γ�ID:";
  cin >> courseId;

  if (JudgeExist(id, courseId))
  {
    cout << endl;
    this->PrintGradeInfo(id, courseId);
    if (Utils::JudgeChoose("�ò����������޸����ݣ��Ƿ����?"))
    {
      cout << "�������µĳɼ�:";
      cin >> grade;
      if (JudgeGrade(grade))
      {
        this->ModifyGrade(id, courseId, grade);
        cout << "�޸ĳɹ�" << endl;
      }
      else
        cout << "��������ȷ�ĳɼ�" << endl;
    }
    else
      cout << "��ȡ���޸Ĳ���" << endl;
  }
  else
    cout << "��������û�в�ѯ���κγɼ�" << endl;

  Utils::PauseAndCls();
}

/** ��ѯ�ɼ� */
void GradeManager::query()
{
  long long id;
  string courseId;
  cout << "------��ѯ�ɼ�------" << endl;
  cout << "������ѧ��ID:";
  cin >> id;
  cout << "������γ�ID:";
  cin >> courseId;
  if (JudgeExist(id, courseId))
    this->PrintGradeInfo(id, courseId);
  else
    cout << "��������û�в�ѯ���κγɼ�" << endl;

  Utils::PauseAndCls();
}

void GradeManager::queryByStudentId()
{
  cout << "------��ѯѧ�����ſγ̳ɼ�------" << endl;
  long long id;
  id = stoll(Utils::GetValidInput("������ѧ��ID:", Student::validateId));

  if (JudgeStudentIdExist(id))
  {
    vector<Grade> grades = this->QueryGrade(id);
    if (grades.empty())
      cout << "��ѧ���������κγɼ�" << endl;
    else
    {
      cout << "IDΪ" << id << "��ѧ�����γ̳ɼ�����:" << endl;
      cout << "�γ�ID\t\t�ɼ�" << endl;
      for (Grade &grade : grades)
        cout << grade.course << "\t" << grade.grade << endl;
    }
  }
  else
    cout << "��ѧ��������" << endl;

  Utils::PauseAndCls();
}

void GradeManager::queryByCourseId()
{
  cout << "------��ѯ�γ̳ɼ��ɼ����------" << endl;
  string courseId;
  cout << "������γ�ID:";
  cin >> courseId;
  if (JudgeCourseIdExist(courseId))
  {
    vector<Grade> grades = this->QueryGrade(courseId);
    if (grades.empty())
      cout << "�ÿγ̲������κγɼ�" << endl;
    else
    {
      cout << "IDΪ" << courseId << "�Ŀγ��и��ɼ�����������:" << endl;
      unordered_map<string, int> GradeMap;
      for (Grade &grade : grades)
        GradeMap[grade.grade]++;
      cout << "�ɼ�\t\t����" << endl;
      for (auto it = GradeMap.begin(); it != GradeMap.end(); it++)
        cout << it->first << "\t\t" << it->second << endl;
    }
  }
  else
    cout << "�ÿγ̲�����" << endl;

  Utils::PauseAndCls();
}

void GradeManager::queryClassFailStudent()
{
  cout << "------��ѯ�γ̲�����ѧ���ĳɼ����------" << endl;
  string className;
  cout << "������༶����:";
  cin >> className;
  vector<Grade> grades = this->QueryFailStudentByClassName(className);
  if (grades.empty())
    cout << "�ð༶�������κ�ѧ����ð༶û�в��ϸ��߻򲻴��ڸð༶" << endl;
  else
  {
    cout << "�༶����Ϊ " << className << " �в�����ѧ���ĳɼ�������:" << endl;
    cout << "ѧ��ID\t\t�γ�ID\t\t�ɼ�" << endl;
    for (Grade &grade : grades)
      cout << grade.id << "\t" << grade.course << "\t" << grade.grade << endl;
  }
  Utils::PauseAndCls();
}

void GradeManager::queryGradeStudentCountByCourseId()
{
  cout << "------��ѯ�γ̳ɼ����------" << endl;
  string courseId;
  cout << "������γ�ID:";
  cin >> courseId;
  if (JudgeCourseIdExist(courseId))
  {
    vector<Grade> grades = this->QueryGrade(courseId);
    if (grades.empty())
      cout << "�ÿγ̲������κγɼ�" << endl;
    else
    {
      cout << "�γ�IDΪ " << courseId << " �Ŀγ��и��ɼ���������ٷֱ�����:" << endl;
      unordered_map<string, int> GradeMap;
      int count = 0;
      for (Grade &grade : grades)
      {
        GradeMap[grade.grade]++;
        count++;
      }
      cout << "�ɼ�\t\t����\t\t�ٷֱ�" << endl;
      for (auto it = GradeMap.begin(); it != GradeMap.end(); it++)
        cout << it->first << "\t\t" << it->second << "\t\t" << (it->second * 1.0 / count * 100) << "%" << endl;
    }
  }
  else
    cout << "�ÿγ̲�����" << endl;

  Utils::PauseAndCls();
}

GradeManager::GradeManager(CourseManager &C, StudentManager &S) : courseManager(C), studentManager(S)
{
  this->grades = ParseString2Vector(this->ReadDB());
}
