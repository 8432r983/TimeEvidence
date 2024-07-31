#include <QDate>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QStringList>
#include <QTextStream>
#include <algorithm>
#include <cmath>

#include "dateranges.h"
#include "datetime.h"
#include "entry.h"
#include "halfiles.h"
#include "holidaychecker.h"
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

void MonthModel::loadEntries(QString date, QString Name, QString act) {
    beginResetModel();

    qDeleteAll(m_entries);
    m_entries.clear();
    m_sums.reset();

    HalFiles hf;
    QString  filePath = hf.getEmployeeMonth(Name, date);

    if(act != "") {
        Entry *currEnt   = new Entry();
        currEnt->day     = DateTime().currentDay();
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
            qDebug() << "hello";
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

            if(entry->total != "-") {
                m_entries.append(entry);
            }
        }
    }

    m_vacation.clear();
    loadVacation(Name);
    m_monthSum = "-";

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

    entriesToFile(Name, date);

    for(int i = 0; i < m_entries.size(); i++) {
        m_sums.travel  = m_sums.intToTime(m_sums.timeToInt(m_sums.travel) + m_sums.timeToInt(m_entries[i]->travel));
        m_sums.holiday = m_sums.intToTime(m_sums.timeToInt(m_sums.holiday) + m_sums.timeToInt(m_entries[i]->holiday));
        if(m_entries[i]->sickdayValidity == "da")
            m_sums.sickday = m_sums.intToTime(m_sums.timeToInt(m_sums.sickday) + m_sums.timeToInt(m_entries[i]->sickday));
        m_sums.vacation = m_sums.intToTime(m_sums.timeToInt(m_sums.vacation) + m_sums.timeToInt(m_entries[i]->vacation));
        if(m_entries[i]->clockIn != "-" && m_entries[i]->clockOut != "-") {
            m_sums.total = m_sums.intToTime(m_sums.timeToInt(m_sums.total) + m_sums.timeToInt(m_entries[i]->total));
        }
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
            m_monthSum = daySum->intToTime(daySum->timeToInt(daySum->total) + daySum->timeToInt(m_monthSum));
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
    m_monthSum = endSum->intToTime(endSum->timeToInt(endSum->total) + endSum->timeToInt(m_monthSum));
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

    QString days     = QString::number(QDate::currentDate().daysInMonth());
    QDate   firstDay = QDate::fromString("01" + month, "dd.MM.yyyy");
    QDate   lastDay  = QDate::fromString(days + month, "dd.MM.yyyy");
    int     dist     = dr.dateDist(firstDay, lastDay);
    m_monthSum += "/" + QString::number(dist * 8) + ":00";

    emit monthSumChanged();
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
        return;
    }

    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "cant open file: " + filePath;
        return;
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

void MonthModel::entriesToFile(QString Name, QString date) {
    HalFiles hf;
    QString  filePath = hf.getEmployeeMonth(Name, date);

    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "cant open file: " << filePath;
    }

    QTextStream in(&file);
    in << "Dan; Datum; Dolazak; Odlazak; Odradeno sati; Visak/Manjak; Sati puta; Drzavni ";
    in << "praznik; Bolovanje; Godisnji; Dozvola za bolovanje\n";

    for(int i = 0; i < m_entries.size(); i++) {
        in << m_entries[i]->day + "; " << m_entries[i]->date + "; " << m_entries[i]->clockIn + "; "
           << m_entries[i]->clockOut + "; " << m_entries[i]->total + "; "
           << m_entries[i]->intToTime(m_entries[i]->calcDifference()) + "; " << m_entries[i]->travel + "; "
           << m_entries[i]->holiday + "; " << m_entries[i]->sickday + "; " << m_entries[i]->vacation + "; "
           << m_entries[i]->sickdayValidity << "\n";
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
        return ent.timeToInt(lhs->clockIn) > ent.timeToInt(rhs->clockIn);
    }
    return lhs->date.toInt() > rhs->date.toInt();
}

QString MonthModel::monthSum() const {
    return m_monthSum;
}
