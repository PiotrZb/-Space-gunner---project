#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>

#include "menu.h"
#include "fpscounter.h"
#include "hero.h"
#include "sounds.h"
#include "bullet.h"
#include "scene1.h"
#include "gameover.h"

void load_texture(sf::Texture &texture, std::string file_path);
void load_bullet_textures(std::vector<sf::Texture> &bullet_textures);

int main(){

//--------------------------------------------------------------------------------------------------> initialization

    //window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Game", sf::Style::Titlebar | sf::Style::Close);
    sf::Image icon;
    if(!icon.loadFromFile( "icon.png" )){
        std::cout<<"ERROR::MAIN::ICON FAILED TO LOAD -> icon.png"<<std::endl;
    }
    window.setIcon( icon.getSize().x, icon.getSize().y, icon.getPixelsPtr() );
    window.setFramerateLimit(60);

    //camera
    sf::View view(sf::Vector2f(0,0),sf::Vector2f(1200,800));
    sf::View view_menu(sf::Vector2f(600,400),sf::Vector2f(1200,800));

    //background
    sf::Texture background_texture;
    load_texture(background_texture, "Textures/Background/background.png");
    sf::Sprite background;
    background.setTexture(background_texture);
    background.setTextureRect(sf::IntRect(0,0,1200, 800));

    GameOver game_over(1200, 800);

    //sounds
    Sounds sounds;
    sounds.play_main_theme(true, 10);

    //fps counter
    Fpscounter fpscounter;

New_game:
    {
        //menu
        Menu menu(1200, 800);


        //hero
        Hero hero(0,700);

        //bullets
        std::vector<sf::Texture> bullet_textures;
        load_bullet_textures(bullet_textures);
        std::list<Bullet> bullets;

        //Scene 1
        Scene1 scene1;

        sf::Clock clock;
        sf::Time elapsed;

        while (window.isOpen() && hero.get_hp() > 0){

//--------------------------------------------------------------------------------------------------> update functions

            elapsed = clock.restart();
            sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            menu.contains_mouse(mouse_position);

            //hero and scene updates
            if(!menu.is_active_){

                scene1.animate_elements(hero.getGlobalBounds(), elapsed);
                scene1.update_bounds(hero, elapsed, bullets);

                hero.gravity();
                hero.collisions(scene1.objects_bounds(), elapsed);
                hero.move_hero(elapsed);
                hero.animate();
            }

            //camera update
            view.setCenter(hero.getGlobalBounds().left + hero.getGlobalBounds().width, 400);


            //moving and removing bullets
            std::vector<sf::FloatRect> objects_bounds = scene1.objects_bounds();
            for(auto it = bullets.begin(); it != bullets.end(); ++it){

                if(!menu.is_active_){it->move_bullet(elapsed);}

                sf::FloatRect bullet_rect = it->getGlobalBounds();

                for(auto itr = objects_bounds.begin(); itr != objects_bounds.end(); ++itr){

                    if(bullet_rect.intersects(*itr)){

                        bullets.erase(it);
                    }
                }

                if(((bullet_rect.left + bullet_rect.width) < (view.getCenter().x - view.getSize().x))
                        || (bullet_rect.left > (view.getCenter().x + view.getSize().x))){

                    bullets.erase(it);
                }
            }

//--------------------------------------------------------------------------------------------------> movement

            if(!menu.is_active_){

                //move right
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){

                    hero.set_velocity_x(300);
                    hero.change_last_direction("right");

                    if(hero.jump_is_active()){

                        sounds.play_run_sound();
                    }
                }

                //move left
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){

                    hero.set_velocity_x(-300);
                    hero.change_last_direction("left");

                    if(hero.jump_is_active()){

                        sounds.play_run_sound();
                    }
                }

                //stop
                if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))){

                    hero.set_velocity_x(0);
                    sounds.stop_run_sound();
                }

                //jump
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && hero.jump_is_active()){

                    hero.set_velocity_y(-600);
                    sounds.play_jump_sound();
                    sounds.stop_run_sound();
                }
            }

//--------------------------------------------------------------------------------------------------> events

            sf::Event event;
            while (window.pollEvent(event)) {

                //closing the window
                if (event.type == sf::Event::Closed){

                    std::cout<<"Program was closed properly"<<std::endl;

                    window.close();
                }
                else{

                    //menu onclick events
                    if(menu.is_active_){

                        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){

                            menu.onclick_event_(mouse_position, window);
                        }
                    }
                    else{

                        //opening the menu
                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){

                            menu.is_active_ = true;
                        }
                        else{

                            //shooting
                            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left){

                                sounds.play_shot_sound(10);

                                Bullet bullet(hero.last_direction(), hero.barrel_cords().first, hero.barrel_cords().second, bullet_textures);
                                bullets.emplace_back(bullet);
                            }
                        }
                    }
                }
            }

//--------------------------------------------------------------------------------------------------> other update functions

            //camera update
            if(menu.is_active_){

                window.setView(view_menu);
                background.setPosition(0,0);
            }
            else{

                if(hero.getGlobalBounds().left + hero.getGlobalBounds().width > 600){

                    window.setView(view);
                    background.setPosition(view.getCenter().x - 600, view.getCenter().y - 400);
                }
            }

            //fps counter update
            fpscounter.update(window.getView().getCenter());

//--------------------------------------------------------------------------------------------------> Display

            window.clear(sf::Color::Black);
            window.draw(background);

            if(!menu.is_active_){

                window.draw(scene1);
                scene1.draw_animated_elements(window);
                window.draw(hero);

                for(auto it = bullets.begin(); it != bullets.end(); ++it){

                    window.draw(*it);
                }
            }

            menu.draw(window);
            window.draw(fpscounter);

            window.display();
        }
    }

//--------------------------------------------------------------------------------------------------> Game Over

    if(window.isOpen()){game_over.is_active_ = true;}

    while(game_over.is_active_){

        sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        game_over.contains_mouse(mouse_position);

        sf::Event event;
        while (window.pollEvent(event)) {

            //closing the window
            if (event.type == sf::Event::Closed){

                std::cout<<"Program was closed properly"<<std::endl;

                window.close();
            }
            else{

                //game over onclick events
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){

                    game_over.onclick_event_(mouse_position, window);
                }
            }
        }

        window.setView(view_menu);
        background.setPosition(0,0);

        window.clear(sf::Color::Black);

        window.draw(background);
        game_over.draw(window);
        window.draw(fpscounter);

        window.display();
    }

    if(window.isOpen()){
        goto New_game;
    }

    return 0;
}

//--------------------------------------------------------------------------------------------------> functions

void load_texture(sf::Texture &texture, std::string file_path){

    if(!texture.loadFromFile(file_path)){

        std::cout<<"ERROR::MAIN::TEXTURE FAILED TO LOAD -> "<<file_path<<std::endl;
    }
}

void load_bullet_textures(std::vector<sf::Texture> &bullet_textures){

    sf::Texture texture;

    load_texture(texture, "Textures/Bullet/bulletright.png");
    bullet_textures.emplace_back(texture);

    load_texture(texture, "Textures/Bullet/bulletleft.png");
    bullet_textures.emplace_back(texture);
}
