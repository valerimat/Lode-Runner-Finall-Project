#pragma once


class Lives
{
public:
	void set_lives()
	{
		m_lives = 1;
	}
	int get_lives()
	{
		return m_lives;
	}
	void dec_lives()
	{
		--m_lives;
	}

private:

	int m_lives;

};