#pragma once
#include <SFML/Graphics.hpp>

// singleton class for clock
class MacroSettings
{
public:
	// get singleton
	static MacroSettings& get_settings(){ static MacroSettings s_settings; return s_settings; };

	// setters
	void set_height(int num);
	void set_width(int num);
	void set_volume(int num);
	void set_map_height(int num);
	void set_map_width(int num);

	// getters
	int get_height();
	int get_width();
	int get_volume();
	float get_scale_height();
	float get_scale_width();
	float get_size_of_tile();

private:

	// c-tor
	MacroSettings();

	// avoids copy 
	MacroSettings(const MacroSettings&) = delete;
	void operator=(MacroSettings const&) = delete;

	// private members
	float m_sacle_height;
	float m_scale_width;
	int   m_map_height;
	int   m_map_width;
	int   m_height;
	int   m_width;
	int   m_volume;
};
