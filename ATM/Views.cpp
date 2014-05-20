#include "Views.h"
#include <iomanip>
using namespace std;
OutputText::OutputText()
{
	//主菜单初始化
	MainMenu[0]  = "ATM";
	MainMenu[1]  = "前台";
	MainMenu[2]  = "退出";
	//ATM菜单初始化
	ATMMenu[0]   = "查询余额";
	ATMMenu[1]   = "取款";
	ATMMenu[2]   = "存款";
	ATMMenu[3]   = "转账";
	ATMMenu[4]   = "修改密码";
	ATMMenu[5]   = "退出";
	//前台菜单初始化
	AdminMenu[0] = "增加用户";
	AdminMenu[1] = "导出用户";
	AdminMenu[2] = "导入用户";
	AdminMenu[3] = "解锁用户";
	AdminMenu[4] = "查询所有用户";
	AdminMenu[5] = "查询指定用户";
	AdminMenu[6] = "用户取款";
	AdminMenu[7] = "用户存款";
	AdminMenu[8] = "用户修改密码";
	AdminMenu[9] = "退出";
	//初始化读取用户方法菜单
	UserInfoMethod[0] = "id";
	UserInfoMethod[1] = "用户名";
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
	if(Menu == NULL){OutputText::Prompt("程序运行发生了一个问题位于Views.cpp");return 9068;}
	for(int index=0;index != array_length;index++)
	{
		string cmend(19-((*(Menu+index)).size()),' ');
		cout << "*         " << index+1 << ".";
		cout << *(Menu+index) << cmend << "*";
		cout << endl;
	}
	OutputText::Prompt("********************************");
	cout << "请输入你的选择(1至" << array_length << "):";
	cout.clear();
	return array_length;
}
int InputText::Choice(int Menu_length)// throw(out_of_range)
{
	int Choice = 0;
	cin >> Choice;
	if(Choice <= Menu_length){return Choice-1;}
	else{throw out_of_range("选择超出范围！");}
}
void OutputText::CardID(void)
{
	OutputText::Prompt("请输入卡号:");
}
void InputText::CardID(long * card_id)
{
    cin >> *card_id;
}
void OutputText::Code()
{
	OutputText::Prompt("请输入密码:");
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
	OutputText::Prompt("请输入后台用户名");
}
void OutputText::UserName()
{
	OutputText::Prompt("请输入用户名");
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
		cout << "未知选项!程序即将退出！" << endl;
		system("pause");
		exit(1365);
	}
}
void OutputText::Confirm(const string O)
{
	cout << "你确定要" << O << "吗？(Y/N)" << endl;
}
void OutputText::Money()
{
	OutputText::Prompt("请输入多少人民币：");
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
		else{throw runtime_error("请输入整百数！");}
	}
	else{throw runtime_error("请输入正数!");}
}
void InputText::Money(double &money)
{
	double tmp;
	cin >> tmp;
	if(tmp > 0)
	{
		money = tmp;
	}
	else{throw runtime_error("请输入正数!");}
}
void OutputText::UserInfo()
{
	OutputText::Prompt("用户id    用户名    余额        账号状态");
}
void OutputText::UserInfo(const long &id,const string &name,const double &balance,const bool &Enable)
{
	string sp(10-name.size(),' ');
	cout << left;
	cout << setw(10)<< id << setw(10) << name << showpoint <<balance << "     " << (Enable?"正常使用":"已被禁用") << endl;
}
void InputText::FileName(string &filename)
{
     cin >> filename;
}