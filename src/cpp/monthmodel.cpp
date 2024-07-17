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
    res[DayChangedRole] = "daychanged";

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
    case DayChangedRole:
        return QVariant(entryItem->daychanged);
    }

    return QVariant();
}

void MonthModel::loadEntries(QString date, QString Name) {
    beginResetModel();

    HalFiles hf;
    QString  filePath = hf.getEmployeeMonth(Name, date);

    if(!QFile::exists(filePath)) {
        qDebug() << "file doesnt exist";
        return;
    }

    QFile file(filePath);

    qDeleteAll(m_entries);
    m_entries.clear();

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
                entry->difference = "-";
                entry->travel     = elements[6].trimmed();
                entry->holiday    = elements[7].trimmed();
                entry->sickday    = elements[8].trimmed();
                entry->vacation   = elements[9].trimmed();
                m_entries.append(entry);
            }
        }

        int totalDayTime = m_entries[0]->calcTotal();

        for(int i = 1; i < m_entries.size(); i++) {
            if(m_entries[i]->date != m_entries[i - 1]->date) {
                Entry *ent = new Entry();

                ent->date  = m_entries[i - 1]->date;
                ent->total = ent->intToTime(totalDayTime);
                ent->setDifference();
                m_entries.insert(m_entries.begin() + i, ent);
                i++;

                m_entries[i - 1]->daychanged = true;
                totalDayTime                 = m_entries[i]->calcTotal();
            } else {
                totalDayTime += m_entries[i]->calcTotal();
            }
        }
        Entry *ent = new Entry();
        ent->total = ent->intToTime(totalDayTime);
        ent->setDifference();
        ent->date = m_entries.last()->date;
        m_entries.append(ent);
    }

    m_sums.reset();

    for(int i = 0; i < m_entries.size(); i++) {
        if(m_entries[i]->clockIn == "-" || m_entries[i]->clockOut == "-") {
            m_sums.total = m_sums.intToTime(m_sums.timeToInt(m_sums.total) +
                                            m_sums.timeToInt(m_entries[i]->total));
        }
        m_sums.difference = m_sums.intToTime(m_sums.timeToInt(m_sums.difference) +
                                             m_sums.timeToInt(m_entries[i]->difference));
        m_sums.travel     = m_sums.intToTime(m_sums.timeToInt(m_sums.travel) +
                                             m_sums.timeToInt(m_entries[i]->travel));
        m_sums.holiday    = m_sums.intToTime(m_sums.timeToInt(m_sums.holiday) +
                                             m_sums.timeToInt(m_entries[i]->holiday));
        m_sums.sickday    = m_sums.intToTime(m_sums.timeToInt(m_sums.sickday) +
                                             m_sums.timeToInt(m_entries[i]->sickday));
        m_sums.vacation   = m_sums.intToTime(m_sums.timeToInt(m_sums.vacation) +
                                             m_sums.timeToInt(m_entries[i]->vacation));
    }

    std::reverse(m_entries.begin(), m_entries.end());
    endResetModel();
}

QString MonthModel::getTotalSum() {
    return m_sums.total;
}

QString MonthModel::getDifferenceSum() {
    return m_sums.difference;
}

QString MonthModel::getTravelSum() {
    return m_sums.travel;
}

QString MonthModel::getHolidaySum() {
    return m_sums.holiday;
}

QString MonthModel::getSickdaySum() {
    return m_sums.sickday;
}

QString MonthModel::getVacationSum() {
    return m_sums.vacation;
}
