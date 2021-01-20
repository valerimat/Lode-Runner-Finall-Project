#include "MacroSettings.h"

// c-tor
MacroSettings::MacroSettings()
{
	m_height = 850;
	m_width = 800;
	m_volume = 50;
	m_sacle_height = 0;
	m_scale_width = 0;
	m_map_height= 0;
	m_map_width= 0;
}
//-------------------------------------------------------------------

// gets height
int MacroSettings::GetHeight()
{
	return m_height;
}
//-------------------------------------------------------------------

// gets width
int MacroSettings::GetWidth()
{
	return m_width;
}
//-------------------------------------------------------------------

// gets volume
int MacroSettings::GetVolume()
{
	return m_volume;
}
//-------------------------------------------------------------------

// sets height
void MacroSettings::SetHeight(int num)
{
	m_height = (num > 0) ? num : 850;
}
//-------------------------------------------------------------------

// sets width
void MacroSettings::SetWidth(int num)
{
	m_width = (num > 0) ? num : 800;
}
//-------------------------------------------------------------------

// sets volume
void MacroSettings::SetVolume(int num)
{
	m_volume = (num > 0) ? num : 50;
}
//-------------------------------------------------------------------
void MacroSettings::SetMapHeight(int num)
{
	m_map_height = num;
	m_sacle_height = ((float)m_width / (float)num)/50.f;
}
//-------------------------------------------------------------------
void MacroSettings::SetMapWidth(int num)
{
	m_map_width = num;
	m_scale_width = ((float)m_width / (float)num) / 50.f;
}
//-------------------------------------------------------------------
float MacroSettings::GetScaleHeight()
{
	return m_sacle_height;
}
//-------------------------------------------------------------------
float MacroSettings::GetScaleWidth()
{
	return m_scale_width;
}
//-------------------------------------------------------------------
float MacroSettings::GetSizeOfTile()
{
	return GetScaleWidth() * 50;
}
//-------------------------------------------------------------------