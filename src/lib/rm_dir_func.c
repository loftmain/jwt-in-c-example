/*
 * Copyright (c) 2023, NEWSYSTECH Inc. All rights reserved.
 *
 * NAME
 *      rm_dir_func.c - Lib Function
 *
 * MODIFIED     (MM/DD/YYYY)
 *
 */

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../IT.extern.h"

int rm_dir_func(char* _rmdir)
{
	DIR *dp;
	struct  dirent *dirp;
	struct  stat statbuf;
	char tempfile[256];
	
	it_loging("%s: rm_dir_func() Start deleting directory (%s)\n", S2O_DAEMON, _rmdir);
	
	if ((dp = opendir(_rmdir)) == NULL) {
		it_loging("%s: rm_dir_func() Couldn't open directory(%s).\n", S2O_DAEMON, _rmdir);
		return(-1);
	}

	while ((dirp = readdir(dp)) != NULL) {
		if (!strcmp(dirp->d_name,".") || !strcmp(dirp->d_name,"..")) continue;
		sprintf(tempfile, "%s/%s", _rmdir, dirp->d_name);

		if (stat(tempfile, &statbuf) < 0) {
			it_loging("%s: rm_dir_func() file(%s) status read error.\n", S2O_DAEMON, tempfile);			
			continue;
		}	
		if (S_ISDIR(statbuf.st_mode)) { /* ���丮 */
			rm_dir_func(tempfile);
		} else {
			it_loging("%s: rm_dir_func() delete file. (%s)\n", S2O_DAEMON, tempfile);
			unlink(tempfile);
		}		
	}
	closedir(dp);
	
	if (rmdir(_rmdir) < 0) {
		it_loging("%s: rm_dir_func() Directory deletion failed. (%s)\n", S2O_DAEMON, _rmdir);
		return(-1);
	}
	it_loging("%s: rm_dir_func() Directory deletion successful. (%s)\n", S2O_DAEMON, _rmdir);

	return (0);
}
