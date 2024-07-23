#ifndef DATERANGES_H
#define DATERANGES_H

#include <QDate>
#include <QObject>

class DateRanges : public QObject {
    Q_OBJECT
  public:
    explicit DateRanges(QObject *parent = nullptr);

    Q_PROPERTY(QDate lowerVacationBound READ lowerVacationBound NOTIFY lowerVacationBoundChanged FINAL)
    Q_PROPERTY(QDate upperVacationBound READ upperVacationBound NOTIFY upperVacationBoundChanged FINAL)

    Q_PROPERTY(QDate lowerValidSickdayBound READ lowerValidSickdayBound NOTIFY lowerValidSickdayBoundChanged FINAL)
    Q_PROPERTY(QDate upperValidSickdayBound READ upperValidSickdayBound NOTIFY upperValidSickdayBoundChanged FINAL)

    Q_PROPERTY(QDate lowerInvalidSickdayBound READ lowerInvalidSickdayBound NOTIFY lowerInvalidSickdayBoundChanged FINAL)
    Q_PROPERTY(QDate upperInvalidSickdayBound READ upperInvalidSickdayBound NOTIFY upperInvalidSickdayBoundChanged FINAL)

    void            loadRanges();
    QDate           calcWorkDays(int bound);
    Q_INVOKABLE int dateDist(QDate dateA, QDate dateB);

    QDate lowerVacationBound() const;
    QDate upperVacationBound() const;
    QDate lowerValidSickdayBound() const;
    QDate upperValidSickdayBound() const;
    QDate lowerInvalidSickdayBound() const;
    QDate upperInvalidSickdayBound() const;

  signals:
    void lowerVacationBoundChanged();
    void upperVacationBoundChanged();
    void lowerValidSickdayBoundChanged();
    void upperValidSickdayBoundChanged();
    void lowerInvalidSickdayBoundChanged();
    void upperInvalidSickdayBoundChanged();

  private:
    QDate m_lowerVacationBound;
    QDate m_upperVacationBound;
    QDate m_lowerValidSickdayBound;
    QDate m_upperValidSickdayBound;
    QDate m_lowerInvalidSickdayBound;
    QDate m_upperInvalidSickdayBound;
};

#endif // DATERANGES_H
