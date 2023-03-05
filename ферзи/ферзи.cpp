#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <set>

void Output(std::vector<std::vector<bool>>& board, std::vector<std::string>& lines, bool last);

// Рекурсивная функция для решения бэк-трэкингом.
// board - доска, board[i][j] == true если стоит ферзь в [i][j], иначе false.
// lines - вспомогательный массив для сбора выводимых в консоль строк.
// N - количество ферзей, cnt - сколько ферзей уже удалось расставить


void Solve1(std::vector<std::vector<bool>>& board, std::vector<std::string>& lines,
    int N, int& num_sol, int cnt = 0, int depth = 0)
{
    if (cnt >= N)
    {
        //std::cout << num_sol << " ";
        ++num_sol;
        return;
    }
    // Обходим всю доску, начиная с позиции последнего ферзя.
    int i = cnt;
    for (int j = 0; j < board[i].size(); ++j)
    {
        bool attacked = false;
        // Цикл по k проверяет атакована ли позиция [i][j]
        for (int k = 0; k < board.size(); ++k)
            if (k != i)
                if (
                    // Есть ли атака по горизонтали
                    //k != j && board[i][k] ||
                    // Атака по вертикали
                    board[k][j] ||
                    // Атака по главной диагонали
                    0 <= j - i + k &&
                    j - i + k < board[i].size() && board[k][j - i + k] ||
                    // Атака по второстепенной диагонали
                    0 <= j + i - k &&
                    j + i - k < board[i].size() && board[k][j + i - k]
                    )
                {
                    attacked = true;
                    break;
                }
        if (attacked)
            continue;
        // Позиция [i][j] не под атакой, потому ставим ферзя
        board[i][j] = true;
        // Рекурисвный спуск для расстановки следующего ферзя
        Solve1(board, lines, N, num_sol, cnt+1, depth + 1);
        // Бэктрэкинг, удаляем прошлого установленного ферзя
        board[i][j] = false;
    }
    
}


void Solve2(std::vector<std::vector<bool>>& board, std::set<int>&visited,
    int N, int& num_sol, int cnt = 0, int depth = 0)
{
    if (cnt >= N)
    {
        ++num_sol;
        return;
    }
    // Обходим всю доску, начиная с позиции последнего ферзя.
    int i = cnt;
    for (int j = 0; j < board[i].size(); ++j)
    {
        bool attacked = false;
        if (visited.find(j) == visited.end())
        {
            // Цикл по k проверяет атакована ли позиция [i][j]
            for (int k = 0; k < board.size(); ++k)
                if (k != i)
                    if (
                        0 <= j - i + k &&
                        j - i + k < board[i].size() && board[k][j - i + k] ||
                        // Атака по второстепенной диагонали
                        0 <= j + i - k &&
                        j + i - k < board[i].size() && board[k][j + i - k]
                        )
                    {
                        attacked = true;
                        break;
                    }
        }
        else attacked = true;
        if (attacked)
            continue;
        // Позиция [i][j] не под атакой, потому ставим ферзя
        board[i][j] = true;
        visited.insert(j);
        // Рекурисвный спуск для расстановки следующего ферзя
        Solve2(board, visited, N, num_sol, cnt + 1, depth + 1);
        visited.erase(j);
        // Бэктрэкинг, удаляем прошлого установленного ферзя
        board[i][j] = false;
    }

}

void Solve3(std::vector<std::vector<bool>>& board, std::set<int>& not_visited,
    int N, int& num_sol, int cnt = 0, int depth = 0)
{
    if (cnt >= N)
    {
        ++num_sol;
        return;
    }
    // Обходим всю доску, начиная с позиции последнего ферзя.
    int i = cnt;
    for (auto j:not_visited)
    {
        bool attacked = false;
        // Цикл по k проверяет атакована ли позиция [i][j]
        for (int k = 0; k < board.size(); ++k)
            if (k != i)
                if (
                    0 <= j - i + k &&
                    j - i + k < board[i].size() && board[k][j - i + k] ||
                    // Атака по второстепенной диагонали
                    0 <= j + i - k &&
                    j + i - k < board[i].size() && board[k][j + i - k]
                    )
                {
                    attacked = true;
                    break;
                }
        if (attacked)
            continue;
        // Позиция [i][j] не под атакой, потому ставим ферзя
        board[i][j] = true;
        not_visited.erase(j);
        // Рекурисвный спуск для расстановки следующего ферзя
        Solve3(board, not_visited, N, num_sol, cnt + 1, depth + 1);
        not_visited.insert(j);
        // Бэктрэкинг, удаляем прошлого установленного ферзя
        try
        {
            board[i][j] = false;
        }
        catch (std::exception ex)
        {
            std::cout << ex.what();
        }
        std::cout << 123456;
    }

}

// Функция для вывода решений.
void Output(std::vector<std::vector<bool>>& board, std::vector<std::string>& lines, bool last) {
    // Вывод решения в консоль. Поставить тут if (0) если не нужно выводить доски в консоль.
    if (0) {
        if (!last) {
            // Добавление одной доски к текущим строкам.
            for (int i = 0; i < board.size(); ++i) {
                for (int j = 0; j < board[i].size(); ++j)
                    lines[i].push_back(board[i][j] ? 'Q' : '.');
                // Символ | в качестве разделителя между досок.
                lines[i] += "|";
            }
        }
        // Если длина строк превысила ширину консоли (70), то выводим строки и разделитель.
        if (lines.at(0).size() >= 70 || last && !lines.at(0).empty()) {
            for (int i = 0; i < lines.size(); ++i)
                std::cout << lines[i] << std::endl;
            for (int j = 0; j < lines.at(0).size(); ++j)
                std::cout << (lines.at(0)[j] == '|' ? '+' : '-');
            std::cout << std::endl;
            // Очищаем строки для следующих выводов досок.
            lines.clear();
            lines.resize(board.size());
        }
    }
}

int main() {
    int start = clock();
    // Входные параметры, rows - число рядов доски, cols - число столбцов
    // N - число ферзей которые нужно расставить
    const int size = 8;
    int const rows = size, cols = size, N = size;
    // Заполняем пустыми значениями доску размером [rows][cols]
    std::vector<std::vector<bool>> board(rows, std::vector<bool>(cols));
    std::vector<std::string> lines(rows);
    std::set<int> visited;
    visited = { 0, 1, 2, 3, 4, 5, 6, 7 };
    // Ответ, число решений
    int num_sol = 0;
    // Запускаем бэк-трэкинг поиск решений.
    std::cout << "-----------";
    Solve3(board, visited, N, num_sol);
    // Вывод ответа.
    int end = clock();
    std::cout << "Number of solutions: " << num_sol << std::endl;
    std::cout << ((double)end - start) / CLOCKS_PER_SEC;
}