#include "queue_t.h"
#include <thread>
#include <iostream>
#include <unistd.h>


void producer(queue_t &q) {
    srand(time(NULL));
    char element;
    while(true) {
        element = rand() % 25 + 65;
        q.push(element);
        sleep(rand() %1);
    }
}
void consumer(queue_t &q) {
    srand(time(NULL));
    while(true) {
        q.pop();
        sleep(rand()%1);
    }
}

void reader1(queue_t &q) {
    srand(time(NULL));
    while(true) {
        q.read_element1();
        sleep(rand() %3);
    }
}

void reader2(queue_t &q) {
    srand(time(NULL));
    while(true) {
        q.read_element2();
        sleep(rand() % 1);
    }
}

int main() {
    queue_t q;
    std::thread Reader1(reader1, std::ref(q));
    std::thread Reader2(reader2,  std::ref(q));
    std::thread Producer(producer,  std::ref(q));
    std::thread Consumer(consumer, std::ref(q));
  
   Reader1.join();
   Reader2.join();
   Producer.join();
   Consumer.join();
    return 0;
}
