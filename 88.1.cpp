#include <iostream>
#include <future>
#include <thread>

// Función que realiza una operación y establece el resultado en un promise
void compute_sum(int a, int b, std::promise<int>&& pr) {
    int result = a + b;
    pr.set_value(result); // Establece el resultado en el promise
}

int main() {
    std::promise<int> pr; // Crea un promise
    std::future<int> fut = pr.get_future(); // Obtiene un future asociado al promise

    // Crea un hilo que ejecuta compute_sum pasando 5 y 3 como argumentos
    std::thread th(compute_sum, 5, 3, std::move(pr));

    // Espera a que el resultado esté disponible y lo recupera
    int result = fut.get();
    std::cout << "El resultado es: " << result << std::endl; // Imprime el resultado

    th.join(); // Espera a que el hilo termine
    return 0;
}