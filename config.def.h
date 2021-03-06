/* watermark your desktop here */
static const char* tag = "x still rulez";
/* update interval (in seconds) */
static const unsigned interval = 1;

/* format of the clock strings (cycled through with every step) */
static const char* clock_fmt[] = {
    "%F %H:%M",
    "%F %H %M",
};

/* battery files */
static const char* battery_now = "/sys/class/power_supply/BAT1/charge_now";
static const char* battery_full = "/sys/class/power_supply/BAT1/charge_full";
static const char* battery_status = "/sys/class/power_supply/BAT1/status";

/* uptime file */
static const char* uptime_fname = "/proc/uptime";

/* amount of different blocks */
enum BlockType blockTypes[] = {
    B_BATTERY,
    B_UPTIME,
    B_CLOCK,
};
