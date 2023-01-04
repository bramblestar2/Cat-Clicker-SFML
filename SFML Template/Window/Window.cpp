#include "Window.h"
#include <iostream>

Window::Window() : button(sf::Vector2f(0, 0), sf::Vector2f(200, 100), "Hello Button!", 15, sf::Color::Blue, sf::Color::Green)
{
	font.loadFromFile("Fonts/font.ttf");

	button.setFont(font);
	
	button.setOnClick([]() { 
		std::cout << "Clicked!" << std::endl; 
	});

	initWindow();

	unsigned int x = 1;
	unsigned int b = 2;

}

Window::~Window()
{
	delete window;
}

void Window::run()
{
	while (window->isOpen())
	{
		update();
		updateDt();
		updateSFMLEvents();
		render();
	}
}

void Window::render()
{
	window->clear();

	button.draw(*window);

	window->display();
}

void Window::update()
{
}

void Window::updateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Window::updateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		button.handleEvent(event);

		switch (event.type)
		{
		case sf::Event::Closed:
				window->close();
				break;
		case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
						window->close();
						break;
				}
				break;
		}
	}
}

void Window::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(600, 400), "TITLE", sf::Style::Default);
}
