/*
  Set of procedures to control resources access
*/
typedef struct ftlock_status {
    int status;
    int pid;
    char name[128 + 1];
} ftlock_status;


int ftlock_open(void);
int ftlock_lock(char *name);
int ftlock_try_lock(char *name);
int ftlock_notify(int code);
int ftlock_get_state(char *name, int *pid);
ftlock_status ftlock_state();
int ftlock_pid(void);
int ftlock_wait(void);
int ftlock_unlock(void);
int ftlock_close(void);

