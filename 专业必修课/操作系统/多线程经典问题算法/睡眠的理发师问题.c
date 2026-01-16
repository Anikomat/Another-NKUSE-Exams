#include"common.h"
void cut_hair();
void get_haircut();

#define CHAIRS 5
typedef int semaphore;
semaphore customers = 0; // 在座位上等待剪发的顾客数
semaphore barbers = 0;    // 空闲的理发师数
semaphore mutex = 1;    // 互斥量
int waiting = 0;    // 当前等待的顾客数

void barber() {
    while (TRUE) {
        down(&customers);
        down(&mutex);
        waiting--;
        up(&barbers);    // 理发师空闲数+1
        up(&mutex);
        cut_hair();
    }
}

void customer() {
    down(&mutex);
    if (waiting < CHAIRS) {
        waiting++;
        up(&customers);
        up(&mutex);
        down(&barbers);
        get_haircut();
    } else {
        up(&mutex);
    }
}