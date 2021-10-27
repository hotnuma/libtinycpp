project(
    'tinycpp',
    ['cpp'],
    version : '1.0',
    license : 'LGPL-2.0',
    default_options : [
        'cpp_std=c++11',
    ],
)

cpp_args = [
    '-Wall',
    '-fno-rtti',
    '-fno-exceptions',
    '-O2',
]

tinycpp_deps = [
    dependency('libpcre'),
]

install_headers(
    'lib/CDirent.h',
    'lib/CDirParser.h',
    'lib/CFile.h',
    'lib/CFileInfo.h',
    'lib/CIniFile.h',
    'lib/CIniLine.h',
    'lib/CIniSection.h',
    'lib/CList.h',
    'lib/CProcess.h',
    'lib/CRegExp.h',
    'lib/CString.h',
    'lib/CStringList.h',
    'lib/deletefunc.h',
    'lib/libapp.h',
    'lib/libconv.h',
    'lib/libhtml.h',
    'lib/libpath.h',
    'lib/libstr.h',
    'lib/libtest.h',
    'lib/print.h',
)

tinycpp_sources = [
    'lib/CDirent.cpp',
    'lib/CDirParser.cpp',
    'lib/CFile.cpp',
    'lib/CFileInfo.cpp',
    'lib/CIniFile.cpp',
    'lib/CIniLine.cpp',
    'lib/CIniSection.cpp',
    'lib/CList.cpp',
    'lib/CProcess.cpp',
    'lib/CRegExp.cpp',
    'lib/CString.cpp',
    'lib/CStringList.cpp',
    'lib/libapp.cpp',
    'lib/libconv.cpp',
    'lib/libhtml.cpp',
    'lib/libpath.cpp',
    'lib/libstr.cpp',
    'lib/libtest.cpp',
    'lib/print.cpp',
]

tinycpp = static_library(
    'tinycpp',
    cpp_args : cpp_args,
    dependencies : tinycpp_deps,
    sources : tinycpp_sources,
    install : true,
)

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : tinycpp,
                 version : '1.0',
                 name : 'libtinycpp',
                 filebase : 'tinycpp',
                 description : 'A simple C++ library.')

tinytest_sources = [
    'tests/test_CDirent.cpp',
    'tests/test_CDirParser.cpp',
    'tests/test_CFile.cpp',
    'tests/test_CFileInfo.cpp',
    'tests/test_CIniFile.cpp',
    'tests/test_CList.cpp',
    'tests/test_CString.cpp',
    'tests/test_CStringList.cpp',
    'tests/test_libapp.cpp',
    'tests/test_libpath.cpp',
    'tests/test_libstr.cpp',
    'test_main.cpp',
]

exe = executable(
    'tinytest',
    include_directories : 'lib',
    cpp_args : cpp_args,
    sources : tinytest_sources,
    link_with : [tinycpp],
)

testcmd_sources = [
    'main.cpp',
]

executable(
    'testcmd',
    include_directories : 'lib',
    cpp_args : cpp_args,
    sources : testcmd_sources,
    link_with : [tinycpp],
)

test('tinytest', exe)


