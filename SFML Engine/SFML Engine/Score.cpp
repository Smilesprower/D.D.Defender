#include "stdafx.h"
#include "Score.h"

Score * Score::m_inst = nullptr;
Score::Score()
	: m_score(0)
	, m_numOfAliveAstros(20)
{
}
Score::~Score()
{
}

Score * Score::Instance()
{
	if (!m_inst)
	{
		m_inst = new Score();
	}
	return m_inst;
}

void Score::increaseScore(int score)
{
	m_score += score;
}

int Score::getScore()
{
	return m_score;
}

int Score::getAliveAstros()
{
	return m_numOfAliveAstros;
}

void Score::removeAstro()
{
	m_numOfAliveAstros--;
	m_displayAstroText = true;
}

bool Score::canDisplayAstroText()
{
	return m_displayAstroText;
}

void Score::setDisplayAstroText(int can)
{
	m_displayAstroText = can;
}