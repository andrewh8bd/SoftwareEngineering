#ifndef GAMEFRAMEWORK_H
#define GAMEFRAMEWORK_H
#include <list>

class Level
{
};

class Gateway
{
};

class GameFramework
{
	private:
		std::list<Level> m_levels;
		std::list<Gateway> m_gateways;
	public:
		//Game Framework related
		GameFramework();
		GameFramework(const GameFramework&);
		~GameFramework();
		const GameFramework& operator=(const GameFramework&);
		
		//Level Related
		void addLevel(const Level&);
		void removeLevel(const int);
		std::list<Level> getLevels() const;
		const Level getLevel(const int) const;
		const int getNumberOfLevels() const;
		
		//Gateway Related
		void addGateway(const Gateway&);
		void removeGateway(const int);
		std::list<Gateway> getGateways() const;
		std::list<Gateway> getGateways(const Level&);
		std::list<Gateway> getGateways(const Level&, const Level&);
		const Level getGateway(const int) const;
		const int getNumberOfGateways() const;
		
};

#endif
