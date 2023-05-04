#include "test_card_game.h"

int main(int argc, char** args){
    // SDL initialisation
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    auto window = SDL_CreateWindow("Window", 100, 100, window_size[0], window_size[1], 0);
    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialisation objects(cards)
    std::list<Card*> card_list;
    Card(std::string("king_of_spades2.png"), card_size, renderer, card_list);
    Card(std::string("4_of_hearts.png"), card_size, renderer, card_list);
    Card(std::string("5_of_diamonds.png"), card_size, renderer, card_list);
    // Create cursor hit-box
    cursor.create_single();
    cursor.set_size(5,5);

    // Initialisation SDL_event
    SDL_Event event;
    // Make main game loop
    bool running = true;
    while (running) {
        SDL_GetMouseState(&xMouse,&yMouse);
        cursor.set_position(xMouse-2, yMouse-2);

        loop(card_list, cursor);
        rendering(renderer);
        // Event loop
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    left_click_down(event, card_list, cursor);
                    break;
                case SDL_MOUSEBUTTONUP:
                    left_click_up(event, card_list);
                    break;
                default:
                    break;
            }
        }
        SDL_Delay(1000/60);
    }
    SDL_Quit();
}


void loop(std::list<Card*>& card_list, HitBox curs){
    int iter = 0, rotation_h;
    Card *top_card = nullptr;
    card_chosen = false;
    rendering_list.clear();
    for(auto &card:card_list) {
        if (card->click){
            card->follow_mouse(); top_card = card;
        }else{
            card->back_to_start(25, iter, int(card_list.size()));
            rotation_h = (((360 - card->rect.w / 2) - card->rect.x) / 10) - card->d;
            if (rotation_h >= 1) card->d += 1;
            else if (rotation_h <= -1) card->d -=1;
        }

        if (card->click and abs(card->d) < 2) card->d = 0;
        else if (card->click and card->d != 0) card->d -= (card->d/abs(card->d))*2;

        if (Collision::simple_collision(*card, curs) and !card_chosen and !card_in_hand){
            // Reset all cards sizes
            for (auto &reset_cards:card_list){
                reset_cards->scale(1);
                reset_cards->rect.w = card_size[0];
                reset_cards->rect.h = card_size[1];
            }
            card_chosen = true;
            card->scale(1.2);
            card->rect.w = std::lround(card_size[0] * 1.2);
            card->rect.h = std::lround(card_size[1] * 1.2);
            top_card = card;


        }else if (!Collision::spacing_collision(*card, curs, 20, 20)){
            card->scale(1);
            card->rect.w = card_size[0];
            card->rect.h = card_size[1];
        }

        card->rotate(float(card->d));
        iter++;
        if (card != top_card)  rendering_list.push_back(card);
    }
    if (top_card != nullptr)rendering_list.push_front(top_card);
}

void rendering(SDL_Renderer* renderer){
    // Load card to renderer
    for (auto card : std::ranges::reverse_view(rendering_list)){
        SDL_RenderCopyEx(renderer, card->texture, nullptr, &card->rect, -card->d,
                         nullptr, SDL_FLIP_NONE);
        // Load hit-box visualisation to renderer
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        for (int i = 0; i < card->processed_columns; i++) {
            SDL_Rect rect;
            rect.y = card->processed_y0 + card->hit_boxes_matrix[i][0] * card->processed_height;
            rect.x = card->processed_x0 + i * card->processed_width;
            rect.w = card->processed_width;
            rect.h = card->hit_boxes_matrix[i][1] * card->processed_height;
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
    // Unpacking renderer to screen
    SDL_RenderPresent(renderer);
    // Clear renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void left_click_down(SDL_Event event, std::list<Card*>& card_list, HitBox& curs){
    int x, y;
    // Checking button click and collision between card and cursor
   for (auto & card : card_list){
    if (event.button.button == SDL_BUTTON_LEFT and Collision::simple_collision(*card, curs)){
        SDL_GetMouseState(&x, &y);
        card->xGrabP = x - card->rect.x;
        card->yGrabP = y - card->rect.y;
        card->click = true;
        card_in_hand = true;

        card->scale(1.25);
        card->set_position(card->rect.x + (card->rect.w - card->processed_columns*card->processed_width)/2,
                           card->rect.y + (card->rect.h - card->processed_rows*card->processed_height)/2);
        card->rect.w = std::lround(card_size[0] * 1.25);
        card->rect.h = std::lround(card_size[1] * 1.25);
        break;
        }
    }
}

void left_click_up(SDL_Event event, std::list<Card*>& card_list){
    for (auto & card : card_list){
        if (event.button.button == SDL_BUTTON_LEFT) {
            card->click = false;
            card_in_hand = false;

            card->scale(1);
            card->rect.w = card_size[0];
            card->rect.h = card_size[1];
        }
    }
}