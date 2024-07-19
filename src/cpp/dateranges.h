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

    void loadRanges();

    QDate lowerVacationBound() const;
    QDate upperVacationBound() const;

  signals:
    void lowerVacationBoundChanged();
    void upperVacationBoundChanged();

  private:
    QDate m_lowerVacationBound;
    QDate m_upperVacationBound;
};

#endif // DATERANGES_H
