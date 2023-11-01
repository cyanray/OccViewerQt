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
              m_ui(new Ui::OccViewer)
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
    }

    OccViewer::~OccViewer()
    {
        delete m_ui;
    }
}