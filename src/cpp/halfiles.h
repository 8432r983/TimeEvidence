#ifndef HALFILES_H
#define HALFILES_H

#include <QObject>

class HalFiles : public QObject {
    Q_OBJECT
  public:
    explicit HalFiles(QObject *parent = nullptr);

    QString getEmployeesFilePath() const;
    QString getHolidaysFilePath() const;
    QString getSettingsFilePath() const;
    QString getEmployeeFolderPath() const;
    QString getEmployeeVacationPath(QString &Name) const;
    QString getEmployeeMonth(const QString &Name, const QString &Date) const;
    QString cleanString(QString str) const;

  private:
#if(WIN_ADR)
    const QString cPathData = "C:\\Users\\Adrian\\Documents\\Praksa\\TimeEvidence\\data\\";
    const QString sep       = "\\";
#elif(WIN_MAR)
    const QString cPathData = "C:/QtProjects/TimeEvidence/data/";
    const QString sep       = "/";
#elif(GUF_ROKO_0700)
    const QString cPathData = "/root/data/";
    const QString sep       = "/";
#elif(CHE_DUNF_0310)
    const QString cPathData = "/home/root/data/";
    const QString sep       = "/";
#endif
    const QString cFnEmployees = "zaposlenici.txt";
    const QString cFnHolidays  = "praznici.txt";
    const QString cFnSettings  = "TimeEvidence.ini";
    const QString cLogFolder   = "monthlog" + sep;
    const QString cVacation    = "Godisnji.txt";
};

#endif // HALFILES_H
