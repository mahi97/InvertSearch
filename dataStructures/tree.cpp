#include "tree.h"

Tree::Tree()
{

}

void Tree::insert(Node * _node) {
    nodes.append(_node);
}

void Tree::show()
{
    for (size_t i{}; i < nodes.size(); i++)
        qDebug() << nodes[i]->key << " -> " << nodes[i]->files;
}
