#include <iostream>
#include <functional>
#include <tuple>
#include <array>

using Notify = void(int, int);
using pNotify = void(*)(int, int);

void send_notification(Notify callback) {
    int x = 6, y = 7;
    callback(x, y);
}

void notification(int x, int y) {
    std::cout << "x*y: " << x*y << std::endl;
}

constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
}

int main(void) {

    Notify* notify = [](int x, int y) {
        std::cout << "x+y: " << x+y << std::endl;
    };


    send_notification(notify);
    send_notification(notification);

    std::cout << "Hello, C++" << std::endl;
    std::cout << "fibonacci(10): " << fibonacci(10) << std::endl;

    auto [x, y, z] = std::make_tuple(1, 2.3, "456");
    std::cout << "x=" << x << ", y=" << y << ", z=" << z << std::endl;

    auto arr = std::array<int, 5>{1, 2, 3, 4, 5};
    std::cout << "arr:" << std::endl;
    for (auto& a : arr) {
        std::cout << a << std::endl;
    }


    return 0;
}
