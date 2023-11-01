#pragma once

#include <QApplication>
#include <OccViewerQt/OccViewer/OccViewer.h>

namespace OccViewerQt
{

    class OccViewerHelper
    {
    private:
        static int m_argc;
        static char** m_argv;
        QApplication m_QApp;
        OccViewer m_OccViewer;
    public:
        OccViewerHelper() : m_QApp(m_argc, m_argv), m_OccViewer()
        {}

        OccViewer& GetViewer()
        {
            return m_OccViewer;
        }

        void ShowViewerDialog()
        {
            m_OccViewer.show();
            while (true)
            {
                if(!m_OccViewer.isVisible()) break;
                QApplication::processEvents();
            }
        }

        static void GlobalInit(int argc, char* argv[])
        {
            OccViewerHelper::m_argc = argc;
            OccViewerHelper::m_argv = argv;
        }
    };


}