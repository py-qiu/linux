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
 * Sample to demo how to implement euivalent operation of
 * POSIX P/V with SysV sem opeartion calls.  
 */

/* P() - int sem_wait(sem_t *sem); */
int my_sem_wait(int semid, int sem_num)
{
	struct sembuf  op;
	op.sem_num = sem_num;
	op.sem_op = -1; // request resource, P() 
	op.sem_flg = 0; // blocking wait
	if(semop(semid, &op, 1) < 0) {
		perror("fail to semop");
		return -1;
	}
	return 0;
}

/* V() - int sem_post(sem_t *sem); */
int my_sem_post(int semid, int sem_num)
{
	struct sembuf  op;
	op.sem_num = sem_num;
	op.sem_op = 1; // release resoource, V()
	op.sem_flg = 0;// blocking wait
	if (semop(semid, &op, 1) < 0) {
		perror("fail to semop");
		return -1;
	}
	return 0;
}
