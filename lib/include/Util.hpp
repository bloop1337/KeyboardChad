
#pragma once

namespace tui {

	void begin_render();
	void end_render();

	char getch();
	void enableAlterScr();
	void disablAlterScr();
	void clearScr();
	void hideCursor();
	void showCursor();
    void moveCursor(int x, int y);


	void set_ctrlc_handler(void(*handler)(int s));
}
