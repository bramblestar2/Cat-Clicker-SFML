#pragma once
#include "Interactable.h"
#include <vector>

class InteractableHandler
{
public:
    //Returns a list that has a position 
    //of each occuring instance of type
    std::vector<int> find(std::string type)
    {
        std::vector<int> instances;

        for (int i = 0; i < m_interactables.size(); i++)
        {
            if (m_interactables.at(i).first == type)
                instances.push_back(i);
        }

        return instances;
    }

    int getSize() const
    {
        return m_interactables.size();
    }

    std::pair<std::string, Interactable*> getInteractable(int index)
    {
        if (index < 0 || index >= m_interactables.size())
            return std::pair<std::string, Interactable*>("NONE", nullptr);

        return m_interactables[index];
    }

    void addInteractable(Interactable* interactable, std::string type)
    {
        m_interactables.push_back(std::pair<std::string, Interactable*>(type, interactable));
    }

    void handleEvent(const sf::Event& event)
    {
        for (auto interactable : m_interactables)
            interactable.second->handleEvent(event);
    }

    void draw(sf::RenderTarget& target)
    {
        for (auto interactable : m_interactables)
            interactable.second->draw(target);
    }

private:
    std::vector<std::pair<std::string, Interactable*>> m_interactables;
};