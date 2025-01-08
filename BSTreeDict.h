#include <iostream>  // Para std::ostream
#include <stdexcept> // Para std::runtime_error
#include <string>    // Para std::string
#include "BSTree.h"  // Para usar la clase BSTree
#include "TableEntry.h"
#include "Dict.h"

using namespace std;

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree; // El ABB que almacena las entradas del diccionario
    int entryCount;              // Número de entradas en el diccionario

public:
    // Constructor
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>(); // Crear un ABB vacío
        entryCount = 0;
    }

    // Destructor
    ~BSTreeDict() {
        delete tree; // Liberar la memoria del árbol
    }

    // Devuelve el número de entradas
    int entries() const override {
        return entryCount;
    }

    // Insertar una nueva entrada en el diccionario
    void insert(string key, V value) override {
        try {
            // Intentar buscar la clave, si existe, lanzar excepción
            search(key);
            throw runtime_error("La clave ya existe");
        } catch (const runtime_error&) {
            // Si no se encuentra, insertamos la nueva entrada
            TableEntry<V> entry(key, value);
            tree->insert(entry); // Usar el método de inserción del ABB
            entryCount++;        // Aumentar el contador de entradas
        }
    }

    // Eliminar una entrada usando la clave
    V remove(string key) override {
        try {
            // Crear una TableEntry para buscar la clave en el árbol
            TableEntry<V> entry(key);
            V value = tree->search(entry).value; // Buscar el valor asociado a la clave
        
            // Llamar a remove para eliminar la entrada en el árbol
            tree->remove(entry); // Eliminar el nodo del árbol

            entryCount--; // Decrementar el contador de entradas
            return value; // Retornar el valor eliminado
        } catch (...) {
            throw runtime_error("Elemento no encontrado");
        }
    }

    // Buscar una entrada usando la clave
    V search(string key) const override {
        try {
            TableEntry<V> entry(key, V());
            TableEntry<V> result = tree->search(entry); // Buscar la entrada en el árbol
            return result.value;                        // Retornar el valor de la entrada encontrada
        } catch (const runtime_error&) {
            throw runtime_error("Elemento no encontrado");
        }
    }

    // Sobrecarga del operador []
    V operator[](string key) const {
        return search(key); // Utilizar el método de búsqueda
    }

    // Sobrecarga del operador << para imprimir el diccionario
    friend ostream& operator<<(ostream &out, const BSTreeDict<V> &dict) {
        out << *dict.tree; // Imprimir el contenido del árbol (usando su operador <<)
        return out;
    }
};

