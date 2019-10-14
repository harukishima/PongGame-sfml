#ifndef __GAME_H__
#define __GAME_H__

#include<SFML/Graphics.hpp>
#include<ctime>
#include"ball.h"
#include"Paddle.h"


class Game
{
public:
	Game();
	void run();
	
private:
	void processEvents();
	void handleInput(sf::Keyboard::Key key, bool isPressed);
	void update(sf::Time);
	void render();
	void defaultWall();
	void defaultPaddleState();
	void defaultBallState();

	void checkWallCollision();
	void checkPaddleCollision();
	void updateBall();
	void updatePaddle();

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