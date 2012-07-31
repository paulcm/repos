#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTableWidgetItem>
#include <QInputDialog>
#include <QSpinBox>

#include <iostream>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  ,m_SelectedReport(NULL)
  ,m_SelectedPatient(NULL)
  ,m_SelectedFinding(NULL)
  ,m_SelectedSegmentation(NULL)
  ,m_SelectedStudy(NULL)
  ,m_DockWidgetModule(NULL)
  ,m_Splitter(NULL)
  ,m_LabelSlicerLogo(NULL)
  ,m_WidgetTop(NULL)
  ,m_WidgetBottom(NULL)
  ,m_ReportSelectionWidget(NULL)
  ,m_ImageSeriesSelectionWidget(NULL)
  ,m_FindingsWidget(NULL)
  ,m_AnalysisWidget(NULL)
  ,m_ReportTree(NULL)
  ,m_StudySliderWidget(NULL)
  ,m_FindingsColorMapDialog(NULL)
{
    this->setStyleSheet("background-color:#fff");

//    Study* test1 = new Study(Study::CTPET,QDateTime::currentDateTime().addDays(1));
//    test1->SetStudyID(111);
//    m_Studies.insert(test1->GetStudyDateTime(),test1);

//    Study* test2 = new Study(Study::CTPET,QDateTime::currentDateTime().addDays(7));
//    test2->SetStudyID(12);
//    m_Studies.insert(test2->GetStudyDateTime(),test2);

//    Study* test3 = new Study(Study::CTPET,QDateTime::currentDateTime().addDays(12));
//    test3->SetStudyID(3);
//    m_Studies.insert(test3->GetStudyDateTime(),test3);

    this->InitializeDICOMDB();

    this->InitializeMainWindow();


    //this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete m_DicomDB;
}

void MainWindow::InitializeMainWindow()
{
    this->addDockWidget(Qt::LeftDockWidgetArea,this->GetDockWidgetModule(),Qt::Vertical);
}


void MainWindow::InitializeDICOMDB()
{

    m_DicomDB = new DICOMDB();

    Patient* peter = new Patient("Peter Pattern",42);
    QDateTime currentDateTime;
    currentDateTime.setDate(QDate::currentDate());
    currentDateTime.setTime(QTime::currentTime());

    Study* peterbaseline = new Study(Study::CTPET,currentDateTime);
    Study* peterfollowup1 = new Study(Study::CTPET,currentDateTime.addMonths(3));
    Study* peterfollowup2 = new Study(Study::CTPET,currentDateTime.addMonths(4));

    peter->AddStudy(peterbaseline);
    peter->AddStudy(peterfollowup1);
    peter->AddStudy(peterfollowup2);

    m_DicomDB->AddPatient(peter);

    Patient* cam = new Patient("Cameron Camouflage",62);


    currentDateTime.addDays(56);
    Study* baseline = new Study(Study::CTPET,currentDateTime);
    Study* followup1 = new Study(Study::CTPET,currentDateTime.addMonths(3));
    Study* followup2 = new Study(Study::CTPET,currentDateTime.addMonths(4));

    cam->AddStudy(baseline);
    cam->AddStudy(followup1);
    cam->AddStudy(followup2);

    m_DicomDB->AddPatient(cam);

}

QList<CategoryButton*> MainWindow::GetListCategoryButtons()
{
    if(m_ListCategoryButtons.isEmpty())
    {
        m_ListCategoryButtons.append(new CategoryButton("Reports",this));
        m_ListCategoryButtons.append(new CategoryButton("Image Series",this));
        m_ListCategoryButtons.append(new CategoryButton("Findings",this));
        m_ListCategoryButtons.append(new CategoryButton("Analysis",this));
    }

    return m_ListCategoryButtons;
}


QDockWidget* MainWindow::GetDockWidgetModule()
{
    if(m_DockWidgetModule == NULL)
    {
        m_DockWidgetModule = new QDockWidget(this);
        m_DockWidgetModule->setFeatures(QDockWidget::NoDockWidgetFeatures);
        m_DockWidgetModule->setFixedWidth(380);

        if(m_DockWidgetModule->widget() == NULL)
            m_DockWidgetModule->setWidget(new QWidget(m_DockWidgetModule));

        m_DockWidgetModule->widget()->setLayout(new QVBoxLayout());
        m_DockWidgetModule->widget()->layout()->setMargin(0);
        m_DockWidgetModule->widget()->layout()->setSpacing(8);

        m_DockWidgetModule->setTitleBarWidget(this->GetLabelSlicerLogo());

        m_DockWidgetModule->widget()->layout()->addWidget(this->GetSplitter());
    }

    return m_DockWidgetModule;
}

