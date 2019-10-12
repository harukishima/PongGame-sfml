#ifndef __GAME_H__
#define __GAME_H__

#include<SFML/Graphics.hpp>
#include"ball.h"
#include"Paddle.h"


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
	Paddle leftPaddle;
	Paddle rightPaddle;

	bool isPlaying = false;
	bool isSingle = false;
	bool isMulti = false;
};


#endif // !__GAME_H__