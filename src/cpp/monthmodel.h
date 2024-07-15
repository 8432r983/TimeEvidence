#ifndef MONTHMODEL_H
#define MONTHMODEL_H

#include "entry.h"
#include <QAbstractListModel>
#include <QObject>

class MonthModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(int totalMonthHours READ totalMonthHours NOTIFY totalMonthHoursChanged FINAL)
    Q_PROPERTY(int totalDifference READ totalDifference NOTIFY totalDifferenceChanged FINAL)

  public:
    enum EntryRoles {
        DayRole        = Qt::UserRole + 1,
        DateRole       = Qt::UserRole + 2,
        ClockInRole    = Qt::UserRole + 3,
        ClockOutRole   = Qt::UserRole + 4,
        TotalRole      = Qt::UserRole + 5,
        TravelRole     = Qt::UserRole + 6,
        DifferenceRole = Qt::UserRole + 7
    };

    explicit MonthModel(QObject *parent = nullptr);

    int                            rowCount(const QModelIndex &parent) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    QVariant                       data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void loadEntries(QString date, QString Name);

    Q_INVOKABLE QString getMonthHours();
    Q_INVOKABLE QString getMonthDifference();
    Q_INVOKABLE QString calcPastMonthTotal(QString Name, QString Date);

    int totalMonthHours() const;
    int totalDifference() const;

  signals:
    void totalMonthHoursChanged();
    void totalDifferenceChanged();

  private:
    QVector<Entry *> m_entries;
    QString          employeeFolder = "";
    int              m_totalMonthHours;
    int              m_totalDifference;
};

#endif // MONTHMODEL_H
