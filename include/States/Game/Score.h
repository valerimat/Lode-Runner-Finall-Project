#pragma once

class Score
{
public:
	static Score& GetScore() {static Score s_score; return s_score;};

	int  GetPoints();
	void IncreasePoints();
	void reset_score();
	void advance_level();

private:
	Score();

	// avoids copy 
	Score(const Score&) = delete;
	void operator=(Score const&) = delete;

	int lvl = 1;
	int m_score;
};
