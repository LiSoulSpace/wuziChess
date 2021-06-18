#ifndef CHESS_MAIN_HPP
#define CHESS_MAIN_HPP
#include "chess_main.h"

template<typename T>
void chess_main<T>::initializate_checkerboard(int x, int y) {
    checkerboard = new T * [x];
    for (int i = 0; i < x; i++) {
        checkerboard[i] = new T[y];
        for (int j = 0; j < y; j++) {
            T tempT{};
            checkerboard[i][j] = tempT;
        }
    }
}

template <typename T>
T chess_main<T>::get_position_status(int x, int y) {
    return this->checkerboard[x][y];
}

template<typename T>
std::stack<coordinate<T>> chess_down<T>::get_record() {
    return record;
}

template<typename T>
void chess_down<T>::revoke() {
    T temp_T{};
    coordinate<T> temp = this->record.top();
    this->record.pop();
    this->checkerboard[temp.x][temp.y] = temp_T;
}

template<typename T>
void chess_down<T>::add_record(coordinate<T> c) {
    this->record.push(c);
    this->checkerboard[c.x][c.y] = c.cs;
}

template<typename T>
void chess_move<T>::add_record(coordinate_move<T> c) {
    T temp;
    this->record.push(c);
    this->checkerboard[c.c_pos.x][c.c_pos.y] = c.c_pre.cs;
    this->checkerboard[c.c_pre.x][c.c_pre.y] = temp;
}

template<typename T>
std::stack<coordinate_move<T>> chess_move<T>::get_record() {
    return record;
}

template<typename T>
void chess_move<T>::revoke() {
    coordinate_move<T> temp = this->record.top();
    this->record.pop();
    this->checkerboard[temp.c_pos.x][temp.c_pos.y] = 0;
    this->checkerboard[temp.c_pre.x][temp.c_pre.y] = temp.c_pos.cs;
}
#endif // CHESS_MAIN_HPP
