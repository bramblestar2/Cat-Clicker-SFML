#pragma once
#include "Interactable.h"

#include <SFML/Graphics.hpp>
#include <functional>

class Button : public Interactable
{
public:
    Button()
        : Button({ 0, 0 }, { 0, 0 }, "", 0, sf::Color::Black, sf::Color::White)
    { }

    Button(const sf::Vector2f& position, const sf::Vector2f& size,
        const std::string& text, unsigned int characterSize,
        const sf::Color& textColor, const sf::Color& hoverColor)
        : Interactable(position, size)
        , m_textColor(textColor)
        , m_hoverColor(hoverColor)
    {
        m_label.setString(text);
        m_label.setCharacterSize(characterSize);

        m_label.setFillColor(textColor);
        m_label.setPosition(position.x + size.x / 2, position.y + size.y / 2);
    }

    void setText(const std::string& text)
    {
        m_label.setString(text);
        sf::FloatRect bounds = m_label.getLocalBounds();
        m_label.setOrigin(bounds.width / 2, bounds.height / 2);
    }

    void setFont(const sf::Font& font)
    {
        m_label.setFont(font);
        sf::FloatRect bounds = m_label.getLocalBounds();
        m_label.setOrigin(bounds.width / 2, bounds.height / 2);
    }

    void setCharacterSize(unsigned int size)
    {
        m_label.setCharacterSize(size);
        sf::FloatRect bounds = m_label.getLocalBounds();
        m_label.setOrigin(bounds.width / 2, bounds.height / 2);
    }

    void setTextColor(const sf::Color& color)
    {
        m_label.setFillColor(color);
    }

    void setHoverColor(const sf::Color& color)
    {
        m_hoverColor = color;
    }

    void setPosition(const sf::Vector2f& position)
    {
        m_bounds.left = position.x;
        m_bounds.top = position.y;
        m_label.setPosition(position.x + m_bounds.width / 2, position.y + m_bounds.height / 2);
    }

    void setSize(const sf::Vector2f& size)
    {
        m_bounds.width = size.x;
        m_bounds.height = size.y;
        m_label.setPosition(m_bounds.left + size.x / 2, m_bounds.top + size.y / 2);
    }

    void draw(sf::RenderTarget& target) override
    {
        sf::RectangleShape shape(sf::Vector2f(Interactable::m_bounds.width,
                                 Interactable::m_bounds.height));
        shape.setPosition(m_bounds.left, m_bounds.top);
        shape.setFillColor(m_isHovered ? m_hoverColor : sf::Color::White);
        target.draw(shape);
        target.draw(m_label);
    }

private:
    sf::Text m_label;
    sf::Color m_textColor;
    sf::Color m_hoverColor;
};