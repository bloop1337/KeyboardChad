#pragma once

#include <Pixel.hpp>

namespace kbchad::config {
	constexpr unsigned int WORD_COUNT    = 25;
	constexpr unsigned int MIN_ACCURACY  = 80;

	constexpr tui::Pixel_Style ERROR = {
		.mode = tui::Pixel_Graphic_Mode::STRIKE,
		.fg   = tui::Pixel_Fg_Color::RED,
		.bg   = tui::Pixel_Bg_Color::DEFAULT,
	};

	constexpr tui::Pixel_Style FINE = {
		.mode = tui::Pixel_Graphic_Mode::BOLD,
		.fg   = tui::Pixel_Fg_Color::DEFAULT,
		.bg   = tui::Pixel_Bg_Color::DEFAULT,
	};

	constexpr tui::Pixel_Style CURSOR = {
		.mode = tui::Pixel_Graphic_Mode::INVERSE,
		.fg   = tui::Pixel_Fg_Color::DEFAULT,
		.bg   = tui::Pixel_Bg_Color::DEFAULT,
	};

};
