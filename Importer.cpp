#include "Importer.h"

Importer::Importer(char * fileName)
{
	file = std::fopen(fileName, "r");
	if (!file) 
	{
		std::cout << "Config file " << fileName << " was not found\n";
		exit(1);
	}
	Read();
}

Importer::~Importer()
{
	std::fclose(file);
}

void Importer::Read()
{
	char buffer[65536];
	rapidjson::FileReadStream source(file, buffer, sizeof(buffer));
	rapidjson::ParseResult result = data.ParseStream(source);
	if (!result)
	{
		std::cout << "JSON parse error: " << rapidjson::GetParseError_En(result.Code()) << std::endl;
		exit(1);
	}
}

auto Importer::GetObject(char* object)
{
	auto it = data.FindMember(object);
	if (it != data.MemberEnd()) 
	{
		rapidjson::Type type = it->value.GetType();
		if (type != rapidjson::kObjectType)
		{
			std::cout << object << " is an invalid key\n";
			exit(1);
		}
		return it->value.GetObject();
	}
	else
	{
		std::cout << "Key " << object << " was not found\n";
		exit(1);
	}
}

char Importer::GetChar(char* object, char* field)
{
	auto obj = GetObject(object);
	auto it = obj.FindMember(field);

	if (it != obj.MemberEnd())
	{
		auto type = it->value.GetType();
		if (type != rapidjson::kStringType)
		{
			std::cout << object << "." << field << " is not a char\n";
			exit(1);
		}
		else
			if (it->value.GetStringLength() == 1)
				return it->value.GetString()[0];
			else if (it->value.GetStringLength() > 1)
			{
				std::cout << object << "." << field << " should be one char\n";
				exit(1);
			}
			else
			{
				std::cout << object << "." << field << " is empty char\n";
				exit(1);
			}
	}
	else
	{
		std::cout << object << "." << field << " was not found\n";
		exit(1);
	}
}

int Importer::GetInt(char* object, char* field)
{
	auto obj = GetObject(object);
	auto it = obj.FindMember(field);

	if (it != obj.MemberEnd())
	{
		auto type = it->value.GetType();
		if (type != rapidjson::kNumberType)
		{
			std::cout << object << "." << field << " is not an integer\n";
			exit(1);
		}
		else
			return it->value.GetInt();
	}
	else
	{
		std::cout << object << "." << field << " was not found\n";
		exit(1);
	}
}