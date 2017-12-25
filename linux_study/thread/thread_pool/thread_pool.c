/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include "thread_pool.h"

#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "condition.h"

void *thread_routine(void *arg)
{
    int timeout = 0;
    struct timespec abstime;
    threadpool_t *pool = (threadpool_t *)arg;
    while (1) {
       timeout = 0; 
       condition_lock(&pool->ready);
	   // 此时线程已创建，idle空闲线程+1
       pool->idle++;
       // 等待队列有任务到来或者线程池销毁通知
       while (pool->first == NULL && ! pool->quit) {
            printf("thread 0x%x is waiting\n", (int)pthread_self());
            clock_gettime(CLOCK_REALTIME, &abstime);
            abstime.tv_sec += 2;
            int status = condition_timewait(&pool->ready, &abstime);
            if (status == ETIMEDOUT) {
                printf("thread 0x%x is wait\n", (int)pthread_self());
                timeout = 1;
                break;
            }

       }
        // 等待到条件，处于工作状态
        pool->idle--;

        // 等待到任务
        if (pool->first != NULL) {
            // 队头取出任务
            task_t *t = pool->first;
            pool->first = t->next;
			// TODO: notice 1
            // 执行任务需要一定的时间，所以要现解锁，以便生产者线程
            // 能够往队列中添加任务，其他消费者线程能够进入等待任务
            condition_unlock(&pool->ready);
            t->run(t->arg);
            free(t);
            condition_lock(&pool->ready);
        }

        // 如果等待到线程池销毁通知，且任务都执行完毕
        if (pool->quit && pool->first == NULL) {
            pool->counter--;
            // when counter == 0, send signal to exit
            if (pool->counter == 0) {
                condition_signal(&pool->ready);
            }
            condition_unlock(&pool->ready);
            // break 之前一定要解锁
            break;
        }

        // timeout and task finished
        if (timeout && pool->first == NULL) {
            pool->counter--;
            if (pool->counter == 0) {
                condition_signal(&pool->ready);
            }
            condition_unlock(&pool->ready);
            // break 之前一定要解锁
            break;
        }
       condition_unlock(&pool->ready);
    }
    printf("thread 0x%x is exiting\n", (int)pthread_self());
    return NULL;
}

// 初始化线程池
void threadpool_init(threadpool_t *pool, int threads)
{
    // 对线程池的各个字段初始化
    condition_init(&pool->ready);
    pool->first  = NULL;
    pool->last   = NULL;
    pool->counter   = 0;
    pool->idle      = 0;
    pool->quit      = 0;
    pool->max_threads   = threads;
}

// 往线程池中添加任务
void threadpool_add_task(threadpool_t *pool
                            , void *(*run)(void *arg)
                            , void *arg)
{
    task_t *newtask = (task_t *)malloc(sizeof(newtask));
    newtask->run    = run;
    newtask->arg    = arg;
    newtask->next   = NULL;

    condition_lock(&pool->ready);

    // 将任务添加到队列
    if (pool->first == NULL) {
        pool->first = newtask;
    } else {
        pool->last->next = newtask;
    }
    pool->last = newtask;

    // 如果有线程等待，则唤醒其中一个
    if (pool->idle > 0) {
        condition_signal(&pool->ready);
    } else if (pool->counter < pool->max_threads) {
        // 没有等待线程，并且当前线程数不超过最大线程数，则创建一个新线程
        pthread_t tid;
        pthread_create(&tid, NULL, thread_routine, pool);
        pool->counter++;
    }
    condition_unlock(&pool->ready);
}

// 销毁线程池
void threadpool_destroy(threadpool_t *pool)
{
    if (pool->quit) {
        return;
    }
    
    condition_lock(&pool->ready);
    pool->quit = 1;

    // one of is processing thread, one of is idle thread
    if (pool->counter > 0) {
        if (pool->idle > 0) {   // idle thread
            condition_broadcast(&pool->ready);
        }

        // processing thread, can't receive broadcast signal
        // wait all thread exit
        while (pool->counter > 0) {
            condition_wait(&pool->ready);
        }
    }

    condition_unlock(&pool->ready);
    condition_destroy(&pool->ready);
}

