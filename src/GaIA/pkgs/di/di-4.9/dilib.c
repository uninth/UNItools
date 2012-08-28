/*
$Id$
$Source: /export/home/bll/DI/RCS/dilib.c,v $
Copyright 1994-2006 Brad Lanam, Walnut Creek, CA
*/

/********************************************************/
/*

    This module contains the system specific routines
    to get the actual disk information.

    di_getDiskEntries ()
        Get a list of mounted filesystems.
    di_testRemoteDisk ()
        Checks the partitions to see if they are mounted
        locally or not.
    di_getDiskInfo
        Gets the disk space used/available on the
        partitions we want displayed.

    To Do:
        The following operating systems have
        empty di_getDiskInfo() routines:
            BeOS OSF/1 Ultrix
        These need to be rewritten to separate
        the fetch of mounted partition info, and
        the fetch of disk space.

*/
/********************************************************/

#include "config.h"
#include "di.h"

#include <stdio.h>
#if _hdr_ctype
# include <ctype.h>
#endif
#if _hdr_errno
# include <errno.h>
#endif
#if _hdr_stdlib
# include <stdlib.h>
#endif
#if _sys_types
# include <sys/types.h>
#endif
#if _hdr_string
# include <string.h>
#endif
#if _hdr_strings && ((! defined (_hdr_string)) || (_include_string))
# include <strings.h>
#endif
#if _hdr_memory
# include <memory.h>
#endif
#if _include_malloc && _hdr_malloc
# include <malloc.h>
#endif
#if _hdr_unistd
# include <unistd.h>
#endif
#if _hdr_time
# include <time.h>
#endif
#if _sys_time
# include <sys/time.h>
#endif
#if _sys_stat
# include <sys/stat.h>
#endif
#if _sys_param
# include <sys/param.h>
#endif

#if _sys_mnttab
# include <sys/mnttab.h>
#endif
#if _hdr_mnttab
# include <mnttab.h>
#endif
#if _hdr_mntent
# include <mntent.h>
#endif
#if _sys_mntent
# include <sys/mntent.h>
#endif
#if _sys_mount
# include <sys/mount.h>
#endif
#if _sys_fstypes
# include <sys/fstypes.h>
#endif
#if _sys_fs_types
# include <sys/fs_types.h>
#endif
#if _sys_mntctl
# include <sys/mntctl.h>
#endif
#if _sys_vmount
# include <sys/vmount.h>
#endif
#if _sys_statfs && ! defined (_sys_statvfs)
# include <sys/statfs.h>
#endif
#if _hdr_fshelp
# include <fshelp.h>
#endif
#if _sys_statvfs
# include <sys/statvfs.h>
#endif
#if _sys_fstyp
# include <sys/fstyp.h>
# define DI_TYPE_LEN          FSTYPSZ
#endif
#if _sys_vfs
# include <sys/vfs.h>
#endif
#if _sys_vfstab
# include <sys/vfstab.h>
# if ! defined (DI_TYPE_LEN)
#  define DI_TYPE_LEN         FSTYPSZ
# endif
#endif

#if _hdr_windows
# include <windows.h>            /* windows */
#endif
#if _hdr_kernel_fs_info
# include <kernel/fs_info.h>
#endif
#if _hdr_storage_Directory
# include <storage/Directory.h>
#endif
#if _hdr_storage_Entry
# include <storage/Entry.h>
#endif
#if _hdr_storage_Path
# include <storage/Path.h>
#endif

/********************************************************/

    /* remap mount flags */
# if defined (M_RDONLY)
#  define MNT_RDONLY M_RDONLY
# endif
# if defined (MNT_READONLY)
#  define MNT_RDONLY MNT_READONLY
# endif
# if defined (M_RONLY)
#  define MNT_RDONLY M_RONLY
# endif
# if defined (M_SYNCHRONOUS)
#  define MNT_SYNCHRONOUS M_SYNCHRONOUS
# endif
# if defined (M_NOEXEC)
#  define MNT_NOEXEC M_NOEXEC
# endif
# if defined (M_NOSUID)
#  define MNT_NOSUID M_NOSUID
# endif
# if defined (M_NODEV)
#  define MNT_NODEV M_NODEV
# endif
# if defined (M_NOATIMES)
#  define MNT_NOATIMES M_NOATIMES
# endif
# if defined (M_GRPID)
#  define MNT_GRPID M_GRPID
# endif
# if defined (M_SECURE)
#  define MNT_SECURE M_SECURE
# endif
# if defined (M_MLSD)
#  define MNT_MLSD M_MLSD
# endif
# if defined (M_SMSYNC2)
#  define MNT_SMSYNC2 M_SMSYNC2
# endif
# if defined (M_LOCAL)
#  define MNT_LOCAL M_LOCAL
# endif
# if defined (M_FORCE)
#  define MNT_FORCE M_FORCE
# endif
# if defined (M_SYNC)
#  define MNT_SYNC M_SYNC
# endif
# if defined (M_NOCACHE)
#  define MNT_NOCACHE M_NOCACHE
# endif

static void convertMountOptions _((long, di_DiskInfo *));
static void convertNFSMountOptions _((long, long, long, di_DiskInfo *));
static void trimChar _((char *, int));
#if _lib_getmntent && \
	! defined (_lib_mntctl)
static char *chkMountOptions _((char *, char *));
#endif


/********************************************************/

#if (_lib_getmntent || \
        _statfs_2arg || \
        _statfs_3arg || \
        _statfs_4arg) && \
        ! defined (_lib_getmntinfo) && \
        ! defined (_lib_getfsstat) && \
        ! defined (_lib_getvfsstat) && \
        ! defined (_lib_mntctl) && \
        ! defined (_lib_getmnt)
# if defined (MOUNTED)
#  define DI_MOUNT_FILE        MOUNTED
# else
#  if defined (MNTTAB)
#   define DI_MOUNT_FILE       MNTTAB
#  else
#   if (USE_ETC_FILESYSTEMS)
#    define DI_MOUNT_FILE       "/etc/filesystems" /* AIX 4.x or /etc/mntent? */
#   else
#    define DI_MOUNT_FILE       "/etc/mnttab"
#   endif
#  endif
# endif
#endif

#if ! defined (_lib_statvfs) && \
	_lib_statfs && \
	_npt_statfs
# if _statfs_2arg
  extern int statfs _((char *, struct statfs *));
# endif
# if _statfs_3arg
  extern int statfs _((char *, struct statfs *, int));
# endif
# if _statfs_4arg
  extern int statfs _((char *, struct statfs *, int, int));
# endif
#endif

#if _statfs_4arg && \
    ! defined (_lib_statvfs) && \
    ! defined (_lib_getmntinfo) && \
    ! defined (_lib_getfsstat) && \
    ! defined (_lib_getvfsstat) && \
    ! defined (_lib_getmnt) /* SYSV.3 */
# if ! defined (UBSIZE)
#  if defined (BSIZE)
#   define UBSIZE            BSIZE
#  else
#   define UBSIZE            512
#  endif
# endif
#endif

/********************************************************/

#if defined (MNTOPT_IGNORE)
# define DI_MNTOPT_IGNORE MNTOPT_IGNORE
#else
# define DI_MNTOPT_IGNORE "ignore"
#endif

#if defined (MNTOPT_RO)
# define DI_MNTOPT_RO MNTOPT_RO
#else
# define DI_MNTOPT_RO "ro"
#endif

#if defined (MNTOPT_DEV)
# define DI_MNTOPT_DEV MNTOPT_DEV
#else
# define DI_MNTOPT_DEV "dev="
#endif

/********************************************************/

#define DI_UNKNOWN_FSTYPE       "Unknown fstyp %.2d"

int di_lib_debug = { 0 };

#if _lib_fs_stat_dev

/*
 * di_getDiskEntries
 *
 * For BeOS.
 *
 */

int
# if _proto_stdc
di_getDiskEntries (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskEntries (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo     *diptr;
    status_t        stat;
    int             idx;
    int32           count;
    dev_t           dev;
    char            buff [B_FILE_NAME_LENGTH];
    fs_info         fsinfo;
    node_ref        nref;
    BDirectory      *dir;
    BEntry          entry;
    BPath           path;

    if (di_lib_debug > 0) { printf ("# lib:getDiskEntries: fs_stat_dev\n"); }
    count = 0;
    while ((dev = next_dev (&count)) != B_BAD_VALUE)
    {
        if ((stat = fs_stat_dev (dev, &fsinfo)) == B_BAD_VALUE)
        {
            break;
        }

        idx = *diCount;
        ++*diCount;
        *diskInfo = (di_DiskInfo *) Realloc ((char *) *diskInfo,
                sizeof (di_DiskInfo) * *diCount);
        diptr = *diskInfo + idx;
        memset ((char *) diptr, '\0', sizeof (di_DiskInfo));
        diptr->printFlag = DI_PRNT_OK;
        *buff = '\0';
        nref.device = dev;
        nref.node = fsinfo.root;
        dir = new BDirectory (&nref);
        stat = dir->GetEntry (&entry);
        stat = entry.GetPath (&path);
        strncpy (diptr->name, path.Path (), DI_NAME_LEN);
        strncpy (diptr->special, fsinfo.device_name, DI_SPEC_NAME_LEN);
        strncpy (diptr->fsType, fsinfo.fsh_name, DI_TYPE_LEN);
        diptr->isLocal = TRUE;
        diptr->isReadOnly = FALSE;
        diptr->blockSize = (_fs_size_t) fsinfo.block_size;
        diptr->totalBlocks = (_fs_size_t) fsinfo.total_blocks;
        diptr->freeBlocks = (_fs_size_t) fsinfo.free_blocks;
        diptr->availBlocks = (_fs_size_t) fsinfo.free_blocks;
        diptr->totalInodes = fsinfo.total_nodes;
        diptr->freeInodes = fsinfo.free_nodes;
        diptr->availInodes = fsinfo.free_nodes;

        if (di_lib_debug > 0)
        {
            printf ("mnt:%s - %s\n", diptr->name,
                    diptr->special);
            printf ("dev:%d fs:%s\n", dev, diptr->fsType);
        }
        if (di_lib_debug > 1)
        {
            printf ("%s: %s\n", diptr->name, diptr->fsType);
            printf ("\tblocks: tot:%ld free:%ld\n",
                    fsinfo.total_blocks, fsinfo.free_blocks);
            printf ("\tinodes: tot:%ld free:%ld\n",
                    fsinfo.total_nodes, fsinfo.free_nodes);
        }
    }
    return 0;
}

#endif

#if _lib_getmntent && \
	! defined (_lib_setmntent) && \
	! defined (_lib_mntctl)

/*
 * di_getDiskEntries
 *
 * For SysV.4, we open the file and call getmntent () repeatedly.
 *
 */

static char *checkMountOptions _((struct mnttab *, char *));

int
# if _proto_stdc
di_getDiskEntries (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskEntries (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo     *diptr;
    FILE            *f;
    int             idx;
    struct mnttab   mntEntry;
    time_t          mtime;
    char            *devp;   /* local ptr to dev entry */


    if (di_lib_debug > 0) { printf ("# lib:getDiskEntries: _lib_getmntent\n"); }
    if ((f = fopen (DI_MOUNT_FILE, "r")) == (FILE *) NULL)
    {
        fprintf (stderr, "Unable to open: %s errno %d\n", DI_MOUNT_FILE, errno);
        return -1;
    }

    while (getmntent (f, &mntEntry) == 0)
    {
        idx = *diCount;
        ++*diCount;
        *diskInfo = (di_DiskInfo *) Realloc ((char *) *diskInfo,
                sizeof (di_DiskInfo) * *diCount);
        diptr = *diskInfo + idx;
        memset ((char *) diptr, '\0', sizeof (di_DiskInfo));
        diptr->printFlag = DI_PRNT_OK;
        diptr->isLocal = TRUE;
        diptr->isReadOnly = FALSE;

        strncpy (diptr->special, mntEntry.mnt_special, DI_SPEC_NAME_LEN);
        strncpy (diptr->name, mntEntry.mnt_mountp, DI_NAME_LEN);
        if (checkMountOptions (&mntEntry, DI_MNTOPT_IGNORE) != (char *) NULL)
        {
            diptr->printFlag = DI_PRNT_IGNORE;
            if (di_lib_debug > 2)
            {
                printf ("mnt: ignore: mntopt 'ignore': %s\n",
                        diptr->name);
            }
        }
        if ((devp = checkMountOptions (&mntEntry, DI_MNTOPT_DEV)) !=
                (char *) NULL)
        {
            if (devp != mntEntry.mnt_mntopts)
            {
                --devp;
            }
            *devp = 0;   /* point to preceeding comma and cut off */
        }
        if (checkMountOptions (&mntEntry, DI_MNTOPT_RO) != (char *) NULL)
        {
            diptr->isReadOnly = TRUE;
        }
        strncpy (diptr->options, mntEntry.mnt_mntopts, DI_OPT_LEN);
        mtime = atol (mntEntry.mnt_time);
        strncpy (diptr->mountTime, ctime (&mtime), DI_MNT_TIME_LEN);

            /* get the file system type now... */
        strncpy (diptr->fsType, mntEntry.mnt_fstype, DI_TYPE_LEN);
        if (di_lib_debug > 2)
        {
            printf ("mnt:%s - %s\n", diptr->name, diptr->fsType);
        }

        if (di_lib_debug > 0)
        {
            printf ("mnt:%s - %s\n", diptr->name, diptr->special);
        }
    }

    fclose (f);
    return 0;
}

static char *
# if _proto_stdc
checkMountOptions (struct mnttab *mntEntry, char *str)
# else
checkMountOptions (mntEntry, str)
    struct mnttab *mntEntry;
    char          *str;
# endif
{
# if _lib_hasmntopt
    return hasmntopt (mntEntry, str);
# else
    return chkMountOptions (mntEntry->mnt_mntopts, str);
# endif
}
#endif /* _lib_getmntent */

#if _lib_getmntent && \
	! defined (_lib_mntctl)

static char *
# if _proto_stdc
chkMountOptions (char *mntopts, char *str)
# else
chkMountOptions (mntopts, str)
    char          *mntopts;
    char          *str;
# endif
{
    char    *ptr;
    char    *tstr;

    tstr = strdup (mntopts);
    ptr = strtok (tstr, ",");
    while (ptr != (char *) NULL)
    {
        if (strcmp (ptr, str) == 0)
        {
            free (tstr);
            return ptr;
        }
        ptr = strtok ((char *) NULL, ",");
    }
    free (tstr);
    return (char *) NULL;
}

#endif /* _lib_getmntent */

#if _lib_statvfs && \
    ! defined (_lib_getmntinfo) && \
    ! defined (_lib_getfsstat) && \
    ! defined (_lib_getvfsstat) && \
    ! defined (_lib_GetVolumeInformation)

/*
 * di_getDiskInfo
 *
 * SysV.4.  statvfs () returns both the free and available blocks.
 *
 */

# define DI_GETDISKINFO_DEF 1

void
# if _proto_stdc
di_getDiskInfo (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskInfo (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo     *diptr;
    int             i;
    Statvfs_t       statBuf;

    if (di_lib_debug > 0) { printf ("# lib:getDiskInfo: statvfs\n"); }
    for (i = 0; i < *diCount; ++i)
    {
        diptr = *diskInfo + i;

        if (diptr->printFlag == DI_PRNT_OK)
        {
            if (statvfs (diptr->name, &statBuf) == 0)
            {
                    /* data general DG/UX 5.4R3.00 sometime returns 0   */
                    /* in the fragment size field.                      */
                if (statBuf.f_frsize == 0 && statBuf.f_bsize != 0)
                {
                    diptr->blockSize = statBuf.f_bsize;
                }
                else
                {
                    diptr->blockSize = statBuf.f_frsize;
                }
/* Linux! statvfs() returns values in f_bsize rather f_frsize.  Bleah.  */
/* Non-POSIX!  Linux manual pages are incorrect.                        */
#  if linux
                diptr->blockSize = statBuf.f_bsize;
#  endif /* linux */

                diptr->totalBlocks = (_fs_size_t) statBuf.f_blocks;
                diptr->freeBlocks = (_fs_size_t) statBuf.f_bfree;
                diptr->availBlocks = (_fs_size_t) statBuf.f_bavail;

                diptr->totalInodes = (_fs_size_t) statBuf.f_files;
                diptr->freeInodes = (_fs_size_t) statBuf.f_ffree;
                diptr->availInodes = (_fs_size_t) statBuf.f_favail;

                if (di_lib_debug > 1)
                {
                    printf ("%s: %s\n", diptr->name, diptr->fsType);
                    printf ("\tbsize:%ld  frsize:%ld\n", (long) statBuf.f_bsize,
                            (long) statBuf.f_frsize);
#if _siz_long_long >= 8
                    printf ("\tblocks: tot:%llu free:%lld avail:%llu\n",
                           statBuf.f_blocks, statBuf.f_bfree, statBuf.f_bavail);
                    printf ("\tinodes: tot:%llu free:%llu avail:%llu\n",
                            statBuf.f_files, statBuf.f_ffree, statBuf.f_favail);
#else
                    printf ("\tblocks: tot:%lu free:%lu avail:%lu\n",
                           statBuf.f_blocks, statBuf.f_bfree, statBuf.f_bavail);
                    printf ("\tinodes: tot:%lu free:%lu avail:%lu\n",
                            statBuf.f_files, statBuf.f_ffree, statBuf.f_favail);
#endif
                }
            }
            else
            {
                fprintf (stderr, "statvfs: %s ", diptr->name);
                perror ("");
            }
        }
    } /* for each entry */
}

#endif /* _lib_statvfs */

#if ! defined (_lib_getmntent) && \
    ! defined (_lib_mntctl) && \
    ! defined (_lib_getmntinfo) && \
    ! defined (_lib_getfsstat) && \
    ! defined (_lib_getvfsstat) && \
    ! defined (_lib_getmnt) && \
    ! defined (_lib_GetDiskFreeSpace) && \
    ! defined (_lib_GetDiskFreeSpaceEx) && \
    ! defined (_lib_fs_stat_dev)

/*
 * di_getDiskEntries
 *
 * For SysV.3 we open the file and read it ourselves.
 *
 */

int
# if _proto_stdc
di_getDiskEntries (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskEntries (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    FILE             *f;
    int              idx;
    struct mnttab    mntEntry;


    if (di_lib_debug > 0) { printf ("# lib:getDiskEntries: not anything; sys v.3\n"); }
    if ((f = fopen (DI_MOUNT_FILE, "r")) == (FILE *) NULL)
    {
        fprintf (stderr, "Unable to open: %s errno %d\n", DI_MOUNT_FILE, errno);
        return -1;
    }

    while (fread ((char *) &mntEntry, sizeof (struct mnttab), 1, f) == 1)
    {
            /* xenix allows null mount table entries */
            /* sco nfs background mounts are marked as "nothing" */
        if (mntEntry.mt_filsys [0] &&
                strcmp (mntEntry.mt_filsys, "nothing") != 0)
        {
            idx = *diCount;
            ++*diCount;
            *diskInfo = (di_DiskInfo *) Realloc ((char *) *diskInfo,
                    sizeof (di_DiskInfo) * *diCount);
            memset ((char *) diptr, '\0', sizeof (di_DiskInfo));
            diptr->printFlag = DI_PRNT_OK;
            diptr->isLocal = TRUE;
            diptr->isReadOnly = FALSE;

# if defined (COHERENT)
                /* Coherent seems to have these fields reversed. oh well. */
            strncpy (diptr->name, mntEntry.mt_dev, DI_NAME_LEN);
            strncpy (diptr->special, mntEntry.mt_filsys, DI_SPEC_NAME_LEN);
# else
            strncpy (diptr->special, mntEntry.mt_dev, DI_SPEC_NAME_LEN);
            strncpy (diptr->name, mntEntry.mt_filsys, DI_NAME_LEN);
# endif
            strncpy (diptr->options, mntEntry.mnt_mntopts, DI_OPT_LEN);
            strncpy (diptr->mountTime, mntEntry.mnt_time,
                    DI_MNT_TIME_LEN);
        }

        if (di_lib_debug > 0)
        {
            printf ("mnt:%s - %s\n", diptr->name,
                    diptr->special);
        }
    }

    fclose (f);
    return 0;
}


#endif /* Sys V.3 */

#if _statfs_4arg && \
    ! defined (_lib_statvfs) && \
    ! defined (_lib_getmntinfo) && \
    ! defined (_lib_getfsstat) && \
    ! defined (_lib_getvfsstat) && \
    ! defined (_lib_getmnt)

/*
 * di_getDiskInfo
 *
 * SysV.3.  We don't have available blocks; just set it to free blocks.
 * The sysfs () call is used to get the disk type name.
 *
 */

# define DI_GETDISKINFO_DEF 1

void
# if _proto_stdc
di_getDiskInfo (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskInfo (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo     *diptr;
    int             i;
    struct statfs   statBuf;

    if (di_lib_debug > 0) { printf ("# lib:getDiskInfo: sysv-statfs 4arg\n"); }
    for (i = 0; i < *diCount; ++i)
    {
        diptr = *diskInfo + i;
        if (diptr->printFlag == DI_PRNT_OK)
        {
            if (statfs (diptr->name, &statBuf, sizeof (statBuf), 0) == 0)
            {
# if _mem_f_frsize_statfs
                if (statBuf.f_frsize == 0 && statBuf.f_bsize != 0)
                {
                    diptr->blockSize = (_fs_size_t) statBuf.f_bsize;
                }
                else
                {
                    diptr->blockSize = (_fs_size_t) statBuf.f_frsize;
                }
# else
                diptr->blockSize = UBSIZE;
# endif
                diptr->totalBlocks = (_fs_size_t) statBuf.f_blocks;
                diptr->freeBlocks = (_fs_size_t) statBuf.f_bfree;
                diptr->availBlocks = (_fs_size_t) statBuf.f_bfree;

                diptr->totalInodes = statBuf.f_files;
                diptr->freeInodes = statBuf.f_ffree;
                diptr->availInodes = statBuf.f_ffree;
# if _lib_sysfs
                sysfs (GETFSTYP, statBuf.f_fstyp, diptr->fsType);
# endif

                if (di_lib_debug > 1)
                {
                    printf ("%s: %s\n", diptr->name, diptr->fsType);
# if _mem_f_frsize_statfs
                    printf ("\tbsize:%ld\n", statBuf.f_bsize);
                    printf ("\tfrsize:%ld\n", statBuf.f_frsize);
# else
                    printf ("\tUBSIZE:%ld\n", UBSIZE);
# endif
                    printf ("\tblocks: tot:%ld free:%ld\n",
                            statBuf.f_blocks, statBuf.f_bfree);
                    printf ("\tinodes: tot:%ld free:%ld\n",
                            statBuf.f_files, statBuf.f_ffree);
                }
            } /* if we got the info */
            else
            {
                fprintf (stderr, "statfs: %s ", diptr->name);
                perror ("");
            }
        }
    } /* for each entry */
}

#endif /* _statfs_4arg */


#if _lib_getmntent && \
    _lib_setmntent && \
    _lib_endmntent && \
    ! defined (_lib_mntctl) && \
    ! defined (_lib_GetDiskFreeSpace) && \
    ! defined (_lib_GetDiskFreeSpaceEx)

/*
 * di_getDiskEntries
 *
 * SunOS supplies an open and close routine for the mount table.
 *
 */

#if ! defined (MNTTYPE_IGNORE)
# define MNTTYPE_IGNORE "ignore"
#endif

int
# if _proto_stdc
di_getDiskEntries (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskEntries (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo     *diptr;
    FILE            *f;
    int             idx;
    struct mntent   *mntEntry;
    char            *devp;   /* local ptr to dev entry */


    if (di_lib_debug > 0) { printf ("# lib:getDiskEntries: get/set/endmntent\n"); }
#if _setmntent_1arg || ! defined (_setmntent_2arg)
    if ((f = setmntent (DI_MOUNT_FILE)) == (FILE *) NULL)
#else
    if ((f = setmntent (DI_MOUNT_FILE, "r")) == (FILE *) NULL)
#endif
    {
        fprintf (stderr, "Unable to open: %s errno %d\n", DI_MOUNT_FILE, errno);
        return -1;
    }

    while ((mntEntry = getmntent (f)) != (struct mntent *) NULL)
    {
        idx = *diCount;
        ++*diCount;
        *diskInfo = (di_DiskInfo *) Realloc ((char *) *diskInfo,
                sizeof (di_DiskInfo) * *diCount);
        diptr = *diskInfo + idx;
        memset ((char *) diptr, '\0', sizeof (di_DiskInfo));
        diptr->printFlag = DI_PRNT_OK;
        diptr->isLocal = TRUE;
        diptr->isReadOnly = FALSE;

        strncpy (diptr->special, mntEntry->mnt_fsname, DI_SPEC_NAME_LEN);
        strncpy (diptr->name, mntEntry->mnt_dir, DI_NAME_LEN);
        strncpy (diptr->fsType, mntEntry->mnt_type, DI_TYPE_LEN);

        if (strcmp (mntEntry->mnt_fsname, "none") == 0)
        {
            diptr->printFlag = DI_PRNT_IGNORE;
            if (di_lib_debug > 2)
            {
                printf ("mnt: ignore: fstype 'none': %s\n",
                        diptr->name);
            }
        }

        if (strcmp (mntEntry->mnt_type, MNTTYPE_IGNORE) == 0)
        {
            diptr->printFlag = DI_PRNT_IGNORE;
            if (di_lib_debug > 2)
            {
                printf ("mnt: ignore: mntopt 'ignore': %s\n",
                        diptr->name);
            }
        }

        if ((devp = strstr (mntEntry->mnt_opts, "dev=")) != (char *) NULL)
        {
            if (devp != mntEntry->mnt_opts)
            {
                --devp;
            }
            *devp = 0;   /* point to preceeding comma and cut off */
        }
        if (chkMountOptions (mntEntry->mnt_opts, DI_MNTOPT_RO) != (char *) NULL)
        {
            diptr->isReadOnly = TRUE;
        }
        strncpy (diptr->options, mntEntry->mnt_opts, DI_OPT_LEN);

        if (di_lib_debug > 0)
        {
            printf ("mnt:%s - %s : %s\n", diptr->name,
                    diptr->special, diptr->fsType);
        }
    }

    endmntent (f);
    return 0;
}

#endif /* _lib_getmntent && _lib_setmntent && _lib_endmntent */

#if _lib_getmntinfo && \
    ! defined (_lib_getfsstat) && \
    ! defined (_lib_getvfsstat)

/*
 * di_getDiskEntries
 *
 * Old OSF/1 system call...
 * OSF/1 does this with a system call and library routine
 *
 *                  [mogul@wrl.dec.com (Jeffrey Mogul)]
 */

# if defined (INITMOUNTNAMES)
 static char *mnt_names [] = INITMOUNTNAMES;
#  define MNT_NUMTYPES (MOUNT_MAXTYPE + 1)
# endif

int
# if _proto_stdc
di_getDiskEntries (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskEntries (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo     *diptr;
    int             count;
    int             idx;
    int             len;
    short           fstype;
    struct statfs   *mntbufp;

    if (di_lib_debug > 0) { printf ("# lib:getDiskEntries: getmntinfo\n"); }
    count = getmntinfo (&mntbufp, MNT_WAIT);
    if (count < 1)
    {
        fprintf (stderr, "Unable to do getmntinfo () errno %d\n", errno);
        return -1;
    }

    *diCount = count;
    *diskInfo = (di_DiskInfo *) malloc (sizeof (di_DiskInfo) * count);
    if (*diskInfo == (di_DiskInfo *) NULL)
    {
        fprintf (stderr, "malloc failed for diskInfo. errno %d\n", errno);
        return -1;
    }
    memset ((char *) *diskInfo, '\0', sizeof (di_DiskInfo) * count);

    if (di_lib_debug > 1)
    {
        printf ("type_len %d name_len %d spec_name_len %d\n", DI_TYPE_LEN,
                DI_NAME_LEN, DI_SPEC_NAME_LEN);
    }

    for (idx = 0; idx < count; idx++)
    {
        diptr = *diskInfo + idx;
        diptr->printFlag = DI_PRNT_OK;
        diptr->isLocal = FALSE;
        diptr->isReadOnly = FALSE;
# if defined (MNT_LOCAL)
        if ((mntbufp [idx].f_flags & MNT_LOCAL) == MNT_LOCAL)
        {
            diptr->isLocal = TRUE;
        }
# endif

        strncpy (diptr->special, mntbufp [idx].f_mntfromname,
                DI_SPEC_NAME_LEN);
        strncpy (diptr->name, mntbufp [idx].f_mntonname, DI_NAME_LEN);

        diptr->blockSize = (_fs_size_t) 1024;

#  if _mem_f_fsize_statfs /* 1.x */
        diptr->blockSize = (_fs_size_t) mntbufp [idx].f_fsize;
#  endif
#  if _mem_f_bsize_statfs /* 2.x */
        diptr->blockSize = (_fs_size_t) mntbufp [idx].f_bsize;
#  endif
        diptr->totalBlocks = (_fs_size_t) mntbufp [idx].f_blocks;
        diptr->freeBlocks = (_fs_size_t) mntbufp [idx].f_bfree;
        diptr->availBlocks = (_fs_size_t) mntbufp [idx].f_bavail;

        diptr->totalInodes = mntbufp [idx].f_files;
        diptr->freeInodes = mntbufp [idx].f_ffree;
        diptr->availInodes = mntbufp [idx].f_ffree;

        fstype = mntbufp [idx].f_type;
# if ! defined (_sys_fstyp) && ! defined (INITMOUNTNAMES) && \
    ! defined (_mem_f_fstypename_statfs)
        if ((fstype >= 0) && (fstype <= MOUNT_MAXTYPE))
        {
            switch (fstype)
            {
#  if defined (MOUNT_NONE)
                case MOUNT_NONE:         /* No Filesystem */
                {
                    strncpy (diptr->fsType, "none", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_UFS)
                case MOUNT_UFS:         /* UNIX "Fast" Filesystem */
                {
                    strncpy (diptr->fsType, "ufs", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_NFS)
                case MOUNT_NFS:         /* Network Filesystem */
                {
                    strncpy (diptr->fsType, "nfs", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_MFS)
                case MOUNT_MFS:         /* Memory Filesystem */
                {
                    strncpy (diptr->fsType, "mfs", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_MSDOS)
                case MOUNT_MSDOS:       /* MSDOS Filesystem */
                {
                    strncpy (diptr->fsType, "msdos", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_LFS)
                case MOUNT_LFS:
                {
                    strncpy (diptr->fsType, "lfs", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_LOFS)
                case MOUNT_LOFS:
                {
                    strncpy (diptr->fsType, "lofs", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_FDESC)
                case MOUNT_FDESC:
                {
                    strncpy (diptr->fsType, "fdesc", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_PORTAL)
                case MOUNT_PORTAL:
                {
                    strncpy (diptr->fsType, "portal", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_NULL)
                case MOUNT_NULL:
                {
                    strncpy (diptr->fsType, "null", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_UMAP)
                case MOUNT_UMAP:
                {
                    strncpy (diptr->fsType, "umap", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_KERNFS)
                case MOUNT_KERNFS:
                {
                    strncpy (diptr->fsType, "kernfs", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_PROCFS)
                case MOUNT_PROCFS:      /* proc filesystem */
                {
                    strncpy (diptr->fsType, "pfs", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_AFS)
                case MOUNT_AFS:
                {
                    strncpy (diptr->fsType, "afs", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_ISOFS)
                case MOUNT_ISOFS:       /* iso9660 cdrom */
                {
                    strncpy (diptr->fsType, "iso9660fs", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_ISO9660) && ! defined (MOUNT_CD9660)
                case MOUNT_ISO9660:       /* iso9660 cdrom */
                {
                    strncpy (diptr->fsType, "iso9660", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_CD9660)
                case MOUNT_CD9660:       /* iso9660 cdrom */
                {
                    strncpy (diptr->fsType, "cd9660", DI_TYPE_LEN);
                    break;
                }
#  endif

#  if defined (MOUNT_UNION)
                case MOUNT_UNION:
                {
                    strncpy (diptr->fsType, "union", DI_TYPE_LEN);
                    break;
                }
#  endif
            } /* switch on mount type */
        }
# else
#  if _mem_f_fstypename_statfs
        strncpy (diptr->fsType, mntbufp [idx].f_fstypename, DI_TYPE_LEN);
#  else
            /* could use getvfsbytype here... */
        if ((fstype >= 0) && (fstype < MNT_NUMTYPES))
        {
            strncpy (diptr->fsType, mnt_names [fstype], DI_TYPE_LEN);
        }
        else
        {
            Snprintf (SPF(diptr->fsType, sizeof (diptr->fsType),
                      DI_UNKNOWN_FSTYPE), fstype);
        }
#  endif
# endif /* has fs_types.h */

        diptr->isReadOnly = FALSE;
# if defined (MNT_RDONLY)
        if ((mntbufp [idx].f_flags & MNT_RDONLY) == MNT_RDONLY)
        {
            diptr->isReadOnly = TRUE;
        }
# endif
        convertMountOptions ((long) mntbufp [idx].f_flags, diptr);
        trimChar (diptr->options, ',');

        if (di_lib_debug > 1)
        {
            printf ("%s: %s\n", diptr->name, diptr->fsType);
            printf ("\tblocks: tot:%ld free:%ld avail:%ld\n",
                    mntbufp [idx].f_blocks, mntbufp [idx].f_bfree,
                    mntbufp [idx].f_bavail);
# if _mem_f_fsize_statfs
            printf ("\tfsize:%ld \n", mntbufp [idx].f_fsize);
# endif
# if _mem_f_bsize_statfs
            printf ("\tbsize:%ld \n", mntbufp [idx].f_bsize);
# endif
# if _mem_f_iosize_statfs
            printf ("\tiosize:%ld \n", mntbufp [idx].f_iosize);
# endif
            printf ("\tinodes: tot:%ld free:%ld\n",
                    mntbufp [idx].f_files, mntbufp [idx].f_ffree);
        }
    }

    free ((char *) mntbufp);  /* man page says this can't be freed. */
                              /* is it ok to try?                   */
    return 0;
}

#endif /* _lib_getmntinfo */

#if _lib_getfsstat && \
    ! defined (_lib_getvfsstat)

/*
 * di_getDiskEntries
 *
 * OSF/1 / Digital Unix / Compaq Tru64 / FreeBSD
 *
 */

int
# if _proto_stdc
di_getDiskEntries (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskEntries (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo     *diptr;
    int             count;
    int             idx;
    long            bufsize;
    struct statfs   *mntbufp;
    struct statfs   *sp;

    if (di_lib_debug > 0) { printf ("# lib:getDiskEntries: getfsstat\n"); }
    count = getfsstat ((struct statfs *) NULL, 0, MNT_NOWAIT);
    if (count < 1)
    {
        fprintf (stderr, "Unable to do getfsstat () errno %d\n", errno);
        return -1;
    }
    bufsize = sizeof (struct statfs) * count;
    mntbufp = malloc (bufsize);
    memset ((char *) mntbufp, '\0', sizeof (struct statfs) * count);
    count = getfsstat (mntbufp, bufsize, MNT_NOWAIT);

    *diCount = count;
    *diskInfo = (di_DiskInfo *) malloc (sizeof (di_DiskInfo) * count);
    if (*diskInfo == (di_DiskInfo *) NULL)
    {
        fprintf (stderr, "malloc failed for diskInfo. errno %d\n", errno);
        return -1;
    }
    memset ((char *) *diskInfo, '\0', sizeof (di_DiskInfo) * count);

    for (idx = 0; idx < count; idx++)
    {
        diptr = *diskInfo + idx;
        diptr->printFlag = DI_PRNT_OK;
        diptr->isLocal = FALSE;
        diptr->isReadOnly = FALSE;
# if defined (MNT_RDONLY)
        if ((mntbufp [idx].f_flags & MNT_RDONLY) == MNT_RDONLY)
        {
            diptr->isReadOnly = TRUE;
        }
# endif
# if defined (MNT_LOCAL)
        if ((mntbufp [idx].f_flags & MNT_LOCAL) == MNT_LOCAL)
        {
            diptr->isLocal = TRUE;
        }
# endif
        sp = mntbufp + idx;
        convertMountOptions ((long) sp->f_flags, diptr);
# if _mem_f_type_statfs
#  if defined (MOUNT_NFS3)
        if (sp->f_type == MOUNT_NFS3)
        {
            strncat (diptr->options, "v3,",
                    DI_OPT_LEN - strlen (diptr->options) - 1);
        }
#  endif
# endif
# if _mem_mount_info_statfs && \
        defined (MOUNT_NFS) && \
        (_mem_f_type_statfs || _mem_f_fstypename_statfs)
#  if _mem_f_type_statfs
        if (sp->f_type == MOUNT_NFS
#  endif
#  if _mem_f_fstypename_statfs
        if (strcmp (sp->f_fstypename, MOUNT_NFS) == 0
#  endif
#  if _mem_f_fstypename_statfs && defined (MOUNT_NFS3)
                || strcmp (sp->f_fstypename, MOUNT_NFS3) == 0
#  endif
#  if _mem_f_type_statfs && defined (MOUNT_NFS3)
                || sp->f_type == MOUNT_NFS3
#  endif
           )
        {
            struct nfs_args *na;
            na = &sp->mount_info.nfs_args;
            convertNFSMountOptions (na->flags, na->wsize, na->rsize, diptr);
        }
# endif
        trimChar (diptr->options, ',');

        strncpy (diptr->special, sp->f_mntfromname, DI_SPEC_NAME_LEN);
        strncpy (diptr->name, sp->f_mntonname, DI_NAME_LEN);
# if _mem_f_fsize_statfs
        diptr->blockSize = (_fs_size_t) mntbufp [idx].f_fsize;
# endif
# if _mem_f_bsize_statfs && ! defined (_mem_f_fsize_statfs)
        diptr->blockSize = (_fs_size_t) mntbufp [idx].f_bsize;
# endif
        diptr->totalBlocks = (_fs_size_t) sp->f_blocks;
        diptr->freeBlocks = (_fs_size_t) sp->f_bfree;
        diptr->availBlocks = (_fs_size_t) sp->f_bavail;

        diptr->totalInodes = sp->f_files;
        diptr->freeInodes = sp->f_ffree;
        diptr->availInodes = sp->f_ffree;
# if _mem_f_fstypename_statfs
        strncpy (diptr->fsType, sp->f_fstypename, DI_TYPE_LEN);
# else
#  if _lib_sysfs && _mem_f_type_statfs
        sysfs (GETFSTYP, sp->f_type, diptr->fsType);
#  endif
# endif
    }

    free ((char *) mntbufp);
    return 0;
}

#endif /* _lib_getfsstat */

#if _lib_getvfsstat

/*
 * di_getDiskEntries
 *
 * NetBSD
 *
 */

int
# if _proto_stdc
di_getDiskEntries (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskEntries (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo     *diptr;
    int             count;
    int             idx;
    long            bufsize;
    struct statvfs  *mntbufp;
    struct statvfs  *sp;

    if (di_lib_debug > 0) { printf ("# lib:getDiskEntries: getvfsstat\n"); }
    count = getvfsstat ((struct statvfs *) NULL, 0, ST_NOWAIT);
    if (count < 1)
    {
        fprintf (stderr, "Unable to do getvfsstat () errno %d\n", errno);
        return -1;
    }
    bufsize = sizeof (struct statvfs) * count;
    mntbufp = malloc (bufsize);
    memset ((char *) mntbufp, '\0', sizeof (struct statvfs) * count);
    count = getvfsstat (mntbufp, bufsize, ST_NOWAIT);

    *diCount = count;
    *diskInfo = (di_DiskInfo *) malloc (sizeof (di_DiskInfo) * count);
    if (*diskInfo == (di_DiskInfo *) NULL)
    {
        fprintf (stderr, "malloc failed for diskInfo. errno %d\n", errno);
        return -1;
    }
    memset ((char *) *diskInfo, '\0', sizeof (di_DiskInfo) * count);

    for (idx = 0; idx < count; idx++)
    {
        diptr = *diskInfo + idx;
        diptr->printFlag = DI_PRNT_OK;
        diptr->isLocal = FALSE;
        diptr->isReadOnly = FALSE;

        sp = mntbufp + idx;

# if defined (MNT_RDONLY)
        if ((sp->f_flag & MNT_RDONLY) == MNT_RDONLY)
        {
            diptr->isReadOnly = TRUE;
        }
# endif
# if defined (MNT_LOCAL)
        if ((sp->f_flag & MNT_LOCAL) == MNT_LOCAL)
        {
            diptr->isLocal = TRUE;
        }
# endif
        convertMountOptions ((long) sp->f_flag, diptr);
        trimChar (diptr->options, ',');

        if (sp->f_frsize == 0 && sp->f_bsize != 0)
        {
            diptr->blockSize = (_fs_size_t) sp->f_bsize;
        }
        else
        {
            diptr->blockSize = (_fs_size_t) sp->f_frsize;
        }
        diptr->totalBlocks = (_fs_size_t) sp->f_blocks;
        diptr->freeBlocks = (_fs_size_t) sp->f_bfree;
        diptr->availBlocks = (_fs_size_t) sp->f_bavail;

        diptr->totalInodes = sp->f_files;
        diptr->freeInodes = sp->f_ffree;
        diptr->availInodes = sp->f_ffree;

        strncpy (diptr->special, sp->f_mntfromname, DI_SPEC_NAME_LEN);
        strncpy (diptr->name, sp->f_mntonname, DI_NAME_LEN);
        strncpy (diptr->fsType, sp->f_fstypename, DI_TYPE_LEN);

        if (di_lib_debug > 1)
        {
            printf ("%s: %s\n", diptr->name, diptr->fsType);
            printf ("\tbsize:%ld  frsize:%ld\n", (long) sp->f_bsize,
                    (long) sp->f_frsize);
#if _siz_long_long >= 8
            printf ("\tblocks: tot:%llu free:%lld avail:%llu\n",
                   sp->f_blocks, sp->f_bfree, sp->f_bavail);
            printf ("\tinodes: tot:%llu free:%llu avail:%llu\n",
                    sp->f_files, sp->f_ffree, sp->f_favail);
#else
            printf ("\tblocks: tot:%lu free:%lu avail:%lu\n",
                   sp->f_blocks, sp->f_bfree, sp->f_bavail);
            printf ("\tinodes: tot:%lu free:%lu avail:%lu\n",
                    sp->f_files, sp->f_ffree, sp->f_favail);
#endif
        }
    }

    free ((char *) mntbufp);
    return 0;
}

#endif /* _lib_getvfsstat */

#if _lib_getmnt

/*
 * di_getDiskEntries
 *
 * ULTRIX does this with a system call.  The system call allows one
 * to retrieve the information in a series of calls, but coding that
 * looks a little tricky; I just allocate a huge buffer and do it in
 * one shot.
 *
 *                  [mogul@wrl.dec.com (Jeffrey Mogul)]
 */

int
# if _proto_stdc
di_getDiskEntries (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskEntries (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo     *diptr;
    int             count;
    int             bufsize;
    int             idx;
    short           fstype;
    struct fs_data  *fsdbuf;
    int             start;
    int             len;


    if (di_lib_debug > 0) { printf ("# lib:getDiskEntries: getmnt\n"); }
    bufsize = NMOUNT * sizeof (struct fs_data);  /* enough for max # mounts */
    fsdbuf = (struct fs_data *) malloc (bufsize);
    if (fsdbuf == (struct fs_data *) NULL)
    {
        fprintf (stderr, "malloc (%d) for getmnt () failed errno %d\n",
                 bufsize, errno);
        return -1;
    }

    start = 0;
    count = getmnt (&start, fsdbuf, bufsize, STAT_MANY, 0);
    if (count < 1)
    {
        fprintf (stderr, "Unable to do getmnt () [= %d] errno %d\n",
                 count, errno);
        free ((char *) fsdbuf);
        return -1;
    }

    *diCount = count;
    *diskInfo = (di_DiskInfo *) malloc (sizeof (di_DiskInfo) * count);
    if (*diskInfo == (di_DiskInfo *) NULL)
    {
        fprintf (stderr, "malloc failed for diskInfo. errno %d\n", errno);
        free ((char *) fsdbuf);
        return -1;
    }
    memset ((char *) *diskInfo, '\0', sizeof (di_DiskInfo) * count);

    for (idx = 0; idx < count; idx++)
    {
        diptr = *diskInfo + idx;
        diptr->printFlag = DI_PRNT_OK;
        diptr->isLocal = TRUE;
        diptr->isReadOnly = FALSE;

        if ((fsdbuf [idx].fd_req.flags & MNT_LOCAL) != MNT_LOCAL)
        {
            diptr->isLocal = FALSE;
        }

        strncpy (diptr->special, fsdbuf [idx].fd_devname, DI_SPEC_NAME_LEN);
        strncpy (diptr->name, fsdbuf [idx].fd_path, DI_NAME_LEN);

            /* ULTRIX keeps these fields in units of 1K byte */
        diptr->totalBlocks = fsdbuf [idx].fd_btot;
        diptr->freeBlocks = fsdbuf [idx].fd_bfree;
        diptr->availBlocks = (int) fsdbuf [idx].fd_bfreen;

        diptr->totalInodes = fsdbuf [idx].fd_gtot;
        diptr->freeInodes = fsdbuf [idx].fd_gfree;
        diptr->availInodes = fsdbuf [idx].fd_gfree;

        fstype = fsdbuf [idx].fd_fstype;
        if (fstype == GT_UNKWN)
        {
            diptr->printFlag = DI_PRNT_IGNORE;
            if (di_lib_debug > 2)
            {
                printf ("mnt: ignore: disk type unknown: %s\n",
                        diptr->name);
            }
        }
        else if ((fstype > 0) && (fstype < GT_NUMTYPES))
        {
            strncpy (diptr->fsType, gt_names [fstype], DI_TYPE_LEN);
        }
        else
        {
            Snprintf (SPF(diptr->fsType, sizeof (diptr->fsType),
                          "Unknown fstyp %.2d"), fstype);
        }

        if ((fsdbuf [idx].fd_req.flags & MNT_RDONLY) == MNT_RDONLY)
        {
            diptr->isReadOnly = TRUE;
        }
        else
        {
            diptr->isReadOnly = FALSE;
        }
        convertMountOptions ((long) fsdbuf [idx].fd_req.flags, diptr);
        trimChar (diptr->options, ',');

        if (di_lib_debug > 1)
        {
            printf ("%s: %s\n", diptr->name, diptr->fsType);
            printf ("\tblocks: tot:%ld free:%ld avail:%ld\n",
                    fsdbuf [idx].fd_btot, fsdbuf [idx].fd_bfree,
                    (int) fsdbuf [idx].fd_bfreen);
            printf ("\tinodes: tot:%ld free:%ld\n",
                    fsdbuf [idx].fd_gtot, fsdbuf [idx].fd_gfree);
        }
    }

    free ((char *) fsdbuf);
    return 0;
}

#endif /* _lib_getmnt */


#if _lib_mntctl

/*
 * di_getDiskEntries
 *
 * AIX uses mntctl to find out about mounted file systems
 * This seems to be better than set/get/end, as we get the
 * remote filesystem flag.
 *
 */

# define DI_FSMAGIC 10    /* base AIX configuration has 5 file systems */
# define NUM_AIX_FSTYPES         6
static char *AIX_fsType [NUM_AIX_FSTYPES] =
    { "oaix", "", "nfs", "jfs", "", "cdrom" };

/*
 * from xfsm-1.80:
 *
 * MNT_AIX - "aix"
 * MNT_NFS - "nfs"
 * MNT_JFS - "jfs"
 * MNT_CDROM - "cdrom"
 * other - "user defined"
 *
 */

#define DI_RETRY_COUNT         5

int
# if _proto_stdc
di_getDiskEntries (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskEntries (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo     *diptr;
    int             num;        /* number of vmount structs returned    */
    char            *vmbuf;     /* buffer for vmount structs returned   */
    int             vmbufsz;    /* size in bytes of vmbuf               */
    int             i;          /* index for looping and stuff          */
    char            *bufp;      /* pointer into vmbuf                   */
    struct vmount   *vmtp;      /* pointer into vmbuf                   */
    struct vfs_ent  *ve;        /* pointer for file system type entry   */
    int             len;


    if (di_lib_debug > 0) { printf ("# lib:getDiskEntries: mntctl\n"); }
    i = 0;
    vmbufsz = sizeof (struct vmount) * DI_FSMAGIC; /* initial vmount buffer */

    do
    {
        if ((vmbuf = (char *) malloc (vmbufsz)) == (char *) NULL)
        {
            fprintf (stderr, "malloc (%d) for mntctl() failed errno %d\n",
                    vmbufsz, errno);
            return -1;
        }

        num = mntctl (MCTL_QUERY, vmbufsz, vmbuf);
            /*
             * vmbuf is too small, could happen for
             * following reasons:
             * - inital buffer is too small
             * - newly mounted file system
             */
        if (num == 0)
        {
            memcpy (&vmbufsz, vmbuf, sizeof (vmbufsz)); /* see mntctl(2) */
            if (di_lib_debug > 0)
            {
                printf ("vmbufsz too small, new size: %d\n", vmbufsz);
            }
            free ((char *) vmbuf); /* free this last, it's still being used! */
            ++i;
        }
    } while (num == 0 && i < DI_RETRY_COUNT);

    if (i >= DI_RETRY_COUNT)
    {
        free ((char *) vmbuf);
        fprintf (stderr, "unable to allocate adequate buffer for mntctl\n");
        return -1;
    }

    if (num == -1)
    {
        free ((char *) vmbuf);
        fprintf (stderr,"%s errno %d\n", strerror (errno), errno);
        return -1;
    }

        /* <num> vmount structs returned in vmbuf */
    *diCount = num;
    *diskInfo = (di_DiskInfo *) calloc (sizeof (di_DiskInfo), *diCount);
    if (*diskInfo == (di_DiskInfo *) NULL)
    {
        fprintf (stderr, "malloc failed for diskInfo. %s errno %d\n",
                 strerror (errno), errno);
        return -1;
    }

    bufp = vmbuf;
    for (i = 0; i < num; i++)
    {
        diptr = *diskInfo + i;
        vmtp = (struct vmount *) bufp;
        diptr->printFlag = DI_PRNT_OK;
        diptr->isLocal = TRUE;
        diptr->isReadOnly = FALSE;
        if ((vmtp->vmt_flags & MNT_REMOTE) == MNT_REMOTE)
        {
            diptr->isLocal = FALSE;
        }
        if ((vmtp->vmt_flags & MNT_RDONLY) == MNT_RDONLY)
        {
            diptr->isReadOnly = TRUE;
        }

        *diptr->special = '\0';
        if (diptr->isLocal == FALSE)
        {
            strncpy (diptr->special,
                    (char *) vmt2dataptr (vmtp, VMT_HOSTNAME),
                    DI_SPEC_NAME_LEN);
            strncat (diptr->special, ":",
                    DI_SPEC_NAME_LEN - strlen (diptr->special) - 1);
        }
        strncat (diptr->special,
                (char *) vmt2dataptr (vmtp, VMT_OBJECT),
                DI_SPEC_NAME_LEN - strlen (diptr->special) - 1);
        strncpy (diptr->name,
                (char *) vmt2dataptr (vmtp, VMT_STUB), DI_NAME_LEN);

        ve = getvfsbytype (vmtp->vmt_gfstype);
        if (ve == (struct vfs_ent *) NULL || *ve->vfsent_name == '\0')
        {
            if (vmtp->vmt_gfstype >= 0 &&
                    (vmtp->vmt_gfstype < NUM_AIX_FSTYPES))
            {
                strncpy (diptr->fsType,
                        AIX_fsType [vmtp->vmt_gfstype], DI_TYPE_LEN);
            }
        }
        else
        {
            strncpy (diptr->fsType, ve->vfsent_name, DI_TYPE_LEN);
        }

        strncpy (diptr->options, (char *) vmt2dataptr (vmtp, VMT_ARGS),
                 DI_OPT_LEN);
        trimChar (diptr->options, ',');

        strncpy (diptr->mountTime, ctime ((time_t *) &vmtp->vmt_time),
                DI_MNT_TIME_LEN);
        bufp += vmtp->vmt_length;

        if (di_lib_debug > 0)
        {
            printf ("mnt:%s - %s : %s\n", diptr->name,
                    diptr->special, diptr->fsType);
            printf ("\t%s\n", (char *) vmt2dataptr (vmtp, VMT_ARGS));
        }
    }
}

#endif  /* _lib_mntctl */

#if (_statfs_2arg || \
        _statfs_3arg) && \
        ! defined (_lib_statvfs) && \
        ! defined (_lib_getmntinfo) && \
        ! defined (_lib_getmnt) && \
        ! defined (_lib_GetDiskFreeSpace) && \
        ! defined (_lib_GetDiskFreeSpaceEx)

/*
 * di_getDiskInfo
 *
 * SunOS/BSD/Pyramid/Some Linux
 *
 */

# define DI_GETDISKINFO_DEF 1

void
# if _proto_stdc
di_getDiskInfo (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskInfo (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo     *diptr;
    int             i;
    struct statfs   statBuf;

    if (di_lib_debug > 0) { printf ("# lib:getDiskEntries: bsd-statfs 2/3arg\n"); }
    for (i = 0; i < *diCount; ++i)
    {
        diptr = *diskInfo + i;
        if (diptr->printFlag == DI_PRNT_OK)
        {
            if (statfs (diptr->name, &statBuf) == 0)
            {
                diptr->blockSize = (_fs_size_t) statBuf.f_bsize;
                diptr->totalBlocks = (_fs_size_t) statBuf.f_blocks;
                diptr->freeBlocks = (_fs_size_t) statBuf.f_bfree;
                diptr->availBlocks = (_fs_size_t) statBuf.f_bavail;

                diptr->totalInodes = statBuf.f_files;
                diptr->freeInodes = statBuf.f_ffree;
                diptr->availInodes = statBuf.f_ffree;
# if _lib_sysfs
                sysfs (GETFSTYP, statBuf.f_fstyp, diptr->fsType);
# endif

                if (di_lib_debug > 1)
                {
                    printf ("%s: %s\n", diptr->name, diptr->fsType);
                    printf ("\tbsize:%ld\n", statBuf.f_bsize);
                    printf ("\tblocks: tot:%ld free:%ld avail:%ld\n",
                            statBuf.f_blocks, statBuf.f_bfree, statBuf.f_bavail);
                    printf ("\tinodes: tot:%ld free:%ld\n",
                            statBuf.f_files, statBuf.f_ffree);
                }
            } /* if we got the info */
            else
            {
                fprintf (stderr, "statfs: %s ", diptr->name);
                perror ("");
            }
        }
    } /* for each entry */
}

#endif /* _statfs_2arg */

#if _lib_GetDiskFreeSpace && \
    _lib_GetDriveType && \
    _lib_GetLogicalDriveStrings

/*
 * di_getDiskInfo
 *
 * Windows
 *
 */

# define MSDOS_BUFFER_SIZE          256
# define BYTES_PER_LOGICAL_DRIVE    4

int
# if _proto_stdc
di_getDiskEntries (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskEntries (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo     *diptr;
    int             i;
    int             diskflag;
    int             rc;
    char            *p;
    char            buff [MSDOS_BUFFER_SIZE];


# if _lib_GetDiskFreeSpaceEx
    if (di_lib_debug > 0) { printf ("# lib:getDiskEntries: GetDiskFreeSpaceEx\n"); }
# else
#  if _lib_GetDiskFreeSpace
    if (di_lib_debug > 0) { printf ("# lib:getDiskEntries: GetDiskFreeSpace\n"); }
#  endif
# endif
    diskflag = DI_PRNT_IGNORE;
    rc = GetLogicalDriveStrings (MSDOS_BUFFER_SIZE, buff);
    *diCount = rc / BYTES_PER_LOGICAL_DRIVE;

    *diskInfo = (di_DiskInfo *) calloc (sizeof (di_DiskInfo), *diCount);
    if (*diskInfo == (di_DiskInfo *) NULL)
    {
        fprintf (stderr, "malloc failed for diskInfo. errno %d\n", errno);
        return -1;
    }

    for (i = 0; i < *diCount; ++i)
    {
        diptr = *diskInfo + i;
        p = buff + (BYTES_PER_LOGICAL_DRIVE * i);
        strncpy (diptr->name, p, DI_NAME_LEN);
        rc = GetDriveType (p);
        diptr->printFlag = DI_PRNT_OK;

        if (rc == DRIVE_NO_ROOT_DIR)
        {
            diptr->printFlag = DI_PRNT_BAD;
        }

            /* assume that any removable drives before the  */
            /* first non-removable disk are floppies...     */
        else if (rc == DRIVE_REMOVABLE)
        {
            diptr->printFlag = diskflag;
        }
        else
        {
            diskflag = DI_PRNT_OK;
        }

        if (rc != DRIVE_REMOTE)
        {
            diptr->isLocal = TRUE;
        }
    } /* for each mounted drive */

    return *diCount;
}

#endif  /* _lib_GetDiskFreeSpace || _lib_GetDiskFreeSpaceEx */

#if _lib_GetVolumeInformation

/*
 * di_getDiskInfo
 *
 * Windows
 *
 */

# define DI_GETDISKINFO_DEF 1

void
# if _proto_stdc
di_getDiskInfo (di_DiskInfo **diskInfo, int *diCount)
# else
di_getDiskInfo (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
# endif
{
    di_DiskInfo         *diptr;
    int                 i;
    int                 rc;
    char                volName [MSDOS_BUFFER_SIZE];
    char                fsName [MSDOS_BUFFER_SIZE];
    DWORD               serialNo;
    DWORD               maxCompLen;
    DWORD               fsFlags;


    if (di_lib_debug > 0) { printf ("# lib:getDiskInfo: GetVolumeInformation\n"); }
    for (i = 0; i < *diCount; ++i)
    {
        diptr = *diskInfo + i;
        if (diptr->printFlag == DI_PRNT_OK)
        {
            rc = GetVolumeInformation (diptr->name,
                    volName, MSDOS_BUFFER_SIZE, &serialNo, &maxCompLen,
                    &fsFlags, fsName, MSDOS_BUFFER_SIZE);
            strncpy (diptr->fsType, fsName, DI_TYPE_LEN);
            strncpy (diptr->special, volName, DI_SPEC_NAME_LEN);

# if _lib_GetDiskFreeSpaceEx
            {
                ULONGLONG bytesAvail;
                ULONGLONG bytesTotal;
                ULONGLONG bytesFree;

                rc = GetDiskFreeSpaceEx (diptr->name,
                        (PULARGE_INTEGER) &bytesAvail,
                        (PULARGE_INTEGER) &bytesTotal,
                        (PULARGE_INTEGER) &bytesFree);
                if (rc > 0)
                {
                    diptr->blockSize = (_fs_size_t) 1;
                    diptr->totalBlocks = (_fs_size_t) bytesTotal;
                    diptr->freeBlocks = (_fs_size_t) bytesFree;
                    diptr->availBlocks = (_fs_size_t) bytesAvail;

                    diptr->totalInodes = 0;
                    diptr->freeInodes = 0;
                    diptr->availInodes = 0;
                }
                else
                {
                    diptr->printFlag = DI_PRNT_BAD;
                    if (di_lib_debug)
                    {
                        printf ("disk %s; could not get disk space\n",
                                diptr->name);
                    }
                }

                if (di_lib_debug > 1)
                {
                    printf ("%s: %s\n", diptr->name, diptr->fsType);
                    printf ("\ttot:%llu  free:%llu\n",
                            bytesTotal, bytesFree);
                    printf ("\tavail:%llu\n", bytesAvail);
                }
            }
# else
#  if _lib_GetDiskFreeSpace
            {
                unsigned long           sectorspercluster;
                unsigned long           bytespersector;
                unsigned long           totalclusters;
                unsigned long           freeclusters;

                rc = GetDiskFreeSpace (diptr->name,
                        (LPDWORD) &sectorspercluster,
                        (LPDWORD) &bytespersector,
                        (LPDWORD) &freeclusters,
                        (LPDWORD) &totalclusters);
                if (rc > 0)
                {
                    diptr->blockSize = (_fs_size_t) (sectorspercluster *
                            bytespersector);
                    diptr->totalBlocks = (_fs_size_t) totalclusters;
                    diptr->freeBlocks = (_fs_size_t) freeclusters;
                    diptr->availBlocks = (_fs_size_t) freeclusters;

                    diptr->totalInodes = 0;
                    diptr->freeInodes = 0;
                    diptr->availInodes = 0;
                }
                else
                {
                    diptr->printFlag = DI_PRNT_BAD;
                    if (di_lib_debug)
                    {
                        printf ("disk %s; could not get disk space\n",
                                diptr->name);
                    }
                }

                if (di_lib_debug > 1)
                {
                    printf ("%s: %s\n", diptr->name, diptr->fsType);
                    printf ("\ts/c:%ld  b/s:%ld\n", sectorspercluster,
                        bytespersector);
                    printf ("\tclusters: tot:%ld free:%ld\n",
                        totalclusters, freeclusters);
                }
            }
#  endif
# endif
        } /* if printable drive */
    } /* for each mounted drive */
}

#endif  /* _lib_GetVolumeInformation */


/*
 * Realloc
 *
 * portable realloc
 *
 */

void *
#if _proto_stdc
Realloc (void *ptr, Size_t size)
#else
Realloc (ptr, size)
    void        *ptr;
    Size_t      size;
#endif
{
    if (ptr == (void *) NULL)
    {
        ptr = (void *) malloc (size);
    }
    else
    {
        ptr = (void *) realloc (ptr, size);
    }

    return ptr;
}

static void
#if _proto_stdc
convertMountOptions (long flags, di_DiskInfo *diptr)
#else
convertMountOptions (flags, diptr)
    long          flags;
    di_DiskInfo   *diptr;
#endif
{
#if defined (MNT_RDONLY)
    if ((flags & MNT_RDONLY) == MNT_RDONLY)
    {
        strncat (diptr->options, "ro,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
    else
    {
        strncat (diptr->options, "rw,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_FORCE)
    if ((flags & MNT_FORCE) == MNT_FORCE)
    {
        strncat (diptr->options, "force,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_GRPID)
    if ((flags & MNT_GRPID) == MNT_GRPID)
    {
        strncat (diptr->options, "grpid,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_MAGICLINKS)
    if ((flags & MNT_MAGICLINKS) == MNT_MAGICLINKS)
    {
        strncat (diptr->options, "magiclinks,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_MLSD)
    if ((flags & MNT_MLSD) == MNT_MLSD)
    {
        strncat (diptr->options, "mlsd,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_NOATIMES)
    if ((flags & MNT_NOATIMES) == MNT_NOATIMES)
    {
        strncat (diptr->options, "noatime,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_NOCACHE)
    if ((flags & MNT_NOCACHE) == MNT_NOCACHE)
    {
        strncat (diptr->options, "nocache,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_NOCOREDUMP)
    if ((flags & MNT_NOCOREDUMP) == MNT_NOCOREDUMP)
    {
        strncat (diptr->options, "nocoredump,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_NODEV)
    if ((flags & MNT_NODEV) == MNT_NODEV)
    {
        strncat (diptr->options, "nodev,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_NODEVMTIME)
    if ((flags & MNT_NODEVMTIME) == MNT_NODEVMTIME)
    {
        strncat (diptr->options, "nodevmtime,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_NOEXEC)
    if ((flags & MNT_NOEXEC) == MNT_NOEXEC)
    {
        strncat (diptr->options, "noexec,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_NOSUID)
    if ((flags & MNT_NOSUID) == MNT_NOSUID)
    {
        strncat (diptr->options, "nosuid,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_QUOTA)
    if ((flags & MNT_QUOTA) == MNT_QUOTA)
    {
        strncat (diptr->options, "quota,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_SECURE)
    if ((flags & MNT_SECURE) == MNT_SECURE)
    {
        strncat (diptr->options, "secure,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_SMSYNC2)
    if ((flags & MNT_SMSYNC2) == MNT_SMSYNC2)
    {
        strncat (diptr->options, "smsync2,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_SOFTDEP)
    if ((flags & MNT_SOFTDEP) == MNT_SOFTDEP)
    {
        strncat (diptr->options, "softdep,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_SYMPERM)
    if ((flags & MNT_SYMPERM) == MNT_SYMPERM)
    {
        strncat (diptr->options, "symperm,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_SYNC)
    if ((flags & MNT_SYNC) == MNT_SYNC)
    {
        strncat (diptr->options, "sync,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_SYNCHRONOUS)
    if ((flags & MNT_SYNCHRONOUS) == MNT_SYNCHRONOUS)
    {
        strncat (diptr->options, "sync,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_THROTTLE)
    if ((flags & MNT_THROTTLE) == MNT_THROTTLE)
    {
        strncat (diptr->options, "throttle,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_UNION)
    if ((flags & MNT_UNION) == MNT_UNION)
    {
        strncat (diptr->options, "union,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (MNT_UNION)
    if ((flags & MNT_UNION) == MNT_UNION)
    {
        strncat (diptr->options, "union,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
}

static void
#if _proto_stdc
convertNFSMountOptions (long flags, long wsize, long rsize, di_DiskInfo *diptr)
#else
convertNFSMountOptions (flags, wsize, rsize, diptr)
    long          flags;
    long          wsize;
    long          rsize;
    di_DiskInfo   *diptr;
#endif
{
#if defined (NFSMNT_SOFT)
    if ((flags & NFSMNT_SOFT) != NFSMNT_SOFT)
    {
        strncat (diptr->options, "hard,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (NFSMNT_WSIZE)
    if ((flags & NFSMNT_WSIZE) == NFSMNT_WSIZE)
    {
        char          tmp [64];

        Snprintf (SPF(tmp, sizeof (tmp), "wsize=%ld,"), wsize);
        strncat (diptr->options, tmp,
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (NFSMNT_RSIZE)
    if ((flags & NFSMNT_RSIZE) == NFSMNT_RSIZE)
    {
        char          tmp [64];

        Snprintf (SPF(tmp, sizeof (tmp), "rsize=%ld,"), rsize);
        strncat (diptr->options, tmp,
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (NFSMNT_INT) && defined (NFSMNT_SOFT)
    if ((flags & NFSMNT_SOFT) != NFSMNT_SOFT &&
        (flags & NFSMNT_INT) == NFSMNT_INT)
    {
        strncat (diptr->options, "intr,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
#if defined (NFSMNT_TCP)
    if ((flags & NFSMNT_TCP) != NFSMNT_TCP)
    {
        strncat (diptr->options, "udp,",
                DI_OPT_LEN - strlen (diptr->options) - 1);
    }
#endif
}


static void
#if _proto_stdc
trimChar (char *str, int ch)
#else
trimChar (str, ch)
    char         *str;
    int          ch;
#endif
{
    int               len;

    len = strlen (str);
    if (len > 0)
    {
        --len;
    }
    if (len >= 0)
    {
        if (str [len] == ch)
        {
            str [len] = '\0';
        }
    }
}

#if ! defined (DI_GETDISKINFO_DEF)
void
#  if _proto_stdc
di_getDiskInfo (di_DiskInfo **diskInfo, int *diCount)
#  else
di_getDiskInfo (diskInfo, diCount)
    di_DiskInfo **diskInfo;
    int *diCount;
#  endif
{
    if (di_lib_debug > 0) { printf ("# lib:getDiskInfo: empty\n"); }
    return;
}
#endif

void
# if _proto_stdc
di_testRemoteDisk (di_DiskInfo *diskInfo)
# else
di_testRemoteDisk (diskInfo)
    di_DiskInfo *diskInfo;
# endif
{
    if (strcmp (diskInfo->fsType, "nfs") == 0 ||
            strcmp (diskInfo->fsType, "nfs3") == 0)
    {
        diskInfo->isLocal = FALSE;
    }
}
