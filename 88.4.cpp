#include <future>
#include <iostream>
#include <thread>
#include <utility>

template<typename F>
auto async_deferred(F&& func) -> std::future<decltype(func())> {
    auto task = std::packaged_task<decltype(func())()>(std::forward<F>(func));
    auto future = task.get_future();
    std::thread(std::move(task)).detach();
    return future;
}

int main() {
    auto future = async_deferred([]() {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simula trabajo
        return 42;
    });

    std::cout << "El resultado es: " << future.get() << std::endl;

    return 0;
}