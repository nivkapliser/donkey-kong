#pragma once
#include "utils.h"

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

	// what is the difference between pushToStack and addStep? ----------------------
	void pushToStack(int itr, char key) { steps.push_back({ itr, key }); }
	void addStep(int iteration, char step) { steps.push_back({ iteration, step }); }
	// ------------------------------------------------------------------------------

	bool isEmpty() { return steps.empty(); }
	bool isNextStepOnItr(int itr) const { return !steps.empty() && steps.front().first == itr; }
	std::pair<int, char> popStep();// { std::pair<int, char> step = steps.front(); steps.pop_front(); return step; }
	void setFinalItr(int itr) { final_itr = itr; }
	int getFinalItr() { return final_itr; }
};

