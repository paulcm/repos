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

    void SetReportID(int id);
    void SetReportName(const QString& name);
    void SetPatient(Patient* patient);

    int GetReportID();
    const QString& GetReportName();

    Patient* GetPatient();
    const QList<Finding*>& GetFindings();
    Finding* GetFinding(int findingID);

private:
    int m_ReportID;
    QString m_StringReportName;
    Patient* m_Patient;
    QList<Finding*> m_ListFindings;

    int m_FindingIDCounter;




};

#endif // REPORT_H
