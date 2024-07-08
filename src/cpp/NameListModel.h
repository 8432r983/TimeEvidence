#ifndef NAMELISTMODEL_H
#define NAMELISTMODEL_H

#include <QAbstractListModel>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QVector>

struct Employee {
    QString name;
    QString password;
    double  hours;
    int     vacation;
    int     device;
    QString employeeStatus;
};

class NameListModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(
        QVector<Employee> employees READ employees NOTIFY employeesChanged)
    Q_PROPERTY(bool verified READ verified NOTIFY verifiedChanged)
    Q_PROPERTY(int currentDevice)

  public:
    explicit NameListModel(QObject *parent = nullptr);

    enum employeeRoles {
        NameRole           = Qt::UserRole + 1,
        PasswordRole       = Qt::UserRole + 2,
        HoursRole          = Qt::UserRole + 3,
        VacationRole       = Qt::UserRole + 4,
        DeviceRole         = Qt::UserRole + 5,
        EmployeeStatusRole = Qt::UserRole + 6
    };

    // QAbstractItemModel interface

    int rowCount(const QModelIndex &parent) const override;
    // int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const override;

    void loadEmployees();

    Q_INVOKABLE bool    verifyEmployee(QString password, QString name);
    Q_INVOKABLE QString getName(int index);
    Q_INVOKABLE QString getStatus(int index);
    Q_INVOKABLE void    popupExited();
    Q_INVOKABLE void    refreshEmployees();

    virtual QHash<int, QByteArray> roleNames() const override;

    QVector<Employee>
         employees() const; // MAR Keep it private... no need for signals...
    bool verified() const;

  signals:
    void verifiedChanged();
    void employeesChanged();

  private:
    QVector<Employee> m_employees;
    bool              m_verified;

#if(WIN_FULL)
    const QString cPath =
        "C:\\QtProjects\\TimeEvidence\\data\\"; // MAR path to server
#elif(WIN_DEMO)
    const QString cPath =
        "C:\\Users\\Adrian\\Documents\\Praksa\\TimeEvidence\\data\\";
#elif(GUF_ROKO_0700)
    const QString cPath = "/root/data/"
#elif(CHE_DUNF_0310)
    const QString cPath = "/home/root/data/"
#endif
    const QString cEmployees      = "zaposlenici.txt";
    const QString cHolidays       = "praznici.txt";
    int           m_currentDevice = 1;
};

#endif // NAMELISTMODEL_H
