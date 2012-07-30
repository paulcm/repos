#ifndef REPORT_H
#define REPORT_H

#include <QString>
#include <QList>
#include "patient.h"
#include "finding.h"

#include <QList>
#include "patient.h"
#include "finding.h"

class Report
{
public:
    Report(const QString& name);
    ~Report();

    void AddFinding(Finding* finding);

    void SetReportName(const QString& name);
    void SetPatient(Patient* patient);

    const QString& GetReportName();

    Patient* GetPatient();
    QList<Finding*>* GetFindings();
    Finding* GetFinding(int idx);

private:
    QString m_StringReportName;
    Patient* m_Patient;
    QList<Finding*> m_ListFindings;

};

#endif // REPORT_H
