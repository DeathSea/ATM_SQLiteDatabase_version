#include "control.h"

void Start::start(bool clear)
{
	if(clear){system("cls");}
	ATM ATM;Admin Admin;
	enum Menu {MainMenu,ATMMenu,AdminMenu};
	unsigned int Menu_length = 0;
	unsigned int Choice = 0;
	bool login=false,ATM_login = false,admin_login = false;
	long id = -1;
	Choice = Start::make_choice(MainMenu);
	switch(Choice)
	{
	case (0):
		system("cls");
		ATM_login = ATM.Login(id);
		break;
	case(1):
		system("cls");
		admin_login = Admin.Login();
		break;
	case(2):
		exit(0);
	default:
		OutputText.Prompt("未知选项！程序即将退出！");
		system("pause");
		exit(1365);
	}
	if(ATM_login)
	{
    	system("cls");
		Start::ATM_choice(id);
	}
	if(admin_login)
	{
    	system("cls");
		Start::Admin_choice();
	}
	else
	{
		Start::start(false);
	}
}
void Start::ATM_choice(long &id)
{
	ATM ATM;
	unsigned int Choice      = 0;
	Choice = Start::make_choice(1);
	switch(Choice)
	{
	case(0):
		ATM.UserBalance(id);
		Start::ATM_choice(id);
		break;
	case(1):
		ATM.Withdrawal(id,false);
		Start::ATM_choice(id);
		break;
	case(2):
		ATM.Deposit(id,false);
		Start::ATM_choice(id);
		break;
	case(3):
		ATM.Transfer(id);
		Start::ATM_choice(id);
		break;
	case(4):
		ATM.ChangeCode();
		Start::ATM_choice(id);
		break;
	case(5):
		Start::start(true);
	default:
		OutputText.Prompt("未知选项！程序即将退出！");
		system("pause");
		exit(1365);
	}
}
void Start::Admin_choice()
{
	Admin Admin;
	unsigned int Choice      = 0;
	long id = 0;
	Choice = Start::make_choice(2);
	switch(Choice)
	{
	case(0):
		Admin.AddUser();
		Start::Admin_choice();
		break;
	case(1):
	     Admin.ExportUser();
	     Start::Admin_choice();
		break;
	case(2):
	     Admin.ImportUser();
	     Start::Admin_choice();
		break;
	case(3):
		Admin.UnEnableUser();
		Start::Admin_choice();
		break;
	case(4):
		Admin.InquiryAllUserInfo();
		Start::Admin_choice();
		break;
	case(5):
		Admin.InquiryNominatedUserInfo();
		Start::Admin_choice();
		break;
	case(6):
		if(Admin.GetID(id))
		{
			Admin.Withdrawal(id,true);
		}
		Start::Admin_choice();
		break;
	case(7):
		if(Admin.GetID(id))
		{
			Admin.Deposit(id,true);
		}
		Start::Admin_choice();
		break;
	case(8):
		if(Admin.GetID(id))
		{
			Admin.ChangeCode(id);
		}
		Start::Admin_choice();
		break;
	case(9):
		Start::start(true);
	default:
		OutputText.Prompt("未知选项！程序即将退出！");
		system("pause");
		exit(1365);
	}
}
bool ATM::Login(long &id)
{
	long card_id;
	char code[255] = {'\0'};
	unsigned database_sha1[5],try_time = 0;
	OutputText.CardID();
	InputText.CardID(&card_id);
	while(!OD.ReadUserCodeSha1Value(card_id,database_sha1))
	{
		OutputText.Prompt("卡号未找到，请检查一遍");
		try_time++;
		if(try_time == 3)
		{
			OutputText.Prompt("尝试次数超过三次！");
			Start.start(false);
			return false;
			break;
		}
	    OutputText.CardID();
	    InputText.CardID(&card_id);
	}
	bool enable =false;
	OD.ReadUserEnableValue(card_id,enable);
	if(!enable){OutputText.Prompt("账号已锁定，请联系管理员");return false;}
	id = card_id;
	try_time = 0;
	OutputText.Code();
	InputText.Code(code);
	while(!helper.check(code,database_sha1))
	{
		OutputText.Prompt("密码错误");
		try_time ++;
		if (try_time==3)
		{
			OutputText.Prompt("尝试次数超过三次，账号已锁定，到后台解决吧少年！");
			OD.ChangeUserEnableValue(card_id,false);//账号锁定
			//Start.start();
			std::cout << std::endl;
			return false;
			break;
		}
		OutputText.Code();
		InputText.Code(code);
	}
		return true;
}
bool Admin::Login(void)
{
	string name;
	char code[255] = {'\0'};
	unsigned database_sha1[5],try_time = 0;
	OutputText.AdminName();
	InputText.AdminName(&name);
	while(name!="root")
	{
		OutputText.Prompt("用户名错误");
		try_time ++;
		if(try_time == 3)
		{
			OutputText.Prompt("输入三次错误！程序即将退出");
			system("pause");
			exit(5921);
			return false;
			break;
		}
		OutputText.AdminName();
		InputText.AdminName(&name);
	}
	OD.ReadAdminCodeSha1Value(database_sha1);
	try_time = 0;
	OutputText.Code();
	InputText.Code(code);
	while(!helper.check(code,database_sha1))
	{
		OutputText.Prompt("密码错误！");
		try_time++;
		if (try_time==3)
		{
			OutputText.Prompt("密码输入三次错误！，程序即将退出");
			system("pause");
			exit(5923);
			return false;
			break;
		}
		OutputText.Code();
		InputText.Code(code);
	}
	return true;
}
unsigned Start::make_choice(unsigned Menu)
{
	unsigned int Menu_length = 0;
	unsigned int Choice      = 0;
	Menu_length = OutputText.Menu(Menu);
	try
	{
		Choice      = InputText.Choice(Menu_length);
	}
	catch(std::out_of_range err)
	{
		std::cout<< err.what() << std::endl << "程序即将退出" << std::endl;
		system("pause");
		exit(1538);
	}
	return Choice;
}
void ATM::UserBalance(long &id)
{
	double balance = 0;
	OD.ReadUserBalanceValue(id,balance);
	OutputText.Prompt("你的余额为:");
	OutputText.Prompt(balance);
}
void ATM::Withdrawal(long &id,bool Admin_or_not)
{
	bool enable = false;OD.ReadUserEnableValue(id,enable);
	if(!enable){OutputText.Prompt("账号已被锁定，请联系管理员!");return ;}
	double money=0;
	if(!Admin_or_not){OutputText.Prompt("注意：取款只支持整百取款");}
	OutputText.Confirm("取款");
	bool Yes_or_No = InputText.Confirm();
    double balance = 0;
	if (!Yes_or_No){return ;}
	else
	{
		OutputText.Money();
		try
		{		
			if(!Admin_or_not){int m = 0;InputText.Money(m);money = (double)m;}
			else{InputText.Money(money);}
			OD.ReadUserBalanceValue(id,balance);
		}
		catch(std::runtime_error err)
		{
			std::cout << err.what() << std::endl;
			return;
		}
		if(balance > money)
		{
			OD.ChangeUserBalanceValue(id,money,0);
			std::cout<<"这是你的"<<money<<"元整，请拿好"<<std::endl;
		}
		else{OutputText.Prompt("余额不足！");}
	}
}
void ATM::Deposit(long &id,bool Admin_or_not)
{
	bool enable = false;OD.ReadUserEnableValue(id,enable);
	if(!enable){OutputText.Prompt("账号已被锁定，请联系管理员!");return ;}
	double money=0;
	if(!Admin_or_not){OutputText.Prompt("注意：存款只支持整百！");}
	OutputText.Money();
	try
	{
		if(!Admin_or_not){int m = (int)money;InputText.Money(m);money = (double)m;}
		else{InputText.Money(money);}
	}
	catch(std::runtime_error err)
	{
		std::cout << err.what() << std::endl;
		return;
	}
	OD.ChangeUserBalanceValue(id,money,1);
	std::cout<<"已存入"<<money<<"元整"<<std::endl;
}
void ATM::Transfer(long &id)
{
	bool enable = false;OD.ReadUserEnableValue(id,enable);
	if(!enable){OutputText.Prompt("账号已被锁定，请联系管理员!");return ;}
    double money = 0,balance = 0;
	long target_id = 0;
	OutputText.Confirm("转账");
	if(!InputText.Confirm()){return;};
	OutputText.Prompt("请输入对方卡号");
	InputText.CardID(&target_id);
	if(!OD.JudgeUserIDExist(target_id))
	{
		OutputText.Prompt("卡号不存在");
		return;
	}
	OutputText.Money();
	InputText.Money(money);
	OD.ReadUserBalanceValue(id,balance);
	if (money > balance){OutputText.Prompt("你的余额不足");return;}
	else
	{
		OD.ChangeUserBalanceValue(id,money,0);
		OD.ChangeUserBalanceValue(target_id,money,1);
		OutputText.Prompt("转账成功！");
	}
}
void ATM::ChangeCode(){OutputText.Prompt("ATM不支持修改密码的说！");}
bool Admin::GetID(long &id)
{
	unsigned database_sha1[5],try_time = 0;char code[255] = {'\0'};
	long id_tmp;
	OutputText.Prompt("请输入要操作的卡号");
	InputText.CardID(&id_tmp);
	if(!OD.JudgeUserIDExist(id_tmp))
	{
		OutputText.Prompt("卡号未找到请重新确认");
		return false;
	}
	OD.ReadUserCodeSha1Value(id_tmp,database_sha1);
	OutputText.Code();
	InputText.Code(code);
	while(!helper.check(code,database_sha1))
	{
		OutputText.Prompt("密码错误！");
		try_time++;
		if (try_time==3)
		{
			return false;
			break;
		}
		OutputText.Code();
		InputText.Code(code);
	}
	id = id_tmp;
	return true;
}
void Admin::ChangeCode(long &id)
{   
	char origin_code[256]={'\0'},first_code_input[256]={'\0'},second_code_input[256]={'\0'};
	unsigned sha1[5],trytime = 0,new_sha[5];bool uncorrect = true;
	OutputText.Confirm("修改密码");
	if(!InputText.Confirm()){return ;}
	OD.ReadUserCodeSha1Value(id,sha1);
	OutputText.Prompt("请输入原密码以再次确认：");
	InputText.Code(origin_code);
	OutputText.Prompt("验证中...请稍候");
	if(!helper.check(origin_code,sha1)){OutputText.Prompt("原密码错误！请再次检查！");return;}
	OutputText.Prompt("输入要修改的密码：");
	InputText.Code(first_code_input);
	OutputText.Prompt("请再次输入密码：");
	InputText.Code(second_code_input);
	while(strlen(first_code_input)!=strlen(second_code_input))
	{
		OutputText.Prompt("两次密码不相同！");
		trytime++;
		if(trytime == 3)
		{
			OutputText.Prompt("尝试超过三次，恶意操作，账号已锁定！");
			OD.ChangeUserEnableValue(id,false);
		}
		OutputText.Prompt("输入要修改的密码：");
		InputText.Code(first_code_input);
		OutputText.Prompt("请再次输入密码：");
		InputText.Code(second_code_input);
	} 
	trytime = 0;
	for(int i=0;first_code_input[i]!='\0';i++)
	{
		if(first_code_input[i]!=second_code_input[i])
		{
			OutputText.Prompt("两次密码不相同！");
			return;
		}
	}
	OutputText.Prompt("处理中，请稍候");
	helper.calculate(first_code_input,new_sha);
	OD.ChangeUserCodeSha1Value(id,new_sha);
	OutputText.Prompt("修改完成");
	return;
}
void Admin::InquiryAllUserInfo()
{
	vector<long> id_list;
	OD.ReadUserIDList(id_list);
	auto list_size = id_list.size();
	decltype(list_size) index = 0;
	string name;double balance;bool enable;
	OutputText.UserInfo();
	for(;index!=list_size;index++)
	{
		OD.ReadUserNameValue(id_list[index],name);
		OD.ReadUserBalanceValue(id_list[index],balance);
		OD.ReadUserEnableValue(id_list[index],enable);
		OutputText.UserInfo(id_list[index],name,balance,enable);
	}
}
void Admin::InquiryNominatedUserInfo()
{
	int Choice = 0,length = OutputText.Menu(3);
	long id = 0;double balance;bool enable;
	string name;
	Choice = InputText.Choice(length);
	if (Choice == 0)//id方法
	{
		OutputText.CardID();
		InputText.CardID(&id);
		if(!OD.JudgeUserIDExist(id))
		{
			OutputText.Prompt("ID不存在！请确认！");
			return;
		}
	}
	else//用户名方式
	{
		OutputText.UserName();
		InputText.AdminName(&name);
		if(!OD.JudgeUserNameExist(name,id))
		{
			OutputText.Prompt("用户名不存在！请确认！");
			return;
		};
	}
	OD.ReadUserNameValue(id,name);
	OD.ReadUserBalanceValue(id,balance);
	OD.ReadUserEnableValue(id,enable);
	OutputText.UserInfo();
	OutputText.UserInfo(id,name,balance,enable);
	return;
}
void Admin::AddUser()
{
	long last_id = 0;
	OD.ReadUserLastID(last_id);
	OutputText.Confirm("添加用户");
	long id = last_id+1;
	string name;
	char first_input_code[255] = {'\0'},second_input_code[255] = {'\0'};
	unsigned code_sha1[5];
	double balance;
	if(InputText.Confirm())
	{
		OutputText.Prompt("系统自动分配id为：");
		std::cout << id << std::endl;
		OutputText.Prompt("请记住！！");
		//OutputText.CardID();
		//InputText.CardID(&id);
		OutputText.UserName();
		InputText.AdminName(&name);
		OutputText.Code();
		InputText.Code(first_input_code);
		OutputText.Prompt("请再次输入密码以确认");
		InputText.Code(second_input_code);
		for(int i=0;first_input_code[i]!='\0';i++)
		{
			if(first_input_code[i]!=second_input_code[i])
			{
				OutputText.Prompt("两次密码不相同！");
				return;
			}
		}
		helper.calculate(first_input_code,code_sha1);
		OutputText.Prompt("预存款为50确认吗？(Y/N):");
		if(InputText.Confirm()){balance = 50;}
		else
		{
			while(1)
			{
				OutputText.Money();
				try{
					InputText.Money(balance);
				}
				catch(std::runtime_error err)
				{
					std::cout << err.what() << std::endl;
					continue;
				}
				break;
			}
		}
		OD.AddUser(id,name,code_sha1,balance);
		OutputText.Prompt("添加成功！");
	}
	else{return ;}
}
void Admin::ExportUser()
{
	string filename;
	ExportData ED;
	OutputText.Prompt("请输入文件名");
	InputText.FileName(filename);
	if(!helper.checkfilename(filename)){OutputText.Prompt("文件名不正确!");return;}
     else
     {
         if(ED.WriteDataFile(filename))
		 {OutputText.Prompt("已写入");}
		 else{OutputText.Prompt("写入出错");}
     }
}
void Admin::ImportUser()
{
	string filename;
	ImportData ID;
	OutputText.Prompt("请输入文件名");
	InputText.FileName(filename);
	if(!helper.checkfilename(filename)){OutputText.Prompt("文件名不正确!");return;}
	else
	{
		if(ID.ReadDataFile(filename)){
			OutputText.Prompt("已读入");}
		else{OutputText.Prompt("读入出错");}
	}	
}
void Admin::UnEnableUser()
{
	long id_tmp;
	bool enable;
	char code[255] = {'\0'};
	unsigned int database_sha1[5];
	OutputText.Prompt("请输入要操作的卡号");
	InputText.CardID(&id_tmp);
	if(!OD.JudgeUserIDExist(id_tmp))
	{
		OutputText.Prompt("卡号未找到请重新确认");
		return;
	}
	OD.ReadUserEnableValue(id_tmp,enable);
	if(enable)
	{
		OutputText.Prompt("你的卡未被锁定，无需解锁！");
		return;
	}
	OD.ReadUserCodeSha1Value(id_tmp,database_sha1);
	OutputText.Code();
	OutputText.Prompt("注意只有一次机会，输错将清除用户信息！");
	InputText.Code(code);
	if(!helper.check(code,database_sha1))
	{
		OD.DeleteUser(id_tmp);
    	OutputText.Prompt(">_<密码错误！账号已删除！");
		return;
	}
	OD.ChangeUserEnableValue(id_tmp,true);
	OutputText.Prompt("解锁成功！");
}