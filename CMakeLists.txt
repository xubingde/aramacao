cmake_minimum_required(VERSION 3.10)

project(aramacao VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES aramacao_zh_CN.ts)

qt5_add_resources(qrc_FILES ./qdarkstyle/dark/darkstyle.qrc)
qt5_add_resources(qrc_FILES ./qdarkstyle/light/lightstyle.qrc)

set(PROJECT_SOURCES
        main.cpp
        main.h
        mainwindow.cpp
        mainwindow.h
        actfn.cpp
        actfn.h
        actgetfn.cpp
        actgetfn.h
        acthasfn.cpp
        acthasfn.h
        actisfn.cpp
        actisfn.h
        actsetconstvaluefn.cpp
        actsetconstvaluefn.h
        actsetcopyfn.cpp
        actsetcopyfn.h
        actsetmovefn.cpp
        actsetmovefn.h
        actsetmutvaluefn.cpp
        actsetmutvaluefn.h
        basicblock.cpp
        basicblock.h
        codeeditor.cpp
        codeeditor.h
        comboboxdelegate.cpp
        comboboxdelegate.h
        constexprfunctions.cpp
        constexprfunctions.h
        constructors.cpp
        constructors.h
        copyconstructorfn.cpp
        copyconstructorfn.h
        copyoperatoreqfn.cpp
        copyoperatoreqfn.h
        defaultconstructorfn.cpp
        defaultconstructorfn.h
        deserializefn.cpp
        deserializefn.h
        destructorfn.cpp
        destructorfn.h
        eobject.cpp
        eobject.h
        eqfn.cpp
        eqfn.h
        extfromstringfn.cpp
        extfromstringfn.h
        extswapfn.cpp
        extswapfn.h
        field.cpp
        field.h
        fmt.cpp
        fmt.h
        function.cpp
        function.h
        functions.cpp
        functions.h
        greatereqfn.cpp
        greatereqfn.h
        greaterfn.cpp
        greaterfn.h
        highlighter.cpp
        highlighter.h
        icode.cpp
        icode.h
        includeitem.cpp
        includeitem.h
        infromstringfn.cpp
        infromstringfn.h
        inswapfn.cpp
        inswapfn.h
        itemstack.cpp
        itemstack.h
        label.cpp
        label.h
        lesseqfn.cpp
        lesseqfn.h
        lessfn.cpp
        lessfn.h
        linenumberarea.cpp
        linenumberarea.h
        manager.cpp
        manager.h
        module.cpp
        module.h
        moveconstructorfn.cpp
        moveconstructorfn.h
        moveoperatoreqfn.cpp
        moveoperatoreqfn.h
        myclass.cpp
        myclass.h
        myclassdec.cpp
        myclassdec.h
        myenum.cpp
        myenum.h
        myenumitem.cpp
        myenumitem.h
        mystruct.cpp
        mystruct.h
        mystructdec.cpp
        mystructdec.h
        mytypedef.cpp
        mytypedef.h
        namespaceitem.cpp
        namespaceitem.h
        noteqfn.cpp
        noteqfn.h
        parameter.cpp
        parameter.h
        privatelabel.cpp
        privatelabel.h
        project.cpp
        project.h
        protectedlabel.cpp
        protectedlabel.h
        publiclabel.cpp
        publiclabel.h
        publictype.cpp
        publictype.h
        staticfunctions.cpp
        staticfunctions.h
        tostringfn.cpp
        tostringfn.h
        tpl.cpp
        tpl.h
        tplconstexprfunctions.cpp
        tplconstexprfunctions.h
        tplconstructors.cpp
        tplconstructors.h
        tplfunctions.cpp
        tplfunctions.h
        tplstaticfunctions.cpp
        tplstaticfunctions.h
        twobeforebehind.cpp
        twobeforebehind.h
        fourbeforebehind.cpp
        fourbeforebehind.h
        virtualeqfn.cpp
        virtualeqfn.h
        virtualexchangefn.cpp
        virtualexchangefn.h
        virtuallessfn.cpp
        virtuallessfn.h
        virtualserializefn.cpp
        virtualserializefn.h
        wtbase.cpp
        wtbase.h
        wtbasicblock.cpp
        wtbasicblock.h
        wtlabel.cpp
        wtlabel.h
        wtmyenum.cpp
        wtmyenum.h
        wtprivatelabel.cpp
        wtprivatelabel.h
        wtproject.cpp
        wtproject.h
        wtprotectedlabel.cpp
        wtprotectedlabel.h
        wtpubliclabel.cpp
        wtpubliclabel.h
        wtfn.cpp
        wtfn.h
        wttplfn.cpp
        wttplfn.h
        wtctorfn.cpp
        wtctorfn.h
        wttplctorfn.cpp
        wttplctorfn.h
        wtmyclassdec.cpp
        wtmyclassdec.h
        wtmystructdec.cpp
        wtmystructdec.h
        wtmystruct.cpp
        wtmystruct.h
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(aramacao
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET aramacao APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(aramacao SHARED
            ${PROJECT_SOURCES}
            ${qrc_FILES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(aramacao WIN32
            ${PROJECT_SOURCES}
            ${qrc_FILES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(aramacao PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(aramacao PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(aramacao)
endif()
