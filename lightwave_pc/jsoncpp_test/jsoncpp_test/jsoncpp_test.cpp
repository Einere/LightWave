// jsoncpp_test.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include "json/json.h"
#include <fstream>
#include <string>



using namespace std;

int main()
{
	Json::Value root;   // 'root' will contain the root value after parsing.
	Json::Reader reader;
	string json = "{"
		"\"encoding\" : \"UTF-8\","
		"\"plug-ins\" : ["
		"\"python\","
		"\"c++\","
		"\"ruby\""
		"],"
		"\"indent\" : { \"length\" : 3, \"use_space\" : true }"
		"}";

	string inputJson;
	cout << inputJson <<endl;
	reader.parse(inputJson, root);
	std::string encoding = root.get("encoding", "default").asString();
	cout << encoding << endl;
	
	//cin >> root;

	cout << root;
	// You can also read into a particular sub-value.
	std::cin >> root["subtree"];
	
	// Get the value of the member of root named 'encoding',
	// and return 'UTF-8' if there is no such member.
	// Get the value of the member of root named 'plug-ins'; return a 'null' value if
	// there is no such member.
	const Json::Value plugins = root["plug-ins"];
	// Iterate over the sequence elements.

	return 0;
}