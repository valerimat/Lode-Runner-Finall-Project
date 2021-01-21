#pragma once


class Lives
{
public:

	// c-tor
	Lives();

	void set_lives();
	int  get_lives();

	void add_lives();
	void dec_lives();

private:
	int m_lives;
};