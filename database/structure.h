#ifndef STRUCTURE_H
#define STRUCTURE_H


struct Time {
    int hour;
    int min;
};

enum Type {LECTURE, SEMINAR};

struct Structure {
    int week_day;
    struct Time start_time;
    enum Type type;
    int duration;
    char *name;
    char *teacher;
    int auditorium;
    int course;
    int group;
};


#endif // STRUCTURE_H 