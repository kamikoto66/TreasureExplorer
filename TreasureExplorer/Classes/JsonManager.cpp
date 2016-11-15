#include "PCH.h"
#include "JsonManager.h"


USING_NS_CC;

CJsonManager::CJsonManager()
{

}


CJsonManager::~CJsonManager()
{
}

void CJsonManager::init()
{
	fileUtils = FileUtils::sharedFileUtils();
	gneraterFilePath();
}

void CJsonManager::gneraterFilePath()
{
	//���� ��� �޾ƿ�
	std::string f_name;
	f_name = "Json/ResourcePath.json";
	//���� �о�帲
	ssize_t fileSize;
	char* file = (char*)fileUtils->getFileData(f_name.c_str(), "rb", &fileSize);

	//unsigend char* ���� string������ ��ȯ
	std::string str_array = file;

	Json::Reader reader;
	//Json �� ���� �������� �־���
	if (!reader.parse(str_array, filePathRoot))
	{
		CCASSERT(false, "File Load Failed");
	}
}
