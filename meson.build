project(
    'tinycpp',
    'cpp',
    default_options : ['cpp_std=c++11'],
)

cpp_args = ['-DUNICODE', '-DPCRE_STATIC', '-Wall', '-fno-rtti', '-fno-exceptions', '-O2']
link_args = ['-static', '-Wl,-s']

stdmin = static_library(
    'stdmin',
    'lib/stdmin.cpp',
    cpp_args : cpp_args,
)

pcre = dependency('pcre')

tinycpp_sources = files(
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
    'lib/CRegKey.cpp',
    'lib/CString.cpp',
    'lib/CStringList.cpp',
    'lib/fnmatch.cpp',
    'lib/libapp.cpp',
    'lib/libconv.cpp',
    'lib/libfile.cpp',
    'lib/libhtml.cpp',
    'lib/libpath.cpp',
    'lib/libstr.cpp',
    'lib/libtest.cpp',
    'lib/print.cpp',
    'lib/wdirent.cpp',
)

tinycpp = static_library(
    'tinycpp',
    dependencies : pcre,
    cpp_args : cpp_args,
    sources : tinycpp_sources,
)

install_data('tinycpp.pc', 'stdmin.pc', install_dir : '.')

executable(
    'testcmd',
    'main.cpp',
    gui_app : false,
    include_directories : 'lib',
    dependencies : pcre,
    cpp_args : cpp_args,
    link_args : link_args,
    link_with : [stdmin, tinycpp],
)

tinytest_sources = files(
    'tests/test_CDirent.cpp',
    'tests/test_CDirParser.cpp',
    'tests/test_CFile.cpp',
    'tests/test_CFileInfo.cpp',
    'tests/test_CIniFile.cpp',
    'tests/test_CList.cpp',
    'tests/test_CProcess.cpp',
    'tests/test_CRegKey.cpp',
    'tests/test_CString.cpp',
    'tests/test_CStringList.cpp',
    'tests/test_fnmatch.cpp',
    'tests/test_libapp.cpp',
    'tests/test_libfile.cpp',
    'tests/test_libpath.cpp',
    'tests/test_strconv.cpp',
    'tests/test_strfuncs.cpp',
    'test_main.cpp',
)

exe = executable(
    'tinytest',
    gui_app : false,
    include_directories : 'lib',
    dependencies : pcre,
    cpp_args : cpp_args,
    link_args : link_args,
    sources : tinytest_sources,
    link_with : [stdmin, tinycpp],
)

test('tinytest', exe)


