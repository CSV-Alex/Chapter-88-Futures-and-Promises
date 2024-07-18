#include <iostream>
#include <future>
#include <thread>

int main() {
    // Crea un promise de tipo std::string
    auto promise = std::promise<std::string>();

    // Crea un hilo productor que establecerá el valor del promise
    auto producer = std::thread([&] {
        promise.set_value("Hello World"); // Establece el valor del promise
    });

    // Obtiene un future asociado al promise
    auto future = promise.get_future();

    // Crea un hilo consumidor que esperará y consumirá el valor del future
    auto consumer = std::thread([&] {
        std::cout << future.get(); // Espera y obtiene el valor del future, luego lo imprime
    });

    // Espera a que el hilo productor termine
    producer.join();
    // Espera a que el hilo consumidor termine
    consumer.join();

    return 0;
}