#pragma once


class Lives
{
public:
	Lives();
	void SetLives();
	void DecLives();
	void AddLives();
	int  GetLives();

private:
	int m_lives;

};