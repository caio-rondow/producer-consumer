#ifndef LIM_BUFFER_H__
#define LIM_BUFFER_H__

#include <exception>
#include <iostream>
#include <unistd.h> 
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <map>
using namespace std;

class LimBuffer{

private:

    // Atributos
    int *buffer;
    int capacity;
    int size;
    int prod, cons;

    mutex mux;
    queue<thread::id> QC, QP; // queue consumidor, queue produtor...

    // métodos block/wakeup implementados no slide
    void block();
    void wakeup(thread::id t);

public:

    // Construtores/Destrutores
    LimBuffer(int capacity);
    LimBuffer();
    ~LimBuffer();

    // métodos
    void produzir(int data);
    int consumir();

    void into_map(thread::id id);
    void debug(bool is_produce);
};

#endif
