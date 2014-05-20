#include "data.h"
#include "helper.h"
struct user_info
{
	long CardID;
	string user_name;
	unsigned code_sha1[5];
	double Balance;
	bool Enable;
	user_info * next;
} user_HEAD;
struct admin_user
{
	string Admin_name;
	unsigned code_sha1[5];
} admin_HEAD;
sqlite3 *conn;
unsigned int CharListConvertToUnsignedInt(const unsigned char * input)
{
	unsigned int ReturnInt;
	std::stringstream ss;
	ss << std::hex << input;
	ss >> ReturnInt;
	return ReturnInt;
}
bool OpenDBFile::OpenFile()
{
	if(sqlite3_open("ATM.db",&conn) == SQLITE_OK)
	{
		return true;
	}
	return false;
}
string GetData::CharListConvertToString(const unsigned char * input)
{
	//写法二：
	//std::string test(reinterpret_cast<char *>(const_cast<unsigned char *>(name)));
	string ReturnString;
	std::stringstream ss;
	ss << input;
	ss >> ReturnString;
	return ReturnString;
}
void GetData::ToUserInfoLinkedList()
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;
	struct user_info * p = &user_HEAD;
	sqlite3_prepare_v2(conn,"select * from user_info",-1,&st,&unused);
	sqlite3_step(st);
	while(1)
	{
		int ROW = sqlite3_data_count(st);
		if (ROW == 0)
		{
			break;
			std::cout << "数据库无数据" << std::endl;
			exit(1526);
			return;
		}
		long id = sqlite3_column_int(st,0);
		const unsigned char * name = sqlite3_column_text(st,1);		
		const unsigned char * sha1_0 = sqlite3_column_text(st,2);
		const unsigned char * sha1_1 = sqlite3_column_text(st,3);
		const unsigned char * sha1_2 = sqlite3_column_text(st,4);
		const unsigned char * sha1_3 = sqlite3_column_text(st,5);
		const unsigned char * sha1_4 = sqlite3_column_text(st,6);
		double balance = sqlite3_column_double(st,7);
		bool enable = static_cast<bool>(sqlite3_column_int(st,8));
		p->CardID       = id;
		p->user_name    = CharListConvertToString(name);
		p->code_sha1[0] = CharListConvertToUnsignedInt(sha1_0);
		p->code_sha1[1] = CharListConvertToUnsignedInt(sha1_1);
		p->code_sha1[2] = CharListConvertToUnsignedInt(sha1_2);
		p->code_sha1[3] = CharListConvertToUnsignedInt(sha1_3);
		p->code_sha1[4] = CharListConvertToUnsignedInt(sha1_4);
		p->Balance      = balance;
		p->Enable       = enable;
		p->next         = NULL;
		if(SQLITE_ROW == sqlite3_step(st))
		{
			p->next         = new struct user_info;
			p               = p->next;
			p->next         = NULL;
		}
		else{break;}
	}
	sqlite3_finalize(st);
	return;
}
void GetData::ToAdminInfoList()
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;
	int tp=0;
	tp = sqlite3_prepare_v2(conn,"select * from admin_info",-1,&st,&unused);
	tp = sqlite3_step(st);
	string admin_name;
	unsigned int sha1[5];
	admin_name = CharListConvertToString(sqlite3_column_text(st,0));
	sha1[0]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,1));
	sha1[1]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,2));
	sha1[2]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,3));
	sha1[3]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,4));
	sha1[4]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,5));
	admin_HEAD.Admin_name = admin_name;
	admin_HEAD.code_sha1[0] = sha1[0];
	admin_HEAD.code_sha1[1] = sha1[1];
	admin_HEAD.code_sha1[2] = sha1[2];
	admin_HEAD.code_sha1[3] = sha1[3];
	admin_HEAD.code_sha1[4] = sha1[4];
	tp = sqlite3_finalize(st);
	return;
}
bool GetData::ToLinkedList()
{
	GetData::ToUserInfoLinkedList();
	GetData::ToAdminInfoList();
	return true;
}
string OperaData::IntConvertToHex(unsigned int & input)
{
	string Hex; 
	std::stringstream ss;
	ss << std::hex << input;
	ss >> Hex;
	ss.clear();
	return Hex;
}
//void OperaData::testConvert()
//{
//	unsigned int iii=1072340962;
//	string hh = OperaData::IntConvertToHex(iii);
//	std::cout << hh << std::endl;
//}
/*void OperaData::testAddUser()
{
	unsigned int code[5];
	helper hp;
	hp.calculate("123456",code);
	OperaData::AddUser(5,"root",code,50);
}*/
bool OperaData::AddUser(const long &id,const string &name,unsigned *code_sha1,const double &balance)//test pass
{
	const char * unused = NULL;
	const char * sql = "insert into user_info values(:id,:name,:sha1_0,:sha1_1,:sha1_2,:sha1_3,:sha1_4,:balance,:enable);";
	sqlite3_stmt * st = NULL;
	sqlite3_prepare_v2(conn,sql,-1,&st,&unused);
	sqlite3_bind_int(st,1,id);
	sqlite3_bind_text(st,2,name.c_str(),-1, SQLITE_STATIC);
	sqlite3_bind_text(st,3,OperaData::IntConvertToHex(code_sha1[0]).c_str(),8, SQLITE_TRANSIENT);//函数返回不是const所以还是要用SQLITE_TRANSTENT
	sqlite3_bind_text(st,4,OperaData::IntConvertToHex(code_sha1[1]).c_str(),8, SQLITE_TRANSIENT);
	sqlite3_bind_text(st,5,OperaData::IntConvertToHex(code_sha1[2]).c_str(),8, SQLITE_TRANSIENT);
	sqlite3_bind_text(st,6,OperaData::IntConvertToHex(code_sha1[3]).c_str(),8, SQLITE_TRANSIENT);
	sqlite3_bind_text(st,7,OperaData::IntConvertToHex(code_sha1[4]).c_str(),8, SQLITE_TRANSIENT);
	sqlite3_bind_double(st,8,balance);
    sqlite3_bind_int(st,9,1);
	if(SQLITE_DONE != sqlite3_step(st))
	{ 
		//std::cout << "fail" <<  std::endl;
    	sqlite3_finalize(st);
		return false;
	}
	sqlite3_finalize(st);
	return true;
}
bool OperaData::ReadAdminCodeSha1Value(unsigned int * code)//test pass
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;
	if(sqlite3_prepare_v2(conn,"select sha1_0,sha1_1,sha1_2,sha1_3,sha1_4 from admin_info;",-1,&st,&unused)!=SQLITE_OK) return false;
	int tp = sqlite3_step(st);
	if(tp!=SQLITE_DONE && tp!=SQLITE_ROW) return false;
	code[0]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,0));
	code[1]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,1));
	code[2]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,2));
	code[3]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,3));
	code[4]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,4));
	sqlite3_finalize(st);
	return true;
}
bool OperaData::JudgeUserIDExist(long & id)
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;
	if(sqlite3_prepare_v2(conn,"select id from user_info where id=:id",-1,&st,&unused)!=SQLITE_OK) return false;
	sqlite3_bind_int(st,1,id);
	int tp = sqlite3_step(st);
	if((tp!=SQLITE_DONE) && (tp!=SQLITE_ROW)) return false;//
	if( sqlite3_data_count(st)==0) return false;//id不存在
	sqlite3_finalize(st);
	return true;
}
bool OperaData::JudgeUserNameExist(const string &name,long &id)
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;
	if(sqlite3_prepare_v2(conn,"select id from user_info where name=:name",-1,&st,&unused)!=SQLITE_OK) return false;
	sqlite3_bind_text(st,1,name.c_str(),-1,SQLITE_STATIC);
	int tp = sqlite3_step(st);
	if((tp!=SQLITE_DONE) && (tp!=SQLITE_ROW)) return false;//
	if( sqlite3_data_count(st)==0) return false;//id不存在
	id = sqlite3_column_int(st,0);
	sqlite3_finalize(st);
	return true;
}
bool OperaData::ReadUserIDList(vector<long> &id_list)
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;
	sqlite3_prepare_v2(conn,"select id from user_info",-1,&st,&unused);
	sqlite3_step(st);
	while(1)
	{
		long id = sqlite3_column_int(st,0);
		id_list.push_back(id);
		if(SQLITE_ROW != sqlite3_step(st))
		{
			break;
		}
	}
	sqlite3_finalize(st);
	return true;
}
bool OperaData::ReadUserLastID(long & last_id)//test pass
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;
	if(sqlite3_prepare_v2(conn,"select id from user_info order by id  desc limit 0,1;",-1,&st,&unused)!=SQLITE_OK) return false;
	int tp = sqlite3_step(st);
	if(tp!=SQLITE_DONE && tp!=SQLITE_ROW) return false;
	last_id = sqlite3_column_int(st,0);
	sqlite3_finalize(st);
	return true;
}
bool OperaData::ReadUserCodeSha1Value(const long &id,unsigned int * code)//test pass
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;
	if(sqlite3_prepare_v2(conn,"select sha1_0,sha1_1,sha1_2,sha1_3,sha1_4 from user_info where id=:id",-1,&st,&unused)!=SQLITE_OK) return false;
	sqlite3_bind_int(st,1,id);
	int tp = sqlite3_step(st);
	if((tp!=SQLITE_DONE) && (tp!=SQLITE_ROW)) return false;//
	//int sqlite3_column_count(sqlite3_stmt *pStmt);
	if( sqlite3_data_count(st)==0) return false;//id不存在
	code[0]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,0));
	code[1]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,1));
	code[2]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,2));
	code[3]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,3));
	code[4]    = CharListConvertToUnsignedInt(sqlite3_column_text(st,4));
	sqlite3_finalize(st);
	return true;
}
bool OperaData::ReadUserEnableValue(const long &id,bool &enable)//test pass
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;
	if(sqlite3_prepare_v2(conn,"select enable from user_info where id=:id",-1,&st,&unused)!=SQLITE_OK) return false;
	sqlite3_bind_int(st,1,id);
	int tp = sqlite3_step(st);
	if((tp!=SQLITE_DONE) && (tp!=SQLITE_ROW)) return false;//
	//int sqlite3_column_count(sqlite3_stmt *pStmt);
	if( sqlite3_data_count(st)==0) return false;//id不存在
	enable = sqlite3_column_int(st,0);
	sqlite3_finalize(st);
	return true;
}
bool OperaData::ReadUserBalanceValue(const long &id,double &balance)//test pass
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;
	if(sqlite3_prepare_v2(conn,"select balance from user_info where id=:id",-1,&st,&unused)!=SQLITE_OK) return false;
	sqlite3_bind_int(st,1,id);
	int tp = sqlite3_step(st);
	if((tp!=SQLITE_DONE) && (tp!=SQLITE_ROW)) return false;//
	//int sqlite3_column_count(sqlite3_stmt *pStmt);
	if( sqlite3_data_count(st)==0) return false;//id不存在
	balance = sqlite3_column_double(st,0);
	sqlite3_finalize(st);
	return true;
}

