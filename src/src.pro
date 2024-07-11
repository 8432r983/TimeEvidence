QT += quick quickcontrols2   network  concurrent

TARGET = TimeEvidence

CONFIG += c++1z

# The following define makes your compiler emit warnings if you use any Qt feature
# that has been marked deprecated (the exact warnings depend on your compiler).
# Refer to the documentation for the deprecated API to know how to port your code
# away from it.

# DEFINES += QT_DEPRECATED_WARNINGS
# DEFINES += QT_NO_DEBUG_OUTPUT
# DEFINES += QT_NO_INFO_OUTPUT
# DEFINES += QT_NO_WARNING_OUTPUT
# DEFINES += QT_QML_DEBUG_NO_WARNING

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# disables all the APIs deprecated before Qt 6.0.0
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

win32 {
  #DEFINES += WIN_ADR
  DEFINES += WIN_MAR
}
unix {
  DEFINES += GUF_ROKO_0700
  #DEFINES += CHE_DUNF_0310
}

include(src.pri)


RC_ICONS = TimeEvidence.ico

SOURCES   +=
HEADERS   +=
RESOURCES += \
    fonts.qrc \
    qml.qrc \
    qt_conf.qrc

TRANSLATIONS +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD/src\
                   $$PWD/qml/Style\
# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# if we complie forms we need to check
QTQUICK_COMPILER_SKIPPED_RESOURCES +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /usr/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES += \
