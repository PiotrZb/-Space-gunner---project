#include "scene1.h"

Scene1::Scene1(){

    if(!scene1_texture_.loadFromFile("Textures/Sceneelements/Scene1.png")){
        std::cout<<"ERROR::SCENE1::TEXTURE FAILED TO LOAD -> Textures/Sceneelements/Scene1.png"<<std::endl;
    }

    setTexture(scene1_texture_);

    //enemies
    turret1_.setPosition(3660,283);

    for(int i = 0; i < 30; i++){

        asteroids_.emplace_back(std::make_unique<Asteroid>());
    }

    //air locks
    air_lock1_.setPosition(1594,201);
    air_lock2_.setPosition(1594,581);
    air_lock3_.setPosition(5673,91);
    objects_bounds_.emplace_back(air_lock1_.getGlobalBounds());
    objects_bounds_.emplace_back(air_lock2_.getGlobalBounds());
    objects_bounds_.emplace_back(air_lock3_.getGlobalBounds());

    //platforms
    platform1_.setPosition(2370,331);
    platform1_.set_movement_bounds(sf::FloatRect(2370,331,800,26));
    platform1_.set_velocity_x(100);
    platform2_.setPosition(3860,171);
    platform2_.set_movement_bounds(sf::FloatRect(4100,171,1140,26));
    platform2_.set_velocity_x(100);
    platform3_.setPosition(5130,711);
    platform3_.set_movement_bounds(sf::FloatRect(4100,441,1140,26));
    platform3_.set_velocity_x(100);

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
    objects_bounds_.emplace_back(sf::FloatRect(5660,0,100,83));
    objects_bounds_.emplace_back(sf::FloatRect(5460,221,450,150));
    objects_bounds_.emplace_back(sf::FloatRect(5460,171,100,50));
    objects_bounds_.emplace_back(sf::FloatRect(5610,371,100,202));
    objects_bounds_.emplace_back(sf::FloatRect(5460,711,450,89));
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

    if(hero_bounds.intersects(sf::FloatRect(5560,91,310,130))){

        air_lock3_.animate("open");
    }
    else{

        air_lock3_.animate("close");
    }

    platform1_.move_platform(elapsed);
    platform2_.move_platform(elapsed);
    platform3_.move_platform(elapsed);

    if(soldier1_.get_hp() > 0){

        soldier1_.move_soldier(elapsed);
        soldier1_.animate();
    }

    if(soldier2_.get_hp() > 0){

        soldier2_.move_soldier(elapsed);
        soldier2_.animate();
    }

    if(turret1_.is_alive_){
        if(turret1_.shot(enemy_bullets_, hero_bounds)){

            sounds_.play_shot_sound(10);
        }
    }

    if(soldier1_.shot(enemy_bullets_, hero_bounds) || soldier2_.shot(enemy_bullets_, hero_bounds)){

        sounds_.play_shot_sound(10);
     }


    if(soldier1_.get_hp() > 0 && abs(hero_bounds.left - soldier1_.getGlobalBounds().left) < 1000){

        sounds_.play_run_sound();
    }
    else{

        if(soldier2_.get_hp() > 0 && abs(hero_bounds.left - soldier2_.getGlobalBounds().left) < 1000){

            sounds_.play_run_sound();
        }
        else{

            sounds_.stop_run_sound();
        }
    }

    for(auto it = enemy_bullets_.begin(); it != enemy_bullets_.end(); ++it){

        it->move_bullet(elapsed);
    }

    for(int i = 0; i < asteroids_.size(); i++){

        asteroids_[i]->move_asteroid(elapsed);
    }
}

void Scene1::draw_animated_elements(sf::RenderWindow &window){

    window.draw(air_lock1_);
    window.draw(air_lock2_);
     window.draw(air_lock3_);

    window.draw(platform1_);
    window.draw(platform2_);
    window.draw(platform3_);

    for(int i = 0; i < asteroids_.size(); i++){

        window.draw(*asteroids_[i]);
    }

    if(soldier1_.get_hp() > 0){

        window.draw(soldier1_);
    }

    if(soldier2_.get_hp() > 0){

        window.draw(soldier2_);
    }

    if(turret1_.is_alive_){

        window.draw(turret1_);
    }

    for(auto it = enemy_bullets_.begin(); it != enemy_bullets_.end(); ++it){

        window.draw(*it);
    }
}

void Scene1::update(Hero &hero, sf::Time &elapsed, std::list<Bullet> &hero_bullets){

    objects_bounds_[0] = air_lock1_.getGlobalBounds();
    objects_bounds_[1] = air_lock2_.getGlobalBounds();
    objects_bounds_[2] = air_lock3_.getGlobalBounds();

    //platforms
    if(hero.getGlobalBounds().left < 3600){
        platform1_.collisions(hero, elapsed);
    }
    if(hero.getGlobalBounds().left > 3600 && hero.getGlobalBounds().left < 5400){

        if(hero.getGlobalBounds().top > 400){

            platform3_.collisions(hero, elapsed);
        }
        else{

            platform2_.collisions(hero, elapsed);
        }
    }

    for(auto it = enemy_bullets_.begin(); it != enemy_bullets_.end(); ++it){

        if(hero.getGlobalBounds().intersects(it->getGlobalBounds())){

            enemy_bullets_.erase(it);
            hero.set_hp(hero.get_hp()-20);
        }
    }

    for(auto it = hero_bullets.begin(); it != hero_bullets.end(); ++it){

        if(it->getGlobalBounds().intersects(turret1_.getGlobalBounds()) && turret1_.is_alive_){

            turret1_.set_hp(turret1_.get_hp()-20);
            hero_bullets.erase(it);
        }

        if(it->getGlobalBounds().intersects(soldier1_.getGlobalBounds()) && soldier1_.get_hp() > 0){

            soldier1_.set_hp(soldier1_.get_hp() - 20);
            hero_bullets.erase(it);
        }

        if(it->getGlobalBounds().intersects(soldier2_.getGlobalBounds()) && soldier2_.get_hp() > 0){

            soldier2_.set_hp(soldier2_.get_hp() - 20);
            hero_bullets.erase(it);
        }
    }

    if(turret1_.get_hp() <= 0){

        turret1_.is_alive_ = false;
    }
}
