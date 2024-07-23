#include <QDate>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QStringList>
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

    res[DayRole]             = "day";
    res[DateRole]            = "date";
    res[ClockInRole]         = "clockIn";
    res[ClockOutRole]        = "clockOut";
    res[TotalRole]           = "total";
    res[TravelRole]          = "travel";
    res[DifferenceRole]      = "difference";
    res[HolidayRole]         = "holiday";
    res[SickdayRole]         = "sickday";
    res[VacationRole]        = "vacation";
    res[DayChangedRole]      = "daychanged";
    res[SickdayValidityRole] = "sickdayvalidity";

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
    case SickdayValidityRole:
        return QVariant(entryItem->sickdayValidity);
    }

    return QVariant();
}

bool comp(const Entry *lhs, const Entry *rhs) {
    if(lhs->date == rhs->date) {
        if(lhs->difference != "-")
            return true;
        if(rhs->difference != "-")
            return false;

        Entry ent;
        return ent.timeToInt(lhs->total) > ent.timeToInt(rhs->total);
    }
    return lhs->date.toInt() > rhs->date.toInt();
}

void MonthModel::loadEntries(QString date, QString Name) {
    beginResetModel();

    HalFiles hf;
    QString  filePath = hf.getEmployeeMonth(Name, date);

    if(!QFile::exists(filePath)) {
        qDebug() << "file doesnt exist: " << filePath;
        return;
    }

    QFile file(filePath);

    qDeleteAll(m_entries);
    m_entries.clear();

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        file.readLine();
        loadVacation(Name);
        while(!file.atEnd()) {
            QString     line     = QString(file.readLine());
            QStringList elements = line.replace("\n", "").split(";");
            Entry      *entry;

            if(elements.size() > 1) {
                entry                  = new Entry();
                entry->day             = elements[0].trimmed();
                entry->date            = elements[1].trimmed();
                entry->clockIn         = elements[2].trimmed();
                entry->clockOut        = elements[3].trimmed();
                entry->total           = elements[4].trimmed();
                entry->difference      = elements[5].trimmed();
                entry->travel          = elements[6].trimmed();
                entry->holiday         = elements[7].trimmed();
                entry->sickday         = elements[8].trimmed();
                entry->vacation        = elements[9].trimmed();
                entry->sickdayValidity = elements[10].trimmed().toLower();
                m_entries.append(entry);
            }
        }

        std::sort(m_entries.begin(), m_entries.end(), comp);

        m_sums.reset();
        for(int i = 0; i < m_entries.size(); i++) {
            if(m_entries[i]->sickdayValidity == "da") {
                m_entries[i]->total = m_entries[i]->sickday;
            } else if(m_entries[i]->sickday == "-") {
                m_sums.total = m_sums.intToTime(m_sums.timeToInt(m_sums.total) + m_sums.timeToInt(m_entries[i]->total));
            } else if(m_entries[i]->sickday != "-") {
                m_entries[i]->total = "-";
            }

            m_sums.travel   = m_sums.intToTime(m_sums.timeToInt(m_sums.travel) + m_sums.timeToInt(m_entries[i]->travel));
            m_sums.holiday  = m_sums.intToTime(m_sums.timeToInt(m_sums.holiday) + m_sums.timeToInt(m_entries[i]->holiday));
            m_sums.sickday  = m_sums.intToTime(m_sums.timeToInt(m_sums.sickday) + m_sums.timeToInt(m_entries[i]->sickday));
            m_sums.vacation = m_sums.intToTime(m_sums.timeToInt(m_sums.vacation) + m_sums.timeToInt(m_entries[i]->vacation));
        }

        int diff          = std::abs(m_entries.last()->date.toInt() - m_entries[0]->date.toInt());
        m_sums.difference = m_sums.intToTime(m_sums.timeToInt(m_sums.total) - 8 * 60 * diff);

        int totalDayTime = m_entries[0]->calcTotal();

        m_entries[0]->difference = "-";
        for(int i = 1; i < m_entries.size(); i++) {
            if(m_entries[i]->date != m_entries[i - 1]->date) {
                Entry *ent = new Entry();

                ent->date  = m_entries[i - 1]->date;
                ent->total = ent->intToTime(totalDayTime);
                ent->setDifference();
                m_entries.insert(m_entries.begin() + i, ent);
                i++;

                totalDayTime             = m_entries[i]->timeToInt(m_entries[i]->total);
                m_entries[i]->difference = "-";
            } else {
                totalDayTime += m_entries[i]->timeToInt(m_entries[i]->total);
                m_entries[i]->total      = "-";
                m_entries[i]->difference = "-";
            }
        }
        Entry *ent = new Entry();
        ent->total = ent->intToTime(totalDayTime);
        ent->setDifference();
        ent->date = m_entries.last()->date;
        m_entries.append(ent);
    }
    std::sort(m_entries.begin(), m_entries.end(), comp);

    for(int i = 1; i < m_entries.size(); i++) {
        if(m_entries[i]->date != m_entries[i - 1]->date) {
            m_entries[i]->daychanged = true;
        }
    }

    m_totalSum      = m_sums.total;
    m_differenceSum = m_sums.difference;
    m_travelSum     = m_sums.travel;
    m_holidaySum    = m_sums.holiday;
    m_sickdaySum    = m_sums.sickday;
    m_vacationSum   = m_sums.vacation;

    emit totalSumChanged();
    emit differenceSumChanged();
    emit travelSumChanged();
    emit holidaySumChanged();
    emit sickdaySumChanged();
    emit vacationSumChanged();

    endResetModel();
}

void MonthModel::loadVacation(QString Name) {
    HalFiles hf;
    QString  filePath = hf.getEmployeeVacationPath(Name);

    if(!QFile::exists(filePath)) {
        qDebug() << "file doesnt exist: " << filePath;
    }

    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "cant open file: " + filePath;
    }
    file.readLine();

    while(!file.atEnd()) {
        QStringList elements = QString(file.readLine()).split(";");

        if(elements.size() == 2) {
            if(elements[1].trimmed().toLower() == "da") {
                m_vacation.append(elements[0].trimmed());
            }
        }
    }
}

QString MonthModel::totalSum() const {
    return m_totalSum;
}

QString MonthModel::differenceSum() const {
    return m_differenceSum;
}

QString MonthModel::travelSum() const {
    return m_travelSum;
}

QString MonthModel::holidaySum() const {
    return m_holidaySum;
}

QString MonthModel::sickdaySum() const {
    return m_sickdaySum;
}

QString MonthModel::vacationSum() const {
    return m_vacationSum;
}
