#include"common.h"
void read_database();
void use_data_read();

typedef int semaphore;
semaphore mutex = 1;    // 控制对rc的访问
semaphore db = 1;   // 控制对数据库的访问
int rc = 0; // 正在读或即将读的数目

void reader() {
    while (TRUE) {
        down(&mutex);
        rc++;
        if (rc == 1) {  // 如果是第一个读者
            down(&db);  // 锁定数据库
        }
        up(&mutex);
        read_database();
        down(&mutex);
        rc--;
        if (rc == 0) {  // 如果是最后一个读者
            up(&db);    // 释放数据库
        }
        up(&mutex);
        use_data_read();
    }
}

void writer() {
    while (TRUE) {
        think_up_data();
        down(&db);
        write_database();
        up(&db);
    }
}