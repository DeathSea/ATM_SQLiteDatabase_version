/*
����������helper function��
Designed by DeathSea 2014 Jnu
sha1ֵ���㣬��֤
*/
#include <iostream>
#include "sha1.h"
using std::string;
class helper
{
private:
	SHA1  sha;
public:
	bool check(const char *input_char_array,unsigned *input_sha );//��鴫��ֵ��sha1ֵ�봫���sha1ֵ�Ƿ���ͬ
	void calculate(const char *input_char_array,unsigned *input_sha);//����input_char_array��sha1ֵ
	bool checkfilename(const string &filename);
};