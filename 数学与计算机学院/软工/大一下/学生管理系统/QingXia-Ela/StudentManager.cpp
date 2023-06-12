#include "StudentManager.h"
#include "Utils.h"
#include <iostream>

string StudentManager::ReadDB()
{
  return Utils::ReadFile("StudentInfo.txt");
}

void StudentManager::WriteDB(string data)
{
  Utils::WriteFile("StudentInfo.txt", data);
}

string StudentManager::ParseStudentList2DBString(vector<Student> StudentList)
{
  string res;
  for (Student &stu : StudentList)
  {
    res += stu.ToString() + '\n';
  }
  return res;
}

vector<Student> StudentManager::ParseString2StudentList(string data)
{
  vector<Student> res;
  vector<string> arr = Utils::StringSplit(data, '\n');
  for (string &str : arr)
  {
    Student stu(str);
    res.push_back(stu);
  }
  return res;
}

bool StudentManager::JudgeExist(long long id)
{
  for (Student stu : this->StudentList)
    if (stu.id == id)
      return true;
  return false;
}

Student *StudentManager::query(long long id)
{
  for (Student &stu : this->StudentList)
    if (stu.id == id)
      return &stu;
  return nullptr;
}

void StudentManager::AddStudent(string data)
{
  Student stu(data);
  if (!JudgeExist(stu.id))
    this->StudentList.push_back(stu);
}

void StudentManager::AddStudent(long long id, string name, string gender, string age, string province, string major)
{
  Student stu(id, name, gender, age, province, major);
  if (!JudgeExist(stu.id))
  {
    this->StudentList.push_back(stu);
    this->WriteDB(this->ParseStudentList2DBString(this->StudentList));
  }
};

void StudentManager::DeleteStudent(long long id)
{
  for (int i = 0; i < this->StudentList.size(); i++)
    if (this->StudentList[i].id == id)
    {
      this->StudentList.erase(this->StudentList.begin() + i);
      this->WriteDB(this->ParseStudentList2DBString(this->StudentList));
      return;
    }
}

void StudentManager::ModifyStudent(Student stu)
{
  for (int i = 0; i < this->StudentList.size(); i++)
    if (this->StudentList[i].id == stu.id)
    {
      this->StudentList[i] = stu;
      this->WriteDB(this->ParseStudentList2DBString(this->StudentList));
      return;
    }
}

void StudentManager::PrintStudentInfo(long long id)
{
  bool exist = false;
  for (Student stu : this->StudentList)
    if (stu.id == id)
    {
      exist = true;
      cout << "IDΪ" << stu.id << "��ѧ����Ϣ����: " << endl;
      cout << "����:" << stu.name << endl;
      cout << "�Ա�:" << stu.gender << endl;
      cout << "����:" << stu.age << endl;
      cout << "ʡ��:" << stu.province << endl;
      cout << "רҵ:" << stu.major << endl;
      return;
    }

  if (!exist)
    cout << "������IDΪ" << id << "��ѧ��!" << endl;
}

void StudentManager::PrintStudentInfoWithLine(Student &stu, const char *spliter)
{
  cout << stu.id << spliter << stu.name << spliter << stu.gender << spliter << stu.age << spliter << stu.province << spliter << stu.major << endl;
}

vector<Student> StudentManager::JudgeStudent(string subName, string gender, string age, string subProvince, string subMajor)
{
  vector<Student> res;

  for (Student stu : this->StudentList)
  {
    if (stu.name.find(subName) != string::npos)
    {
      if (stu.gender.find(gender) != string::npos)
      {
        if (stu.age.find(age) != string::npos)
        {
          if (stu.province.find(subProvince) != string::npos)
          {
            if (stu.major.find(subMajor) != string::npos)
            {
              res.push_back(stu);
            }
          }
        }
      }
    }
  }

  return res;
}

void StudentManager::add()
{
  long long id;
  string name;
  string gender;
  string age;
  string province;
  string major;
  cout << "-----���ѧ����Ϣ-----" << endl;
  id = stoll(Utils::GetValidInput("������ѧ��ID(12λ����): ", Student::validateId));
  if (JudgeExist(id))
  {
    cout << "��ѧ���Ѵ���!" << endl;
    Utils::PauseAndCls();
    return;
  }
  name = Utils::GetValidInput("������ѧ������(������20���ַ�): ", Student::validateName);
  gender = Utils::GetValidInput("������ѧ���Ա�(��/Ů/M/F): ", Student::validateGender);
  age = Utils::GetValidInput("������ѧ������(2λ����): ", Student::validateAge);
  province = Utils::GetValidInput("������ѧ��ʡ��: ", Student::validateProvince);
  major = Utils::GetValidInput("������ѧ��רҵ(������8���ַ�): ", Student::validateMajor);

  AddStudent(id, name, gender, age, province, major);
  cout << "��ӳɹ�!" << endl;
  Utils::PauseAndCls();
}

