#ifndef DATA_HEAD
#define DATA_HEAD
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "sqlite3.h"
using std::string;using std::vector;using std::ofstream;using std::ifstream;
//sqlite3_stmt *stm;

unsigned int CharListConvertToUnsignedInt(const unsigned char * input);//hex to int
class OpenDBFile//open sqlite file
{
public:
	bool OpenFile();
};
class InitData
{
public:
	InitData();
	~InitData();
};
class GetData
{
private:
	string CharListConvertToString(const unsigned char * input);
	void ToUserInfoLinkedList();
	void ToAdminInfoList();
public :
	//static int callback(void * NoUse,int ColNum,char ** ColValue,char ** ColName);
	bool ToLinkedList();
};
class OperaData
{
private:
	string IntConvertToHex(unsigned int &input);//int to hex
public:
	bool AddUser(const long &id,const string &name,unsigned *code_sha1,const double &balance);//

	bool ReadAdminCodeSha1Value(unsigned int * code);

	bool JudgeUserIDExist(long & id);
	bool JudgeUserNameExist(const string &name,long &id);

	bool ReadUserIDList(vector<long> &id_list);
	bool ReadUserLastID(long & last_id);
	bool ReadUserCodeSha1Value(const long &id,unsigned int * code);
	bool ReadUserEnableValue(const long &id,bool &enable);
	bool ReadUserBalanceValue(const long &id,double &balance);
	bool ReadUserNameValue(const long &id,string &name);

	bool ChangeUserCodeSha1Value(const long &id,unsigned int * new_code);
	bool ChangeUserBalanceValue(const long &id,const double &money,const bool &I_OR_O);//1Îª´æ(in)£¬0ÎªÈ¡(out)
	bool ChangeUserEnableValue(const long &id,const bool &enable);

	bool DeleteUser(const long &id);
	//void testAddUser();
	//void testConvert();
};
class ExportData
{
public:
	bool WriteDataFile(const string &filename);
};
class ImportData
{
public:
	bool ReadDataFile(const string &filename);
};
#endif