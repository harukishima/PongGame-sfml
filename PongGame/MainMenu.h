#ifndef __MAINMENU_H__
#define __MAINMENU_H__
#include"Menu.h"

class MainMenu : public Menu
{
private:
	bool isLeft = false;
	bool isRight = false;
public:
	sf::Font titleFont;
	sf::Text title;
	sf::Text leftText, rightText;
	sf::RectangleShape leftBox, rightBox;
	
	MainMenu();
	virtual ~MainMenu() = default;

	void setLeftState(bool);
	void setRightState(bool);
	bool getLeftState();
	bool getRightState();

	virtual void updateMenu();
	virtual void navigate(sf::Keyboard::Key key);
};





#endif // !__MAINMENU_H__