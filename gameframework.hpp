#ifndef GAMEFRAMEWORK_H
#define GAMEFRAMEWORK_H
#include <list>

class Level
{
};

class GameFramework
{
	private:
		std::list<Level> m_levels;
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
};

#endif
