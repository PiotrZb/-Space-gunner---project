#ifndef SCENE1_H
#define SCENE1_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "airlock.h"

class Scene1 : public sf::Sprite
{
private:

    //stationary elements
    std::vector<sf::FloatRect> objects_bounds_;
    sf::Texture scene1_texture_;

    //animated elements
    AirLock air_lock1_;
    AirLock air_lock2_;

public:

    Scene1();

    std::vector<sf::FloatRect> objects_bounds();

    void draw_animated_elements(sf::RenderWindow &window);
    void animate_elements(sf::FloatRect hero_bounds);
    void update_bounds();
};

#endif // SCENE1_H
