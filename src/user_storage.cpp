#include "user_storage.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#include <unistd.h>

namespace kbchad {
	constexpr std::string MINI_DICT[10] = {
		"there",
		"when",
		"leave",
		"another",
		"wood",
		"man",
		"school",
		"include",
		"delete",
		"fox",
	};

	using namespace std::filesystem;

	std::string get_home() {
		const char* home = getenv("HOME");
		if (home == nullptr) {
			throw std::runtime_error("HOME environment variable is not set");
		}
		return std::string(home);
	}

	void init_defaults() {
		std::string kbchad_data = get_home() + "./local/share/kbchad/";
        std::ifstream f(kbchad_data);
		if (!f.good()) create_directories(path(kbchad_data));

		std::ofstream user_data(kbchad_data + "userdata.csv");
		user_data << "wpm,acc,errors,words_count,typing_time\n";

		std::ifstream english(path(kbchad_data + "english.txt"));
		if (english.good()) return;	

		if (!copy_file(path("static/englsih.txt"), path(kbchad_data))) {
			std::ofstream outfile(kbchad_data + "english.txt");
			for (int i = 0; i < 10; ++i) outfile << MINI_DICT[i] << "\n";
		}
	}

	User_Context load() {
		
		return {};
	}


	bool write(User_Context context) {
		return false;
	}
};

