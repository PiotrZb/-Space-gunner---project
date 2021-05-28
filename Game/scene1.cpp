#include "scene1.h"

Scene1::Scene1(){

    if(!scene1_texture_.loadFromFile("Textures/Sceneelements/Scene1.png")){
        std::cout<<"ERROR::SCENE1::TEXTURE FAILED TO LOAD -> Textures/Sceneelements/Scene1.png"<<std::endl;
    }

    setTexture(scene1_texture_);

    //enemies
    turret1_.setPosition(1400,200);

    //air locks
    air_lock1_.setPosition(1594,201);
    air_lock2_.setPosition(1594,581);
    objects_bounds_.emplace_back(air_lock1_.getGlobalBounds());
    objects_bounds_.emplace_back(air_lock2_.getGlobalBounds());

    //platforms
    platform1_.setPosition(2370,331);
    platform1_.set_movement_bounds(sf::FloatRect(2370,331,800,26));
    platform1_.set_velocity_x(100);

    //stationary elements
    objects_bounds_.emplace_back(sf::FloatRect(0,0,1,800));
    objects_bounds_.emplace_back(sf::FloatRect(0,700,350,100));
    objects_bounds_.emplace_back(sf::FloatRect(508,573,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(801,447,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(808,711,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(1133,711,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(1100,331,450,26));
    objects_bounds_.emplace_back(sf::FloatRect(1501,711,50,26));    
    objects_bounds_.emplace_back(sf::FloatRect(1551,331,200,100));
    objects_bounds_.emplace_back(sf::FloatRect(1551,0,100,193));
    objects_bounds_.emplace_back(sf::FloatRect(1551,431,100,142));
    objects_bounds_.emplace_back(sf::FloatRect(1551,711,300,90));
    objects_bounds_.emplace_back(sf::FloatRect(1591,573,21,8));
    objects_bounds_.emplace_back(sf::FloatRect(1591,193,21,8));
    objects_bounds_.emplace_back(sf::FloatRect(1981,331,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(2151,711,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(2601,711,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(3023,711,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(3410,711,450,89));
    objects_bounds_.emplace_back(sf::FloatRect(3410,331,450,150));
    objects_bounds_.emplace_back(sf::FloatRect(3660,231,200,100));
    objects_bounds_.emplace_back(sf::FloatRect(3560,171,300,60));
    objects_bounds_.emplace_back(sf::FloatRect(3518,205,42,26));
}

std::vector<sf::FloatRect> Scene1::objects_bounds(){

    return objects_bounds_;
}

void Scene1::animate_elements(sf::FloatRect hero_bounds, sf::Time &elapsed){

    if(hero_bounds.intersects(sf::FloatRect(1452,200,299,131))){

        air_lock1_.animate("open");
    }
    else{

        air_lock1_.animate("close");
    }

    if(hero_bounds.intersects(sf::FloatRect(1452,580,299,131))){

        air_lock2_.animate("open");
    }
    else{

        air_lock2_.animate("close");
    }

    platform1_.move_platform(elapsed);

    if(turret1_.shot(enemy_bullets_, hero_bounds)){

        sounds_.play_shot_sound(10);
    }

    for(auto it = enemy_bullets_.begin(); it != enemy_bullets_.end(); ++it){

        it->move_bullet(elapsed);
    }
}

void Scene1::draw_animated_elements(sf::RenderWindow &window){

    window.draw(air_lock1_);
    window.draw(air_lock2_);
    window.draw(platform1_);
    window.draw(turret1_);

    for(auto it = enemy_bullets_.begin(); it != enemy_bullets_.end(); ++it){

        window.draw(*it);
    }
}

void Scene1::update_bounds(Hero &hero, sf::Time &elapsed){

    objects_bounds_[0] = air_lock1_.getGlobalBounds();
    objects_bounds_[1] = air_lock2_.getGlobalBounds();

    platform1_.collisions(hero, elapsed);

    for(auto it = enemy_bullets_.begin(); it != enemy_bullets_.end(); ++it){

        if(hero.getGlobalBounds().intersects(it->getGlobalBounds())){

            enemy_bullets_.erase(it);
            hero.set_hp(hero.get_hp()-20);
        }
    }
}
