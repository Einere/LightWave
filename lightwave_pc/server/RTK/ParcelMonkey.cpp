#include "stdafx.h"
#include "ParcelMonkey.h"

ParcelMonkey::ParcelMonkey() : Monkey("parcel")
{

}

ParcelMonkey::~ParcelMonkey()
{
}

Json::Value ParcelMonkey::doGet(Json::Value props)
{
	Json::Value root;
	root["message"] = "Yeah~~~!";
	return root;
}