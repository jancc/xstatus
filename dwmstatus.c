#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define STATUS_SIZE 512
#define BLOCK_SIZE 128
char status[STATUS_SIZE];
char blocks[2][BLOCK_SIZE];

void print() {
#ifdef DEBUG
    puts(status);
#else
    if(fork() == 0) execlp("xsetroot", "xsetroot", "-name", status, NULL);
#endif
}

void update_battery() {
    char buf_cur[32], buf_max[32], buf_status[1];
    int cur, max;
    FILE * fp;

    fp = fopen("/sys/class/power_supply/BAT1/charge_now", "r");
    fread(buf_cur, 32, 1, fp);
    fclose(fp);

    fp = fopen("/sys/class/power_supply/BAT1/charge_full", "r");
    fread(buf_max, 32, 1, fp);
    fclose(fp);

    fp = fopen("/sys/class/power_supply/BAT1/status", "r");
    fread(buf_status, 1, 1, fp);
    fclose(fp);

    cur = atoi(buf_cur);
    max = atoi(buf_max);

    sprintf(blocks[1], "%i%% %c", cur * 100 / max, buf_status[0]);
}

void update_time() {
    time_t t = time(NULL);
    struct tm * tm = localtime(&t);
    strftime(blocks[0], BLOCK_SIZE, "%F %H:%M", tm);
}

int main() {
    while(1) {
        update_time();
        update_battery();
        snprintf(status, STATUS_SIZE, "%s | %s", blocks[1], blocks[0]);
        print();
        sleep(60);
    }
}
