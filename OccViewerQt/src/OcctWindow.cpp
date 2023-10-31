#include <OccViewerQt/OccViewer/OcctWindow.hpp>


IMPLEMENT_STANDARD_RTTIEXT(OccViewerQt::OcctWindow, Aspect_Window)

namespace OccViewerQt
{
    OcctWindow::OcctWindow(QWidget* theWidget, const Quantity_NameOfColor theBackColor)
            : myWidget(theWidget)
    {
        SetBackground(theBackColor);
        myXLeft = myWidget->rect().left();
        myYTop = myWidget->rect().top();
        myXRight = myWidget->rect().right();
        myYBottom = myWidget->rect().bottom();
    }

    Aspect_Drawable OcctWindow::NativeParentHandle() const
    {
        QWidget* aParentWidget = myWidget->parentWidget();
        return aParentWidget ? (Aspect_Drawable) aParentWidget->winId() : (Aspect_Drawable){};
    }

    void OcctWindow::Map() const
    {
        myWidget->show();
        myWidget->update();
    }

    void OcctWindow::Unmap() const
    {
        myWidget->hide();
        myWidget->update();
    }

    Aspect_TypeOfResize OcctWindow::DoResize()
    {
        int aMask = 0;
        Aspect_TypeOfResize aMode = Aspect_TOR_UNKNOWN;

        if (!myWidget->isMinimized())
        {
            if (Abs(myWidget->rect().left() - myXLeft) > 2)
            {
                aMask |= 1;
            }
            if (Abs(myWidget->rect().right() - myXRight) > 2)
            {
                aMask |= 2;
            }
            if (Abs(myWidget->rect().top() - myYTop) > 2)
            {
                aMask |= 4;
            }
            if (Abs(myWidget->rect().bottom() - myYBottom) > 2)
            {
                aMask |= 8;
            }

            switch (aMask)
            {
                case 0:
                    aMode = Aspect_TOR_NO_BORDER;
                    break;
                case 1:
                    aMode = Aspect_TOR_LEFT_BORDER;
                    break;
                case 2:
                    aMode = Aspect_TOR_RIGHT_BORDER;
                    break;
                case 4:
                    aMode = Aspect_TOR_TOP_BORDER;
                    break;
                case 5:
                    aMode = Aspect_TOR_LEFT_AND_TOP_BORDER;
                    break;
                case 6:
                    aMode = Aspect_TOR_TOP_AND_RIGHT_BORDER;
                    break;
                case 8:
                    aMode = Aspect_TOR_BOTTOM_BORDER;
                    break;
                case 9:
                    aMode = Aspect_TOR_BOTTOM_AND_LEFT_BORDER;
                    break;
                case 10:
                    aMode = Aspect_TOR_RIGHT_AND_BOTTOM_BORDER;
                    break;
                default:
                    break;
            }  // end switch

            myXLeft = myWidget->rect().left();
            myXRight = myWidget->rect().right();
            myYTop = myWidget->rect().top();
            myYBottom = myWidget->rect().bottom();
        }

        return aMode;
    }

    Standard_Real OcctWindow::Ratio() const
    {
        QRect aRect = myWidget->rect();
        return Standard_Real(aRect.right() - aRect.left()) / Standard_Real(aRect.bottom() - aRect.top());
    }

    void OcctWindow::Size(Standard_Integer& theWidth, Standard_Integer& theHeight) const
    {
        QRect aRect = myWidget->rect();
        auto dpi = myWidget->devicePixelRatio();
        theWidth = (Standard_Integer)(aRect.width() * dpi);
        theHeight =(Standard_Integer)(aRect.height() * dpi);
    }

    void OcctWindow::Position(Standard_Integer& theX1, Standard_Integer& theY1,
                              Standard_Integer& theX2, Standard_Integer& theY2) const
    {
        theX1 = myWidget->rect().left();
        theX2 = myWidget->rect().right();
        theY1 = myWidget->rect().top();
        theY2 = myWidget->rect().bottom();
    }
}