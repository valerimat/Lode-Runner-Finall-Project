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
	void SetMapHeight(int num);
	void SetMapWidth(int num);
	float GetScaleHeight();
	float GetScaleWidth();

private:
	MacroSettings();

	// avoids copy 
	MacroSettings(const MacroSettings&) = delete;
	void operator=(MacroSettings const&) = delete;
	float m_sacle_height;
	float m_scale_width;
	int m_map_height;
	int m_map_width;
	int m_height;
	int m_width;
	int m_volume;
};
