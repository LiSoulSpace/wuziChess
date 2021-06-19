#ifndef WUZI_CHESS_HPP
#define WUZI_CHESS_HPP

#include <iostream>

#include "wuzi_chess.h"

template <typename T>
wuzi_chess<T>::wuzi_chess() {
    this->initializate_checkerboard(15, 15);
    three_three_Forbidden = true;
    four_four_Forbidden = true;
    long_consecutive_Forbidden = true;
    is_four_four = false;
    is_three_three = false;
    is_long_consecutive = false;
    long_consecutive = false;
    true_five = false;
    checkArray = new Forbidden*[15];
    for (int i = 0; i < 15; ++i) {
        checkArray[i] = new Forbidden[15];
        for (int j = 0; j < 15; ++j) {
            checkArray[i][j] = UNKNOWN;
        }
    }
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

template <typename T>
T wuzi_chess<T>::get_winner() {
    return this->winner;
}

template <typename T>
bool wuzi_chess<T>::get_isFinished() {
    return this->isFinished;
}

template <typename T>
auto wuzi_chess<T>::get_position_status(int x, int y) -> T {
    return this->checkerboard[x][y];
}

template<typename T>
void wuzi_chess<T>::setForbidden(bool isForbidden)
{
    this->four_four_Forbidden = isForbidden;
    this->three_three_Forbidden = isForbidden;
    this->long_consecutive_Forbidden = isForbidden;
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
    } else if (three_three_Forbidden && four_four_Forbidden && long_consecutive_Forbidden) {
        if (is_three_three || is_four_four || is_long_consecutive) {
            this->isFinished = true;
            this->winner = WHITE;
        } else {
            if (this->true_five || this->long_consecutive) {
                this->isFinished = true;
                this->winner = this->get_record().top().cs;
            }
        }
    }
    reset_checkArray();
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

    T** test_board = new T*[15];
    for (int i = 0; i < 15; ++i) {
        test_board[i] = new T[15];
        for (int j = 0; j < 15; ++j) {
            test_board[i][j] = this->checkerboard[i][j];
        }
    }

    // std::cout << "___test_board_beg___\n";
    // for (int i = 0; i < 15; ++i) {
    // 	for (int j = 0; j < 15; ++j) {
    // 		std::cout << test_board[i][j] << " ";
    // 	}
    // 	std::cout << '\n';
    // }
    // std::cout << "___test_board_end____\n";

    if(three_three_Forbidden){
        if (top.cs == BLACK) {
            x = top.x;
            y = top.y;
            std::cout << "BLACK DOWN : " << x << " " << y << std::endl;
            Forbidden fb = forbidden_check(test_board, x, y);
            std::cout << "fb : " << fb << '\n';
            if (fb == THREE_THREE_FORBIDDEN) {
                this->is_three_three = true;
                return;
            } else if (fb == FOUR_FOUR_FORBIDDEN) {
                this->is_four_four = true;
                return;
            } else if (fb == LONG_CONSECUTIVE_FORBIDDEN) {
                this->is_long_consecutive = true;
                return;
            }
            this->checkerboard[x][y] = BLACK;
        }
    }

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
    if (now_connected > max_connected) max_connected = now_connected;
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
    if (now_connected > max_connected) max_connected = now_connected;
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
    if (now_connected > max_connected) max_connected = now_connected;
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
    if (now_connected > max_connected) max_connected = now_connected;
    x = top.x;
    y = top.y;
    std::cout << "max_connected : " << max_connected << "\n";
}

