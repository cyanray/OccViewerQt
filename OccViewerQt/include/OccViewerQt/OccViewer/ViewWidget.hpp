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

    enum CurrentAction3d
    {
        CurrentAction3d_Nothing,
        CurrentAction3d_DynamicZooming,
        CurrentAction3d_WindowZooming,
        CurrentAction3d_DynamicPanning,
        CurrentAction3d_GlobalPanning,
        CurrentAction3d_DynamicRotation,
        CurrentAction3d_ObjectDececting
    };

    enum ViewAction
    {
        ViewAction_FitAll,
        ViewAction_FitArea,
        ViewAction_Zoom,
        ViewAction_Pan,
        ViewAction_GlobalPan,
        ViewAction_Front,
        ViewAction_Back,
        ViewAction_Top,
        ViewAction_Bottom,
        ViewAction_Left,
        ViewAction_Right,
        ViewAction_Axo,
        ViewAction_Rotation,
        ViewAction_Reset,
        ViewAction_HlrOff,
        ViewAction_HlrOn,
        ViewAction_Shading,
        ViewAction_Wireframe,
        ViewAction_Transparency
    };

    enum RaytraceAction
    {
        RaytraceAction_Raytracing,
        RaytraceAction_Shadows,
        RaytraceAction_Reflections,
        RaytraceAction_Antialiasing
    };

    //! Qt widget containing V3d_View and toolbar with view manipulation buttons.
    //! Also use AIS_ViewController for redirecting user input (mouse, keyboard)
    //! into 3D viewer events (rotation, panning, zooming)
    class ViewWidget : public QWidget, protected AIS_ViewController
    {
    Q_OBJECT

    public:
        ViewWidget(const Handle(AIS_InteractiveContext)& theContext, bool theIs3dView, QWidget* theParent);

        ~ViewWidget() override
        {
            delete myBackMenu;
        }

        void init();

        QList<QAction*> getViewActions();

        QAction* getViewAction(ViewAction theAction);

        QList<QAction*> getRaytraceActions();

        QAction* getRaytraceAction(RaytraceAction theAction);

        void EnableRaytracing();

        void DisableRaytracing();

        void SetRaytracedShadows(bool theState);

        void SetRaytracedReflections(bool theState);

        void SetRaytracedAntialiasing(bool theState);

        bool IsRaytracingMode() const { return myIsRaytracing; }

        bool IsShadowsEnabled() const { return myIsShadowsEnabled; }

        bool IsReflectionsEnabled() const { return myIsReflectionsEnabled; }

        bool IsAntialiasingEnabled() const { return myIsAntialiasingEnabled; }

        static QString GetMessages(int type, TopAbs_ShapeEnum aSubShapeType, TopAbs_ShapeEnum aShapeType);

        static QString GetShapeType(TopAbs_ShapeEnum aShapeType);

        Standard_EXPORT static void OnButtonuseraction(int ExerciceSTEP, Handle(AIS_InteractiveContext)&);

        Standard_EXPORT static void DoSelection(int Id, Handle(AIS_InteractiveContext)&);

        Standard_EXPORT static void OnSetSelectionMode(Handle(AIS_InteractiveContext)&,
                                                       Standard_Integer&,
                                                       TopAbs_ShapeEnum& SelectionMode,
                                                       Standard_Boolean&);

        virtual QPaintEngine* paintEngine() const override;

        const Handle(V3d_View)& getView() const { return myV3dView; }

    signals:

        void selectionChanged();

    public slots:

        void fitAll();

        void axo();

        void hlrOn();

        void hlrOff();

        void shading();

        void wireframe();

        void onTransparency();

        void updateToggled(bool);

        void onBackground();

        void onEnvironmentMap();

        void onRaytraceAction();

    private slots:

        void onTransparencyChanged(int theVal);

    protected:
        virtual void paintEvent(QPaintEvent*) Standard_OVERRIDE;

        virtual void resizeEvent(QResizeEvent*) Standard_OVERRIDE;

        virtual void mousePressEvent(QMouseEvent*) Standard_OVERRIDE;

        virtual void mouseReleaseEvent(QMouseEvent*) Standard_OVERRIDE;

        virtual void mouseMoveEvent(QMouseEvent*) Standard_OVERRIDE;

        virtual void wheelEvent(QWheelEvent*) Standard_OVERRIDE;

        virtual void addItemInPopup(QMenu*);

        Handle(AIS_InteractiveContext)& getContext() { return myContext; }

        void activateCursor(CurrentAction3d);

        CurrentAction3d getCurrentMode() const { return myCurrentMode; }

    private:
        void initCursors();

        void initViewActions();

        void initRaytraceActions();

        QAction* RegisterAction(QString theIconPath, QString thePromt);

    private:
        bool myIsRaytracing;
        bool myIsShadowsEnabled;
        bool myIsReflectionsEnabled;
        bool myIsAntialiasingEnabled;

        bool myIs3dView;

        Handle(V3d_View) myV3dView;
        Handle(AIS_InteractiveContext) myContext;
        AIS_MouseGestureMap myDefaultGestures;
        Graphic3d_Vec2i myClickPos;

        void updateView();

        //! Setup mouse gestures.
        void defineMouseGestures();

        //! Set current action.
        void setCurrentAction(CurrentAction3d theAction)
        {
            myCurrentMode = theAction;
            defineMouseGestures();
        }

        //! Handle selection changed event.
        void OnSelectionChanged(const Handle(AIS_InteractiveContext)& theCtx,
                                const Handle(V3d_View)& theView) Standard_OVERRIDE;

        CurrentAction3d myCurrentMode;
        Standard_Real myCurZoom;
        QMap<ViewAction, QAction*> myViewActions;
        QMap<RaytraceAction, QAction*> myRaytraceActions;
        QMenu* myBackMenu;
        QToolBar* myViewBar;
    };


}