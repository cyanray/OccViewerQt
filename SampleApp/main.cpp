#include <QApplication>
#include <OccViewerQt/OccViewer/OccViewer.h>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    OccViewerQt::OccViewer viewer{};
    viewer.show();

    return QApplication::exec();
}