QLabel* MainWindow::GetLabelSlicerLogo()
{
    if(m_LabelSlicerLogo == NULL)
    {
        m_LabelSlicerLogo = new QLabel(this);
        m_LabelSlicerLogo->setAlignment(Qt::AlignLeft);
        m_LabelSlicerLogo->setPixmap(QPixmap(":/resources/slicer_logo.png"));
        m_LabelSlicerLogo->setMargin(5);
    }

    return m_LabelSlicerLogo;
}

QSplitter* MainWindow::GetSplitter()
{
    if(m_Splitter == NULL)
    {
        m_Splitter = new QSplitter(Qt::Vertical,this);
        m_Splitter->insertWidget(0,this->GetWidgetTop());
        m_Splitter->insertWidget(1,this->GetWidgetBottom());
        m_Splitter->setStretchFactor(0,2);
        m_Splitter->setStretchFactor(1,0);
    }

    return m_Splitter;
}

QWidget* MainWindow::GetWidgetTop()
{
    if(m_WidgetTop == NULL)
    {
        m_WidgetTop = new QWidget(this);
        m_WidgetTop->setLayout(new QVBoxLayout());

        m_WidgetTop->layout()->addWidget(this->GetListCategoryButtons().at(0));
        m_WidgetTop->layout()->addWidget(this->GetReportSelectionWidget());

        m_WidgetTop->layout()->addWidget(this->GetListCategoryButtons().at(1));
        m_WidgetTop->layout()->addWidget(this->GetImageSeriesSelectionWidget());

        m_WidgetTop->layout()->addWidget(this->GetListCategoryButtons().at(2));
        m_WidgetTop->layout()->addWidget(this->GetFindingsWidget());

        m_WidgetTop->layout()->addWidget(this->GetListCategoryButtons().at(3));
        m_WidgetTop->layout()->addWidget(this->GetAnalysisWidget());

        m_WidgetTop->layout()->addItem(new QSpacerItem(20,1,QSizePolicy::Minimum,QSizePolicy::Expanding));
    }

    return m_WidgetTop;
}

QWidget* MainWindow::GetWidgetBottom()
{
    if(m_WidgetBottom == NULL)
    {
        m_WidgetBottom = new QWidget(this);
        m_WidgetBottom->setLayout(new QVBoxLayout());

        m_WidgetBottom->layout()->addWidget(this->GetStudySliderWidget());
        m_WidgetBottom->layout()->addWidget(this->GetReportTree());

        m_WidgetBottom->layout()->addItem(new QSpacerItem(20,1,QSizePolicy::Minimum,QSizePolicy::Expanding));
    }

    return m_WidgetBottom;
}

StudySliderWidget* MainWindow::GetStudySliderWidget()
{
    if(m_StudySliderWidget == NULL)
    {
        m_StudySliderWidget = new StudySliderWidget(this);

        connect(m_StudySliderWidget, SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));
    }

    return m_StudySliderWidget;
}


FindingsColorMapDialog* MainWindow::GetFindingsColorMapDialog()
{
    if(m_FindingsColorMapDialog == NULL)
    {
        m_FindingsColorMapDialog = new FindingsColorMapDialog(this);
    }

    return m_FindingsColorMapDialog;
}


ReportSelectionWidget* MainWindow::GetReportSelectionWidget()
{
    if(m_ReportSelectionWidget == NULL)
    {
        m_ReportSelectionWidget = new ReportSelectionWidget(&m_Reports,this);

        connect(m_ReportSelectionWidget, SIGNAL(SignalCreateNewReport(QString)), this, SLOT(SlotReportCreate(QString)) );
        connect(m_ReportSelectionWidget, SIGNAL(SignalChangeReport(QString)), this, SLOT(SlotReportChange(QString)) );
        connect(m_ReportSelectionWidget, SIGNAL(SignalRenameReport(QString,QString)), this, SLOT(SlotReportRename(QString,QString)) );
        connect(m_ReportSelectionWidget, SIGNAL(SignalDeleteReport(QString)), this, SLOT(SlotReportDelete(QString)) );

    }
    return m_ReportSelectionWidget;
}

ImageSeriesSelectionWidget* MainWindow::GetImageSeriesSelectionWidget()
{
    if(m_ImageSeriesSelectionWidget == NULL)
    {
        m_ImageSeriesSelectionWidget = new ImageSeriesSelectionWidget(m_DicomDB->GetPatients(), this);

        connect(m_ImageSeriesSelectionWidget, SIGNAL(SignalPatientChanged(QString)), this, SLOT(SlotImageSelectionPatientChanged(QString)) );
        connect(m_ImageSeriesSelectionWidget, SIGNAL(SignalStudySelected(int,bool)), this, SLOT(SlotImageSelectionStudySelected(int,bool)) );

    }

    return m_ImageSeriesSelectionWidget;
}

