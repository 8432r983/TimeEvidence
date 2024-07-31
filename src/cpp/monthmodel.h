#ifndef MONTHMODEL_H
#define MONTHMODEL_H

#include "entry.h"
#include <QAbstractListModel>
#include <QHash>
#include <QObject>
#include <QString>

class MonthModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(QString totalSum READ totalSum NOTIFY totalSumChanged FINAL)
    Q_PROPERTY(QString differenceSum READ differenceSum NOTIFY differenceSumChanged FINAL)
    Q_PROPERTY(QString travelSum READ travelSum NOTIFY travelSumChanged FINAL)
    Q_PROPERTY(QString holidaySum READ holidaySum NOTIFY holidaySumChanged FINAL)
    Q_PROPERTY(QString sickdaySum READ sickdaySum NOTIFY sickdaySumChanged FINAL)
    Q_PROPERTY(QString vacationSum READ vacationSum NOTIFY vacationSumChanged FINAL)
    Q_PROPERTY(QString monthSum READ monthSum NOTIFY monthSumChanged FINAL)

  public:
    enum EntryRoles {
        DayRole             = Qt::UserRole + 1,
        DateRole            = Qt::UserRole + 2,
        ClockInRole         = Qt::UserRole + 3,
        ClockOutRole        = Qt::UserRole + 4,
        TotalRole           = Qt::UserRole + 5,
        TravelRole          = Qt::UserRole + 6,
        DifferenceRole      = Qt::UserRole + 7,
        HolidayRole         = Qt::UserRole + 8,
        SickdayRole         = Qt::UserRole + 9,
        VacationRole        = Qt::UserRole + 10,
        SickdayValidityRole = Qt::UserRole + 11,
        DayChangedRole      = Qt::UserRole + 12
    };

    explicit MonthModel(QObject *parent = nullptr);

    int                            rowCount(const QModelIndex &parent) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    QVariant                       data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void loadEntries(QString date, QString Name, QString act = "");
    void             loadVacation(QString Name);
    void             entriesToFile(QString Name, QString date);

    QString totalSum() const;
    QString differenceSum() const;
    QString travelSum() const;
    QString holidaySum() const;
    QString sickdaySum() const;
    QString vacationSum() const;
    QString monthSum() const;

  signals:
    void totalSumChanged();
    void differenceSumChanged();
    void travelSumChanged();
    void holidaySumChanged();
    void sickdaySumChanged();
    void vacationSumChanged();
    void monthSumChanged();

  private:
    QVector<Entry *> m_entries;
    QVector<QString> m_vacation;
    Entry            m_sums;
    QString          m_totalSum;
    QString          m_differenceSum;
    QString          m_travelSum;
    QString          m_holidaySum;
    QString          m_sickdaySum;
    QString          m_vacationSum;
    QString          m_monthSum;
    static bool      comp(const Entry *lhs, const Entry *rhs);
};

#endif // MONTHMODEL_H
