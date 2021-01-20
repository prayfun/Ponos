QT       += core gui widgets sql network

CONFIG += c++17


SOURCES += \
    About.cpp \
    Quit.cpp \
    main.cpp \
    MainWindow.cpp\
    CMyTextBrowser.cpp\
    CLoaderThread.cpp\


HEADERS += \
    About.h \
    MainWindow.h\
    CMyTextBrowser.h\
    CLoaderThread.h\
    Quit.h


FORMS += \
    About.ui \
    MainWindow.ui\
    Quit.ui


CONFIG(debug,debug|release){
      TARGET = "../../run/ShipsBrowser_dbg" #дебажный экзешник
}else{TARGET = "../../run/ShipsBrowser"     #релизный
}

RESOURCES += \
    Res.qrc
