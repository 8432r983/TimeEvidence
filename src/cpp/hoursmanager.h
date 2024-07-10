#ifndef HOURSMANAGER_H
#define HOURSMANAGER_H

#include <QObject>
#include <QString>

class HoursManager : public QObject {
    Q_OBJECT
  public:
    explicit HoursManager(QObject *parent = nullptr);

    Q_PROPERTY(
        QString employeeName READ employeeName NOTIFY employeeNameChanged FINAL)

    Q_INVOKABLE void addEntry(QString day, QString date, QString clockIn,
                              QString clockOut);
    Q_INVOKABLE void setMainPath(QString EmployeeName);

    QString getFileName(QString date);

    QString employeeName() const;

    void setEmployeeFolder();

  signals:
    void employeeNameChanged();

  private:
    QString m_employeeName;
    QString mainFilePath;
    QString employeeFolder = "";
};

#endif // HOURSMANAGER_H
