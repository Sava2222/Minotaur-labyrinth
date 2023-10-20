#include <iostream>

#define N 10000

// Эта функция для получения данных о стенках и пустых клеток от лабиринта
char** get_field(int n) {
  char **f = new char* [n];
  for (int i = 0; i < n; i++) {
    f[i] = new char [n];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      std::cin >> f[i][j];
  }
  return f;
}

// Проверка на то, обошли ли мы весь лабиринт
bool field_done(char** f) {
  bool flag = true;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (f[i][j] == '_') { // это значит, что клетка без стены, но Минотавр там еще не был
        flag = false;
      }
    }
  }
  return flag;
}

char** query_1(char** f, int c_x, int c_y, int n_x, int n_y, int ans) {
  bool horizontal = false;
  if (ans == 1) { // То есть там нет стены
    if (c_x == n_x) {
      horizontal = false;
    } else {
      horizontal = true;
    }
    c_x = n_x;
    c_y = n_y;
    if (horizontal) {
      n_y++;
    } else {
      n_x++;
    }
    f[c_x][c_y] = '+';
  }
  return f;
}

std::pair<int, int> query_2_0(int n_x, int n_y) {
  n_x--;
  n_y++;
  std::pair<int, int> p = std::make_pair(n_x, n_y);
  return p;
}

std::pair<int, int> query_2_1(int n_x, int n_y) {
  n_x--;
  n_y--;
  std::pair<int, int> p = std::make_pair(n_x, n_y);
  return p;
}

int main() {
  int x, y, x_1, y_1;
  int a, b, c;
  int k;
  std::cin >> x >> y >> x_1 >> y_1 >> a >> b >> c >> k;
  char **field = new char* [N];
  for (int i = 0; i < N; i++) {
    field[i] = new char [N];
  }
  field = get_field(N);
  int cur_x = x;
  int cur_y = y;
  int next_x = x_1;
  int next_y = y_1;
  int time = 0;
  field[cur_x][cur_y] = '+'; // Минотавр здесь побывал
  bool done = field_done(field);
  while (!done) {
    std::cout << "1" << std::endl;
    int answer_1 = 2;
    std::cin >> answer_1;
    field = query_1(field, cur_x, cur_y, next_x, next_y, answer_1);
    time += a;

    std::cout << "2" << "0" << std::endl;
    int answer_2_0 = 1;
    std::cin >> answer_2_0;
    std::pair<int, int> pair_0 = query_2_0(next_x, next_y);
    next_x = pair_0.first;
    next_y = pair_0.second;
    time += b;

    std::cout << "2" << "1" << std::endl;
    int answer_2_1 = 1;
    std::cin >> answer_2_1;
    std::pair<int, int> pair_1 = query_2_0(next_x, next_y);
    next_x = pair_1.first;
    next_y = pair_1.second;
    time += b;

    std::cout << "3" << std::endl;
    char **part_field = new char* [2 * k + 1];
    for (int i = 0; i < 2 * k + 1; i++) {
      part_field[i] = new char [2 * k + 1];
    }
    part_field = get_field(2 * k + 1);
    time += c;
    done = field_done(field);
  }
  std::cout << "4" << time << std::endl;
}
