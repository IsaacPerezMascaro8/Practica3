#ifndef DICT_H
#define DICT_H

#include <string>
#include <stdexcept>

using namespace std;

template <typename V>
class Dict {
public:
    // Inserta el par key->value en el diccionario.
    virtual void insert(string key, V value) = 0;

    // Busca el valor correspondiente a key. Devuelve el valor asociado si key está en el diccionario.
    virtual V search(string key) = 0;

    // Elimina el par key->value si se encuentra en el diccionario.
    virtual V remove(string key) = 0;

    // Devuelve el número de elementos que tiene el diccionario.
    virtual int entries() = 0;
};

#endif

