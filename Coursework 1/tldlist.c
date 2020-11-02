#include "tldlist.h"
#include <stdlib.h>
#include <string.h>


/*
 * TLDList that is actually the AVL tree.
 * 
 * begin  : the earliest date a log/node can be
 * end    : the latest date a log/node can be
 * count  : number of successful node insertions
 * root   : root node of the avl tree
 * 
 */
struct tldlist{

    Date *begin;
    Date *end;
    long count;
    struct tldnode *root;

};


/*
 * TLDNode that is actually a node of the AVL tree.
 * 
 * tldname : top level domain name (key for all nodes)
 * count   : number of logs/nodes corresponding to that tld
 * left    : left node (comes before, alphabetically)
 * right   : right node (comes after, alphabetically)
 * parent  : parent node
 * 
 */
struct tldnode{

    char *tldname;
    long count;

    long height;
    long balance;

    struct tldnode *left;
    struct tldnode *right;
    struct tldnode *parent;

};


/*
 * TLDIterator that moves through the AVL tree.
 * 
 * next : next node it will point to
 * prev : previous node being pointed
 * root : the root node for subtree
 * 
 */
struct tlditerator{
    struct tldnode *next;
    struct tldnode *prev;
    struct tldnode *root;
};


/*
 * Generates a list structure (TLDList / AVL Tree) for
 * storing counts against top level domains (TLDs).
 * 
 * parameters
 * -----------
 * begin : the earliest date a log can have
 * end   : the latest date a log can have
 * 
 * 
 * returns
 * --------
 * TLDList structure if successfully created, else NULL
 * 
 */
TLDList *tldlist_create(Date *begin, Date *end){
    struct tldlist *tld;

    if((tld = (struct tldlist *)malloc(sizeof(struct tldlist))) != NULL){
        tld->begin = date_duplicate(begin);
        tld->end = date_duplicate(end);
        tld->count = 0;
        tld->root = NULL;
    }
    return tld;
}


/*
 * HELPER FUNCTION (NOT DECLARED IN TLDLIST.H)
 * 
 * Deletes all TLDNode structures from the heap recursively.
 * First the tldname (char pointer) is freed. Then it moves
 * onto removing left and right nodes using recursion.
 * Finally, after the other nodes are NULL, the node itself is freed.
 * 
 * 
 * parameters
 * -----------
 * node : the node to remove
 * 
 */
void tldnode_destroy(TLDNode *node){
    if(node!=NULL){
        free(node->tldname);
        tldnode_destroy(node->left);
        tldnode_destroy(node->right);
        return free(node);
    }
}


/*
 * Deletes a TLDList and all its nodes that
 * were allocated in the heap.
 * 
 * parameters
 * -----------
 * tld : the TLDList to destroy
 * 
 */
void tldlist_destroy(TLDList *tld){
    date_destroy(tld->begin);
    date_destroy(tld->end);

    tldnode_destroy(tld->root);
    return free(tld);
}


/*
 * HELPER FUNCTION (NOT DECLARED IN TLDLIST.H)
 * 
 * Creates a TLDNode with all passed values.
 * 
 * 
 * parameters
 * -----------
 * tldname : the top level domain name
 * parent  : parent of the node (if any)
 * 
 * 
 * returns
 * --------
 * TLDNode structure if successfully created, else NULL
 * 
 */
TLDNode *tldnode_create(char *tldname, TLDNode *parent){
    struct tldnode *node;

    if((node = (struct tldnode *)malloc(sizeof(struct tldnode))) != NULL){
        if((node->tldname = (char *)malloc(sizeof(char)*(strlen(tldname) + 1))) != NULL){
            strcpy(node->tldname, tldname);
            node->count = 1;
            node->left = NULL;
            node->right = NULL;
            node->parent = parent;
        }
        else{
            /*
            * This is a case where TLDNode struct was successfully
            * allocated space, but char wasn't. So, since `tldname`
            * can't be store, the node needs to be free-d.
            * 
            */
            free(node);
        }
    }
    return node;
}


/*
 * HELPER FUNCTION (NOT DECLARED IN TLDLIST.H)
 * 
 * Returns the height of a node in AVL tree.
 * 
 * 
 * parameters
 * -----------
 * n : node to get the height for
 * 
 * 
 * returns
 * --------
 * node's height
 * 
 */
