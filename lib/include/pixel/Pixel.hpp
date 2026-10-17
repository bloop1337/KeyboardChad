#pragma once

#include <format>
#include <string>

namespace tui {

enum class Pixel_Graphic_Mode:unsigned int {
	NONE      = 0,
	BOLD      = 1,
	DIM       = 2,
	ITALIC    = 3,
	UNDERLINE = 4,
	BLINKING  = 5,
	INVERSE   = 7,
	HIDDEN    = 8,
	STRIKE    = 9,
}; 

enum class Pixel_Fg_Color:unsigned int {
	BLACK   = 30,
	RED     = 31,
	GREEN   = 32,
	YELLOW  = 33,
	BLUE    = 34,
	MAGENTA = 35,
	CYAN    = 36,
	WHITE   = 37,
	DEFAULT = 39,
};

enum class Pixel_Bg_Color:unsigned int {
	BLACK   = 40,
	RED     = 41,
	GREEN   = 42,
	YELLOW  = 43,
	BLUE    = 44,
	MAGENTA = 45,
	CYAN    = 46,
	WHITE   = 47,
	DEFAULT = 49,
};

struct Pixel_Style {
	Pixel_Graphic_Mode mode;	
	Pixel_Fg_Color       fg;	
	Pixel_Bg_Color       bg;


    bool operator==(const Pixel_Style& rhs) const = default;
};

struct Pixel {
	char pixelContent = ' ';
	Pixel_Style style = {
		.mode = Pixel_Graphic_Mode::NONE,
		.fg   = Pixel_Fg_Color::DEFAULT,
		.bg   = Pixel_Bg_Color::DEFAULT,
	};

	Pixel() = default;
	Pixel(const char content) : pixelContent(content) {}

	void clearStyles() {
		style.mode = Pixel_Graphic_Mode::NONE;
		style.fg   = Pixel_Fg_Color::DEFAULT;
		style.bg   = Pixel_Bg_Color::DEFAULT;
	}

	std::string with_styles() const {
		return std::format("\033[{};{};{}m{}", (unsigned)style.mode, (unsigned)style.fg, (unsigned)style.bg, pixelContent);
	}

    bool operator==(const Pixel& rhs) const = default;
};
} // namespace
