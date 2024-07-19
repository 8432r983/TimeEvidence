#include <QDebug>
#include <QTextCodec>

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

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    tempName.replace("\u010d", "c");
    tempName.replace("\u0107", "c");
    tempName.replace("\u017e", "z");
    tempName.replace("\u0161", "s");
    tempName.replace("\u0111", "d");
    tempName.replace("\u010c", "C");
    tempName.replace("\u0106", "C");
    tempName.replace("\u017d", "Z");
    tempName.replace("\u0160", "S");
    tempName.replace("\u0110", "D");

    str = getEmployeeFolderPath() + tempName + "\\" + tempName + "_" + dlist[2] + "_" + dlist[1] + ".txt";

    // qDebug() << "Employee log file" << str;
    return str;
}
