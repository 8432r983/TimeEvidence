#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScreen>
#include <QSettings>
#include <QtGui/QFontDatabase>

#include "datetime.h"
#include "monthmodel.h"

#include "employeelistmodel.h"

#include "activity.h"
#include "holidaychecker.h"
#include "monthlogger.h"
/*----------------------------------------------------------------------------*/
void appQmlRegisterFonts() {
    /* Add fonts to application */
    QFontDatabase::addApplicationFont(":/fonts/segoeui.ttf");
    QFontDatabase::addApplicationFont(":/fonts/seguisym.ttf");

    /* Set default Font for the application in case we miss to set */
    QFont font("Segoe UI");
    font.setPixelSize(12);
    QGuiApplication::setFont(font);
}
/*----------------------------------------------------------------------------*/
void appQmlRegisterStyle(QScreen *screen) {
    int width  = screen->geometry().width();
    int height = screen->geometry().height();
    qDebug() << width << height;

    // clang-format off
    if((width == 800) && (height == 480)) {
        // 7 inches with low resolution
        qmlRegisterSingletonType(QUrl("qrc:/qml/Style/Style1.qml"), "Style", 1, 0, "Style");
        qDebug() << "Display type 1";
    } else if((width == 1024) && (height == 600)) {
        // 7.1 inches with high resolution
        qmlRegisterSingletonType(QUrl("qrc:/qml/Style/Style2.qml"), "Style", 1, 0, "Style");
        qDebug() << "Display type 2";
    } else if((width == 1280) && (height == 800)) {
        // 10.1 inches as Santaro or Christ 12"
        qmlRegisterSingletonType(QUrl("qrc:/qml/Style/Style3.qml"), "Style", 1, 0, "Style");
        qDebug() << "Display type 3";
    } else if((width == 1024) && (height == 768)) {
        // 12.1 inches as Santoka
        qmlRegisterSingletonType(QUrl("qrc:/qml/Style/Style4.qml"), "Style", 1, 0, "Style");
        qDebug() << "Display type 4";
    } else if((width == 1366) && (height == 768)) {
        // 15" CHE
        qmlRegisterSingletonType(QUrl("qrc:/qml/Style/Style5.qml"), "Style", 1, 0, "Style");
        qDebug() << "Display type 5";
    } else {
        // windows display
        qmlRegisterSingletonType(QUrl("qrc:/qml/Style/Style4.qml"), "Style", 1, 0, "Style");
        qDebug() << "Display type windows";
    }
    // clang-format on
}

int main(int argc, char *argv[]) {
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    appQmlRegisterFonts();
    appQmlRegisterStyle(app.primaryScreen());

    qmlRegisterType<MonthModel>("MonthModel", 1, 0, "MonthModel");

    qmlRegisterType<EmployeeListModel>("EmployeeListModel", 1, 0, "EmployeeListModel");

    qmlRegisterType<MonthLogger>("MonthLogger", 1, 0, "MonthLogger");

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("datetime", DateTime::instance());

    activity act;
    context->setContextProperty("activity", &act);

    HolidayChecker holidayChecker;
    context->setContextProperty("holidaycheck", &holidayChecker);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if(!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
