#pragma once



class Hud
{
public:
	void draw();
	void set_score();
	void set_live();

private:
	int m_score;
	int m_lives;

};