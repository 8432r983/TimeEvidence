#include "holidaychecker.h"
#include "halfiles.h"
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QString>

HolidayChecker::HolidayChecker(QObject *parent)
    : QObject{parent} {
    loadHolidays();
}

QString HolidayChecker::holiday() {
    QDateTime curr     = QDateTime::currentDateTime();
    QString   formated = curr.toString("dd.MM");

    if(holidayCheck(formated)) {
        return "Praz.";
    }

    return "";
}

bool HolidayChecker::holidayCheck(QString date) {
    if(m_holidays.contains(date))
        return true;
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

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while(!file.atEnd()) {
            QString line     = QString(file.readLine()).replace("\n", "");
            m_holidays[line] = true;
        }
    }
}
