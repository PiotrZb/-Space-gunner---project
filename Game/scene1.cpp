#include "scene1.h"

Scene1::Scene1(){

    if(!scene1_texture_.loadFromFile("Textures/Sceneelements/Scene1.png")){
        std::cout<<"ERROR::SCENE1::TEXTURE FAILED TO LOAD -> Textures/Sceneelements/Scene1.png"<<std::endl;
    }

    setTexture(scene1_texture_);

    //air locks
    air_lock1_.setPosition(1594,201);
    air_lock2_.setPosition(1594,581);

    //platforms
//    platform1_.setPosition(200,200);
//    platform1_.set_movement_bounds(sf::FloatRect(201,210,800,30));
//    platform1_.set_velocity_x(100);

    //animated elements
    objects_bounds_.emplace_back(air_lock1_.getGlobalBounds());
    objects_bounds_.emplace_back(air_lock2_.getGlobalBounds());

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

//    platform1_.move_platform(elapsed);
}

void Scene1::draw_animated_elements(sf::RenderWindow &window){

    window.draw(air_lock1_);
    window.draw(air_lock2_);
//    window.draw(platform1_);
}

void Scene1::update_bounds(){

    objects_bounds_[0] = air_lock1_.getGlobalBounds();
    objects_bounds_[1] = air_lock2_.getGlobalBounds();
}
