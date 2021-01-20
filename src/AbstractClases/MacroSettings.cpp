#include "MacroSettings.h"

// c-tor
MacroSettings::MacroSettings()
{
	m_height = 850;
	m_width = 800;
	m_volume = 80;
	m_sacle_height = 0;
	m_scale_width = 0;
	m_map_height= 0;
	m_map_width= 0;
}
//-------------------------------------------------------------------

// gets height
int MacroSettings::get_height()
{
	return m_height;
}
//-------------------------------------------------------------------

// gets width
int MacroSettings::get_width()
{
	return m_width;
}
//-------------------------------------------------------------------

// gets volume
int MacroSettings::get_volume()
{
	return m_volume;
}
//-------------------------------------------------------------------

// sets height
void MacroSettings::set_height(int num)
{
	m_height = (num > 0) ? num : 850;
}
//-------------------------------------------------------------------

// sets width
void MacroSettings::set_width(int num)
{
	m_width = (num > 0) ? num : 800;
}
//-------------------------------------------------------------------

// sets volume
void MacroSettings::set_volume(int num)
{
	m_volume = (num > 0) ? num : 50;
}
//-------------------------------------------------------------------
void MacroSettings::set_map_height(int num)
{
	m_map_height = num;
	m_sacle_height = ((float)m_width / (float)num)/50.f;
}
//-------------------------------------------------------------------
void MacroSettings::set_map_width(int num)
{
	m_map_width = num;
	m_scale_width = ((float)m_width / (float)num) / 50.f;
}
//-------------------------------------------------------------------
float MacroSettings::get_scale_height()
{
	return m_sacle_height;
}
//-------------------------------------------------------------------
float MacroSettings::get_scale_width()
{
	return m_scale_width;
}
//-------------------------------------------------------------------
float MacroSettings::get_size_of_tile()
{
	return get_scale_width() * 50;
}
//-------------------------------------------------------------------