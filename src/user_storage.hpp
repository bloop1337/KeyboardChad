#pragma once

#include "user_context.hpp"
#include <string>

namespace kbchad {
	void init_defaults();
	std::string get_home();

	User_Context load();
	bool write_test(const Wpm_Test test);	
};

