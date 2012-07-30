#ifndef FINDINGSWIDGET_H
#define FINDINGSWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "separator.h"
#include "nodecombobox.h"

#include "finding.h"
#include "editorwidget.h"

class FindingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FindingsWidget(QList<Finding *> *findings, QWidget *parent = 0);
    ~FindingsWidget();
    
    void UpdateFindingsNameListNodeComboBox(Finding* currentFinding);
    void UpdateSegmentationNameListNodeComboBox(Finding* currentFinding, Segmentation* currentSegmentation);

    void SetFindings(QList<Finding*>* findings);

    void EnableEditor(const QString& findingType, const QString& cssColor);
    void DisableEditor();

signals:
    void SignalChangeFinding(const QString& name);
    void SignalCreateNewFinding(const QString& name);
    void SignalRenameFinding(const QString& oldname, const QString& newname);
    void SignalDeleteFinding(const QString& name);

    void SignalChangeSegmentation(const QString& name);
    void SignalCreateNewSegmentation(const QString& name);
    void SignalRenameSegmentation(const QString& oldname, const QString& newname);
    void SignalDeleteSegmentation(const QString& name);

public slots:
    
protected:
    QGridLayout* GetLayout();
    QLabel* GetLabelSelectFinding();
    QLabel* GetLabelSelectSegmentation();
    NodeComboBox* GetNodeComboBoxSelectFinding();
    NodeComboBox* GetNodeComboBoxSelectSegmentation();
    EditorWidget* GetEditorWidget();

    QList<QString>* UpdateFindingNamesList();
    QList<QString>* UpdateSegmentationNamesList(Finding* finding, QDateTime studyDate);

    void InitializeWidget();


private:
    QGridLayout* m_Layout;
    QLabel* m_LabelSelectFinding;
    QLabel* m_LabelSelectSegmentation;
    NodeComboBox* m_NodeComboBoxSelectFinding;
    NodeComboBox* m_NodeComboBoxSelectSegmentation;
    EditorWidget* m_EditorWidget;

    QList<Finding*>* m_FindingsPtr;
    QList<QString> m_ListFindingNames;

    QList<Segmentation*>* m_SegmentationPtr;
    QList<QString> m_ListSegmentationNames;


};

#endif // FINDINGSWIDGET_H
