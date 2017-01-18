/*! \brief Holds all score information required for the game.
*
*
*
*/

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

	int getKillStreak();
	void setKillStreak();
	void resetKillStreak();

	void updatePlayTime(float time);
	float getPlayTime();

	void reset();

private:
	static Score *m_inst;

	// Disallow Copying
	Score(const Score&);
	Score& operator=(const Score&);

	int m_score;
	int m_numOfAliveAstros;
	bool m_displayAstroText;
	int m_killSreak;
	float m_playTime;

	Score();
	~Score();
};

