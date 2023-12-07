#pragma once

#include "PacmanCore.h"
#include "Grid\GridGenerator.h"

struct PacmanLevelInfo {
	bool bIsValid;
	int Height, Width;
	std::vector<CellContent> Content;
	std::vector<CellRule> Rules;
	Point2 PlayerSpawn;
	std::vector<Point2> GhostSpawn;
};

class PacmanLevelInfoParser
{
public:
	//Will always return a struct, but make sure to verify that bIsValid before using.
	static PacmanLevelInfo ParseFromStringVector(const std::vector<std::string> UnparsedStringVector);

	//This produces a dummy struct which is minimal but valid. Good for testing only
	static PacmanLevelInfo GetTestLevelInfo();
};

