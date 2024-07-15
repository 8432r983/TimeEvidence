#include "entry.h"
#include <QDebug>
#include <cmath>

Entry::Entry(QObject *parent)
    : QObject(parent)
    , day("-")
    , date("-")
    , clockIn("-")
    , clockOut("-")
    , total("-")
    , travel("-")
    , difference("-") {
}

void Entry::fromEntry(Entry *val) {
    if(!val)
        return;
    day        = val->day;
    date       = val->date;
    clockIn    = val->clockIn;
    clockOut   = val->clockOut;
    total      = val->total;
    travel     = val->travel;
    difference = val->difference;
}

int Entry::calcTotal() {
    return timeToInt(clockOut) - timeToInt(clockIn);
}

int Entry::calcDifference() {
    return timeToInt(total) - 8 * 60;
}

void Entry::setTotal() {
    total = intToTime(calcTotal());
}

void Entry::setDifference() {
    difference = intToTime(calcDifference());
}

int Entry::timeToInt(QString time) {
    if(time == "")
        return 0;
    int Hours   = time.split(":")[0].toInt();
    int Minutes = time.split(":")[1].toInt();
    return Hours * 60 + Minutes;
}

QString Entry::intToTime(int time) {
    int Hours   = floor(abs(time) / 60);
    int Minutes = abs(time) % 60;

    QString res = "";

    if(Hours < 10)
        res += "0" + QString::number(Hours);
    else
        res += QString::number(Hours);

    res += ":";
    if(Minutes < 10)
        res += "0" + QString::number(Minutes);
    else
        res += QString::number(Minutes);

    if(time < 0)
        res = "-" + res;

    return res;
}
