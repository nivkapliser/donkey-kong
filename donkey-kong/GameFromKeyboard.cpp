#include "GameFromKeyboard.h"

void GameFromKeyboard::showMenu() {
	MenuGraphics menuGraphics = getMenuGraphics();
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
					currentState = GameState::RUNNING;
					run = false;
				}
				else
				{
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
			results.addResult(getCurrItr(), Results::ResultValue::GAME_FINISH);
			saveFiles();
			menuGraphics.displayGameOver();
			currentState = GameState::MENU;
			break;
		case GameState::GAME_WON:	// to display game won screen and return to menu
			results.addResult(getCurrItr(), Results::ResultValue::GAME_WON);
			saveFiles();
			setCurrItr(0);
			menuGraphics.displayGameWon();
			checkNextStage();
			break;
		case GameState::NEXT_STAGE:	// moving on to the next stage after winning
			// currItr is 0
			resetStage();
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


void GameFromKeyboard::runGame() {
	Mario& mario = getMario();
	BarrelManager& barrelsManager = getBarrelManager();
	GhostManager& ghostsManager = getGhostManager();
	Hammer& hammer = getHammer();
	SpacialGhost& spacialGhost = getSpacialGhost();

	steps.setRandomSeed(getRandomSeed());

	// moving loop for mario and barrels
	while (currentState == GameState::RUNNING || currentState == GameState::NEXT_STAGE) {
		setCurrItr(getCurrItr() + 1);
		mario.draw();
		barrelsManager.draw(mario);
		ghostsManager.draw(mario);
		hammer.draw();
		spacialGhost.draw(); // for debug

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

		barrelsManager.move(mario);
		ghostsManager.move(mario);
		spacialGhost.erase(); // for debug
		spacialGhost.move(); // for debug

		// if mario encounters a barrel, reset the stage or game over
		checkBarrelEncounters(barrelsManager, mario);
		checkGhostEncounters(ghostsManager, mario);

		barrelsManager.barrelsActivation(); // reseting the barrel activation

		// draw the score 
		if (!ghostsManager.getEncounters() && !barrelsManager.getEncounters())
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
				// moved to the state control
				//steps.setFinalItr(getCurrItr());
				//std::string steps_f_name = createFileName(getBoard().getBoardName(), "steps");
				//steps.saveSteps(steps_f_name);
				results.addResult(getCurrItr(), Results::ResultValue::GAME_LOSE);
			}
			break;
		}
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
void GameFromKeyboard::checkNextStage() { // maybe should be inputs
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

void GameFromKeyboard::explodeMarioAndResetStage(Mario& mario) {	
	Game::explodeMarioAndResetStage(mario);
	if (mario.getLives() == 0) {
		currentState = GameState::GAME_OVER;
	}
}

void GameFromKeyboard::checkBarrelEncounters(BarrelManager& bm, Mario& mario) {
	if (bm.getEncounters()) {
		mario.downLives();
		results.addResult(getCurrItr(), Results::ResultValue::ENC_BARREL);
		resetStage();
		if (mario.getLives() == 0) {
			currentState = GameState::GAME_OVER;
		}
		bm.setEncounters(false);
	}
}

void GameFromKeyboard::checkGhostEncounters(GhostManager& gm, Mario& mario) {
	if (gm.getEncounters()) {
		mario.ghosted();
		results.addResult(getCurrItr(), Results::ResultValue::ENC_GHOST);
		mario.downLives();
		resetStage();
		if (mario.getLives() == 0) {
			currentState = GameState::GAME_OVER;
		}
		gm.setEncounters(false);
	}
}

void GameFromKeyboard::saveFiles() {
	results.saveResults(createFileName(getBoard().getBoardName(), "results"));
	steps.setFinalItr(getCurrItr());
	steps.saveSteps(createFileName(getBoard().getBoardName(), "steps"));
}
