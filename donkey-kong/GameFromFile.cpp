#include "GameFromFile.h"

void GameFromFile::run() {
	showAndLoadBoards();
	steps = steps.readSteps(createFileName(getBoard().getBoardName(), "steps")); //reading the steps
	results = results.readResults(createFileName(getBoard().getBoardName(), "results")); //reading the results
	setRandomSeed(steps.getRandomSeed());  //random seed set
	initGame();
	runGame();
	checkNextStage();
}

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

void GameFromFile::checkNextStage()
{
	int currentBoardIndex = getCurrBoardIndex();
	std::vector<std::string> boardFiles = getBoards();
	

	if (currentBoardIndex + 1 < boardFiles.size()) {
		setCurrentBoardIndex(++currentBoardIndex);
		Board& board = getBoard();
		Hammer& hammer = getHammer();
		Mario& mario = getMario();
		board.readBoard(boardFiles[currentBoardIndex], mario, hammer);
		steps = steps.readSteps(createFileName(board.getBoardName(), "steps"));
		results = results.readResults(createFileName(board.getBoardName(), "results"));
		setRandomSeed(steps.getRandomSeed());
		initGame();
		runGame();
		//currentState = GameState::NEXT_STAGE;
	}
	else {
		system("cls");
		std::cout << "No more stages. Exiting recording.\n";
		Sleep(3000);
	}
		//currentState = GameState::MENU;
}

void GameFromFile::checkEnemyEncounters(EnemiesManager& em, Mario& mario) {
	if (em.getEncounters()) {
		if (results.popResult().second != results.ResultValue::ENC_ENEMY) {
			reportResultError("Result file does not match enemy encounter", getBoard().getBoardName(), getCurrItr());	
		}
		mario.downLives();
		resetStage();
		/*if (mario.getLives() == 0) {
			if (results.popResult().second != results.ResultValue::GAME_LOSE) {
				reportResultError("Result file does not match game over", getBoard().getBoardName(), getCurrItr());
			}
		}*/
		em.setEncounters(false);
	}
}

//void GameFromFile::checkBarrelEncounters(BarrelManager& bm, Mario& mario)
//{
//	if (bm.getEncounters()) {
//		if (results.popResult().second != results.ResultValue::ENC_BARREL) {
//			reportResultError("Result file does not match barrel encounter", getBoard().getBoardName(), getCurrItr());
//		}
//		mario.downLives();
//		resetStage();
//		/*if (mario.getLives() == 0) {
//			if (results.popResult().second != results.ResultValue::GAME_LOSE) {
//				reportResultError("Result file does not match game over", getBoard().getBoardName(), getCurrItr());
//			}
//		}*/
//		bm.setEncounters(false);
//	}
//}

//void GameFromFile::checkGhostEncounters(GhostManager& gm, Mario& mario)
//{
//	if (gm.getEncounters()) {
//		if (results.popResult().second != results.ResultValue::ENC_GHOST) {
//			reportResultError("Result file does not match ghost encounter", getBoard().getBoardName(), getCurrItr());
//		}
//		mario.ghosted();
//		mario.downLives();
//		resetStage();
//		/*if (mario.getLives() == 0) {
//			if (results.popResult().second != results.ResultValue::GAME_LOSE) {
//				reportResultError("Result file does not match game over", getBoard().getBoardName(), getCurrItr());
//			}
//		}*/
//		gm.setEncounters(false);
//	}
//}


void GameFromFile::runGame() {
	int final_itr = steps.getFinalItr();

	//TODO: things that we are exactly doing in regular game - do with it something
	Mario& mario = getMario();
	/*BarrelManager& barrelsManager = getBarrelManager();
	GhostManager& ghostsManager = getGhostManager();*/
	EnemiesManager& enemiesManager = getEnemiesManager();
	Hammer& hammer = getHammer();
	//SpacialGhost& spacialGhost = getSpacialGhost();
	///////////////////
	setCurrItr(0);  //reset the itr counter
	std::pair<int, char> next_step;
	//int curr_itr = 0;  //itr index

	if (!steps.isEmpty())
		next_step = steps.popStep();  // gets the first step (if exist)

	// moving loop for mario and barrels
	for(int i = 0; i < final_itr; i++) {  //change the condition to a final itr - need to be saved in file
		// increament for the itr counter
		setCurrItr(getCurrItr() + 1);
		mario.draw();
		enemiesManager.draw(mario);
		hammer.draw();
		//spacialGhost.draw(); // for debug

		// check and get user input
		for (int i = 0; i < 2; i++) {
			if (getCurrItr() == next_step.first) {
				mario.keyPressed(next_step.second);
				if (!steps.isEmpty())
					next_step = steps.popStep();  //get the next step
			}
			Sleep(10);
		}

		mario.erase();
		mario.move();
		hammer.erase();

		// check if mario has met and used hammer
		checkHammer(mario, hammer);
		if (mario.getSmash()) {
			marioHit();
		}

		enemiesManager.move(mario);
		//spacialGhost.erase(); // for debug
		//spacialGhost.move(); // for debug

		// if mario encounters a barrel, reset the stage or game over
	/*	checkBarrelEncounters(barrelsManager, mario);
		checkGhostEncounters(ghostsManager, mario);*/
		checkEnemyEncounters(enemiesManager, mario);

		enemiesManager.barrelsActivation(); // reseting the barrel activation	

		// draw the score 
		if (!enemiesManager.getEncounters())
			mario.drawScore();

		// check if mario has fallen 5 lines and reset the stage
		if (mario.fellTooFar() && mario.isOnFloor()) {
			explodeMarioAndResetStage(mario);
			if (results.popResult().second != results.ResultValue::ENC_FALL) {
				reportResultError("Result file does not match Mario fell too far", getBoard().getBoardName(), getCurrItr());
			}
		}

		//if mario meets Pauline, game won
		marioMetPauline(mario);

		if (mario.getLives() == 0) {
			if (results.popResult().second != results.ResultValue::GAME_LOSE) {
				reportResultError("Result file does not match game over", getBoard().getBoardName(), getCurrItr());
			}
		}
	}
}

void GameFromFile::reportResultError(const std::string& message, const std::string& filename, size_t iteration) {
	system("cls");
	std::cout << "Screen" << filename << " - " << message << '\n';
	std::cout << "Iteration: " << iteration << '\n';
	std::cout << "Press any key to continue to next screen (if any)" << std::endl;
	_getch();
}
