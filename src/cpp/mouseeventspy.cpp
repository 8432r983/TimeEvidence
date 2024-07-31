#include <QDebug>
#include <QEvent>
#include <QGuiApplication>
#include <QJSEngine>
#include <QKeyEvent>
#include <QQmlEngine>
#include <QSettings>

#include "halfiles.h"
#include "mouseeventspy.h"

Q_LOGGING_CATEGORY(lcMouseSpy, "lcMouseSpy")

MouseEventSpy::MouseEventSpy(QObject *parent)
    : QObject(parent) {
    qDebug(lcMouseSpy) << "Constructor....";
    initializeTimer();
}

// This implements the SINGLETON PATTERN (*usually evil*)
// so you can get the instance in C++
MouseEventSpy *MouseEventSpy::instance() {
    static MouseEventSpy *inst;
    if(inst == nullptr) {
        /* If no instance has been created yet,creat a new and install
         * it as event filter. Uppon first use of the instance, it will
         * automatically install itself in the QGuiApplication */
        inst                 = new MouseEventSpy();
        QGuiApplication *app = qGuiApp;
        app->installEventFilter(inst);
    }
    return inst;
}

// This is the method to fullfill the signature required by
// qmlRegisterSingletonType.
QObject *MouseEventSpy::singletonProvider(QQmlEngine *, QJSEngine *) {
    return MouseEventSpy::instance();
}

void MouseEventSpy::initializeTimer() {
    HalFiles hf;

    const QString cGroupId       = "AppSettingsGeneral";
    const QString cTimerDuration = "timerDuration";

    QSettings settings(hf.getSettingsFilePath(), QSettings::IniFormat, this);
    settings.beginGroup(cGroupId);

    timerDuration = settings.value(cTimerDuration, 0).toInt();

    mainTimer = new QTimer(this);
    connect(mainTimer, &QTimer::timeout, this, timerDone);
    mainTimer->start(1000 * timerDuration);

    settings.endGroup();
}

void MouseEventSpy::timerDone() {
    m_logout = true;
    emit logoutChanged();
}

// This is the method is necessary for 'installEventFilter'
bool MouseEventSpy::eventFilter(QObject *watched, QEvent *event) {
    QEvent::Type t = event->type();

    if(t == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        if(mouseEvent->buttons() == Qt::LeftButton) {
            mainTimer->start(1000 * timerDuration);
            m_logout = false;
            emit logoutChanged();
        }
        return QObject::eventFilter(watched, event);
    }
    return QObject::eventFilter(watched, event);
}

bool MouseEventSpy::logout() const {
    return m_logout;
}
