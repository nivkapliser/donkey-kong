#include "GameFromKeyboard.h"

// Function to show the menu and get user input
void GameFromKeyboard::showMenu() {
	MenuGraphics& menuGraphics = getMenuGraphics();
	char choice;
	bool run = true;
	std::string input; // to clear the buffer

	menuGraphics.displayMenu();

	while (run) {
		std::cout << "Enter Your Choice: ";
		std::getline(std::cin, input);

		if (input.length() == 1) {
			choice = input[0];
			switch (choice) {
			case '1':
				if (showAndLoadBoards()) {
					if (save)
						clearPreviousFiles();
					currentState = GameState::RUNNING;
					run = false;
				}
				else {
					currentState = GameState::FINISH;
					return;
				}
				break;
			case '2':
				menuGraphics.disableColors();
				break;
			case '8':
				menuGraphics.displayInstructions();
				run = false;
				break;
			case '9':
				currentState = GameState::FINISH;
				return;
			default:
				system("cls"); // for priting in the screen size
				menuGraphics.displayMenu();
				std::cout << "Invalid Choice. Please try again.\n";
			}
		}
		else {
			system("cls"); // for printing in the screen size
			menuGraphics.displayMenu();
			std::cout << "Invalid Choice. Please try again.\n";
		}
	}
	system("cls");
}

// Function to run the game and control the states
void GameFromKeyboard::run() {
	MenuGraphics& menuGraphics = getMenuGraphics();
	Board& board = getBoard();
	Mario& mario = getMario();
	bool run = true;

	menuGraphics.displayOpenScreen();
	while (run) {
		switch (getGameState()) {	
		case GameState::MENU:		// the default game state
			showMenu();
			break;
		case GameState::RUNNING:	// to start the game movement loop
			initGame();
			results.setLives(mario.getLives());
			results.setScore(mario.getScore());
			runGame();
			break;
		case GameState::RESUME:		// to resume the game after pausing
			board.print();
			mario.drawLife();
			currentState = GameState::RUNNING;
			runGame();
			break;
		case GameState::PAUSED:		// to pause the game
			pauseGame();
			break;
		case GameState::GAME_OVER:	// to display game over screen and return to menu
			saveFiles();
			menuGraphics.displayGameOver();
			currentState = GameState::MENU;
			break;
		case GameState::GAME_WON:	// to display game won screen and return to menu
			saveFiles();
			setCurrItr(0);
			menuGraphics.displayGameWon();
			checkNextStage();
			break;
		case GameState::NEXT_STAGE:	// moving on to the next stage after winning
			resetStage();
			results.setLives(mario.getLives());
			results.setScore(mario.getScore());
			runGame();
			break;
		case GameState::FINISH:		// to exit the game loop
			run = false;
			break;
		default:
			currentState = GameState::MENU; // default state
			break;
		}
	}
	Sleep(50);
	menuGraphics.displayGoodBye();
}

