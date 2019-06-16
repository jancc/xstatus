#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define STATUS_SIZE 256
char status[STATUS_SIZE];

void print() {
#ifdef DEBUG
    puts(status);
#else
    if(fork() == 0) execlp("xsetroot", "xsetroot", "-name", status, NULL);
#endif
}

void update() {
    time_t t = time(NULL);
    struct tm * tm = localtime(&t);
    strftime(status, STATUS_SIZE, "%F %H:%M", tm);
}

int main() {
    while(1) {
        update();
        print();
        sleep(60);
    }
}
