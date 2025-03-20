/*
   $Id: configPcuSet.c,v 1.8 2005/03/12 srp Exp $

   Copyright (c) 2000-2005 i-TOP System Inc.  All rights reserved.
*/
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>


#include "../IT.extern.h"

extern int it_loging(char *format,...);
extern int getitem(int ch, char *src, char *dest, int seqitem);
extern int getitemc(int ch, char *src);
extern int rtrim(char* sbuf);

int configPcuSet(char *homedir)
{
  	FILE 	*fd;

  	char 	fline[1024], cfgname[256]; 
	char 	def_owner[25], def_pname[512], def_uncheck[2]; 
	char	def_memory[16], def_cpuusage[4], def_cputime[16];
	char	def_item[8], def_command[128], def_save[2], def_occur[64];
	char	def_elevel[2];
	char	buf[16];
  	int 	proc_num = 0, cputime = 0, f_cputime = 0, memory = 0;
	float	cpuusage = 0, f_cpuusage = 0;

	sprintf(cfgname, "%s/proccpu.cfg", homedir);

  	if ((fd = fopen (cfgname, "r")) == NULL) {
		it_loging("libIT.a(%s): configPcuSet() file open error.\n", S2O_DAEMON);
      	return (0);
    }

  	/* read lines off of the file until EOF */
  	while (fgets(fline, 1023, fd) != NULL) {
      	/* perl-style comments */
      	if (fline[0] == '#' || isspace (fline[0]) || fline[0] == '\n')
			continue;
		
		memset(def_pname, 0x00, sizeof def_pname);
		memset(def_uncheck, 0x00, sizeof def_uncheck);
		memset(def_owner, 0x00, sizeof def_owner);
		memset(def_memory, 0x00, sizeof def_memory);
		memset(def_cpuusage, 0x00, sizeof def_cpuusage);
		memset(def_cputime, 0x00, sizeof def_cputime);
		memset(def_item, 0x00, sizeof def_item);
		memset(def_command, 0x00, sizeof def_command);
		memset(def_save, 0x00, sizeof def_save);
		memset(def_occur, 0x00, sizeof def_occur);
		memset(def_elevel, 0x00, sizeof def_elevel);

		getitem(';', fline, def_pname, 1);
		getitem(';', fline, def_uncheck, 2);
		getitem(';', fline, def_owner, 3);
		if (getitem(';', fline, def_memory, 4) == 0) {
			if (strlen(def_memory) == 0)
				memory = 0;
			else 
				memory = atoi(def_memory);
		}
		else 
			memory = 0;

		if (getitem(';', fline, def_cpuusage, 5) == 0)
			cpuusage = atof(def_cpuusage);
		else 
			cpuusage = 0;
		if (getitem(';', fline, def_cputime, 6) == 0)
			cputime = atoi(def_cputime);
		else 
			cputime = 0;
		getitem(';', fline, def_item, 7);
		getitem(';', fline, def_command, 8);
		getitem(';', fline, def_save, 9);
		getitem(';', fline, def_occur, 10);

		memset(buf, 0, sizeof buf);
		if (getitem(';', fline, buf, 11) == 0)
			f_cpuusage = atof(buf);
		else 
			f_cpuusage = 0;

		memset(buf, 0, sizeof buf);
		if (getitem(';', fline, buf, 12) == 0)
			f_cputime = atoi(buf);
		else 
			f_cputime = 0;

		memset(buf, 0, sizeof buf);
		getitem(';', fline, buf, 13);
		def_elevel[0] = buf[0];
	

  		/* reallocate array to hold the new entry */
		defPcu = (struct def_pcu *) realloc (defPcu, (proc_num + 1) * sizeof (struct def_pcu));

		if (defPcu == NULL) {
			it_loging("libIT.a(%s): configPcuSet() struct realloc error.\n", S2O_DAEMON);
			fclose(fd);
  			return(-1);
		}
		if ( strlen(def_pname) > 254) def_pname[255]='\0';
	    strcpy(defPcu[proc_num].processName, def_pname);
	    strcpy(defPcu[proc_num].uncheck, def_uncheck);
	    strcpy(defPcu[proc_num].owner, def_owner);
	    defPcu[proc_num].memory = memory;
	    defPcu[proc_num].cpuusage = cpuusage;
	    defPcu[proc_num].cputime = cputime;
	    defPcu[proc_num].f_cpuusage = f_cpuusage;
	    defPcu[proc_num].f_cputime = f_cputime;
	    strcpy(defPcu[proc_num].item, def_item);
	    strcpy(defPcu[proc_num].command, def_command);
	    strcpy(defPcu[proc_num].save, def_save);
		if (strlen(def_occur) == 0) strcpy(def_occur, "1");
		defPcu[proc_num].occurence = atoi(def_occur);
		if(defPcu[proc_num].occurence < 1) defPcu[proc_num].occurence = 1;
		if(defPcu[proc_num].occurence > 100 ) defPcu[proc_num].occurence = 100;
	    strcpy(defPcu[proc_num].Level, def_elevel);
/*
		it_loging("libIT.a(%s); configPcuSet() -> %s %s %s %d %5.2f %d %s %s %s\n", S2O_DAEMON, defPcu[proc_num].processName, defPcu[proc_num].uncheck, defPcu[proc_num].owner, defPcu[proc_num].memory, defPcu[proc_num].cpuusage, defPcu[proc_num].cputime, defPcu[proc_num].item, defPcu[proc_num].command, defPcu[proc_num].save);
*/
      	proc_num++;
    }
	fclose(fd);
  	return (proc_num);
}
