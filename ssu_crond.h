/*
 * @file ssu_crond.h
 * @brief ssu_crond.c에서 사용되는 라이브러리, 매크로, 프로토타입 선언
 * @author 김병준 (kbj9704@gmail.com)
 */
#ifndef SSU_CROND_H
#define SSU_CROND_H

#include "common.h"
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

void set_daemon_process(void); // 데몬 프로세스 설정
#endif // SSU_CROND_H