int screenMode = 0;
// 0 = menuscreen, 1 = encounter, 2 = lore

int onEncounter = 0;

int pRow = 0;
int pPos = 0;

int bRow = 1;
int bPos = 15;

int bHealth = 10;
int pHealth = 3;

char player = '$';
char boss;

string menuscreens[3] = {
	"Kill V. Ta'aurc",
	"Slay Borgeth",
	"Slay Savathun"
}

task control() {
										//  spec,  up,    down,  left,  right
	bool buttonDown[5] = {false, false, false, false, false};
	while (true) {
		if (screenMode == 0) {
			if (vexRT[Btn6U] == 1) {
					screenMode = 1;
			}
		} else if (screenMode == 1) {
			if (vexRT[Btn8U] == 1 && !buttonDown[1]) {
				if (pRow == 1) pRow = 0;
				buttonDown[1] = true;
			} else if (vexRT[Btn8U] == 0 && buttonDown[1]) {
				buttonDown[1] = false;
			}

			if (vexRT[Btn8D] == 1 && !buttonDown[2]) {
				if (pRow == 0) pRow = 1;
				buttonDown[2] = true;
			} else if (vexRT[Btn8D] == 0 && buttonDown[2]) {
				buttonDown[2] = false;
			}

			if (vexRT[Btn8L] == 1 && !buttonDown[3]) {
				if (pPos > 0) pPos--;
				buttonDown[3] = true;
			} else if (vexRT[Btn8L] == 0 && buttonDown[3]) {
				buttonDown[3] = false;
			}

			if (vexRT[Btn8R] == 1 && !buttonDown[4]) {
				if (pPos < 15) pPos++;
				buttonDown[4] = true;
			} else if (vexRT[Btn8R] == 0 && buttonDown[4]) {
				buttonDown[4] = false;
			}
		}
	}
}

task render() {
	while (true) {
		if (screenMode == 0) {
			displayLCDCenteredString(0, menuscreens[onEncounter]);
			displayLCDCenteredString(1, "= Start =");
		} else if (screenMode == 1) {
			char screen[2][16] = {
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
			};

			screen[pRow][pPos] = player;
			screen[bRow][bPos] = boss;

			string ln0 = "";
			string ln1 = "";

			for (int c1 = 0; c1 < 16; c1++) {
				ln0 += screen[0][c1];
			}

			for (int c2 = 0; c2 < 16; c2++) {
				ln1 += screen[1][c2];
			}

			displayLCDString(0, 0, ln0);
			displayLCDString(1, 0, ln1);
		} else if (screenMode == 2) {

		}
	}
}

task gameMechanics() {
	while (true) {
		if (screenMode == 1) {
			if (onEncounter == 0) {
				boss = '@';
			}
		}
	}
}

task main() {
	bLCDBacklight = true;

	startTask(render);
	startTask(gameMechanics);
	startTask(control);

	while (true) {}
}
