/* : : generated from features/di.iffe by iffe version 2003-03-06 : : */
#ifndef _config_H
#define _config_H	1
#define	_sys_types	1	/* #include <sys/types.h> ok */
#define _hdr_stdio	1	/* #include <stdio.h> ok */
#define _hdr_stdlib	1	/* #include <stdlib.h> ok */
#define _sys_param	1	/* #include <sys/param.h> ok */
#define _key_void	1	/* void is a reserved keyword */
#define _proto_stdc	1	/* Standard-C prototypes ok  */
#define _command_msgfmt	1	/* Is msgfmt available?  */
#undef	_command_gmsgfmt		/* Is gmsgfmt available?  failed */
#define _hdr_ctype	1	/* #include <ctype.h> ok */
#define _hdr_errno	1	/* #include <errno.h> ok */
#undef	_hdr_fshelp		/* #include <fshelp.h> not ok */
#define _hdr_getopt	1	/* #include <getopt.h> ok */
#undef	_hdr_kernel_fs_info		/* #include <kernel/fs_info.h> not ok */
#define _hdr_limits	1	/* #include <limits.h> ok */
#define _hdr_libintl	1	/* #include <libintl.h> ok */
#define _hdr_locale	1	/* #include <locale.h> ok */
#define _hdr_malloc	1	/* #include <malloc.h> ok */
#define _hdr_math	1	/* #include <math.h> ok */
#define _hdr_memory	1	/* #include <memory.h> ok */
#define _hdr_mntent	1	/* #include <mntent.h> ok */
#undef	_hdr_mnttab		/* #include <mnttab.h> not ok */
#undef	_hdr_storage_Directory		/* #include <storage/Directory.h> not ok */
#undef	_hdr_storage_Entry		/* #include <storage/Entry.h> not ok */
#undef	_hdr_storage_Path		/* #include <storage/Path.h> not ok */
#define _hdr_string	1	/* #include <string.h> ok */
#define _hdr_strings	1	/* #include <strings.h> ok */
#define _hdr_time	1	/* #include <time.h> ok */
#define _hdr_unistd	1	/* #include <unistd.h> ok */
#undef	_hdr_windows		/* #include <windows.h> not ok */
#undef	_hdr_zone		/* #include <zone.h> not ok */
#undef	_sys_fs_types		/* #include <sys/fs_types.h> not ok */
#undef	_sys_fstyp		/* #include <sys/fstyp.h> not ok */
#undef	_sys_fstypes		/* #include <sys/fstypes.h> not ok */
#undef	_sys_mntctl		/* #include <sys/mntctl.h> not ok */
#undef	_sys_mntent		/* #include <sys/mntent.h> not ok */
#undef	_sys_mnttab		/* #include <sys/mnttab.h> not ok */
#define _sys_mount	1	/* #include <sys/mount.h> ok */
#define _sys_stat	1	/* #include <sys/stat.h> ok */
#define _sys_statfs	1	/* #include <sys/statfs.h> ok */
#define _sys_statvfs	1	/* #include <sys/statvfs.h> ok */
#define _sys_time	1	/* #include <sys/time.h> ok */
#define _sys_vfs	1	/* #include <sys/vfs.h> ok */
#undef	_sys_vfstab		/* #include <sys/vfstab.h> not ok */
#undef	_sys_vmount		/* #include <sys/vmount.h> not ok */
#define _include_malloc	1	/* Is it safe to include malloc.h?  */
#define _include_string	1	/* Is it safe to include both string.h and strings.h?  */
#undef	_npt_getenv		/* getenv() does not need a prototype */
#undef	_npt_statfs		/* statfs() does not need a prototype */
#define	_sys_times	1	/* #include <sys/times.h> ok */
#define	_hdr_stddef	1	/* #include <stddef.h> ok */
#undef	_typ_statvfs_t		/* statvfs_t is not a type */
#define _typ_size_t	1	/* size_t is a type */
#undef	_typ_uint_t		/* uint_t is not a type */
#define _typ_uid_t	1	/* uid_t is a type */
#define _lib_bcopy	1	/* bcopy() in default lib(s) */
#undef	_LIB_intl		/* -lintl is not a library */
#undef	_LIB_iconv		/* -liconv is not a library */
#define _lib_bindtextdomain	1	/* bindtextdomain() in default lib(s) */
#define _lib_bzero	1	/* bzero() in default lib(s) */
#define _lib_endmntent	1	/* endmntent() in default lib(s) */
#undef	_lib_fmod		/* fmod() not in default lib(s) */
#undef	_lib_fs_stat_dev		/* fs_stat_dev() not in default lib(s) */
#undef	_lib_fshelp		/* fshelp() not in default lib(s) */
#undef	_lib_GetDiskFreeSpace		/* GetDiskFreeSpace() not in default lib(s) */
#undef	_lib_GetDiskFreeSpaceEx		/* GetDiskFreeSpaceEx() not in default lib(s) */
#undef	_lib_GetDriveType		/* GetDriveType() not in default lib(s) */
#undef	_lib_GetLogicalDriveStrings		/* GetLogicalDriveStrings() not in default lib(s) */
#undef	_lib_GetVolumeInformation		/* GetVolumeInformation() not in default lib(s) */
#undef	_lib_getfsstat		/* getfsstat() not in default lib(s) */
#undef	_lib_getmnt		/* getmnt() not in default lib(s) */
#define _lib_getmntent	1	/* getmntent() in default lib(s) */
#undef	_lib_getmntinfo		/* getmntinfo() not in default lib(s) */
#define _lib_getopt	1	/* getopt() in default lib(s) */
#define _lib_gettext	1	/* gettext() in default lib(s) */
#undef	_lib_getvfsstat		/* getvfsstat() not in default lib(s) */
#undef	_lib_getzoneid		/* getzoneid() not in default lib(s) */
#define _lib_hasmntopt	1	/* hasmntopt() in default lib(s) */
#define _lib_memcpy	1	/* memcpy() in default lib(s) */
#define _lib_memset	1	/* memset() in default lib(s) */
#undef	_lib_mntctl		/* mntctl() not in default lib(s) */
#define _lib_setlocale	1	/* setlocale() in default lib(s) */
#define _lib_setmntent	1	/* setmntent() in default lib(s) */
#define _lib_snprintf	1	/* snprintf() in default lib(s) */
#define _lib_statfs	1	/* statfs() in default lib(s) */
#define _lib_statvfs	1	/* statvfs() in default lib(s) */
#undef	_lib_sysfs		/* sysfs() not in default lib(s) */
#define _lib_textdomain	1	/* textdomain() in default lib(s) */
#undef	_lib_zone_getattr		/* zone_getattr() not in default lib(s) */
#undef	_lib_zone_list		/* zone_list() not in default lib(s) */
#define _mth_fmod	1	/* fmod() in math lib */
#undef	_setmntent_1arg		/* does setmntent take one arg?  failed */
#define _setmntent_2arg	1	/* does setmntent take two args?  */
#define _statfs_2arg	1	/* does statfs take 2 args?  */
#undef	_statfs_3arg		/* does statfs take 3 args?  failed */
#undef	_statfs_4arg		/* does statfs take 4 args?  failed */
#define _user_prompt	1	/* ask user for args in setmntent/statfs  */
#define _dcl_errno	1	/* is errno declared?  */
#define _dcl_optind	1	/* is optind declared?  */
#define _dcl_optarg	1	/* is optarg declared?  */
#define _mem_f_bsize_statfs	1	/* f_bsize is a member of struct statfs */
#undef	_mem_f_fsize_statfs		/* f_fsize is not a member of struct statfs */
#undef	_mem_f_iosize_statfs		/* f_iosize is not a member of struct statfs */
#define _mem_f_frsize_statfs	1	/* f_frsize is a member of struct statfs */
#undef	_mem_f_fstypename_statfs		/* f_fstypename is not a member of struct statfs */
#undef	_mem_mount_info_statfs		/* mount_info is not a member of struct statfs */
#define _mem_f_type_statfs	1	/* f_type is a member of struct statfs */
#undef	_mem_mnt_time_mnttab		/* mnt_time is not a member of struct mnttab */
#undef	_mem_vmt_time_vmount		/* vmt_time is not a member of struct vmount */
#define _siz_long_long	8	/* sizeof(long long) */

#if ! _key_void || ! _proto_stdc
# define void int
#endif

#ifndef _
# if _proto_stdc
#  define _(args) args
# else
#  define _(args) ()
# endif
#endif

#if _lib_bindtextdomain && \
_lib_gettext && \
_lib_setlocale && \
_lib_textdomain && \
_hdr_libintl && \
_hdr_locale && \
(_command_msgfmt || _command_gmsgfmt)
# define _enable_nls 1
#else
# define _enable_nls 0
#endif

#if _typ_statvfs_t
# define Statvfs_t statvfs_t
#else
# define Statvfs_t struct statvfs
#endif

#if _typ_size_t
# define Size_t size_t
#else
# define Size_t unsigned int
#endif

#if _typ_uint_t
# define Uint_t uint_t
#else
# define Uint_t unsigned int
#endif

#if _typ_uid_t
# define Uid_t uid_t
#else
# define Uid_t int
#endif

#if _lib_snprintf
# define Snprintf snprintf
# define SPF(a1,a2,a3)      a1,a2,a3
#else
# define Snprintf sprintf
# define SPF(a1,a2,a3)      a1,a3
#endif

#define _config_by_iffe_ 1
#define _config_by_mkconfig_pl_ 0

#endif