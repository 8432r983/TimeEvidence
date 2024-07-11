#ifndef EMPLOYEEMODEL_H
#define EMPLOYEEMODEL_H

#include <QAbstractListModel>
#include <QObject>

struct Entry {
    QString day;
    QString date;
    QString clockIn;
    QString clockOut;
    QString total;
    QString travel;
    QString difference;
};

class EmployeeModel : public QAbstractListModel {
    Q_OBJECT

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

    explicit EmployeeModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void loadEntries(QString date, QString Name);
    void             setEmployeeFolder();

    int     timeToInt(QString time);
    QString intToTime(int time);

  private:
    QVector<Entry *> m_entries;
    QString          employeeFolder = "";
};

#endif // EMPLOYEEMODEL_H
