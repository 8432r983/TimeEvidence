#include <QDate>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QStringList>
#include <algorithm>
#include <cmath>

#include "dateranges.h"
#include "entry.h"
#include "halfiles.h"
#include "holidaychecker.h"
#include "monthmodel.h"
#include "specialdaylogger.h"

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

void MonthModel::loadEntries(QString date, QString Name, QString act) {
    beginResetModel();

    qDeleteAll(m_entries);
    m_entries.clear();

    HalFiles hf;
    QString  filePath = hf.getEmployeeMonth(Name, date);

    if(act != "") {
        Entry *currEnt   = new Entry();
        currEnt->date    = date.split(".")[0];
        currEnt->clockIn = act;
        m_entries.append(currEnt);
    }

    if(!QFile::exists(filePath)) {
        qDebug() << "file doesnt exist: " << filePath;
        endResetModel();
        return;
    }

    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "cant open file: " << filePath;
        endResetModel();
        return;
    }
    file.readLine();

    while(!file.atEnd()) {
        QString     line     = QString(file.readLine());
        QStringList elements = line.replace("\n", "").split(";");
        Entry      *entry;

        if(elements.size() == 11) {
            entry                  = new Entry();
            entry->day             = elements[0].trimmed();
            entry->date            = elements[1].trimmed();
            entry->clockIn         = elements[2].trimmed();
            entry->clockOut        = elements[3].trimmed();
            entry->total           = elements[4].trimmed();
            entry->difference      = "-";
            entry->travel          = elements[6].trimmed();
            entry->holiday         = elements[7].trimmed();
            entry->sickday         = elements[8].trimmed();
            entry->vacation        = elements[9].trimmed();
            entry->sickdayValidity = elements[10].trimmed().toLower();
            m_entries.append(entry);
        }
    }

    loadVacation(Name);

    for(int i = 0; i < m_vacation.size(); i++) {
        if(m_vacation[i].split(".")[1] == date.split(".")[1]) {
            Entry *vacationEnt    = new Entry();
            vacationEnt->date     = m_vacation[i].split(".")[0];
            vacationEnt->vacation = "08:00";
            vacationEnt->setTotal();
            m_entries.append(vacationEnt);
        }
    }

    std::sort(m_entries.begin(), m_entries.end(), comp);

    m_sums.reset();
    for(int i = 0; i < m_entries.size(); i++) {
        m_sums.travel  = m_sums.intToTime(m_sums.timeToInt(m_sums.travel) + m_sums.timeToInt(m_entries[i]->travel));
        m_sums.holiday = m_sums.intToTime(m_sums.timeToInt(m_sums.holiday) + m_sums.timeToInt(m_entries[i]->holiday));
        if(m_entries[i]->sickdayValidity == "da")
            m_sums.sickday = m_sums.intToTime(m_sums.timeToInt(m_sums.sickday) + m_sums.timeToInt(m_entries[i]->sickday));
        m_sums.vacation = m_sums.intToTime(m_sums.timeToInt(m_sums.vacation) + m_sums.timeToInt(m_entries[i]->vacation));
    }

    int totalTime    = 0;
    int sickdayTime  = 0;
    int vacationTime = 0;

    bool valid = false;

    QVector<Entry *> tempV;

    for(int i = 0; i < m_entries.size(); i++) {
        if(i != 0 && m_entries[i]->date != m_entries[i - 1]->date) {
            Entry *daySum = new Entry();
            if(sickdayTime != 0 && valid) {
                totalTime = sickdayTime;
            }
            if(vacationTime != 0) {
                totalTime = vacationTime;
            }

            daySum->total = daySum->intToTime(totalTime);
            daySum->date  = m_entries[i - 1]->date;
            daySum->setDifference();
            m_sums.total = m_sums.intToTime(m_sums.timeToInt(m_sums.total) + totalTime);
            tempV.append(daySum);

            totalTime = 0;

            vacationTime = m_entries[i]->timeToInt(m_entries[i]->vacation);
            sickdayTime  = m_entries[i]->timeToInt(m_entries[i]->sickday);
            if(m_entries[i]->sickday == "-") {
                totalTime = m_entries[i]->timeToInt(m_entries[i]->total);
            } else {
                m_entries[i]->total = "00:00";
            }

            if(m_entries[i]->sickdayValidity == "da")
                valid = true;
            else
                valid = false;

        } else {
            vacationTime += m_entries[i]->timeToInt(m_entries[i]->vacation);
            sickdayTime += m_entries[i]->timeToInt(m_entries[i]->sickday);
            if(m_entries[i]->sickday == "-") {
                totalTime += m_entries[i]->timeToInt(m_entries[i]->total);
            } else {
                m_entries[i]->total = "00:00";
            }
            if(m_entries[i]->sickdayValidity == "da")
                valid = true;
        }
    }

    Entry *endSum = new Entry();
    // qDebug() << totalTime << sickdayTime << vacationTime;
    if(sickdayTime != 0 && valid) {
        totalTime = sickdayTime;
    }
    if(vacationTime != 0) {
        totalTime = vacationTime;
    }
    endSum->total = endSum->intToTime(totalTime);
    endSum->date  = m_entries.last()->date;
    endSum->setDifference();
    m_sums.total = m_sums.intToTime(m_sums.timeToInt(m_sums.total) + totalTime);
    tempV.append(endSum);

    for(int i = 0; i < tempV.size(); i++) {
        m_entries.append(tempV[i]);
    }

    std::sort(m_entries.begin(), m_entries.end(), comp);
    for(int i = 1; i < m_entries.size(); i++) {
        if(m_entries[i]->date != m_entries[i - 1]->date) {
            m_entries[i]->daychanged = true;
        }
    }

    HolidayChecker   hch;
    SpecialDayLogger Spl;
    for(int i = 0; i < m_entries.size(); i++) {
        if(m_entries[i]->difference != "-") {
            QString Date = m_entries[i]->date + "." + date.split(".")[1] + "." + date.split(".")[2];
            if(QDate::fromString(Date, "dd.MM.yyyy").dayOfWeek() >= 6) {
                Spl.addDay(Name, Date, "vikend", m_entries[i]->total);
            } else if(hch.holidayCheck(QDate::fromString(Date, "dd.MM.yyyy"))) {
                Spl.addDay(Name, Date, "praznik", m_entries[i]->total);
            }
        }
    }

    m_totalSum = m_sums.total;

    DateRanges dr;
    QString    month     = "." + date.split(".")[1] + "." + date.split(".")[2];
    QDate      startDate = QDate::fromString(m_entries.last()->date + month, "dd.MM.yyyy");
    QDate      endDate   = QDate::fromString(m_entries[0]->date + month, "dd.MM.yyyy");

    m_differenceSum = m_sums.intToTime(m_sums.timeToInt(m_sums.total) - 8 * 60 * dr.dateDist(startDate, endDate));
    m_travelSum     = m_sums.travel;
    m_holidaySum    = m_sums.holiday;
    if(m_sums.sickday == "-") {
        m_sums.sickday = "00:00";
    }
    m_sickdaySum  = m_sums.sickday;
    m_vacationSum = m_sums.vacation;

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

        if(elements.size() == 3) {
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

bool MonthModel::comp(const Entry *lhs, const Entry *rhs) {
    if(lhs->date == rhs->date) {
        if(lhs->difference != "-")
            return true;
        if(rhs->difference != "-")
            return false;

        Entry ent;
        if(ent.timeToInt(lhs->total) > ent.timeToInt(rhs->total)) {
            return true;
        } else if(ent.timeToInt(lhs->total) < ent.timeToInt(rhs->total)) {
            return false;
        }

        return ent.timeToInt(lhs->clockIn) > ent.timeToInt(rhs->clockIn);
    }
    return lhs->date.toInt() > rhs->date.toInt();
}
