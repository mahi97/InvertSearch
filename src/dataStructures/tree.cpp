#include "dataStructures/tree.h"

Tree::Tree()
{

}

void Tree::insert(Data *_node) {
//    nodes.append(_node);
}

void Tree::show()
{
    for (size_t i{}; i < nodes.size(); i++)
        qDebug() << nodes[i]->key << " -> " /*<< nodes[i]->files*/;
}
