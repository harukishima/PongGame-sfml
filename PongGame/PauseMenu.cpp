#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
	//Set title
	titleFont.loadFromFile("sansation.ttf");
	title.setFont(titleFont);
	title.setCharacterSize(80);
	title.setString("PAUSE");
	title.setPosition(270, 100);

	//Set upper box
	upperBox.setSize(sf::Vector2f(200, 50));
	upperBox.setFillColor(sf::Color::Transparent);
	upperBox.setOutlineThickness(2);
	upperBox.setOutlineColor(sf::Color::White);
	upperBox.setPosition(sf::Vector2f(300, 300));
	//Upper box text
	upperText.setFont(titleFont);
	upperText.setCharacterSize(25);
	upperText.setString("Continue");
	upperText.setFillColor(sf::Color::White);
	upperText.setPosition(sf::Vector2f(upperBox.getPosition().x + 50, upperBox.getPosition().y + 8));

	//Set midle box
	midleBox.setSize(sf::Vector2f(200, 50));
	midleBox.setFillColor(sf::Color::Transparent);
	midleBox.setOutlineThickness(2);
	midleBox.setOutlineColor(sf::Color::White);
	midleBox.setPosition(sf::Vector2f(300, 380));
	//Midle box text
	midleText = upperText;
	midleText.setString("Main menu");
	midleText.setPosition(sf::Vector2f(midleBox.getPosition().x + 35, midleBox.getPosition().y + 8));

	//Set bottom box
	bottomBox.setSize(sf::Vector2f(200, 50));
	bottomBox.setFillColor(sf::Color::Transparent);
	bottomBox.setOutlineThickness(2);
	bottomBox.setOutlineColor(sf::Color::White);
	bottomBox.setPosition(sf::Vector2f(300, 460));
	//Bottom box text
	bottomText = midleText;
	bottomText.setString("Exit game");
	bottomText.setPosition(sf::Vector2f(bottomBox.getPosition().x + 45, bottomBox.getPosition().y + 8));
}

void PauseMenu::setState(int state)
{
	mState = state;
}

int PauseMenu::getState()
{
	return mState;
}

void PauseMenu::updateMenu()
{
	switch (mState)
	{
	case 1:
		upperBox.setFillColor(sf::Color::White);
		upperText.setFillColor(sf::Color::Black);
		midleBox.setFillColor(sf::Color::Transparent);
		midleText.setFillColor(sf::Color::White);
		bottomBox.setFillColor(sf::Color::Transparent);
		bottomText.setFillColor(sf::Color::White);
		break;
	case 2:
		upperBox.setFillColor(sf::Color::Transparent);
		upperText.setFillColor(sf::Color::White);
		midleBox.setFillColor(sf::Color::White);
		midleText.setFillColor(sf::Color::Black);
		bottomBox.setFillColor(sf::Color::Transparent);
		bottomText.setFillColor(sf::Color::White);
		break;
	case 3:
		upperBox.setFillColor(sf::Color::Transparent);
		upperText.setFillColor(sf::Color::White);
		midleBox.setFillColor(sf::Color::Transparent);
		midleText.setFillColor(sf::Color::White);
		bottomBox.setFillColor(sf::Color::White);
		bottomText.setFillColor(sf::Color::Black);
		break;
	default:
		break;
	}
}

void PauseMenu::navigate(sf::Keyboard::Key key)
{
	if (mState != 3)
	{
		if (key == sf::Keyboard::Down)
		{
			mState++;
		}
	}
	if (mState != 1)
	{
		if (key == sf::Keyboard::Up)
		{
			mState--;
		}
	}
}
