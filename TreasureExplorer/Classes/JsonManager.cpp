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
	//파일 경로 받아옴
	std::string f_name;
	f_name = "Json/ResourcePath.json";
	//파일 읽어드림
	ssize_t fileSize;
	char* file = (char*)fileUtils->getFileData(f_name.c_str(), "rb", &fileSize);

	//unsigend char* 형을 string형으로 전환
	std::string str_array = file;

	Json::Reader reader;
	//Json 에 파일 읽은것을 넣어줌
	if (!reader.parse(str_array, filePathRoot))
	{
		CCASSERT(false, "File Load Failed");
	}
}