template <typename T>
Forbidden wuzi_chess<T>::forbidden_check(T** checkerboard, int x, int y) {
    //std::cout << "Forbidden Check : " << x << " " << y << std::endl;
    //std::cout << "_____________________forbidden_check_(" << x << "," << y << ")_beg______________________\n";
//    for (int m = 0; m < 15; ++m) {
//        for (int n = 0; n < 15; ++n) {
//            std::cout << checkerboard[m][n] << " ";
//        }
//        std::cout << std::endl;
//    }
    int connectBlack[8]{};
    int connectEmpty[8]{};
    int jConnectBlack[8]{};
    int jConnectEmpty[8]{};
    int djConnectBlack[8]{};
    for (int i = 0; i < 8; ++i) {
        connectBlack[i] = 0;
        connectEmpty[i] = 0;
        jConnectBlack[i] = 0;
        jConnectEmpty[i] = 0;
        djConnectBlack[i] = 0;
    }

    checkerboard[x][y] = BLACK;

    int x_, y_;
    //向左搜索
    if (y != 0) {
        for (y_ = y - 1; y_ >= 0 && checkerboard[x][y_] == BLACK; y_--, connectBlack[6]++);
        for (; y_ >= 0 && checkerboard[x][y_] == NONE; y_--, connectEmpty[6]++);
        for (; y_ >= 0 && checkerboard[x][y_] == BLACK; y_--, jConnectBlack[6]++);
        for (; y_ >= 0 && checkerboard[x][y_] == NONE; y_--, jConnectEmpty[6]++);
        for (; y_ >= 0 && checkerboard[x][y_] == BLACK; y_--, djConnectBlack[6]++);
    }

    //左下搜索
    if (x != 14 && y != 0) {
        for (x_ = x + 1, y_ = y - 1; x_ < 15 && y_ >= 0 && checkerboard[x_][y_] == BLACK; x_++, y_--, connectBlack[5]++);
        for (; x_ < 15 && y_ >= 0 && checkerboard[x_][y_] == NONE; x_++, y_--, connectEmpty[5]++);
        for (; x_ < 15 && y_ >= 0 && checkerboard[x_][y_] == BLACK; x_++, y_--, jConnectBlack[5]++);
        for (; x_ < 15 && y_ >= 0 && checkerboard[x_][y_] == NONE; x_++, y_--, jConnectEmpty[5]++);
        for (; x_ < 15 && y_ >= 0 && checkerboard[x_][y_] == BLACK; x_++, y_--, djConnectBlack[5]++);
    }

    //向下搜索
    if (x != 14) {
        for (x_ = x + 1; x_ < 15 && checkerboard[x_][y] == BLACK; x_++, connectBlack[4]++);
        for (; x_ < 15 && checkerboard[x_][y] == NONE; x_++, connectEmpty[4]++);
        for (; x_ < 15 && checkerboard[x_][y] == BLACK; x_++, jConnectBlack[4]++);
        for (; x_ < 15 && checkerboard[x_][y] == NONE; x_++, jConnectEmpty[4]++);
        for (; x_ < 15 && checkerboard[x_][y] == BLACK; x_++, djConnectBlack[4]++);
    }

    //向右下搜索
    if (y != 14 && x != 14) {
        for (y_ = y + 1, x_ = x + 1; y_ < 15 && x_ < 15 && checkerboard[x_][y_] == BLACK; y_++, x_++, connectBlack[3]
             ++);
        for (; x_ < 15 && y_ < 15 && checkerboard[x_][y_] == NONE; y_++, x_++, connectEmpty[3]++);
        for (; x_ < 15 && y_ < 15 && checkerboard[x_][y_] == BLACK; y_++, x_++, jConnectBlack[3]++);
        for (; x_ < 15 && y_ < 15 && checkerboard[x_][y_] == NONE; y_++, x_++, jConnectEmpty[3]++);
        for (; x_ < 15 && y_ < 15 && checkerboard[x_][y_] == BLACK; y_++, x_++, djConnectBlack[3]++);
    }

    //向右搜索
    if (y != 14) {
        for (y_ = y + 1; y_ < 15 && checkerboard[x][y_] == BLACK; y_++, connectBlack[2]++);
        for (; y_ < 15 && checkerboard[x][y_] == NONE; y_++, connectEmpty[2]++);
        for (; y_ < 15 && checkerboard[x][y_] == BLACK; y_++, jConnectBlack[2]++);
        for (; y_ < 15 && checkerboard[x][y_] == NONE; y_++, jConnectEmpty[2]++);
        for (; y_ < 15 && checkerboard[x][y_] == BLACK; y_++, djConnectBlack[2]++);
    }

    //向右上搜索
    if (y != 14 && x != 0) {
        for (y_ = y + 1, x_ = x - 1; x_ >= 0 && y_ < 15 && checkerboard[x_][y_] == BLACK; y_++, x_--, connectBlack[1]++);
        for (; x_ >= 0 && y_ < 15 && checkerboard[x_][y_] == NONE; y_++, x_--, connectEmpty[1]++);
        for (; x_ >= 0 && y_ < 15 && checkerboard[x_][y_] == BLACK; y_++, x_--, jConnectBlack[1]++);
        for (; x_ >= 0 && y_ < 15 && checkerboard[x_][y_] == NONE; y_++, x_--, jConnectEmpty[1]++);
        for (; x_ >= 0 && y_ < 15 && checkerboard[x_][y_] == BLACK; y_++, x_--, djConnectBlack[1]++);
    }

    //向上搜索
    if (x != 0) {
        for (x_ = x - 1; x_ >= 0 && checkerboard[x_][y] == BLACK; x_--, connectBlack[0]++);
        for (; x_ >= 0 && checkerboard[x_][y] == NONE; x_--, connectEmpty[0]++);
        for (; x_ >= 0 && checkerboard[x_][y] == BLACK; x_--, jConnectBlack[0]++);
        for (; x_ >= 0 && checkerboard[x_][y] == NONE; x_--, jConnectEmpty[0]++);
        for (; x_ >= 0 && checkerboard[x_][y] == BLACK; x_--, djConnectBlack[0]++);
    }

    //向左上搜索
    if (x != 0 && y != 0) {
        for (x_ = x - 1, y_ = y - 1; x_ >= 0 && y_ >= 0 && checkerboard[x_][y_] == BLACK; x_--, y_--, connectBlack[7]++);
        for (; x_ >= 0 && y_ >= 0 && checkerboard[x_][y_] == NONE; x_--, y_--, connectEmpty[7]++);
        for (; x_ >= 0 && y_ >= 0 && checkerboard[x_][y_] == BLACK; x_--, y_--, jConnectBlack[7]++);
        for (; x_ >= 0 && y_ >= 0 && checkerboard[x_][y_] == NONE; x_--, y_--, jConnectEmpty[7]++);
        for (; x_ >= 0 && y_ >= 0 && checkerboard[x_][y_] == BLACK; x_--, y_--, djConnectBlack[7]++);
    }

    checkerboard[x][y] = NONE;

    for (int i = 0; i < 4; ++i) {
        if (connectBlack[i] + connectBlack[i + 4] == 4) {
            return NO_FORBIDDEN;
        }
    }
    int threeCount = 0;
    int fourCount = 0;
    for (int i = 0; i < 4; ++i) {
        if (connectBlack[i] + connectBlack[i + 4] >= 5) {
            return LONG_CONSECUTIVE_FORBIDDEN;
        }
        if (connectBlack[i] + connectBlack[i + 4] == 3) {
            //?0010?
            bool isFour = false;
            if (connectEmpty[i] > 0) {
                //?+0010?
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i], i) == NO_FORBIDDEN) isFour = true;
            }
            if (connectEmpty[i + 4] > 0) {
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i + 4], i + 4) == NO_FORBIDDEN)
                    isFour = true;
            }
            if (isFour) {
                fourCount++;
            }
        } else if (connectBlack[i] + connectBlack[i + 4] == 2) {
            //?000?
            if (connectEmpty[i] == 1 && jConnectBlack[i] == 1) {
                //0?000
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i], i) == NO_FORBIDDEN) {
                    fourCount++;
                }
            }
            if (connectEmpty[i + 4] == 1 && jConnectBlack[i + 4] == 1) {
                //000?0
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i + 4], i + 4) == NO_FORBIDDEN) {
                    fourCount++;
                }
            }

            bool isThree = false;

            if ((connectEmpty[i] > 2 || connectEmpty[i] == 2 && jConnectBlack[i] == 0) && (connectEmpty[i + 4] > 1 ||
                                                                                           connectEmpty[i + 4] == 1 && jConnectBlack[i + 4] == 0)) {
                //??000??? ??000??x x?000??? x?000??x
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i], i) == NO_FORBIDDEN) isThree = true;
            }

            if ((connectEmpty[i + 4] > 2 || connectEmpty[i + 4] == 2 && jConnectBlack[i + 4] == 0) && (connectEmpty[i] >
                                                                                                       1 || connectEmpty[i] == 1 && jConnectBlack[i] == 0)) {
                //???000?? x??000??  ???000?x x??000?x
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i + 4], i + 4) == NO_FORBIDDEN)
                    isThree = true;
            }
            if (isThree) {
                threeCount++;
            }
        } else if (connectBlack[i] + connectBlack[i + 4] == 1) {
            if (connectEmpty[i] == 1 && jConnectBlack[i] == 2) {
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i], i) == NO_FORBIDDEN) {
                    fourCount++;
                }
            }
            if (connectEmpty[i + 4] == 1 && jConnectBlack[i + 4] == 2) {
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i + 4], i + 4) == NO_FORBIDDEN) {
                    fourCount++;
                }
            }
            if (connectEmpty[i] == 1 && jConnectBlack[i] == 1 && (jConnectEmpty[i] > 1 || jConnectEmpty[i] == 1 &&
                                                                  djConnectBlack[i] == 0) && (connectEmpty[i + 4] > 1 || connectEmpty[i + 4] == 1 && jConnectBlack[i + 4]
                                                                                              == 0)) {
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i], i) == NO_FORBIDDEN) {
                    threeCount++;
                }
            }
            if (connectEmpty[i + 4] == 1 && jConnectBlack[i + 4] == 1 && (jConnectEmpty[i + 4] > 1 || jConnectEmpty[i +
                                                                          4] == 1 && djConnectBlack[i + 4] == 0) && (connectEmpty[i] > 1 || connectEmpty[i] == 1 && jConnectBlack[
                                                                                                                     i] == 0)) {
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i + 4], i + 4) == NO_FORBIDDEN) {
                    threeCount++;
                }
            }
        } else if (connectBlack[i] + connectBlack[i + 4] == 0) {
            if (connectEmpty[i] == 1 && jConnectBlack[i] == 3) {
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i], i) == NO_FORBIDDEN) {
                    fourCount++;
                }
            }
            if (connectEmpty[i + 4] == 1 && jConnectBlack[i + 4] == 3) {
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i + 4], i + 4) == NO_FORBIDDEN) {
                    fourCount++;
                }
            }

            if (connectEmpty[i] == 1 && jConnectBlack[i] == 2 && (jConnectEmpty[i] > 1 || jConnectEmpty[i] == 1 &&
                                                                  djConnectBlack[i] == 0) && (connectEmpty[i + 4] > 1 || connectEmpty[i + 4] == 1 && jConnectBlack[i + 4]
                                                                                              == 0)) {
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i], i) == NO_FORBIDDEN) {
                    threeCount++;
                }
            }
            if (connectEmpty[i + 4] == 1 && jConnectBlack[i + 4] == 2 && (jConnectEmpty[i + 4] > 1 || jConnectEmpty[i +
                                                                          4] == 1 && djConnectBlack[i + 4] == 0) && (connectEmpty[i] > 1 || connectEmpty[i] == 1 && jConnectBlack[
                                                                                                                     i] == 0)) {
                if (key_point_forbidden_check(checkerboard, x, y, connectBlack[i], i) == NO_FORBIDDEN) {
                    threeCount++;
                }
            }
        }
    }
    //std::cout << "3 : " << threeCount << "\t\t\t4 : " << fourCount << '\n';
    //std::cout << "_____________________forbidden_check_(" << x << "," << y << ")_end______________________\n";
    if (fourCount > 1) return FOUR_FOUR_FORBIDDEN;
    if (threeCount > 1) return THREE_THREE_FORBIDDEN;
    return NO_FORBIDDEN;
}

