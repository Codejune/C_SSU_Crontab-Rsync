/**
 * @file cron_support.c
 * @brief ssu_crontab, ssu_crond���� ���������� ���Ǵ� �Լ� 
 * @author �躴�� (kbj9704@gmail.com)
 */

#include "cron_support.h"

extern char reservation_command[BUFFER_SIZE][MAX_BUFFER_SIZE];

/**
 * @brief �Է��� ������� ��ū ����ü�� ��ȯ
 * @param command ����� ��ū ����ü
 * @param command_buffer ��� ���ڿ�
 */
void make_command_token(CommandToken *command, char *command_buffer) // �Է��� ������� ��ū ����ü�� ��ȯ
{
	char *tmp;
	char *last;
#ifdef DEBUG
	printf("make_command_token(): command_buffer = %s\n", command_buffer);
#endif
	command->argv = (char**)calloc(BUFFER_SIZE, sizeof(char*));
	command->argc = 0;

	if ((tmp = strtok_r(command_buffer, " ", &last)) == NULL)
		return;
#ifdef DEBUG
	printf("make_command_token(): command->argv[%d] = %s\n", command->argc, tmp);
#endif

	command->argv[command->argc] = (char *)calloc(BUFFER_SIZE, sizeof(char));
	strcpy(command->argv[command->argc++], tmp);

	while ((tmp = strtok_r(NULL, " ", &last)) != NULL) {
#ifdef DEBUG
		printf("make_command_token(): command->argv[%d] = %s\n", command->argc, tmp);
#endif
		command->argv[command->argc] = (char *)calloc(BUFFER_SIZE, sizeof(char)); // ����� ���� �޸� ���� �Ҵ�
		strcpy(command->argv[command->argc++], tmp);
	}
}

/**
 * @brief ����� ����ü �ʱ�ȭ
 * @param command ����� ����ü
 */
void free_command_token(CommandToken *command) // ����� ����ü �ʱ�ȭ
{
	int i;

	for (i = 0; i < command->argc; i++)
		free(command->argv[i]);
	free(command->argv);
}

/**
 * @brief ���� ��� ��� ��������
 */
int get_reservation_command(void) // ���� ��� ��� ��������
{
	FILE *fp;

	int count = 0;

	if ((fp = fopen(CRONTAB_FILE, "r+")) == NULL) {
		fprintf(stderr, "get_reservation_command: fopen error for %s\n", CRONTAB_FILE);
		return count;
	}

	while(fscanf(fp, "%[^\n]\n", reservation_command[count]) > 0)
		count++;
#ifdef DEBUG
	printf("get_reservation_command: reservation_count = %d\n", count);
#endif

	fclose(fp);
	return count;
}

/**
 * @brief �α� ���Ͽ� �̷� ���
 * @param command_type ��� Ÿ�� ��ȣ
 * @param command ��� ���ڿ�
 */
void write_log(int command_type, char *command) // �α� ���Ͽ� �̷� ���
{
	FILE *fp;
	time_t now_t;
	struct tm *now_tm;
	char temp[MAX_BUFFER_SIZE];

	/*
	if ((fp = fopen(CRONTAB_LOG, "r+")) == NULL)
	{
		fprintf(stderr, "write_log: fopen error for %s\n", CRONTAB_LOG);
		return;
	}
	fseek(fp, 0, SEEK_END);
*/
	time(&now_t);
	now_tm = localtime(&now_t);

	switch (command_type) {
		case ADD:
			sprintf(temp, "echo \"[%.24s] %s %s\" >> %s", asctime(now_tm), "add", command, CRONTAB_LOG);
			//fprintf(fp, "[%.24s] %s %s\n", asctime(now_tm), "add", command);
			break;
		case REMOVE:
			sprintf(temp, "echo \"[%.24s] %s %s\" >> %s", asctime(now_tm), "remove", command, CRONTAB_LOG);
			//fprintf(fp, "[%.24s] %s %s\n", asctime(now_tm), "remove", command);
			break;
		case RUN:
			sprintf(temp, "echo \"[%.24s] %s %s\" >> %s", asctime(now_tm), "run", command, CRONTAB_LOG);
			//fprintf(fp, "[%.24s] %s %s\n", asctime(now_tm), "run", command);
			break;
	}
	system(temp);
	//fflush(fp);
	//fclose(fp);
}


