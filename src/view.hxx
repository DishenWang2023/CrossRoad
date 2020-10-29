//
// Created by Avery on 3/8/20.
//

#ifndef FINAL_PROJECT_VIEW_HXX
#define FINAL_PROJECT_VIEW_HXX

#endif //FINAL_PROJECT_VIEW_HXX


#pragma once

#include "model.hxx"
#include "../.cs211/lib/ge211/include/ge211_sprites.hxx"

#include <string>

class View
{
public:
    explicit View(Model const&);

    void draw(ge211::Sprite_set& set);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

private:
    Model const& model_;

    ge211::Font const sans_;

    ge211::Rectangle_sprite const
            blockadeSpr;
    ge211::Image_sprite const
            gooseSpr;
    ge211::Image_sprite const
            gooseMSpr;
    ge211::Image_sprite const
            car1Spr;
    ge211::Image_sprite const
            car2Spr;
    ge211::Image_sprite const
            car3Spr;
    ge211::Image_sprite const
            coinSpr;
    ge211::Rectangle_sprite const
            grassSpr;
    ge211::Rectangle_sprite const
            roadSpr;
    Text_sprite
            levelSpr;
    Text_sprite
            coin_countSpr;
    ge211::Text_sprite
            liveSpr;
};