FindingsWidget* MainWindow::GetFindingsWidget()
{
    if(m_FindingsWidget == NULL)
    {
        std::cout << "Try to instanciate Findings Widget" << std::endl;
        if(m_SelectedReport == NULL)
            m_FindingsWidget = new FindingsWidget(NULL, this);
        else
            m_FindingsWidget = new FindingsWidget(m_SelectedReport->GetFindings(),this);

        connect(m_FindingsWidget, SIGNAL(SignalCreateNewFinding(QString)), this, SLOT(SlotFindingCreate(QString)) );
        connect(m_FindingsWidget, SIGNAL(SignalChangeFinding(QString)), this, SLOT(SlotFindingChange(QString)) );
        connect(m_FindingsWidget, SIGNAL(SignalRenameFinding(QString,QString)), this, SLOT(SlotFindingRename(QString,QString)) );
        connect(m_FindingsWidget, SIGNAL(SignalDeleteFinding(QString)), this, SLOT(SlotFindingDelete(QString)) );

        connect(m_FindingsWidget, SIGNAL(SignalCreateNewSegmentation(QString)), this, SLOT(SlotSegmentationCreate(QString)) );
        connect(m_FindingsWidget, SIGNAL(SignalChangeSegmentation(QString)), this, SLOT(SlotSegmentationChange(QString)) );
        connect(m_FindingsWidget, SIGNAL(SignalRenameSegmentation(QString,QString)), this, SLOT(SlotSegmentationRename(QString,QString)) );
        connect(m_FindingsWidget, SIGNAL(SignalDeleteSegmentation(QString)), this, SLOT(SlotSegmentationDelete(QString)) );

    }

    return m_FindingsWidget;
}

AnalysisWidget* MainWindow::GetAnalysisWidget()
{
    if(m_AnalysisWidget == NULL)
    {
        m_AnalysisWidget = new AnalysisWidget(this);

        connect(m_AnalysisWidget, SIGNAL(SignalShowReportSummaryDialog()), this, SLOT(SlotAnaylsisShowReportSummaryDialog()) );
        connect(m_AnalysisWidget, SIGNAL(SignalAddStudyToView(int)), this, SLOT(SlotAnalysisAddStudy(int)) );
        connect(m_AnalysisWidget, SIGNAL(SignalRemoveStudyFromView(int)), this, SLOT(SlotAnaylsisRemoveStudy(int)) );
        connect(m_AnalysisWidget, SIGNAL(SignalQualitativeSelected()), this, SLOT(SlotAnalysisQualitativeSelected()) );
        connect(m_AnalysisWidget, SIGNAL(SignalQuantitativeSelected()), this, SLOT(SlotAnalysisQuantitativeSelected()) );


    }

    return m_AnalysisWidget;
}

ReportTree* MainWindow::GetReportTree()
{
    if(m_ReportTree == NULL)
    {
        m_ReportTree = new ReportTree(this);

        connect(m_ReportTree, SIGNAL(SignalItemSelected(QString)), this, SLOT(SlotReportTreeClicked(QString)) );
    }

    return m_ReportTree;
}

void MainWindow::SlotReportTreeClicked(const QString& positionCode)
{
    if(!m_SelectedReport)
        return;

    Finding* tempFinding = NULL;

    for(int i=0; i < positionCode.length(); ++i)
    {
        bool ok;

        if(i == 0)
        {
            int findingID = positionCode.left(1).toInt(&ok);

            if(ok && findingID < m_SelectedReport->GetFindings()->size())
            {
                tempFinding = m_SelectedReport->GetFinding(findingID);
                this->SetSelectedFinding(tempFinding,false,false);
            }
        }
        else if(i == 1)
        {
            int segmentationID = positionCode.right(1).toInt(&ok);

            if(tempFinding && ok && segmentationID < tempFinding->GetAllSegmentations()->size())
                this->SetSelectedSegmentation(tempFinding->GetAllSegmentations()->value(segmentationID),false,false,false);
        }
    }

    disconnect(this->GetStudySliderWidget(), SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));


    if(m_SelectedSegmentation)
    {
        int idx = -1;
        QDateTime tempDT;
        Study* tempStudy = NULL;
        for(int j=0; j < this->GetCurrentPatientsSelectedStudies().size(); ++j)
        {
            if(this->GetCurrentPatientsSelectedStudies().at(j)->GetStudyDateTime() == m_SelectedSegmentation->GetImageSeries()->GetImageSeriesDateTime())
            {
                idx = j;
                tempStudy = this->GetCurrentPatientsSelectedStudies().value(j);
                tempDT = m_SelectedSegmentation->GetImageSeries()->GetImageSeriesDateTime();
                break;
            }
        }
        if(tempStudy)
        {
            disconnect(this->GetStudySliderWidget(), SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));
            this->GetStudySliderWidget()->UpdateValues(this->GetCurrentPatientsSelectedStudies().size()-1,this->GetCurrentPatientsSelectedStudies().indexOf(tempStudy),m_SelectedSegmentation->GetImageSeries()->GetDateTimeStr());
            connect(this->GetStudySliderWidget(), SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));
        }
    }
}

