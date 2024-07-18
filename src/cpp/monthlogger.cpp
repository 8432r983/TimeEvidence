#include "monthlogger.h"
#include "entry.h"
#include "halfiles.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

MonthLogger::MonthLogger(QObject *parent)
    : QObject{parent} {
}

void MonthLogger::addEntry(QString Name, QString Day, QString Date, QString clockIn,
                           QString clockOut, QString travel, QString holiday, QString sickday,
                           QString vacation) {
    HalFiles hf;
    QString  filePath = hf.getEmployeeMonth(Name, Date);

    if(!QFile::exists(filePath)) {
        qDebug() << "file doesnt exist";
        return;
    }

    QFile file(filePath);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "cant open file: " + filePath;
    }

    QTextStream in(&file);
    if(file.size() == 0) {
        in << "Dan; Datum; Dolazak; Odlazak; Odradeno sati; Visak/Manjak; Sati puta; Drzavni ";
        in << "praznik; Bolovanje; Godisnji\r\n";
    }

    Entry ent;
    ent.clockIn  = clockIn;
    ent.clockOut = clockOut;
    ent.travel   = travel;
    ent.holiday  = holiday;
    ent.sickday  = sickday;
    ent.vacation = vacation;

    ent.setTotal();
    ent.setDifference();

    in << Day + "; " << Date.split(".")[0] + "; " << clockIn + "; " << clockOut + "; "
       << ent.total + "; " << ent.difference + "; " << travel + "; " << holiday + "; "
       << sickday + "; " << vacation << '\n';
}
