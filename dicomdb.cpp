#include "dicomdb.h"

DICOMDB::DICOMDB() : m_PatientIDCounter(0)
{
}

DICOMDB::~DICOMDB()
{
    for(int i=0; i < m_ListPatients.size(); ++i)
    {
        delete m_ListPatients.value(i);
    }

    m_ListPatients.clear();
}

void DICOMDB::AddPatient(Patient *patient)
{
    if(patient)
        m_ListPatients.append(patient);
}

QList<Patient *> * DICOMDB::GetPatients()
{
    return &m_ListPatients;
}

Patient* DICOMDB::GetPatient(int idx)
{
    if(idx >= 0 && idx < m_ListPatients.size())
        return m_ListPatients.value(idx);
    else
        return NULL;
}


Patient* DICOMDB::GetPatientByName(const QString& name)
{
    for(int i=0; i < m_ListPatients.size(); ++i)
    {
        if(m_ListPatients.at(i)->GetName().compare(name) == 0)
            return m_ListPatients.value(i);
    }

    return NULL;
}
