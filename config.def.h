// watermark your desktop here
#define TAG "dwm rulez"
// update interval (in seconds)
#define INTERVAL 60
// maximum length of an individual block
#define BLOCK_SIZE 128

// format of the clock string
#define CLOCK_FORMAT "%F %H:%M"

#define BATTERY_NOW    "/sys/class/power_supply/BAT1/charge_now"
#define BATTERY_FULL   "/sys/class/power_supply/BAT1/charge_full"
#define BATTERY_STATUS "/sys/class/power_supply/BAT1/status"

enum BlockType {B_TAG, B_CLOCK, B_BATTERY};

// amount of different blocks
#define BLOCK_COUNT 2
enum BlockType blockTypes[] = {
    B_TAG,
    B_CLOCK
};

#define STATUS_SIZE (BLOCK_COUNT + 1) * BLOCK_SIZE
#define STATUS_TMP_SIZE (BLOCK_COUNT - 1) * BLOCK_SIZE
