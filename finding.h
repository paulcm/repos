#ifndef FINDING_H
#define FINDING_H

#include <QString>
#include <QList>
#include "segmentation.h"
#include "imageseries.h"
#include <QMap>
#include <QDateTime>

class Finding
{
public:
    enum FindingType
    {
        TUMOR = 0,
        NODE = 1,
        METASTASIS = 2,
        REFERENCE = 3
    };

    static QString GetFindingTypeDescription(const FindingType& type);
    static QString GetFindingTypeCssColor(const FindingType& type);

    Finding(const QString& name, FindingType type);
    ~Finding();

    void SetFindingName(const QString& name);
    FindingType GetFindingType();

    const QString& GetFindingName();

    QList<Segmentation*>* GetAllSegmentations();
    QList<Segmentation*> GetSegmentations(const QDateTime& dateTime);

    bool AddSegmentation(Segmentation* segmentation);
    bool RemoveSegmentation(Segmentation* segmentation);

private:
    QString m_StringFindingName;
    QList<Segmentation*> m_ListSegmentations;
    FindingType m_Type;
};

#endif // FINDING_H
