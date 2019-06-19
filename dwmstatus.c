#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <X11/Xlib.h>

#include "config.h"

static char status[STATUS_SIZE];
static char status_tmp[STATUS_TMP_SIZE];

static Display * dpy;
static int screen;
static Window root;

void print() {
#ifdef DEBUG
    puts(status);
#else
    XStoreName(dpy, root, status);
    XFlush(dpy);
#endif
}

void error(const char * err) {
    fputs(err, stderr);
    exit(EXIT_FAILURE);
}

void update_tag(char * dst) {
    strncpy(dst, TAG, BLOCK_SIZE);
}

void update_battery(char * dst) {
    char buf_cur[32], buf_max[32], buf_status[1];
    int cur, max;
    FILE * fp;

    if((fp = fopen(BATTERY_NOW, "r")) == NULL) 
        error("failed to read current battery state");
    fread(buf_cur, 32, 1, fp);
    fclose(fp);

    if((fp = fopen(BATTERY_FULL, "r")) == NULL)
        error("failed to read max battery state");
    fread(buf_max, 32, 1, fp);
    fclose(fp);

    if((fp = fopen(BATTERY_STATUS, "r")) == NULL)
        error("failed to read battery status");
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

void print_version() {
    printf("dwmstatus %s\n", VERSION);
    puts("  simple status bar helper for dwm");
    puts("  (c) 2019 Jan Wolff");
    exit(EXIT_SUCCESS);
}

int main(int argc, char * argv[]) {
    for(int i = 0; i < argc; i++) {
        if(strcmp(argv[i], "-v") == 0) print_version();
        else if(strcmp(argv[i], "--version") == 0) print_version();
    }

    if((dpy = XOpenDisplay(NULL)) == NULL)
        error("failed to open X display");
    screen = DefaultScreen(dpy);
    root = RootWindow(dpy, screen);

    while(1) {
        update();
        print();
        sleep(INTERVAL);
    }
}
