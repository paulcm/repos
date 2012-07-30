#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QList>

#include "study.h"


class Patient
{
public:
    Patient(const QString& name, int age);
    ~Patient(void);

    int GetPatientID() const;
    int GetPatientAge() const;
    const QString& GetName() const;

    QList<Study*>* GetStudies();
    Study* GetStudy(int idx);

    void AddStudy(Study *study);

private:
    int m_PatientAge;

    QString m_StringPatientName;
    QList<Study*> m_ListStudies;
};

#endif // PATIENT_H
