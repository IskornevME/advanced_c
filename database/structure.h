#ifndef DATABASE_STRUCTURE_H_
#define DATABASE_STRUCTURE_H_

struct Time {
    int hour;
    int min;
};

enum Type {LECTURE, SEMINAR};

struct LessonInfo {
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

#endif  // DATABASE_STRUCTURE_H_
