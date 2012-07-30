#ifndef DICOMDB_H
#define DICOMDB_H

#include <QList>
#include "patient.h"

class DICOMDB
{
public:
    DICOMDB();
    ~DICOMDB();

    QList<Patient*>* GetPatients();
    Patient* GetPatient(int idx);

    void AddPatient(Patient* patient);

    Patient* GetPatientByName(const QString& name);

private:
    QList<Patient*> m_ListPatients;

    int m_PatientIDCounter;
};

#endif // DICOMDB_H
