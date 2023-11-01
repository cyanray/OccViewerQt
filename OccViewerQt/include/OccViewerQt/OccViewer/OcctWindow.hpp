#pragma once

#include <Aspect_Window.hxx>
#include <QWidget>

namespace OccViewerQt
{
    //!  OcctWindow class implements Aspect_Window interface using Qt API
    //!  as a platform-independent source of window geometry information.
    //!  A similar class should be used instead of platform-specific OCCT
    //!  classes (WNT_Window, Xw_Window) in any Qt 5 application using OCCT
    //!  3D visualization.
    //!
    //!  With Qt 5, the requirement for a Qt-based application to rely fully
    //!  on Qt public API and stop using platform-specific APIs looks mandatory.
    //!  An example of this is changed QWidget event sequence: when a widget is
    //!  first shown on the screen, a resize event is generated before the
    //!  underlying native window is resized correctly, however the QWidget instance
    //!  already holds correct size information at that moment. The OCCT classes
    //!  acting as a source of window geometry for V3d_View class (WNT_Window, Xw_Window)
    //!  are no longer compatible with changed Qt behavior because they rely on
    //!  platform-specific API that cannot return correct window geometry information
    //!  in some cases. A reasonable solution is to provide a Qt-based implementation
    //!  of Aspect_Window interface at application level.
    class OcctWindow : public Aspect_Window
    {
    DEFINE_STANDARD_RTTIEXT(OcctWindow, Aspect_Window)

    public:

        //! Constructor
        explicit OcctWindow(QWidget* widget, Quantity_NameOfColor background_color = Quantity_NOC_MATRAGRAY);

        //! Destructor
        virtual ~OcctWindow()
        {
            m_Widget = nullptr;
        }

        //! Returns native Window handle
        virtual Aspect_Drawable NativeHandle() const Standard_OVERRIDE
        {
            return (Aspect_Drawable) m_Widget->winId();
        }

        //! Returns parent of native Window handle.
        virtual Aspect_Drawable NativeParentHandle() const Standard_OVERRIDE;

        //! Applies the resizing to the window <me>
        virtual Aspect_TypeOfResize DoResize() Standard_OVERRIDE;

        //! Returns True if the window <me> is opened
        //! and False if the window is closed.
        virtual Standard_Boolean IsMapped() const Standard_OVERRIDE
        {
            return !(m_Widget->isMinimized() || m_Widget->isHidden());
        }

        //! Apply the mapping change to the window <me>
        //! and returns TRUE if the window is mapped at screen.
        virtual Standard_Boolean DoMapping() const Standard_OVERRIDE { return Standard_True; }

        //! Opens the window <me>.
        virtual void Map() const Standard_OVERRIDE;

        //! Closes the window <me>.
        virtual void Unmap() const Standard_OVERRIDE;

        virtual void Position(Standard_Integer& x1, Standard_Integer& y1,
                              Standard_Integer& x2, Standard_Integer& y2) const Standard_OVERRIDE;

        //! Returns The Window RATIO equal to the physical
        //! WIDTH/HEIGHT dimensions.
        virtual Standard_Real Ratio() const Standard_OVERRIDE;

        virtual void Size(Standard_Integer& width, Standard_Integer& height) const Standard_OVERRIDE;

        virtual Aspect_FBConfig NativeFBConfig() const Standard_OVERRIDE { return nullptr; }

    protected:
        Standard_Integer m_XLeft;
        Standard_Integer m_YTop;
        Standard_Integer m_XRight;
        Standard_Integer m_YBottom;
        QWidget* m_Widget;
    };
}