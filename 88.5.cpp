#include <future> // Necesario para std::promise

enum class future_errc {
    broken_promise = 1, // la tarea ya no está compartida
    future_already_retrieved = 2, // la respuesta ya fue recuperada
    promise_already_satisfied = 3, // la respuesta ya fue almacenada
    no_state = 4 // acceso a una promesa en estado no compartido
};

// Función para demostrar una promesa inactiva
int test_inactive_promise()
{
    std::promise<int> pr; // Crea una promesa de tipo int
    return 0; // retorna ok indicando que la función se ejecutó correctamente
}

// Función para demostrar el uso de una promesa activa (aunque aquí no se utiliza)
int test_active_promise()
{
    std::promise<int> pr; // Crea otra promesa de tipo int
    // Aquí se debería hacer algo con la promesa, como establecer un valor o una excepción.
    return 0; // retorna ok
}