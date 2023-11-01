#if !defined _WIN32
#define QT_CLEAN_NAMESPACE         /* avoid definition of INT32 and INT8 */
#endif

#include <OccViewerQt/OccViewer/ViewWidget.hpp>
#include <OccViewerQt/OccViewer/OcctWindow.hpp>

#include <QApplication>
#include <QBoxLayout>
#include <QFileInfo>
#include <QFileDialog>
#include <QMouseEvent>
#include <QMdiSubWindow>
#include <QColorDialog>
#include <QCursor>
#include <QPainter>
#include <QStyleFactory>

#if !defined(_WIN32) && (!defined(__APPLE__) || defined(MACOSX_USE_GLX)) && QT_VERSION < 0x050000
#include <QX11Info>
#endif

#include <Aspect_DisplayConnection.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <Graphic3d_TextureEnv.hxx>


namespace
{
    //! Map Qt buttons bitmask to virtual keys.
    Aspect_VKeyMouse QtMouseButtons2VKeyMouse(Qt::MouseButtons buttons)
    {
        Aspect_VKeyMouse vkey_mouse = Aspect_VKeyMouse_NONE;
        if ((buttons & Qt::LeftButton) != 0)
        {
            vkey_mouse |= Aspect_VKeyMouse_LeftButton;
        }
        if ((buttons & Qt::MiddleButton) != 0)
        {
            vkey_mouse |= Aspect_VKeyMouse_MiddleButton;
        }
        if ((buttons & Qt::RightButton) != 0)
        {
            vkey_mouse |= Aspect_VKeyMouse_RightButton;
        }
        return vkey_mouse;
    }

    //! Map Qt mouse modifiers bitmask to virtual keys.
    Aspect_VKeyFlags QtMouseModifiers2VKeyFlags(Qt::KeyboardModifiers modifiers)
    {
        Aspect_VKeyFlags vkey_flags = Aspect_VKeyFlags_NONE;
        if ((modifiers & Qt::ShiftModifier) != 0)
        {
            vkey_flags |= Aspect_VKeyFlags_SHIFT;
        }
        if ((modifiers & Qt::ControlModifier) != 0)
        {
            vkey_flags |= Aspect_VKeyFlags_CTRL;
        }
        if ((modifiers & Qt::AltModifier) != 0)
        {
            vkey_flags |= Aspect_VKeyFlags_ALT;
        }
        return vkey_flags;
    }
}

namespace OccViewerQt
{

    ViewWidget::ViewWidget(const Handle(AIS_InteractiveContext)& ais_context, QWidget* parent)
            : QWidget(parent),
              m_IsRaytracing(false),
              m_IsShadowsEnabled(true),
              m_IsReflectionsEnabled(false),
              m_IsAntialiasingEnabled(false)
    {
#if !defined(_WIN32) && (!defined(__APPLE__) || defined(MACOSX_USE_GLX)) && QT_VERSION < 0x050000
        XSynchronize(x11Info().display(), true);
#endif
        m_AISContext = ais_context;
        m_CurZoom = 0;

        setAttribute(Qt::WA_PaintOnScreen);
        setAttribute(Qt::WA_NoSystemBackground);

        m_DefaultGestures = myMouseGestureMap;
        m_CurrentMode = CurrentAction3d::Nothing;
        setMouseTracking(true);

        setBackgroundRole(QPalette::NoRole);

        // set focus policy to threat QContextMenuEvent from keyboard
        setFocusPolicy(Qt::StrongFocus);
        setAttribute(Qt::WA_PaintOnScreen);
        setAttribute(Qt::WA_NoSystemBackground);
        Init();
    }

    void ViewWidget::Init()
    {
        if (m_V3dView.IsNull())
        {
            m_V3dView = m_AISContext->CurrentViewer()->CreateView();
        }

        Handle(OcctWindow) hWnd = new OcctWindow(this);
        m_V3dView->SetWindow(hWnd);
        if (!hWnd->IsMapped()) hWnd->Map();


        SetAllowRotation(Standard_True);
        m_V3dView->SetBackgroundColor(Quantity_Color(0.08, 0.08, 0.08, Quantity_TOC_RGB));

        m_V3dView->MustBeResized();

        if (m_IsRaytracing)
        {
            m_V3dView->ChangeRenderingParams().Method = Graphic3d_RM_RAYTRACING;
        }
    }

    void ViewWidget::paintEvent(QPaintEvent*)
    {
        m_V3dView->InvalidateImmediate();
        FlushViewEvents(m_AISContext, m_V3dView, true);
    }

    void ViewWidget::resizeEvent(QResizeEvent*)
    {
        if (m_V3dView.IsNull()) return;
        m_V3dView->MustBeResized();
    }

