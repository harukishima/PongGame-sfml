#ifndef __GAME_H__
#define __GAME_H__

#include<SFML/Graphics.hpp>
#include"ball.h"



class Game
{
public:
	Game();
	void run();
	
private:
	void processEvents();
	void update(sf::Time);
	void render();
	void defaultWall();
	void checkWallCollision();

	sf::RenderWindow mWindow;
	Ball NewBall;
	sf::RectangleShape upperWall;
	sf::RectangleShape lowerWall;
};


#endif // !__GAME_H__