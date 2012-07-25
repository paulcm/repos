#include "report.h"

Report::Report(const QString& name) : m_ReportID(-1)
  ,m_Patient(NULL)
  ,m_FindingIDCounter(0)
{
    m_StringReportName = name;
}

Report::~Report()
{
    for(int i=0; i < m_ListFindings.size(); ++i)
    {
        delete m_ListFindings.value(i);
    }

    m_ListFindings.clear();
}

void Report::AddFinding(Finding* finding)
{
    if(finding)
    {
        finding->SetFindingID(m_FindingIDCounter++);
        m_ListFindings.append(finding);
    }

}

void Report::SetReportName(const QString& name)
{
    m_StringReportName = name;
}


void Report::SetReportID(int id)
{
    m_ReportID = id;
}

void Report::SetPatient(Patient *patient)
{
    m_Patient = patient;
}

int Report::GetReportID()
{
    return m_ReportID;
}

const QString& Report::GetReportName()
{
    return m_StringReportName;
}

Patient* Report::GetPatient()
{
    return m_Patient;
}

const QList<Finding*>& Report::GetFindings()
{
    return m_ListFindings;
}

Finding* Report::GetFinding(int findingID)
{
    for(int i=0; i < m_ListFindings.size(); ++i)
    {
        if(m_ListFindings.at(i)->GetFindingID() == findingID)
            return m_ListFindings.value(i);
    }

    return NULL;
}

