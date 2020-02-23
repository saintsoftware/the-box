

// ========== DECLARATION =================

qboolean      fileOpen;
fileHandle_t  f;
char          file_name[ MAX_QPATH ];
int           file_size;

qboolean      motionJpeg;

int           chunkStack[ MAX_RIFF_CHUNKS ];
int           chunkStackTop;

byte          *cBuffer, *eBuffer;