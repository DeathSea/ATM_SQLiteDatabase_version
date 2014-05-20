#include "Views.h"
#include <iomanip>
using namespace std;
OutputText::OutputText()
{
	//���˵���ʼ��
	MainMenu[0]  = "ATM";
	MainMenu[1]  = "ǰ̨";
	MainMenu[2]  = "�˳�";
	//ATM�˵���ʼ��
	ATMMenu[0]   = "��ѯ���";
	ATMMenu[1]   = "ȡ��";
	ATMMenu[2]   = "���";
	ATMMenu[3]   = "ת��";
	ATMMenu[4]   = "�޸�����";
	ATMMenu[5]   = "�˳�";
	//ǰ̨�˵���ʼ��
	AdminMenu[0] = "�����û�";
	AdminMenu[1] = "�����û�";
	AdminMenu[2] = "�����û�";
	AdminMenu[3] = "�����û�";
	AdminMenu[4] = "��ѯ�����û�";
	AdminMenu[5] = "��ѯָ���û�";
	AdminMenu[6] = "�û�ȡ��";
	AdminMenu[7] = "�û����";
	AdminMenu[8] = "�û��޸�����";
	AdminMenu[9] = "�˳�";
	//��ʼ����ȡ�û������˵�
	UserInfoMethod[0] = "id";
	UserInfoMethod[1] = "�û���";
}
void OutputText::Prompt(const string pro)
{
	cout << pro << endl;
}
void OutputText::Prompt(double o)
{
	cout <<setiosflags(ios::fixed) << o << endl;
}
unsigned int OutputText::Menu(int Menu_Option)
{
	OutputText::Prompt("********************************");
	string * Menu = NULL;
	unsigned int array_length = 0;
	switch(Menu_Option)
	{
	case(0):
		Menu = MainMenu;
		array_length = 3;
		break;
	case(1):
		Menu = ATMMenu;
		array_length = 6;
		break;
	case(2):
		Menu = AdminMenu;
		array_length = 10;
		break;
	case(3):
		Menu = UserInfoMethod;
		array_length = 2;
	default:
		break;
	}
	if(Menu == NULL){OutputText::Prompt("�������з�����һ������λ��Views.cpp");return 9068;}
	for(int index=0;index != array_length;index++)
	{
		string cmend(19-((*(Menu+index)).size()),' ');
		cout << "*         " << index+1 << ".";
		cout << *(Menu+index) << cmend << "*";
		cout << endl;
	}
	OutputText::Prompt("********************************");
	cout << "���������ѡ��(1��" << array_length << "):";
	cout.clear();
	return array_length;
}
int InputText::Choice(int Menu_length)// throw(out_of_range)
{
	int Choice = 0;
	cin >> Choice;
	if(Choice <= Menu_length){return Choice-1;}
	else{throw out_of_range("ѡ�񳬳���Χ��");}
}
void OutputText::CardID(void)
{
	OutputText::Prompt("�����뿨��:");
}
void InputText::CardID(long * card_id)
{
    cin >> *card_id;
}
void OutputText::Code()
{
	OutputText::Prompt("����������:");
}
void InputText::Code(char * code)
{
	unsigned int index = 0;
	bool get_input = true;
	char input;
	while(get_input)
	{
		input = _getch();
		switch(input)
		{
		case 13:
			get_input = false;
			break;
		case 8:
			if(index > 0){index--;cout << "\b \b";}
			break;
		case 10:
			break;
		default:
			_putch('*');
			code[index] = input;
			index ++;
		}
	}
	cout << endl;
}
void OutputText::AdminName(void)
{
	OutputText::Prompt("�������̨�û���");
}
void OutputText::UserName()
{
	OutputText::Prompt("�������û���");
}
void InputText::AdminName(string * in)
{
	cin >> *in;
}
bool InputText::Confirm()
{
	char in = '\0';
	cin >> in;
	switch(in)
	{
	case 'Y':case 'y':
		return true;
	case 'N':case 'n':
		return false;
	default:
		cout << "δ֪ѡ��!���򼴽��˳���" << endl;
		system("pause");
		exit(1365);
	}
}
void OutputText::Confirm(const string O)
{
	cout << "��ȷ��Ҫ" << O << "��(Y/N)" << endl;
}
void OutputText::Money()
{
	OutputText::Prompt("�������������ң�");
}
void InputText::Money(int &input)
{
	double tmp;
	cin >> tmp;
	if(tmp > 0)
	{
		if((int)tmp%100 == 0)
		{
		    input = tmp;
		}
		else{throw runtime_error("��������������");}
	}
	else{throw runtime_error("����������!");}
}
void InputText::Money(double &money)
{
	double tmp;
	cin >> tmp;
	if(tmp > 0)
	{
		money = tmp;
	}
	else{throw runtime_error("����������!");}
}
void OutputText::UserInfo()
{
	OutputText::Prompt("�û�id    �û���    ���        �˺�״̬");
}
void OutputText::UserInfo(const long &id,const string &name,const double &balance,const bool &Enable)
{
	string sp(10-name.size(),' ');
	cout << left;
	cout << setw(10)<< id << setw(10) << name << showpoint <<balance << "     " << (Enable?"����ʹ��":"�ѱ�����") << endl;
}
void InputText::FileName(string &filename)
{
     cin >> filename;
}