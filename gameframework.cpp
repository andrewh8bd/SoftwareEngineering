#include "gameframework.hpp"

GameFramework::GameFramework()
{
}

GameFramework::GameFramework(const GameFramework& _gf) : m_levels(_gf.m_levels)
{
}

GameFramework::~GameFramework()
{
	m_levels.clear();
}

const GameFramework& GameFramework::operator=(const GameFramework& _gf)
{
	m_levels.clear();
	m_levels = _gf.m_levels;
	return *this;
}

void GameFramework::addLevel(const Level& _l)
{
	m_levels.push_back(_l);
}

void GameFramework::removeLevel(const int _id)
{
	///TODO
}

std::list<Level> GameFramework::getLevels() const
{
	return m_levels;
}

const Level GameFramework::getLevel(const int _id) const
{
	///TODO
}

const int GameFramework::getNumberOfLevels() const 
{
	return m_levels.size();
}

void GameFramework::addGateway(const Gateway& _g)
{
	m_gateways.push_back(_g);
}

void GameFramework::removeGateway(const int _id)
{
	///TODO
}

std::list<Gateway> GameFramework::getGateways() const
{
	return m_gateways;
}

std::list<Gateway> GameFramework::getGateways(const Level& _l)
{
	///TODO
}

std::list<Gateway> GameFramework::getGateways(const Level& _l1, const Level& _l2)
{
	///TODO
}

const Level GameFramework::getGateway(const int) const
{
	///TODO
}

const int GameFramework::getNumberOfGateways() const
{
	return m_gateways.size();
}
