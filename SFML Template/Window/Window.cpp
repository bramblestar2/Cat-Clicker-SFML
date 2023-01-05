#include "Window.h"
#include <iostream>

Window::Window() : 
	button(sf::Vector2f(100, 100), sf::Vector2f(200, 100), 
		   "Hello Button! (3)", 20, sf::Color::Blue, sf::Color::Green)
{
	something.push_back(5);
	something.push_back(53);
	something.push_back(2);

	font.loadFromFile("Fonts/font.ttf");
	button.setFont(font);

	int clicks = 0;

	//Set click event
	button.setOnClick(sf::Mouse::Left, [&clicks, this]()
		{
			clicks++;
			button.setText("Hello Button! (" + std::to_string(clicks) + ")");
		});

	button.setOnClick(sf::Mouse::Right, [&clicks, this]()
		{
			clicks--;
			button.setText("Hello Button! (" + std::to_string(clicks) + ")");
		});

	button.setOnClick(sf::Mouse::Middle, [&clicks, this]()
		{
			clicks *= clicks;
			button.setText("Hello Button! (" + std::to_string(clicks) + ")");
		});

	//Set hover event
	button.setOnEnter([&clicks, this]()
		{
			std::cout << "Mouse hovering over Button!" << std::endl;
			/*
			something.push_back(rand() % 100);

			std::cout << "[";
			for (int i = 0; i < something.size(); i++)
				std::cout << something.at(i) << (i == something.size() - 1 ? "]" : ", ");
			std::cout << std::endl;

			button.setText("Hello Button! (" + std::to_string(something.size()) + ")");
			*/
		});

	initWindow();
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
