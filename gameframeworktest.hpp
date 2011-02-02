#ifndef GAMEFRAMEWORKTEST_H
#define GAMEFRAMEWORKTEST_H
#include <cxxtest/TestSuite.h>
#include <iostream>
#include "gameframework.hpp"

class GameFrameworkTest : public CxxTest::TestSuite
{
	public:
		void testCreate()
		{
			GameFramework* g;
			g = new GameFramework;
			TS_ASSERT(g != NULL);
			TS_ASSERT_EQUALS(g->getNumberOfLevels(), 0);
			
			delete g;
		}
		
		void testCopy()
		{
			GameFramework* g1;
			GameFramework* g2;
			g1 = new GameFramework;
			
			g1->addLevel(*(new Level));
			g2 = new GameFramework(*g1);
			
			TS_ASSERT_EQUALS(g1->getNumberOfLevels(), g2->getNumberOfLevels());
			
						
			TS_ASSERT(g2 != NULL);
			TS_ASSERT_EQUALS(g1->getNumberOfLevels(), g2->getNumberOfLevels());
			TS_ASSERT_EQUALS(g2->getNumberOfLevels(), 1);
			
			delete g1;
			delete g2;
			g1 = new GameFramework;
			for(int i=0; i < 100; i++)
			{
				g1->addLevel(*(new Level));
			}
			
			g2 = new GameFramework(*g1);
			TS_ASSERT_EQUALS(g2->getNumberOfLevels(), g1->getNumberOfLevels())
		//	for(std::list<Level>::iterator at = g1->getLevels().begin(),
		//	    std::list<Level>::iterator bt = g2->getLevels().begin();
		//		at != g1->getLevels().end(), bt != g2->getLevels();
		//		at++, bt++)
		//	{
		//		TS_ASSERT_EQUALS(*at, *bt);
		//	}
			delete g1;
			delete g2;
		}
		
		void testAssignment()
		{
			GameFramework* g1;
			GameFramework* g2;
			g1 = new GameFramework;
			g2 = new GameFramework;
			
			*g2 = *g1;
			
			TS_ASSERT_EQUALS(g1->getNumberOfLevels(), g2->getNumberOfLevels());
			g1->addLevel(*(new Level));
			
			*g2 = *g1;
			TS_ASSERT_EQUALS(g1->getNumberOfLevels(), g2->getNumberOfLevels());
			//TS_ASSERT_EQUALS(g1->getLevel(0), g2->getLevel(0));
						
			
			delete g1;
			delete g2;
			g1 = new GameFramework;
			g2 = new GameFramework;
			for(int i=0; i < 100; i++)
			{
				g1->addLevel(*(new Level));
			}
			
			*g2 = *g1;
			
			TS_ASSERT_EQUALS(g2->getNumberOfLevels(), g1->getNumberOfLevels())
		//	for(std::list<Level>::iterator at = g1->getLevels().begin(),
		//	    std::list<Level>::iterator bt = g2->getLevels().begin();
		//		at != g1->getLevels().end(), bt != g2->getLevels();
		//		at++, bt++)
		//	{
		//		TS_ASSERT_EQUALS(*at, *bt);
		//	}
			delete g1;
			delete g2;
		}
		
		void testDestroy()
		{
			GameFramework* a = new GameFramework;
			
			delete a;
			a = NULL;
			TS_ASSERT(a == NULL);
		}
		
		void testAddLevel()
		{
			GameFramework* a = new GameFramework;
			Level* l = new Level;
			TS_ASSERT_EQUALS(a->getNumberOfLevels(), 0);
			a->addLevel(*l);
			
			TS_ASSERT_EQUALS(a->getNumberOfLevels(), 1);
			//TS_ASSERT_EQUALS(a->getLevel(0), *l);
			
			delete a;
			delete l;
			
			a = new GameFramework;
			
			for(int i=0; i<100; i++)
			{
				l = new Level;
				TS_ASSERT_EQUALS(a->getNumberOfLevels(), i);
				a->addLevel(*l);
				TS_ASSERT_EQUALS(a->getNumberOfLevels(), i+1);
				l = NULL;
			}
			TS_ASSERT_EQUALS(a->getNumberOfLevels(), 100);
			
		}
		
		void testRemoveLevel()
		{
			///TODO
		}
		
		void testGetLevels()
		{
			GameFramework* a = new GameFramework;
			TS_ASSERT_EQUALS(a->getNumberOfLevels(), 0);
			
			Level* l = new Level;
			std::list<Level> ls;
			a->addLevel(*l);
			ls.push_back(*l);
			
			TS_ASSERT_EQUALS(a->getLevels().size(), ls.size());
			TS_ASSERT_EQUALS(a->getLevels().size(), 1);
			
			delete a;
			ls.clear();
			delete l;
			
			a = new GameFramework;
			for(int i=0; i<100; i++)
			{
				l = new Level;
				a->addLevel(*l);
				ls.push_back(*l);
				l = NULL;
				
				TS_ASSERT_EQUALS(a->getLevels().size(), ls.size());
				TS_ASSERT_EQUALS(a->getLevels().size() - 1, i);
			}
			delete a;
			ls.clear();
			delete l;
		}
		
		void testGetLevel()
		{
			///TODO
		}
		
		void testGetNumberOfLevels()
		{
			GameFramework* a = new GameFramework;
			
			TS_ASSERT_EQUALS(a->getNumberOfLevels(), 0);
			
			a->addLevel(*(new Level));
			TS_ASSERT_EQUALS(a->getNumberOfLevels(), 1);
			
			delete a;
			a = new GameFramework;
			for(int i = 0; i < 1000; i++)
			{
				a->addLevel(*(new Level));
				TS_ASSERT_EQUALS(a->getNumberOfLevels() - 1, i);
			}
			
			delete a;
		}
		
};

#endif
