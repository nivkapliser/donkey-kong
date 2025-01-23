#include "GameFromFile.h"

//
void GameFromFile::run() {
	showAndLoadBoards();
	initGame();
	runGame();
}

void GameFromFile::checkNextStage()
{
	int currentBoardIndex = getCurrBoardIndex();
	std::vector<std::string> boardFiles = getBoards();
	Board board = getBoard();
	Hammer hammer = getHammer();
	Mario mario = getMario();

	if (currentBoardIndex < boardFiles.size()) {
		setCurrentBoardIndex(++currentBoardIndex);
		board.readBoard(boardFiles[currentBoardIndex - 1], mario, hammer);
		//currentState = GameState::NEXT_STAGE;
	}
	//else
		//currentState = GameState::MENU;
}

void GameFromFile::checkBarrelEncounters(BarrelManager& bm, Mario& mario)
{
	if (bm.getEncounters()) {
		mario.downLives();
		resetStage();
		if (mario.getLives() == 0) {
			//currentState = GameState::GAME_OVER;
		}
		bm.setEncounters(false);
	}
}

void GameFromFile::checkGhostEncounters(GhostManager& gm, Mario& mario)
{
	if (gm.getEncounters()) {
		mario.ghosted();
		mario.downLives();
		resetStage();
		if (mario.getLives() == 0) {
			//currentState = GameState::GAME_OVER;
		}
		gm.setEncounters(false);
	}
}


void GameFromFile::runGame() {
	Steps steps;
	steps = steps.readSteps("board01.steps"); //reading the steps
	setRandomSeed(steps.getRandomSeed());  //random seed set

	//TODO: things that we are exactly doing in regular game - do with it something
	Mario& mario = getMario();
	BarrelManager& barrelsManager = getBarrelManager();
	GhostManager& ghostsManager = getGhostManager();
	Hammer& hammer = getHammer();
	SpacialGhost& spacialGhost = getSpacialGhost();
	///////////////////

	std::pair<int, char> next_step;
	int curr_itr = 0;  //itr index

	if (!steps.isEmpty())
		next_step = steps.popStep();  // gets the first step (if exist)

	// moving loop for mario and barrels
	while (!steps.isEmpty()) {  //change the condition to a final itr - need to be saved in file
		
		mario.draw();
		barrelsManager.draw(mario);
		ghostsManager.draw(mario);
		hammer.draw();
		spacialGhost.draw(); // for debug

		// check and get user input
		if (curr_itr == next_step.first) {
			mario.keyPressed(next_step.second);
			next_step = steps.popStep();  //get the next step
		}
		Sleep(10);

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
		if (mario.fellTooFar() && mario.isOnFloor())
			explodeMarioAndResetStage(mario);

		// if mario meets Pauline, game won
		//marioMetPauline(mario);

		//if (currentState == GameState::GAME_OVER) {
		//	break;
		//}

		curr_itr++; // increament for the itr counter
	}
}
