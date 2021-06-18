#ifndef CHESS_MAIN_H
#define CHESS_MAIN_H
#include <vector>
#include <stack>
enum ChessStatus { NONE, BLACK, WHITE, ANY };
template <typename T>
struct coordinate {
    int x;
    int y;
    T cs;
};

template <typename T>
struct coordinate_move {
    coordinate<T> c_pre;
    coordinate<T> c_pos;
};

template <typename T>
class chess_main {
public:
    virtual ~chess_main() = default;
    T** checkerboard;
    bool isFinished = false;
    T winner;
    virtual void revoke() = 0;
    virtual void check_finish() = 0;
    void initializate_checkerboard(int x, int y);
    auto get_position_status(int x, int y) -> T;
};

template<typename T>
class chess_down :protected chess_main<T> {
public:
    std::stack<coordinate<T>> get_record();
protected:
    void revoke() override;
    void add_record(coordinate<T> c);
private:
    std::stack<coordinate<T>> record;
};

template<typename T>
class chess_move :protected chess_main<T> {
public:
    std::stack<coordinate_move<T>> get_record();
protected:
    void revoke() override;
    void add_record(coordinate_move<T> c);
private:
    std::stack<coordinate_move<T>> record;
};

#endif // CHESS_MAIN_H
