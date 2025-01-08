#include <iostream>
#include <string>
#include <stdexcept>
#include "Dict.h"
#include "ListLinked.h"
#include "TableEntry.h"

using namespace std;

template <typename V>
class HashTable : public Dict<V> {
private:
    int n; // Número de elementos almacenados
    int max; // Tamaño total de la tabla (número de cubetas)
    ListLinked<TableEntry<V>>* table; // Array de punteros a listas enlazadas

    // Función hash para calcular la posición en la tabla
    int h(string key) const {
        int sum = 0;
        for (char c : key)
            sum += static_cast<int>(c);
        return sum % max;
    }

public:
    // Constructor
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Inserción de un par clave->valor
    void insert(string key, V value) override {
        int index = h(key);
        TableEntry<V> entry(key, value);

        // Verificar si la clave ya existe
        if (table[index].search(TableEntry<V>(key)) != -1)
            throw runtime_error("La clave ya existe en el diccionario.");

        table[index].prepend(entry);
        n++;
    }

    // Búsqueda de un valor por su clave
    V search(string key) override {
        int index = h(key);
        int pos = table[index].search(TableEntry<V>(key));
        if (pos == -1)
            throw runtime_error("Clave no encontrada.");

        return table[index].get(pos).value;
    }

    // Eliminación de un par clave->valor
    V remove(string key) override {
        int index = h(key);
        int pos = table[index].search(TableEntry<V>(key));
        if (pos == -1)
            throw runtime_error("Clave no encontrada.");

        TableEntry<V> entry = table[index].get(pos);
        table[index].remove(pos);
        n--;
        return entry.value;
    }

    // Número de elementos en la tabla
    int entries() override {
        return n;
    }

    // Capacidad total de la tabla (número de cubetas)
    int capacity() const {
        return max;
    }

    // Sobrecarga del operador []
    V operator[](string key) {
        return search(key);
    }

    // Sobrecarga del operador << para imprimir la tabla
    friend ostream& operator<<(ostream& out, const HashTable<V>& ht) {
        for (int i = 0; i < ht.max; ++i) {
            out << "Cubeta " << i << ": " << ht.table[i] << "\n";
        }
        return out;
    }
};