bool OperaData::ReadUserNameValue(const long &id ,string &name)//test pass
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;std::stringstream ss;
	if(sqlite3_prepare_v2(conn,"select name from user_info where id=:id",-1,&st,&unused)!=SQLITE_OK) return false;
	sqlite3_bind_int(st,1,id);
	int tp = sqlite3_step(st);
	if((tp!=SQLITE_DONE) && (tp!=SQLITE_ROW)) return false;//
	if( sqlite3_data_count(st)==0) return false;//id不存在
	ss << sqlite3_column_text(st,0);ss >> name;
	sqlite3_finalize(st);
	return true;
}
bool OperaData::ChangeUserCodeSha1Value(const long &id,unsigned int * code)// some problem
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;std::stringstream ss;
	if(sqlite3_prepare_v2(conn,"update user_info set sha1_0=:sha1_0,sha1_1=:sha1_1,sha1_2=:sha1_2,sha1_3=:sha1_3,sha1_4=:sha1_4 where id=:id;",-1,&st,&unused)!=SQLITE_OK) return false;
	sqlite3_bind_text(st,1,OperaData::IntConvertToHex(code[0]).c_str(),8,SQLITE_TRANSIENT);
	sqlite3_bind_text(st,2,OperaData::IntConvertToHex(code[1]).c_str(),8,SQLITE_TRANSIENT);
	sqlite3_bind_text(st,3,OperaData::IntConvertToHex(code[2]).c_str(),8,SQLITE_TRANSIENT);
	sqlite3_bind_text(st,4,OperaData::IntConvertToHex(code[3]).c_str(),8,SQLITE_TRANSIENT);
	sqlite3_bind_text(st,5,OperaData::IntConvertToHex(code[4]).c_str(),8,SQLITE_TRANSIENT);
	sqlite3_bind_int(st,6,id);
	int tp = sqlite3_step(st);
	if((tp!=SQLITE_DONE) && (tp!=SQLITE_ROW)) return false;//
	//没法判断id是否存在，，，
	sqlite3_finalize(st);
	return true;
}
bool OperaData::ChangeUserBalanceValue(const long &id,const double &money,const bool &I_or_O)//test pass;
{
	if(I_or_O)//存
	{
		const char * unused = NULL;
		sqlite3_stmt *st = NULL;std::stringstream ss;
		if(sqlite3_prepare_v2(conn,"update user_info set balance=balance+:money where id=:id;",-1,&st,&unused)!=SQLITE_OK) return false;
		sqlite3_bind_double(st,1,money);
		sqlite3_bind_int(st,2,id);
		int tp = sqlite3_step(st);
		if((tp!=SQLITE_DONE) && (tp!=SQLITE_ROW)) return false;//
		//没法判断id是否存在，，，
		sqlite3_finalize(st);
		return true;
	}
	else//取
	{
		const char * unused = NULL;
		sqlite3_stmt *st = NULL;std::stringstream ss;
		if(sqlite3_prepare_v2(conn,"update user_info set balance=balance-:money where id=:id;",-1,&st,&unused)!=SQLITE_OK) return false;
		sqlite3_bind_double(st,1,money);
		sqlite3_bind_int(st,2,id);
		int tp = sqlite3_step(st);
		if((tp!=SQLITE_DONE) && (tp!=SQLITE_ROW)) return false;//
		//没法判断id是否存在，，，
		sqlite3_finalize(st);
		return true;
	}
	// update user_info set balance=balance+1 where id=2;
}
bool OperaData::ChangeUserEnableValue(const long &id,const bool &enable)//test pass
{
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;std::stringstream ss;
	if(sqlite3_prepare_v2(conn,"update user_info set enable=:enable where id=:id;",-1,&st,&unused)!=SQLITE_OK) return false;
	sqlite3_bind_int(st,1,enable);
	sqlite3_bind_int(st,2,id);
	int tp = sqlite3_step(st);
	if((tp!=SQLITE_DONE) && (tp!=SQLITE_ROW)) return false;//
	//没法判断id是否存在，，，
	sqlite3_finalize(st);
	return true;
}
bool OperaData::DeleteUser(const long &id)
{
	sqlite3_stmt * st = NULL;
	if(sqlite3_prepare_v2(conn,"delete from user_info where id=:id",-1,&st,NULL)!=SQLITE_OK)
	{
		return false;
	}
	sqlite3_bind_int(st,1,id);
	sqlite3_step(st);
	sqlite3_finalize(st);
	return true;
}
bool ExportData::WriteDataFile(const string &filename)//test pass
{
	GetData GD;
	GD.ToLinkedList();
	struct user_info *p = &user_HEAD;
	ofstream tp_file(filename);
	if(tp_file)
	{
		while (p !=NULL)
		{
			tp_file << p->CardID
			<< " " << p->user_name 
			<< " " << std::hex << p->code_sha1[0] 
			<< " " << p->code_sha1[1] 
			<< " " << p->code_sha1[2]
			<< " " << p->code_sha1[3] 
			<< " " << p->code_sha1[4]
			<< std::dec
			<< " " << p->Balance
			<< " " << p->Enable
			<< std::endl;
			p = p->next;
		}
		return true;
	}
	return false;
}
bool ImportData::ReadDataFile(const string &filename)//test pass
{
	//这是确保文件格式正确的情况下
	ifstream File(filename);
	const char * unused = NULL;
	sqlite3_stmt *st = NULL;std::stringstream ss;
	sqlite3_exec(conn,"drop table user_info;",NULL,NULL,NULL);
	sqlite3_exec(conn,"CREATE TABLE user_info(id int,name text,sha1_0 text,sha1_1 text,sha1_2 text,sha1_3 text,sha1_4 text,balance real,enable int,primary key(id));",NULL,NULL,NULL);
	sqlite3_prepare_v2(conn,"insert into user_info values(:id,:name,:sha1_0,:sha1_1,:sha1_2,:sha1_3,:sha1_4,:balance,:enable);",-1,&st,NULL);
	if (File)
	{
		while(!File.eof())
		{
			long id;
			string name;
			string code[5];
			double balance;
			bool enable;
    		File >> id >> name >> code[0] >> code[1] >> code[2] >> code[3] >> code[4] >> balance >> enable;
            sqlite3_bind_int(st,1,id);
			sqlite3_bind_text(st,2,name.c_str(),-1,SQLITE_TRANSIENT);
			sqlite3_bind_text(st,3,code[0].c_str(),-1,SQLITE_TRANSIENT);
			sqlite3_bind_text(st,4,code[1].c_str(),-1,SQLITE_TRANSIENT);
			sqlite3_bind_text(st,5,code[2].c_str(),-1,SQLITE_TRANSIENT);
			sqlite3_bind_text(st,6,code[3].c_str(),-1,SQLITE_TRANSIENT);
			sqlite3_bind_text(st,7,code[4].c_str(),-1,SQLITE_TRANSIENT);
			sqlite3_bind_double(st,8,balance);
			sqlite3_bind_int(st,9,enable);
			sqlite3_step(st);
			sqlite3_reset(st);
			if(File.eof())
			{break;}
		}
		File.close();
	}
	sqlite3_finalize(st);
	return true;
}
InitData::InitData()
{
	user_HEAD.next = NULL;
	OpenDBFile ODF;
	GetData GD;
	user_HEAD.next = NULL;
	//OD.testConvert();
	if(ODF.OpenFile())
	{
		GD.ToLinkedList();
	}
	//	OD.testAddUser();
}
InitData::~InitData()
{
	sqlite3_close(conn);
	//delete &user_HEAD;
	//delete &admin_HEAD;
}