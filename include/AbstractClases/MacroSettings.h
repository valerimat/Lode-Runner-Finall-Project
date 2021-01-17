#pragma once
#include <SFML/Graphics.hpp>

// singleton class for clock
class MacroSettings
{
public:
	static MacroSettings& GetSettings() { static MacroSettings s_settings; return s_settings; };

	int GetHeight();
	int GetWidth();
	int GetVolume();

	void SetHeight(int num);
	void SetWidth(int num);
	void SetVolume(int num);

private:
	MacroSettings();

	// avoids copy 
	MacroSettings(const MacroSettings&) = delete;
	void operator=(MacroSettings const&) = delete;
	           
	int m_height;
	int m_width;
	int m_volume;
};
