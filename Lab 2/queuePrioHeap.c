#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define QUEUE_SIZE 1024

struct q_element {
	int prio;
	void *value;
};

struct queue {
	int nentries;
	struct q_element entry[QUEUE_SIZE+1];
};

static void swap(struct q_element *x, struct q_element *y){
	struct q_element t;

	t.value = x->value; t.prio = x->prio;
	x->value = y->value; x->prio = y->prio;
	y->value = t.value; y->prio =t.prio;
}

static void up(struct q_element x[], int n){
	int p, i = n;
	while(i > 1){
		p = i / 2;
		if(x[p].prio <= x[i].prio){
			break;
        }
		swap(x+p, x+i);
		i = p;
	}
}

static void down(struct q_element x[], int n){
	int c, i;

	i = 1;
	while(1){
		c = 2 * i;
		if(c > n){
			break;
        }
		if((c+1) <= n && x[c+1].prio < x[c].prio){
			c++;
        }
		if(x[i].prio <= x[c].prio){
			break;
        }
		swap(x+c, x+i);
		i = c;
	}
}

Queue *q_create(void){
	struct queue *p;
	int i;

	if((p = (struct queue *)malloc(sizeof(struct queue))) != NULL){
		p->nentries = 0;
		for(i = 1; i <= QUEUE_SIZE; i++){
			p->entry[i].value = NULL;
        }
	}
	return p;
}

int q_add(Queue *q, Item i, int prio){
	struct q_element *p;
	int n;

	if (prio < MAX_PRIO || prio > MIN_PRIO){
		return 0;
    }

	n = q->nentries + 1;
	if(n > QUEUE_SIZE){
		return 0;
    }
	p = &(q->entry[n]);
	p->value = i;
	p->prio = prio;
	if(n > 1){
		up(q->entry, n);
    }
	q->nentries = n;
	return 1;
}

Item q_remove(Queue *q){
	struct q_element *p;
	int n;
	Item i;

	if((n = q->nentries) <= 0){
		return NULL;
    }

	p = &(q->entry[1]);
	i = p->value;
	swap(p, p+n-1);
	if(--n > 1){
		down(q->entry, n);
    }
	q->nentries = n;
	return i;
}
