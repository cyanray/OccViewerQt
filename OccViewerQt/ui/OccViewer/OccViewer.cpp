#include "OccViewerQt/OccViewer/OccViewer.h"
#include "ui_OccViewer.h"

#include <Standard_WarningsDisable.hxx>
#include <QtWidgets>
#include <Standard_WarningsRestore.hxx>


#include <OpenGl_GraphicDriver.hxx>
#include <OSD_Environment.hxx>

namespace OccViewerQt
{
    OccViewer::OccViewer(QWidget* parent)
        : QMainWindow(parent),
          m_ui(new Ui::OccViewer),
          m_SettingsDialog(new SettingsDialog(this))
    {
        m_ui->setupUi(this);

        static Handle(OpenGl_GraphicDriver) graphic_driver;
        if (graphic_driver.IsNull())
        {
            Handle(Aspect_DisplayConnection) aDisplayConnection;
#if !defined(_WIN32) && !defined(__WIN32__) && (!defined(__APPLE__) || defined(MACOSX_USE_GLX))
            aDisplayConnection = new Aspect_DisplayConnection(OSD_Environment("DISPLAY").Value());
#endif
            graphic_driver = new OpenGl_GraphicDriver(aDisplayConnection);
        }

        Standard_Real view_size{500.0};
        V3d_TypeOfOrientation view_proj{V3d_TypeOfOrientation::V3d_XposYnegZpos};
        Standard_Boolean computed_mode{true};
        Standard_Boolean default_computed_mode{true};

        m_V3dViewer = new V3d_Viewer(graphic_driver);
        m_V3dViewer->SetDefaultViewSize(view_size);
        m_V3dViewer->SetDefaultViewProj(view_proj);
        m_V3dViewer->SetComputedMode(computed_mode);
        m_V3dViewer->SetDefaultComputedMode(default_computed_mode);


        m_V3dViewer->SetDefaultLights();
        m_V3dViewer->SetLightOn();


        m_AISContext = new AIS_InteractiveContext(m_V3dViewer);

        m_ViewWidget = new ViewWidget(m_AISContext, this);
        m_ui->mainVertLayout->addWidget(m_ViewWidget);
        m_ui->actionTrihedron->setChecked(true);
        SetupActions();
    }

    OccViewer::~OccViewer()
    {
        delete m_SettingsDialog;
        delete m_ViewWidget;
        delete m_ui;
    }

    void OccViewer::SetupActions()
    {
        connect(m_ui->actionExit, &QAction::triggered, this, &OccViewer::close);
        connect(m_ui->actionFitAll, &QAction::triggered, m_ViewWidget, &ViewWidget::FitAll);
        connect(m_ui->actionFront, &QAction::triggered, m_ViewWidget, &ViewWidget::FrontView);
        connect(m_ui->actionBack, &QAction::triggered, m_ViewWidget, &ViewWidget::BackView);
        connect(m_ui->actionTop, &QAction::triggered, m_ViewWidget, &ViewWidget::TopView);
        connect(m_ui->actionBottom, &QAction::triggered, m_ViewWidget, &ViewWidget::BottomView);
        connect(m_ui->actionLeft, &QAction::triggered, m_ViewWidget, &ViewWidget::LeftView);
        connect(m_ui->actionRight, &QAction::triggered, m_ViewWidget, &ViewWidget::RightView);
        connect(m_ui->actionAxo, &QAction::triggered, m_ViewWidget, &ViewWidget::AxoView);
        connect(m_ui->actionWireframe, &QAction::triggered, m_ViewWidget, &ViewWidget::Wireframe);
        connect(m_ui->actionShade, &QAction::triggered, m_ViewWidget, &ViewWidget::Shading);
        connect(m_ui->actionRayTracing, &QAction::triggered, m_ViewWidget, &ViewWidget::TriggerRaytracing);
        connect(m_ui->actionShadow, &QAction::triggered, m_ViewWidget, &ViewWidget::SetRaytracedShadows);
        connect(m_ui->actionReflection, &QAction::triggered, m_ViewWidget, &ViewWidget::SetRaytracedReflections);
        connect(m_ui->actionTransparency, &QAction::triggered, m_ViewWidget, &ViewWidget::onTransparency);
        connect(m_ui->actionTrihedron, &QAction::triggered, m_ViewWidget, &ViewWidget::TriggerTrihedron);
        connect(m_ui->actionSettings, &QAction::triggered, m_SettingsDialog, &SettingsDialog::show);
    }

}