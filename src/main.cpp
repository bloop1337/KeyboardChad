// KeyboardChad is a simple terminal-based typing practice tool 
// Copyright (C) 2026 bloop
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-2.0

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
