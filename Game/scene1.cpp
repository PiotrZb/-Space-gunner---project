#include "scene1.h"

Scene1::Scene1(){

    objects_bounds_.emplace_back(sf::FloatRect(0,0,1,800));

    if(!scene1_texture_.loadFromFile("Textures/Sceneelements/Scene1.png")){
        std::cout<<"ERROR::SCENE1::TEXTURE FAILED TO LOAD -> Textures/Sceneelements/Scene1.png"<<std::endl;
    }

    setTexture(scene1_texture_);

    objects_bounds_.emplace_back(sf::FloatRect(0,700,350,100));
    objects_bounds_.emplace_back(sf::FloatRect(508,573,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(801,447,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(808,711,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(1133,711,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(1100,331,450,26));
    objects_bounds_.emplace_back(sf::FloatRect(1501,711,50,26));
    objects_bounds_.emplace_back(sf::FloatRect(1551,331,200,100));
    objects_bounds_.emplace_back(sf::FloatRect(1551,0,100,200));
    objects_bounds_.emplace_back(sf::FloatRect(1551,431,100,144));
    objects_bounds_.emplace_back(sf::FloatRect(1551,711,300,90));
    objects_bounds_.emplace_back(sf::FloatRect(1981,331,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(2151,711,150,26));
    objects_bounds_.emplace_back(sf::FloatRect(2601,711,150,26));

}

std::vector<sf::FloatRect> Scene1::objects_bounds(){

    return objects_bounds_;
}

