/*
 * SCH.h
 *
 *  Created on: Nov 20, 2022
 *      Author: Admin
 */

#ifndef INC_SCH_H_
#define INC_SCH_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*pTask)(void); // function pointer
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe; // timerFlag

} sTasks;
typedef struct taskNode {
    sTasks task;
    struct taskNode *pNext;
} taskNode;
typedef struct {
    taskNode *head;

    uint32_t size;
} TaskLL;

#define TICKS 10


void SCH_Init(void);

uint32_t SCH_Add_Task(void (*pFunction)(),
                      uint32_t DELAY,
                      uint32_t PERIOD); // setTimer

void SCH_Update(void); // timerRun

void SCH_Dispatch_Tasks(void); // check flag

void SCH_Delete(uint32_t ID);
#endif /* INC_SCH_H_ */
