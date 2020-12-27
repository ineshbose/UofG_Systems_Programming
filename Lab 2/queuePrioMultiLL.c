#include "queue.h"
#include <stdlib.h>
#include <string.h>

#define PRIODIFF (MIN_PRIO - MAX_PRIO + 1)

struct q_element {
	struct q_element *next;
	void *value;
};

struct q_head {
	struct q_element *head;
	struct q_element *tail;
};

struct queue {
	struct q_head llist[PRIODIFF];
};

Queue *q_create(void){
	struct queue *p;
	struct q_head *h;
	int i;

	if((p = (struct queue *)malloc(sizeof(struct queue))) != NULL){
		for(i = 0; i < PRIODIFF; i++){
			h = &(p->llist[i]);
			h->head = NULL;
			h->tail = NULL;
		}
	}
	return p;
}

int q_add(Queue *q, Item i, int prio){
	struct q_element *p;
	struct q_head *h;

	if (prio < MAX_PRIO || prio > MIN_PRIO){
		return 0;
    }

	prio -= MAX_PRIO;
	if((p = (struct q_element *)malloc(sizeof(struct q_element))) != NULL){
		p->value = i;
		p->next = NULL;
		h = &(q->llist[prio]);
		if(h->head == NULL){
			h->head = p;
        }
		else{
			h->tail->next = p;
        }
		h->tail = p;
		return 1;
	}
	return 0;
}

Item q_remove(Queue *q){
	struct q_head *h;
	struct q_element *p;
	int prio;
	Item i;

	for(prio = 0; prio < PRIODIFF; prio++){
		h = &(q->llist[prio]);
		if(h->head == NULL){
			continue;
        }
		p = h->head;
		h->head = p->next;
		if(h->head == NULL){
			h->tail = NULL;
        }
		i = p->value;
		free(p);
		return i;
	}
	return NULL;
}
