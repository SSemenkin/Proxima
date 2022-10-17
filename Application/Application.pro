QT       += core gui sql network
include(Application.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rd_party/MapGraphics/MapGraphics/release/ -lMapGraphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rd_party/MapGraphics/MapGraphics/debug/ -lMapGraphics

INCLUDEPATH += $$PWD/../3rd_party/MapGraphics/MapGraphics
DEPENDPATH += $$PWD/../3rd_party/MapGraphics/MapGraphics

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rd_party/QSimpleUpdater/release/ -lQSimpleUpdater
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rd_party/QSimpleUpdater/debug/ -lQSimpleUpdater

INCLUDEPATH += $$PWD/../3rd_party/QSimpleUpdater
DEPENDPATH += $$PWD/../3rd_party/QSimpleUpdater

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rd_party/SqlQueryExecutor/release/ -lSqlQueryExecutor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rd_party/SqlQueryExecutor/debug/ -lSqlQueryExecutor

INCLUDEPATH += $$PWD/../3rd_party/SqlQueryExecutor
DEPENDPATH += $$PWD/../3rd_party/SqlQueryExecutor
