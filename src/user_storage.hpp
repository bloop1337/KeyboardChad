#pragma once

#include "user_context.hpp"
#include "wpm_test_utils.hpp"
#include <string>

namespace kbchad {
	void init_defaults();
	std::string get_home();

	User_Context load_ud();
	bool write_test(const Wpm_Test test);	
};

