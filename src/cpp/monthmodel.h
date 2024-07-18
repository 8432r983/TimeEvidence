#ifndef MONTHMODEL_H
#define MONTHMODEL_H

#include "entry.h"
#include <QAbstractListModel>
#include <QObject>
#include <QString>

class MonthModel : public QAbstractListModel {
    Q_OBJECT

  public:
    enum EntryRoles {
        DayRole        = Qt::UserRole + 1,
        DateRole       = Qt::UserRole + 2,
        ClockInRole    = Qt::UserRole + 3,
        ClockOutRole   = Qt::UserRole + 4,
        TotalRole      = Qt::UserRole + 5,
        TravelRole     = Qt::UserRole + 6,
        DifferenceRole = Qt::UserRole + 7,
        HolidayRole    = Qt::UserRole + 8,
        SickdayRole    = Qt::UserRole + 9,
        VacationRole   = Qt::UserRole + 10,
        DayChangedRole = Qt::UserRole + 11
    };

    explicit MonthModel(QObject *parent = nullptr);

    int                            rowCount(const QModelIndex &parent) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    QVariant                       data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void loadEntries(QString date, QString Name);

    Q_INVOKABLE QString getTotalSum();
    Q_INVOKABLE QString getDifferenceSum();
    Q_INVOKABLE QString getTravelSum();
    Q_INVOKABLE QString getHolidaySum();
    Q_INVOKABLE QString getSickdaySum();
    Q_INVOKABLE QString getVacationSum();

  private:
    QVector<Entry *> m_entries;
    Entry            m_sums;
};

#endif // MONTHMODEL_H
