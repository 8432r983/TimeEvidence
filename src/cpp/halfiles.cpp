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

QString HalFiles::getEmployeeVacationPath(QString Name) const {
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QString newName = cleanString(Name);

    QString fileName = newName.replace(" ", "_") + "_" + "Godisnji.txt";
    return getEmployeeFolderPath() + newName.replace(" ", "_") + sep + fileName;
}

QString HalFiles::getEmployeeMonth(const QString &name, const QString &date) const {
    QString str("");
    QString tempName  = name;
    tempName          = tempName.replace(" ", "_");
    QStringList dlist = date.split(".");

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QString newtempName = cleanString(tempName);

    str = getEmployeeFolderPath() + newtempName + sep + newtempName + "_" + dlist[2] + "_" + dlist[1] + ".txt";
    qDebug() << "Employee log file" << str;
    return str;
}

QString HalFiles::cleanString(QString str) const {
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    str.replace("\u010D", "c");
    str.replace("\u0107", "c");
    str.replace("\u017e", "z");
    str.replace("\u0161", "s");
    str.replace("\u0111", "d");

    str.replace("\u010c", "C");
    str.replace("\u0106", "C");
    str.replace("\u017d", "Z");
    str.replace("\u0160", "S");
    str.replace("\u0110", "D");

    str.replace("ć", "c");
    str.replace("č", "c");
    str.replace("ž", "z");
    str.replace("š", "s");
    str.replace("Đ", "d");

    str.replace("Ć", "C");
    str.replace("Č", "C");
    str.replace("Z", "Z");
    str.replace("Š", "S");
    str.replace("Đ", "D");
    return str;
}
