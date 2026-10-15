#include <Util.hpp>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

namespace tui {

	char getch() {
        char buf = 0;
		struct termios old = {0};
        
		if (tcgetattr(0, &old) < 0)
            std::cerr << "error: getattr()";
        
		old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        
		if (tcsetattr(0, TCSANOW, &old) < 0)
                std::cerr << "tcsetattr ICANON";
        
		if (read(0, &buf, 1) < 0)
                std::cerr << "read()";
        
		old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        
		if (tcsetattr(0, TCSADRAIN, &old) < 0)
                std::cerr << "tcsetattr ~ICANON";

        return (buf);

	}

	void enableAlterScr() {
		std::cout << "\x1B[?1049h";
	}
	void disablAlterScr() {
		std::cout << "\x1B[?1049l";
	}
	
	void clearScr() {
		std::cout << "\x1B[2J";
	}

	void hideCursor() {
		std::cout << "\x1B[?25l";
	}
	void showCursor() {
		std::cout << "\x1B[?24h";
	}
    
    void moveCursor(int x, int y) {
        std::cout << "\x1B[" << y << ";" << x+1 << "H";
    }
	
	void end_render() {
		disablAlterScr();
		showCursor();
	}

	
	void begin_render() {
		enableAlterScr();
		clearScr();
	}


	void set_ctrlc_handler(void(*handler)(int s)) {
		struct sigaction sa;
		sa.sa_handler = handler;
	    sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;

		sigaction(SIGINT, &sa, NULL);
	}
}
