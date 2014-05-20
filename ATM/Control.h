/*
控制层（Control Layer）
Designed by DeathSea 2014 Jnu
程序主要逻辑
*/

#ifndef CONTROL_HEAD
#define CONTROL_HEAD
#include <stdexcept>
#include "Views.h"
#include "Data.h"
#include "helper.h"
class Start
{
private:
	OutputText OutputText;
	InputText  InputText;
public:
	void start(bool clear);
	unsigned make_choice(unsigned Menu_option);
	void ATM_choice(long &);
	void Admin_choice();
};
class ATM
{
private:
	friend class Admin;
	OutputText OutputText;
	InputText  InputText;
	OperaData  OD;
	Start Start;
	helper helper;
public:
	bool Login(long &card_id);
	void UserBalance(long &id);//查询余额
	void Withdrawal(long &id,bool Admin_or_not);//#取款
	void Deposit(long &id,bool Admin_or_not);//#存款
	void Transfer(long &id);//#转账
	void ChangeCode(); 
};
class Admin:public ATM
{        
public:
	bool Login();
	void AddUser();
	void ExportUser();
	void ImportUser();
	void InquiryAllUserInfo();
	void InquiryNominatedUserInfo();
	void ChangeCode(long &id);
	bool GetID(long &id);
	void UnEnableUser();
};
#endif