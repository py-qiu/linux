/*
 * (C) Copyright 2014
 * http://www.farsight.com.cn/
 * http://nj.hqyj.com/
 * 
 * This program is distributed in the purpose for training only
 * and hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Revision history
 * ------------------------------------------------------
 * 20140928	unicornx	initial archived
 */
/*
 * Sample to demo how to use semctl() to control sysV sem set.
 */

/* 
 * To call semctl(), the calling program must define this union 
 * as follows:
 */
union semun {
       int              val;    /* Value for SETVAL */
       struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
       unsigned short  *array;  /* Array for GETALL, SETALL */
       struct seminfo  *__buf;  /* Buffer for IPC_INFO(Linux-specific) */
};

/* create a sysV sem set object with 10 semaphore */
int semid = semget(key, 10, IPC_CREAT | 0666);

/* 
 * Sample 1: set the value for the first semaphore of the set to 1 
 * similar as POSIX sem_init()
 */
union semun mysemun;
mysemun.val = 1;
if ((semctl( 
	semid,	
	0,	/* first semaphore of the set */
	SETVAL, /* set value */
	mysemun
	)) < 0) {
	perror("Fail to semctl");
	exit(EXIT_FAILURE);
}

/* 
 * Sample 2: remove the semaphore set 
 * similar as POSIX sem_destroy(), but here is to remove the
 * whole semaphore set, including all the semaphores.
 */
if (semctl(
	semid,
	0, /* this argument is ignored when cmd is IPC_RMID */
	IPC_RMID,
	0
	) < 0 ) {
	perror("Fail to semctl  IPC_RMID");
	exit(EXIT_FAILURE);
}
