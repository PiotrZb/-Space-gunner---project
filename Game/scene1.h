#ifndef SCENE1_H
#define SCENE1_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "airlock.h"
#include "movingplatform.h"
#include "hero.h"
#include "turret.h"
#include "sounds.h"

class Scene1 : public sf::Sprite
{
private:

    //stationary elements
    std::vector<sf::FloatRect> objects_bounds_;
    sf::Texture scene1_texture_;

    //animated elements
    AirLock air_lock1_;
    AirLock air_lock2_;
    MovingPlatform platform1_;
    Turret turret1_;

    //enemy bullets
    std::list<Bullet> enemy_bullets_;

    Sounds sounds_;

public:

    Scene1();

    std::vector<sf::FloatRect> objects_bounds();

    void draw_animated_elements(sf::RenderWindow &window);
    void animate_elements(sf::FloatRect hero_bounds, sf::Time &elapsed);
    void update_bounds(Hero &hero, sf::Time &elapsed, std::list<Bullet> &hero_bullets);
};

#endif // SCENE1_H
