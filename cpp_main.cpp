//
// Created by chen weibin on 16/9/14.
//
#include <iostream>
#include <memory>
#include <stdint.h>
#include <string>
#include <queue>
#include <mutex>
#include <vector>
#include <deque>
#include <cstring>

typedef std::vector<uint8_t> XBuffer;
typedef std::deque<std::shared_ptr<XBuffer>> XBufferQueue;

XBufferQueue queue;

void callback(uint8_t* data, size_t size)
{
    XBuffer* buffer = new XBuffer();
    buffer->resize(size);

    uint8_t* head = &buffer->front();
    memcpy(head, data, size);

    queue.push_back(std::shared_ptr<XBuffer>(buffer));
}


int main(int argc, char **argv) {
    FILE *fp = fopen("/home/chenwb/reverseme.pcm", "rb");
    FILE *fw = fopen("/home/chenwb/reverseme2.pcm", "wb");

    int len; //decode
    do {
        XBuffer buffer = XBuffer();
        buffer.resize(4096);
        len = (int) fread(&buffer.front(), 1, 4096, fp);
        callback(&buffer.front(), buffer.size());
        printf("file read len = %d \n", len);
    }while(len == 4096);

    fclose(fp);

    size_t writer_max = 4099 * 2;//encode
    do {
        std::shared_ptr<XBuffer>& buffer = queue.front();
        size_t min_size = std::min<size_t>(writer_max, buffer->size());
        size_t writed = fwrite(&buffer->front(), 1, min_size, fw);
        if (writed < buffer->size())
        {
            XBuffer* newBuffer = new XBuffer();
            newBuffer->resize(buffer->size() - writed);
            memcpy(&newBuffer->front(), &buffer->front() + writed, newBuffer->size());

            queue.pop_front();
            queue.push_front(std::shared_ptr<XBuffer>(newBuffer));
        }
        else
        {
            queue.pop_front();
        }

    }while(queue.size());

    fclose(fw);
}

//
////    std::queue<std::shared_ptr<std::vector<char>>> queue;
////
////    const char *content = "fdsfjas;jkeeeejjjdfsafjaskfjeiiiiiiiii";
////
////    std::vector<char> *buffer = new std::vector<char>();
////    buffer->insert(buffer->end(), content, content + strlen(content));
////
////    queue.push(std::shared_ptr<std::vector<char>>(buffer));
//
//
//    int len = 0;
//
//    FILE *fp = fopen("/Users/chenweibin/Downloads/test_encode/test2.pcm", "rb");
//    FILE *fw = fopen("/Users/chenweibin/Downloads/test_encode/test3.pcm", "wb");
//    int file_size = fp->_lbfsize;
//    Queue queue = create_queue();
//    int read_max_size = 1024;
//    do {
//        uint8_t *buf = (uint8_t *) malloc(4096);
//        len = (int) fread(buf, 1, (size_t) read_max_size, fp);
//        queue.write_buf(&queue, buf, len);
//        free(buf);
//        printf("file read size = %d , len = %d \n", file_size, len);
//    }while(len >= read_max_size);
//    fclose(fp);
//
//    read_max_size = 1028;
//    do {
////        usleep(1500);
//        uint8_t *buf = (uint8_t *) malloc(4096);
//        len = queue.read_buf(&queue, buf, read_max_size);
//        printf("read_buf = %d , len = %d \n", file_size, len);
//        fwrite(buf, 1, (size_t) len, fw);
//        free(buf);
//    }while(len >= read_max_size);
//
//    queue.destroy_queue(&queue);
//
//    fclose(fw);
//}