#include "WordList.hpp"
#include "Util.hpp"
#include "FileUtil.hpp"
#include "user_storage.hpp"
#include "window_factory.hpp"

using namespace tui;
using namespace utils;

int main() {
    kbchad::init_defaults();

	WordList list = WordList{kbchad::get_home() + "/.local/share/kbchad/english.txt"};

	kbchad::Typing_Window tw = kbchad::type_window(list);

	util::enableAlterScr();
	util::hideCursor();

	while (true) {
		if (!tw.input()->isEnd()) {
			tw.renderDiff();
			char ch = util::getch();
			if (ch == Key::ESC) break;
			tw.press_key((Key)ch);
		} else {
			Window statistic = kbchad::statistic_window(tw);
			util::clearScr();
			statistic.renderDiff();	
			char ch = util::getch();
			if (ch == Key::ESC) break;
			statistic.press((Key)ch);
		}
	}

	util::disablAlterScr();
	util::showCursor();
    return 0;
}
