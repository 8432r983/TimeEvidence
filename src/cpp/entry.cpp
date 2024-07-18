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
    , difference("-")
    , travel("-")
    , vacation("-")
    , holiday("-")
    , sickday("-")
    , daychanged(false) {
}

int Entry::calcTotal() {
    return timeToInt(clockOut) - timeToInt(clockIn) + timeToInt(travel) + timeToInt(vacation) +
           timeToInt(holiday) + timeToInt(sickday);
}

int Entry::calcDifference() {
    if(total == "-")
        return -8 * 60;
    return timeToInt(total) - 8 * 60;
}

void Entry::setTotal() {
    total = intToTime(calcTotal());
}

void Entry::setDifference() {
    difference = intToTime(calcDifference());
}

void Entry::reset() {
    day        = "-";
    date       = "-";
    clockIn    = "-";
    clockOut   = "-";
    total      = "-";
    difference = "-";
    travel     = "-";
    vacation   = "-";
    holiday    = "-";
    sickday    = "-";
    daychanged = false;
}

int Entry::timeToInt(QString time) {
    if(time == "" || time == "-")
        return 0;

    bool flag = time[0] == "-";

    int Hours   = time.replace("-", "").split(":")[0].toInt();
    int Minutes = time.replace("-", "").split(":")[1].toInt();

    int res = Hours * 60 + Minutes;

    if(flag)
        return -res;

    return res;
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
