//
/*
����㣨View Layer��
Designed by DeathSea 2014 Jnu
�ṩ�ı���������������
*/
#ifndef VIEW_HEAD
#define VIEW_HEAD
#include <iostream>
#include <string>
#include <locale>
#include <iterator>
#include <stdexcept>
#include <conio.h>
using std::string;
class OutputText
{
private:
	string MainMenu[3];
	string ATMMenu[6];
	string AdminMenu[10];
	string UserInfoMethod[2];
public:
	OutputText();
	unsigned int Menu(int Menu_Option);//��ӡ�˵�������ֵ0,1,2�ֱ�Ϊ���˵���ATM�˵�,ǰ̨�˵�
	void CardID(void);//��ӡ���뿨�ŵ���ʾ
	void Code();//��ӡ�����������ʾ
	void Money();//��ӡ����Ǯ������ʾ
	void Prompt(const string pro);//��ʾ
	void Prompt(double);
	void Confirm(const string con);//ȷ��
	void ChangeCode();//��ӡ�޸��������ʾ
	void AdminName();//��ӡ����admin������Ϣ
	void UserName();
	void AddUser();//��ӡ�����û�����Ϣ
	void UserInfo(const long &id,const string &name,const double &balance,const bool &Enable);//��ӡ�û���Ϣ
	void UserInfo();
};
class InputText
{
private:
	OutputText OutputText;
public:
	int Choice(int Menu_length);//��ȡ�û�����//�����û�ѡ��//����˵�����
	void CardID(long * card_id);//����û��û�����
	void AdminName(string * in);//��ȡadmin��
	void Code(char * code);//��ȡ����
	void Money(int &);//��ȡǮ��
	void Money(double &);
	void FileName(string &filename);//��ȡ�ļ�·��
	//void UserName();//��ȡ�û���
	bool Confirm();
};
#endif