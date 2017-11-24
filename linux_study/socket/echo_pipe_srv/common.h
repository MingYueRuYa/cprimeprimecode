#ifndef common_h
#define common_h

#define ERR_EXIT(msg)   \
    do  \
    {   \
        perror(msg);    \
        exit(EXIT_FAILURE);  \
    } while (0)

typedef struct packet {
    int len;
    char buff[1024];
} packet;

#endif //common_h
