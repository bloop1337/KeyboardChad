#include "user_storage.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
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

		try {
			copy_file(path("static/english.txt"), path(kbchad_data + "english.txt"));
		} catch (const std::runtime_error& err) {
			std::ofstream out(path(kbchad_data + "english.txt"));
			for (int i = 0; i < 10; ++i) out << MINI_DICT[i] << "\n";
		} 
	}

	static std::vector<std::string> split_to_vec(std::string s, char delim) {
    	std::vector<std::string> result;
    	std::stringstream ss(s);
    	std::string item;
    	while (std::getline(ss, item, delim)) {
    	    result.push_back(item);
    	}
    	return result;
	}

	User_Context load_ud() {
		
		User_Context context = { .tests = std::vector<Wpm_Test>() };
		std::ifstream user_data { get_home() + kbchad_home + user_data_fn };

		if (!user_data.good()) return context;
		std::string line;
		getline(user_data, line);

		while (getline(user_data, line)) {
			std::vector<std::string> cont = split_to_vec(line, ',');
			try {
				context.tests.emplace_back(
					std::stof(cont[0]),
					std::stof(cont[1]),
					std::stoi(cont[2]),
					std::stoi(cont[3]),
					std::stol(cont[4])
				);
			} catch (std::invalid_argument& err) {
				continue;
			}	
		}

		user_data.close();
		
		return context;
	}

	bool write_test(const Wpm_Test test) { 
		if (!is_valid_test(test)) return false;

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

