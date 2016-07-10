#include <iostream>
#include <vector>
#include <algorithm>

void disp(int x) {
  std::cout << x << std::endl;
}

struct mutate {
  int n;
  mutate() : n(0) { }
  void operator()(int& v) {
    v += n++;
  }
};

int main() {
  std::vector<int> v;

  v.push_back(3);
  v.push_back(1);
  v.push_back(4);

  // vの全ての要素にdisp()関数を適用する
  std::for_each(v.begin(), v.end(), disp);

  std::cout << "----" << std::endl;

  // 要素の内容を書き換えても構わないし、呼び出し順序に依存した処理を書いても構わない
  std::for_each(v.begin(), v.end(), mutate());
  std::for_each(v.begin(), v.end(), disp);
}
