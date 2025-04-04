#include "GameFromFile.h"

// Function to run the game from file
void GameFromFile::run() {
	showAndLoadBoards();

	steps = steps.readSteps(createFileName(getBoard().getBoardName(), "steps")); //reading the steps
	results = results.readResults(createFileName(getBoard().getBoardName(), "results")); //reading the results
	if (steps.isEmpty() || results.isEmpty()) {
		std::cout << "Error while reading steps or results file. Exiting game.\n";
		Sleep(3000);
		return;
	}
	
	setRandomSeed(steps.getRandomSeed());  //random seed set
	initGame();
	getMario().setLives(results.getLives());
	getMario().setScore(results.getScore());
	runGame();
	checkNextStage();
}

// Function to load the boards from the file
bool GameFromFile::showAndLoadBoards() {
	system("cls");
	namespace fs = std::filesystem;
	std::vector<std::string>& boardFiles = getBoards();
	Board& board = getBoard();
	Mario& mario = getMario();
	Hammer& hammer = getHammer();
	boardFiles.clear();	
	std::string input; // to clear the buffer
	int currentBoardIndex = getCurrBoardIndex();

	// scan directory for board files
	for (const auto& entry : fs::directory_iterator(".")) {
		if (entry.path().string().find("dkong_") != std::string::npos &&
			entry.path().string().find(".screen") != std::string::npos) {
			boardFiles.push_back(entry.path().string());
		}
	}

	// if no board files found, return false for game exit
	if (boardFiles.empty()) {
		std::cout << "No board files found. Exiting game.\n";
		return false;
	}

	// check if the board file was read successfully
	if (board.readBoard(boardFiles[getCurrBoardIndex()], mario, hammer) != 1) {
		std::cout << "Error while reading board file. Exiting game.\n";
		Sleep(3000); // so user can see
		return false;
	}
}

// Function to check if next stage exists
void GameFromFile::checkNextStage()
{
	int currentBoardIndex = getCurrBoardIndex();
	std::vector<std::string> boardFiles = getBoards();
	

	if (currentBoardIndex + 1 < boardFiles.size() || final_board != -1) {
		if (final_board != -1)
			return;

		setCurrentBoardIndex(++currentBoardIndex);
		Board& board = getBoard();
		Hammer& hammer = getHammer();
		Mario& mario = getMario();
		board.readBoard(boardFiles[currentBoardIndex], mario, hammer);
		steps = steps.readSteps(createFileName(board.getBoardName(), "steps"));
		results = results.readResults(createFileName(board.getBoardName(), "results"));
		if (steps.isEmpty() || results.isEmpty()) {
			system("cls");
			if (getSilent())
			{
				if(getFinalBoard() == -1)
					setFinalBoard(currentBoardIndex + 1);
				std::cout << "Running in silent mode worked well until screen number " << final_board << std::endl;
				std::cout << "There is no results file or steps file for screen number "<< final_board << " .Exiting game";
			}
			else
			{
				std::cout << "Error while reading steps or results file. Exiting game.\n";
				Sleep(3000);
				setFinalBoard(currentBoardIndex + 1);
			}
			return;
		}
		setRandomSeed(steps.getRandomSeed());

		resetStage();
		mario.setLives(results.getLives());
		mario.setScore(results.getScore());
		runGame();
	}
	else {
		system("cls"); 
		if (getSilent()) std::cout << "Run in Silent mode.\n";
		std::cout << "No more stages, everything looks good!!\n";
		std::cout << "Exiting recording.";
		Sleep(3000);
	}
}

// Function to check if mario encounters a barrel or ghost
bool GameFromFile::checkEnemyEncounters(EnemiesManager& em, Mario& mario) {
	if (em.getEncounters()) {
		mario.downLives();
		em.setEncounters(false);
		return true;
	}
	return false;
}

// Function to run the game loop
void GameFromFile::runGame() {
	int final_itr = steps.getFinalItr();
	bool silent = getSilent();

	Mario& mario = getMario();
	EnemiesManager& enemiesManager = getEnemiesManager();
	Hammer& hammer = getHammer();
	mario.drawLife();
	setCurrItr(0);  //reset the itr counter
	std::pair<int, char> next_step;
	std::pair<size_t, char> curr_result;
	
	if (!steps.isEmpty())
		next_step = steps.popStep();  // gets the first step (if exist)

	// moving loop for mario and barrels
	for(int i = 0; i < final_itr; i++) { 

		if (!silent) {
			mario.draw();
			enemiesManager.draw(mario);
			hammer.draw();
		}
			
		// check and get user input
		for (int i = 0; i < 2; i++) {
			if (getCurrItr() == next_step.first) {
				mario.keyPressed(next_step.second);
				if (!steps.isEmpty())
					next_step = steps.popStep();  //get the next step
			}
			Sleep(silent ? SLEEP_IN_SILENT : SLEEP_TIME);
		}

		if (!silent) {
			mario.erase();	
			hammer.erase();
		}
		mario.move();

		// check if mario has met and used hammer
		checkHammer(mario, hammer);
		if (mario.getSmash()) {
			marioHit();
		}

		enemiesManager.move(mario);
		
		// if mario encounters a barrel or ghost, reset the stage or game over
		if (checkEnemyEncounters(enemiesManager, mario))
		{
			curr_result = results.popResult();
			if (curr_result.first != i || curr_result.second != results.ResultValue::ENC_ENEMY) {
				reportResultError("Result file does not match enemy encounter", getBoard().getBoardName(), getCurrItr());
			}
			resetStage();
		}

		enemiesManager.barrelsActivation(); // reseting the barrel activation	

		// draw the score 
		if (!enemiesManager.getEncounters())
			if (!silent) mario.drawScore();

		// check if mario has fallen 5 lines and reset the stage
		if (mario.fellTooFar() && mario.isOnFloor()) {
			explodeMarioAndResetStage(mario);
			curr_result = results.popResult();
			if (curr_result.first != i || curr_result.second != results.ResultValue::ENC_FALL) {
				reportResultError("Result file does not match Mario fell too far", getBoard().getBoardName(), getCurrItr());
			}
		}

		//if mario meets Pauline, game won
		marioMetPauline(mario);

		if (mario.getLives() == 0) {
			if (!results.isEmpty())
			{
				curr_result = results.popResult();
				if (curr_result.first != i || curr_result.second != results.ResultValue::GAME_LOSE) {
					reportResultError("Result file does not match game over", getBoard().getBoardName(), getCurrItr());
				}

			}

		}
		// increament for the itr counter
		setCurrItr(getCurrItr() + 1);
	}
}

// Function to report results error
void GameFromFile::reportResultError(const std::string& message, const std::string& filename, size_t iteration) {
	system("cls");
	std::cout << "Screen" << filename << " - " << message << '\n';
	std::cout << "Iteration: " << iteration << '\n';
	std::cout << "Press any key to continue to next screen (if any)" << std::endl;
	_getch();
}

// Function to check if mario has met Pauline
bool GameFromFile::marioMetPauline(Mario& mario) {
	if (mario.metPauline()) {
		std::pair<size_t, char> curr_result = results.popResult();
		if (curr_result.first != getCurrItr() || curr_result.second != results.ResultValue::STAGE_FINISH) {
			reportResultError("Result file does not match finish stage", getBoard().getBoardName(), getCurrItr());
		}
		checkNextStage();
		return true;
	}
	return false;
}