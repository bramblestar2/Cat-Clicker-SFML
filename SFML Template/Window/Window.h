#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Button.h"
#include "../InteractableHandler.h"
#include "../Checkbox.h"
#include "../TextField.h"

class Window
{
public:
	Window();
	//Free memory
	virtual ~Window();

	void run();
	void render();
	void update();
	void updateDt();
	void updateSFMLEvents();
private:
	void initWindow();
	
	sf::Clock dtClock;
	double dt;

	sf::RenderWindow* window;
	sf::Event event;

	InteractableHandler handler;

	TextField field;
	Checkbox check;
	sf::Font font;

	std::vector<int> something;
};

