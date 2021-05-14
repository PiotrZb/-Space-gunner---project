#ifndef SCENE1_H
#define SCENE1_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Scene1 : public sf::Sprite
{
private:

    std::vector<sf::FloatRect> objects_bounds_;
    sf::Texture scene1_texture_;

public:

    Scene1();

    std::vector<sf::FloatRect> objects_bounds();
};

#endif // SCENE1_H
