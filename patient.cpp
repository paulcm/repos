#include "patient.h"

Patient::Patient(const QString &name, int age)
{
    m_PatientAge = age;
    m_StringPatientName = name;
}

Patient::~Patient()
{
    for(int i=0; i < m_ListStudies.size(); ++i)
        delete m_ListStudies.value(i);

    m_ListStudies.clear();
}


void Patient::AddStudy(Study* study)
{
    if(study)
    {
        for(int i=0; i < m_ListStudies.size(); ++i)
        {
            if(study->GetStudyDateTime() < m_ListStudies.at(i)->GetStudyDateTime())
            {
                m_ListStudies.insert(i,study);
                return;
            }
        }
        m_ListStudies.append(study);
    }
}

int Patient::GetPatientAge() const
{
    return m_PatientAge;
}

const QString& Patient::GetName() const
{
    return m_StringPatientName;
}

QList<Study *>* Patient::GetStudies()
{
    return &m_ListStudies;
}

Study *Patient::GetStudy(int idx)
{
    if(idx >= 0 && idx < m_ListStudies.size())
        return m_ListStudies.value(idx);
    else
        return NULL;

}
