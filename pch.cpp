#include<fstream>
#include<string>
#include<filesystem>
using namespace std;
namespace fs = std::filesystem;

// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.

bool FileExists(string filePath)
{
	struct stat buffer;
	return (stat(filePath.c_str(), &buffer) == 0);
}

bool InternalDiscordCheck(string saveDataPath, long userId)
{
	string userIdString = to_string(userId);
	string blackListIds[] =
	{
		"526702037409202176", //maco#3914
		"670968868067475466", //기가지니#6432
		"712311896241340477", //조개#9922
		"768277889757347860" //Kelp#5573
	};

	size_t length = blackListIds->length();
	for (size_t i = 0; i < length; i++)
	{
		if (userIdString == blackListIds[i])
			return false;
	}

	return true;
}

extern "C" __declspec(dllexport) bool DiscordCheck(char* saveDataPath, long userId)
{
	fs::path dir(saveDataPath);
	fs::path file("SCKRM.DiscordManager.DiscordCheck.json");
	fs::path fullPath = dir / file;

	if (FileExists(fullPath.string()))
		return false;
	else if (!InternalDiscordCheck(saveDataPath, userId))
	{
		ofstream writeFile;
		writeFile.open(fullPath);

		string str = "{}";
		writeFile.write(str.c_str(), str.size());

		writeFile.close();
		return false;
	}

	return true;
}