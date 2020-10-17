#include "../common/common.c"

struct VcInfo {
    int socket;
    struct VoiceBlock *vb;
};

int recvOneBlock(int socketId, struct VoiceBlock *vb) {
    char *buf = malloc(BLOCKSIZ);
    size_t i = 0;
    size_t vbsize = BLOCKSIZ;

    while (listening) {
        read(socketId, buf + i, 1);
        if ((i >= sizeof(ENDVC) -1)
            && (strcmp(buf + i - sizeof(ENDVC) + 1, ENDVC) == 0)) {
                buf = realloc(buf, i + 2);
                break;
            }
        }
        i++;
        if (i < vbsize) continue;
            
        vbsize += BLOCKSIZ;

        char *tmp = realloc(buf, vbsize);
        
        if (!tmp) {
            logError("Error, tried to realloc %sz for socket %d.", vbsize, socketId);
            free(buf);
            return ERROR;
        }
        buf = tmp;
    }

    *vb = {
        .data = buf,
        .size = i
    };

    return 0;
}

void playOnceBlock(struct VoiceBlock vb) {
    ;/*play a voice block*/
}

void vcRecvPlay(int socketId) {
    /* recieve blocks of voice? how tf does that work
     * play the block, discard then recieve then go back
     */
    struct VoiceBlock vb;

    while (listening) {
        if (recvOneBlock(socketId, &vb) == ERROR)
            break;
        playOneBlock(vb);
    }

}

void vcRecvAll(int **sockets, size_t *connections) {
    size_t i;
    pthread_t threads[MAXCONN];

    while (listening) {

        if (i < *connections) {
            pthread_create(&threads[i], (void*)0, vcRecvPlay, (*sockets)[i]);
        }
    }

    for (; i; i--) {
        pthread_join(threads[i], (void*)0);
    }
}