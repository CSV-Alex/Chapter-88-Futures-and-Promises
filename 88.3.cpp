#include <iostream>
#include <thread>
#include <future>
#include <functional>
#include <exception>

template<typename F>
auto async_deferred(F&& func) -> std::future<decltype(func())>
{
    using result_type = decltype(func());
    auto promise = std::promise<result_type>();
    auto future = promise.get_future();
    std::thread(std::bind([=](std::promise<result_type>& promise)
    {
        try
        {
            promise.set_value(func());
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    }, std::move(promise))).detach();
    return future;
}

int main() {
    auto future = async_deferred([]() -> int {
        std::this_thread::sleep_for(std::chrono::seconds(2)); //espera
        return 42; //resultado
    });

    std::cout << "Doing other work..." << std::endl;

    std::cout << "The answer is " << future.get() << std::endl;

    return 0;
}