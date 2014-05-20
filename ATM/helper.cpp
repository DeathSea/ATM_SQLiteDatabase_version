#include "helper.h"
bool helper::check(const char * input_char_array,unsigned *input_sha)
{
	helper::sha.Reset();
	unsigned output_sha[5];
	bool check_result = true;
	helper::sha << input_char_array;
	if(helper::sha.Result(output_sha))
	{
		for(int i=0;i<=4;i++)
		{
			if(output_sha[i] != input_sha[i])
			{
				check_result = false;
				break;
			}
		}
	}
	else
	{
		std::cout << "Can't not produce sha1 value"<<std::endl;
	}
	return check_result;
}
void helper::calculate(const char * input_char_array,unsigned * input_sha1)
{
	helper::sha.Reset();
	helper::sha << input_char_array;
	if(!helper::sha.Result(input_sha1))
	{
		std::cout<<"Can't not calculate the sha1 value"<<std::endl;
	}
}
bool helper::checkfilename(const string &filename)
{
	if (filename.find("/") !=-1 || filename.find("\\") !=-1)
	{
		return true;
	}
     return false;
}