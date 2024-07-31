#include "holidaychecker.h"
#include "halfiles.h"
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QString>

HolidayChecker::HolidayChecker(QObject *parent)
    : QObject{parent} {
    loadHolidays();
}

QString HolidayChecker::holiday() {
    QDate today = QDate::currentDate();

    if(holidayCheck(today)) {
        return "Praz.";
    }

    return "";
}

bool HolidayChecker::holidayCheck(QDate date) {
    if(m_holidays.contains(date.toString("dd.MM")))
        return true;
    return false;
}

bool HolidayChecker::checkString(QString date) {
    if(m_holidays.contains(date)) {
        return true;
    }
    return false;
}

void HolidayChecker::loadHolidays() {
    HalFiles hf;

    QString filePath = hf.getHolidaysFilePath();

    if(!QFile::exists(filePath)) {
        qDebug() << "file doesnt exist";
        return;
    }

    QFile file(filePath);

    m_holidays.clear();

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while(!file.atEnd()) {
            QString line     = QString(file.readLine()).replace("\n", "");
            m_holidays[line] = true;
        }
    }
}
