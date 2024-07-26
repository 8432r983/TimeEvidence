#include "specialdaylogger.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "halfiles.h"

SpecialDayLogger::SpecialDayLogger(QObject *parent)
    : QObject{parent} {
}

void SpecialDayLogger::addDay(QString Name, QString date, QString type, QString hours) {
    HalFiles hf;
    QString  filePath = hf.getSpecialDays(Name);

    if(!QFile::exists(filePath)) {
        qDebug() << "file doesnt exist: " << filePath;
    }

    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "cant open file: " << filePath;
    }

    QTextStream in(&file);
    if(file.size() == 0) {
        in << "Datum; vrsta dana; odradeno sati;"
           << "\n";
    }

    in << date + "; " << type + "; " << hours << "\n";
}
