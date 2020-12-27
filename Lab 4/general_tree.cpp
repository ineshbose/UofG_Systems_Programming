#include <stdio.h>
#include <memory>
#include <vector>

struct node {
    const char * value;
    std::vector< std::unique_ptr<node> > children;

    node(const char * v) { value = v; }

    void add_child(std::unique_ptr<node> n) {
        children.push_back(std::move(n));
    }
};


// This function should print the tree.
// It should take NO ownership of any node.
// The int level should be used to indent the value with whitespace,
// it should be increased for every recursive call
void print(/* ??? */ ptr, int level);

// This function should return the first child of the given node.
// It should remove the child from the tree and return it.
// The ownership should be transfered out of the tree to the caller.
//
// Think about what the 
// Think about what the return type of the function should be!
/* ??? */ take_first_child(/* ??? */ root);

int main() {
    // create a node using
    //   std::make_unique<node>("name");
    // you will need to add the -std=c++14 flag for this
    // alternatively, with the -std=c++11 flag you can use:
    //   std::unique_ptr<node>(new node("name") );
}