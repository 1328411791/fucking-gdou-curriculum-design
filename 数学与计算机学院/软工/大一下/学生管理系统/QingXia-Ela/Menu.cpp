#include "Menu.h"
#include "Utils.h"
#include <iostream>
using namespace std;

bool JudgeContains(string s)
{
  return s.length() == 1 && s.find_first_not_of("01234") == string::npos;
}

void Menu::gotoCourseMenu()
{
  string choose;
  do
  {
    cout << "------�γ̹���------" << endl;
    cout << "1. ��ӿγ�" << endl;
    cout << "2. ɾ���γ�" << endl;
    cout << "3. �޸Ŀγ�" << endl;
    cout << "4. ��ѯ�γ�" << endl;
    cout << "0. �����ϼ��˵�" << endl;
    choose = Utils::GetValidInput("������ѡ��:", JudgeContains);
    system("cls");

    switch (choose[0])
    {
    case '1':
      courseManager.add();
      break;
    case '2':
      courseManager.del();
      break;
    case '3':
      courseManager.modify();
      break;
    case '4':
      courseManager.query();
      break;
    }
  } while (choose != "0");
}

bool JudgeStudentContains(string s)
{
  return s.length() == 1 && s.find_first_not_of("012345") == string::npos;
}
void Menu::gotoStudentMenu()
{
  string choose;
  do
  {
    cout << "------ѧ������------" << endl;
    cout << "1. ���ѧ��" << endl;
    cout << "2. ɾ��ѧ��" << endl;
    cout << "3. �޸�ѧ��" << endl;
    cout << "4. ��ѯѧ��" << endl;
    cout << "5. ��������ѯѧ��" << endl;
    cout << "0. �����ϼ��˵�" << endl;
    choose = Utils::GetValidInput("������ѡ��:", JudgeStudentContains);
    system("cls");

    switch (choose[0])
    {
    case '1':
      studentManager.add();
      break;
    case '2':
      studentManager.del();
      break;
    case '3':
      studentManager.modify();
      break;
    case '4':
      studentManager.query();
      break;
    case '5':
      studentManager.queryWithCondition();
    }
  } while (choose != "0");
}

bool JudgeGradeMenuContains(string s)
{
  return s.length() == 1 && s.find_first_not_of("012345678") == string::npos;
}
void Menu::gotoGradeMenu()
{
  string choose;
  do
  {
    cout << "------�ɼ�����------" << endl;
    cout << "1. ��ӳɼ�" << endl;
    cout << "2. ɾ���ɼ�" << endl;
    cout << "3. �޸ĳɼ�" << endl;
    cout << "4. ��ѯ�ɼ�" << endl;
    cout << "5. ����ѧ�Ų�ѯĳ��ѧ���ĸ��ſγ̵ĳɼ�" << endl;
    cout << "6. ���ݿγ̺Ų�ѯĳ�ſγ̵ĳɼ����" << endl;
    cout << "7. ��ѯĳ�༶������ѧ������" << endl;
    cout << "8. ͳ��ĳ�ſγ̸��ɼ�����������ٷֱ�" << endl;
    cout << "0. �����ϼ��˵�" << endl;
    choose = Utils::GetValidInput("������ѡ��:", JudgeGradeMenuContains);
    system("cls");

    switch (choose[0])
    {
    case '1':
      gradeManager.add();
      break;
    case '2':
      gradeManager.del();
      break;
    case '3':
      gradeManager.modify();
      break;
    case '4':
      gradeManager.query();
      break;
    case '5':
      gradeManager.queryByStudentId();
      break;
    case '6':
      gradeManager.queryByCourseId();
      break;
    case '7':
      gradeManager.queryClassFailStudent();
      break;
    case '8':
      gradeManager.queryGradeStudentCountByCourseId();
      break;
    }
  } while (choose != "0");
}

void Menu::gotoMainMenu()
{
  string choose;
  do
  {
    cout << "------��ӭʹ��ѧ���ɼ�����ϵͳ------" << endl;
    cout << "1. �γ̹���" << endl;
    cout << "2. ѧ������" << endl;
    cout << "3. �ɼ�����" << endl;
    cout << "4. �˳�ϵͳ" << endl;
    choose = Utils::GetValidInput("������ѡ��:", JudgeContains);
    system("cls");

    switch (choose[0])
    {
    case '1':
      gotoCourseMenu();
      break;
    case '2':
      gotoStudentMenu();
      break;
    case '3':
      gotoGradeMenu();
      break;
    case '4':
      gotoExitMenu();
      break;
    default:
      break;
    }
  } while (true);
}

void Menu::gotoExitMenu()
{
  if (Utils::JudgeChoose("ȷ���˳�ϵͳ?"))
    exit(0);
  system("cls");
}

void Menu::StartMenu()
{
  gotoMainMenu();
}