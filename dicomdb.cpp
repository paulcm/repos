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
    {
        patient->SetPatientID(m_PatientIDCounter++);
        m_ListPatients.append(patient);
    }
}

QList<Patient *> * DICOMDB::GetPatients()
{
    return &m_ListPatients;
}

const Patient* DICOMDB::GetPatient(int patientID) const
{
    for(int i=0; i < m_ListPatients.size(); ++i)
    {
        if(m_ListPatients.at(i)->GetPatientID() == patientID)
            return m_ListPatients.at(i);
    }

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