void MainWindow::SlotImageSelectionPatientChanged(const QString& name)
{
    if(m_SelectedReport == NULL)
    {
        QMessageBox::warning(NULL,"Select Patient","A Report must be selected in order to select a Patient");
        this->GetImageSeriesSelectionWidget()->UpdatePatientsNamesListNodeComboBox(NULL);
        return;
    }

    Patient* tempPatient = m_DicomDB->GetPatientByName(name);

    if(tempPatient == m_SelectedPatient)
        return;

    this->SetSelectedPatient(tempPatient);

}

QList<Study*> MainWindow::GetCurrentPatientsSelectedStudies()
{
    QList<Study*> resultList;

    if(m_SelectedPatient != NULL)
    {
        for(int i=0; i < m_SelectedPatient->GetStudies()->size();++i)
        {
            if(m_AllSelectedStudies.contains(m_SelectedPatient->GetStudies()->at(i)))
            {
                resultList.append(m_SelectedPatient->GetStudies()->value(i));
            }
        }
    }

    return resultList;
}

QList<QString> MainWindow::GetCurrentPatientsSelectedStudyDates()
{
    QList<Study*> tempStudyList = this->GetCurrentPatientsSelectedStudies();
    QList<QString> resultList;

    for(int i=0; i < tempStudyList.size(); ++i)
    {
        resultList.append(tempStudyList.at(i)->GetDateTimeStr());
    }

    return resultList;
}

bool MainWindow::RemoveCurrentReportsSegmentationsForStudy(Study* study)
{
    bool triggeredOnce = false;
    int ret = QMessageBox::Cancel;

    if(m_SelectedReport && m_SelectedPatient && m_SelectedFinding && m_SelectedStudy)
    {
        for(int i=0; i < m_SelectedReport->GetFindings()->size(); ++i)
        {
            Finding* tempFinding = m_SelectedReport->GetFinding(i);

            for(int j=0; j < tempFinding->GetAllSegmentations()->size(); ++j)
            {
                Segmentation* tempSegmentation = tempFinding->GetAllSegmentations()->value(j);

                if(tempSegmentation->GetImageSeries() == study->GetImageSeries(ImageSeries::PET))
                {
                    if(triggeredOnce == false)
                    {
                        ret = QMessageBox::warning(NULL,"Study selection","All Segmentations belonging to this study will be removed from the Findings",QMessageBox::Ok,QMessageBox::Cancel);
                        triggeredOnce = true;
                    }
                    if(ret == QMessageBox::Ok)
                    {
                        QList<Segmentation*> tempCurrentFindingSegmentations = m_SelectedFinding->GetSegmentations(m_SelectedStudy->GetStudyDateTime());
                        Segmentation* nextSegmentation = NULL;
                        if(tempCurrentFindingSegmentations.contains(tempSegmentation))
                        {
                           int idx = tempCurrentFindingSegmentations.indexOf(tempSegmentation);
                           if(tempCurrentFindingSegmentations.size() == 2)
                               nextSegmentation = tempCurrentFindingSegmentations.value(0);
                           else
                               nextSegmentation = tempCurrentFindingSegmentations.value(--idx);

                        }
                        tempFinding->RemoveSegmentation(tempSegmentation);

                        if(tempCurrentFindingSegmentations.contains(tempSegmentation))
                            this->SetSelectedSegmentation(nextSegmentation);
                    }
                    else
                        return false;
                }
            }
        }
    }

    return true;
}

