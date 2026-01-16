#include "common.h"
int produce_item();
void insert_item(int item);
int remove_item();
void consume_item(int item);

#define N 100
typedef int semaphore;
semaphore mutex = 1;    // 互斥量
semaphore empty = N;    // 空缓冲区数量
semaphore full = 0; // 满缓冲区数量

void producer() {
    int item;
    while (TRUE) {
        item = produce_item();
        down(&empty);
        down(&mutex);
        insert_item(item);
        up(&mutex);
        up(&full);
    }
}

void consumer() {
    int item;
    while (TRUE) {
        down(&full);
        down(&mutex);
        item = remove_item();
        up(&mutex);
        up(&empty);
        consume_item(item);
    }
}