    void ViewWidget::OnSelectionChanged(const Handle(AIS_InteractiveContext)& context,
                                        const Handle(V3d_View)& view)
    {
        Q_UNUSED(context)
        Q_UNUSED(view)
    }

    void ViewWidget::FitAll()
    {
        if (m_V3dView.IsNull()) return;
        m_V3dView->FitAll();
        m_V3dView->ZFitAll();
        m_V3dView->Redraw();
    }

    void ViewWidget::AxoView()
    {
        if (m_V3dView.IsNull()) return;
        m_V3dView->SetProj(V3d_XposYnegZpos);
        FitAll();
    }

    void ViewWidget::FrontView()
    {
        if (m_V3dView.IsNull()) return;
        m_V3dView->SetProj(V3d_Yneg);
        FitAll();
    }

    void ViewWidget::BackView()
    {
        if (m_V3dView.IsNull()) return;
        m_V3dView->SetProj(V3d_Ypos);
        FitAll();
    }

    void ViewWidget::TopView()
    {
        if (m_V3dView.IsNull()) return;
        m_V3dView->SetProj(V3d_Zpos);
        FitAll();
    }

    void ViewWidget::BottomView()
    {
        if (m_V3dView.IsNull()) return;
        m_V3dView->SetProj(V3d_Zneg);
        FitAll();
    }

    void ViewWidget::LeftView()
    {
        if (m_V3dView.IsNull()) return;
        m_V3dView->SetProj(V3d_Xneg);
        FitAll();
    }

    void ViewWidget::RightView()
    {
        if (m_V3dView.IsNull()) return;
        m_V3dView->SetProj(V3d_Xpos);
        FitAll();
    }

    void ViewWidget::HLROff()
    {
        if (m_V3dView.IsNull()) return;
        QApplication::setOverrideCursor(Qt::WaitCursor);
        m_V3dView->SetComputedMode(Standard_False);
        m_V3dView->Redraw();
        QApplication::restoreOverrideCursor();
    }

    void ViewWidget::HLROn()
    {
        if (m_V3dView.IsNull()) return;
        QApplication::setOverrideCursor(Qt::WaitCursor);
        m_V3dView->SetComputedMode(Standard_True);
        m_V3dView->Redraw();
        QApplication::restoreOverrideCursor();
    }

    void ViewWidget::Shading()
    {
        if (m_V3dView.IsNull()) return;
        m_AISContext->SetDisplayMode(1, Standard_True);
    }

    void ViewWidget::Wireframe()
    {
        if (m_V3dView.IsNull()) return;
        m_AISContext->SetDisplayMode(0, Standard_True);
    }

    void ViewWidget::SetRaytracedShadows(bool state)
    {
        if (m_V3dView.IsNull()) return;
        m_V3dView->ChangeRenderingParams().IsShadowEnabled = state;
        m_IsShadowsEnabled = state;
        m_AISContext->UpdateCurrentViewer();
    }

    void ViewWidget::SetRaytracedReflections(bool state)
    {
        if (m_V3dView.IsNull()) return;
        m_V3dView->ChangeRenderingParams().IsReflectionEnabled = state;
        m_IsReflectionsEnabled = state;
        m_AISContext->UpdateCurrentViewer();
    }

    void ViewWidget::SetRaytracedAntialiasing(bool state)
    {
        if (m_V3dView.IsNull()) return;
        m_V3dView->ChangeRenderingParams().IsAntialiasingEnabled = state;
        m_IsAntialiasingEnabled = state;
        m_AISContext->UpdateCurrentViewer();
    }

    void ViewWidget::EnableRaytracing()
    {
        if (m_V3dView.IsNull()) return;
        if (!m_IsRaytracing)
        {
            m_V3dView->ChangeRenderingParams().Method = Graphic3d_RM_RAYTRACING;
        }
        m_IsRaytracing = true;
        m_AISContext->UpdateCurrentViewer();
    }

    void ViewWidget::DisableRaytracing()
    {
        if (m_IsRaytracing)
        {
            m_V3dView->ChangeRenderingParams().Method = Graphic3d_RM_RASTERIZATION;
        }
        m_IsRaytracing = false;
        m_AISContext->UpdateCurrentViewer();
    }

    QPaintEngine* ViewWidget::paintEngine() const
    {
        return nullptr;
    }

    void ViewWidget::mousePressEvent(QMouseEvent* event)
    {
        Qt::MouseButtons mouose_buttons = event->buttons();
        auto dpi = this->devicePixelRatio();
        const Graphic3d_Vec2i pnt(event->pos().x() * dpi, event->pos().y() * dpi);
        const Aspect_VKeyFlags flags = QtMouseModifiers2VKeyFlags(event->modifiers());
        if (!m_V3dView.IsNull()
            && UpdateMouseButtons(pnt, QtMouseButtons2VKeyMouse(mouose_buttons), flags, false))
        {
            UpdateView();
        }
        m_ClickPos = pnt;
    }