void MainWindow::SlotImageSelectionStudySelected(int idx, bool selected)
{
    disconnect(this->GetStudySliderWidget(), SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));

    QList<Study*> selectedPatientStudies = this->GetCurrentPatientsSelectedStudies();

    Study* tempStudy = m_SelectedPatient->GetStudy(idx);
    int oldidx = selectedPatientStudies.indexOf(tempStudy);

    if(!selected)
    {
        bool cont = this->RemoveCurrentReportsSegmentationsForStudy(tempStudy);

        if(!cont)
        {
            this->GetImageSeriesSelectionWidget()->UndoTableRowCheck(idx);
            connect(this->GetStudySliderWidget(), SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));

            return;
        }

        m_AllSelectedStudies.removeOne(tempStudy);
    }
    else
        m_AllSelectedStudies.append(tempStudy);


    selectedPatientStudies = this->GetCurrentPatientsSelectedStudies();
    int newidx = selectedPatientStudies.indexOf(tempStudy);

    if(selected)
    {
        this->SetSelectedStudy(tempStudy);

        if(selectedPatientStudies.size() > 1)
            this->GetStudySliderWidget()->UpdateValues(selectedPatientStudies.size()-1,newidx,tempStudy->GetDateTimeStr());
        else
            this->GetStudySliderWidget()->UpdateValues(0,0,tempStudy->GetDateTimeStr());

    }
    else
    {
        if(selectedPatientStudies.empty())
        {
            this->SetSelectedStudy(NULL);
            this->GetStudySliderWidget()->UpdateValues();
        }
        else
        {
            this->SetSelectedStudy(selectedPatientStudies.value(--oldidx));
            this->GetStudySliderWidget()->UpdateValues(selectedPatientStudies.size()-1,oldidx,selectedPatientStudies.at(oldidx)->GetDateTimeStr());
        }
    }

    QStringList input;
    for(int i=0; i < selectedPatientStudies.size();++i)
    {
        input.append(selectedPatientStudies.at(i)->GetDateTimeStr());
    }

    this->GetAnalysisWidget()->UpdateStudiesList(input);


    connect(this->GetStudySliderWidget(), SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));
}



void MainWindow::SlotChangeStudyInView(int idx)
{
    this->SetSelectedStudy(this->GetCurrentPatientsSelectedStudies().value(idx));
}


void MainWindow::UpdateTree()
{
    QList<ReportTree::TreeInput> inputList;

    if(m_SelectedReport && m_SelectedStudy)
    {
        QList<Finding*>* tempFindings = m_SelectedReport->GetFindings();

        for(int i=0; i < tempFindings->size(); ++i)
        {
            QList<Segmentation*>* tempSegmentations = tempFindings->at(i)->GetAllSegmentations();

            ReportTree::TreeInput input;
            input.findingName = tempFindings->at(i)->GetFindingName();

            for(int j=0; j < tempSegmentations->size(); ++j)
            {
                input.segmentationNames.append(tempSegmentations->at(j)->GetImageSeries()->GetDateStr() + " | " +tempSegmentations->at(j)->GetSegmentationName());
            }

            inputList.append(input);
        }
    }

    this->GetReportTree()->UpdateTree(inputList);
}


void MainWindow::SetSelectedReport(Report* report, bool renamed)
{
    if(report == m_SelectedReport && !renamed)
        return;

    m_SelectedReport = report;

    if(m_SelectedReport)
    {
        this->SetSelectedPatient(m_SelectedReport->GetPatient(),true);
        this->GetFindingsWidget()->SetFindings(m_SelectedReport->GetFindings());
    }
    else
    {
        this->SetSelectedPatient(NULL,true);
        this->GetFindingsWidget()->SetFindings(NULL);
    }

    this->GetReportSelectionWidget()->UpdateReportSelectorNodeComboBox(m_SelectedReport);
    this->UpdateTree();
}

void MainWindow::SetSelectedPatient(Patient* patient, bool reportChanged)
{


    if(patient == m_SelectedPatient && !reportChanged)
        return;

    m_SelectedPatient = patient;

    if(m_SelectedReport)
    {
        m_SelectedReport->SetPatient(m_SelectedPatient);

        if(m_SelectedReport->GetFindings()->isEmpty())
            this->GetImageSeriesSelectionWidget()->LockPatientSelection(false);
        else
            this->GetImageSeriesSelectionWidget()->LockPatientSelection(true);
    }


    if(m_SelectedPatient)
    {
        this->SetSelectedFinding(m_SelectedReport->GetFinding(0));
        this->GetImageSeriesSelectionWidget()->UpdateStudiesTable(m_SelectedPatient->GetStudies(),this->GetCurrentPatientsSelectedStudies());

        disconnect(this->GetStudySliderWidget(), SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));
        this->SetSelectedStudy(m_SelectedPatient->GetStudy(0));
        connect(this->GetStudySliderWidget(), SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));

    }
    else
    {
        this->SetSelectedFinding(NULL);
        QList<Study*> emptyListSelected;
        this->GetImageSeriesSelectionWidget()->UpdateStudiesTable(NULL,emptyListSelected);

        disconnect(this->GetStudySliderWidget(), SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));
        this->SetSelectedStudy(NULL);
        connect(this->GetStudySliderWidget(), SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));

    }


    this->GetImageSeriesSelectionWidget()->UpdatePatientsNamesListNodeComboBox(m_SelectedPatient);

}

