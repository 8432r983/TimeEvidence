#ifndef NAMELISTMODEL_H
#define NAMELISTMODEL_H

#include <QAbstractListModel>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QVector>

struct Employee1 {
    QString name;
    QString password;
    double  hours;
    int     vacation;
    int     device;
    QString employeeStatus;
};

class NameListModel : public QAbstractListModel {
    Q_OBJECT

  public:
    explicit NameListModel(QObject *parent = nullptr);

    enum NameListModelRoles {
        NameRole           = Qt::UserRole + 1,
        PasswordRole       = Qt::UserRole + 2,
        HoursRole          = Qt::UserRole + 3,
        VacationRole       = Qt::UserRole + 4,
        DeviceRole         = Qt::UserRole + 5,
        EmployeeStatusRole = Qt::UserRole + 6
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int                role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    void loadEmployees();

    QString getConfigFilePath();
    void    setDevice();

    Q_INVOKABLE bool    verifyEmployee(QString password, QString name);
    Q_INVOKABLE QString getName(int index);
    Q_INVOKABLE QString getStatus(int index);
    Q_INVOKABLE void    popupExited();
    Q_INVOKABLE void    refreshEmployees();

    bool verified() const;

    int currentDevice() const;

  signals:
    void verifiedChanged();
    void employeesChanged();
    void currentDeviceChanged();

  private:
    QVector<Employee1> mlst;

#if(WIN_ADR)
    const QString cPath =
        "C:\\Users\\Adrian\\Documents\\Praksa\\TimeEvidence\\data\\";
#elif(WIN_MAR)
    const QString cPath = "C:\\QtProjects\\TimeEvidence\\data\\";
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
