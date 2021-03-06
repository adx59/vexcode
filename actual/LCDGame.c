/*
Easy WR: 1521 pts - Alan Luo
Hard WR: 493 pts - Alan Luo
Food WR: 1275 pts - Alan Luo
*/

// state of the game
int gameState = 2; // 0 = end of game, 1 = playing game, 2 = in menus
bool foodActive = false;
int foodCycles = 0;

// player attributes
int player = 0;
int score = 0;
int lives = 3;
char playerChar = '$';

// enemies / obstacles
int eLn[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int ePos[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

// food
int fLn[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int fPos[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

// variables controlling difficulty
bool useFood = false;
int mechDelay = 500;
int minDelay = 220;
int minusDelay = 20;

task watchButtons() {
	int cachedButton = nLCDButtons;
	while (true) {
			if (nLCDButtons == 1 || vexRT[Btn6U] == 1) {
				player = 0;
			} else if (nLCDButtons == 2 || vexRT[Btn6D] == 1) {
				player = 1;
			}
			if (gameState == 2) {
				if (nLCDButtons == 4 || vexRT[Btn8R] == 1) {
					gameState = 1;
				}
				if (nLCDButtons == 2 || vexRT[Btn8D] == 1) {
					minDelay = 175;
					minusDelay = 25;
					gameState = 1;
				}
				if (nLCDButtons == 1 || vexRT[Btn8L] == 1) {
					useFood = true;
					gameState = 1;
				}
			}
			cachedButton = nLCDButtons;
	}
}

task render() {
	while (true) {
		char row[2][16];

		row[player][0] = playerChar;
		row[1 - player][0] = ' ';

		for (int i = 1; i < 16; i++){
			row[player][i] = ' ';
			row[1 - player][i] = ' ';
		}

		for (int i = 0; i < 16; i++){
			int line = eLn[i];
			int pos = ePos[i];

			if (line <= -1 || pos <= -1) {
				continue;
			}

			if (!foodActive) {
				row[line][pos] = '<';
			} else {
				row[line][pos] = '>';
			}
		}
		for (int i = 0; i < 16; i++) {
			if (fLn[i] <= -1 || fPos[i] <= -1) {
				continue;
			}

			row[fLn[i]][fPos[i]] = '%';
		}

		row[0][15] = lives + '0';

		string ln0 = "";
		string ln1 = "";

		for (int c1 = 0; c1 < 16; c1++) {
			ln0 += row[0][c1];
		}

		for (int c2 = 0; c2 < 16; c2++) {
			ln1 += row[1][c2];
		}

		displayLCDString(0, 0, ln0);
		displayLCDString(1, 0, ln1);
	}
}

task manageGameMechanics() {
	int loops = 0;
	while (true) {
		delay(mechDelay);

		// end game if player dead
		if (lives == 0) {
			gameState = 0;
		}

		for (int i = 0; i < 16; i++) {
			// move obstacles and food
			ePos[i] -= 1;
			fPos[i] -= 1;

			// hit detection
			if (eLn[i] == player && ePos[i] == 0) {
				if (foodActive) {
					score += 5;
					writeDebugStream("boosted boi");
				} else {
					lives--;
				}
			} else if (fLn[i] == player && fPos[i] == 0) {
				foodActive = true;
			}
		}

		if (foodCycles == 30) {
				foodActive = false;
				foodCycles = 0;
		}

		// spawn obstacles
		if (loops % 2 == 0) {
			int where = 0;
			for (int i = 0; i < 16; i++){
				if (eLn[i] <= -1 || ePos[i] <= -1) {
					where = i;
					break;
				}
			}

			srand(nSysTime);
			int randInt = random(50);
			if (randInt >= 25) {
				eLn[where] = 1;
			} else {
				eLn[where] = 0;
			}
			ePos[where] = 15;
		}

		// spawn food
		if (useFood) {
			if (loops % 120 == 0) {
				int where = 0;
				for (int i = 0; i < 16; i++){
					if (fLn[i] <= -1 || fPos[i] <= -1) {
						where = i;
						break;
					}
				}

				int randInt = random(50);
				if (randInt >= 25) {
					fLn[where] = 1;
				} else {
					fLn[where] = 0;
				}
				fPos[where] = 15;

				for (int i = 0; i < 16; i++) {
					if (eLn[i] == fLn[where] && ePos[i] == fPos[where]) {
						eLn[i] = -1;
						ePos[i] = -1;
					}
				}
			}
		}

		// make game harder as progresses
		if (loops % 10 == 0 && mechDelay > minDelay) {
			mechDelay -= minusDelay;
		}

		if (foodActive) {
			foodCycles++;
		}

		score++;
		loops++;
	}
}

task main() {
	bLCDBacklight = true;

	startTask(watchButtons);

	while (gameState == 2) {
			displayLCDCenteredString(0, "Lasa'gna");
			displayLCDString(1, 0, "Food  Hard  Easy");
	}

	startTask(render);
	startTask(manageGameMechanics);

	clearLCDLine(0);
	clearLCDLine(1);

	while(true){
		if (gameState == 0) {
			stopTask(render);
			stopTask(manageGameMechanics);

			clearLCDLine(0);
			clearLCDLine(1);

			string scoreString;
			sprintf(scoreString, "Score: %d", score);

			displayLCDCenteredString(0, "Game over!");
			displayLCDCenteredString(1, scoreString);
		}
	}
}
