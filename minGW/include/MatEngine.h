#ifndef MATENGINE_H
#define MATENGINE_H

#include <cmath>
#include <algorithm>
#include <iostream>

#define pi 3.14159265

class HitBox{
public:
    int columns, rows, processed_columns, processed_rows;
    int x0, y0, width, height, processed_x0, processed_y0, processed_width, processed_height;
    int ** hit_boxes_matrix;
    void create_rectangle(int rows_len, int columns_len);
    void create_circle(int radius);
    void create_single();
    void set_geometry(int x_0, int y_0, int w, int h);
    void set_position(int x_0, int y_0);
    void set_size(int w, int h);
    void reset();
    void rotate(float degree);
    void scale(float multiplicand);

private:
    bool ** template_matrix, ** processed_matrix;
    int columns_shifting, rows_shifting;
    void generate_matrices(int rows_len, int columns_len);
    void generate_rotated_matrix();
    void rotate_matrix_size(float radians);
    void coordinate_shifting(float radians);
    void matrix2hit_box();
    template <typename t> void delete_matrix(t **matrix, int quantity);
};

class Collision{
public:
    static bool simple_collision(HitBox& object1, HitBox& object2);
    static bool spacing_collision(HitBox& object1, HitBox& object2, int x_space, int y_space);
};

#endif