#pragma once

#include <functional>

#include <Standard_WarningsDisable.hxx>
#include <QAction>
#include <QList>
#include <QMenu>
#include <QToolBar>
#include <QWidget>
#include <Standard_WarningsRestore.hxx>

#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewController.hxx>
#include <V3d_View.hxx>

class TopoDS_Shape;

namespace OccViewerQt
{
    enum class CurrentAction3d
    {
        Nothing,
        DynamicZooming,
        WindowZooming,
        DynamicPanning,
        GlobalPanning,
        DynamicRotation,
        ObjectDececting
    };

    enum class ViewAction
    {
        FitAll,
        FitArea,
        Zoom,
        Pan,
        GlobalPan,
        Front,
        Back,
        Top,
        Bottom,
        Left,
        Right,
        Axo,
        Rotation,
        Reset,
        HlrOff,
        HlrOn,
        Shading,
        Wireframe,
        Transparency
    };

    enum class RaytraceAction
    {
        Raytracing,
        Shadows,
        Reflections,
        Antialiasing
    };

    //! Qt widget containing V3d_View and toolbar with view manipulation buttons.
    //! Also use AIS_ViewController for redirecting user input (mouse, keyboard)
    //! into 3D viewer events (rotation, panning, zooming)
    class ViewWidget : public QWidget, protected AIS_ViewController
    {
    Q_OBJECT

    public:
        ViewWidget(const Handle(AIS_InteractiveContext)& ais_context, QWidget* parent);

        ~ViewWidget() override = default;

        void Init();

        void EnableRaytracing();

        void DisableRaytracing();

        void SetRaytracedShadows(bool state);

        void SetRaytracedReflections(bool state);

        void SetRaytracedAntialiasing(bool state);

        bool IsRaytracingMode() const { return m_IsRaytracing; }

        bool IsShadowsEnabled() const { return m_IsShadowsEnabled; }

        bool IsReflectionsEnabled() const { return m_IsReflectionsEnabled; }

        bool IsAntialiasingEnabled() const { return m_IsAntialiasingEnabled; }

        virtual QPaintEngine* paintEngine() const override;

        const Handle(V3d_View)& getView() const { return m_V3dView; }

    public slots:

        void FitAll();

        void Axo();

        void HLROn();

        void HLROff();

        void Shading();

        void Wireframe();

        void onTransparency();

        void onBackground();

    private slots:

        void onTransparencyChanged(int value);

    protected:
        virtual void paintEvent(QPaintEvent*) Standard_OVERRIDE;

        virtual void resizeEvent(QResizeEvent*) Standard_OVERRIDE;

        virtual void mousePressEvent(QMouseEvent*) Standard_OVERRIDE;

        virtual void mouseReleaseEvent(QMouseEvent*) Standard_OVERRIDE;

        virtual void mouseMoveEvent(QMouseEvent*) Standard_OVERRIDE;

        virtual void wheelEvent(QWheelEvent*) Standard_OVERRIDE;

        auto& GetAISContext() { return m_AISContext; }

        CurrentAction3d GetCurrentMode() const { return m_CurrentMode; }

    private:
        bool m_IsRaytracing;
        bool m_IsShadowsEnabled;
        bool m_IsReflectionsEnabled;
        bool m_IsAntialiasingEnabled;

        CurrentAction3d m_CurrentMode;
        Standard_Real m_CurZoom;

        Handle(V3d_View) m_V3dView;
        Handle(AIS_InteractiveContext) m_AISContext;
        AIS_MouseGestureMap m_DefaultGestures;

        Graphic3d_Vec2i m_ClickPos;

        void UpdateView();

        //! Setup mouse gestures.
        void DefineMouseGestures();

        //! Set current action.
        void SetCurrentAction(CurrentAction3d action)
        {
            m_CurrentMode = action;
            DefineMouseGestures();
        }

        //! Handle selection changed event.
        void OnSelectionChanged(const Handle(AIS_InteractiveContext)& context,
                                const Handle(V3d_View)& view) Standard_OVERRIDE;

    };


}