#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class TextureHandler {
public:
    // Load a texture from a file
    void loadTexture(const std::string& filename) {
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            throw std::runtime_error("Error loading texture: " + filename);
        }
        textures[filename] = texture;
    }

    // Get a texture by its filename
    sf::Texture& getTexture(const std::string& filename) {
        if (textures.find(filename) == textures.end()) {
            throw std::runtime_error("Error: texture not found: " + filename);
        }
        return textures[filename];
    }

private:
    std::unordered_map<std::string, sf::Texture> textures;
};