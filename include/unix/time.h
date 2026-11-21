#ifndef TIME_H
#define TIME_H

struct Time
{
    long seconds;
    long minutes;
    long hour;
    long weekday;
    long day;
    long month;
    long year;
};

extern struct Time Time;

void time_init();

#endif