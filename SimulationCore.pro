#include(../rep-buildproject.pri)

QT       += network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimulationCore
TEMPLATE = lib

DEFINES += SIMULATION_CORE_LIBRARY

CONFIG += c++17
INCLUDEPATH += .

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DynamicMapGraphics/MapGraphics/release/ -lMapGraphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DynamicMapGraphics/MapGraphics/debug/ -lMapGraphics
else:unix:!symbian: LIBS += -L$$OUT_PWD/../DynamicMapGraphics/MapGraphics/ -lMapGraphics

INCLUDEPATH += $$PWD/../DynamicMapGraphics/MapGraphics/
DEPENDPATH += $$PWD/../DynamicMapGraphics/MapGraphics/

SOURCES += \
    Cluster/ClusterRoutingService.cpp \
    Cluster/ClusterSyncService.cpp \
    Core/LocalService.cpp \
    Core/Logger.cpp \
    HeaderWidget.cpp \
    Core/RoutingService.cpp \
    Core/SyncService.cpp \
    Core/ServiceTime.cpp \
    Core/BaseMapAgent.cpp \
    MainWidget.cpp \
#    main.cpp

HEADERS += \
    Core/IGraphicsObject.h \
    Core/Logger.h \
    Core/MemoryManager.h \
    MainWidget.h \
    Cluster/ClusterRoutingService.h \
    Cluster/ClusterSyncService.h \
    Core/INetwork.h \
    Core/LocalService.h \
    HeaderWidget.h \
    Core/RoutingService.h \
    Core/SyncService.h \
    Core/BaseMapAgent.h \
    SimulationCore_global.h \
    api.h \
    Core/ServiceTime.h \
    api/IAgent.h \
    api/IAnnotation.h \
    api/IAuction.h \
    api/IMessage.h \
    api/IMessageHandler.h \
    api/IPopulation.h \
    api/SimulationCoreAPI.h \
    api/errors.h \
    api/func.h \
    api/types.h \

FORMS += \
    HeaderWidget.ui \
    MainWidget.ui \

RESOURCES += \
    core_resources.qrc

