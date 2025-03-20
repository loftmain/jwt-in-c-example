#include <stdio.h>
#include <string.h>
/*
사용되지 안음 ( is_exclude_mounted 사용됨)
*/

int confirm_mounted(char* _mounted)
{
	if (!strncmp(_mounted, "/cdrom", 6)
		|| !strncmp(_mounted, "/proc", 5)
		|| !strncmp(_mounted, "/stats", 6) /* NCRUX */
		|| !strncmp(_mounted, "/dev/shm", 8)
		|| !strncmp(_mounted, "/dev/odm", 8)
		|| !strncmp(_mounted, "/localrepo", 10)  /* LGD */
		|| !strncmp(_mounted, "/etc/mnttab", 11)
		|| !strncmp(_mounted, "/mnt/cdrom", 10)
		|| !strncmp(_mounted, "/media/", 7 )	/* LGD (cdrom mountd) */
		|| !strcmp(_mounted, "/root/mnt")	/* LGD (cdrom mountd) */
		|| !strcmp(_mounted, "/root/ib")	/* LGD (cdrom mountd) */
		|| !strncmp(_mounted, "/dev/fd", 7)) { /* if cdrom mounted, skip it checking */
		return 0;
	}
	return 1;
}
