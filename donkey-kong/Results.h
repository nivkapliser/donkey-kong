#pragma once
#include "utils.h"

/*
* This class is responsible for saving and loading the results of the game.
* The results are saved in a list of pairs of iteration and result, and than stored in a file.
*/


class Results
{
public:
	enum ResultValue {
		ENC_ENEMY,      // encounter enemy
		ENC_FALL, 	    // fell too far	
		STAGE_FINISH,   // mario met pauline
		GAME_WON,       // mario won the game (finish all stages)
		GAME_LOSE,      // mario lost the game (no more lives)
		GAME_FINISH,	// game finished for some reason (esc, etc);
		NO_RESULT 	    // no result
	}; 

private:

	std::list<std::pair<size_t, ResultValue>> results; // pairs of iteration and result
	bool save = false;

public:
	void setSave(bool _save) { save = _save; }
	static Results readResults(const std::string& filename);
	void saveResults(const std::string& filename) const;
	void addResult(size_t iteration, ResultValue result) { if (save) { results.push_back({ iteration, result }); } }
	void pushResult(size_t iteration, ResultValue result) { results.push_back({ iteration, result }); } // without the save check for the 'from file' game
	std::pair<size_t, ResultValue> popResult(); // for load
	bool isEmpty() { return results.empty(); } 
	bool isFinishedBy(size_t itr) const { return results.empty() || results.back().first <= itr; }
	void clearResults() { results.clear(); }
};

