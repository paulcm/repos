#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTableWidgetItem>
#include <QInputDialog>
#include <QSpinBox>

#include <iostream>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  ,m_DockWidgetModule(NULL)
  ,m_Splitter(NULL)
  ,m_LabelSlicerLogo(NULL)
  ,m_WidgetTop(NULL)
  ,m_WidgetBottom(NULL)
  ,m_ReportSelectionWidget(NULL)
  ,m_ImageSeriesSelectionWidget(NULL)
  ,m_StudySliderWidget(NULL)
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


    this->showMaximized();
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
        m_WidgetTop->layout()->addWidget(this->GetListCategoryButtons().at(3));

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
    }

    return m_WidgetBottom;
}

StudySliderWidget* MainWindow::GetStudySliderWidget()
{
    if(m_StudySliderWidget == NULL)
    {
        m_StudySliderWidget = new StudySliderWidget(&m_Studies,this);

        connect(m_StudySliderWidget, SIGNAL(SignalSliderPositionChanged(int)), this, SLOT(SlotChangeStudyInView(int)));
    }

    return m_StudySliderWidget;
}

ReportSelectionWidget* MainWindow::GetReportSelectionWidget()
{
    if(m_ReportSelectionWidget == NULL)
    {
        m_ReportSelectionWidget = new ReportSelectionWidget(&m_Reports,this);

        this->ConnectReportSelectionSignals();

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

void MainWindow::SlotImageSelectionPatientChanged(const QString& name)
{
    Patient* tempPat = m_DicomDB->GetPatientByName(name);

    if(tempPat != m_SelectedPatient)
        this->GetImageSeriesSelectionWidget()->UpdateStudiesTable(tempPat,m_SelectedStudies);

    m_SelectedPatient = tempPat;
}


void MainWindow::SlotImageSelectionStudySelected(int idx, bool selected)
{
    Study* tempStudy;

    if(selected && m_SelectedPatient != NULL)
    {
        tempStudy = m_SelectedPatient->GetStudy(idx);

        if(!m_SelectedStudies.contains(tempStudy))
            m_SelectedStudies.append(tempStudy);
    }
    else if(!selected && m_SelectedPatient != NULL)
    {
        tempStudy = m_SelectedPatient->GetStudy(idx);

        if(m_SelectedStudies.contains(tempStudy))
            m_SelectedStudies.removeOne(tempStudy);
    }
}

void MainWindow::SlotChangeStudyInView(int idx)
{
    std::cout << m_Studies.values().at(idx)->GetStudyID() << std::endl;
}


void MainWindow::SlotReportCreate(const QString& name)
{
    Report* report = new Report(name);
    report->SetReportID(m_Reports.size());


    m_Reports.prepend(report);

    m_SelectedReport = report;

    this->GetReportSelectionWidget()->UpdateReportSelectorNodeComboBox(m_SelectedReport);

    if(m_SelectedReport)
       std::cout << "Currently selected Report: " << m_SelectedReport->GetReportName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Report" << std::endl;
}

void MainWindow::SlotReportChange(const QString& name)
{
    m_SelectedReport = this->GetReportByName(name);

    this->GetReportSelectionWidget()->UpdateReportSelectorNodeComboBox(m_SelectedReport);

    if(m_SelectedReport)
       std::cout << "Currently selected Report: " << m_SelectedReport->GetReportName().toStdString() << std::endl;
    else
        std::cout << "No currently selected Report" << std::endl;
}

void MainWindow::SlotReportRename(const QString& oldname, const QString& newname)
{
    Report* tempReport = this->GetReportByName(oldname);
    tempReport->SetReportName(newname);

    m_SelectedReport = tempReport;

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
        m_SelectedReport = m_Reports.value(idx-1);
    else if(idx == 0 && !m_Reports.isEmpty())
        m_SelectedReport = m_Reports.value(0);
    else
        m_SelectedReport = NULL;

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

void MainWindow::DisconnectReportSelectionSignals()
{
    disconnect(m_ReportSelectionWidget, SIGNAL(SignalCreateNewReport(QString)), this, SLOT(SlotReportCreate(QString)) );
    disconnect(m_ReportSelectionWidget, SIGNAL(SignalChangeReport(QString)), this, SLOT(SlotReportChange(QString)) );
    disconnect(m_ReportSelectionWidget, SIGNAL(SignalRenameReport(QString,QString)), this, SLOT(SlotReportRename(QString,QString)) );
    disconnect(m_ReportSelectionWidget, SIGNAL(SignalDeleteReport(QString)), this, SLOT(SlotReportDelete(QString)) );
}

void MainWindow::ConnectReportSelectionSignals()
{
    connect(m_ReportSelectionWidget, SIGNAL(SignalCreateNewReport(QString)), this, SLOT(SlotReportCreate(QString)) );
    connect(m_ReportSelectionWidget, SIGNAL(SignalChangeReport(QString)), this, SLOT(SlotReportChange(QString)) );
    connect(m_ReportSelectionWidget, SIGNAL(SignalRenameReport(QString,QString)), this, SLOT(SlotReportRename(QString,QString)) );
    connect(m_ReportSelectionWidget, SIGNAL(SignalDeleteReport(QString)), this, SLOT(SlotReportDelete(QString)) );
}







//    m_ButtonIconOpened.addPixmap(QPixmap(":/resources/opened.png"));
//    m_ButtonIconClosed.addPixmap(QPixmap(":/resources/closed.png"));
//    m_ButtonIconShow.addPixmap(QPixmap(":/resources/eye_open.png"));
//    m_ButtonIconHide.addPixmap(QPixmap(":/resources/eye_shut.png"));

//    m_Dates << "2011/11/01" << "2012/02/15" << "2012/05/16";
//    m_Times << "01:02:03 pm" << "02:03:04 pm" << "03:04:05 pm";




//    //DockWidget with Module Control Panel
//    m_DockWidgetLeft = new QDockWidget();
//    m_DockWidgetLeft->setFeatures(QDockWidget::NoDockWidgetFeatures);
//    this->addDockWidget(Qt::LeftDockWidgetArea,m_DockWidgetLeft,Qt::Vertical);
//    m_DockWidgetLeft->setFixedWidth(380);

//    if(m_DockWidgetLeft->widget() == NULL)
//        m_DockWidgetLeft->setWidget(new QWidget(m_DockWidgetLeft));

//    m_DockWidgetLeft->widget()->setLayout(new QVBoxLayout());
//    m_DockWidgetLeft->widget()->layout()->setMargin(0);
//    m_DockWidgetLeft->widget()->layout()->setSpacing(8);

//    // Slicer Logo in title of DockWidget
//    QLabel* logoLabel = new QLabel(this);
//    logoLabel->setAlignment(Qt::AlignLeft);
//    logoLabel->setPixmap(QPixmap(":/resources/slicer_logo.png"));
//    logoLabel->setMargin(5);
//    m_DockWidgetLeft->setTitleBarWidget(logoLabel);

//    m_DockWidgetLeftSplitter = new QSplitter(Qt::Vertical,this);
//    m_DockWidgetLeft->widget()->layout()->addWidget(m_DockWidgetLeftSplitter);

//    m_ModulePanelTop = new QWidget(m_DockWidgetLeft);
//    m_ModulePanelTop->setLayout(new QVBoxLayout());

//    m_ModulePanelBottom = new QWidget(m_DockWidgetLeft);
//    m_ModulePanelBottom->setLayout(new QGridLayout());


//    m_DockWidgetLeftSplitter->insertWidget(0,m_ModulePanelTop);
//    m_DockWidgetLeftSplitter->insertWidget(1,m_ModulePanelBottom);
//    m_DockWidgetLeftSplitter->setStretchFactor(0,2);
//    m_DockWidgetLeftSplitter->setStretchFactor(1,0);


//    if(this->centralWidget() == NULL)
//        this->setCentralWidget(new QWidget(this));
//    m_CentralWidgetLayout = new QGridLayout(this->centralWidget());

//    m_CentralWidgetLayout->setMargin(0);
//    m_CentralWidgetLayout->setSpacing(0);
//    this->centralWidget()->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    this->centralWidget()->layout()->setMargin(0);

//    m_CentralWidgetLabel = new QLabel(this);
//    m_CentralWidgetLabel->setScaledContents(true);

//    this->centralWidget()->layout()->addWidget(m_CentralWidgetLabel);

//    m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene0.png"));

//    //Initialization of all displayable stuff
//    //this->InitializeImageViewWidgets();

//    this->InitializeTopPanelElements();
//    this->InitializeBottomPanelElements();

//    //this->ChangeImageView(FOUR_UP);

//    this->showMaximized();

//}



//void MainWindow::InitializeImageViewWidgets()
//{
//    //3D
//    m_ImageViewWidget3D = new QWidget(this);

//    m_ImageViewWidget3D->setLayout(new QVBoxLayout());
//    m_ImageViewWidget3D->layout()->setMargin(0);
//    m_ImageViewWidget3D->layout()->setSpacing(0);
//    m_ImageViewWidget3D->setStyleSheet("background-image: url(:/resources/3d_back.png);\nbackground-repeat: repeat-x;\nbackground-color: #c1c3e8;");

//    m_ImageViewWidget3DTitlebarLabel = new QLabel(m_ImageViewWidget3D);
//    m_ImageViewWidget3DTitlebarLabel->setMaximumHeight(15);
//    m_ImageViewWidget3DTitlebarLabel->setStyleSheet("background-image: url(:/resources/3D_titleback.png);\nbackground-repeat: repeat-x;");

//    m_ImageViewWidget3DRenderAreaLabel = new QLabel(m_ImageViewWidget3D);
//    m_ImageViewWidget3DRenderAreaLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//    m_ImageViewWidget3DRenderAreaLabel->setPixmap(QPixmap(":/resources/scene0.png"));

//    m_ImageViewWidget3D->layout()->addWidget(m_ImageViewWidget3DTitlebarLabel);
//    m_ImageViewWidget3D->layout()->addWidget(m_ImageViewWidget3DRenderAreaLabel);

//    //Axial
//    m_ImageViewWidgetAxial = new QWidget(this);

//    m_ImageViewWidgetAxial->setLayout(new QVBoxLayout());
//    m_ImageViewWidgetAxial->layout()->setMargin(0);
//    m_ImageViewWidgetAxial->layout()->setSpacing(0);
//    m_ImageViewWidgetAxial->setStyleSheet("background-color:#000;");

//    m_ImageViewWidgetAxialTitlebarLabel = new QLabel(m_ImageViewWidgetAxial);
//    m_ImageViewWidgetAxialTitlebarLabel->setMaximumHeight(15);
//    m_ImageViewWidgetAxialTitlebarLabel->setStyleSheet("background-image: url(:/resources/axial_titleback.png);\nbackground-repeat: repeat-x;");

//    m_ImageViewWidgetAxialRenderAreaLabel = new QLabel(m_ImageViewWidgetAxial);

//    m_ImageViewWidgetAxial->layout()->addWidget(m_ImageViewWidgetAxialTitlebarLabel);
//    m_ImageViewWidgetAxial->layout()->addWidget(m_ImageViewWidgetAxialRenderAreaLabel);

//    //Sagittal
//    m_ImageViewWidgetSagittal = new QWidget(this);

//    m_ImageViewWidgetSagittal->setLayout(new QVBoxLayout());
//    m_ImageViewWidgetSagittal->layout()->setMargin(0);
//    m_ImageViewWidgetSagittal->layout()->setSpacing(0);
//    m_ImageViewWidgetSagittal->setStyleSheet("background-color:#000;");

//    m_ImageViewWidgetSagittalTitlebarLabel = new QLabel(m_ImageViewWidgetSagittal);
//    m_ImageViewWidgetSagittalTitlebarLabel->setMaximumHeight(15);
//    m_ImageViewWidgetSagittalTitlebarLabel->setStyleSheet("background-image: url(:/resources/sagittal_titleback.png);\nbackground-repeat: repeat-x;");

//    m_ImageViewWidgetSagittalRenderAreaLabel = new QLabel(m_ImageViewWidgetSagittal);

//    m_ImageViewWidgetSagittal->layout()->addWidget(m_ImageViewWidgetSagittalTitlebarLabel);
//    m_ImageViewWidgetSagittal->layout()->addWidget(m_ImageViewWidgetSagittalRenderAreaLabel);

//    //Coronal
//    m_ImageViewWidgetCoronal = new QWidget(this);

//    m_ImageViewWidgetCoronal->setLayout(new QVBoxLayout());
//    m_ImageViewWidgetCoronal->layout()->setMargin(0);
//    m_ImageViewWidgetCoronal->layout()->setSpacing(0);
//    m_ImageViewWidgetCoronal->setStyleSheet("background-color:#000;");

//    m_ImageViewWidgetCoronalTitlebarLabel = new QLabel(m_ImageViewWidgetCoronal);
//    m_ImageViewWidgetCoronalTitlebarLabel->setMaximumHeight(15);
//    m_ImageViewWidgetCoronalTitlebarLabel->setStyleSheet("background-image: url(:/resources/coronal_titleback.png);\nbackground-repeat: repeat-x;");

//    m_ImageViewWidgetCoronalRenderAreaLabel = new QLabel(m_ImageViewWidgetCoronal);

//    m_ImageViewWidgetCoronal->layout()->addWidget(m_ImageViewWidgetCoronalTitlebarLabel);
//    m_ImageViewWidgetCoronal->layout()->addWidget(m_ImageViewWidgetCoronalRenderAreaLabel);

//}


//void MainWindow::ChangeImageView(VIEW_TYPE type)
//{
//    m_CentralWidgetLayout->removeWidget(m_ImageViewWidget3D);
//    m_CentralWidgetLayout->removeWidget(m_ImageViewWidgetAxial);
//    m_CentralWidgetLayout->removeWidget(m_ImageViewWidgetSagittal);
//    m_CentralWidgetLayout->removeWidget(m_ImageViewWidgetCoronal);

//    if(type == CONVENTIONAL)
//    {
//        m_CentralWidgetLayout->addWidget(m_ImageViewWidget3D,0,0,1,3);
//        m_CentralWidgetLayout->addWidget(m_ImageViewWidgetAxial,1,0,1,1);
//        m_CentralWidgetLayout->addWidget(m_ImageViewWidgetSagittal,1,1,1,1);
//        m_CentralWidgetLayout->addWidget(m_ImageViewWidgetCoronal,1,2,1,1);
//    }
//    else if(type == FOUR_UP)
//    {
//        m_CentralWidgetLayout->addWidget(m_ImageViewWidgetAxial,0,0,1,1);
//        m_CentralWidgetLayout->addWidget(m_ImageViewWidget3D,0,1,1,1);
//        m_CentralWidgetLayout->addWidget(m_ImageViewWidgetSagittal,1,0,1,1);
//        m_CentralWidgetLayout->addWidget(m_ImageViewWidgetCoronal,1,1,1,1);
//    }
//}



//void MainWindow::InitializeBottomPanelElements()
//{
//    QLabel* selectTimepointLabel = new QLabel("Selected timepoint:",m_ModulePanelBottom);
//    selectTimepointLabel->setAlignment(Qt::AlignBottom);
//    m_BottomPanelTimepointSliderWidget = new StudySliderWidget(&m_Studies, this);


//    m_BottomPanelTreeWidget = new QTreeWidget(m_ModulePanelBottom);
//    m_BottomPanelTreeWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

//    m_BottomPanelTreeWidget->setHeaderLabel("Findings");
//    //m_BottomPanelTreeWidget->setSelectionMode(QAbstractItemView::NoSelection);

//    connect(m_BottomPanelTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(on_BottomPanelTreeWidgetItemPressed(QTreeWidgetItem*,int)) );

//    QGridLayout* tempLayoutPtr = (QGridLayout*) m_ModulePanelBottom->layout();
//    tempLayoutPtr->setColumnStretch(0,0);
//    tempLayoutPtr->setColumnStretch(1,2);

//    //tempLayoutPtr->addItem(new QSpacerItem(20,1,QSizePolicy::Minimum, QSizePolicy::Expanding),0,0,1,2);
//    tempLayoutPtr->addWidget(m_BottomPanelTimepointSliderWidget,0,0);
//    tempLayoutPtr->addWidget(this->CreateSeparator(),1,0);
//    tempLayoutPtr->addWidget(m_BottomPanelTreeWidget,2,0);
//}

//void MainWindow::InitializeTopPanelElements()
//{
//    //The Buttons
//    m_HelpButton = this->CreateTopPanelButton("Help and Acknowledgement", m_ModulePanelTop);
//    m_ReportButton = this->CreateTopPanelButton("Report Settings", m_ModulePanelTop);
//    m_ImagesButton = this->CreateTopPanelButton("Image Series Management", m_ModulePanelTop);
//    m_ImagesButton->setEnabled(false);
//    m_FindingsButton = this->CreateTopPanelButton("Findings",m_ModulePanelTop);
//    m_FindingsButton->setEnabled(false);
//    m_AnalysisButton = this->CreateTopPanelButton("Analysis",m_ModulePanelTop);
//    m_AnalysisButton->setEnabled(false);

//    //Widgets
//    m_ReportWidget = this->CreateReportWidget(m_ModulePanelTop);
//    m_ImagesWidget = this->CreateImagesWidget(m_ModulePanelTop);
//    m_FindingsWidget = this->CreateFindingsWidget(m_ModulePanelTop);
//    m_AnalysisWidget = this->CreateAnalysisWidget(m_ModulePanelTop);

//    m_ModulePanelTop->layout()->addWidget(m_HelpButton);
//    m_ModulePanelTop->layout()->addWidget(this->CreateSeparator(m_ModulePanelTop));
//    m_ModulePanelTop->layout()->addWidget(m_ReportButton);
//    m_ModulePanelTop->layout()->addWidget(m_ReportWidget);
//    m_ModulePanelTop->layout()->addWidget(m_ImagesButton);
//    m_ModulePanelTop->layout()->addWidget(m_ImagesWidget);
//    m_ModulePanelTop->layout()->addWidget(m_FindingsButton);
//    m_ModulePanelTop->layout()->addWidget(m_FindingsWidget);
//    m_ModulePanelTop->layout()->addWidget(m_AnalysisButton);
//    m_ModulePanelTop->layout()->addWidget(m_AnalysisWidget);
//    m_ModulePanelTop->layout()->addItem(new QSpacerItem(20,1,QSizePolicy::Minimum,QSizePolicy::Expanding));
//}

//QFrame* MainWindow::CreateSeparator(QWidget* parent)
//{
//    QFrame* separator = new QFrame(parent);
//    separator->setFrameStyle(QFrame::HLine | QFrame::Sunken);

//    return separator;
//}


//void MainWindow::on_TopPanelButtonClicked(bool checked)
//{
//    QPushButton* senderButton = (QPushButton*) QObject::sender();

//    for(int i=0; i < m_TopPanelButtons.size(); ++i)
//    {
//        if(m_TopPanelButtons.at(i) != senderButton)
//        {
//            disconnect( m_TopPanelButtons.at(i), SIGNAL(toggled(bool)), this, SLOT(on_TopPanelButtonClicked(bool)) );
//            m_TopPanelButtons.at(i)->setChecked(false);
//            m_TopPanelButtons.at(i)->setIcon(m_ButtonIconClosed);
//            connect( m_TopPanelButtons.at(i), SIGNAL(toggled(bool)), this, SLOT(on_TopPanelButtonClicked(bool)) );
//        }
//    }

//    if(checked)
//        senderButton->setIcon(m_ButtonIconOpened);
//    else
//        senderButton->setIcon(m_ButtonIconClosed);

//    this->on_ShowTopPanelWidget(checked,senderButton);
//}

//QPushButton* MainWindow::CreateTopPanelButton(const QString& text, QWidget* parent)
//{
//    QString buttonStyleSheet("text-align: left; padding-left: 5px;");

//    QPushButton* result = new QPushButton(m_ButtonIconClosed, text, parent);
//    result->setMaximumHeight(24);
//    result->setCheckable(true);
//    result->setStyleSheet(buttonStyleSheet);
//    connect( result, SIGNAL(toggled(bool)), this, SLOT(on_TopPanelButtonClicked(bool)) );

//    m_TopPanelButtons.append(result);

//    return result;
//}

//void MainWindow::on_FindingsComboboxSelectionChanged(int index)
//{
//    //TODO COMPLETE

//    static int turn = 0;

//    if(index == 3)
//    {
//        QStringList list;
//        list << "Tumor" << "Lymph Node" << "Reference Structure";
//        QString itemSelected = QInputDialog::getItem(this,"Finding type","Please select the type of the Finding",list,0,false);

//        if(!itemSelected.isEmpty())
//        {
//            disconnect(m_FindingsSelectComboBox,SIGNAL(currentIndexChanged(int)),this, SLOT(on_FindingsComboboxSelectionChanged(int)) );
//            if(turn==0)
//                m_FindingsSelectComboBox->removeItem(0);
//            QString name = QString().setNum(++turn)+"_"+itemSelected;
//            m_FindingsSelectComboBox->insertItem(turn-1,name);
//            m_FindingsSelectComboBox->setCurrentIndex(turn-1);
//            connect(m_FindingsSelectComboBox,SIGNAL(currentIndexChanged(int)),this, SLOT(on_FindingsComboboxSelectionChanged(int)) );

//            this->on_EnableFindingsWidgetContent(true);

//            QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(name));
//            m_BottomPanelTreeWidget->insertTopLevelItem(m_BottomPanelTreeWidget->topLevelItemCount(),item);
//        }

//        m_AnalysisButton->setEnabled(true);

//        if(turn == 0)
//            m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene1.png"));
//        else if(turn == 1)
//            m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene2.png"));
//        else if(turn > 1)
//            m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene3.png"));

//    }


//}

//void MainWindow::on_DisplayROIButtonClicked()
//{
//    static int turn = 1;

//    QPushButton* senderButton = (QPushButton*) QObject::sender();

//    //TODO Complete for views

//    if(turn % 2 == 0)
//        senderButton->setIcon(m_ButtonIconShow);
//    else
//        senderButton->setIcon(m_ButtonIconHide);

//    turn++;
//}

//void MainWindow::on_EnableFindingsWidgetContent(bool enable)
//{
//    m_FindingsNewSegmentationRadioButton->setEnabled(enable);
//    m_FindingsNewSegmentationWidget->setEnabled(enable);

//    m_FindingsSelectSegmentationRadioButton->setEnabled(enable);
//    m_FindingsSelectSegmentationWidget->setEnabled(enable);

//    m_FindingsOrLabel->setEnabled(enable);

//    m_FindingsAddSegmentationButton->setEnabled(enable);
//}


//QWidget* MainWindow::CreateAnalysisWidget(QWidget* parent)
//{
//    if(m_AnalysisWidget == NULL)
//    {
//        m_AnalysisWidget = new QWidget(parent);
//        QGridLayout* layout = new QGridLayout(m_AnalysisWidget);
//        layout->setMargin(8);
//        layout->setSpacing(8);

//        QLabel* infoLabel = new QLabel("Select between qualitative and quantitative analysis.");
//        infoLabel->setWordWrap(true);

//        m_AnalysisQualitativeRadioButton = new QRadioButton("Qualitative");
//        m_AnalysisQualitativeRadioButton->setChecked(true);
//        connect(m_AnalysisQualitativeRadioButton,SIGNAL(toggled(bool)),this,SLOT(on_AnalysisViewChanged(bool)) );
//        m_AnalysisQuantitativeRadioButton = new QRadioButton("Quantitative");
//        connect(m_AnalysisQuantitativeRadioButton,SIGNAL(toggled(bool)),this,SLOT(on_AnalysisViewChanged(bool)) );

//        QLabel* selectInfo = new QLabel("Select image series for comparison");

//        for(int i=0; i < 3; ++i)
//        {
//            QCheckBox* tempChB = new QCheckBox(m_Dates.at(i)+" | "+m_Times.at(i),m_AnalysisWidget);
//            tempChB->setChecked(true);
//            tempChB->setStyleSheet("margin-left:15px");
//            m_AnalysisCheckboxes.append(tempChB);
//        }

//        m_AnalysisPrintReportButton = new QPushButton("Show Report Summary");
//        m_AnalysisPrintReportButton->setMaximumHeight(24);

//        int row = 0;

//        layout->addWidget(infoLabel,row,0,1,2);
//        row++;
//        layout->addWidget(this->CreateSeparator(),row,0,1,2);
//        row++;
//        layout->addWidget(m_AnalysisQualitativeRadioButton,row,0,1,1);
//        layout->addWidget(m_AnalysisQuantitativeRadioButton,row,1,1,1);
//        row++;
//        layout->addWidget(this->CreateSeparator(),row,0,1,2);
//        row++;
//        layout->addWidget(selectInfo,row,0,1,2);
//        for(int i=0; i < 3; ++i)
//        {
//            row++;
//            layout->addWidget(m_AnalysisCheckboxes.at(i),row,0,1,2);
//        }
//        row++;
//        layout->addWidget(this->CreateSeparator(),row,0,1,2);
//        row++;
//        layout->addWidget(m_AnalysisPrintReportButton,row,0,1,2);


//        layout->setAlignment(m_AnalysisQualitativeRadioButton,Qt::AlignCenter);
//        layout->setAlignment(m_AnalysisQuantitativeRadioButton,Qt::AlignCenter);


//        m_AnalysisWidget->setVisible(false);
//        m_TopPanelWidgets.append(m_AnalysisWidget);
//    }

//    return m_AnalysisWidget;
//}


//QWidget* MainWindow::CreateFindingsWidget(QWidget* parent)
//{
//    if(m_FindingsWidget == NULL)
//    {
//        m_FindingsWidget = new QWidget(parent);
//        QGridLayout* layout = new QGridLayout(m_FindingsWidget);
//        layout->setMargin(8);
//        layout->setSpacing(8);

//        QLabel* selectFindingLabel = new QLabel("Select Finding",parent);

//        m_FindingsSelectComboBox = new QComboBox(parent);
//        m_FindingsSelectComboBox->setMaximumHeight(24);

//        m_FindingsSelectComboBox->addItem("None");
//        m_FindingsSelectComboBox->addItem("---------------------");
//        m_FindingsSelectComboBox->addItem("Rename current Finding");
//        m_FindingsSelectComboBox->addItem("Create new Finding");
//        m_FindingsSelectComboBox->addItem("Delete current Finding");

//        connect(m_FindingsSelectComboBox,SIGNAL(currentIndexChanged(int)),this, SLOT(on_FindingsComboboxSelectionChanged(int)) );

//        m_FindingsDisplayROIButton = new QPushButton(m_ButtonIconShow,"Display ROI",parent);
//        m_FindingsDisplayROIButton->setMaximumHeight(24);
//        m_FindingsDisplayROIButton->setStyleSheet("border: none");

//        connect(m_FindingsDisplayROIButton,SIGNAL(clicked()), this, SLOT(on_DisplayROIButtonClicked()) );

//        m_FindingsNewSegmentationRadioButton = new QRadioButton("Create a new\nsegmentation");
//        m_FindingsNewSegmentationRadioButton->setChecked(true);
//        m_FindingsOrLabel = new QLabel("or",parent);
//        m_FindingsOrLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        m_FindingsSelectSegmentationRadioButton = new QRadioButton("Select existing\nsegmentation");


//        m_FindingsNewSegmentationWidget = new QWidget(m_FindingsWidget);
//        QGridLayout* newseglayout = new QGridLayout(m_FindingsNewSegmentationWidget);
//        QLabel* thresholdLabel = new QLabel("Choose threshold");
//        //spinboxes
//        QSpinBox* minSpinBox = new QSpinBox(m_FindingsNewSegmentationWidget);
//        minSpinBox->setMinimum(0);
//        minSpinBox->setMaximum(20);
//        minSpinBox->setValue(10);
//        QSpinBox* maxSpinBox = new QSpinBox(m_FindingsNewSegmentationWidget);
//        maxSpinBox->setMinimum(21);
//        maxSpinBox->setMaximum(40);
//        maxSpinBox->setValue(30);
//        //sliders
//        QSlider* minSlider = new QSlider(Qt::Horizontal,m_FindingsNewSegmentationWidget);
//        minSlider->setMinimum(0);
//        minSlider->setMaximum(20);
//        minSlider->setValue(10);
//        QSlider* maxSlider = new QSlider(Qt::Horizontal,m_FindingsNewSegmentationWidget);
//        maxSlider->setMinimum(21);
//        maxSlider->setMaximum(40);
//        maxSlider->setValue(30);
//        //connect sliders and spinboxes
//        connect(minSlider,SIGNAL(sliderMoved(int)),minSpinBox,SLOT(setValue(int)) );
//        connect(maxSlider,SIGNAL(sliderMoved(int)),maxSpinBox,SLOT(setValue(int)) );
//        connect(minSpinBox,SIGNAL(valueChanged(int)),minSlider,SLOT(setValue(int)) );
//        connect(maxSpinBox,SIGNAL(valueChanged(int)),maxSlider,SLOT(setValue(int)) );
//        //layouting
//        newseglayout->addWidget(thresholdLabel,0,0,1,4);
//        newseglayout->addWidget(minSpinBox,1,0,1,1);
//        newseglayout->addWidget(minSlider,1,1,1,1);
//        newseglayout->addWidget(maxSlider,1,2,1,1);
//        newseglayout->addWidget(maxSpinBox,1,3,1,1);

//        //Select Segmentation Widget
//        m_FindingsSelectSegmentationWidget = new QWidget(m_FindingsWidget);
//        QHBoxLayout* selseglayout = new QHBoxLayout(m_FindingsSelectSegmentationWidget);
//        QLabel* selectSegmentationLabel = new QLabel("Segmentation",m_FindingsSelectSegmentationWidget);
//        QComboBox* selectSegmentationComboBox = new QComboBox(m_FindingsSelectSegmentationWidget);
//        selectSegmentationComboBox->setMaximumHeight(24);
//        selectSegmentationComboBox->addItem("None");
//        selectSegmentationComboBox->addItem("---------------------");
//        selectSegmentationComboBox->addItem("Rename current Segmentation");
//        selectSegmentationComboBox->addItem("Delete current Segmentation");
//        //layouting
//        selseglayout->addWidget(selectSegmentationLabel);
//        selseglayout->addWidget(selectSegmentationComboBox);
//        m_FindingsSelectSegmentationWidget->setVisible(false);

//        //connect RadioButtons with Segmentation Widgets
//        connect(m_FindingsNewSegmentationRadioButton,SIGNAL(toggled(bool)),this,SLOT(on_ShowSegmentationTypeWidget(bool)) );
//        connect(m_FindingsSelectSegmentationRadioButton,SIGNAL(toggled(bool)),this,SLOT(on_ShowSegmentationTypeWidget(bool)) );

//        m_FindingsAddSegmentationButton = new QPushButton("Add Segmentation to selected Finding");
//        m_FindingsAddSegmentationButton->setMaximumHeight(24);
//        //connect(m_FindingsAddSegmentationButton,SIGNAL(clicked()),this,SLOT(on_AddSegmentationToFinding()));

//        int row=0;

//        layout->addWidget(selectFindingLabel,row,0,1,1);
//        layout->addWidget(m_FindingsSelectComboBox,row,1,1,2);
//        row++;
//        layout->addWidget(m_FindingsDisplayROIButton,row,2,1,1);
//        row++;
//        layout->addWidget(this->CreateSeparator(),row,0,1,3);
//        row++;
//        layout->addWidget(m_FindingsNewSegmentationRadioButton,row,0,1,1);
//        layout->addWidget(m_FindingsOrLabel,row,1,1,1);
//        layout->addWidget(m_FindingsSelectSegmentationRadioButton,row,2,1,1);
//        row++;
//        layout->addWidget(m_FindingsNewSegmentationWidget,row,0,1,3);
//        //layout->addWidget(m_FindingsSelectSegmentationWidget,row,0,1,3);
//        row++;
//        layout->addWidget(this->CreateSeparator(),row,0,1,3);
//        row++;
//        layout->addWidget(m_FindingsAddSegmentationButton,row,0,1,3);
//        row++;
//        layout->addItem(new QSpacerItem(20,1,QSizePolicy::Minimum,QSizePolicy::Expanding),row,0,1,3);

//        this->on_EnableFindingsWidgetContent(false);
//        m_FindingsWidget->setVisible(false);
//        m_TopPanelWidgets.append(m_FindingsWidget);
//    }

//    return m_FindingsWidget;
//}

//void MainWindow::on_ShowSegmentationTypeWidget(bool show)
//{


//    QRadioButton* senderButton = (QRadioButton*) QObject::sender();

//    if(senderButton == m_FindingsNewSegmentationRadioButton && show)
//    {
//        this->setWindowTitle("show new");

//        m_FindingsWidget->layout()->removeWidget(m_FindingsSelectSegmentationWidget);
//        m_FindingsSelectSegmentationWidget->setVisible(false);

//        m_FindingsNewSegmentationWidget->setVisible(true);
//        ((QGridLayout*) m_FindingsWidget->layout())->addWidget(m_FindingsNewSegmentationWidget,4,0,1,3);
//    }
//    else if(senderButton == m_FindingsSelectSegmentationRadioButton && show)
//    {
//        this->setWindowTitle("show select");

//        m_FindingsWidget->layout()->removeWidget(m_FindingsNewSegmentationWidget);
//        m_FindingsNewSegmentationWidget->setVisible(false);

//        m_FindingsSelectSegmentationWidget->setVisible(true);
//        ((QGridLayout*) m_FindingsWidget->layout())->addWidget(m_FindingsSelectSegmentationWidget,4,0,1,3);
//    }
//}

//QWidget* MainWindow::CreateImagesWidget(QWidget* parent)
//{
//    if(m_ImagesWidget == NULL)
//    {
//        m_ImagesWidget = new QWidget(parent);
//        QVBoxLayout* layout = new QVBoxLayout(m_ImagesWidget);
//        layout->setMargin(8);
//        layout->setSpacing(8);

//        QLabel* selectPatientLabel = new QLabel("Select a patient from the DICOM Database", parent);
//        selectPatientLabel->setWordWrap(true);

//        m_ImagesSelectPatientComboBox = new QComboBox(parent);
//        m_ImagesSelectPatientComboBox->setMaximumHeight(24);
//        m_ImagesSelectPatientComboBox->addItem("None");
//        m_ImagesSelectPatientComboBox->addItem("---------------------");
//        //m_ImagesSelectPatientComboBox->addItem("Eve Example");
//        m_ImagesSelectPatientComboBox->addItem("Patrick Pattern");

//        connect(m_ImagesSelectPatientComboBox,SIGNAL(currentIndexChanged(int)),this, SLOT(on_PatientsComboboxFillTable(int)) );

//        QLabel* selectImagesLabel = new QLabel("Select images for the workflow", parent);
//        selectImagesLabel->setWordWrap(true);

//        m_ImagesSelectImageTable = new QTableWidget(0,4,parent);
//        m_ImagesSelectImageTable->setColumnWidth(0,14);
//        m_ImagesSelectImageTable->setHorizontalHeaderItem(0, new QTableWidgetItem(""));
//        m_ImagesSelectImageTable->setColumnWidth(1,100);
//        m_ImagesSelectImageTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Date"));
//        m_ImagesSelectImageTable->setColumnWidth(2,100);
//        m_ImagesSelectImageTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Time"));
//        m_ImagesSelectImageTable->setColumnWidth(3,81);
//        m_ImagesSelectImageTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Modality"));

//        m_ImagesSelectImageTable->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

//        layout->addWidget(selectPatientLabel);
//        layout->addWidget(m_ImagesSelectPatientComboBox);
//        layout->addWidget(this->CreateSeparator());
//        layout->addWidget(selectImagesLabel);
//        layout->addWidget(m_ImagesSelectImageTable);
//        layout->addItem(new QSpacerItem(20,1,QSizePolicy::Minimum,QSizePolicy::Expanding));

//        m_ImagesWidget->setVisible(false);

//        m_TopPanelWidgets.append(m_ImagesWidget);

//    }
//    return m_ImagesWidget;
//}
//QWidget* MainWindow::CreateReportWidget(QWidget* parent)
//{
//    if(m_ReportWidget == NULL)
//    {
//        m_ReportWidget = new QWidget(parent);
//        QGridLayout* layout = new QGridLayout(m_ReportWidget);
//        layout->setMargin(8);
//        layout->setSpacing(8);

//        QLabel* infoLabel = new QLabel("Create a new Report for the workflow or select an exisiting one.",parent);
//        infoLabel->setWordWrap(true);

//        QLabel* selectLabel = new QLabel("Select Report", parent);
//        m_ReportComboBox = new QComboBox(parent);
//        m_ReportComboBox->setMaximumHeight(24);

//        m_ReportComboBox->addItem("None");
//        m_ReportComboBox->addItem("---------------------");
//        m_ReportComboBox->addItem("Rename current Report");
//        m_ReportComboBox->addItem("Create new Report");
//        m_ReportComboBox->addItem("Delete current Report");

//        connect(m_ReportComboBox,SIGNAL(currentIndexChanged(int)),this, SLOT(on_ReportComboboxImageWidgetActivation(int)) );

//        layout->addWidget(infoLabel,0,0,1,2);
//        layout->addWidget(this->CreateSeparator(),1,0,1,2);
//        layout->addWidget(selectLabel,2,0,1,1);
//        layout->addWidget(m_ReportComboBox,2,1,1,1);
//        layout->addItem(new QSpacerItem(20,1,QSizePolicy::Minimum,QSizePolicy::Expanding),3,0,1,2);

//        layout->setColumnStretch(0,0);
//        layout->setColumnStretch(1,1);
//        m_ReportWidget->setVisible(false);

//        m_TopPanelWidgets.append(m_ReportWidget);

//    }

//    return m_ReportWidget;
//}

//void MainWindow::on_ShowTopPanelWidget(bool show, QPushButton* button)
//{
//    for(int i=0; i < m_TopPanelWidgets.size(); ++i)
//        m_TopPanelWidgets.at(i)->setVisible(false);

//    if(button == m_ReportButton)
//        m_ReportWidget->setVisible(show);
//    else if(button == m_ImagesButton)
//        m_ImagesWidget->setVisible(show);
//    else if(button == m_FindingsButton)
//        m_FindingsWidget->setVisible(show);
//    else if(button == m_AnalysisButton)
//    {
//        m_AnalysisWidget->setVisible(show);
//        if(m_AnalysisQualitativeRadioButton->isChecked())
//            m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene4.png"));
//        else
//            m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene5.png"));
//    }
//}




//void MainWindow::on_PatientsComboboxFillTable(int selectedID)
//{
//    this->setWindowTitle("Selected ID: "+QString().setNum(selectedID));
//    if(selectedID == 0 || selectedID == 1)
//    {
//        m_ImagesSelectImageTable->clearContents();
//    }
//    else if(selectedID == 2)
//    {
//        m_ImagesSelectImageTable->insertRow(0);
//        m_ImagesSelectImageTable->setVerticalHeaderItem(0,NULL);
//        m_ImagesSelectImageTable->insertRow(1);
//        m_ImagesSelectImageTable->setVerticalHeaderItem(1,NULL);
//        m_ImagesSelectImageTable->insertRow(2);
//        m_ImagesSelectImageTable->setVerticalHeaderItem(2,NULL);


//        for(int i=0; i < 3; ++i)
//        {
//            QCheckBox* currCheckBox = new QCheckBox(this);
//            connect( currCheckBox, SIGNAL(clicked(bool)), this, SLOT(on_TableCheckboxClicked(bool)) );

//            m_ImagesSelectImageTable->setCellWidget(i,0,currCheckBox);

//            m_ImagesTableCheckBoxes.append(currCheckBox);
//        }

//        QTableWidgetItem* date1 = new QTableWidgetItem(m_Dates.at(0));
//        QTableWidgetItem* date2 = new QTableWidgetItem(m_Dates.at(1));
//        QTableWidgetItem* date3 = new QTableWidgetItem(m_Dates.at(2));

//        QTableWidgetItem* time1 = new QTableWidgetItem(m_Times.at(0));
//        QTableWidgetItem* time2 = new QTableWidgetItem(m_Times.at(1));
//        QTableWidgetItem* time3 = new QTableWidgetItem(m_Times.at(2));

//        QString modality = "PET/CT";

//        m_ImagesSelectImageTable->setItem(0,1,date1);
//        m_ImagesSelectImageTable->setItem(1,1,date2);
//        m_ImagesSelectImageTable->setItem(2,1,date3);

//        m_ImagesSelectImageTable->setItem(0,2,time1);
//        m_ImagesSelectImageTable->setItem(1,2,time2);
//        m_ImagesSelectImageTable->setItem(2,2,time3);

//        m_ImagesSelectImageTable->setItem(0,3,new QTableWidgetItem(modality));
//        m_ImagesSelectImageTable->setItem(1,3,new QTableWidgetItem(modality));
//        m_ImagesSelectImageTable->setItem(2,3,new QTableWidgetItem(modality));
//    }

//}

//void MainWindow::on_TableCheckboxClicked(bool checked)
//{
//    int abort = -1;
//    if(!checked)
//        abort = QMessageBox::warning(this,"Deselect Image Series","Are you sure you want to remove this image series from your workflow?\n\nAll Findings related to this image series will be removed too!",QMessageBox::Yes, QMessageBox::Cancel);

//    if(abort == QMessageBox::Cancel)
//    {
//        ((QCheckBox*) QObject::sender())->setChecked(true);
//        return;
//    }
//    //TODO: enhance
//    QList<int> selected;

//    for(int i=0; i < m_ImagesTableCheckBoxes.size(); ++i)
//    {
//        if(m_ImagesTableCheckBoxes.at(i)->isChecked())
//            selected.append(i);
//    }

//    if(selected.size() > 0)
//    {
//        m_FindingsButton->setEnabled(true);
//        m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene1.png"));

//        //workaround

//    }
//    else
//    {
//        m_FindingsButton->setEnabled(false);
//        m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene0.png"));
//    }

//    //setting value correspoding to last clicked checkbox
//    if(checked)
//    {
//        for(int k=0; k < m_ImagesTableCheckBoxes.size(); ++k)
//        {
//            if(QObject::sender() == m_ImagesTableCheckBoxes.at(k))
//            {
//                //m_BottomPanelTimepointSlider->setValue(k);
//            }
//        }
//    }

//    for(int l=0; l < m_AnalysisCheckboxes.size();++l)
//    {
//        if(selected.contains(l))
//            m_AnalysisCheckboxes.at(l)->setVisible(true);
//        else
//            m_AnalysisCheckboxes.at(l)->setVisible(false);
//    }


//}

////void MainWindow::on_AddSegmentationToFinding()
////{
////    int idx = m_FindingsSelectComboBox->currentIndex();

////    QString name = QInputDialog::getText(this,"Name Segmentation","Name of Segmentation");

////    if(!name.isEmpty())
////    {
////        QList<QTreeWidgetItem*> items = m_BottomPanelTreeWidget->findItems(m_FindingsSelectComboBox->currentText(),Qt::MatchExactly);

////        if(!items.isEmpty())
////        {
////            //items.first()->addChild(new QTreeWidgetItem(QStringList(name+ " | " + m_Dates.at(m_BottomPanelTimepointSlider->value()))));
////            m_BottomPanelTreeWidget->expandItem(items.first());
////        }
////    }
////}

//void MainWindow::on_ReportComboboxImageWidgetActivation(int selectedID)
//{

//    static int turn = 0;

//    if(selectedID == turn+3 || (turn > 0 && selectedID==turn+2))
//    {
//        m_ImagesButton->setEnabled(true);

//        disconnect(m_ReportComboBox,SIGNAL(currentIndexChanged(int)),this, SLOT(on_ReportComboboxImageWidgetActivation(int)) );
//        if(turn==0)
//            m_ReportComboBox->removeItem(0);
//        QString name = "Report"+QString().setNum((turn+1));
//        m_ReportComboBox->insertItem(turn,name);
//        m_ReportComboBox->setCurrentIndex(turn++);
//        connect(m_ReportComboBox,SIGNAL(currentIndexChanged(int)),this, SLOT(on_ReportComboboxImageWidgetActivation(int)) );


//    }


//    //    else
//    //    {
//    //        if(created)
//    //        {
//    //            int ret = QMessageBox::warning(this,"Report Selection","Are you sure you want to change the current Report?\n\nAll unsaved changes will be lost!",QMessageBox::Yes, QMessageBox::Cancel);

//    //            if(ret == QMessageBox::Yes)
//    //            {
//    //                m_ImagesButton->setEnabled(false);
//    //                m_FindingsButton->setEnabled(false);
//    //                m_AnalysisButton->setEnabled(false);
//    //            }

//    //        }
//    //    }
//}

//void MainWindow::on_AnalysisViewChanged(bool show)
//{
//    if(show && QObject::sender() == m_AnalysisQualitativeRadioButton)
//        m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene4.png"));
//    else if(show && QObject::sender() == m_AnalysisQuantitativeRadioButton)
//        m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene5.png"));
//}

//void MainWindow::on_BottomPanelTreeWidgetItemPressed(QTreeWidgetItem* item, int column)
//{
//    QString text = m_BottomPanelTreeWidget->selectedItems().first()->text(0);

//    if(text.compare(m_FindingsSelectComboBox->itemText(0)))
//        m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene6.png"));
//    else if(text.compare(m_FindingsSelectComboBox->itemText(1)))
//        m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene7.png"));
//    else
//        m_CentralWidgetLabel->setPixmap(QPixmap(":/resources/scene5.png"));
//}

