#pragma once
#include "Interactable.h"

class TextField : public Interactable
{
public:
    TextField(const sf::Vector2f& position = sf::Vector2f(), const sf::Vector2f& size = sf::Vector2f(), const std::string& defaultText = "");

    void setFocused(const bool _Is_Focused);
    bool isFocused() const;

    void setText(const std::string& text);
    std::string getText() const;

    void setTextColor(const sf::Color& color);
    void setTextSize(unsigned int size);
    void setTextStyle(sf::Text::Style style);
    void setTextFont(const sf::Font& font);

    void setBackgroundColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);

    void setCursorColor(const sf::Color& color);
    void setCursorSize(unsigned int size);

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const;

    virtual void draw(sf::RenderTarget& target) override;
    virtual void handleEvent(const sf::Event& event) override;

private:
    sf::RectangleShape m_background;
    sf::Text m_text;
    sf::RectangleShape m_cursor;
    bool m_isFocused;
    bool m_cursorVisible;
    sf::Clock m_cursorClock;
};

