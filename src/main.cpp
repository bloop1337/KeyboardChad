#include "WordList.hpp"
#include "Util.hpp"
#include "FileUtil.hpp"
#include "user_storage.hpp"
#include "Elements.hpp"
#include "Window.hpp"
#include <iostream>
#include "WinSize.hpp"
#include "window_factory.hpp"

using namespace tui;
using namespace utils;

int main() {
    kbchad::init_defaults();

	WordList list = WordList{kbchad::get_home() + "/.local/share/kbchad/english.txt"};

//	kbchad::Typing_Window tw = kbchad::type_window(list);

	util::enableAlterScr();
	util::hideCursor();
	
	tui::Window w = Window{std::make_shared<tui::size::FullScreen>()};
	kbchad::User_Context uc = kbchad::load_ud();
	
	std::string wpm_line = "AVG WPM: ";
	float avg_wpm = 0;
	int counter = 0;
	for (const kbchad::Wpm_Test& test: uc.tests) {
		avg_wpm+=test.wpm;
		++counter;
	}
	avg_wpm/=counter;
	wpm_line += std::to_string(avg_wpm);

	w.setContent({
		text("KeyboardChad") | centerX | centerY,
		text(wpm_line) | centerX,
	});
	

	while (true) {
		w.renderDiff();
		char ch = util::getch();
		if (ch == Key::ESC) break;
//		if (!tw.input()->isEnd()) {
//			tw.renderDiff();
//			char ch = util::getch();
//			if (ch == Key::ESC) break;
//			tw.press_key((Key)ch);
//		} else {
//			Window statistic = kbchad::statistic_window(tw);
//			util::clearScr();
//			statistic.renderDiff();	
//			char ch = util::getch();
//			if (ch == Key::ESC) break;
//			statistic.press((Key)ch);
//		}
	}

	util::disablAlterScr();
	util::showCursor();
    return 0;
}
