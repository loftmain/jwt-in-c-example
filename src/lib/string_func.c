#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 


/* ��Ʈ�� �ڸ��� */
char * substr(char *line, int offset, int len)
{ 
	int 	i; 
	char 	*res; 

	/* Memory Size */
	if ((offset + len) > (int)strlen(line))
		len = strlen(line) - offset;

	for (i = 0; i < offset; i++) 
		line++; 

	res = (char *)malloc(sizeof(char) * (len + 1)); 
	strncpy(res, line, len); 
	res[len] = '\0'; 

	return res; 
}

/* ���꽺Ʈ���� ��ġ�� �����Ѵ�. */
int str_index(char *line, char *kword, int offset)
{ 
	int 	pos; 
	char 	*temp; 

	temp = substr(line, offset, strlen(line) - offset); 
	pos = strstr(temp, kword) - temp + offset; 
	free(temp); 

	if (pos < 0)
		return -1;

	return pos; 
} 


/* ���꽺Ʈ���� ������ ��ġ�� �����Ѵ�. */
int str_rindex(char *line, char *kword)
{ 
	int 	offset, pos, old_pos; 

	if (!strstr(line, kword))
		return -1;

	offset = 0; 
	while (1)
	{ 
		pos = str_index(line, kword, offset); 
		if (pos > -1)
		{ 
			offset = pos + strlen(kword); 
			old_pos = pos; 
		} else
			break;
	} 
	return old_pos; 
} 

/* ��Ʈ�� �ӿ� ���Ե� ���꽺Ʈ���� ���� �����Ѵ�. */
int str_count(char *line, char *kword)
{ 
	int 	offset, pos, count = 0; 

	offset = 0; 
	while (1) { 
		pos = str_index(line, kword, offset); 
		if (pos > -1) { 
			count++; 
			offset = pos + strlen(kword); 
		} else
			break;
	} 
	return count; 
}
