#pragma once
#include "Window.hpp"

#include "user_context.hpp"

#include <Elements.hpp>
#include <TextWidget.hpp>
#include <Input.hpp>
#include <chrono>

namespace kbchad {

	enum class CurrentState {
		ShowStatistic, ShowProfile, RestartTest, Exit, None
	};

	class Screen {
	public:
		virtual void render(tui::Window& w)       = 0;
		virtual CurrentState on_key(tui::Key key) = 0;
		~Screen() = default;
	};



	class TypingScreen: public Screen {
	private:	
		std::shared_ptr<tui::Input> input_;
		Typing_Session_Context context_;
	
	public:
		TypingScreen(); 
	
		void render(tui::Window& w)       override;	
		CurrentState on_key(tui::Key key) override;	
		void reset_input(const std::string sentence);	
		Typing_Session_Context& context();
	};


	class TestStatisticScreen: public Screen {
	private:	
		Typing_Session_Context context_;
	
	public:
		explicit TestStatisticScreen(Typing_Session_Context context);
		
		void render(tui::Window& w) override;
		CurrentState on_key(tui::Key key) override;
	};


	class ProfileScreen: public Screen {
	private:	
		User_Context context_;

	public:	
		explicit ProfileScreen(User_Context context);
		
		float avg_wpm();	
		int test_completed();
		std::pair<std::chrono::hours, std::chrono::minutes> typing_time();

		void render(tui::Window& w) override;
		CurrentState on_key(tui::Key key) override;	
	};


};
