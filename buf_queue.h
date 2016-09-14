////
//// Created by chenwb on 16-9-13.
////
//
//#ifndef TESTCPP_BUF_QUEUE_H
//#define TESTCPP_BUF_QUEUE_H
//
//#include <cstdint>
//#include <cstdio>
//#include <cstring>
//
//#define MIN(a,b) ((a) > (b) ? (b) : (a))
//
//class BufNode {
//public:
//    BufNode(uint8_t *buf, int size) {
//        this->buf = buf;
//        this->buf_size = size;
//    }
//    ~BufNode() {
//        delete next;
//        delete buf;
//    }
//    BufNode * next;
//    uint8_t * buf;
//    int buf_size;
//};
//
//class BufQueue {
//public:
//    BufQueue() {
//        firstNode = new BufNode(NULL, 0);
//        lastNode = firstNode;
//    }
//    ~BufQueue() {
//        while (firstNode) {
//            BufNode *node = firstNode->next;
//            delete firstNode;
//            firstNode = node;
//        }
//    }
//    void add(uint8_t *buf, int size) {
//        if (lastNode) {
//            BufNode *next = new BufNode(buf, size);
//            lastNode->next = next;
//            lastNode = next;
//        }
//    }
//
//    void read(uint8_t *buf, int size) {
//        int start = firstNode->buf_size;
//        BufNode *f_node = firstNode;
//        memcpy(buf, bd->ptr, buf_size);
//        while (start < size && f_node) {
//            start += f_node->next->buf_size;
//        }
//    }
//
//private:
//    BufNode *firstNode;
//    BufNode *lastNode;
//};
//#endif //TESTCPP_BUF_QUEUE_H
