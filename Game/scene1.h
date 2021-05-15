#ifndef SCENE1_H
#define SCENE1_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Scene1 : public sf::Sprite
{
private:

    //stationary elements
    std::vector<sf::FloatRect> objects_bounds_;
    sf::Texture scene1_texture_;

    //air lock 1
    sf::Texture air_lock_texture_;
    sf::Sprite air_lock_;
    int air_lock_current_frame_;

    sf::Clock clock_;

public:

    Scene1();

    std::vector<sf::FloatRect> objects_bounds();

    void draw_animated_elements(sf::RenderWindow &window);
    void animate_elements(sf::FloatRect hero_bounds);
    void update_bounds();

    void animate_air_lock(std::string status);
};

#endif // SCENE1_H
