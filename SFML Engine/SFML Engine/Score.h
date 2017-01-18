/*! \brief Holds all score information required for the game.
*
*
*
*/

#pragma once
class Score
{
public:

	static Score * Instance();			/*!< Set up instance of score class for other classes to access it*/

	void increaseScore(int score);		/*!< Function to increase the score*/
	int getScore();						/*!< Allow other classes to get the current score*/
	
	int getAliveAstros();				/*!< Allow other classes to get the number of astronauts currently alive*/
	void removeAstro();					/*!< Function to remove an astronaut*/

	bool canDisplayAstroText();			/*!< Allows the number of currently alive astronauts to be displayed on screen*/
	void setDisplayAstroText(int can);	/*!< Displays number of astronauts alive*/

	int getKillStreak();				/*!< Allows other classes to get the current killstreak*/
	void setKillStreak();				/*!< Set current killstreak based on enemies killed*/
	void resetKillStreak();				/*!< Reset the killstreak when a health pack has been earned*/

	void updatePlayTime(float time);	/*!< Update the time since the game started*/
	float getPlayTime();				/*!< Access how long the game has been playing for*/

	void reset();						/*!< Reset all score when new game is started*/

	bool getGameWon();					/*!< Access if the game has been won*/
	void setGameWon(bool won);			/*!< Set if game has been won*/

private:
	static Score *m_inst;

	// Disallow Copying
	Score(const Score&);
	Score& operator=(const Score&);

	int m_score;					/*!< Player's score in current game*/
	int m_numOfAliveAstros;			/*!< Number of astronauts alive*/
	bool m_displayAstroText;		/*!< Set to true when you can display the number of astronauts alive*/
	int m_killSreak;				/*!< Current killstreak*/
	float m_playTime;				/*!< How long game has been played for*/
	bool m_gameWon;					/*!< If game has been won*/

	Score();
	~Score();
};

