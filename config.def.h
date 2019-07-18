// watermark your desktop here
static const char * tag = "dwm rulez";
// update interval (in seconds)
static const unsigned interval = 60;
// maximum length of an individual block
#define BLOCK_SIZE 128

// format of the clock string
static const char * clock_fmt = "%F %H:%M";

// battery files
static const char * battery_now = "/sys/class/power_supply/BAT1/charge_now";
static const char * battery_full = "/sys/class/power_supply/BAT1/charge_full";
static const char * battery_status = "/sys/class/power_supply/BAT1/status";

// uptime file
static const char * uptime_fname = "/proc/uptime";

// amount of different blocks
enum BlockType blockTypes[] = {
    B_BATTERY,
    B_UPTIME,
    B_CLOCK,
};
