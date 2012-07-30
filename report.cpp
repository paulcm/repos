#include "report.h"

Report::Report(const QString& name) :
    m_Patient(NULL)
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
        m_ListFindings.prepend(finding);
}

void Report::SetReportName(const QString& name)
{
    m_StringReportName = name;
}


void Report::SetPatient(Patient *patient)
{
    m_Patient = patient;
}


const QString& Report::GetReportName()
{
    return m_StringReportName;
}

Patient* Report::GetPatient()
{
    return m_Patient;
}

QList<Finding*>* Report::GetFindings()
{
    return &m_ListFindings;
}

Finding* Report::GetFinding(int idx)
{
    if(idx >= 0 && idx < m_ListFindings.size())
        return m_ListFindings.value(idx);

    else
        return NULL;
}

