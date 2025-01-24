#pragma once
#include "utils.h"

class Results
{
public:
	//       encounted ghost,    barrel,    special ghost, fell to far, pauline save, final win, final lose, game finish (other reason)
	enum ResultValue { ENC_GHOST, ENC_BARREL, ENC_SP_GHOST, ENC_FALL, STAGE_FINISH, GAME_WON ,GAME_LOSE, GAME_FINISH, NO_RESULT }; 
private:
	std::list<std::pair<size_t, ResultValue>> results; // pairs of iteration and result
	bool save = false; 
	// maybe add silent
public:
	void setSave(bool _save) { save = _save; }
	static Results readResults(const std::string& filename);
	void saveResults(const std::string& filename) const;
	void addResult(size_t iteration, ResultValue result) { if (save) { results.push_back({ iteration, result }); } }
	std::pair<size_t, ResultValue> popResult(); // for load
	bool isEmpty() { return results.empty(); } // where to use?
	bool isFinishedBy(size_t itr) const { return results.empty() || results.back().first <= itr; } // where to use?
	
	//void setFinalItr(size_t itr) { final_itr = itr; }
	//size_t getFinalItr() { return final_itr; }
};