void MainWindow::SetSelectedStudy(Study* study)
{
    if(study == m_SelectedStudy)
        return;

    m_SelectedStudy = study;

    QList<Study*> tempPatientSelectedStudies = this->GetCurrentPatientsSelectedStudies();
    int idx = tempPatientSelectedStudies.indexOf(study);

    disconnect(this->GetStudySliderWidget(), SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));

    if(m_SelectedFinding && m_SelectedStudy)
    {
        if(!m_SelectedFinding->GetSegmentations(m_SelectedStudy->GetStudyDateTime()).isEmpty())
            this->SetSelectedSegmentation(m_SelectedFinding->GetSegmentations(m_SelectedStudy->GetStudyDateTime()).value(0),true);
        else
            this->SetSelectedSegmentation(NULL,true);

    }


    if(m_SelectedStudy)
        this->GetStudySliderWidget()->UpdateValues(tempPatientSelectedStudies.size()-1,idx,study->GetDateTimeStr());

    else
        this->GetStudySliderWidget()->UpdateValues();


    connect(this->GetStudySliderWidget(), SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));

}

void MainWindow::SetSelectedFinding(Finding* finding, bool renamed, bool updateTree)
{
    if(finding == m_SelectedFinding && !renamed)
        return;

    m_SelectedFinding = finding;

    if(!m_SelectedFinding)
        this->GetFindingsWidget()->DisableEditor();
    else
        this->GetFindingsWidget()->EnableEditor(Finding::GetFindingTypeDescription(m_SelectedFinding->GetFindingType()),Finding::GetFindingTypeCssColor(m_SelectedFinding->GetFindingType()));



    if(m_SelectedFinding && ! m_SelectedFinding->GetSegmentations(m_SelectedStudy->GetStudyDateTime()).isEmpty())
        this->SetSelectedSegmentation(m_SelectedFinding->GetSegmentations(m_SelectedStudy->GetStudyDateTime()).value(0));
    else
        this->SetSelectedSegmentation(NULL);


    this->GetFindingsWidget()->UpdateFindingsNameListNodeComboBox(m_SelectedFinding);
    if(updateTree)
        this->UpdateTree();

}

void MainWindow::SetSelectedSegmentation(Segmentation* segmentation, bool sliderChanged, bool renamed, bool updateTree)
{
    if(segmentation == m_SelectedSegmentation && sliderChanged && !renamed)
        return;

    m_SelectedSegmentation = segmentation;

    if(m_SelectedSegmentation)
        this->GetFindingsWidget()->UpdateSegmentationNameListNodeComboBox(m_SelectedFinding, m_SelectedSegmentation);
    else if(m_SelectedFinding)
        this->GetFindingsWidget()->UpdateSegmentationNameListNodeComboBox(m_SelectedFinding, m_SelectedFinding->GetSegmentations(m_SelectedStudy->GetStudyDateTime()).value(0));
    else
        this->GetFindingsWidget()->UpdateSegmentationNameListNodeComboBox(NULL,NULL);

    if(updateTree)
        this->UpdateTree();
}



///// REPORT SLOTS

void MainWindow::SlotReportCreate(const QString& name)
{
    Report* report = new Report(name);

    m_Reports.prepend(report);

    this->SetSelectedReport(report);



    this->GetReportSelectionWidget()->UpdateReportSelectorNodeComboBox(m_SelectedReport);

    if(m_SelectedReport)
       std::cout << "Currently selected Report: " << m_SelectedReport->GetReportName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Report" << std::endl;
}

void MainWindow::SlotReportChange(const QString& name)
{
    Report* tempReport = this->GetReportByName(name);


    this->SetSelectedReport(tempReport);

    if(m_SelectedReport)
       std::cout << "Currently selected Report: " << m_SelectedReport->GetReportName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Report" << std::endl;
}

void MainWindow::SlotReportRename(const QString& oldname, const QString& newname)
{
    Report* tempReport = this->GetReportByName(oldname);

    if(tempReport == NULL)
        return;

    tempReport->SetReportName(newname);

    this->SetSelectedReport(tempReport,true);

    this->GetReportSelectionWidget()->UpdateReportSelectorNodeComboBox(m_SelectedReport);

    if(m_SelectedReport)
       std::cout << "Currently selected Report: " << m_SelectedReport->GetReportName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Report" << std::endl;
}

