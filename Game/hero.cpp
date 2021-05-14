#include "hero.h"

Hero::Hero(float x, float y){

    sf::Texture texture;

    load_texture(texture, "standright.png");
    standing_.emplace_back(texture);

    load_texture(texture, "standleft.png", sf::IntRect(4,4,37,46));
    standing_.emplace_back(texture);

    load_texture(texture, "jumpright.png");
    jumping_.emplace_back(texture);

    load_texture(texture, "jumpleft.png", sf::IntRect(4,4,37,46));
    jumping_.emplace_back(texture);

    for(int i = 1; i < 9; i++){

        load_texture(texture, "runright" + std::to_string(i) + ".png");
        running_right_.emplace_back(texture);

        load_texture(texture, "runleft" + std::to_string(i) + ".png", sf::IntRect(4,4,37,46));
        running_left_.emplace_back(texture);
    }

    setTexture(standing_[0]);
    setScale(sf::Vector2f(2.5,2.5));
    setPosition(x, y - getGlobalBounds().height);

    velocity_x_ = 0;
    velocity_y_ = 0;
    current_image_right_ = 0;
    current_image_left_ = 0;
    last_direction_ = "right";
}

void Hero::move_hero(sf::Time &elapsed){

    move(velocity_x_ * elapsed.asSeconds(), velocity_y_ * elapsed.asSeconds());

    if(last_direction_ == "right"){

        barrel_cords_.first = getPosition().x + 90;
    }
    else{
        barrel_cords_.first = getPosition().x - 20;
    }

    barrel_cords_.second = getPosition().y + 32;
}

void Hero::animate(){

    if(velocity_y_ == 0 && velocity_x_ == 0){

        if(last_direction_ == "right"){

            setTexture(standing_[0]);
        }
        else{

            setTexture(standing_[1]);
        }

        reset_run_animation();
    }
    else{

        if(velocity_y_ != 0 ){

            jump_animation();
            reset_run_animation();
        }
        else{

            run_animation();
        }
    }
}

bool Hero::jump_is_active(){

    if(velocity_y_ == 0){return true;}
    else {return false;}
}

void Hero::set_velocity_x(int velx){

    velocity_x_ = velx;
}

void Hero::set_velocity_y(int vely){

    velocity_y_ = vely;
}

void Hero::gravity(){

    velocity_y_ +=21;
}

void Hero::load_texture(sf::Texture &texture, std::string file_name, sf::IntRect rect){

    if(!texture.loadFromFile("Textures/Hero/" + file_name, rect)){

        std::cout<<"ERROR::HERO::TEXTURE FAILED TO LOAD -> Textures/Hero/" + file_name<<std::endl;
    }
}

void Hero::change_last_direction(std::string direction){

    last_direction_ = direction;
}

void Hero::jump_animation(){

    if(last_direction_ == "right"){

        setTexture(jumping_[0]);
    }
    else{

        setTexture(jumping_[1]);
    }
}

void Hero::run_animation(){

    if(last_direction_ == "right"){

        current_image_left_ = 0;

        if(clock.getElapsedTime().asSeconds() >= 0.07){

            current_image_right_++;
            clock.restart();
        }

        if(current_image_right_ == 8){

            current_image_right_ = 0;
        }

        setTexture(running_right_[current_image_right_]);
    }
    else{

        current_image_right_ = 0;

        if(clock.getElapsedTime().asSeconds() >= 0.07){

            current_image_left_++;
            clock.restart();
        }

        if(current_image_left_ == 8){

            current_image_left_ = 0;
        }

        setTexture(running_left_[current_image_left_]);
    }
}

std::string Hero::last_direction(){

    return last_direction_;
}

std::pair<float,float> Hero::barrel_cords(){

    return barrel_cords_;
}

void Hero::collisions(std::vector<sf::FloatRect> objects_bounds, sf::Time &elapsed){

    sf::FloatRect X = getGlobalBounds();
    sf::FloatRect Y = getGlobalBounds();

    X.left += velocity_x_ * elapsed.asSeconds();
    Y.top += velocity_y_ * elapsed.asSeconds();

    for(size_t i = 0; i < objects_bounds.size(); i++){

        if(X.intersects(objects_bounds[i])){

            if(velocity_x_ > 0){

                setPosition(objects_bounds[i].left - getGlobalBounds().width, getGlobalBounds().top);
            }
            else{

                setPosition(objects_bounds[i].left + objects_bounds[i].width, getGlobalBounds().top);
            }

            velocity_x_ = 0;
        }

        if(Y.intersects(objects_bounds[i])){

            if(velocity_y_ < 0){

                velocity_y_ = 1;
                setPosition(getGlobalBounds().left, objects_bounds[i].top + objects_bounds[i].height);
            }
            else{

                velocity_y_ = 0;
                setPosition(getGlobalBounds().left, objects_bounds[i].top - getGlobalBounds().height);
            }
        }
    }
}

void Hero::reset_run_animation(){

    current_image_left_ = 0;
    current_image_right_ = 0;
}
