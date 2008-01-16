# Must contain a call to AC_INIT before the checks, and call to
# AC_OUTPUT at the end.
#
# The layout of standard autoconf.ac
#
# AC_INIT(package, version, bug-report-address)
# information on the package
# checks for programs
# checks for libraries
# checks for header files
# checks for types
# checks for structures
# checks for compiler characteristics
# checks for library functions
# checks for system services
# AC_CONFIG_FILES([file...])
# AC_OUTPUT
#

AC_PREREQ(2.59)
AC_INIT(Spartan Cross-Platform Config Library, 0.1.0, cyphactor@gmail.com, lib_sxcfg)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/sxcfg.c])
AM_CONFIG_HEADER([src/sxcfg_config.h])


# checks for programs
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL
AC_PROG_CC

# checks for libraries

case $host in
    # Handle the mingw32 (Windows 32-bit Cross-Compiler options,
    # necessary to be able to build the Windows DLL and link to the
    # proper mingw32 libraries. The '-Wl,--output-def,.libspmf.def'
    # option tells it linker (mingw32 version) to output the
    # .libspmf.def, a file that is used on a Windows machine to build
    # the import .LIB library for the DLL. The '-s' linker option
    # stripts all symbol information from the output file. This reduces
    # the size of the DLL since the mingw32 linker includes all symbols
    # by default.
    *mingw32*) SXCFG_SYSTEM='-Wl,--output-def,.libs/libsxcfg.def,-s' ;;

    # Handle the Mac OS X specific build options such as the
    # '-Wl,-prebind,-seg1addr,0xC0000000' followed by the normal
    # libraries to link to. The '-Wl,-prebind' passing the -prebind
    # option to the linker (ld) to tell it to map the functions to
    # addresses at build time so that applications that use the library
    # don't have to. This increases the loading speed of applications
    # for Mac OS X 10.3 and below. The '-seg1addr,0xC0000000' option
    # specifies to the linker (ld) that the starting address at which it
    # should start binding is 0xC0000000. This is done to avoid overlap
    # of address space mapping.
    #*-apple-darwin*) SXCFG_SYSTEM='-Wl,-prebind,-seg1addr,0xC0000000' ;;

	*-apple-darwin*)
	    SXCFG_SYSTEM="-Wl,-syslibroot,/Developer/SDKs/MacOSX10.4u.sdk -arch i386 -arch ppc"
		CFLAGS="$CFLAGS -isysroot /Developer/SDKs/MacOSX10.4u.sdk -arch i386 -arch ppc"
		;;


    # Handle linking to the proper libraries for all other machines.
    *)          SXCFG_SYSTEM='' ;;
esac

#case $host in
    # Handle setting the propper CFLAGS for the mingw32 build,
    # specifically setting the include path to the project provided
    # include path and defining the PTW32_STATIC_LIB macro so that we
    # can properly build and link to the provided PTW32 static library.
#    *mingw32*)  PMF_CFLAGS='-I../include -DPTW32_STATIC_LIB' ;;

    # Handle setting the propper CFLAGS for all other machines.
#    *)          PMF_CFLAGS='' ;;
#esac

# This is set to replace the default CFLAGS value provided by the
# AC_PROG_CC macro which is '-g -02'. Hence, there will be no more '-g'
# (the debug symbols option), meaning that the default build version of
# the library is the release version.
#CFLAGS='-O2'

AC_SUBST([CFLAGS])
AC_SUBST([SXCFG_SYSTEM])
#AC_SUBST([PMF_CFLAGS])

# checks for header files
AC_HEADER_STDC
#AC_CHECK_HEADERS([arpa/inet.h netinet/in.h string.h sys/socket.h stdint.h])

# checks for types

# checks for structures

# checks for compiler characteristics
AC_C_BIGENDIAN(
[AH_VERBATIM([WORD_BIGENDIAN],
[
/* This a custom Verbatim macro template created to handle proper compiler based big-endian detection on apple machines when building universal binaries. This is needed because autoconf normally will only check the endianness of the system it is running on, not the system that the other systems that are cross-compiled for when building universal binaries. */
#ifdef __APPLE__
#ifdef __BIG_ENDIAN__
#define WORD_BIGENDIAN 1
#endif
#else
#define WORD_BIGENDIAN 1
#endif])],
[AH_VERBATIM([WORD_BIGENDIAN],[
/* This a custom Verbatim macro template created to handle proper compiler based big-endian detection on apple machines when building universal binaries. This is needed because autoconf normally will only check the endianness of the system it is running on, not the system that the other systems that are cross-compiled for when building universal binaries. */
#ifdef __APPLE__
#ifdef __BIG_ENDIAN__
#define WORD_BIGENDIAN 1
#endif
#endif])],
[AH_VERBATIM([WORD_BIGENDIAN],[
/* This a custom Verbatim macro template created to handle proper compiler based big-endian detection on apple machines when building universal binaries. This is needed because autoconf normally will only check the endianness of the system it is running on, not the system that the other systems that are cross-compiled for when building universal binaries. */
#ifdef __APPLE__
#ifdef __BIG_ENDIAN__
#define WORD_BIGENDIAN 1
#endif
#endif])])

# checks for library functions
AC_CHECK_FUNCS([memset])

# checks for system services

AC_CONFIG_FILES([Makefile src/Makefile testing/Makefile])
AC_OUTPUT
