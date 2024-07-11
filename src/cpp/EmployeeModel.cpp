#include <QDebug>
#include <QFile>
#include <QSettings>
#include <algorithm>
#include <cmath>

#include "EmployeeModel.h"

EmployeeModel::EmployeeModel(QObject *parent)
    : QAbstractListModel(parent) {
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

    const Entry *entryItem = m_entries[index.row()];

    switch(role) {
    case DayRole:
        return QVariant(entryItem->day);
    case DateRole:
        return QVariant(entryItem->date);
    case ClockInRole:
        return QVariant(entryItem->clockIn);
    case ClockOutRole:
        return QVariant(entryItem->clockOut);
    case TotalRole:
        return QVariant(entryItem->total);
    case TravelRole:
        return QVariant(entryItem->travel);
    case DifferenceRole:
        return QVariant(entryItem->difference);
    }

    return QVariant();
}

void EmployeeModel::loadEntries(QString date, QString Name) {
    beginResetModel();
    setEmployeeFolder();
    QString filePath =
        employeeFolder + Name.split(" ")[0] + "_" + Name.split(" ")[1] + "\\";

    QFile file(filePath + date.split(".")[2] + "_" + date.split(".")[1] +
               ".txt");

    m_entries.clear();
    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            int    TotalTime = 0;
            Entry *pastEntry = new Entry();

            bool c = false;
            while(!file.atEnd()) {
                QString     line  = QString(file.readLine());
                QStringList items = line.replace(" ", "").split(";");

                QString Day      = items[0];
                QString Date     = items[1];
                QString ClockIn  = items[2];
                QString ClockOut = items[3].replace("\n", "");

                Entry *entry = new Entry();
                // pastEntry    = new Entry();

                if(Day != pastEntry->day && c) {
                    pastEntry->clockIn    = "-";
                    pastEntry->clockOut   = "-";
                    pastEntry->total      = intToTime(TotalTime);
                    pastEntry->travel     = "-";
                    pastEntry->difference = intToTime(TotalTime - 480);

                    m_entries.append(pastEntry);

                    pastEntry = new Entry();
                    TotalTime = timeToInt(ClockOut) - timeToInt(ClockIn);
                } else {
                    TotalTime += timeToInt(ClockOut) - timeToInt(ClockIn);
                    c = true;
                }

                entry->day        = Day;
                entry->date       = Date;
                entry->clockIn    = ClockIn;
                entry->clockOut   = ClockOut;
                entry->total      = "-";
                entry->travel     = "-";
                entry->difference = "-";

                m_entries.append(entry);
                *pastEntry = *entry;
            }

            if(TotalTime != 0) {
                pastEntry->clockIn    = "-";
                pastEntry->clockOut   = "-";
                pastEntry->total      = intToTime(TotalTime);
                pastEntry->travel     = "-";
                pastEntry->difference = intToTime(TotalTime - 480);

                m_entries.append(pastEntry);
            }
        }
    } else {
        qDebug() << "file doesnt exist";
    }

    std::reverse(m_entries.begin(), m_entries.end());

    endResetModel();
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
    int Hours   = floor(abs(time) / 60);
    int Minutes = abs(time) % 60;

    QString res = "";

    if(Hours < 10)
        res += "0" + QString::number(Hours);
    else
        res += QString::number(Hours);

    res += ":";
    if(Minutes < 10)
        res += "0" + QString::number(Minutes);
    else
        res += QString::number(Minutes);

    if(time < 0)
        res = "-" + res;

    return res;
}
