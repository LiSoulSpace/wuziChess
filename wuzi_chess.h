#ifndef WUZI_CHESS_H
#define WUZI_CHESS_H
#include "chess_main.h"
#include "chess_main.cpp"
#include <QObject>
#include <QDebug>

template <typename T>
class wuzi_chess :protected chess_down<T> {
public:
    wuzi_chess();
    void down_chess(coordinate<T> c);
    void show_chessboard();
    T get_winner();
    bool get_isFinished();
    auto get_position_status(int x, int y) -> T;
protected:
    void check_finish() override;
    void find_items();
private:
    bool three_three_Forbidden;
    bool four_four_Forbidden;
    bool long_consecutive_Forbidden;
    bool is_three_three;
    bool is_four_four;
    bool is_long_consecutive;
    int live_three;
    int live_four;
    bool long_consecutive;
    bool true_five;
};

#endif // WUZI_CHESS_H
