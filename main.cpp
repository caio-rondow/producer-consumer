#include "limBuffer.h"
#define MAX_VALUE 10 // produz valores de 0 a 99

void consume(LimBuffer &buffer){ buffer.consumir(); }

void produce(LimBuffer &buffer){ buffer.produzir(1); }

bool solve(LimBuffer &buffer, vector<thread>&threads, char t){
    
    bool is_task=true;

    if(t=='p'){ // produz

        thread t(produce, ref(buffer));
        threads.push_back(move(t));
        buffer.into_map(t.get_id());

    } else if(t=='c'){ // consome
        
        thread t(consume, ref(buffer));
        threads.push_back(move(t));
        buffer.into_map(t.get_id());

    } else is_task=false; // finaliza

    return is_task;
}

int main(int argc, char **argv){

    // valores aleatórios
    srand(time(0));

    int n;          // capacidade do buffer
    bool ans=true;  // tarefa (p, c ou .) -> se taks == '.' finalize...

    // lê capacidade do buffer
    cin>>n;

    // inicializa buffer de tamanho n...
    LimBuffer buffer(n);

    // vetor de threads
    vector<thread> threads; 

    while(ans){
        // tarefa a ser feita (produzir/consumir)
        char task;
        cin>>task;

        // Disparando as threads
        ans=solve(buffer, threads, task);
    }

    // Sincronizando threads
    for(auto &t:threads) t.join();

    return 0;
}
