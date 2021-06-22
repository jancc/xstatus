#ifndef XSTATUS_H
#define XSTATUS_H

#define BLOCK_SIZE 256

enum BlockType { B_TAG, B_CLOCK, B_BATTERY, B_UPTIME };

void update_tag(char* dst);
void update_clock(char* dst);
void update_battery(char* dst);
void update_uptime(char* dst);

#endif
