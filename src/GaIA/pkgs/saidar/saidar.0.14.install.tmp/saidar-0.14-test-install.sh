#! /bin/sh
#
# Test script for saidar
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/saidar/saidar.0.14.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/bin/saidar
/bin/rm -f /var/opt/UNItools/bin/statgrab
/bin/rm -f /var/opt/UNItools/bin/statgrab-make-mrtg-index
/bin/rm -f /var/opt/UNItools/bin/statgrab-make-mrtg-config
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_user_stats.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats_diff.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_fs_stats.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/saidar.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/statgrab.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_process_stats.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/README
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/statgrab.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_percents.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_process_count.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/COPYING.LGPL
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_load_stats.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats_diff.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats_diff.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats_diff.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/saidar.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_user_stats.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_host_info.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_mem_stats.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_process_stats.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/COPYING
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_iface_stats.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats_diff.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats_diff.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/NEWS
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-config.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-index.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_iface_stats.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/AUTHORS
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-config.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_swap_stats.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats_diff.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_fs_stats.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_user_stats.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_fs_stats.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_host_info.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_process_count.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/statgrab.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_percents.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_load_stats.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats_diff.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_load_stats.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats_diff.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_host_info.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_mem_stats.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/saidar.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats_diff.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_percents.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_process_stats.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats_diff.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-index.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats_diff.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-index.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_iface_stats.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_mem_stats.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-config.pdf
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_process_count.html
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_swap_stats.txt
/bin/rm -f /var/opt/UNItools/docs/saidar.0.14/sg_get_swap_stats.html
/bin/rm -f /var/opt/UNItools/lib/libstatgrab.a
/bin/rm -f /var/opt/UNItools/lib/libstatgrab.la
/bin/rm -f /var/opt/UNItools/lib/pkgconfig/libstatgrab.pc
/bin/rm -f /var/opt/UNItools/include/statgrab_deprecated.h
/bin/rm -f /var/opt/UNItools/include/statgrab.h
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/bin/saidar ]; then
	echo "ERROR: file /var/opt/UNItools/bin/saidar exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/statgrab ]; then
	echo "ERROR: file /var/opt/UNItools/bin/statgrab exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/statgrab-make-mrtg-index ]; then
	echo "ERROR: file /var/opt/UNItools/bin/statgrab-make-mrtg-index exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/statgrab-make-mrtg-config ]; then
	echo "ERROR: file /var/opt/UNItools/bin/statgrab-make-mrtg-config exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_user_stats.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_user_stats.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats_diff.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats_diff.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_fs_stats.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_fs_stats.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/saidar.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/saidar.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/statgrab.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/statgrab.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_process_stats.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_process_stats.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/statgrab.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/statgrab.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_percents.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_percents.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_process_count.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_process_count.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/COPYING.LGPL ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/COPYING.LGPL exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_load_stats.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_load_stats.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats_diff.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats_diff.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats_diff.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats_diff.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats_diff.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats_diff.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/saidar.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/saidar.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_user_stats.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_user_stats.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_host_info.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_host_info.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_mem_stats.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_mem_stats.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_process_stats.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_process_stats.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_iface_stats.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_network_iface_stats.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats_diff.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats_diff.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats_diff.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats_diff.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/NEWS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/NEWS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-config.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-config.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-index.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-index.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_iface_stats.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_network_iface_stats.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-config.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-config.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_swap_stats.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_swap_stats.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats_diff.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats_diff.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_fs_stats.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_fs_stats.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_user_stats.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_user_stats.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_fs_stats.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_fs_stats.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_host_info.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_host_info.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_process_count.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_process_count.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_page_stats.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/statgrab.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/statgrab.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_percents.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_percents.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_load_stats.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_load_stats.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats_diff.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats_diff.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_load_stats.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_load_stats.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats_diff.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats_diff.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_host_info.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_host_info.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_mem_stats.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_mem_stats.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/saidar.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/saidar.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats_diff.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats_diff.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_percents.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_percents.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_process_stats.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_process_stats.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_cpu_stats.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats_diff.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats_diff.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-index.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-index.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats_diff.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_disk_io_stats_diff.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_network_io_stats.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-index.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-index.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_network_iface_stats.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_network_iface_stats.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_mem_stats.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_mem_stats.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-config.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/statgrab-make-mrtg-config.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_process_count.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_process_count.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_swap_stats.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_swap_stats.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/saidar.0.14/sg_get_swap_stats.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/saidar.0.14/sg_get_swap_stats.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/lib/libstatgrab.a ]; then
	echo "ERROR: file /var/opt/UNItools/lib/libstatgrab.a exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/lib/libstatgrab.la ]; then
	echo "ERROR: file /var/opt/UNItools/lib/libstatgrab.la exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/lib/pkgconfig/libstatgrab.pc ]; then
	echo "ERROR: file /var/opt/UNItools/lib/pkgconfig/libstatgrab.pc exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/include/statgrab_deprecated.h ]; then
	echo "ERROR: file /var/opt/UNItools/include/statgrab_deprecated.h exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/include/statgrab.h ]; then
	echo "ERROR: file /var/opt/UNItools/include/statgrab.h exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/saidar
ldd /var/opt/UNItools/bin/statgrab
	) | sed '/=>/!d; s/.*=>//; s/(.*//' | while read SHAREDLIB
	do
		echo "$SHAREDLIB ... "
		if [ ! -e $SHAREDLIB ]; then
			echo "ERROR: shared lib $SHAREDLIB not found"
			ERROR=1
		else
			echo "ok"
		fi
	done
	else
		echo "no dynamically linked files found"
	fi
}

################################################################################
# Main
################################################################################

case $1 in
	cleanup)	rmfiles
				exit 0
	;;
	test)		:
	;;
	*)			echo "usage: /lan/ssi/shared/software/internal/pkg_tools/bin/pkg_conbat cleanup | test"
				exit 0
esac

test_noclobber
case $ERROR in
	0)	echo "no clobber passed ok"
	;;
	*)	echo error: fix the errors first
		exit 1
	;;
esac

(
	echo "installing files ... "
	cd $TMPROOT
	find var -type f| /bin/cpio -pvdVn /
)

echo "testing shared libs ... "
test_shared_libs

echo "Now try executing some of the commands"
echo "Clean up by executing /lan/ssi/shared/software/internal/pkg_tools/bin/pkg_conbat cleanup"

