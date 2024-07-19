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
    QString getEmployeeMonth(const QString &Name, const QString &Date) const;

  private:
#if(WIN_ADR)
    const QString cPathData = "C:\\Users\\Adrian\\Documents\\Praksa\\TimeEvidence\\data\\";
#elif(WIN_MAR)
    const QString cPathData = "C:\\QtProjects\\TimeEvidence\\data\\";
#elif(GUF_ROKO_0700)
    const QString cPathData = "/root/data/";
#elif(CHE_DUNF_0310)
    const QString cPathData = "/home/root/data/";
#endif
    const QString cFnEmployees = "zaposlenici.txt";
    const QString cFnHolidays  = "praznici.txt";
    const QString cFnSettings  = "TimeEvidence.ini";
    const QString cLogFolder   = "monthlog\\";
};

#endif // HALFILES_H
