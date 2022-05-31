#pragma once
#define LOAD_MOAD "load"
#define SAVE_MOAD "save"
enum class GameMode
{
	LOAD = 0,
	SAVE = 1,
	ERROR_MODE = 2
	
};

inline GameMode getMode(std::string& mode)
{
	if (mode == LOAD_MOAD)
		return GameMode::LOAD;
	else if (mode == "SAVE_MOAD")
		return GameMode::SAVE;
	else
		return GameMode::ERROR_MODE;
}