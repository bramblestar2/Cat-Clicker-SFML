#include "Window.h"
#include <iostream>

Window::Window()
{
	font.loadFromFile("Fonts/font.ttf");

	handler.addInteractable(&check, "check");
	handler.addInteractable(&field, "textfield");

	int clicks = 0;

	auto add = [](int a, int b) -> int { return a + b; };

	//std::cout << add(1, 6) << std::endl;


	field.setSize({ 200, 50 });
	field.setTextFont(font);
	field.setTextColor(sf::Color::White);
	field.setCursorColor(sf::Color::White);
	field.setTextSize(20);
	field.setText("Hi");
	field.setBackgroundColor(sf::Color::Transparent);

	check.setPosition({ 100,100 });
	check.setOnClick(sf::Mouse::Left, [&]()
		{
			check.setChecked(check.isChecked() ? false : true);
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

	handler.draw(*window);

	window->display();
}

void Window::update()
{
	if (((Checkbox*)handler.getInteractable(0).second)->isChecked())
	{
		TextField* field = ((TextField*)handler.getInteractable(1).second);
		if (field->isFocused())
		{
			field->setFocused(false);
		}
	}
}

void Window::updateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Window::updateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		handler.handleEvent(event);

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
