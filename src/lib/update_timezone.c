#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int get_cfg(char* ENV, char* value);
extern int get_cfg2(char* config, char* ENV, char* value);

void update_timezone(char *_timezone)
{
	char tmp_timezone[256];

	memset(tmp_timezone, 0, sizeof tmp_timezone);
    get_cfg("IT_TIMEZONE", tmp_timezone);

    if (!strcmp(tmp_timezone, "KST")) {
        /* localtime�� �ѱ� �ð����� ���� */
        putenv("TZ=UTC-9\0");
        /*setenv("TZ", "UTC-9", 1);*/
    } else if (!strcmp(tmp_timezone, "VIETNAM")) {
        /* localtime�� ��Ʈ�� �ð����� ���� */
        putenv("TZ=UTC-7\0");
        /*setenv("TZ", "UTC-7", 1);*/
    } else {
		return;
	}

	sprintf(_timezone, "%s\0", tmp_timezone);
}

void update_timezone2(char* _config, char *_timezone)
{
	char tmp_timezone[256];

	memset(tmp_timezone, 0, sizeof tmp_timezone);
    get_cfg2(_config, "IT_TIMEZONE", tmp_timezone);

    if (!strcmp(tmp_timezone, "KST")) {
        /* localtime�� �ѱ� �ð����� ���� */
        putenv("TZ=UTC-9\0");
        /*setenv("TZ", "UTC-9", 1);*/
    } else if (!strcmp(tmp_timezone, "VIETNAM")) {
        /* localtime�� ��Ʈ�� �ð����� ���� */
        putenv("TZ=UTC-7\0");
        /*setenv("TZ", "UTC-7", 1);*/
    } else {
		return;
	}
	sprintf(_timezone, "%s\0", tmp_timezone);
}

