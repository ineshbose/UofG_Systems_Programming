#include "queue.h"
#include <stdlib.h>
#include <string.h>

struct q_element {
	struct q_element *next;
	void *value;
	int prio;
};

struct queue {
	struct q_element *head;
};


Queue *q_create(void){
	struct queue *p;

	if((p = (struct queue *)malloc(sizeof(struct queue))) != NULL){
		p->head = NULL;
	}
	return p;
}

int q_add(Queue *q, Item i, int prio){
	struct q_element *p;
	struct q_element *x, *y;

	if(prio < MAX_PRIO || prio > MIN_PRIO){
		return 0;
    }

	if((p = (struct q_element *)malloc(sizeof(struct q_element))) != NULL){
		p->value = i;
		p->prio = prio;
		for(x=NULL, y=q->head; y != NULL; x=y, y=x->next){
			if(y->prio > prio){
				break;
            }
		}
		p->next = y;
		if(x == NULL){
			q->head = p;
        }
		else{
			x->next = p;
        }
		return 1;
	}
	return 0;
}

Item q_remove(Queue *q){
	struct q_element *p;
	Item i;

	if (q->head == NULL)
		return NULL;
	p = q->head;
	q->head = p->next;
	i = p->value;
	free(p);
	return i;
}
