#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QString>
#include <QTextStream>

#include "hoursmanager.h"

HoursManager::HoursManager(QObject *parent)
    : QObject{parent} {
    setEmployeeFolder();
}

void HoursManager::addEntry(QString day, QString date, QString clockIn,
                            QString clockOut) {
    QString fileName = getFileName(date);
    QFile   file(mainFilePath + fileName + ".txt");

    if(file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        QTextStream in(&file);
        in << day + "; " << date.split(".")[0] + "; " << clockIn + "; "
           << clockOut << '\n';
    }
}

void HoursManager::setMainPath(QString EmployeeName) {
    QString first_name = EmployeeName.split(" ")[0];
    QString last_name  = EmployeeName.split(" ")[1];

    mainFilePath = employeeFolder + first_name + "_" + last_name + "\\";
}

QString HoursManager::getFileName(QString date) {
    QString Year  = date.split(".")[2];
    QString Month = date.split(".")[1];

    return Year + "_" + Month;
}

QString HoursManager::employeeName() const {
    return m_employeeName;
}

void HoursManager::setEmployeeFolder() {
    QString filePath =
        "C:\\Users\\Adrian\\Documents\\Praksa\\TimeEvidence\\build\\Desktop_Qt_"
        "5_15_"
        "2_MinGW_32_bit-Debug\\src\\debug\\inelteh\\items.ini";

    QSettings settings(filePath, QSettings::IniFormat);
    settings.beginGroup("AppSettingsGeneral");
    employeeFolder = settings.value("employeefolder", "").toString();
    settings.endGroup();
}
