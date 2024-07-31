#pragma once
#include <QJSEngine>
#include <QKeyEvent>
#include <QObject>
#include <QQmlEngine>
#include <QTimer>
#include <QtQml>

class MouseEventSpy : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool logout READ logout NOTIFY logoutChanged FINAL)

  public:
    explicit MouseEventSpy(QObject *parent = nullptr);

    static MouseEventSpy *instance();
    static QObject       *singletonProvider(QQmlEngine *engine, QJSEngine *script);

    void initializeTimer();
    bool logout() const;

  public slots:
    void timerDone();

  signals:
    void logoutChanged();

  private:
    QTimer *mainTimer;
    int     timerDuration;
    bool    m_logout;

  protected:
    bool eventFilter(QObject *watched, QEvent *event);
};
