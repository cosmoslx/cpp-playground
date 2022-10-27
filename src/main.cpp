#include <iostream>
#include <functional>

using Notify = void(int, int);
using pNotify = void(*)(int, int);

void send_notification(Notify callback) {
    int x = 6, y = 7;
    callback(x, y);
}

void notification(int x, int y) {
    std::cout << "x*y: " << x*y << std::endl;
}

int main(void) {

    Notify* notify = [](int x, int y) {
        std::cout << "x+y: " << x+y << std::endl;
    };


    send_notification(notify);
    send_notification(notification);

    std::cout << "Hello, C++" << std::endl;

    return 0;
}
