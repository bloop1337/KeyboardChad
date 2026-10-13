#include "user_storage.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#include <unistd.h>

namespace kbchad {
	static const std::string user_data_fn = "userdata.csv";
	static const std::string kbchad_home  = "/.local/share/kbchad/";
	static const std::string MINI_DICT[10] = {
		"there",
		"guide",
		"leave",
		"another",
		"monkey",
		"delete",
		"free",
		"quick",
		"chad",
		"pure",
	};

	using namespace std::filesystem;

	std::string get_home() {
		const char* home = getenv("HOME");
		if (home == nullptr) {
			throw std::runtime_error("HOME environment variable is not set");
		}
		return std::string(home);
	}


	static void init_def_dir() {
		std::string kbchad_data = get_home() + kbchad_home;
		std::ifstream f(kbchad_data);
		if (!f.good()) create_directories(path(kbchad_data));
	}



	static void user_data_write(const std::string text) {
		std::string kbchad_data = get_home() + kbchad_home;
		std::ofstream user_data;
		user_data.open(kbchad_data + user_data_fn, std::ios::app);
		user_data << text;
	}

	void init_defaults() {
		const std::string kbchad_data = get_home() + kbchad_home;
		
		init_def_dir();
		
		std::ifstream user_data(kbchad_data + user_data_fn);
		if (!user_data.good())
			user_data_write("wpm,acc,errors,words_count,typing_time\n");

		std::ifstream english(path(kbchad_data + "english.txt"));
		if (english.good()) return;	
		copy_file(path("static/english.txt"), path(kbchad_data + "english.txt"));
	}

	User_Context load() {
		
		return {};
	}

	bool write_test(const Wpm_Test test) {
		user_data_write(
			std::to_string(test.wpm) + "," +
			std::to_string(test.acc) + "," +
			std::to_string(test.errors) + "," +
			std::to_string(test.words_count) + "," +
			std::to_string(test.typing_time) + "\n"
		);

		return true;
	}
};

