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

    void SetPatientID(int id);

    int GetPatientID() const;
    int GetPatientAge() const;
    const QString& GetName() const;

    QList<Study*>* GetStudies();
    Study* GetStudy(int studyID);

    void AddStudy(Study *study);

private:
    int m_PatientID;
    int m_PatientAge;

    QString m_StringPatientName;
    QList<Study*> m_ListStudies;

    int m_StudyIDCounter;

};

#endif // PATIENT_H
