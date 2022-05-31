#pragma once
#define LOAD_MOAD "load"
#define SAVE_MOAD "save"
enum class GameMode
{
	LOAD = 0,
	SAVE = 1,
	ERROR = 2
	
};

inline GameMode getMode(std::string& mode)
{
	if (mode == "load")
		return GameMode::LOAD;
	else if (mode == "save")
		return GameMode::SAVE;
	else
		return GameMode::ERROR;
}