    void ViewWidget::mouseReleaseEvent(QMouseEvent* event)
    {
        Qt::MouseButtons mouse_buttons = event->buttons();
        auto dpi = this->devicePixelRatio();
        const Graphic3d_Vec2i pnt(event->pos().x() * dpi, event->pos().y() * dpi);
        const Aspect_VKeyFlags flags = QtMouseModifiers2VKeyFlags(event->modifiers());
        if (!m_V3dView.IsNull()
            && UpdateMouseButtons(pnt, QtMouseButtons2VKeyMouse(mouse_buttons), flags, false))
        {
            UpdateView();
        }

        if (m_CurrentMode == CurrentAction3d::GlobalPanning)
        {
            m_V3dView->Place(pnt.x(), pnt.y(), m_CurZoom);
        }
        if (m_CurrentMode != CurrentAction3d::Nothing)
        {
            SetCurrentAction(CurrentAction3d::Nothing);
        }
    }

    void ViewWidget::mouseMoveEvent(QMouseEvent* event)
    {
        Qt::MouseButtons mouse_buttons = event->buttons();
        auto dpi = this->devicePixelRatio();
        const Graphic3d_Vec2i new_pos(event->pos().x() * dpi, event->pos().y() * dpi);
        if (!m_V3dView.IsNull()
            && UpdateMousePosition(new_pos, QtMouseButtons2VKeyMouse(mouse_buttons),
                                   QtMouseModifiers2VKeyFlags(event->modifiers()), false))
        {
            UpdateView();
        }
    }

    void ViewWidget::wheelEvent(QWheelEvent* event)
    {
        const Graphic3d_Vec2i pos((int) event->position().x(), (int) event->position().y());
        if (!m_V3dView.IsNull()
            && UpdateZoom(Aspect_ScrollDelta(pos, event->angleDelta().y() / 8.0)))
        {
            UpdateView();
        }
    }


    void ViewWidget::UpdateView()
    {
        update();
    }

    void ViewWidget::DefineMouseGestures()
    {
        myMouseGestureMap.Clear();
        switch (m_CurrentMode)
        {
            case CurrentAction3d::Nothing:
            {
                myMouseGestureMap = m_DefaultGestures;
                break;
            }
            case CurrentAction3d::DynamicZooming:
            {
                myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_Zoom);
                break;
            }
            case CurrentAction3d::GlobalPanning:
            {
                break;
            }
            case CurrentAction3d::WindowZooming:
            {
                myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_ZoomWindow);
                break;
            }
            case CurrentAction3d::DynamicPanning:
            {
                myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_Pan);
                break;
            }
            case CurrentAction3d::DynamicRotation:
            {
                myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_RotateOrbit);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    void ViewWidget::onBackground()
    {
        QColor aColor;
        Standard_Real R1;
        Standard_Real G1;
        Standard_Real B1;
        m_V3dView->BackgroundColor(Quantity_TOC_RGB, R1, G1, B1);
        aColor.setRgb((Standard_Integer) (R1 * 255), (Standard_Integer) (G1 * 255), (Standard_Integer) (B1 * 255));

        QColor aRetColor = QColorDialog::getColor(aColor);
        if (aRetColor.isValid())
        {
            R1 = aRetColor.red() / 255.;
            G1 = aRetColor.green() / 255.;
            B1 = aRetColor.blue() / 255.;
            m_V3dView->SetBackgroundColor(Quantity_TOC_RGB, R1, G1, B1);
        }
        m_V3dView->Redraw();
    }

    void ViewWidget::onTransparency()
    {
/*        AIS_ListOfInteractive anAisObjectsList;
        myContext->DisplayedObjects(anAisObjectsList);
        if (anAisObjectsList.Extent() == 0)
        {
            return;
        }

        double aTranspValue = anAisObjectsList.First()->Transparency();
        DialogTransparency aDlg(this);
        aDlg.setValue(int(aTranspValue * 10));
        connect(&aDlg, SIGNAL(sendTransparencyChanged(int)), SLOT(onTransparencyChanged(int)));
        aDlg.exec();*/
    }

    void ViewWidget::onTransparencyChanged(int value)
    {
        AIS_ListOfInteractive objs;
        m_AISContext->DisplayedObjects(objs);
        double val = value / 10.;
        for (AIS_ListOfInteractive::Iterator it(objs); it.More(); it.Next())
        {
            const auto& ais_obj = it.Value();
            m_AISContext->SetTransparency(ais_obj, val, Standard_False);
        }
        m_AISContext->UpdateCurrentViewer();
    }

    void ViewWidget::TiggerRaytracing(bool checked)
    {
        if (checked)
        {
            EnableRaytracing();
        }
        else
        {
            DisableRaytracing();
        }
    }


}