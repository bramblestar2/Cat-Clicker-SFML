#include "TextField.h"

TextField::TextField(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& defaultText) :
    Interactable(position, size),
    m_isFocused(false),
    m_cursorVisible(false)
{
    // initialize the background rectangle
    m_background.setPosition(position);
    m_background.setSize(size);
    m_background.setFillColor(sf::Color::White);
    m_background.setOutlineThickness(1);
    m_background.setOutlineColor(sf::Color::Black);

    // initialize the text
    m_text.setPosition(position + sf::Vector2f(2, 2)); // offset the position slightly to give some padding within the text field
    m_text.setString(defaultText);
    m_text.setCharacterSize(12);
    m_text.setFillColor(sf::Color::Black);

    // initialize the cursor rectangle
    m_cursor.setSize(sf::Vector2f(2, m_text.getCharacterSize() + 4)); // set the size of the cursor to 2x(font size + 4) pixels
    m_cursor.setFillColor(sf::Color::Black);
}

void TextField::setFocused(const bool _Is_Focused)
{
    m_isFocused = _Is_Focused;
}

bool TextField::isFocused() const
{
    return m_isFocused;
}

void TextField::setText(const std::string& text)
{
    m_text.setString(text);
}

std::string TextField::getText() const
{
    return m_text.getString();
}

void TextField::setTextColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}

void TextField::setTextSize(unsigned int size)
{
    m_text.setCharacterSize(size);
}

void TextField::setTextStyle(sf::Text::Style style)
{
    m_text.setStyle(style);
}

void TextField::setTextFont(const sf::Font& font)
{
    m_text.setFont(font);
}

void TextField::setBackgroundColor(const sf::Color& color)
{
    m_background.setFillColor(color);
}

void TextField::setOutlineColor(const sf::Color& color)
{
    m_background.setOutlineColor(color);
}

void TextField::setOutlineThickness(float thickness)
{
    m_background.setOutlineThickness(thickness);
}

void TextField::setCursorColor(const sf::Color& color)
{
    m_cursor.setFillColor(color);
}

void TextField::setCursorSize(unsigned int size)
{
    m_cursor.setSize(sf::Vector2f(2, size + 4));
}

void TextField::draw(sf::RenderTarget& target)
{
    // draw the background rectangle
    target.draw(m_background);

    // draw the text
    target.draw(m_text);

    // draw the cursor if the text field is focused and the cursor is visible
    if (m_isFocused && m_cursorVisible)
    {
        // update the cursor rectangle position to be after the last character in the text
        sf::FloatRect textBounds = m_text.getLocalBounds();
        m_cursor.setPosition(m_text.getPosition().x + textBounds.width + 2, m_text.getPosition().y + (textBounds.height/3));
        target.draw(m_cursor);
    }
}

void TextField::handleEvent(const sf::Event& event)
{
    if (m_cursorClock.getElapsedTime().asSeconds() > 0.5)
    {
        m_cursorVisible = m_cursorVisible ? false : true;

        m_cursorClock.restart();
    }

    if (!m_isFocused)
        m_cursorClock.restart();

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left && m_bounds.contains(event.mouseButton.x, event.mouseButton.y))
        {
            m_isFocused = true;
        }
        else
        {
            m_isFocused = false;
        }
    }
    else if (event.type == sf::Event::TextEntered && m_isFocused)
    {
        // handle text input for the text field
        if (event.text.unicode == 8) // backspace
        {
            // remove the last character in the text
            std::string str = m_text.getString();
            if (!str.empty())
            {
                str.erase(str.size() - 1, 1);
                setText(str);
            }
        }
        else if (event.text.unicode == 13) // enter
        {
            // add a newline to the text
            m_text.setString(m_text.getString() + "\n");
        }
        else if (event.text.unicode < 128) // regular ASCII character
        {
            // add the character to the text
            m_text.setString(m_text.getString() + static_cast<char>(event.text.unicode));
        }
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
        {
            m_isFocused = false;
        }
        else if (event.type == sf::Event::MouseMoved && m_isFocused)
        {
            // update the cursor clock and cursor visibility when the mouse is moved while the text field is focused
            m_cursorClock.restart();
        }
        else if (event.type == sf::Event::MouseLeft)
        {
            // clear focus and hide the cursor when the mouse leaves the window
            m_isFocused = false;
        }
        else if (event.type == sf::Event::LostFocus)
        {
            // hide the cursor when the text field loses focus
            m_cursorVisible = false;
        }
    }
}

void TextField::setPosition(const sf::Vector2f& position)
{
    m_background.setPosition(position);
    m_text.setPosition(position + sf::Vector2f(2, 2)); // offset the position slightly to give some padding within the text field
    m_bounds.left = position.x;
    m_bounds.top = position.y;
}

sf::Vector2f TextField::getPosition() const
{
    return m_background.getPosition();
}

void TextField::setSize(const sf::Vector2f& size)
{
    m_background.setSize(size);
    m_bounds.width = size.x;
    m_bounds.height = size.y;
}

sf::Vector2f TextField::getSize() const
{
    return m_background.getSize();
}