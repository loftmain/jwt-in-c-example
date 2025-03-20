#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "../IT.extern.h"

extern int get_cfg2(char* config, char* ENV, char* value);
extern int get_cfg(char* ENV, char* value);
extern int it_loging(char *format,...);
extern int decrypt_file(char* file, char *type, char* dest);

int get_masterenv(char* _username, char* _passwd, char* _tnsname)
{
	char *default_user = "ITOPS";
	char *default_passwd = "itopsmgr";
	char *default_tnsname = "S2ODB";
	struct stat stbuf;
	char www_property[512];
	char itsm_home[256];
	char tnsName[128];
	/*char dbName[128];*/
	char userID[128];
	char pwdType[128];
	char passwd[128];
	char homedir[256];
	char dest[2048];
	int ret = -1;
	char file[512];

	/*
	IT_ORACLE_TNSNAME = S2ODB
	IT_ORACLE_USERID = itops
	IT_ORACLE_PSWDTYPE = 1
	IT_ORACLE_PSWD = IT_ORAPSWD.key
	*/

	memset(tnsName, 0, sizeof tnsName);
	memset(userID, 0, sizeof userID);
	memset(pwdType, 0, sizeof pwdType);
	memset(passwd, 0, sizeof passwd);

	get_cfg("IT_ORACLE_TNSNAME", tnsName);
	get_cfg("IT_ORACLE_USERID", userID);
	get_cfg("IT_ORACLE_PSWDTYPE", pwdType);
	get_cfg("IT_ORACLE_PSWD", passwd);

	if (strlen(tnsName) > 0 && strlen(userID) > 0 && strlen(pwdType) > 0 && strlen(passwd) > 0) {

		if (!strcmp(pwdType, "1") || !strcmp(pwdType, "2")) {
			memset(homedir, 0, sizeof homedir);
			get_cfg("IT_HOME", homedir);

			memset(dest, 0, sizeof dest);

			memset(file, 0, sizeof file);
			sprintf(file, "%s/%s", homedir, passwd);

			memset(passwd, 0, sizeof passwd);
			if (decrypt_file(file, pwdType, dest) > 0) {
				if (strlen(dest) > 0 && strlen(dest) < 128) {
					strncpy(passwd, dest, 127);	
				} else {
					it_loging("libIT.a(%s): get_masterenv() Decryption value error. file = %s\n", S2O_DAEMON, file);
				}
			}
		} else if ( !strcmp(pwdType, "0")) {
		} else {
			memset(passwd, 0, sizeof passwd);
			it_loging("libIT.a(%s): get_masterenv() Invalid Input value (IT_ORACLE_PSWDTYPE - Only allowed between 1 and 2)\n", S2O_DAEMON);
		}

		if (strlen(passwd) > 0) {
			strcpy(_tnsname, tnsName);
			strcpy(_username, userID);
			strcpy(_passwd, passwd);
			return 1;
		}
	}

	memset(itsm_home, 0, sizeof itsm_home);
	get_cfg("ITSM_HOME", itsm_home);

	memset(tnsName, 0, sizeof tnsName);
	/*memset(dbName, 0, sizeof dbName);*/
	memset(userID, 0, sizeof userID);
	memset(passwd, 0, sizeof passwd);

	memset(www_property, 0, sizeof www_property);
	if (strlen(itsm_home) > 0) {
		sprintf(www_property, "%s/WEB-INF/classes/db/dbpool/config/itops.properties", itsm_home);				
		ret = stat(www_property, &stbuf);
		if (ret > -1) {
			get_cfg2(www_property, "tnsName", tnsName);
			/*get_cfg2(www_property, "dbName", dbName);*/
			get_cfg2(www_property, "userID", userID);
			get_cfg2(www_property, "passwd", passwd);

			if (strlen(tnsName) > 0 || strlen(userID) > 0 || strlen(passwd) > 0 ) {
				if ( strlen(tnsName) > 0) strcpy(_tnsname, tnsName);
				else strcpy(_tnsname, default_tnsname);

				if (strlen(userID) > 0) strcpy(_username, userID);
				else strcpy(_username, default_user);

				if (strlen(passwd) > 0) strcpy(_passwd, passwd);
				else strcpy(_passwd, default_passwd);
				return 2;
			}
		}
	}
	strcpy(_tnsname, default_tnsname);
	strcpy(_username, default_user);
	strcpy(_passwd, default_passwd);
	return 3;
}

int get_masterenv2(char* _orahome, char* _oratnsadmin, char* _username, char* _passwd, char* _tnsname)
{
    if (strlen(s2oenv.cfg_home) == 0) return(-1);

    get_cfg("IT_ORACLE_HOME", _orahome);
    get_cfg("IT_ORACLE_TNS_ADMIN", _oratnsadmin);

	return get_masterenv(_username, _passwd, _tnsname);
}

int get_masterenv_mariadb(char* _username, char* _passwd, char* _instance, char* _ip, char* _port, char* _database1, char* _database2)
{
	char userID[128], passwd[128], instance[128], ip[128], port[128], database1[128], database2[128];

/*
	IT_MARIA_USERID =  root
	IT_MARIA_PSWD = 
	IT_MARIA_INSTANCE = maria
	IT_MARIA_IP = localhost
	IT_MARIA_PORT = 3306
	IT_MARIA_DATABASE1 = S2ODBS
	IT_MARIA_DATABASE2 = S2OCAPADBS

*/

	memset(userID, 0, sizeof userID);
	memset(passwd, 0, sizeof passwd);
	memset(instance, 0, sizeof instance);
	memset(ip, 0, sizeof ip);
	memset(port, 0, sizeof port);
	memset(database1, 0, sizeof database1);
	memset(database2, 0, sizeof database2);

	get_cfg("IT_MARIA_USERID", userID);
	get_cfg("IT_MARIA_PSWD", passwd);

	get_cfg("IT_MARIA_INSTANCE", instance);
	get_cfg("IT_MARIA_IP", ip);
	get_cfg("IT_MARIA_PORT", port);
	get_cfg("IT_MARIA_DATABASE1", database1);
	get_cfg("IT_MARIA_DATABASE2", database2);

	strcpy(_username, userID);
	strcpy(_passwd, passwd);

	if (strlen(instance) == 0) strcpy(_instance, "maria");
	else strcpy(_instance, instance);

	if (strlen(ip) == 0) strcpy(_ip, "127.0.0.1");
	else strcpy(_ip, ip);

	if (strlen(port) == 0) strcpy(_port, "3306");
	else strcpy(_port, port);

	if (strlen(database1) == 0) strcpy(_database1, "s2odbs");
	else strcpy(_database1, database1);

	if (strlen(database2) == 0) strcpy(_database2, "s2ocapadbs");
	else strcpy(_database2, database2);

	return 1;
}


