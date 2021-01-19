#pragma once


class Lives
{
public:
	void set_lives()
	{
		m_lives = 1;
	}
	int GetLives()
	{
		return m_lives;
	}
	void dec_lives()
	{
		--m_lives;
	}
	void AddLives()
	{
		++m_lives;
	}
private:

	int m_lives;

};