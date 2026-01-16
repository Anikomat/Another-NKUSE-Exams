#include"common.h"
void think();
void eat();

#define N 5
typedef int semaphore;
typedef enum { THINKING, HUNGRY, EATING } State;    // 哲学家状态
State state[5];
semaphore mutex = 1;    // 互斥量
semaphore s[N]; // 每个哲学家的信号量（初始化为0）

int left(int i) {
    return (i + N - 1) % N;
}

int right(int i) {
    return (i + 1) % N;
}

void test(int i) {
    if (state[i] == HUNGRY &&
        state[left(i)] != EATING &&
        state[right(i)] != EATING) {
        state[i] = EATING;
        up(&s[i]);
    }
}

void take_forks(int i) {
    down(&mutex);
    state[i] = HUNGRY;
    test(i);    // 尝试获取2把叉子
    up(&mutex);
    down(&s[i]);    // 如果没获取到则阻塞在此
}

void put_forks(int i) {
    down(&mutex);
    state[i] = THINKING;
    test(left(i));  // 检查左右的哲学家能不能吃饭
    test(right(i)); // 如果能则唤醒他们
    up(&mutex);
}

void philosopher(int i) {
    while (TRUE) {
        think();
        take_forks(i);
        eat();
        put_forks(i);
    }
}