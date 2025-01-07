#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

using namespace std;

template <typename V>

class TableEntry {

public:
   
    string key;
    V value;

    
    TableEntry(string key, V value) : key(key), value(value) {} //Constructor con key y value
    TableEntry(string key) : key(key), value() {} //Constructor con key pero sin value
    TableEntry() : key(""), value() {} //Cadena vacía y sin valor

    // Determinar que dos instancias de TableEntry son iguales (solo si comparten la misma clave)
    friend bool operator==(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        return te1.key == te2.key;
    }

    // Determinar que dos instancias de TableEntry son diferentes (solo si sus claves son distintas)
    friend bool operator!=(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        return !(te1 == te2);
    }

    // Imprimir el contenido de la entrada
    friend ostream& operator<<(ostream& out, const TableEntry<V>& te) {
        out << "{" << te.key << " -> " << te.value << "}";
        return out;
    }
};

#endif

