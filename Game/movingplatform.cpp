#include "movingplatform.h"

MovingPlatform::MovingPlatform(){

    if(!texture_.loadFromFile("Textures/Sceneelements/Platform.png")){
        std::cout<<"ERROR::SCENE1::MOVINGPLATFORM::TEXTURE FAILED TO LOAD -> Textures/Sceneelements/Platform.png"<<std::endl;
    }

    setTexture(texture_);
    setTextureRect(sf::IntRect(0,0,200,26));
    texture_.setRepeated(true);

    velocity_x_ = 0;
    velocity_y_ = 0;
}

void MovingPlatform::set_movement_bounds(sf::FloatRect movement_bounds){

    movement_bounds_ = movement_bounds;
}

void MovingPlatform::move_platform(sf::Time &elapsed){

    if(movement_bounds_.left > getGlobalBounds().left){

        velocity_x_ = abs(velocity_x_);
    }
    else {
        if(movement_bounds_.left + movement_bounds_.width < getGlobalBounds().left + getGlobalBounds().width){

            velocity_x_ = abs(velocity_x_) * (-1);
        }
    }

    if(movement_bounds_.top > getGlobalBounds().top){

        velocity_y_ *= abs(velocity_y_);
    }
    else {

        if(movement_bounds_.top + movement_bounds_.height < getGlobalBounds().top + getGlobalBounds().height){

            velocity_y_ = abs(velocity_y_) * (-1);
        }
    }

    move(elapsed.asSeconds() * velocity_x_, elapsed.asSeconds() * velocity_y_);
}

void MovingPlatform::set_velocity_x(int velocity_x){

    velocity_x_ = velocity_x;
}

void MovingPlatform::set_velocity_y(int velocity_y){

    velocity_y_ = velocity_y;
}

int MovingPlatform::get_velocity_x(){

    return velocity_x_;
}

int MovingPlatform::get_velocity_y(){

    return velocity_y_;
}
