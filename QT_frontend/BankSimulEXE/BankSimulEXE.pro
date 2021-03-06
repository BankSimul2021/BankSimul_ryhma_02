QT += core gui serialport charts
QT += network svg


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    balance.cpp \
    browse_transactions.cpp \
    deposit.cpp \
    deposit_instructions.cpp \
    graphical_transaction_view.cpp \
    main.cpp \
    main_window.cpp \
    start_window.cpp \
    withdraw.cpp \
    withdraw_done.cpp \
    withdraw_error.cpp

HEADERS += \
    balance.h \
    browse_transactions.h \
    deposit.h \
    deposit_instructions.h \
    graphical_transaction_view.h \
    main_window.h \
    start_window.h \
    withdraw.h \
    withdraw_done.h \
    withdraw_error.h

FORMS += \
    balance.ui \
    browse_transactions.ui \
    deposit.ui \
    deposit_instructions.ui \
    graphical_transaction_view.ui \
    main_window.ui \
    start_window.ui \
    withdraw.ui \
    withdraw_done.ui \
    withdraw_error.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




win32: LIBS += -L$$PWD/../build-DLLPincode-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/ -lDLLPincode

INCLUDEPATH += $$PWD/../DLLPincode
DEPENDPATH += $$PWD/../DLLPincode

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLLRestAPI-Desktop_Qt_5_15_2_MinGW_64_bit-Release/release/ -lDLLRestAPI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLLRestAPI-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/ -lDLLRestAPI

INCLUDEPATH += $$PWD/../DLLRestAPI
DEPENDPATH += $$PWD/../DLLRestAPI

win32: LIBS += -L$$PWD/../build-DLLSerialPort-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/ -lDLLSerialPort

INCLUDEPATH += $$PWD/../DLLSerialPort
DEPENDPATH += $$PWD/../DLLSerialPort

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLLMobileLogin-Desktop_Qt_5_15_2_MinGW_64_bit-Release/release/ -lDLLMobileLogin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLLMobileLogin-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/ -lDLLMobileLogin

INCLUDEPATH += $$PWD/../DLLMobileLogin
DEPENDPATH += $$PWD/../DLLMobileLogin
