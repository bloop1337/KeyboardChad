#include <WordList.hpp>
#include <Util.hpp>
#include <Window.hpp>

#include "user_storage.hpp"
#include "screen.hpp"

void on_ctrlc(int a) {
	tui::end_render();
	exit(0);
}

int main() {
    kbchad::init_defaults();

	WordList list = WordList{kbchad::get_home() + "/.local/share/kbchad/english.txt"};

	tui::Window w = tui::Window{std::make_shared<tui::size::FullScreen>()};
	std::unique_ptr<kbchad::Screen> s  = std::make_unique<kbchad::TypingScreen>();	
	
	static_cast<kbchad::TypingScreen*>(s.get())->reset_input(list.generateSentence(10));

	tui::begin_render();
	tui::set_ctrlc_handler(&on_ctrlc);
	tui::hideCursor();

	bool running = true;
	while (running) {
		
		s->render(w);
	
		switch(s->on_key((tui::Key)tui::getch())) {
			case kbchad::CurrentState::Exit: {
				running = false;
				break;
			}
			case kbchad::CurrentState::RestartTest: {
				s = std::make_unique<kbchad::TypingScreen>();
				static_cast<kbchad::TypingScreen*>(s.get())->reset_input(list.generateSentence(10));
				break;
			}
			case kbchad::CurrentState::ShowStatistic: {	
				kbchad::Typing_Session_Context ctx = static_cast<kbchad::TypingScreen*>(s.get())->context();
				write_test(TSC_to_Wpm_Test(ctx));
				s = std::make_unique<kbchad::TestStatisticScreen>(ctx);
				break;
			}
			case kbchad::CurrentState::ShowProfile: {
				kbchad::User_Context ctx = kbchad::load_ud();
				s = std::make_unique<kbchad::ProfileScreen>(ctx);
				break;
			}
			case kbchad::CurrentState::None:
				break;
		}
	}

	tui::end_render();
    return 0;
}
