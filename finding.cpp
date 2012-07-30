#include "finding.h"

Finding::Finding(const QString& name, FindingType type)
{
    m_StringFindingName = name;
    m_Type = type;

}

Finding::~Finding()
{
    for(int i=0; i < m_ListSegmentations.size(); ++i)
    {
        delete m_ListSegmentations.value(i);
    }

    m_ListSegmentations.clear();
}


QString Finding::GetFindingTypeDescription(const FindingType& type)
{
    switch(type)
    {
    case TUMOR:
        return QString("Tumor");
    case NODE:
        return QString("Lymph Node");
    case METASTASIS:
        return QString("Metastasis");
    case REFERENCE:
        return QString("Reference");
    }

    return QString();
}

QString Finding::GetFindingTypeCssColor(const FindingType& type)
{
    switch(type)
    {
    case TUMOR:
        return QString("background-color: #dcf400");
    case NODE:
        return QString("background-color: #41ac63");
    case METASTASIS:
        return QString("background-color: #8eee8e");
    case REFERENCE:
        return QString("background-color: #df8265");
    }

    return QString();
}


Finding::FindingType Finding::GetFindingType()
{
    return m_Type;
}

void Finding::SetFindingName(const QString& name)
{
    m_StringFindingName = name;
}


const QString& Finding::GetFindingName()
{
    return m_StringFindingName;
}


QList<Segmentation*>* Finding::GetAllSegmentations()
{
    return &m_ListSegmentations;
}

QList<Segmentation*> Finding::GetSegmentations(const QDateTime &dateTime)
{
    QList<Segmentation*> resultList;

    for(int i=0; i < m_ListSegmentations.size(); ++i)
    {
        Segmentation* tempSegmentation = m_ListSegmentations.value(i);

        if(tempSegmentation->GetImageSeries()->GetImageSeriesDateTime() == dateTime)
            resultList.append(tempSegmentation);
    }

   return resultList;
}



bool Finding::AddSegmentation(Segmentation *segmentation)
{

    if(m_ListSegmentations.contains(segmentation))
        return false;


    m_ListSegmentations.prepend(segmentation);

    return true;
}

bool Finding::RemoveSegmentation(Segmentation* segmentation)
{
    if(!m_ListSegmentations.contains(segmentation))
        return false;

    m_ListSegmentations.removeOne(segmentation);

    return true;
}

