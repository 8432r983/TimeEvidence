#include "monthlogger.h"
#include "halfiles.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

MonthLogger::MonthLogger(QObject *parent)
    : QObject{parent} {
}

void MonthLogger::addEntry(QString Name, QString Day, QString Date,
                           QString clockIn, QString clockOut) {
    HalFiles hf;
    QString  filePath =
        hf.getEmployeeFolderPath() + Name.replace(" ", "_") + "\\";

    QString fileName = Date.split(".")[2] + "_" + Date.split(".")[1] + ".txt";

    QFile file(filePath + fileName);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "cant open file: " + filePath;
    }

    QTextStream in(&file);
    in << Day + "; " << Date.split(".")[0] + "; " << clockIn + "; " << clockOut
       << '\n';
}
