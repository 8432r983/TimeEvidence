#pragma once
#include <QDateTime>
#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QTimer>

class DateTime : public QObject {
    Q_OBJECT
    // clang-format off
    Q_PROPERTY(QString formatted  READ formatted  NOTIFY formattedChanged  FINAL)
    Q_PROPERTY(QString currentDay READ currentDay NOTIFY currentDayChanged FINAL)
    Q_PROPERTY(bool    isDemo     READ isDemo     NOTIFY isDemoChanged     FINAL)
    // clang-format on

  public:
    explicit DateTime(QObject *parent = nullptr);
    ~DateTime();

    static DateTime *instance();
    static QObject  *singletonProvider(QQmlEngine *, QJSEngine *);

    QString formatted() const;
    void    setFormatted(const QString &newFormattedDateTime);

    int minutes() const;

    QString currentDay() const;
    void    setCurrentDay();

    bool isDemo() const;
    void setIsDemo(const bool &newIsDemo);

  signals:
    void formattedChanged();

    void currentDayChanged();

    void isDemoChanged();

  private:
    bool      m_isDemo;
    QDateTime m_dateTime;
    QString   m_formattedDateTime;
    QTimer   *m_timer;
    void      initializeTimer();

    QString m_currentDay;

  private slots:
    void timerTout();
};
