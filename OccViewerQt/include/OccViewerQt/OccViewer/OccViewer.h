#pragma once


#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>

#include <QMainWindow>

#include "ViewWidget.hpp"
#include "OccViewerQt/SettingsDialog/SettingsDialog.h"

namespace Ui
{
    class OccViewer;
}

namespace OccViewerQt
{
    class OccViewer : public QMainWindow
    {
    Q_OBJECT

    public:
        explicit OccViewer(QWidget* parent = nullptr);

        ~OccViewer() override;

        [[nodiscard]] auto& GetAISContext()
        {
            return m_AISContext;
        }

        [[nodiscard]] auto& GetV3dViewer()
        {
            return m_V3dViewer;
        }

        [[nodiscard]] auto& GetV3dView()
        {
            return m_ViewWidget->GetV3dView();
        }

        [[nodiscard]] auto GetViewWidget()
        {
            return m_ViewWidget;
        }

    private:
        Ui::OccViewer* m_ui;

        SettingsDialog* m_SettingsDialog;

        ViewWidget* m_ViewWidget;

        Handle(V3d_Viewer) m_V3dViewer;
        Handle(AIS_InteractiveContext) m_AISContext;

    private:
        void SetupActions();

    };
}