int height(TLDNode *n){
    return (n == NULL) ? -1 : n->height;
}


/*
 * HELPER FUNCTION (NOT DECLARED IN TLDLIST.H)
 * 
 * Reheights a node during rebalancing according
 * to the height of its children.
 * 
 * 
 * parameters
 * -----------
 * n : node to reheight
 * 
 */
void reheight(TLDNode *n){
    if(n != NULL){
        n->height = 1 + ((height(n->left) > height(n->right)) ? height(n->left) : height(n->right));
    }
}


/*
 * HELPER FUNCTION (NOT DECLARED IN TLDLIST.H)
 * 
 * Sets balance for a node after reheighting it.
 * 
 * 
 * parameters
 * -----------
 * n : node to reheight and balance
 * 
 */
void setBalance(TLDNode *n){
    reheight(n);
    n->balance = height(n->right) - height(n->left);
}


/*
 * HELPER FUNCTION (NOT DECLARED IN TLDLIST.H)
 * 
 * Rotates / moves around node(s) to left.
 * 
 * 
 * parameters
 * -----------
 * a : node(s) to rotate
 * 
 * returns
 * --------
 * newly rotated node(s) with its children
 * 
 */
TLDNode *rotateLeft(TLDNode *a){
    TLDNode *b = a->right;
    b->parent = a->parent;

    a->right = b->left;

    if(a->right != NULL){
        a->right->parent = a;
    }

    b->left = a;
    a->parent = b;

    if(b->parent != NULL){
        if(b->parent->right == a){
            b->parent->right = b;
        }
        else{
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);

    return b;
}


/*
 * HELPER FUNCTION (NOT DECLARED IN TLDLIST.H)
 * 
 * Rotates / moves around node(s) to right.
 * 
 * 
 * parameters
 * -----------
 * a : node(s) to rotate
 * 
 * returns
 * --------
 * newly rotated node(s) with its children
 * 
 */
TLDNode *rotateRight(TLDNode *a){
    TLDNode *b = a->left;
    b->parent = a->parent;

    a->left = b->right;

    if(a->left != NULL){
        a->left->parent = a;
    }

    b->right = a;
    a->parent = b;

    if(b->parent != NULL){
        if(b->parent->right == a){
            b->parent->right = b;
        }
        else{
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);

    return b;
}


/*
 * HELPER FUNCTION (NOT DECLARED IN TLDLIST.H)
 * 
 * Rotates / moves around node(s) to left then right.
 * 
 * 
 * parameters
 * -----------
 * a : node(s) to rotate
 * 
 * returns
 * --------
 * newly rotated node(s) with its children
 * 
 */
TLDNode *rotateLeftThenRight(TLDNode *n){
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}


/*
 * HELPER FUNCTION (NOT DECLARED IN TLDLIST.H)
 * 
 * Rotates / moves around node(s) to right then left.
 * 
 * 
 * parameters
 * -----------
 * a : node(s) to rotate
 * 
 * returns
 * --------
 * newly rotated node(s) with its children
 * 
 */
TLDNode *rotateRightThenLeft(TLDNode *n){
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}


/*
 * HELPER FUNCTION (NOT DECLARED IN TLDLIST.H)
 * 
 * Rebalances an AVL tree and its nodes after
 * an insertion.
 * 
 * 
 * parameters
 * -----------
 * n   : node to rebalance
 * tld : tld to rebalance
 * 
 */
void rebalance(TLDNode *n, TLDList *tld){
    setBalance(n);

    if(n->balance == -2){
        if(height(n->left->left) >= height(n->left->right)){
            n = rotateRight(n);
        }
        else{
            n = rotateLeftThenRight(n);
        }
    }
    else if(n->balance == 2){
        if(height(n->right->right) >= height(n->right->left)){
            n = rotateLeft(n);
        }
        else{
            n = rotateRightThenLeft(n);
        }
    }

    if(n->parent != NULL){
        rebalance(n->parent, tld);
    }
    else{
        tld->root = n;
    }
}


/*
 * Attempts to add a node to the TLDList (AVL Tree).
 * 
 * parameters
 * -----------
 * tld : the TLDList to add to
 * hostname : the hostname in the log
 * d : date of log
 * 
 * 
 * returns
 * --------
 * 0 if addition was a fail
 * 1 if addition was a success
 * 
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d){
    if(date_compare(tld->begin, d) > 0 || date_compare(d, tld->end) > 0){
        // if date lies outside the range, don't add
        return 0;
    }

    tld->count+=1;

    // gets TLD from hostname (+ 1 to remove '.' by going over that pointer)
    char *tldname = strrchr(hostname, '.') + 1;

    if(tld->root == NULL){
        // The tree is empty, therefore direct insertion
        tld->root = tldnode_create(tldname, NULL);
        return 1;
    }

    TLDNode *n = tld->root;
    while(1){
        if(strcmp(n->tldname, tldname) == 0){
            n->count+=1;
            return 0;
        }
        
        TLDNode *parent = n;
        int goLeft = (strcmp(tldname, n->tldname) < 0);
        n = goLeft ? n->left : n->right;

        if(n == NULL){
            if(goLeft){
                parent->left = tldnode_create(tldname, parent);
            }
            else{
                parent->right = tldnode_create(tldname, parent);
            }
            rebalance(parent, tld);
            break;
        }
    }
    return 1;
}


/*
 * Returns number of successful additions in
 * a TLDList (AVL Tree).
 * 
 * parameters
 * -----------
 * tld : the TLDList to get number of additions of
 * 
 * 
 * returns
 * --------
 * number of successful additions
 * 
 */
long tldlist_count(TLDList *tld){
    return tld->count;
}


/*
 * Generates an iterator structure (TLDIterator) for
 * iterating through the AVL Tree (TLDList).
 * 
 * parameters
 * -----------
 * tld : the TLDList to iterate through
 * 
 * 
 * returns
 * --------
 * TLDIterator structure if successfully created, else NULL
 * 
 */
TLDIterator *tldlist_iter_create(TLDList *tld){
    struct tlditerator *iter;

    if((iter = (struct tlditerator *)malloc(sizeof(struct tlditerator))) != NULL){
        iter->root = tld->root;
        iter->next = tld->root;
        iter->prev = NULL;
    }
    return iter;
}


/*
 * Iterates through TLDList and returns the next node.
 * 
 * parameters
 * -----------
 * iter : the TLDIterator
 * 
 * 
 * returns
 * --------
 * TLDNode if there is a next node, else NULL
 * 
 */
TLDNode *tldlist_iter_next(TLDIterator *iter){

    while(iter->next != NULL){
        if(iter->next->left != NULL){
            // starts to move to the left child
            iter->root = iter->next->left;
            
            while((iter->root->right != NULL) && (iter->root->right != iter->next)){
                // prepares subtree for next call
                iter->root = iter->root->right;
            }
            
            if(iter->root->right!=NULL){
                // moves state to right child
                iter->root->right = NULL;
                iter->prev = iter->next;
                iter->next = iter->next->right;
                return iter->prev;
            }
            else{
                // moves state to left child
                iter->root->right = iter->next;
                iter->next = iter->next->left;
            }
        }
        else{
            // moves to right child
            iter->prev = iter->next;
            iter->next = iter->next->right;
            return iter->prev;
        }
    }

    return NULL;
}


/*
 * Deletes a TLDIterator structure from the heap.
 * 
 * parameters
 * -----------
 * iter : the TLDIterator to destroy
 * 
 */
void tldlist_iter_destroy(TLDIterator *iter){
    return free(iter);
}


/*
 * Returns the Top Level Domain name of a log/node.
 * 
 * parameters
 * -----------
 * node : the node/log to get tldname from
 * 
 * 
 * returns
 * --------
 * top level domain name
 * 
 */
char *tldnode_tldname(TLDNode *node){
    return node->tldname;
}


/*
 * Returns number of logs for a specific tldname.
 * 
 * parameters
 * -----------
 * node : the node/tldname to get count from
 * 
 * 
 * returns
 * --------
 * number of logs for that tldname
 * 
 */
long tldnode_count(TLDNode *node){
    return node->count;
}