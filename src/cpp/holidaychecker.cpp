#include "holidaylogger.h"
#include "halfiles.h"
#include <QDebug>
#include <QFile>

HolidayLogger::HolidayLogger(QObject *parent)
    : QObject{parent} {
    loadHolidays();
}

bool HolidayLogger::holidayCheck(QString date) {
    if(m_holidays.contains(date.split(".")[0] + "." + date.split(".")[1]))
        return true;
    return false;
}

void HolidayLogger::loadHolidays() {
    HalFiles hf;

    QString filePath = hf.getHolidaysFilePath();

    QFile file(filePath);

    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            while(!file.atEnd()) {
                QString line     = QString(file.readLine()).replace("\n", "");
                m_holidays[line] = true;
            }
        }
    } else {
        qDebug() << filePath << "doesnt exist";
    }
}
