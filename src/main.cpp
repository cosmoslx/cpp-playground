#include <iostream>
#include <functional>
#include <tuple>
#include <array>
#include <coroutine>


// ======== basic ========= 

using Notify = void(int, int);
using pNotify = void (*)(int, int);

void send_notification(Notify callback)
{
    int x = 6, y = 7;
    callback(x, y);
}

void notification(int x, int y)
{
    std::cout << "x*y: " << x * y << std::endl;
}

constexpr int fibonacci(const int n)
{
    return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

int usage_notification(void)
{

    Notify *notify = [](int x, int y)
    {
        std::cout << "x+y: " << x + y << std::endl;
    };

    send_notification(notify);
    send_notification(notification);

    std::cout << "Hello, C++" << std::endl;
    std::cout << "fibonacci(10): " << fibonacci(10) << std::endl;

    auto [x, y, z] = std::make_tuple(1, 2.3, "456");
    std::cout << "x=" << x << ", y=" << y << ", z=" << z << std::endl;

    auto arr = std::array<int, 5>{1, 2, 3, 4, 5};
    std::cout << "arr:" << std::endl;
    for (auto &a : arr)
    {
        std::cout << a << std::endl;
    }

    return 0;
}

// ======= hello coroutine =======

/// @brief coroutine return object
struct Task
{
    struct promise_type
    {
        int current_value;

        Task get_return_object()
        {
            //return Task(std::coroutine_handle<promise_type>::from_promise(*this));
            return Task{this};
        }

        std::suspend_never initial_suspend() { return {}; }

        std::suspend_always final_suspend() noexcept { return {}; }
        
        std::suspend_always yield_value(int value)
        {
            current_value = value;
            return {};
        }

        // void return_void() {}
        void return_value(int value) { current_value = value; }

        void unhandled_exception() { std::exit(1); }
    };


    //Task(std::coroutine_handle<promise_type> h) : handle(h) {}
    Task(promise_type *promise) : handle(std::coroutine_handle<promise_type>::from_promise(*promise)) {}
    ~Task() { if (handle) handle.destroy(); }

    int get_value() { return handle.promise().current_value; }

    void resume() { handle.resume(); }

    bool is_done() { return handle.done(); }

    std::coroutine_handle<promise_type> handle;
};

/// @brief coroutine function, function using Task as a return type became a coroutine
/// @return coroutine return object
Task coroutineFunction() {
    co_yield 1;
    co_yield 2;
    co_yield 3;
    co_return -1;
}

void usage_hello_coroutine() {
    Task co_ret = coroutineFunction();
    while(!co_ret.is_done()) {
        std::cout << co_ret.get_value() << std::endl;
        co_ret.resume();
    }
    std::cout << "final: " << co_ret.get_value() << std::endl;
}

// ========== main ===========

int main()
{
    std::cout << "=== main begin ===" << std::endl;

    // usage_notification();
    usage_hello_coroutine();

    std::cout << "=== main end ===" << std::endl;
    return 0;
}
