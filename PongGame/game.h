#ifndef __GAME_H__
#define __GAME_H__

#include<SFML/Graphics.hpp>
#include<ctime>
#include<random>
#include<cmath>
#include"ball.h"
#include"Paddle.h"
#include"MainMenu.h"
#include"PauseMenu.h"


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
	void updateScore();
	void reset();
	void gamePause();
	void gameResume();

	sf::RenderWindow mWindow;
	Ball NewBall;
	sf::RectangleShape upperWall;
	sf::RectangleShape lowerWall;
	Paddle leftPaddle;
	Paddle rightPaddle;

	bool isPlaying = false;
	bool isSingle = false;
	bool isMainMenu = true;
	//int score1 = 0, score2 = 0;
	sf::Text Score1, Score2;
	sf::Font font;
	MainMenu mainMenu;
	PauseMenu pauseMenu;
};


#endif // !__GAME_H__