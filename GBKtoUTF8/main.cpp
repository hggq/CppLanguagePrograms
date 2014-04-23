#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <assert.h>
#include "GBKtoUTF8.h"
using namespace std;


void GetText(bool isUtf8, std::vector<std::string>& vecStr)
{
	const char* filename = isUtf8 ? "utf8.txt" : "gbk.txt";
	std::ifstream ifs(filename);
	assert(!ifs.fail());

	while(!ifs.eof())
	{
		std::string str;
		ifs >> str;
		vecStr.push_back(str);
	}

	ifs.close();
}

void test_gbbk_utf_unicode()
{
	char const * p = "你";
	std::cout<<PrintStringAsBinaryString(p)<<"\n";
	std::cout<<PrintStringAsBinaryString("位")<<"\n";

	//将bgbk按空格分开，每连续两个表示是一个字符的二进制编码，转成int类型后通过one_gbk_to_unicode调用，得到该字符的unicode编码，然后通过one_unicode_to_utf8转为utf-8

	//一的二进制表示是11010010 10111011（D2BB，210-187），通过one_gbk_to_unicode转换为unicode是4E00，然后通过one_unicode_to_utf8转为utf-8
	std::cout << std::hex<<one_gbk_to_unicode(196,227) <<"\n";
	std::cout << std::hex<<one_gbk_to_unicode(186,195) <<"\n";
	std::cout << std::hex<<one_gbk_to_unicode(210,187) <<"\n";
	std::cout << std::hex<<one_gbk_to_unicode(182,254) <<"\n";
	unsigned long one = 0x4E00; //0xD2BB;//0x4E00;
	unsigned char pOutput[6];  
	memset(pOutput,0,6);
	one_unicode_to_utf8(one,pOutput,6);
	cout << pOutput << "\n";
	std::cout<<PrintStringAsBinaryString((char*)pOutput)<<"\n";
}

int main()
{
	std::cout<<PrintStringAsBinaryString("你")<<"\n";
	std::cout<<PrintStringAsBinaryString("好")<<"\n";
	std::cout<<PrintStringAsBinaryString("你好")<<"\n";
	const char *p = "浣犲ソ";//"涓�"; //utf-8字符
	unsigned short unibuf[32];
	utf8_to_unicode(p,unibuf,32);
	std::cout<<unibuf<<"--"<<PrintStringAsBinaryString((char*)unibuf)<<"\n";
	unsigned short wch = 0;
	one_utf8_to_unicode(p, wch);
	std::cout<<wch<<"--"<<PrintStringAsBinaryString((char*)&wch)<<"\n";


	unsigned short unicode = 0x4E00;
	char buf[32] = {'0'};
	unicode_to_utf8(unicode,buf);


	test_gbbk_utf_unicode();
	
	std::cout<<"-----------------------------------------\n";

	std::string ghello = "你好";
	std::string gthank = "谢谢";
	std::cout<<ghello<<"\t"<<ConvertGBKToUtf8(ghello)<<"\t"<<IsTextUTF8(ghello.c_str(),ghello.size())<<"\t"<<IsTextUTF8(ghello)<<"\n";
	std::cout<<gthank<<"\t"<<ConvertGBKToUtf8(gthank)<<"\t"<<IsTextUTF8(gthank.c_str(),gthank.size())<<"\t"<<IsTextUTF8(gthank)<<"\n";

	std::vector<std::string> uVecStr;
	std::vector<std::string> gVecStr;
	GetText(true,uVecStr);
	GetText(false,gVecStr);

	std::cout<<"--------------utf8--->gbk----------------\n";
	for (std::vector<std::string>::iterator itr = uVecStr.begin();itr!=uVecStr.end();++itr)
	{
		std::cout<<*itr<<"\t"<<ConvertUtf8ToGBK(*itr)<<"\t"<<IsTextUTF8((*itr).c_str(),(*itr).size())<<"\t"<<IsTextUTF8(*itr)<<"\n";
	}

	std::cout<<"--------------gbk--->utf8----------------\n";
	for (std::vector<std::string>::iterator itr = gVecStr.begin();itr!=gVecStr.end();++itr)
	{
		std::cout<<*itr<<"\t"<<ConvertGBKToUtf8(*itr)<<"\t"<<IsTextUTF8((*itr).c_str(),(*itr).size())<<"\t"<<IsTextUTF8(*itr)<<"\n";
	}

	std::cout<<"---------------------------------\n";
	system("pause");
	return 0;
}