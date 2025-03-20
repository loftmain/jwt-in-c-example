   /************************************************************************/
   /*  FILENAME     : update_logfile.c                                     */
   /*  DISCRIPTION  : log file¿« check point (chkpt.dat) update.           */ 
   /*  DATE         : 2000. 08. 29                                         */
   /*  WRITTEN      : ywoopark                                             */
   /************************************************************************/

#include <stdio.h>

extern char S2O_DAEMON[64];
extern int loging(char *msg,...);
extern int it_loging(char *format,...);

int update_chkpt(char *f_name, int count)
{
	FILE *fp;
	int sernum;
	int ret;

	if((fp=fopen(f_name,"r")) == NULL)
	{
		it_loging("libIT.a(%s): update_chkpt() file(%s) open error!\n", S2O_DAEMON, f_name);
		return(-1);
	}
	ret = fscanf(fp,"%d", &sernum);
	fclose(fp);

	if(sernum < 0)
		return(-1);

	if((fp=fopen(f_name,"w")) == NULL)
	{
		it_loging("libIT.a(%s): update_chkpt() file(%s) open error!\n", S2O_DAEMON, f_name);
		return(-1);
	}
	if(count == 0)
	{
		if((sernum+1) >= 100)
			fprintf(fp,"%d\n",0);
		else
			fprintf(fp,"%d\n",sernum+1);
	}
	else
	{
		if((sernum+1) >= count)
			fprintf(fp,"%d\n",0);
		else
			fprintf(fp,"%d\n",sernum+1);
	}
	fclose(fp);
	return(0);
}

int update_chkpt2(char *f_name, int count)
{
	FILE *fp;
	int sernum;
	int ret;

	if((fp=fopen(f_name,"r")) == NULL)
	{
		it_loging("libIT.a(%s): update_chkpt2() file(%s) open error!\n", S2O_DAEMON, f_name);
	} else {
		ret = fscanf(fp,"%d", &sernum);
		fclose(fp);
	}

	if(sernum < 0) sernum = 0;

	if((fp=fopen(f_name,"w")) == NULL)
	{
		it_loging("libIT.a(%s): update_chkpt2() file(%s) open error!\n", S2O_DAEMON, f_name);
		return(-1);
	}

	if(count == 0)
	{
		if((sernum+1) >= 100)
			fprintf(fp,"%d\n",0);
		else
			fprintf(fp,"%d\n",sernum+1);
	}
	else
	{
		if((sernum+1) >= count) fprintf(fp,"%d\n",0);
		else fprintf(fp,"%d\n",sernum+1);
	}

	fclose(fp);
	return(0);
}
