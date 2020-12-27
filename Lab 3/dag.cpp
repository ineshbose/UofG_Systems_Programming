#include <stdio.h>
#include <memory>
#include <vector>

struct node{
    const char *value;
    std::vector<std::shared_ptr<node>> edges_to;

    node(const char *v){
        value = v;
    }

    void add_edge_to(std::shared_ptr<node> n){
        edges_to.push_back(n);
    }
};

int main(){
    std::shared_ptr<node> a = std::make_shared<node>("a");
    std::shared_ptr<node> b = std::make_shared<node>("b");
    std::shared_ptr<node> c = std::make_shared<node>("c");
    std::shared_ptr<node> d = std::make_shared<node>("d");
    std::shared_ptr<node> e = std::make_shared<node>("e");
    std::shared_ptr<node> f = std::make_shared<node>("f");

    a->add_edge_to(b);
    a->add_edge_to(d);
    b->add_edge_to(c);
    b->add_edge_to(d);
    c->add_edge_to(e);
    d->add_edge_to(f);
    e->add_edge_to(f);

    return 0;
}
