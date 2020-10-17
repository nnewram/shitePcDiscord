void vcsendall(int *sockets, size_t connections, char *voiceBlock, size_t voiceBlockSize) {
  size_t i;
  for (i = 0; i < connections; i++)
    send(sockets[i], voiceBlock, voiceBlockSize, MSG_CONFIRM);
}