#pragma once
#include <vector>

namespace kbchad {	
	struct Typing_Session_Context {
		long start_time;
		long end_time;
		int errors;
		int text_size;
		int words_count;
	};
	
	struct Wpm_Test {
		float wpm;
		float acc;
		int errors;
		int words_count;
		long typing_time;
	};

	struct User_Context {
		std::vector<Wpm_Test> tests;
	};
};
