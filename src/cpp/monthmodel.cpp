#include <QDate>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <algorithm>
#include <cmath>

#include "entry.h"
#include "halfiles.h"
#include "monthmodel.h"

MonthModel::MonthModel(QObject *parent)
    : QAbstractListModel(parent) {
}

int MonthModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid() || m_entries.isEmpty())
        return 0;
    return m_entries.size();
}

QHash<int, QByteArray> MonthModel::roleNames() const {
    QHash<int, QByteArray> res;

    res[DayRole]        = "day";
    res[DateRole]       = "date";
    res[ClockInRole]    = "clockIn";
    res[ClockOutRole]   = "clockOut";
    res[TotalRole]      = "total";
    res[TravelRole]     = "travel";
    res[DifferenceRole] = "difference";
    res[HolidayRole]    = "holiday";
    res[SickdayRole]    = "sickday";
    res[VacationRole]   = "vacation";

    return res;
}

QVariant MonthModel::data(const QModelIndex &index, int role) const {
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
    case HolidayRole:
        return QVariant(entryItem->holiday);
    case SickdayRole:
        return QVariant(entryItem->sickday);
    case VacationRole:
        return QVariant(entryItem->vacation);
    }

    return QVariant();
}

void MonthModel::loadEntries(QString date, QString Name) {
    beginResetModel();

    HalFiles hf;
    QString  filePath = hf.getEmployeeMonth(Name, date);

    QFile file(filePath);

    qDeleteAll(m_entries);
    m_entries.clear();

    int totalMonthTime           = 0;
    int totalMonthTimeDifference = 0;

    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            file.readLine();
            while(!file.atEnd()) {
                QString     line     = QString(file.readLine());
                QStringList elements = line.replace("\n", "").split(";");
                Entry      *entry;

                if(elements.size() > 1) {
                    entry             = new Entry();
                    entry->day        = elements[0].trimmed();
                    entry->date       = elements[1].trimmed();
                    entry->clockIn    = elements[2].trimmed();
                    entry->clockOut   = elements[3].trimmed();
                    entry->total      = elements[4].trimmed();
                    entry->difference = elements[5].trimmed();
                    entry->travel     = elements[6].trimmed();
                    entry->holiday    = elements[7].trimmed();
                    entry->sickday    = elements[8].trimmed();
                    entry->vacation   = elements[9].trimmed();
                    m_entries.append(entry);
                }
            }

            int totalDayTime = m_entries[0]->calcTotal();

            totalMonthTime           = m_entries[0]->calcTotal();
            totalMonthTimeDifference = m_entries[0]->calcDifference();

            for(int i = 1; i < m_entries.size(); i++) {
                if(m_entries[i]->date != m_entries[i - 1]->date) {
                    Entry *ent = new Entry();

                    ent->date  = m_entries[i - 1]->date;
                    ent->total = ent->intToTime(totalDayTime);
                    ent->setDifference();
                    m_entries.insert(m_entries.begin() + i, ent);
                    i++;

                    totalDayTime = m_entries[i]->timeToInt(m_entries[i]->total);

                } else {
                    totalDayTime += m_entries[i]->calcTotal();
                }

                totalMonthTime += m_entries[i]->calcTotal();
                totalMonthTimeDifference += m_entries[i]->calcDifference();
            }
            Entry *ent = new Entry();
            ent->total = ent->intToTime(totalDayTime);
            ent->setDifference();
            m_entries.append(ent);
        }
    } else {
        qDebug() << "file doesnt exist";
    }

    Entry en;
    m_totalMonthHours      = en.intToTime(totalMonthTime);
    m_totalMonthDifference = en.intToTime(totalMonthTimeDifference);

    emit totalMonthHoursChanged();
    emit totalMonthDifferenceChanged();

    std::reverse(m_entries.begin(), m_entries.end());
    endResetModel();
}

QString MonthModel::totalMonthHours() const {
    return m_totalMonthHours;
}

QString MonthModel::totalMonthDifference() const {
    return m_totalMonthDifference;
}
