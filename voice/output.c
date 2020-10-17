#include "../common/common.c"



void vcSendAll(int *sockets, size_t connections, struct VoiceBlock vb) {
  size_t i;
  for (i = 0; i < connections; i++) {
    send(sockets[i], vb.data, vb.size, MSG_CONFIRM);
    send(sockets[i], ENDVC, sizeof(ENDVC), MSG_CONFIRM);
  }
}