void MainWindow::SlotReportDelete(const QString& name)
{
    Report* tempReport = this->GetReportByName(name);
    int idx = m_Reports.indexOf(tempReport);

    if(tempReport != NULL)
    {
        m_Reports.removeOne(tempReport);
        delete tempReport;
    }

    if(idx > 0)
        this->SetSelectedReport(m_Reports.value(idx-1));
    else if(idx == 0 && !m_Reports.isEmpty())
        this->SetSelectedReport(m_Reports.value(0));
    else
        this->SetSelectedReport(NULL);

    this->GetReportSelectionWidget()->UpdateReportSelectorNodeComboBox(m_SelectedReport);

    if(m_SelectedReport)
       std::cout << "Currently selected Report: " << m_SelectedReport->GetReportName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Report" << std::endl;
}

Report* MainWindow::GetReportByName(const QString& name)
{
    for(int i=0; i < m_Reports.size(); ++i)
    {
        if(m_Reports.at(i)->GetReportName().compare(name) == 0)
            return m_Reports.at(i);
    }

    return NULL;
}


///// FINDING SLOTS

void MainWindow::SlotFindingCreate(const QString& name)
{
    if(m_SelectedReport == NULL)
    {
        QMessageBox::warning(NULL,"Create Finding","A Report must be selected in order to create a new Finding");
        return;
    }

    if(m_SelectedStudy == NULL)
    {
        QMessageBox::warning(NULL,"Create Finding","A Study must be selected in order to create a new Finding");
        return;
    }

    this->GetFindingsColorMapDialog()->SetApplied(false);
    this->GetFindingsColorMapDialog()->exec();

    if(this->GetFindingsColorMapDialog()->GetApplied())
    {

        Finding::FindingType type = Finding::FindingType(this->GetFindingsColorMapDialog()->GetSelectedLabelColor());

        Finding* finding = new Finding(name, type);
        m_SelectedReport->AddFinding(finding);
        this->GetImageSeriesSelectionWidget()->LockPatientSelection(true);

        this->SetSelectedFinding(finding);

        this->GetFindingsWidget()->EnableEditor(Finding::GetFindingTypeDescription(type),Finding::GetFindingTypeCssColor(type));

    }
    if(m_SelectedFinding)
       std::cout << "Currently selected Finding: " << m_SelectedFinding->GetFindingName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Finding" << std::endl;
 }

void MainWindow::SlotFindingChange(const QString& name)
{
    Finding* tempFinding = this->GetFindingByName(name);

    this->SetSelectedFinding(tempFinding);

    if(m_SelectedFinding)
       std::cout << "Currently selected Finding: " << m_SelectedFinding->GetFindingName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Finding" << std::endl;
}

void MainWindow::SlotFindingRename(const QString& oldname, const QString& newname)
{
    Finding* tempFinding = this->GetFindingByName(oldname);

    if(m_SelectedReport == NULL || tempFinding == NULL)
        return;

    tempFinding->SetFindingName(newname);

    this->SetSelectedFinding(tempFinding, true);


    if(m_SelectedFinding)
       std::cout << "Currently selected Finding: " << m_SelectedFinding->GetFindingName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Finding" << std::endl;
}

void MainWindow::SlotFindingDelete(const QString& name)
{
    Finding* tempFinding = this->GetFindingByName(name);

    std::cout << "DELETE FINDING PTR: " << tempFinding << std::endl;
    if(m_SelectedReport == NULL || tempFinding == NULL)
        return;

    int idx = m_SelectedReport->GetFindings()->indexOf(tempFinding);

    std::cout << "DELETE FINDING IDX: " << idx << std::endl;

    if(tempFinding != NULL)
    {
        m_SelectedReport->GetFindings()->removeOne(tempFinding);
        delete tempFinding;

         std::cout << "FINDING DELETED: " << std::endl;

        if(m_SelectedReport->GetFindings()->isEmpty())
            this->GetImageSeriesSelectionWidget()->LockPatientSelection(false);
    }

    if(idx > 0)
        this->SetSelectedFinding(m_SelectedReport->GetFindings()->value(idx-1));
    else if(idx == 0 && !m_SelectedReport->GetFindings()->isEmpty())
        this->SetSelectedFinding(m_SelectedReport->GetFindings()->value(0));
    else
    {   std::cout << "SET SELECTED FINDING TO NULL" << std::endl;
        this->SetSelectedFinding(NULL);
    }

    if(m_SelectedFinding)
       std::cout << "Currently selected Finding: " << m_SelectedFinding->GetFindingName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Finding" << std::endl;
}

