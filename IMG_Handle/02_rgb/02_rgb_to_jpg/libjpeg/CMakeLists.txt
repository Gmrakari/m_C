cmake_minimum_required(VERSION 3.10)
project(jpeg_lib C)

set(JPEG_SOURCES
    jaricom.c
    jcapimin.c
    jcapistd.c
    jcarith.c
    jccoefct.c
    jccolor.c
    jcdctmgr.c
    jchuff.c
    jcinit.c
    jcmainct.c
    jcmarker.c
    jcmaster.c
    jcomapi.c
    jcparam.c
    jcprepct.c
    jcsample.c
    jctrans.c
    jdapimin.c
    jdapistd.c
    jdarith.c
    jdatadst.c
    jdatasrc.c
    jdcoefct.c
    jdcolor.c
    jddctmgr.c
    jdhuff.c
    jdinput.c
    jdmainct.c
    jdmarker.c
    jdmaster.c
    jdmerge.c
    jdpostct.c
    jdsample.c
    jdtrans.c
    jerror.c
    jfdctflt.c
    jfdctfst.c
    jfdctint.c
    jidctflt.c
    jidctfst.c
    jidctint.c
    jmemmgr.c
    jmemnobs.c
    jutils.c
    jquant1.c
    jquant2.c
)

set(JPEG_HEADERS
    cderror.h
    cdjpeg.h
    jconfig.h
    jdct.h
    jerror.h
    jinclude.h
    jmemsys.h
    jmorecfg.h
    jpegint.h
    jpeglib.h
    jversion.h
    transupp.h
)

add_library(jpeg ${JPEG_SOURCES} ${JPEG_HEADERS})
target_include_directories(jpeg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS jpeg
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES ${JPEG_HEADERS} DESTINATION include)