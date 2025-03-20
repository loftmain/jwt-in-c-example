#
# $Id: Makefile,v 1.7 2002/09/04 srp Exp $
#
#   Copyright (c) 2013,2014,2015
#             NewSystech Inc.  All rights reserved.
#

CC          = gcc
#CFLAGS		= -g -O2				  # for Linux
CFLAGS		= -g -O2 -fPIC			  # for Linux (64bit)
#CFLAGS     = -O                      # This is for Solaris, NCRUX, Digital Unix
#CFLAGS     = -O -xarch=v9            # This is for Solaris, NCRUX, Digital Unix(64bit) 
                                      # IT.orac 64bit컴파일시 -xarch=v9 포함 필요
#CFLAGS     = -O ultra -xarch=v9 -xO5 -xstrconst -xdepend -Xa # This is for Solaris, NCRUX, Digital Unix(64bit) 
#CFLAGS     = -O -m64                 # This is for Solaris, NCRUX, Digital Unix
#CFLAGS     = -O -Aa -D_HPUX_SOURCE   		# This is for only HP Unix
#CFLAGS     = -O -Aa -D_HPUX_SOURCE +DA2.0W # This is for only HP Unix, 64bit로 컴파일시
#CFLAGS     = -O -Aa -D_HPUX_SOURCE +DA2.0N # This is for only HP Unix, 32bit로 컴파일시
#CFLAGS     = -O -Aa -Wl,-a -D_HPUX_SOURCE   # This is for only HP Unix ia64
#CFLAGS     = -O -Aa -Wl,-a -D_HPUX_SOURCE +DD64   # This is for only HP Unix ia64, 64bit로 컴파일시
#CFLAGS     = -O -Aa -Wl,-a -D_HPUX_SOURCE +DD32   # This is for only HP Unix ia64, 32bit로 컴파일시
#CFLAGS     =  -Wl,-a -D_HPUX_SOURCE   # This is for only HP Unix ia64 (11.23)
#CFLAGS     = -O                 	  # This is for AIX compile 
#CFLAGS     = -O -q64                	  # This is for AIX 64bit compile
CONFIGSH    = ../config.sh
LDFLAG      = -G
LIBS        = -lsocket -lnsl
OBJECTS     = date1.o time2epoch.o get_cfg.o chkip.o getdata.o wlog.o local_write.o \
			  loging.o ltrim.o rtrim.o sigchldwaitpid.o signal.o \
			  readable_timeo.o readn.o writen.o wrapsock.o ping.o mailsock.o \
              socket.o sockutil.o error_log.o rm_dir_func.o \
              update_chkpt.o store_errmsg.o set_blocking.o \
              fcopy.o size_check.o changetab.o slog.o get_chkpt.o \
              getitem.o prscnt.o search_point.o loging_f.o it_loging.o \
              is_valid_msg.o etc_encrypt.o etc_decrypt.o ora_encrypt.o \
              time.o timestr.o token_string.o is_valid_ip.o expand_env.o \
              check_lic.o daemonize.o daemonized.o get_chkserv.o get_chkrouter.o \
			  set_process.o get_process.o dump_ps.o dump_tempfile.o strutil.o \
			  set_job.o set_jobpattern.o agentver.o set_except_host.o set_allow_host.o set_sysmods_lst.o \
			  configSyslogSet.o configPcuSet.o runPcuGet.o is_exclude_mounted.o \
			  configNetwork.o set_sysmods.o set_read_cfg.o get_name.o DES_func.o s2o_crypt.o \
			  changedate.o file_write.o file_read.o file_compare.o get_filesystem.o int2comma.o \
			  set_cfg.o rcvd_local_write.o lm_md5_crypt.o KISA_SHA256.o s2o_sha256_encrypt.o s2o_sha256_encrypt2.o \
			  get_evt_subclass.o get_sock_errno.o read_ha_status_set.o write_ver.o it_call_loging.o \
			  get_masterenv.o get_s2o_hostname.o get_s2opid.o get_linuxtype.o get_osrelease.o mtrim.o \
			  get_s2o_env.o get_envhome.o save_rawdata.o get_itdev.o get_accountinfo.o set_account_expire.o \
			  get_bootmin.o change_orac_auth.o update_timezone.o set_except_chktime.o config_daemon_sighup.o

all          : config libIT.a install

# making config.h
config       :
	$(CONFIGSH)

# shared library make
libIT.so : $(OBJECTS) 
		$(LD) $(LDFLAG) -o $@ $(OBJECTS)

# static library make
libIT.a  : $(OBJECTS)
		ar cr $@ $(OBJECTS) 
#		ar -X64 cr $@ $(OBJECTS) 		# This for AIX 64bit compile option

install      :
		cp libIT.a  ../

clean        :
		rm -f *.o
		rm -f libIT.a
