#include "sickdaylogger.h"
#include "halfiles.h"
#include "holidaychecker.h"
#include "monthlogger.h"

#include <QDebug>
#include <QFile>

SickdayLogger::SickdayLogger(QObject *parent)
    : QObject{parent} {
}

void SickdayLogger::addSickdayEntry(QString Name, QDate start, QDate end, QString validity) {
    HolidayChecker hch;
    MonthLogger    monthlogger;
    for(QDate i = start; i <= end; i = i.addDays(1)) {
        if(i.dayOfWeek() != 6 && i.dayOfWeek() != 7 && !hch.holidayCheck(i)) {
            monthlogger.addEntry(Name, getDay(i), i.toString("dd.MM.yyyy"), "-", "-", "-", "-", "08:00", "-", validity);
        }
    }
}

QString SickdayLogger::getDay(QDate date) {
    int day = date.dayOfWeek();
    switch(day) {
    case 1:
        return "pon";
    case 2:
        return "uto";
    case 3:
        return "sri";
    case 4:
        return "čet";
    case 5:
        return "pet";
    case 6:
        return "sub";
    case 7:
        return "ned";
    }
    return "";
}