void StudentManager::del()
{
  cout << "-----ɾ��ѧ����Ϣ-----" << endl;
  long long id;
  id = stoll(Utils::GetValidInput("������Ҫɾ����ѧ��ID: ", Student::validateId));
  if (JudgeExist(id))
  {
    PrintStudentInfo(id);
    if (Utils::JudgeChoose("�Ƿ�ɾ��ѧ����Ϣ?"))
    {
      DeleteStudent(id);
      cout << "ɾ���ɹ�!" << endl;
    }
    else
      cout << "��ȡ��ɾ������" << endl;
  }
  else
    cout << "������IDΪ" << id << "��ѧ��!" << endl;
  Utils::PauseAndCls();
}

void StudentManager::modify()
{
  cout << "-----�޸�ѧ����Ϣ-----" << endl;
  long long id;
  string name;
  string gender;
  string age;
  string province;
  string major;

  id = stoll(Utils::GetValidInput("������Ҫ�޸ĵ�ѧ��ID: ", Student::validateId));

  if (JudgeExist(id))
  {
    PrintStudentInfo(id);
    if (Utils::JudgeChoose("�Ƿ��޸�ѧ����Ϣ?"))
    {
      name = Utils::GetValidInput("������ѧ������(������20���ַ�): ", Student::validateName);
      gender = Utils::GetValidInput("������ѧ���Ա�(��/Ů/M/F): ", Student::validateGender);
      age = Utils::GetValidInput("������ѧ������(2λ����): ", Student::validateAge);
      province = Utils::GetValidInput("������ѧ��ʡ��: ", Student::validateProvince);
      major = Utils::GetValidInput("������ѧ��רҵ(������8���ַ�): ", Student::validateMajor);

      Student stu(id, name, gender, age, province, major);
      ModifyStudent(stu);
      cout << "�޸ĳɹ�!" << endl;
    }
    else
      cout << "��ȡ���޸�" << endl;
  }
  else
    cout << "������IDΪ" << id << "��ѧ��!" << endl;
  Utils::PauseAndCls();
}

void StudentManager::query()
{
  cout << "-----��ѯѧ����Ϣ-----" << endl;
  long long id;
  id = stoll(Utils::GetValidInput("������Ҫ��ѯ��ѧ��ID: ", Student::validateId));
  PrintStudentInfo(id);
  Utils::PauseAndCls();
}

void StudentManager::queryWithCondition()
{
  cout << "------��������ѯѧ����Ϣ------" << endl;

  string subName;
  string gender;
  string age;
  string subMajor;
  string subProvince;

  string temp;

  cout << "����������������Ϣ������#��ʾ��������Ϊ��ѯ����: \n\n";

  cout << "������ѧ������(�Ӵ�����): ";
  cin >> temp;
  if (temp != "#")
    subName = temp;

  cout << "������ѧ���Ա�: ";
  cin >> temp;
  if (temp != "#")
    gender = temp;

  cout << "������ѧ������: ";
  cin >> temp;
  if (temp != "#")
    age = temp;

  cout << "������ѧ��רҵ(�Ӵ�����): ";
  cin >> temp;
  if (temp != "#")
    subMajor = temp;

  cout << "������ѧ��ʡ��(�Ӵ�����): ";
  cin >> temp;
  if (temp != "#")
    subProvince = temp;

  vector<Student> res = this->JudgeStudent(subName, gender, age, subProvince, subMajor);

  if (res.empty())
  {
    cout << "û�в�ѯ������������ѧ����Ϣ!" << endl;
    Utils::PauseAndCls();
    return;
  }

  cout << "����ѯ��" << res.size() << "������������ѧ����Ϣ!\n"
       << endl;

  cout << "ѧ��ID\t\t����\t�Ա�\t����\tʡ��\tרҵ" << endl;
  for (auto stu : res)
    PrintStudentInfoWithLine(stu, "\t");

  Utils::PauseAndCls();
}

StudentManager::StudentManager()
{
  this->StudentList = ParseString2StudentList(ReadDB());
}