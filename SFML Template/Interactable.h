#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Interactable
{
public:
    Interactable(const sf::Vector2f& position, const sf::Vector2f& size) :
        m_bounds(position, size)
    {}

    virtual ~Interactable() = default;

    virtual void setOnClick(std::function<void()> onClick)
    {
        m_onClick = onClick;
    }

    virtual void setOnHover(std::function<void()> onHover)
    {
        m_onHover = onHover;
    }

    virtual void setOnLeave(std::function<void()> onLeave)
    {
        m_onLeave = onLeave;
    }

    virtual void handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            if (m_bounds.contains(event.mouseButton.x, event.mouseButton.y) && m_onClick)
                m_onClick();
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            if (m_bounds.contains(event.mouseMove.x, event.mouseMove.y))
            {
                if (!m_isHovered && m_onHover)
                    m_onHover();

                m_isHovered = true;
            }
            else
            {
                if (m_isHovered && m_onLeave)
                    m_onLeave();

                m_isHovered = false;
            }
        }
    }

    virtual void draw(sf::RenderTarget& target) = 0;
    
protected:
    sf::FloatRect m_bounds;
    std::function<void()> m_onClick;
    std::function<void()> m_onHover;
    std::function<void()> m_onLeave;
    bool m_isHovered = false;
};


class RectangleInteractable : public Interactable
{
public:
    RectangleInteractable(const sf::Vector2f& position, const sf::Vector2f& size)
        : Interactable(position, size)
    {
    }

    void draw(sf::RenderTarget& target) override
    {
        sf::RectangleShape shape(sf::Vector2f(Interactable::m_bounds.width,
                                 Interactable::m_bounds.height));
        shape.setPosition(m_bounds.left, m_bounds.top);
        shape.setFillColor(m_isHovered ? sf::Color::Yellow : sf::Color::Red);
        target.draw(shape);
    }
};