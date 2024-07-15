#include <QDebug>
#include <QFile>
#include <QSettings>
#include <algorithm>
#include <cmath>

#include "EmployeeModel.h"
#include "entry.h"
#include "halfiles.h"

EmployeeModel::EmployeeModel(QObject *parent)
    : QAbstractListModel(parent) {
}

int EmployeeModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid() || m_entries.isEmpty())
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

    HalFiles hf;

    QString filePath =
        hf.getEmployeeFolderPath() + Name.replace(" ", "_") + "\\";
    QString fileName = date.split(".")[2] + "_" + date.split(".")[1] + ".txt";

    QFile file(filePath + fileName);

    qDeleteAll(m_entries);
    m_entries.clear();

    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            Entry *lastEntry;
            int    totalTime = 0;

            lastEntry = new Entry();
            while(!file.atEnd()) {
                QString     line     = QString(file.readLine());
                QStringList elements = line.replace("\n", "").split(";");
                Entry      *entry;

                if(elements.size() == 4) {
                    entry           = new Entry();
                    entry->day      = elements[0].trimmed();
                    entry->date     = elements[1].trimmed();
                    entry->clockIn  = elements[2].trimmed();
                    entry->clockOut = elements[3].trimmed();
                    m_entries.append(entry);

                    if(entry->date != lastEntry->date &&
                       lastEntry->date != "-") {
                        lastEntry->total = lastEntry->intToTime(totalTime);
                        lastEntry->calcDifference();
                        m_entries.append(lastEntry);
                        totalTime = 0;
                    } else {
                        entry->calcTotal();
                        totalTime += entry->timeToInt(entry->total);
                    }
                    lastEntry->fromEntry(entry);
                }
            }
            if(totalTime != 0) {
                lastEntry->total = lastEntry->intToTime(totalTime);
                lastEntry->calcDifference();
                lastEntry->clockIn  = "-";
                lastEntry->clockOut = "-";
                m_entries.append(lastEntry);
            }
        }
    } else {
        qDebug() << "file doesnt exist";
    }

    std::reverse(m_entries.begin(), m_entries.end());
    endResetModel();
}
