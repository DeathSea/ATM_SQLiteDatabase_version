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
		OutputText.Prompt("δ֪ѡ����򼴽��˳���");
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
		OutputText.Prompt("δ֪ѡ����򼴽��˳���");
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
		OutputText.Prompt("δ֪ѡ����򼴽��˳���");
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
		OutputText.Prompt("����δ�ҵ�������һ��");
		try_time++;
		if(try_time == 3)
		{
			OutputText.Prompt("���Դ����������Σ�");
			Start.start(false);
			return false;
			break;
		}
	    OutputText.CardID();
	    InputText.CardID(&card_id);
	}
	bool enable =false;
	OD.ReadUserEnableValue(card_id,enable);
	if(!enable){OutputText.Prompt("�˺�������������ϵ����Ա");return false;}
	id = card_id;
	try_time = 0;
	OutputText.Code();
	InputText.Code(code);
	while(!helper.check(code,database_sha1))
	{
		OutputText.Prompt("�������");
		try_time ++;
		if (try_time==3)
		{
			OutputText.Prompt("���Դ����������Σ��˺�������������̨��������꣡");
			OD.ChangeUserEnableValue(card_id,false);//�˺�����
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
		OutputText.Prompt("�û�������");
		try_time ++;
		if(try_time == 3)
		{
			OutputText.Prompt("�������δ��󣡳��򼴽��˳�");
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
		OutputText.Prompt("�������");
		try_time++;
		if (try_time==3)
		{
			OutputText.Prompt("�����������δ��󣡣����򼴽��˳�");
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
		std::cout<< err.what() << std::endl << "���򼴽��˳�" << std::endl;
		system("pause");
		exit(1538);
	}
	return Choice;
}
void ATM::UserBalance(long &id)
{
	double balance = 0;
	OD.ReadUserBalanceValue(id,balance);
	OutputText.Prompt("������Ϊ:");
	OutputText.Prompt(balance);
}
void ATM::Withdrawal(long &id,bool Admin_or_not)
{
	bool enable = false;OD.ReadUserEnableValue(id,enable);
	if(!enable){OutputText.Prompt("�˺��ѱ�����������ϵ����Ա!");return ;}
	double money=0;
	if(!Admin_or_not){OutputText.Prompt("ע�⣺ȡ��ֻ֧������ȡ��");}
	OutputText.Confirm("ȡ��");
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
			std::cout<<"�������"<<money<<"Ԫ�������ú�"<<std::endl;
		}
		else{OutputText.Prompt("���㣡");}
	}
}
void ATM::Deposit(long &id,bool Admin_or_not)
{
	bool enable = false;OD.ReadUserEnableValue(id,enable);
	if(!enable){OutputText.Prompt("�˺��ѱ�����������ϵ����Ա!");return ;}
	double money=0;
	if(!Admin_or_not){OutputText.Prompt("ע�⣺���ֻ֧�����٣�");}
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
	std::cout<<"�Ѵ���"<<money<<"Ԫ��"<<std::endl;
}
void ATM::Transfer(long &id)
{
	bool enable = false;OD.ReadUserEnableValue(id,enable);
	if(!enable){OutputText.Prompt("�˺��ѱ�����������ϵ����Ա!");return ;}
    double money = 0,balance = 0;
	long target_id = 0;
	OutputText.Confirm("ת��");
	if(!InputText.Confirm()){return;};
	OutputText.Prompt("������Է�����");
	InputText.CardID(&target_id);
	if(!OD.JudgeUserIDExist(target_id))
	{
		OutputText.Prompt("���Ų�����");
		return;
	}
	OutputText.Money();
	InputText.Money(money);
	OD.ReadUserBalanceValue(id,balance);
	if (money > balance){OutputText.Prompt("�������");return;}
	else
	{
		OD.ChangeUserBalanceValue(id,money,0);
		OD.ChangeUserBalanceValue(target_id,money,1);
		OutputText.Prompt("ת�˳ɹ���");
	}
}
void ATM::ChangeCode(){OutputText.Prompt("ATM��֧���޸������˵��");}
bool Admin::GetID(long &id)
{
	unsigned database_sha1[5],try_time = 0;char code[255] = {'\0'};
	long id_tmp;
	OutputText.Prompt("������Ҫ�����Ŀ���");
	InputText.CardID(&id_tmp);
	if(!OD.JudgeUserIDExist(id_tmp))
	{
		OutputText.Prompt("����δ�ҵ�������ȷ��");
		return false;
	}
	OD.ReadUserCodeSha1Value(id_tmp,database_sha1);
	OutputText.Code();
	InputText.Code(code);
	while(!helper.check(code,database_sha1))
	{
		OutputText.Prompt("�������");
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
	OutputText.Confirm("�޸�����");
	if(!InputText.Confirm()){return ;}
	OD.ReadUserCodeSha1Value(id,sha1);
	OutputText.Prompt("������ԭ�������ٴ�ȷ�ϣ�");
	InputText.Code(origin_code);
	OutputText.Prompt("��֤��...���Ժ�");
	if(!helper.check(origin_code,sha1)){OutputText.Prompt("ԭ����������ٴμ�飡");return;}
	OutputText.Prompt("����Ҫ�޸ĵ����룺");
	InputText.Code(first_code_input);
	OutputText.Prompt("���ٴ��������룺");
	InputText.Code(second_code_input);
	while(strlen(first_code_input)!=strlen(second_code_input))
	{
		OutputText.Prompt("�������벻��ͬ��");
		trytime++;
		if(trytime == 3)
		{
			OutputText.Prompt("���Գ������Σ�����������˺���������");
			OD.ChangeUserEnableValue(id,false);
		}
		OutputText.Prompt("����Ҫ�޸ĵ����룺");
		InputText.Code(first_code_input);
		OutputText.Prompt("���ٴ��������룺");
		InputText.Code(second_code_input);
	} 
	trytime = 0;
	for(int i=0;first_code_input[i]!='\0';i++)
	{
		if(first_code_input[i]!=second_code_input[i])
		{
			OutputText.Prompt("�������벻��ͬ��");
			return;
		}
	}
	OutputText.Prompt("�����У����Ժ�");
	helper.calculate(first_code_input,new_sha);
	OD.ChangeUserCodeSha1Value(id,new_sha);
	OutputText.Prompt("�޸����");
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
	if (Choice == 0)//id����
	{
		OutputText.CardID();
		InputText.CardID(&id);
		if(!OD.JudgeUserIDExist(id))
		{
			OutputText.Prompt("ID�����ڣ���ȷ�ϣ�");
			return;
		}
	}
	else//�û�����ʽ
	{
		OutputText.UserName();
		InputText.AdminName(&name);
		if(!OD.JudgeUserNameExist(name,id))
		{
			OutputText.Prompt("�û��������ڣ���ȷ�ϣ�");
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
	OutputText.Confirm("����û�");
	long id = last_id+1;
	string name;
	char first_input_code[255] = {'\0'},second_input_code[255] = {'\0'};
	unsigned code_sha1[5];
	double balance;
	if(InputText.Confirm())
	{
		OutputText.Prompt("ϵͳ�Զ�����idΪ��");
		std::cout << id << std::endl;
		OutputText.Prompt("���ס����");
		//OutputText.CardID();
		//InputText.CardID(&id);
		OutputText.UserName();
		InputText.AdminName(&name);
		OutputText.Code();
		InputText.Code(first_input_code);
		OutputText.Prompt("���ٴ�����������ȷ��");
		InputText.Code(second_input_code);
		for(int i=0;first_input_code[i]!='\0';i++)
		{
			if(first_input_code[i]!=second_input_code[i])
			{
				OutputText.Prompt("�������벻��ͬ��");
				return;
			}
		}
		helper.calculate(first_input_code,code_sha1);
		OutputText.Prompt("Ԥ���Ϊ50ȷ����(Y/N):");
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
		OutputText.Prompt("��ӳɹ���");
	}
	else{return ;}
}
void Admin::ExportUser()
{
	string filename;
	ExportData ED;
	OutputText.Prompt("�������ļ���");
	InputText.FileName(filename);
	if(!helper.checkfilename(filename)){OutputText.Prompt("�ļ�������ȷ!");return;}
     else
     {
         if(ED.WriteDataFile(filename))
		 {OutputText.Prompt("��д��");}
		 else{OutputText.Prompt("д�����");}
     }
}
void Admin::ImportUser()
{
	string filename;
	ImportData ID;
	OutputText.Prompt("�������ļ���");
	InputText.FileName(filename);
	if(!helper.checkfilename(filename)){OutputText.Prompt("�ļ�������ȷ!");return;}
	else
	{
		if(ID.ReadDataFile(filename)){
			OutputText.Prompt("�Ѷ���");}
		else{OutputText.Prompt("�������");}
	}	
}
void Admin::UnEnableUser()
{
	long id_tmp;
	bool enable;
	char code[255] = {'\0'};
	unsigned int database_sha1[5];
	OutputText.Prompt("������Ҫ�����Ŀ���");
	InputText.CardID(&id_tmp);
	if(!OD.JudgeUserIDExist(id_tmp))
	{
		OutputText.Prompt("����δ�ҵ�������ȷ��");
		return;
	}
	OD.ReadUserEnableValue(id_tmp,enable);
	if(enable)
	{
		OutputText.Prompt("��Ŀ�δ�����������������");
		return;
	}
	OD.ReadUserCodeSha1Value(id_tmp,database_sha1);
	OutputText.Code();
	OutputText.Prompt("ע��ֻ��һ�λ��ᣬ�������û���Ϣ��");
	InputText.Code(code);
	if(!helper.check(code,database_sha1))
	{
		OD.DeleteUser(id_tmp);
    	OutputText.Prompt(">_<��������˺���ɾ����");
		return;
	}
	OD.ChangeUserEnableValue(id_tmp,true);
	OutputText.Prompt("�����ɹ���");
}