Finding* MainWindow::GetFindingByName(const QString& name)
{
    if(m_SelectedReport == NULL)
        return NULL;

    QList<Finding*>* findingsPtr = m_SelectedReport->GetFindings();

    if(findingsPtr == NULL)
        return NULL;

    for(int i=0; i < findingsPtr->size(); ++i)
    {
        if(findingsPtr->at(i)->GetFindingName().compare(name) == 0)
            return findingsPtr->value(i);
    }

    return NULL;
}


///// SEGMENTATION SLOTS

void MainWindow::SlotSegmentationCreate(const QString& name)
{
    if(m_SelectedReport == NULL)
    {
        QMessageBox::warning(NULL,"Create Segmentation","A Report must be selected in order to create a new Segmentation");
        return;
    }

    if(m_SelectedFinding == NULL)
    {
        QMessageBox::warning(NULL,"Create Segmentation","A Finding must be selected in order to create a new Segmentation");
        return;
    }

    if(m_SelectedStudy == NULL)
    {
        QMessageBox::warning(NULL,"Create Segmentation","A Study must be selected in order to create a new Segmentation");
        return;
    }

    std::cout << "Creating new Segmentation" << std::endl;
    Segmentation* segmentation = new Segmentation(name,m_SelectedStudy->GetImageSeries(ImageSeries::PET));
    m_SelectedFinding->AddSegmentation(segmentation);

    this->SetSelectedSegmentation(segmentation);

    if(m_SelectedSegmentation)
       std::cout << "Currently selected Segmentation: " << m_SelectedSegmentation->GetSegmentationName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Segmentation" << std::endl;
 }

void MainWindow::SlotSegmentationChange(const QString& name)
{
    Segmentation* tempSeg = this->GetSegmentationByName(name);

    this->SetSelectedSegmentation(tempSeg);

    if(m_SelectedSegmentation)
       std::cout << "Currently selected Segmentation: " << m_SelectedSegmentation->GetSegmentationName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Segmentation" << std::endl;
}

void MainWindow::SlotSegmentationRename(const QString& oldname, const QString& newname)
{
    Segmentation* tempSeg = this->GetSegmentationByName(oldname);

    if(m_SelectedReport == NULL || m_SelectedFinding == NULL || tempSeg == NULL)
        return;

    tempSeg->SetSegmentationName(newname);

    this->SetSelectedSegmentation(tempSeg, false, true);

    if(m_SelectedSegmentation)
       std::cout << "Currently selected Segmentation: " << m_SelectedSegmentation->GetSegmentationName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Segmentation" << std::endl;
}

void MainWindow::SlotSegmentationDelete(const QString& name)
{
    Segmentation* tempSeg = this->GetSegmentationByName(name);

    if(m_SelectedReport == NULL || m_SelectedFinding == NULL || tempSeg == NULL)
        return;

    int idx = m_SelectedFinding->GetAllSegmentations()->indexOf(tempSeg);

    if(tempSeg != NULL)
    {
        m_SelectedFinding->RemoveSegmentation(tempSeg);
        delete tempSeg;
    }

    if(idx > 0)
        this->SetSelectedSegmentation(m_SelectedFinding->GetAllSegmentations()->value(idx-1));
    else if(idx == 0 && !m_SelectedFinding->GetAllSegmentations()->isEmpty())
        this->SetSelectedSegmentation(m_SelectedFinding->GetAllSegmentations()->value(0));
    else
        this->SetSelectedSegmentation(NULL);


    if(m_SelectedSegmentation)
       std::cout << "Currently selected Segmentation: " << m_SelectedSegmentation->GetSegmentationName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Segmentation" << std::endl;
}

Segmentation* MainWindow::GetSegmentationByName(const QString& name)
{
    if(m_SelectedReport == NULL || m_SelectedFinding == NULL)
        return NULL;

    QList<Segmentation*>* segmentations = m_SelectedFinding->GetAllSegmentations();

    for(int i=0; i < segmentations->size(); ++i)
    {
        if(segmentations->at(i)->GetSegmentationName().compare(name) == 0)
            return segmentations->value(i);
    }

    return NULL;
}

void MainWindow::SlotAnaylsisShowReportSummaryDialog()
{
    std::cout << "SHOW REPORT SUMMARY" << std::endl;
}

void MainWindow::SlotAnalysisAddStudy(int studyIdx)
{
    std::cout << "ADD STUDY " << studyIdx << std::endl;
}

void MainWindow::SlotAnaylsisRemoveStudy(int studyIdx)
{
    std::cout << "REMOVE STUDY " << studyIdx << std::endl;
}

void MainWindow::SlotAnalysisQuantitativeSelected()
{
    std::cout << "QUANTITATIVE" << std::endl;
}

void MainWindow::SlotAnalysisQualitativeSelected()
{
    std::cout << "QUALITATIVE" << std::endl;
}