// Function to run the game loop
void GameFromKeyboard::runGame() {
	Mario& mario = getMario();
	EnemiesManager& enemiesManager = getEnemiesManager();
	Hammer& hammer = getHammer();
	results.clearResults();
	steps.clearSteps();
	steps.setRandomSeed(getRandomSeed());	

	// moving loop for mario and barrels
	while (currentState == GameState::RUNNING || currentState == GameState::NEXT_STAGE) {
		mario.draw();
		enemiesManager.draw(mario);
		hammer.draw();

		// check and get user input
		for (int i = 0; i < 2; i++) {
			if (_kbhit()) {
				char key = _getch();
				if (key == ESC) {
					currentState = GameState::PAUSED;
					break;
				}
				if (mario.keyPressed(key) && save == true) //if the key is a legit key and save mode is on
					steps.addStep(getCurrItr(), key);
			}
			Sleep(25);
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

		// if mario encounters a barrel or ghost, reset the stage or game over
		checkEnemyEncounters(enemiesManager, mario);

		enemiesManager.barrelsActivation(); // reseting the barrel activation

		// draw the score 
		if (!enemiesManager.getEncounters())
			mario.drawScore();

		// check if mario has fallen 5 lines and reset the stage
		if (mario.fellTooFar() && mario.isOnFloor()) {
			results.addResult(getCurrItr(), Results::ResultValue::ENC_FALL);
			explodeMarioAndResetStage(mario);
		}
			

		// if mario meets Pauline, game won
		marioMetPauline(mario);

		if (currentState == GameState::GAME_OVER) {
			if (save) 
			{
				results.addResult(getCurrItr(), Results::ResultValue::GAME_LOSE);
			}
			break;
		}
		setCurrItr(getCurrItr() + 1);
	}
}

// Pauses the game and waits for user input to resume or return to menu
void GameFromKeyboard::pauseGame() {
	MenuGraphics& menuGraphics = getMenuGraphics();

	menuGraphics.displayStopScreen();
	while (currentState == GameState::PAUSED) {
		if (_kbhit()) {
			char key = _getch();
			if (key == ESC) {
				currentState = GameState::RESUME;
			}
			else {
				currentState = GameState::MENU;
			}
		}
	}
}

// Function to check if there is a next stage and move to it
void GameFromKeyboard::checkNextStage() { 
	int currentBoardIndex = getCurrBoardIndex();	
	std::vector<std::string> boardFiles = getBoards();	
	Board& board = getBoard();
	Hammer& hammer = getHammer();
	Mario& mario = getMario();

	if (currentBoardIndex < boardFiles.size()) {
		setCurrentBoardIndex(++currentBoardIndex);
		board.readBoard(boardFiles[currentBoardIndex - 1], mario, hammer);
		currentState = GameState::NEXT_STAGE;
	}
	else
		currentState = GameState::MENU;
}

// Function to reset the stage after mario dies
void GameFromKeyboard::explodeMarioAndResetStage(Mario& mario) {	
	Game::explodeMarioAndResetStage(mario);
	if (mario.getLives() == 0) {
		currentState = GameState::GAME_OVER;
	}
}

// Function to check if mario has encountered a barrel or ghost
bool GameFromKeyboard::checkEnemyEncounters(EnemiesManager& em, Mario& mario) {
	if (em.getEncounters()) {
		mario.downLives();
		results.addResult(getCurrItr(), Results::ResultValue::ENC_ENEMY);
		resetStage();
		if (mario.getLives() == 0) {
			currentState = GameState::GAME_OVER;
		}
		em.setEncounters(false);
		return true;
	}
	return false;
}

// Function to save the results and steps to files
void GameFromKeyboard::saveFiles() {
	if (save) {
		results.saveResults(createFileName(getBoard().getBoardName(), "results"));	
		steps.setFinalItr(getCurrItr());
		steps.saveSteps(createFileName(getBoard().getBoardName(), "steps"));
	}
}

void GameFromKeyboard::clearPreviousFiles()
{
		namespace fs = std::filesystem;

		try {
			for (const auto& entry : fs::directory_iterator(".")) {
				if (!entry.is_regular_file()) continue;  // skip directories and special files

				std::string fileName = entry.path().filename().string();

				// check if the filename ends with "steps" or "results"
				if (fileName.size() >= 5 &&
					(fileName.substr(fileName.size() - 5) == "steps" ||
						fileName.substr(fileName.size() - 7) == "results")) {

					fs::remove(entry.path());  // delete the file safely
				}
			}
		}
		catch (...) {
			// silently catch all exceptions (no aborts)
		}
}

// Function to check if mario has met Pauline
bool GameFromKeyboard::marioMetPauline(Mario& mario) {
	if (mario.metPauline()) {
		currentState = GameState::GAME_WON;
		results.addResult(getCurrItr(), Results::ResultValue::STAGE_FINISH);
		return true;
	}
	return false;
}
