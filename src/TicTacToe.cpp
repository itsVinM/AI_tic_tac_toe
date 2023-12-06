#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <vector>

char game_state(const std::vector<std::vector<char>>& game) {
    const std::vector<std::pair<int, int>> directions{{1, 0}, {0, 1}, {1, 1}, {1, -1}};

    for (const auto& dir : directions) {
        int countX = 0, countO = 0;
        for (int i = 0; i < 3; ++i) {
            int row = i * dir.first;
            int col = i * dir.second;

            if (row >= 0 && row < 3 && col >= 0 && col < 3) {
                if (game[row][col] == 'X') {
                    ++countX;
                } else if (game[row][col] == 'O') {
                    ++countO;
                }
            }
        }
        if (countX == 3) {
            return 'X';
        } else if (countO == 3) {
            return 'O';
        }
    }

    int countEmpty = 0;
    for (const auto& row : game) {
        for (char cell : row) {
            if (cell == ' ') {
                ++countEmpty;
            }
        }
    }
    if (countEmpty == 0) {
        return 't';
    }

    return 'a';
}

void ask_for_move(std::vector<std::vector<char>>& game, char mark) {
    std::string str;
    int row, col;
    do {
        std::cout << "Place your mark (" << mark << ") in row:" << std::endl;
        std::cin >> str;
        row = stoi(str) - 1; // Adjust for 0-based indexing
        std::cout << "Place your mark (" << mark << ") in column:" << std::endl;
        std::cin >> str;
        col = stoi(str) - 1; // Adjust for 0-based indexing
    } while (game[row][col] != ' ');
    game[row][col] = mark;
}

void make_move(std::vector<std::vector<char>>& game, char mark) {
    // AI move logic
    int row, col;

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::default_random_engine generator(static_cast<unsigned>(seed));
    std::uniform_int_distribution<int> distribution(0, 2);

    do {
        row = distribution(generator);
        col = distribution(generator);
    } while (game[row][col] != ' ');

    game[row][col] = mark;
}

void print_game(const std::vector<std::vector<char>>& game) {
    std::cout << std::endl << std::endl;
    std::cout << "    1   2   3\n\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << i + 1 << "   ";
        for (int j = 0; j < 3; ++j) {
            std::cout << game[i][j];
            if (j < 2) {
                std::cout << " | ";
            }
        }
        std::cout << "\n";
        if (i < 2) {
            std::cout << "   ---+---+---\n";
        }
    }

    std::cout << std::endl << std::endl;
}

int main() {
    std::vector<std::vector<char>> game(3, std::vector<char>(3, ' '));
    char user_mark = 'X', ai_mark = 'O', turn = 'X';
    std::string str;

    std::cout << "Pick your mark (X goes first): " << std::endl;
    std::cin >> str;
    if (str[0] == 'O' || str[0] == 'o') {
        user_mark = 'O';
        ai_mark = 'X';
    }else{
    	user_mark = 'X';
        ai_mark = 'O';
    } 
    std::cout << "      User: " << user_mark << "     AI: " << ai_mark << "\n";

    print_game(game);

    while (game_state(game) == 'a') {
        std::cout << turn << "'s turn...\n";
        if (turn == user_mark)
            ask_for_move(game, user_mark);
        else
            make_move(game, ai_mark);
        print_game(game);
        turn = (turn == 'X') ? 'O' : 'X';
    }

    if (game_state(game) == 't')
        std::cout << "It's a tie.\n\n";
    else
        std::cout << game_state(game) << " is the winner.\n\n";

    std::cout << std::endl;
    return 0;
}

