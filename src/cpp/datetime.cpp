#include <QLoggingCategory>

#include "datetime.h"

Q_LOGGING_CATEGORY(lcDateTime, "lcDateTime")

DateTime::DateTime(QObject *parent)
    : QObject{parent}
    , m_dateTime(QDateTime::currentDateTime())
    , m_formattedDateTime("hh:mm dd.MM.yyyy.") {
    initializeTimer();
}

DateTime::~DateTime() {
    m_timer->deleteLater();
}

DateTime *DateTime::instance() {
    static DateTime *inst;
    if(inst == nullptr) {
        inst = new DateTime();
    }
    return inst;
}

QObject *DateTime::singletonProvider(QQmlEngine *, QJSEngine *) {

    return DateTime::instance();
}

QString DateTime::formatted() const {
    return m_formattedDateTime;
}

void DateTime::setFormatted(const QString &newFormattedDateTime) {
    if(m_formattedDateTime == newFormattedDateTime)
        return;
    m_formattedDateTime = newFormattedDateTime;
    qCDebug(lcDateTime) << m_formattedDateTime;
    emit formattedChanged();
}

void DateTime::initializeTimer() {
    m_timer = new QTimer(this);

    m_timer->setTimerType(Qt::VeryCoarseTimer);
    m_timer->setInterval(1000UL);
    m_timer->setSingleShot(false);
    QObject::connect(m_timer, &QTimer::timeout, this, &DateTime::timerTout);
    m_timer->start();
}

void DateTime::setCurrentDay() {
    QDate   date;
    int     day = date.currentDate().dayOfWeek();
    QString weekDay;

    switch(day) {
    case 1:
        weekDay = "pon";
        break;
    case 2:
        weekDay = "uto";
        break;
    case 3:
        weekDay = "sri";
        break;
    case 4:
        weekDay = "čet";
        break;
    case 5:
        weekDay = "pet";
        break;
    case 6:
        weekDay = "sub";
        break;
    case 7:
        weekDay = "ned";
        break;
    }
    m_currentDay = weekDay;
    emit currentDayChanged();
}

void DateTime::timerTout() {
    QDateTime curr     = QDateTime::currentDateTime();
    QString   formated = curr.toString("hh:mm dd.MM.yyyy");
    // qCDebug(lcDateTime) << formated;
    setFormatted(formated);
    setCurrentDay();
}

QString DateTime::currentDay() const {
    return m_currentDay;
}
