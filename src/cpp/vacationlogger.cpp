#include "vacationlogger.h"
#include "halfiles.h"
#include "holidaychecker.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

VacationLogger::VacationLogger(QObject *parent)
    : QObject{parent} {
}

void VacationLogger::addVacation(QString Name, QDate startDate, QDate endDate) {

    HalFiles hf;
    QString  filePath = hf.getEmployeeVacationPath(Name);

    if(!QFile::exists(filePath)) {
        qDebug() << "file doesnt exist: " << filePath;
    }

    QFile file(filePath);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "cant open file: " + filePath;
    }

    QTextStream in(&file);
    if(file.size() == 0) {
        in << "Datum; "
           << "odobreno"
           << "\n";
    }

    QDate begin = startDate;
    QDate end   = endDate;

    bool           isSmaller = (begin < end);
    HolidayChecker hch;

    while(begin != end) {
        if(isSmaller)
            begin = begin.addDays(1);
        else
            begin = begin.addDays(-1);

        if(begin.dayOfWeek() != 6 && begin.dayOfWeek() != 7 && !hch.holidayCheck(begin)) {
            in << begin.toString("dd.MM.yyyy") + "; "
               << "-"
               << "\n";
        }
    }
}
