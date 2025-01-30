#pragma once
#include "utils.h"

/*
* This class is used to store the steps of the user in the game.
* It stores the iteration number, the key pressed by the user and the random seed used to generate the ghosts move.
* It also provides some useful methods to manage the reading and writing. 
*/

class Steps
{
	long random_seed = 0;
	int final_itr;
	std::list<std::pair<int, char>> steps;  //pairs of iteration and key pressed

public:
	static Steps readSteps(const std::string& filename); 
	void saveSteps(const std::string& filename) const;
	long getRandomSeed() { return random_seed; }
	void setRandomSeed(long seed) { random_seed = seed; }
	void pushToStack(int itr, char key) { steps.push_back({ itr, key }); }
	void addStep(int iteration, char step) { steps.push_back({ iteration, step }); }
	bool isEmpty() { return steps.empty(); }
	bool isNextStepOnItr(int itr) const { return !steps.empty() && steps.front().first == itr; }
	std::pair<int, char> popStep();
	void setFinalItr(int itr) { final_itr = itr; }
	int getFinalItr() { return final_itr; }
	void clearSteps() { steps.clear(); }
};

