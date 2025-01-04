#include "shared.h"
#include <stdio.h>
#include <stdlib.h>

int create_semaphores(key_t key) {
    int semid = semget(key, NUM_SEMAPHORES, IPC_CREAT | 0600);
    if (semid < 0) {
        perror("Blad przy tworzeniu zestawu semaforow (semget)");
        exit(1);
    }
    return semid;
}

void init_semaphore(int semid, int semnum, int value) {
    if (semctl(semid, semnum, SETVAL, value) == -1) {
        perror("Blad przy inicjalizacji semafora (semctl SETVAL)");
        exit(1);
    }
}

void P(int semid, int semnum) {
    struct sembuf sb;
    sb.sem_num = semnum;
    sb.sem_op  = -1;
    sb.sem_flg = 0;
    if (semop(semid, &sb, 1) == -1) {
        perror("Operacja P nie powiodła sie (semop)");
        exit(1);
    }
}

void V(int semid, int semnum) {
    struct sembuf sb;
    sb.sem_num = semnum;
    sb.sem_op  = +1; 
    sb.sem_flg = 0;
    if (semop(semid, &sb, 1) == -1) {
        perror("Operacja V nie powiodła sie (semop)");
        exit(1);
    }
}

void remove_semaphores(int semid) {
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("Blad przy usuwaniu zestawu semaforow (semctl IPC_RMID)");
    }
}

int get_semaphores(key_t key) {
    int semid = semget(key, NUM_SEMAPHORES, 0);
    if (semid < 0) {
        perror("Blad przy uzyskiwaniu zestawu semaforow (semget)");
        exit(1);
    }
    return semid;
}