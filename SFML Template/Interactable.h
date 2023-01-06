#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include <iostream>

class Interactable
{
public:
    virtual ~Interactable() = default;

    virtual void setOnClick(sf::Mouse::Button button, std::function<void()> onClick)
    {
        m_onClick[button] = onClick;
    }

    virtual void setOnEnter(std::function<void()> onEnter)
    {
        m_onEnter = onEnter;
    }

    virtual void setOnLeave(std::function<void()> onLeave)
    {
        m_onLeave = onLeave;
    }

    virtual void handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            auto it = m_onClick.find(event.mouseButton.button);
            if (it != m_onClick.end() && m_bounds.contains(event.mouseButton.x, event.mouseButton.y))
                it->second();
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            if (m_bounds.contains(event.mouseMove.x, event.mouseMove.y))
            {
                if (!m_isHovered && m_onEnter)
                    m_onEnter();

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
    Interactable(const sf::Vector2f& position, const sf::Vector2f& size) :
        m_bounds(position, size)
    { }

    sf::FloatRect m_bounds;
    std::map< sf::Mouse::Button, std::function<void()> > m_onClick;
    std::function<void()> m_onEnter;
    std::function<void()> m_onLeave;
    bool m_isHovered = false;
};