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
    Finding(const QString& name);
    ~Finding();

    void SetFindingName(const QString& name);

    const QString& GetFindingName();

    QList<Segmentation*>* GetAllSegmentations();
    QList<Segmentation*> GetSegmentations(const QDateTime& dateTime);

    bool AddSegmentation(Segmentation* segmentation);
    bool RemoveSegmentation(Segmentation* segmentation);

private:
    QString m_StringFindingName;
    QList<Segmentation*> m_ListSegmentations;
};

#endif // FINDING_H
