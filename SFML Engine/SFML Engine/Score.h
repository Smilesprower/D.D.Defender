#pragma once
class Score
{
public:

	static Score * Instance();
	void increaseScore(int score);
	int getScore();
	int getAliveAstros();
	void removeAstro();

	bool canDisplayAstroText();
	void setDisplayAstroText(int can);

private:
	static Score *m_inst;

	// Disallow Copying
	Score(const Score&);
	Score& operator=(const Score&);

	int m_score;
	int m_numOfAliveAstros;
	bool m_displayAstroText;

	Score();
	~Score();
};

