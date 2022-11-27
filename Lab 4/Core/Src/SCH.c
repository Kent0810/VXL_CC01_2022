/*
 * SCH.c
 *
 *  Created on: Nov 20, 2022
 *      Author: Admin
 */

#include <SCH.h>

TaskLL SCH_tasks_G;


void SCH_Init(void) {
    SCH_tasks_G.head = NULL;
    SCH_tasks_G.size = 0;
}

uint32_t SCH_Add_Task(void (*pFunction)(void), uint32_t DELAY, uint32_t PERIOD) {
    taskNode *node = (taskNode *)malloc(sizeof(taskNode));
    node->task.pTask = pFunction; // node->data->pTask
    node->task.Delay = DELAY;
    node->task.Period = PERIOD;
    if (TICKS > 0) {
        node->task.Delay /= TICKS; // ko bi /0
    }
    node->task.RunMe = 0;
    // init gia tri cho node

    uint8_t idx = 0;
    if (SCH_tasks_G.size == 0) {
        SCH_tasks_G.head = node;
    } else {
        taskNode *cur = SCH_tasks_G.head;
        taskNode *prev = NULL;
        while (cur != NULL && node->task.Delay > cur->task.Delay) { // trừ cho delay của các tásk trước đó để tránh overlapping
            node->task.Delay -= cur->task.Delay;
            prev = cur;
            cur = cur->pNext;
            idx++;
        }
        if (prev == NULL) { //add vao dau
            node->pNext = cur;
            cur->task.Delay -= node->task.Delay;
            SCH_tasks_G.head = node;
        } else {
        	//add vao giua 2 node
            prev->pNext = node;
            node->pNext = cur;
            if (cur) {
                cur->task.Delay -= node->task.Delay;
            }
        }
    }
    SCH_tasks_G.size++;
    return idx;
}
void SCH_Delete_Task(uint32_t TaskIdx) {
    if (TaskIdx < 0 || TaskIdx >= SCH_tasks_G.size)
        return;

    taskNode *temp = SCH_tasks_G.head;
    if (TaskIdx == 0) {
        SCH_tasks_G.head = temp->pNext;
        SCH_tasks_G.head->task.Delay += temp->task.Delay;
    } else {
        uint32_t Index = 0;
        taskNode *cur = SCH_tasks_G.head;

        while (Index < TaskIdx - 1) {
            cur = cur->pNext;
            Index++;
        }
        temp = cur->pNext;
        cur->pNext = temp->pNext;
        cur->pNext->task.Delay += temp->task.Delay;
    } //lam cho chac
    free(temp);
    temp = NULL;
    SCH_tasks_G.size--;
}

void SCH_Update(void) {
    if (SCH_tasks_G.head->task.Delay == 0) {
        SCH_tasks_G.head->task.RunMe = 1;
    } else {
        SCH_tasks_G.head->task.Delay--;
    }
}

void SCH_Dispatch_Tasks(void) {
    if (SCH_tasks_G.head->task.RunMe == 1) {
        (*SCH_tasks_G.head->task.pTask)();

        if (SCH_tasks_G.head->task.Period > 0) { //ko add vo lai -oneshot task
            SCH_Add_Task(SCH_tasks_G.head->task.pTask, SCH_tasks_G.head->task.Period, SCH_tasks_G.head->task.Period);
        }

        SCH_Delete_Task(0);
    }
}
