#include <iostream>
#include <map>

using rational = std::pair<size_t, size_t>;

int main(int argc, const char * argv[]) {
    constexpr int limit = 1000000;
    rational a(2,5), b(3,7);
    size_t k{(limit - a.second)/b.second};

    a = std::make_pair(b.first * k + a.first, b.second * k + a.second);

    std::cout << a.first << std::endl;
    return 0;
}
