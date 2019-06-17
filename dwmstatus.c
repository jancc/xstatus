#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "config.h"

const size_t blockc = sizeof(blockTypes) / sizeof(enum BlockType);

char status[STATUS_SIZE];
char status_tmp[STATUS_TMP_SIZE];

void print() {
#ifdef DEBUG
    puts(status);
#else
    if(fork() == 0) execlp("xsetroot", "xsetroot", "-name", status, NULL);
#endif
}

void update_tag(char * dst) {
    strncpy(dst, TAG, BLOCK_SIZE);
}

void update_battery(char * dst) {
    char buf_cur[32], buf_max[32], buf_status[1];
    int cur, max;
    FILE * fp;

    fp = fopen(BATTERY_NOW, "r");
    fread(buf_cur, 32, 1, fp);
    fclose(fp);

    fp = fopen(BATTERY_FULL, "r");
    fread(buf_max, 32, 1, fp);
    fclose(fp);

    fp = fopen(BATTERY_STATUS, "r");
    fread(buf_status, 1, 1, fp);
    fclose(fp);

    cur = atoi(buf_cur);
    max = atoi(buf_max);

    snprintf(dst, BLOCK_SIZE, "%i%% %c", cur * 100 / max, buf_status[0]);
}

void update_clock(char * dst) {
    time_t t = time(NULL);
    struct tm * tm = localtime(&t);
    strftime(dst, BLOCK_SIZE, CLOCK_FORMAT, tm);
}

void update() {
    char block[BLOCK_SIZE];
    status[0] = '\0';

    for(size_t i = 0; i < BLOCK_COUNT; i++) {
        switch(blockTypes[i]) {
        case B_TAG:
            update_tag(block);
            break;
        case B_CLOCK:
            update_clock(block);
            break;
        case B_BATTERY:
            update_battery(block);
            break;
        }

        if(i == 0) {
            strncpy(status, block, BLOCK_SIZE);
        } else {
            strncpy(status_tmp, status, STATUS_SIZE);
            snprintf(status, STATUS_SIZE, "%s | %s", status_tmp, block);
        }
    }
}

int main() {
    while(1) {
        update();
        print();
        sleep(INTERVAL);
    }
}
