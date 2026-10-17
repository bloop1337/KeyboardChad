
#include "wpm_test_utils.hpp"
#include <sstream>
#include <iterator>
#include "config.hpp"

namespace kbchad {

	bool is_valid_test(const Wpm_Test& test) {
		return test.acc > config::MIN_ACCURACY;	
	}
	// Source - https://stackoverflow.com/a/3672259
	// Posted by Loki Astari, modified by community. See post 'Timeline' for change history
	// Retrieved 2026-10-09, License - CC BY-SA 2.5
	unsigned int word_count(std::string const& str) {
   		std::stringstream stream(str);
    	return std::distance(
			std::istream_iterator<std::string>(stream),
			std::istream_iterator<std::string>()
		) - 1;
	}

};
