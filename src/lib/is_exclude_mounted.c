/*

	* 2018-09-05
		- /var/xen/xc-install 이이사님 요청으로 제외
	* 2021-12-27
		- /snap/ 이이사님 요청으로 제외
*/
#include<stdio.h>
#include<string.h>
#include "config.h"

int is_exclude_mounted(char* _mounted, char* _filesystem)
{
	if (!strncmp(_mounted, "/cdrom", 6)
		|| !strncmp(_mounted, "/proc", 5)
		|| !strncmp(_mounted, "/stats", 6) /* NCRUX */
		|| !strncmp(_mounted, "/dev/shm", 8)
		|| !strncmp(_mounted, "/dev/odm", 8)
		|| !strncmp(_mounted, "/localrepo", 10)  /* LGD */
		|| !strncmp(_mounted, "/etc/mnttab", 11)
		|| !strncmp(_mounted, "/media/UDF", 10)
		|| !strncmp(_mounted, "/mnt/cdrom", 10)
		|| !strncmp(_mounted, "/run/midia", 10)
		|| !strncmp(_mounted, "/run/media", 10)
		|| !strncmp(_mounted, "/mnt/iso", 8)
		|| !strncmp(_mounted, "/snap/gnome-", 12) /* UBC */
		|| !strncmp(_mounted, "/snap/core", 10) /* UBC */
		|| !strncmp(_mounted, "/snap/gtk-common-", 17) /* UBC */
		|| !strncmp(_mounted, "/media/", 7)   /* LGD (cdrom mountd) */
		|| !strncmp(_mounted, "/var/opt/ignite/recovery", strlen("/var/opt/ignite/recovery"))   /* LGD (backup) 2023/03/06 */
		|| !strcmp(_mounted, "/root/mnt") /* cdrom (LGD) */
		|| !strcmp(_mounted, "/root/ib") /* cdrom (LGD) */
		|| !strncmp(_mounted, "/var/xen/xc-install", strlen("/var/xen/xc-install"))
		|| !strcmp(_mounted, "/mnt") /* (LGD) 2020-02-03 */
		|| !strcmp(_filesystem, "/dev/loop0") /* (LGD) 2020-02-03 */
		|| !strncmp(_filesystem, "/dev/loop", strlen("/dev/loop")) /* 2022/06/16 */
		|| !strncmp(_mounted, "/dev/fd", 7)) { /* if cdrom mounted, skip it checking */
		return 1;
	}

	#if defined(LINUX)
		if (!strncmp(_mounted, "/snap/lxd/", 10)
			|| !strncmp(_mounted, "/snap/snapd/", 12)
			|| !strncmp(_mounted, "/snap/", 6) /* 2021/12/27 ( 대교CNS) */
		)
		{
			return 1;
		}
	#elif defined(AIX)
		if (!strcmp(_filesystem, "/ahafs") /* 2023/12/26 */
		)
		{
			return 1;
		}
	#endif

	return 0;
}
