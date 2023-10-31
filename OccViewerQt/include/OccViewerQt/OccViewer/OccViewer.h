#pragma once


#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>

#include <Standard_WarningsDisable.hxx>
#include <QMainWindow>
#include <Standard_WarningsRestore.hxx>

#include "ViewWidget.hpp"

namespace Ui {
    class OccViewer;
}

namespace OccViewerQt
{
    class OccViewer : public QMainWindow
    {
    Q_OBJECT
    public:
        explicit OccViewer(QWidget *parent = nullptr);
        ~OccViewer() override;
    private:
        Ui::OccViewer *m_ui;

        ViewWidget*                    m_ViewWidget;

        Handle(V3d_Viewer)             m_V3dViewer;
        Handle(AIS_InteractiveContext) m_AISContext;
    };
}