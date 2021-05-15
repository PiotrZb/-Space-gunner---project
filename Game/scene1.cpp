#include "scene1.h"

Scene1::Scene1(){

    if(!scene1_texture_.loadFromFile("Textures/Sceneelements/Scene1.png")){
        std::cout<<"ERROR::SCENE1::TEXTURE FAILED TO LOAD -> Textures/Sceneelements/Scene1.png"<<std::endl;
    }

    setTexture(scene1_texture_);

    if(!air_lock_texture_.loadFromFile("Textures/Sceneelements/Gate.png")){
        std::cout<<"ERROR::SCENE1::TEXTURE FAILED TO LOAD -> Textures/Sceneelements/Gate.png"<<std::endl;
    }

    air_lock_.setTexture(air_lock_texture_);
    air_lock_texture_.setRepeated(true);
    air_lock_.setTextureRect(sf::IntRect(0,0,15,123));
    air_lock_.setPosition(1594,208);
    air_lock_current_frame_ = 12;

    //animated elements
    objects_bounds_.emplace_back(air_lock_.getGlobalBounds());

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

void Scene1::animate_elements(sf::FloatRect hero_bounds){

    if(hero_bounds.intersects(sf::FloatRect(1452,200,299,131))){

        animate_air_lock("open");
    }
    else{

        animate_air_lock("close");
    }
}

void Scene1::animate_air_lock(std::string status){

    if(clock_.getElapsedTime().asSeconds() >= 0.07){

        if(air_lock_current_frame_ > 0 && status == "open"){

            air_lock_current_frame_--;
        }
        else{

            if(air_lock_current_frame_ < 12 && status == "close"){

                air_lock_current_frame_++;
            }
        }

        clock_.restart();
    }

    switch (air_lock_current_frame_) {

    case 0: air_lock_.setTextureRect(sf::IntRect(0,0,15,0)); break;
    case 1: air_lock_.setTextureRect(sf::IntRect(0,0,15,10)); break;
    case 2: air_lock_.setTextureRect(sf::IntRect(0,0,15,20)); break;
    case 3: air_lock_.setTextureRect(sf::IntRect(0,0,15,30)); break;
    case 4: air_lock_.setTextureRect(sf::IntRect(0,0,15,40)); break;
    case 5: air_lock_.setTextureRect(sf::IntRect(0,0,15,50)); break;
    case 6: air_lock_.setTextureRect(sf::IntRect(0,0,15,60)); break;
    case 7: air_lock_.setTextureRect(sf::IntRect(0,0,15,70)); break;
    case 8: air_lock_.setTextureRect(sf::IntRect(0,0,15,80)); break;
    case 9: air_lock_.setTextureRect(sf::IntRect(0,0,15,90)); break;
    case 10: air_lock_.setTextureRect(sf::IntRect(0,0,15,100)); break;
    case 11: air_lock_.setTextureRect(sf::IntRect(0,0,15,110)); break;
    case 12: air_lock_.setTextureRect(sf::IntRect(0,0,15,123)); break;
    }
}

void Scene1::draw_animated_elements(sf::RenderWindow &window){

    window.draw(air_lock_);
}

void Scene1::update_bounds(){

    objects_bounds_[0] = air_lock_.getGlobalBounds();
}
