#include <stdio.h>
#include <stdlib.h>
#include "linked-list.h"

LinkedList::LinkedList() {
    _length = 0;
    _head = NULL;
    _tail = NULL;
}

LinkedList::~LinkedList() {}

int LinkedList::size() {
    return _length;
}

void LinkedList::add(CheckerboardIndex new_cb_index) {
    LinkedNode *newNode = new LinkedNode();
    (*newNode).index = new_cb_index;
    (*newNode).next = NULL;

    if (_length <= 0) {
        _head = newNode;
        _tail = _head;
    } else {
        (*_tail).next = newNode;
        _tail = (*_tail).next;
    }

    _length += 1;
}

void LinkedList::remove(int index) {
    if (_length <= index) {
        printf("Out of list size: %d\n", index);
    } else if (index == 0){
        _head = (*_head).next;
    } else {
        LinkedNode *temp = _head;
        for (int i = 0; i < index - 1; i++) {
            temp = (*temp).next;
        }

        if ((*temp).next == NULL) {
            delete [] temp;
            _head = NULL;
            _tail = NULL;
        } else if ((*(*temp).next).next != NULL) {
            LinkedNode *del_node = (*temp).next;
            (*temp).next = (*(*temp).next).next;
            delete [] del_node;
        } else {
            delete [] (*temp).next;
            (*temp).next = NULL;
            _tail = temp;
        }
    }

    _length -= 1;
}

CheckerboardIndex LinkedList::get(int index) {
    if (_length <= index) {
        printf("Out of list size: %d\n", index);
        exit(1);
    } else {
        LinkedNode *temp = _head;
        for (int i = 0; i < index; i++) {
            temp = (*temp).next;
        }

        return (*temp).index;
    }
}

bool LinkedList::isEmpty() {
    if (_length < 1) {
        return true;
    }

    return false;
}

void LinkedList::clear() {
    if (_length > 0) {
        LinkedNode *temp = _head;
        LinkedNode *del_node = temp;
        for (int idx = 0; idx < _length; idx++) {
            if (idx < _length - 1) {
                temp = (*temp).next;
            }
            delete [] del_node;
            del_node = temp;
        }

        _head = NULL;
        _tail = NULL;
        _length = 0;
    }
}