TEMPLATE = app
CONFIG = console c++11
TARGET = tinytest
#TARGET = testcmd
CONFIG = c++11
DEFINES =
INCLUDEPATH = lib

HEADERS += \
    lib/CDirent.h \
    lib/CDirParser.h \
    lib/CFile.h \
    lib/CFileInfo.h \
    lib/CIniFile.h \
    lib/CIniLine.h \
    lib/CIniSection.h \
    lib/CList.h \
    lib/CProcess.h \
    lib/CRegExp.h \
    lib/CString.h \
    lib/CStringList.h \
    lib/deletefunc.h \
    lib/libapp.h \
    lib/libconv.h \
    lib/libfile.h \
    lib/libhtml.h \
    lib/libpath.h \
    lib/libstr.h \
    lib/libtest.h \
    lib/print.h \

SOURCES += \
    lib/CDirent.cpp \
    lib/CDirParser.cpp \
    lib/CFile.cpp \
    lib/CFileInfo.cpp \
    lib/CIniFile.cpp \
    lib/CIniLine.cpp \
    lib/CIniSection.cpp \
    lib/CList.cpp \
    lib/CProcess.cpp \
    lib/CRegExp.cpp \
    lib/CString.cpp \
    lib/CStringList.cpp \
    lib/libapp.cpp \
    lib/libconv.cpp \
    lib/libfile.cpp \
    lib/libhtml.cpp \
    lib/libpath.cpp \
    lib/libstr.cpp \
    lib/libtest.cpp \
    lib/print.cpp \
    tests/test_CDirent.cpp \
    tests/test_CDirParser.cpp \
    tests/test_CFile.cpp \
    tests/test_CFileInfo.cpp \
    tests/test_CIniFile.cpp \
    tests/test_CList.cpp \
    tests/test_CProcess.cpp \
    tests/test_CString.cpp \
    tests/test_CStringList.cpp \
    tests/test_libapp.cpp \
    tests/test_libfile.cpp \
    tests/test_libpath.cpp \
    tests/test_strfuncs.cpp \
    0Temp.cpp \
    main.cpp \
    test_main.cpp \

DISTFILES += \
    install.sh \
    meson.build \
    Readme.txt \


