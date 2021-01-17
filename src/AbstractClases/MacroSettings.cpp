#include "MacroSettings.h"

// c-tor
MacroSettings::MacroSettings()
{
	m_height = 850;
	m_width = 800;
	m_volume = 50;
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