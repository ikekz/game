#pragma once

#include<iostream>
#include<rapidjson\document.h>
#include<rapidjson\writer.h>
#include<rapidjson\stringbuffer.h>
#include<rapidjson\filereadstream.h>
#include<rapidjson\error\en.h>
#include<rapidjson\error\error.h>

class Importer
{
public:
	Importer(char* fileName);
	~Importer();
	char GetChar(char* object, char* field);
	int GetInt(char* object, char* field);
private:
	FILE* file;
	void Read();
	rapidjson::Document data;
	auto GetObject(char* object);
};