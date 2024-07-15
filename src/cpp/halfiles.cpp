#include <QDebug>

#include "halfiles.h"

HalFiles::HalFiles(QObject *parent)
    : QObject{parent} {
}

QString HalFiles::getEmployeesFilePath() const {
    return cPathData + cFnEmployees;
}

QString HalFiles::getHolidaysFilePath() const {
    return cPathData + cFnHolidays;
}

QString HalFiles::getSettingsFilePath() const {
    return cPathData + cFnSettings;
}

QString HalFiles::getEmployeeFolderPath() const {
    return cPathData + cLogFolder;
}

QString HalFiles::getEmployeeMonth(const QString &name, const QString &date) const {
    QString str("");
    QString tempName  = name;
    tempName          = tempName.replace(" ", "_");
    QStringList dlist = date.split(".");

    str = getEmployeeFolderPath() + tempName + "\\" + tempName + "_" + dlist[2] + "_" + dlist[1] +
          ".txt";

    qDebug() << "Employee log file" << str;
    return str;
}
