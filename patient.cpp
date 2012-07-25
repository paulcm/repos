#include "patient.h"

Patient::Patient(const QString &name, int age) : m_PatientID(-1)
  ,m_StudyIDCounter(0)
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

void Patient::SetPatientID(int id)
{
    m_PatientID = id;
}

void Patient::AddStudy(Study* study)
{
    if(study)
    {
        study->SetStudyID(m_StudyIDCounter++);
        m_ListStudies.append(study);
    }
}

int Patient::GetPatientID() const
{
    return m_PatientID;
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

Study *Patient::GetStudy(int studyID)
{
    for(int i=0; i < m_ListStudies.size(); ++i)
    {
        if(m_ListStudies.at(i)->GetStudyID() == studyID)
            return m_ListStudies.at(i);
    }

    return NULL;
}
