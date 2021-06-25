#include "hud.h"

HUD::HUD(){

    if(!hp_bar_texture_.loadFromFile("Textures/Hero/hp.png")){

        std::cout<<"ERROR::HUD::TEXTURE FAILED TO LOAD -> Textures/Hero/hp.png"<<std::endl;
    }

    if(!black_heart_texture_.loadFromFile("Textures/Hero/blackheart.png")){

        std::cout<<"ERROR::HUD::TEXTURE FAILED TO LOAD -> Textures/Hero/blackheart.png"<<std::endl;
    }

    hp_bar_.setTexture(hp_bar_texture_);
    hp_bar_.setScale(3,3);

    for(int i = 0; i < 3; i++){

        black_hearts_.emplace_back(std::make_unique<sf::Sprite>(black_heart_texture_));
        black_hearts_[i]->setScale(3,3);

        switch (i) {

        case 0: black_hearts_[i]->setPosition(hp_bar_.getPosition().x + (54 * 3), hp_bar_.getPosition().x + (5 * 3) + 10); break;
        case 1: black_hearts_[i]->setPosition(hp_bar_.getPosition().x + (43 * 3), hp_bar_.getPosition().x + (5 * 3) + 10); break;
        case 2: black_hearts_[i]->setPosition(hp_bar_.getPosition().x + (32 * 3), hp_bar_.getPosition().x + (5 * 3) + 10); break;
        }
    }

    hp_ = 0;
}

void HUD::draw_hud(sf::RenderWindow &window){

    int i = 0;

    window.draw(hp_bar_);

    switch (hp_) {

    case 0: i = 3; break;
    case 1: i = 3; break;
    case 2: i = 2; break;
    case 3: i = 1; break;
    case 4: i = 0; break;
    }

    for(int j = 0; j < i; j++){

        window.draw(*black_hearts_[j]);
    }
}

int HUD::get_energy(){

    return energy_;
}

void HUD::set_energy(int &val){

    energy_ = val;
}

int HUD::get_hp(){

    return hp_;
}

void HUD::set_hp(int &val){

    hp_ = val;
}

void HUD::update(sf::Vector2f view, int hp){

    hp_bar_.setPosition(view.x - 590, view.y - 390);
    hp_ = hp;

    for(int i = 0; i < 3; i++){

        switch (i) {

        case 0: black_hearts_[i]->setPosition(hp_bar_.getPosition().x + (54 * 3), black_hearts_[i]->getPosition().y); break;
        case 1: black_hearts_[i]->setPosition(hp_bar_.getPosition().x + (43 * 3), black_hearts_[i]->getPosition().y); break;
        case 2: black_hearts_[i]->setPosition(hp_bar_.getPosition().x + (32 * 3), black_hearts_[i]->getPosition().y); break;
        }
    }
}
