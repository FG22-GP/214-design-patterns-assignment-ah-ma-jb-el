#include "PacmanCore.h"
#include "PacmanLevelInfoParser.h"

PacmanLevelInfo PacmanLevelInfoParser::ParseFromStringVector(const std::vector<std::string> UnparsedStringVector)
{
	PacmanLevelInfo ParsedInfo;
	ParsedInfo.bIsValid = false;
	auto it = UnparsedStringVector.begin();

	//Will be used repeatedly to verify that we haven't reached end of vector.
#define CheckIterator() if (it == UnparsedStringVector.end()) return ParsedInfo;

	//Accept 2 integers as Width and Height
	CheckIterator();
	ParsedInfo.Width = std::stoi(*it); it++;
	CheckIterator();
	ParsedInfo.Height = std::stoi(*it); it++;

	//Parse Cell Rules
	for (int j = 0; j < ParsedInfo.Height; j++)
	{
		CheckIterator();
		std::string Line = *it; it++;
		if (Line.length() != ParsedInfo.Width) return ParsedInfo;
		for (int i = 0; i < ParsedInfo.Width; i++)
		{
			char CharDigit = Line[i];
			int Digit = CharDigit - '0';
			if (Digit < 0 || Digit > 9) return ParsedInfo;
			ParsedInfo.Rules.push_back((CellRule)(Digit));
		}
	}

	//Parse Cell Contents
	for (int j = 0; j < ParsedInfo.Height; j++)
	{
		CheckIterator();
		std::string Line = *it; it++;
		if (Line.length() != ParsedInfo.Width) return ParsedInfo;
		for (int i = 0; i < ParsedInfo.Width; i++)
		{
			char CharDigit = Line[i];
			int Digit = CharDigit - '0';
			ParsedInfo.Content.push_back((CellContent)(Digit));
		}
	}

	//Parse player spawn location
	CheckIterator();
	int PlayerSpawnX = std::stoi(*it); it++;
	CheckIterator();
	int PlayerSpawnY = std::stoi(*it); it++;
	Point2 PlayerSpawnLocation = Point2(PlayerSpawnX, PlayerSpawnY);
	ParsedInfo.PlayerSpawn = PlayerSpawnLocation;

	//Parse ghost amount
	CheckIterator();
	int GhostAmount = std::stoi(*it); it++;
	if (GhostAmount < 0) return ParsedInfo;

	//Parse spawn location for each ghost
	for (int i = 0; i < GhostAmount; i++)
	{
		CheckIterator();
		int GhostSpawnX = std::stoi(*it); it++;
		CheckIterator();
		int GhostSpawnY = std::stoi(*it); it++;
		Point2 GhostSpawnLocation = Point2(GhostSpawnX, GhostSpawnY);
		ParsedInfo.GhostSpawn.push_back(GhostSpawnLocation);
	}

	ParsedInfo.bIsValid = true;
	return ParsedInfo;
}

PacmanLevelInfo PacmanLevelInfoParser::GetTestLevelInfo()
{
	std::vector<std::string> TestVector;
	TestVector.push_back("4");
	TestVector.push_back("4");

	TestVector.push_back("0000");
	TestVector.push_back("0110");
	TestVector.push_back("0110");
	TestVector.push_back("0000");

	TestVector.push_back("0000");
	TestVector.push_back("0110");
	TestVector.push_back("0110");
	TestVector.push_back("0000");

	TestVector.push_back("1");
	TestVector.push_back("1");

	TestVector.push_back("2");
	TestVector.push_back("2");
	TestVector.push_back("2");
	TestVector.push_back("2");
	TestVector.push_back("1");


	return ParseFromStringVector(TestVector);
}
