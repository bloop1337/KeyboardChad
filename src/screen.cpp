#include "screen.hpp"
#include "word_counter.hpp"

#include <chrono>

namespace kbchad {
	using namespace tui;
	using namespace std::chrono;

	TypingScreen::TypingScreen(): input_(std::make_shared<Input>("")), context_({}) {}

	void TypingScreen::render(Window& w) {
		w.setContent({
			text("KeyboardChad") | centerX,
			input_ | centerABS,
			text("[ecs] exit [entr] restart [tab] profile") | buttom | centerX 
		});

		w.renderDiff();
	}

	CurrentState TypingScreen::on_key(tui::Key key) {
		if (key == tui::Key::ESC) return CurrentState::Exit;
		if (key == tui::Key::ENTER) return CurrentState::RestartTest;
		if (key == tui::Key::TAB) return CurrentState::ShowProfile;
		if (context_.start_time == 0) context_.start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		input_->press(key);
		if (input_->isEnd()) {
			context_.errors   = input_->getMisses();
			context_.end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();;
			return CurrentState::ShowStatistic;
		}
		return CurrentState::None;
	}
	
	void TypingScreen::reset_input(const std::string sentence) {
		input_->updateSentence(sentence);
		context_.errors      = 0;
		context_.start_time  = 0l;
		context_.end_time    = 0l;
		context_.text_size   = sentence.size();
		context_.words_count = word_count(sentence);
	}

	Typing_Session_Context& TypingScreen::context() { return context_; }

	TestStatisticScreen::TestStatisticScreen(Typing_Session_Context context): context_(context) {}
	
	void TestStatisticScreen::render(Window& w) {
		const float acc = context_.errors > 0 ? 100.0 - (100.0 * context_.errors / context_.text_size) : 100;
		const float wpm = (context_.words_count * 60000.0 / (context_.end_time - context_.start_time));

		auto stat_text = std::make_shared<tui::TextWidget>(
			"WPM: " + std::to_string(wpm) + 
			" ACC: " + std::to_string(acc) + "%"
		);

		w.setContent({
			text("KeyboardChad") | centerX,
			stat_text | centerABS,
			text("[ecs] exit [entr] restart [tab] profile") | buttom | centerX 
		});

		w.renderDiff();
	}

	CurrentState TestStatisticScreen::on_key(tui::Key key) {
		if (key == tui::Key::ESC) return CurrentState::Exit;
		if (key == tui::Key::ENTER) return CurrentState::RestartTest;
		if (key == tui::Key::TAB) return CurrentState::ShowProfile;
	
		return CurrentState::None;
	}	

	
	ProfileScreen::ProfileScreen(User_Context context): context_(context) {}
	
	float ProfileScreen::avg_wpm() {
		float wpm = 0;	
		if (context_.tests.size() == 0) return wpm;
	
		size_t i = 0;
		for (; i < context_.tests.size(); ++i) {
			wpm+=context_.tests[i].wpm;
		}
		return wpm/i;
	}
	
	int ProfileScreen::test_completed() {
		return context_.tests.size();
	}

	std::pair<hours, minutes> ProfileScreen::typing_time() {
		long typing_time = 0l;
		for (Wpm_Test test: context_.tests) typing_time += test.typing_time;

		auto h = duration_cast<hours>(milliseconds(typing_time));
		auto m = duration_cast<hours>(h - milliseconds(typing_time));

		return {h, m};	
	}

	void ProfileScreen::render(Window& w) {
		w.setContent({
	
			text("KeyboardChad") | centerX,
			
			text("[" + std::format("{:.1f}", avg_wpm()) + "] AVG_WPM " +	
			    "[" + std::to_string(test_completed()) + "] TESTS " +	
				"[" + std::to_string(typing_time().first.count()) + "h " +
				std::to_string(typing_time().second.count()) + " m" + 
			"] OF TYPE") | centerABS,	
			
			text("[ecs] exit [entr] restart [tab] profile") | buttom | centerX 
		});

		w.renderDiff();
	}

	CurrentState ProfileScreen::on_key(tui::Key key) {
		if (key == tui::Key::ESC) return CurrentState::Exit;
		if (key == tui::Key::ENTER) return CurrentState::RestartTest;
		if (key == tui::Key::TAB) return CurrentState::None;
	
		return CurrentState::None;
	}	
};