template <typename T>
Forbidden wuzi_chess<T>::key_point_forbidden_check(T** checkerboard, int x, int y, int connectBlack, int direction) {
    int i, j;
    connectBlack++;
    if (direction >= 4) connectBlack = -connectBlack;
    switch (direction % 4) {
    case 0: i = x - connectBlack;
        j = y;
        break;
    case 1: i = x - connectBlack;
        j = y + connectBlack;
        break;
    case 2: i = x;
        j = y + connectBlack;
        break;
    default: i = x + connectBlack;
        j = y + connectBlack;
        break;
    }
    //if (this->checkArray[i][j] != UNKNOWN) return this->checkArray[i][j];
    //std::cout << "direction : " << direction << " " << connectBlack << '\n';
    for (int m = 0; m < 15; ++m) {
        for (int n = 0; n < 15; ++n) {
            std::cout << checkerboard[m][n] << " ";
        }
        std::cout << std::endl;
    }
    checkerboard[x][y] = BLACK;
    checkerboard[i][j] = BLACK;

    const Forbidden result = forbidden_check(checkerboard, i, j);
    //this->checkArray[i][j] = result;
//    std::cout << "result : " << result << '\n';
//    std::cout << "__________________end___________________\n";
    checkerboard[x][y] = NONE;
    checkerboard[i][j] = NONE;
    return result;
}

template <typename T>
void wuzi_chess<T>::reset_checkArray() const {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            checkArray[i][j] = UNKNOWN;
        }
    }
}

#endif // WUZI_CHESS_HPP
