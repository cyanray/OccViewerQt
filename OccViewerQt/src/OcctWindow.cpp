#include <OccViewerQt/OccViewer/OcctWindow.hpp>

#include <array>

IMPLEMENT_STANDARD_RTTIEXT(OccViewerQt::OcctWindow, Aspect_Window)

namespace OccViewerQt
{
    OcctWindow::OcctWindow(QWidget* widget, const Quantity_NameOfColor background_color)
            : m_Widget(widget)
    {
        SetBackground(background_color);
        m_XLeft = m_Widget->rect().left();
        m_YTop = m_Widget->rect().top();
        m_XRight = m_Widget->rect().right();
        m_YBottom = m_Widget->rect().bottom();
    }

    Aspect_Drawable OcctWindow::NativeParentHandle() const
    {
        QWidget* aParentWidget = m_Widget->parentWidget();
        return aParentWidget ? (Aspect_Drawable) aParentWidget->winId() : Aspect_Drawable{};
    }

    void OcctWindow::Map() const
    {
        m_Widget->show();
        m_Widget->update();
    }

    void OcctWindow::Unmap() const
    {
        m_Widget->hide();
        m_Widget->update();
    }

    Aspect_TypeOfResize OcctWindow::DoResize()
    {
        if (m_Widget->isMinimized()) return Aspect_TOR_UNKNOWN;

        const static std::array<Aspect_TypeOfResize, 11> mode_table =
        {
            Aspect_TOR_NO_BORDER,
            Aspect_TOR_LEFT_BORDER,
            Aspect_TOR_RIGHT_BORDER,
            Aspect_TOR_UNKNOWN,             // UNKNOWN
            Aspect_TOR_TOP_BORDER,
            Aspect_TOR_LEFT_AND_TOP_BORDER,
            Aspect_TOR_TOP_AND_RIGHT_BORDER,
            Aspect_TOR_UNKNOWN,             // UNKNOWN
            Aspect_TOR_BOTTOM_BORDER,
            Aspect_TOR_BOTTOM_AND_LEFT_BORDER,
            Aspect_TOR_RIGHT_AND_BOTTOM_BORDER
        };

        int mask = 0;
        if (Abs(m_Widget->rect().left() - m_XLeft) > 2)
        {
            mask |= 1;
        }
        if (Abs(m_Widget->rect().right() - m_XRight) > 2)
        {
            mask |= 2;
        }
        if (Abs(m_Widget->rect().top() - m_YTop) > 2)
        {
            mask |= 4;
        }
        if (Abs(m_Widget->rect().bottom() - m_YBottom) > 2)
        {
            mask |= 8;
        }

        Aspect_TypeOfResize mode = Aspect_TOR_UNKNOWN;
        if (mask >= 0 && mask < mode_table.size())
        {
            mode = mode_table[mask];
        }

        m_XLeft = m_Widget->rect().left();
        m_XRight = m_Widget->rect().right();
        m_YTop = m_Widget->rect().top();
        m_YBottom = m_Widget->rect().bottom();

        return mode;
    }

    Standard_Real OcctWindow::Ratio() const
    {
        QRect aRect = m_Widget->rect();
        return Standard_Real(aRect.right() - aRect.left()) / Standard_Real(aRect.bottom() - aRect.top());
    }

    void OcctWindow::Size(Standard_Integer& width, Standard_Integer& height) const
    {
        QRect aRect = m_Widget->rect();
        auto dpi = m_Widget->devicePixelRatio();
        width = (Standard_Integer) (aRect.width() * dpi);
        height = (Standard_Integer) (aRect.height() * dpi);
    }

    void OcctWindow::Position(Standard_Integer& x1, Standard_Integer& y1,
                              Standard_Integer& x2, Standard_Integer& y2) const
    {
        x1 = m_Widget->rect().left();
        x2 = m_Widget->rect().right();
        y1 = m_Widget->rect().top();
        y2 = m_Widget->rect().bottom();
    }
}