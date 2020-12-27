#include "queue.h"
#include <stdlib.h>
#include <string.h>

struct q_element {
	struct q_element *next;
	void *value;
};

struct queue {
	struct q_element *head;
};


Queue *q_create(void) {
	struct queue *p;

	if((p = (struct queue *)malloc(sizeof(struct queue))) != NULL){
		p->head = NULL;
	}
	return p;
}

int q_add(Queue *q, Item i, int prio) {
	(void) prio;
	struct q_element *p;

	p = (struct q_element *)malloc(sizeof(struct q_element));
	if (p != NULL) {
		p->value = i;
		p->next = q->head;
		q->head = p;
		return 1;
	}
	return 0;
}

Item q_remove(Queue *q) {
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
