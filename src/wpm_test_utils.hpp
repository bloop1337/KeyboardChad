#pragma once

#include <string>
#include "user_context.hpp"

namespace kbchad {
	unsigned int word_count(std::string const& str);

	bool is_valid_test(const Wpm_Test& test);
}
