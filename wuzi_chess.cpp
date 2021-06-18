#ifndef WUZI_CHESS_HPP
#define WUZI_CHESS_HPP
#include <iostream>

#include "wuzi_chess.h"

template <typename T>
wuzi_chess<T>::wuzi_chess() {
    this->initializate_checkerboard(15, 15);
    three_three_Forbidden = false;
    four_four_Forbidden = false;
    long_consecutive_Forbidden = false;
    is_four_four = false;
    is_three_three = false;
    is_long_consecutive = false;
    live_three = 0;
    live_four = 0;
    long_consecutive = false;
    true_five = false;
}

template <typename T>
void wuzi_chess<T>::down_chess(coordinate<T> c) {
    if (this->get_position_status(c.x, c.y) == NONE) {
        this->add_record(c);
        check_finish();
    }
}

template <typename T>
void wuzi_chess<T>::show_chessboard() {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            std::cout << this->checkerboard[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    if (this->isFinished) std::cout << "Yes" << std::endl;
    else std::cout << "No" << std::endl;
}

template<typename T>
T wuzi_chess<T>::get_winner()
{
    return this->winner;
}

template <typename T>
bool wuzi_chess<T>::get_isFinished() {
    return this->isFinished;
}

template<typename T>
T wuzi_chess<T>::get_position_status(int x, int y)
{
    return this->checkerboard[x][y];
}

template <typename T>
void wuzi_chess<T>::check_finish() {
    //TODO:Finish checking function
    find_items();
    if (!three_three_Forbidden && !four_four_Forbidden && !long_consecutive_Forbidden) {
        if (this->true_five || this->long_consecutive) {
            this->isFinished = true;
            this->winner = this->get_record().top().cs;
        }
    }
}

template <typename T>
void wuzi_chess<T>::find_items() {
    auto top = this->get_record().top();
    std::cout << top.x << " " << top.y << std::endl;
    int x = top.x;
    int y = top.y;
    ChessStatus cs = top.cs;
    int now_connected = 0;
    int max_connected = 0;

    //左右判断
    while (this->checkerboard[x--][y] == cs) {
        now_connected++;
        if (x < 0) break;
    }
    x = top.x;
    if (x < 14) {
        while (this->checkerboard[++x][y] == cs) {
            now_connected++;
            if (x == 14) break;
        }
    }
    if (now_connected == 5) this->true_five = true;
    else if (now_connected > 5) this->long_consecutive = true;
    if (now_connected > max_connected)max_connected = now_connected;
    x = top.x;
    y = top.y;

    //上下判断
    now_connected = 0;
    while (this->checkerboard[x][y--] == cs) {
        now_connected++;
        if (y < 0) break;
    }
    y = top.y;
    if (y < 14) {
        while (this->checkerboard[x][++y] == cs) {
            now_connected++;
            if (y == 14) break;
        }
    }
    if (now_connected == 5) this->true_five = true;
    else if (now_connected > 5) this->long_consecutive = true;
    if (now_connected > max_connected)max_connected = now_connected;
    x = top.x;
    y = top.y;

    //左上右下判断
    now_connected = 0;
    while (this->checkerboard[x--][y--] == cs) {
        now_connected++;
        if (y < 0 || x < 0) break;
    }
    x = top.x;
    y = top.y;
    if (x != 14 && y != 14) {
        while (this->checkerboard[++x][++y] == cs) {
            now_connected++;
            if (y == 14 || x == 14) break;
        }
    }
    if (now_connected == 5) this->true_five = true;
    else if (now_connected > 5) this->long_consecutive = true;
    if (now_connected > max_connected)max_connected = now_connected;
    x = top.x;
    y = top.y;

    //右上左下判断
    now_connected = 0;
    while (this->checkerboard[x--][y++] == cs) {
        now_connected++;
        if (y < 0 || x < 0) break;
    }
    x = top.x;
    y = top.y;
    if (x != 14 && y != 14) {
        while (this->checkerboard[++x][--y] == cs) {
            now_connected++;
            if (y == 14 || x == 14) break;
        }
    }
    if (now_connected == 5) this->true_five = true;
    else if (now_connected > 5) this->long_consecutive = true;
    if (now_connected > max_connected)max_connected = now_connected;
    x = top.x;
    y = top.y;
    std::cout <<"max_connected : " << max_connected << "\n";
}
#endif // WUZI_CHESS_HPP
