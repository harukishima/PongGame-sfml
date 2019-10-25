#include "game.h"



Game::Game()
	: mWindow(sf::VideoMode(wWidth, wHeight), "Pong Game")
{
	defaultWall();
	leftPaddle.defaultPaddle(); rightPaddle.defaultPaddle();
	defaultPaddleState();
	isPlaying = true;
	isSingle = true;
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
		/*processEvents();
		update(clock.restart());
		render();*/
	}
}



void Game::processEvents()
{
	sf::Event ev;
	while (mWindow.pollEvent(ev))
	{
		switch (ev.type) {
		case sf::Event::Closed:
			mWindow.close();
			break;
		case sf::Event::KeyPressed:
			handleInput(ev.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handleInput(ev.key.code, false);
			break;
		}
	}
}

void Game::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (isPlaying && key == sf::Keyboard::W)
	{
		leftPaddle.setUpState(isPressed);
	}
	if (isPlaying && key == sf::Keyboard::S)
	{
		leftPaddle.setDownState(isPressed);
	}
	if (isPlaying && key == sf::Keyboard::Up)
	{
		rightPaddle.setUpState(isPressed);
	}
	if (isPlaying && key == sf::Keyboard::Down)
	{
		rightPaddle.setDownState(isPressed);
	}
}

void Game::update(sf::Time TimePerFrame)
{
	if (isPlaying)
	{
		updateBall();
		updatePaddle();
		
		/*
		movement = sf::Vector2f(0, 0);
		movement = rightPaddle.getDirection() * rightPaddle.getSpeed();
		rightPaddle.move(movement);*/
	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(leftPaddle);
	mWindow.draw(rightPaddle);
	mWindow.draw(NewBall);
	mWindow.draw(upperWall);
	mWindow.draw(lowerWall);
	mWindow.display();
}

void Game::defaultWall()
{
	float wallWidth = 20.f;
	upperWall.setSize(sf::Vector2f(wWidth, wallWidth));
	lowerWall.setSize(sf::Vector2f(wWidth, wallWidth));
	upperWall.setFillColor(sf::Color::White); 
	lowerWall.setFillColor(sf::Color::White);
	upperWall.setPosition(sf::Vector2f(0.f, 0.f));
	lowerWall.setPosition(sf::Vector2f(0.f, wHeight - wallWidth));
}

void Game::defaultPaddleState()
{
	leftPaddle.setPosition(sf::Vector2f(0.f,wHeight/2.f));
	
	rightPaddle.setPosition(sf::Vector2f(wWidth-rightPaddle.getSize().x,wHeight/2.f));
}

void Game::defaultBallState()
{
	NewBall.setSpeed(2);
	NewBall.setPosition(sf::Vector2f(wWidth/2.f, wHeight/2.f));
	srand((int)time(0));
	float angle;
	do {
		angle = rand() % 360 + 1;
	} while ((angle > 45 && angle < 135) || (angle > 225 && angle < 315));
	float x = cos(angle*(3.1415 / 180)) * NewBall.getPosition().x - sin(angle * (3.1415 / 180)) * NewBall.getPosition().y;
	float y = sin(angle*(3.1415 / 180)) * NewBall.getPosition().x + cos(angle * (3.1415 / 180)) * NewBall.getPosition().y;
	sf::Vector2f direction(x, y);
	direction = MoveableObject::normalizeVector(direction);
	NewBall.setDirection(direction);
}

void Game::checkWallCollision()
{
	if ((NewBall.getPosition().y - NewBall.getRadius()) <= upperWall.getSize().y)
	{
		NewBall.setDirection(NewBall.getDirection().x, -NewBall.getDirection().y);
	}
	if ((NewBall.getPosition().y + NewBall.getRadius()) >= (wHeight - lowerWall.getSize().y))
	{
		NewBall.setDirection(NewBall.getDirection().x, -NewBall.getDirection().y);
	}
}

void Game::checkPaddleCollision()
{
	if ((NewBall.getPosition().x - NewBall.getRadius()) <= (leftPaddle.getPosition().x + leftPaddle.getSize().x) && NewBall.getPosition().y >= (leftPaddle.getPosition().y - leftPaddle.getSize().y/2.f) && NewBall.getPosition().y <= (leftPaddle.getPosition().y + leftPaddle.getSize().y/2.f))
	{
		NewBall.setDirection(-NewBall.getDirection().x, NewBall.getDirection().y);
		NewBall.setSpeed(NewBall.getSpeed() + NewBall.getSpeed() * 0.1);
	}
	if ((NewBall.getPosition().x + NewBall.getRadius()) >= rightPaddle.getPosition().x && NewBall.getPosition().y >= (rightPaddle.getPosition().y - rightPaddle.getSize().y / 2.f) && NewBall.getPosition().y <= (rightPaddle.getPosition().y + rightPaddle.getSize().y / 2.f))
	{
		NewBall.setDirection(-NewBall.getDirection().x, NewBall.getDirection().y);
		NewBall.setSpeed(NewBall.getSpeed() + NewBall.getSpeed() * 0.1);
	}
}

void Game::updateBall()
{
	checkWallCollision();
	if ((NewBall.getPosition().x + NewBall.getRadius()) <= 0)
	{
		//P2 scored
		defaultBallState();
	}
	if ((NewBall.getPosition().x - NewBall.getRadius()) >= wWidth)
	{
		//P1 scored
		defaultBallState();
	}
	sf::Vector2f movement;
	movement = NewBall.getDirection() * NewBall.getSpeed();
	NewBall.move(movement);
}

void Game::updatePaddle()
{
	checkPaddleCollision();
	sf::Vector2f leftMove(0, 0);
	sf::Vector2f rightMove(0, 0);
	if (isPlaying && leftPaddle.getUpState() && (leftPaddle.getPosition().y - leftPaddle.getSize().y / 2.f) >= upperWall.getSize().y)
	{
		leftPaddle.setDirection(0.f,-1.f);
	}
	if (isPlaying && leftPaddle.getDownState() && (leftPaddle.getPosition().y + leftPaddle.getSize().y / 2.f) <= (wHeight - lowerWall.getSize().y))
	{
		leftPaddle.setDirection(0.f, 1.f);
	}
	leftMove = leftPaddle.getSpeed() * leftPaddle.getDirection();
	if (isPlaying && rightPaddle.getUpState() && (rightPaddle.getPosition().y - rightPaddle.getSize().y / 2.f) >= upperWall.getSize().y)
	{
		rightPaddle.setDirection(0.f, -1.f);
	}
	if (isPlaying && rightPaddle.getDownState() && (rightPaddle.getPosition().y + rightPaddle.getSize().y / 2.f) <= (wHeight - lowerWall.getSize().y))
	{
		rightPaddle.setDirection(0.f, 1.f);
	}
	rightMove = rightPaddle.getSpeed() * rightPaddle.getDirection();
	leftMove = leftPaddle.getSpeed() * leftPaddle.getDirection();
	
		leftPaddle.move(leftMove);
	
		rightPaddle.move(rightMove);

	rightPaddle.setDirection(0.f, 0.f);
	leftPaddle.setDirection(0.f, 0.f);
}
