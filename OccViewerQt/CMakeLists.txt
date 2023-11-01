cmake_minimum_required(VERSION 3.26)
project(OccViewerQt)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)



find_package(OpenCASCADE CONFIG REQUIRED)
# List of available OpenCASCADE libraries for each module
set(OpenCASCADE_FoundationClasses_LIBRARIES TKernel TKMath)
set(OpenCASCADE_ModelingData_LIBRARIES TKG2d TKG3d TKGeomBase TKBRep)
set(OpenCASCADE_ModelingAlgorithms_LIBRARIES TKGeomAlgo TKTopAlgo TKPrim TKBO TKShHealing TKBool TKHLR TKFillet TKOffset TKFeat TKMesh TKXMesh)
set(OpenCASCADE_Visualization_LIBRARIES TKService TKV3d TKOpenGl TKMeshVS TKD3DHost)
set(OpenCASCADE_ApplicationFramework_LIBRARIES TKCDF TKLCAF TKCAF TKBinL TKXmlL TKBin TKXml TKStdL TKStd TKTObj TKBinTObj TKXmlTObj TKVCAF)
set(OpenCASCADE_DataExchange_LIBRARIES TKXDE TKXSBase TKSTEPBase TKSTEPAttr TKSTEP209 TKSTEP TKIGES TKXCAF TKXDEIGES TKXDESTEP TKSTL TKVRML TKRWMesh TKXmlXCAF TKBinXCAF TKXDECascade TKExpress)
set(OpenCASCADE_Draw_LIBRARIES TKDraw TKTopTest TKOpenGlTest TKViewerTest TKD3DHostTest TKXSDRAW TKDCAF TKXDEDRAW TKTObjDRAW TKQADraw)
# List of available OpenCASCADE libraries.
set (OpenCASCADE_LIBRARIES TKernel  TKMath  TKG2d  TKG3d  TKGeomBase  TKBRep  TKGeomAlgo  TKTopAlgo  TKPrim  TKBO  TKShHealing  TKBool  TKHLR  TKFillet  TKOffset  TKFeat  TKMesh  TKXMesh  TKService  TKV3d  TKOpenGl  TKMeshVS  TKD3DHost  TKCDF  TKLCAF  TKCAF  TKBinL  TKXmlL  TKBin  TKXml  TKStdL  TKStd  TKTObj  TKBinTObj  TKXmlTObj  TKVCAF  TKXDE  TKXSBase  TKSTEPBase  TKSTEPAttr  TKSTEP209  TKSTEP  TKIGES  TKXCAF  TKXDEIGES  TKXDESTEP  TKSTL  TKVRML  TKRWMesh  TKXmlXCAF  TKBinXCAF  TKXDECascade  TKExpress  TKDraw  TKTopTest  TKOpenGlTest  TKViewerTest  TKD3DHostTest  TKXSDRAW  TKDCAF  TKXDEDRAW  TKTObjDRAW  TKQADraw)



set(OccViewerQt_INCLUDES
        include/OccViewerQt/OccViewerQt.hpp
        include/OccViewerQt/OccViewer/OccViewer.h
        include/OccViewerQt/OccViewer/ViewWidget.hpp
        include/OccViewerQt/OccViewer/OcctWindow.hpp
        include/OccViewerQt/SettingsDialog/SettingsDialog.h
        include/OccEasyDrawing/EasyDrawing.hpp
        include/OccEasyDrawing/Common/Common.hpp
        include/OccEasyDrawing/Common/ShapeRenderStyle.hpp)

set(OccViewerQt_SRCS
        src/OccViewerQt.cpp
        ui/OccViewer/OccViewer.cpp
        src/ViewWidget.cpp
        src/OcctWindow.cpp
        ui/SettingsDialog/SettingsDialog.cpp
        src/EasyDrawing.cpp)

set(OccViewerQt_UIS
        ui/OccViewer/OccViewer.ui
        ui/SettingsDialog/SettingsDialog.ui)




add_library(OccViewerQt STATIC ${OccViewerQt_INCLUDES} ${OccViewerQt_SRCS} ${OccViewerQt_UIS})
target_include_directories(OccViewerQt PUBLIC include)
target_link_libraries(OccViewerQt PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets)
target_link_libraries(OccViewerQt PUBLIC TKernel  TKMath  TKG2d  TKG3d  TKGeomBase  TKBRep  TKGeomAlgo  TKTopAlgo  TKPrim  TKBO  TKShHealing  TKBool  TKHLR  TKFillet  TKOffset  TKFeat  TKMesh  TKXMesh  TKService  TKV3d  TKOpenGl  TKMeshVS   TKCDF  TKLCAF  TKCAF  TKBinL  TKXmlL  TKBin  TKXml  TKStdL  TKStd  TKTObj  TKBinTObj  TKXmlTObj  TKVCAF  TKXDE  TKXSBase  TKSTEPBase  TKSTEPAttr  TKSTEP209  TKSTEP  TKIGES  TKXCAF  TKXDEIGES  TKXDESTEP  TKSTL  TKVRML  TKRWMesh  TKXmlXCAF  TKBinXCAF  TKXDECascade   )



if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
