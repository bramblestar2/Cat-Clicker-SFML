#include "Checkbox.h"


Checkbox::Checkbox(const sf::Vector2f& position, bool checked) :
    Interactable(position, sf::Vector2f(20, 20)), // set the size of the checkbox to 20x20 pixels
    m_checked(checked)
{
    // initialize the checkbox rectangle
    m_box.setPosition(position);
    m_box.setSize(sf::Vector2f(20, 20));
    m_box.setOutlineThickness(1);
    m_box.setOutlineColor(sf::Color::Black);
    m_box.setFillColor(sf::Color::White);

    // initialize the checkmark circle
    m_checkmark.setPosition(position + sf::Vector2f(3, 3)); // offset the position slightly to center the checkmark within the box
    m_checkmark.setRadius(7);
    m_checkmark.setOutlineThickness(1);
    m_checkmark.setOutlineColor(sf::Color::Black);
    m_checkmark.setFillColor(sf::Color::Black);
}

void Checkbox::setChecked(bool checked)
{
    m_checked = checked;
}

bool Checkbox::isChecked() const
{
    return m_checked;
}

void Checkbox::setBoxColor(const sf::Color& color)
{
    m_box.setFillColor(color);
}

void Checkbox::setCheckmarkColor(const sf::Color& color)
{
    m_checkmark.setFillColor(color);
}

void Checkbox::setBoxSize(const sf::Vector2f& size)
{
    m_box.setSize(size);
    m_bounds.width = size.x;
    m_bounds.height = size.y;
}

void Checkbox::setCheckmarkSize(float radius)
{
    m_checkmark.setRadius(radius);
}

void Checkbox::setPosition(const sf::Vector2f& position)
{
    m_box.setPosition(position);
    m_checkmark.setPosition(position + sf::Vector2f(3, 3)); // offset the position slightly to center the checkmark within the box
    m_bounds.left = position.x;
    m_bounds.top = position.y;
}

sf::Vector2f Checkbox::getPosition() const
{
    return m_box.getPosition();
}

void Checkbox::draw(sf::RenderTarget& target)
{
    // draw the checkbox rectangle
    target.draw(m_box);

    // draw the checkmark if the checkbox is checked
    if (m_checked)
        target.draw(m_checkmark);
}