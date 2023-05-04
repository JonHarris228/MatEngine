#ifndef CARD_H
#define CARD_H
#include <MatEngine.h>
#include <list>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "source_path.h"


class Card: public HitBox{
public:
    int xGrabP{0} , yGrabP{0}, d{0};
    int card_size[2], window_size[2] = {720, 480};
    bool click{false};
    SDL_Texture* texture;
    SDL_Rect rect{};
    Card(const std::string& sprite_name, const int size[2], SDL_Renderer* renderer, std::list<Card*>& card_list);
    void follow_mouse();
    void back_to_start(int speed, int card_number, int quantity);
private:
    void setting_up(const int size[2]);
};

#endif