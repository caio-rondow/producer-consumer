#include "limBuffer.h"

mutex block_wakeup_mux;
std::map<thread::id,int> A;

LimBuffer::LimBuffer(int _capacity): capacity(_capacity), size(0), prod(0), cons(0){
    
    // Aloca buffer de tamanho capacity
    buffer = new int[capacity];
    for(int i=0; i<capacity; i++) buffer[i]=-1;
}

// Desaloca buffer
LimBuffer::~LimBuffer(){ delete[] buffer; }

/* BLOCK/WAKEUP DOS SLIDES DE AULA */
void LimBuffer::block(){
    bool sair=false;
    thread::id eu=this_thread::get_id();
    do {
        block_wakeup_mux.lock();
        if(A[eu] > 0) {
            A[eu]--;
            sair=true;
        }
        block_wakeup_mux.unlock();
    } while (!sair);
}

void LimBuffer::wakeup(thread::id t){
    block_wakeup_mux.lock();
    A[t]++;
    block_wakeup_mux.unlock();
}

void LimBuffer::produzir(int data){
    
    bool blk;

    do{
        blk=false;

        // INICIO REGIÃO CRÍTICA
        mux.lock();

        // Se o buffer está cheio...
        if(size==capacity){
            blk=true;                       // marcar para thread esperar
            q.push(this_thread::get_id());  // colocar na fila de espera

        } else{

            // Adiciona dado no buffer
            buffer[prod]=data;
            prod=(prod+1)%capacity;
            size++;

            // acorda thread
            if(!q.empty()){ 
                thread::id id=q.front(); q.pop();
                wakeup(id);
            }

            // Imprime estado do buffer
            debug();
        }

        // FINAL REGIÃO CRÍTICA
        mux.unlock();

        if(blk) block(); // colocando 'this' thread para esperar
    } while(blk);
}

int LimBuffer::consumir(){

    bool blk;
    int ans;
    
    do{
        blk=false;

        // INICIO REGIÃO CRÍTICA
        mux.lock();

        // Se o buffer está vazio...
        if(size==NULL){
            blk=true;                       // marcar para thread esperar
            q.push(this_thread::get_id());  // colocar na fila de espera

        } else{

            // Tira dado do buffer
            ans=buffer[cons];
            buffer[cons]=-1;
            cons=(cons+1)%capacity;
            size--;

            // acorda thread
            if(!q.empty()){
                thread::id id=q.front(); q.pop();
                wakeup(id);
            }

            // Imprime estado do buffer
            debug();
        }

        // FINAL REGIÃO CRÍTICA
        mux.unlock();

        if(blk) block(); // colocando 'this' thread para esperar
    } while(blk);

    return ans;
}

void LimBuffer::into_map(thread::id id){ A.insert(make_pair(id,0)); }

void LimBuffer::debug(){
    cout << "Buffer: [ ";
    for(int i=0; i<capacity; i++) cout << buffer[i] << " ";
    cout << "]\n";
}