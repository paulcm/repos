#ifndef FINDING_H
#define FINDING_H

#include <QString>
#include <QList>
#include "segmentation.h"
#include "imageseries.h"
#include <QMap>

class Finding
{
public:
    Finding(const QString& name);
    ~Finding();

    void SetFindingID(int id);

    int GetFindingID();
    const QString& GetFindingName();
    QList<Segmentation*> GetAllSegmentations() const;

    Segmentation* GetSegmentation(ImageSeries* series) const;

    bool AddSegmentation(ImageSeries* series, Segmentation* segmentation);
    bool RemoveSegmentation(ImageSeries* series);

private:
    int m_FindingID;
    QString m_StringFindingName;

    QMap<ImageSeries*,Segmentation*> m_MapSegmentations;
};

#endif // FINDING_H
