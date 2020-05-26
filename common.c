#include "common.h"

/**
 * @brief ���� �ð� ���
 * @param begin_t ���� �ð�
 * @param end_t ���� �ð�
 */
void ssu_runtime(struct timeval *begin_t, struct timeval *end_t) // ����ð� ��� 
{
	end_t->tv_sec -= begin_t->tv_sec;

	if(end_t->tv_usec < begin_t->tv_usec){
		end_t->tv_sec--;
		end_t->tv_usec += SECOND_TO_MICRO;
	}

	end_t->tv_usec -= begin_t->tv_usec;
	printf("Runtime: %ld:%06ld(sec:usec)\n", end_t->tv_sec, end_t->tv_usec);
}
