#include "EmployeeModel.h"

#include <QDebug>
#include <QFile>
#include <QSettings>
#include <cmath>

EmployeeModel::EmployeeModel(QObject *parent)
    : QAbstractListModel(parent) {

    beginResetModel();
    endResetModel();
}

int EmployeeModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid())
        return 0;
    return m_entries.size();
}

QHash<int, QByteArray> EmployeeModel::roleNames() const {
    QHash<int, QByteArray> res;

    res[DayRole]        = "day";
    res[DateRole]       = "date";
    res[ClockInRole]    = "clockIn";
    res[ClockOutRole]   = "clockOut";
    res[TotalRole]      = "total";
    res[TravelRole]     = "travel";
    res[DifferenceRole] = "difference";

    return res;
}

QVariant EmployeeModel::data(const QModelIndex &index, int role) const {
    if(!hasIndex(index.row(), index.column(), index.parent()))
        return QVariant();

    const Entry entryItem = m_entries[index.row()];

    switch(role) {
    case DayRole:
        return QVariant(entryItem.day);
    case DateRole:
        return QVariant(entryItem.date);
    case ClockInRole:
        return QVariant(entryItem.clockIn);
    case ClockOutRole:
        return QVariant(entryItem.clockOut);
    case TotalRole:
        return QVariant(entryItem.total);
    case TravelRole:
        return QVariant(entryItem.travel);
    case DifferenceRole:
        return QVariant(entryItem.difference);
    }

    return QVariant();
}

void EmployeeModel::loadEntries(QString date, QString Name) {
    QString filePath =
        employeeFolder + Name.split(" ")[0] + "_" + Name.split(" ")[1];

    QFile file(filePath + date.split(".")[2] + "_" + date.split(".")[1]);

    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            int     TotalTime = 0;
            QString pastDay   = "";

            while(!file.atEnd()) {
                QString     line  = QString(file.readLine());
                QStringList items = line.replace(" ", "").split(";");

                QString Day      = items[0];
                QString Date     = items[1];
                QString ClockIn  = items[3];
                QString ClockOut = items[4];

                Entry entry;

                if(Day != pastDay) {
                    entry.day        = Day;
                    entry.date       = Date;
                    entry.clockIn    = ClockIn;
                    entry.clockOut   = ClockOut;
                    entry.total      = TotalTime.toString();
                    entry.travel     = "-";
                    entry.difference = intToTime(TotalTime - 8);

                    TotalTime = 0;
                } else {
                    TotalTime += timeToInt(ClockOut) - timeToInt(ClockIn);
                    entry.day        = Day;
                    entry.date       = Date;
                    entry.clockIn    = ClockIn;
                    entry.clockOut   = ClockOut;
                    entry.total      = "-";
                    entry.travel     = "-";
                    entry.difference = "-";
                }

                pastDay = Day;
                m_entries.append(entry);
            }
        }
    } else {
        qDebug() << "file doesnt exist";
    }
}

void EmployeeModel::setEmployeeFolder() {
    QString filePath =
        "C:\\Users\\Adrian\\Documents\\Praksa\\TimeEvidence\\build\\Desktop_Qt_"
        "5_15_"
        "2_MinGW_32_bit-Debug\\src\\debug\\inelteh\\items.ini";

    QSettings settings(filePath, QSettings::IniFormat);
    settings.beginGroup("AppSettingsGeneral");
    employeeFolder = settings.value("employeefolder", "").toString();
    settings.endGroup();
}

int EmployeeModel::timeToInt(QString time) {
    if(time == "")
        return 0;
    int Hours   = time.split(":")[0].toInt();
    int Minutes = time.split(":")[1].toInt();

    return Hours * 60 + Minutes;
}

QString EmployeeModel::intToTime(int time) {
    int Hours   = floor(time / 60);
    int Minutes = time & 60;

    QString res;

    if(Hours < 10)
        res += "0" +

               return res;
}

QVector<Entry> EmployeeModel::entries() const {
    return m_entries;
}
