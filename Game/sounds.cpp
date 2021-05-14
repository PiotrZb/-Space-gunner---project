#include "sounds.h"

Sounds::Sounds(){

    if(!main_theme_.openFromFile("Sounds/maintheme.wav")){

        std::cout<<"ERROR::SOUNDS::SOUND FAILED TO LOAD -> Sounds/maintheme.wav"<<std::endl;
    }

    sound_load(jump_, "jump.wav");
    sound_load(run_, "longrun.wav");
    sound_load(shot_, "shot1.wav");

    rs_is_active_ = false;
}

void Sounds::play_main_theme(bool loop, float volume){

    main_theme_.setLoop(loop);
    main_theme_.setVolume(volume);
    main_theme_.play();
}

void Sounds::sound_load(sf::SoundBuffer &sound, std::string file_name){

    if(!sound.loadFromFile("Sounds/" + file_name)){

        std::cout<<"ERROR::SOUNDS::SOUND FAILED TO LOAD -> Sounds/" + file_name<<std::endl;
    }
}

void Sounds::play_jump_sound(float volume){

    jump_sound_.setBuffer(jump_);
    jump_sound_.setVolume(volume);
    jump_sound_.play();
    jump_sound_.pause();
    jump_sound_.setPlayingOffset(sf::milliseconds(250));
    jump_sound_.play();
}

void Sounds::play_run_sound(float volume){

    if(!rs_is_active_){

        run_sound_.setBuffer(run_);
        run_sound_.setVolume(volume);
        run_sound_.setLoop(true);
        run_sound_.play();
    }

    rs_is_active_ = true;
}

void Sounds::stop_run_sound(){

    run_sound_.stop();
    rs_is_active_ = false;
}

void Sounds::play_shot_sound(float volume){

    shot_sound_.setBuffer(shot_);
    shot_sound_.setVolume(volume);
    shot_sound_.play();
}
