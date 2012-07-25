#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <QString>
#include "study.h"

class Segmentation
{
public:
    Segmentation(const QString& name, Study* study);
    ~Segmentation();

    const QString& GetSegmentationName() const;
    Study* GetStudy() const;

private:
    QString m_StringSegmentationName;
    Study* m_Study;
};

#endif // SEGMENTATION_H
