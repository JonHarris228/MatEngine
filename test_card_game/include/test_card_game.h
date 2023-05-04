#ifndef TEST_CARD_GAME_H
#define TEST_CARD_GAME_H
#include "card.h"
#include <MatEngine.h>
#include <ranges>
#include <list>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

HitBox cursor;
std::list<Card*> rendering_list;
int xMouse, yMouse;
int card_size[2] = {250, 363}, window_size[2] = {720, 480};
bool card_in_hand = false;
bool card_chosen = false;

void loop(std::list<Card*>& card_list, HitBox curs);
void rendering(SDL_Renderer* renderer);
void left_click_down(SDL_Event event, std::list<Card*>& card_list, HitBox& curs);
void left_click_up(SDL_Event event, std::list<Card*>& card_list);

#endif