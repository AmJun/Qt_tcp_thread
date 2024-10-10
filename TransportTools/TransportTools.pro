QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Client.e/ClientMul.exe \
    Client.e/D3Dcompiler_47.dll \
    Client.e/Qt5Core.dll \
    Client.e/Qt5Gui.dll \
    Client.e/Qt5Network.dll \
    Client.e/Qt5Svg.dll \
    Client.e/Qt5Widgets.dll \
    Client.e/bearer/qgenericbearer.dll \
    Client.e/iconengines/qsvgicon.dll \
    Client.e/imageformats/qgif.dll \
    Client.e/imageformats/qicns.dll \
    Client.e/imageformats/qico.dll \
    Client.e/imageformats/qjpeg.dll \
    Client.e/imageformats/qsvg.dll \
    Client.e/imageformats/qtga.dll \
    Client.e/imageformats/qtiff.dll \
    Client.e/imageformats/qwbmp.dll \
    Client.e/imageformats/qwebp.dll \
    Client.e/libEGL.dll \
    Client.e/libGLESv2.dll \
    Client.e/libgcc_s_seh-1.dll \
    Client.e/libstdc++-6.dll \
    Client.e/libwinpthread-1.dll \
    Client.e/opengl32sw.dll \
    Client.e/platforms/qwindows.dll \
    Client.e/styles/qwindowsvistastyle.dll \
    Client.e/translations/qt_ar.qm \
    Client.e/translations/qt_bg.qm \
    Client.e/translations/qt_ca.qm \
    Client.e/translations/qt_cs.qm \
    Client.e/translations/qt_da.qm \
    Client.e/translations/qt_de.qm \
    Client.e/translations/qt_en.qm \
    Client.e/translations/qt_es.qm \
    Client.e/translations/qt_fi.qm \
    Client.e/translations/qt_fr.qm \
    Client.e/translations/qt_gd.qm \
    Client.e/translations/qt_he.qm \
    Client.e/translations/qt_hu.qm \
    Client.e/translations/qt_it.qm \
    Client.e/translations/qt_ja.qm \
    Client.e/translations/qt_ko.qm \
    Client.e/translations/qt_lv.qm \
    Client.e/translations/qt_pl.qm \
    Client.e/translations/qt_ru.qm \
    Client.e/translations/qt_sk.qm \
    Client.e/translations/qt_uk.qm \
    Client.e/translations/qt_zh_TW.qm \
    Server/D3Dcompiler_47.dll \
    Server/Qt5Core.dll \
    Server/Qt5Gui.dll \
    Server/Qt5Network.dll \
    Server/Qt5Svg.dll \
    Server/Qt5Widgets.dll \
    Server/bearer/qgenericbearer.dll \
    Server/iconengines/qsvgicon.dll \
    Server/imageformats/qgif.dll \
    Server/imageformats/qicns.dll \
    Server/imageformats/qico.dll \
    Server/imageformats/qjpeg.dll \
    Server/imageformats/qsvg.dll \
    Server/imageformats/qtga.dll \
    Server/imageformats/qtiff.dll \
    Server/imageformats/qwbmp.dll \
    Server/imageformats/qwebp.dll \
    Server/libEGL.dll \
    Server/libGLESv2.dll \
    Server/libgcc_s_seh-1.dll \
    Server/libstdc++-6.dll \
    Server/libwinpthread-1.dll \
    Server/opengl32sw.dll \
    Server/platforms/qwindows.dll \
    Server/styles/qwindowsvistastyle.dll \
    Server/translations/qt_ar.qm \
    Server/translations/qt_bg.qm \
    Server/translations/qt_ca.qm \
    Server/translations/qt_cs.qm \
    Server/translations/qt_da.qm \
    Server/translations/qt_de.qm \
    Server/translations/qt_en.qm \
    Server/translations/qt_es.qm \
    Server/translations/qt_fi.qm \
    Server/translations/qt_fr.qm \
    Server/translations/qt_gd.qm \
    Server/translations/qt_he.qm \
    Server/translations/qt_hu.qm \
    Server/translations/qt_it.qm \
    Server/translations/qt_ja.qm \
    Server/translations/qt_ko.qm \
    Server/translations/qt_lv.qm \
    Server/translations/qt_pl.qm \
    Server/translations/qt_ru.qm \
    Server/translations/qt_sk.qm \
    Server/translations/qt_uk.qm \
    Server/translations/qt_zh_TW.qm
