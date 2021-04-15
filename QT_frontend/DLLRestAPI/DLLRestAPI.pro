QT -= gui
QT += network

TEMPLATE = lib
DEFINES += DLLRESTAPI_LIBRARY

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dll_rest_api.cpp \
    engine_class.cpp

HEADERS += \
    DLLRestAPI_global.h \
    dll_rest_api.h \
    engine_class.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target