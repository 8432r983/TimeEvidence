#ifndef MONTHMODEL_H
#define MONTHMODEL_H

#include "entry.h"
#include <QAbstractListModel>
#include <QObject>
#include <QString>

class MonthModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(QString totalMonthHours READ totalMonthHours NOTIFY totalMonthHoursChanged FINAL)
    Q_PROPERTY(QString totalMonthDifference READ totalMonthDifference NOTIFY
                   totalMonthDifferenceChanged FINAL)

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
        VacationRole   = Qt::UserRole + 10
    };

    explicit MonthModel(QObject *parent = nullptr);

    int                            rowCount(const QModelIndex &parent) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    QVariant                       data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void loadEntries(QString date, QString Name);

    QString totalMonthHours() const;
    QString totalMonthDifference() const;

  signals:
    void totalMonthHoursChanged();
    void totalMonthDifferenceChanged();

  private:
    QVector<Entry *> m_entries;
    QString          m_totalMonthHours;
    QString          m_totalMonthDifference;
};

#endif // MONTHMODEL_H
