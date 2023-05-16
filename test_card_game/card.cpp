#define SOURCE_PATH_H
#include "card.h"

Card::Card(const std::string& sprite_name, const int size[2], SDL_Renderer* renderer, std::list<Card*>& card_list) :
HitBox(), card_size{size[0], size[1]}{
    setting_up(size);
    std::string path = std::string(dir_path)+ "/sprites/" + sprite_name;
    char char_arr[path.length() + 1];
    strcpy(char_arr, path.c_str());
    SDL_Surface *image;
    image = IMG_Load(char_arr);
    texture = SDL_CreateTextureFromSurface(renderer, image);
    card_list.push_front(this);
}

void Card::follow_mouse() {
    int xMouse, yMouse, x, y;
    SDL_GetMouseState(&xMouse,&yMouse);
    x = xMouse - xGrabP;
    y = yMouse - yGrabP;
    set_position(x + (rect.w - processed_columns*processed_width)/2, y + (rect.h - processed_rows*processed_height)/2);
    rect.x = x;
    rect.y = y;
    set_position()
}

void Card::back_to_start(int speed, int card_number, int quantity) {
    int x_start_point, y_start_point;
    x_start_point = window_size[0]/2 - rect.w/(1 + quantity/2) + (card_number - quantity/2)*lround(float(rect.w)/(1+float(quantity)/5.));
    y_start_point = std::lround(window_size[1] - rect.h*1.1);
    if (abs(rect.x - x_start_point) >= speed | abs(rect.y - y_start_point) >= speed ) {
        float sinus = float(rect.x - x_start_point) /
                float(std::hypot(rect.x - x_start_point, rect.y - y_start_point));
        rect.x -= std::lround(float(speed) * sinus);
        float cosine = float(rect.y - y_start_point) /
                float(std::hypot(rect.x - x_start_point, rect.y - y_start_point));
        rect.y -= std::lround(float(speed) * cosine);
    }
    set_position(rect.x + (rect.w - processed_columns*processed_width)/2, rect.y + (rect.h - processed_rows*processed_height)/2);
}

void Card::setting_up(const int size[2]) {
    create_rectangle(std::ceil(size[1]/5.),std::ceil(size[0]/5.));
    set_geometry(0, 0, 5, 5);

    rect.w = size[0];
    rect.h = size[1];
}
