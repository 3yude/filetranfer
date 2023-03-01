#include "net.h"
#include <pthread.h>
#include <unistd.h>

void *test(void *);
struct id{
    pid_t pid;
    pthread_t tid;
};
int main() {
    struct id m, t;
    void *status;

    m.pid = getpid();
    m.tid = pthread_self();

    pthread_create(&t.tid, NULL, test, &t);

    pthread_join(t.tid, &status);

    printf("main: pid = %d tid = %ld \n", m.pid, m.tid);
    printf("child: pid = %d tid = %ld \n", t.pid, t.tid);
    printf("status = %d\n", (int)(status));

    return 0;
}


void *test(void *arg) {
    int ret = 63;
    struct id *t = (struct id *)arg;
    t->tid = pthread_self();
    t->pid = getpid();

    return (void *)ret;
}
