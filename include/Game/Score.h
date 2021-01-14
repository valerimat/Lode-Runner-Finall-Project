#pragma once

class Score
{
public:
	static Score& GetScore() {static Score s_score; return s_score;};

	int  GetPoints();
	void IncreasePoints(int lvl);

private:
	Score();

	// avoids copy 
	Score(const Score&) = delete;
	void operator=(Score const&) = delete;

	int m_score;
};
