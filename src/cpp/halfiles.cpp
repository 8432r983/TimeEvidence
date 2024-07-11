#include "halfiles.h"

HalFiles::HalFiles(QObject *parent)
    : QObject{parent} {
}

QString HalFiles::getEmployeesFilePath() const {
    return cPathData + cFnEmployees;
}

QString HalFiles::getHolidaysFilePath() const {
    return cPathData + cFnHolidays;
}

QString HalFiles::getSettingsFilePath() const {
    return cPathData + cFnSettings;
}
