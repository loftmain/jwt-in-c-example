#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>

char *get_user_name(uid_t id)
{
	struct passwd *pass  = NULL;
	char *name = NULL;

	pass = getpwuid(id);

	if (pass) {
	  	name = pass->pw_name;
	} else return "";
	return name;
}

char *get_group_name(gid_t gid)
{
	struct group *grp  = NULL;
	char *gname = NULL;

	grp = getgrgid(gid);

	if (grp) {
	  	gname = grp->gr_name;
	} else return "";
	return gname;
}
