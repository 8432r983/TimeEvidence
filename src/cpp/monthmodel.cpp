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

    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
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
                }
            }

            int totalTime     = m_entries[0]->calcTotal();
            m_totalMonthHours = m_entries[0]->calcTotal();
            m_totalDifference = 0;
            for(int i = 1; i < m_entries.size(); i++) {
                if(m_entries[i]->date != m_entries[i - 1]->date) {
                    m_entries[i - 1]->total =
                        m_entries[i - 1]->intToTime(totalTime);
                    m_entries[i - 1]->setDifference();

                    m_totalDifference += m_entries[i - 1]->calcDifference();

                    totalTime = m_entries[i]->calcTotal();
                } else {
                    totalTime += m_entries[i]->calcTotal();
                }

                m_totalMonthHours += m_entries[i]->calcTotal();
            }

            m_entries[m_entries.size() - 1]->total =
                m_entries[m_entries.size() - 1]->intToTime(totalTime);
            m_entries[m_entries.size() - 1]->setDifference();
            m_totalDifference +=
                m_entries[m_entries.size() - 1]->calcDifference();
        }
    } else {
        qDebug() << "file doesnt exist";
    }

    emit totalMonthHoursChanged();
    emit totalDifferenceChanged();

    std::reverse(m_entries.begin(), m_entries.end());
    endResetModel();
}

QString MonthModel::getMonthHours() {
    if(m_entries.size() != 0)
        return m_entries[0]->intToTime(m_totalMonthHours);
    return "";
}

QString MonthModel::getMonthDifference() {
    if(m_entries.size() != 0)
        return m_entries[0]->intToTime(m_totalDifference);
    return "";
}

int MonthModel::totalMonthHours() const {
    return m_totalMonthHours;
}

int MonthModel::totalDifference() const {
    return m_totalDifference;
}
