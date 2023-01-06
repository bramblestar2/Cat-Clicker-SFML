#pragma once
#include "Interactable.h"

class Checkbox : public Interactable
{
public:
    Checkbox(const sf::Vector2f& position = sf::Vector2f(0, 0), bool checked = false);

    void setChecked(bool checked);
    bool isChecked() const;

    void setBoxColor(const sf::Color& color);
    void setCheckmarkColor(const sf::Color& color);
    void setBoxSize(const sf::Vector2f& size);
    void setCheckmarkSize(float radius);
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

    virtual void draw(sf::RenderTarget& target) override;

private:
    sf::RectangleShape m_box;
    sf::CircleShape m_checkmark;
    bool m_checked;
};

