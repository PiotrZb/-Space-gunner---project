#ifndef SCENE1_H
#define SCENE1_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "airlock.h"
#include "movingplatform.h"
#include "hero.h"
#include "turret.h"
#include "sounds.h"
#include "soldier.h"
#include "asteroid.h"

class Scene1 : public sf::Sprite
{
private:

    //stationary elements
    std::vector<sf::FloatRect> objects_bounds_;
    sf::Texture scene1_texture_;

    //animated elements
    AirLock air_lock1_;
    AirLock air_lock2_;
    AirLock air_lock3_;
    MovingPlatform platform1_;
    MovingPlatform platform2_;
    MovingPlatform platform3_;
    std::vector<std::unique_ptr<Asteroid>> asteroids_;

    //enemies
    Turret turret1_;
    Soldier soldier1_ = Soldier(1150,331,sf::FloatRect(1150,193,400,140));
    Soldier soldier2_ = Soldier(3430,711,sf::FloatRect(3430,571,400,140));


    //enemy bullets
    std::vector<std::unique_ptr<Bullet>> enemy_bullets_;

    Sounds sounds_;

public:

    Scene1();

    std::vector<sf::FloatRect> objects_bounds();

    void draw_animated_elements(sf::RenderWindow &window);
    void animate_elements(sf::FloatRect hero_bounds, sf::Time &elapsed);
    void update(Hero &hero, sf::Time &elapsed, std::vector<std::unique_ptr<Bullet>> &hero_bullets);
};

#endif // SCENE1_H
