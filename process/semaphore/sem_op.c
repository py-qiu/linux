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
 * Sample to demo how to use semop() to operate the sysV sem set.
 * The sample creates a sysV semaphore set object which contains
 * 10 semaphores, operates P() on the first semaphore and operates 
 * V() on the last one. 
 */

int semid = semget(key, 10, IPC_CREAT | 0666);

/* 
 * type struct sembuf, containing the following members:
 * unsigned short sem_num;  // semaphore number
 * short          sem_op;   // semaphore operation
 * short          sem_flg;  // operation flags
 */
struct sembuf sops[2]; /* only operate 2 of 10 */

sops[0].sem_num = 0;	/* Operate on semaphore 0, the first one in the set */
sops[0].sem_op = -1;	/* do P() for this semaphore */
sops[0].sem_flg = 0;	/* in blocking mode */

sops[1].sem_num = 9;	/* Operate on semaphore 9, the last one in the set */
sops[1].sem_op  = 1;	/* do V() for this semaphore */
sops[1].sem_flg = 0;	/* in blocking mode */

if (semop(semid, sops, 2) == -1) {
	perror("semop");
	exit(EXIT_FAILURE);
}
