#include "game.h"



Game::Game()
	: mWindow(sf::VideoMode(wWidth, wHeight), "Pong Game")
{
	defaultWall();
	leftPaddle.defaultPaddle(); rightPaddle.defaultPaddle();
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
		if (ev.type == sf::Event::Closed) {
			mWindow.close();
		}
		/*if (isPlaying && ev.type == sf::Event::KeyPressed)
		{
			if (ev.key.code == sf::Keyboard::W)
			{
				leftPaddle.setDirection(sf::Vector2f(0.f, -1.f));
			}
			if (ev.key.code == sf::Keyboard::S)
			{
				leftPaddle.setDirection(sf::Vector2f(0.f, 1.f));
			}
		}
		if (isPlaying && ev.type == sf::Event::KeyReleased)
		{
			if (ev.key.code == sf::Keyboard::W || ev.key.code == sf::Keyboard::S)
			{
				leftPaddle.setDirection(sf::Vector2f(0.f, 0.f));
			}
		}*/
	}
}

void Game::update(sf::Time TimePerFrame)
{
	if (isPlaying)
	{
		
		leftPaddle.setPosition(sf::Vector2f(0, wHeight / 2.f)); rightPaddle.setPosition(sf::Vector2f(wWidth - rightPaddle.getSize().x, wHeight / 2.f));
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			leftPaddle.setDirection(sf::Vector2f(0.f, -1.f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			leftPaddle.setDirection(sf::Vector2f(0.f, 1.f));
		}
		
		
		
		
		checkWallCollision();
		sf::Vector2f movement;
		movement = NewBall.getDirection() * NewBall.getSpeed();
		NewBall.move(movement);
		sf::Vector2f paddleMove;
		paddleMove = sf::Vector2f(0,0);
		paddleMove = leftPaddle.getDirection() * leftPaddle.getSpeed();
		leftPaddle.move(paddleMove);
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
