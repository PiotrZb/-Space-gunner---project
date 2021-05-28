#ifndef TURRET_H
#define TURRET_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "bullet.h"

class Turret : public sf::Sprite
{
private:

    sf::Texture texture_;
    std::vector<sf::Texture> bullet_textures_;

    sf::Clock clock_;

    int hp_;


public:

    Turret();

    void set_hp(int hp);
    int get_hp();
    bool shot(std::list<Bullet> &bullets, sf::FloatRect hero_rec);
};

#endif // TURRET_H
