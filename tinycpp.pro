TEMPLATE = app
CONFIG = console c++11
#TARGET = tinytest
TARGET = testcmd
CONFIG = c++11
DEFINES =
INCLUDEPATH =

#INCLUDEPATH += \
#    $$DEVFILES/build/pcre/include \
#    lib

HEADERS += \
    lib/CFile.h \
    lib/CFileInfo.h \
    lib/CIniFile.h \
    lib/CIniLine.h \
    lib/CIniSection.h \
    lib/CList.h \
    lib/CProcess.h \
    lib/CRegKey.h \
    lib/CString.h \
    lib/CStringList.h \
    lib/fnmatch.h \
    lib/libapp.h \
    lib/libconv.h \
    lib/libfile.h \
    lib/libpath.h \
    lib/libtest.h \
    lib/print.h \
    lib/wdirent.h \
    lib/CRegExp.h \
    lib/libstr.h \
    lib/libhtml.h \
    lib/CDirParser.h \
    lib/CDirent.h \
    lib/deletefunc.h

SOURCES += \
    lib/CDirent.cpp \
    lib/CFile.cpp \
    lib/CFileInfo.cpp \
    lib/CIniFile.cpp \
    lib/CIniLine.cpp \
    lib/CIniSection.cpp \
    lib/CList.cpp \
    lib/CProcess.cpp \
    lib/CRegKey.cpp \
    lib/CString.cpp \
    lib/CStringList.cpp \
    lib/fnmatch.cpp \
    lib/libapp.cpp \
    lib/libconv.cpp \
    lib/libfile.cpp \
    lib/libpath.cpp \
    lib/libtest.cpp \
    lib/print.cpp \
    lib/wdirent.cpp \
    samples/file_read.cpp \
    samples/proc_cpuinfos.cpp \
    tests/test_CDirent.cpp \
    tests/test_CFile.cpp \
    tests/test_CFileInfo.cpp \
    tests/test_CIniFile.cpp \
    tests/test_CList.cpp \
    tests/test_CProcess.cpp \
    tests/test_CString.cpp \
    tests/test_CStringList.cpp \
    tests/test_fnmatch.cpp \
    tests/test_libapp.cpp \
    tests/test_libfile.cpp \
    tests/test_libpath.cpp \
    tests/test_strfuncs.cpp \
    0Temp.cpp \
    main.cpp \
    test_main.cpp \
    lib/CRegExp.cpp \
    lib/libstr.cpp \
    lib/libhtml.cpp \
    lib/CDirParser.cpp \
    tests/test_CDirParser.cpp \

DISTFILES += \
    meson.build \
    readme.txt \
    install.sh \


