#include "dateranges.h"
#include "halfiles.h"
#include "holidaychecker.h"
#include <QDebug>
#include <QFile>
#include <QSettings>

DateRanges::DateRanges(QObject *parent)
    : QObject{parent} {
    loadRanges();
}

void DateRanges::loadRanges() {
    HalFiles hf;

    const QString cGroupId             = "AppSettingsGeneral";
    const QString cVacationRangeLower  = "vacationRangeLower";
    const QString cVacationRangeUpper  = "vacationRangeUpper";
    const QString cValidSickdayLower   = "validSickdayRangeLower";
    const QString cValidSickdayUpper   = "validSickdayRangeUpper";
    const QString cInvalidSickdayLower = "invalidSickdayRangeLower";
    const QString cInvalidSickdayUpper = "invalidSickdayRangeUpper";

    QSettings settings(hf.getSettingsFilePath(), QSettings::IniFormat, this);
    settings.beginGroup(cGroupId);

    int vacationLowerBound  = settings.value(cVacationRangeLower, 0).toInt();
    int vacationUpperBound  = settings.value(cVacationRangeUpper, 0).toInt();
    int validSickdayLower   = settings.value(cValidSickdayLower, 0).toInt();
    int validSickdayUpper   = settings.value(cValidSickdayUpper, 0).toInt();
    int invalidSickdayLower = settings.value(cInvalidSickdayLower, 0).toInt();
    int invalidSickdayUpper = settings.value(cInvalidSickdayUpper, 0).toInt();

    settings.endGroup();

    m_lowerVacationBound       = calcWorkDays(vacationLowerBound);
    m_upperVacationBound       = calcWorkDays(vacationUpperBound);
    m_lowerValidSickdayBound   = calcWorkDays(validSickdayLower);
    m_upperValidSickdayBound   = calcWorkDays(validSickdayUpper);
    m_lowerInvalidSickdayBound = calcWorkDays(invalidSickdayLower);
    m_upperInvalidSickdayBound = calcWorkDays(invalidSickdayUpper);

    emit lowerVacationBoundChanged();
    emit upperVacationBoundChanged();
    emit lowerValidSickdayBoundChanged();
    emit upperValidSickdayBoundChanged();
    emit lowerInvalidSickdayBoundChanged();
    emit upperInvalidSickdayBoundChanged();
}

QDate DateRanges::calcWorkDays(int bound) {
    bool  isNeg = (bound < 0);
    QDate today = QDate::currentDate();

    HolidayChecker hch;

    bound = abs(bound);
    while(bound > 0) {
        if(isNeg)
            today = today.addDays(-1);
        else
            today = today.addDays(1);

        if(today.dayOfWeek() != 6 && today.dayOfWeek() != 7 && !hch.holidayCheck(today)) {
            bound--;
        }
    }

    return today;
}

int DateRanges::dateDist(QDate dateA, QDate dateB) {
    int  res       = 0;
    bool isSmaller = (dateA < dateB);

    HolidayChecker hch;

    if(dateA.dayOfWeek() != 6 && dateA.dayOfWeek() != 7 && !hch.holidayCheck(dateA)) {
        res++;
    }

    while(dateA != dateB) {
        if(isSmaller)
            dateA = dateA.addDays(1);
        else
            dateA = dateA.addDays(-1);

        if(dateA.dayOfWeek() != 6 && dateA.dayOfWeek() != 7 && !hch.holidayCheck(dateA)) {
            res++;
        }
    }

    return res;
}

QDate DateRanges::lowerVacationBound() const {
    return m_lowerVacationBound;
}

QDate DateRanges::upperVacationBound() const {
    return m_upperVacationBound;
}

QDate DateRanges::lowerValidSickdayBound() const {
    return m_lowerValidSickdayBound;
}

QDate DateRanges::upperValidSickdayBound() const {
    return m_upperValidSickdayBound;
}

QDate DateRanges::lowerInvalidSickdayBound() const {
    return m_lowerInvalidSickdayBound;
}

QDate DateRanges::upperInvalidSickdayBound() const {
    return m_upperInvalidSickdayBound;
}
