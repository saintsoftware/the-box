
// ========== INCLUDES =================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "../include/asoundlib.h"

// ========== DECLARATION =================

int audio_rate;
int audio_format;
int audio_channels;
int audio_bits;
int audio_sample_size;
int audio_total_bytes;

qboolean      audio;
audioFormat_t a;
int audio_num_frames;

char audio_id[4];
uint32_t audio_size;


audio_timer_id_class_id;
snd_timer_id_get_sclass(id),
snd_timer_id_get_card(id),
snd_timer_id_get_device(id),
snd_timer_id_get_subdevice(id));

//int i;
int audio_error;
int audio_thru=0;
int audio_verbose = 0;
char *audio_device_in = NULL;
char *audio_device_out = NULL;
char *audio_node_in = NULL;
char *audio_node_out = NULL;

typedef struct _wavheader {
	int16_t	format;
	int16_t	nchannels;
	int32_t	framerate;
	int32_t	byterate;
	int16_t	blocksize;
	int16_t	bitdepth;
} wavheader_t;

typedef struct _extdouble {
	int16_t		expon;
	uint32_t	himant;
	uint32_t	lomant;
} __attribute__((__packed__)) extdouble_t;

typedef struct _aifheader {
	int16_t		nchannels;
	int32_t		nframes;
	int16_t		bitdepth;
	extdouble_t	framerate;
	char		comptype[4];
} __attribute__((__packed__)) aifheader_t;

typedef struct _sunheader {
	uint32_t	size;
	int32_t		encoding;
	int32_t		framerate;
	int32_t		nchannels;
} __attribute__((__packed__)) sunheader_t;

typedef struct _wav_info {
	int	nchannels;
	int	nframes;
	int	sampwidth;
	int	framerate;
	int	devformat;
} wav_info_t;


void show_status(void *handle){
        int err;
        snd_timer_status_t *status;
        
        snd_timer_status_alloca(&status);
        if ((err = snd_timer_status(handle, status)) < 0) {
                fprintf(stderr, "timer status %i (%s)\n", err, snd_strerror(err));
                return;
        }
        printf("STATUS:\n");
        printf("  resolution = %li\n", snd_timer_status_get_resolution(status));
        printf("  lost = %li\n", snd_timer_status_get_lost(status));
        printf("  overrun = %li\n", snd_timer_status_get_overrun(status));
        printf("  queue = %li\n", snd_timer_status_get_queue(status));
}

void read_loop(void *handle, int master_ticks, int timeout){
	
        int count, err;
        struct pollfd *fds;
        snd_timer_read_t tr;
        
        count = snd_timer_poll_descriptors_count(handle);
        fds = calloc(count, sizeof(struct pollfd));
        if (fds == NULL) {
                fprintf(stderr, "malloc error\n");
                exit(EXIT_FAILURE);
        }
        while (master_ticks-- > 0) {
                if ((err = snd_timer_poll_descriptors(handle, fds, count)) < 0) {
                        fprintf(stderr, "snd_timer_poll_descriptors error: %s\n", snd_strerror(err));
                        exit(EXIT_FAILURE);
                }
                if ((err = poll(fds, count, timeout)) < 0) {
                        fprintf(stderr, "poll error %i (%s)\n", err, strerror(err));
                        exit(EXIT_FAILURE);
                }
                if (err == 0) {
                        fprintf(stderr, "timer time out!!\n");
                        exit(EXIT_FAILURE);
                }
                while (snd_timer_read(handle, &tr, sizeof(tr)) == sizeof(tr)) {
                        printf("TIMER: resolution = %uns, ticks = %u\n",
                                tr.resolution, tr.ticks);
                }
        }
        free(fds);
}
static void async_callback(snd_async_handler_t *ahandler)
{
        snd_timer_t *handle = snd_async_handler_get_timer(ahandler);
        int *acount = snd_async_handler_get_callback_private(ahandler);
        snd_timer_read_t tr;
        
        while (snd_timer_read(handle, &tr, sizeof(tr)) == sizeof(tr)) {
                printf("TIMER: resolution = %uns, ticks = %u\n",
                        tr.resolution, tr.ticks);
        }
        (*acount)++;
}
int main(int argc, char *argv[])
{
        int idx, err;
        int class = SND_TIMER_CLASS_GLOBAL;
        int sclass = SND_TIMER_CLASS_NONE;
        int card = 0;
        int device = SND_TIMER_GLOBAL_SYSTEM;
        int subdevice = 0;
        int list = 0;
        int async = 0;
        int acount = 0;
        snd_timer_t *handle;
        snd_timer_id_t *id;
        snd_timer_info_t *info;
        snd_timer_params_t *params;
        char timername[64];
        snd_async_handler_t *ahandler;
        snd_timer_id_alloca(&id);
        snd_timer_info_alloca(&info);
        snd_timer_params_alloca(&params);
        idx = 1;
        while (idx < argc) {
                if (!strncmp(argv[idx], "class=", 5)) {
                        class = atoi(argv[idx]+6);
                } else if (!strncmp(argv[idx], "sclass=", 6)) {
                        sclass = atoi(argv[idx]+7);
                } else if (!strncmp(argv[idx], "card=", 5)) {
                        card = atoi(argv[idx]+5);
                } else if (!strncmp(argv[idx], "device=", 7)) {
                        device = atoi(argv[idx]+7);
                } else if (!strncmp(argv[idx], "subdevice=", 10)) {
                        subdevice = atoi(argv[idx]+10);
                } else if (!strcmp(argv[idx], "list")) {
                        list = 1;
                } else if (!strcmp(argv[idx], "async")) {
                        async = 1;
                }
                idx++;
        }
        if (class == SND_TIMER_CLASS_SLAVE && sclass == SND_TIMER_SCLASS_NONE) {
                fprintf(stderr, "slave class is not set\n");
                exit(EXIT_FAILURE);
        }
        if (list) {
                snd_timer_query_t *qhandle;
                if ((err = snd_timer_query_open(&qhandle, "hw", 0)) < 0) {
                        fprintf(stderr, "snd_timer_query_open error: %s\n", snd_strerror(err));
                        exit(EXIT_FAILURE);
                }
                snd_timer_id_set_class(id, SND_TIMER_CLASS_NONE);
                while (1) {
                        if ((err = snd_timer_query_next_device(qhandle, id)) < 0) {
                                fprintf(stderr, "timer next device error: %s\n", snd_strerror(err));
                                break;
                        }
                        if (snd_timer_id_get_class(id) < 0)
                                break;
                        printf("Timer device: class %i, sclass %i, card %i, device %i, subdevice %i\n",
                                        snd_timer_id_get_class(id),
                                        snd_timer_id_get_sclass(id),
                                        snd_timer_id_get_card(id),
                                        snd_timer_id_get_device(id),
                                        snd_timer_id_get_subdevice(id));
                }
                snd_timer_query_close(qhandle);
                exit(EXIT_SUCCESS);
        }
        sprintf(timername, "hw:CLASS=%i,SCLASS=%i,CARD=%i,DEV=%i,SUBDEV=%i", class, sclass, card, device, subdevice);
        if ((err = snd_timer_open(&handle, timername, SND_TIMER_OPEN_NONBLOCK))<0) {
                fprintf(stderr, "timer open %i (%s)\n", err, snd_strerror(err));
                exit(EXIT_FAILURE);
        }
        printf("Using timer class %i, slave class %i, card %i, device %i, subdevice %i\n", class, sclass, card, device, subdevice);
        if ((err = snd_timer_info(handle, info)) < 0) {
                fprintf(stderr, "timer info %i (%s)\n", err, snd_strerror(err));
                exit(0);
        }
        printf("Timer info:\n");
        printf("  slave = %s\n", snd_timer_info_is_slave(info) ? "yes" : "no");
        printf("  card = %i\n", snd_timer_info_get_card(info));
        printf("  id = '%s'\n", snd_timer_info_get_id(info));
        printf("  name = '%s'\n", snd_timer_info_get_name(info));
        printf("  average resolution = %li\n", snd_timer_info_get_resolution(info));
        snd_timer_params_set_auto_start(params, 1);
        if (!snd_timer_info_is_slave(info)) {
                snd_timer_params_set_ticks(params, (1000000000 / snd_timer_info_get_resolution(info)) / 50); /* 50Hz */
                if (snd_timer_params_get_ticks(params) < 1)
                        snd_timer_params_set_ticks(params, 1);
                printf("Using %li tick(s)\n", snd_timer_params_get_ticks(params));
        } else {
                snd_timer_params_set_ticks(params, 1);
        }
        if ((err = snd_timer_params(handle, params)) < 0) {
                fprintf(stderr, "timer params %i (%s)\n", err, snd_strerror(err));
                exit(0);
        }
        show_status(handle);
        if (async) {
                err = snd_async_add_timer_handler(&ahandler, handle, async_callback, &acount);
                if (err < 0) {
                        fprintf(stderr, "unable to add async handler %i (%s)\n", err, snd_strerror(err));
                        exit(EXIT_FAILURE);
                }
        }
        if ((err = snd_timer_start(handle)) < 0) {
                fprintf(stderr, "timer start %i (%s)\n", err, snd_strerror(err));
                exit(EXIT_FAILURE);
        }
        if (async) {
                /* because all other work is done in the signal handler,
                   suspend the process */
                while (acount < 25)
                        sleep(1);
                snd_timer_stop(handle);
        } else {
                read_loop(handle, 25, snd_timer_info_is_slave(info) ? 10000 : 25);
        }
        show_status(handle);
        snd_timer_close(handle);
        printf("Done\n");
        return EXIT_SUCCESS;
}

// Links : http://www.portaudio.com/download.html

/*
MP3

#include <conio.h>
#include "inc/fmod.h"

FSOUND_SAMPLE* handle;

int main ()
{
   // init FMOD sound system
   FSOUND_Init (44100, 32, 0);

   // load and play mp3
   handle=FSOUND_Sample_Load (0,"my.mp3",0, 0, 0);
   FSOUND_PlaySound (0,handle);

   // wait until the users hits a key to end the app
   while (!_kbhit())
   {
   }

   // clean up
   FSOUND_Sample_Free (handle);
   FSOUND_Close();
}

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/asoundlib.h"
#include <signal.h>
static void usage(void)
{
        fprintf(stderr, "usage: rawmidi [options]\n");
        fprintf(stderr, "  options:\n");
        fprintf(stderr, "    -v: verbose mode\n");
        fprintf(stderr, "    -i device-id : test ALSA input device\n");
        fprintf(stderr, "    -o device-id : test ALSA output device\n");
        fprintf(stderr, "    -I node      : test input node\n");
        fprintf(stderr, "    -O node      : test output node\n");
        fprintf(stderr, "    -t: test midi thru\n");
        fprintf(stderr, "  example:\n");
        fprintf(stderr, "    rawmidi -i hw:0,0 -O /dev/midi1\n");
        fprintf(stderr, "    tests input for card 0, device 0, using snd_rawmidi API\n");
        fprintf(stderr, "    and /dev/midi1 using file descriptors\n");
}
int stop=0;
void sighandler(int dum)
{
        stop=1;
}
int main(int argc,char** argv)
{
        int i;
        int err;
        int thru=0;
        int verbose = 0;
        char *device_in = NULL;
        char *device_out = NULL;
        char *node_in = NULL;
        char *node_out = NULL;
        
        int fd_in = -1,fd_out = -1;
        snd_rawmidi_t *handle_in = 0,*handle_out = 0;
        
        if (argc==1) {
                usage();
                exit(0);
        }
        
        for (i = 1 ; i<argc ; i++) {
                if (argv[i][0]=='-') {
                        switch (argv[i][1]) {
                                case 'h':
                                        usage();
                                        break;
                                case 'v':
                                        verbose = 1;
                                        break;
                                case 't':
                                        thru = 1;
                                        break;
                                case 'i':
                                        if (i + 1 < argc)
                                                device_in = argv[++i];
                                        break;
                                case 'I':
                                        if (i + 1 < argc)
                                                node_in = argv[++i];
                                        break;
                                case 'o':
                                        if (i + 1 < argc)
                                                device_out = argv[++i];
                                        break;
                                case 'O':
                                        if (i + 1 < argc)
                                                node_out = argv[++i];
                                        break;
                        }                       
                }
        }
        if (verbose) {
                fprintf(stderr,"Using: \n");
                fprintf(stderr,"Input: ");
                if (device_in) {
                        fprintf(stderr,"device %s\n",device_in);
                }else if (node_in){
                        fprintf(stderr,"%s\n",node_in); 
                }else{
                        fprintf(stderr,"NONE\n");
                }
                fprintf(stderr,"Output: ");
                if (device_out) {
                        fprintf(stderr,"device %s\n",device_out);
                }else if (node_out){
                        fprintf(stderr,"%s\n",node_out);                
                }else{
                        fprintf(stderr,"NONE\n");
                }
        }
        
        if (device_in) {
                err = snd_rawmidi_open(&handle_in,NULL,device_in,0);    
                if (err) {
                        fprintf(stderr,"snd_rawmidi_open %s failed: %d\n",device_in,err);
                }
        }
        if (node_in && (!node_out || strcmp(node_out,node_in))) {
                fd_in = open(node_in,O_RDONLY);
                if (fd_in<0) {
                        fprintf(stderr,"open %s for input failed\n",node_in);
                }       
        }
        signal(SIGINT,sighandler);
        if (device_out) {
                err = snd_rawmidi_open(NULL,&handle_out,device_out,0);
                if (err) {
                        fprintf(stderr,"snd_rawmidi_open %s failed: %d\n",device_out,err);
                }
        }
        if (node_out && (!node_in || strcmp(node_out,node_in))) {
                fd_out = open(node_out,O_WRONLY);               
                if (fd_out<0) {
                        fprintf(stderr,"open %s for output failed\n",node_out);
                }       
        }
        if (node_in && node_out && strcmp(node_out,node_in)==0) {
                fd_in = fd_out = open(node_out,O_RDWR);         
                if (fd_out<0) {
                        fprintf(stderr,"open %s for input and output failed\n",node_out);
                }               
        }
        if (!thru) {
                if (handle_in || fd_in!=-1) {
                        fprintf(stderr,"Read midi in\n");
                        fprintf(stderr,"Press ctrl-c to stop\n");
                }
                if (handle_in) {
                        unsigned char ch;
                        while (!stop) {
                                snd_rawmidi_read(handle_in,&ch,1);
                                if (verbose) {
                                        fprintf(stderr,"read %02x\n",ch);
                                }
                        }
                }
                if (fd_in!=-1) {
                        unsigned char ch;
                        while (!stop) {
                                read(fd_in,&ch,1);
                                if (verbose) {
                                        fprintf(stderr,"read %02x\n",ch);
                                }
                        }       
                }
                if (handle_out || fd_out!=-1) {
                        fprintf(stderr,"Writing note on / note off\n");
                }
                if (handle_out) {
                        unsigned char ch;
                        ch=0x90; snd_rawmidi_write(handle_out,&ch,1);
                        ch=60;   snd_rawmidi_write(handle_out,&ch,1);
                        ch=100;  snd_rawmidi_write(handle_out,&ch,1);
                        snd_rawmidi_drain(handle_out);
                        sleep(1);
                        ch=0x90; snd_rawmidi_write(handle_out,&ch,1);
                        ch=60;   snd_rawmidi_write(handle_out,&ch,1);
                        ch=0;    snd_rawmidi_write(handle_out,&ch,1);
                        snd_rawmidi_drain(handle_out); 
                }
                if (fd_out!=-1) {
                        unsigned char ch;
                        ch=0x90; write(fd_out,&ch,1);
                        ch=60;   write(fd_out,&ch,1);
                        ch=100;  write(fd_out,&ch,1);
                        sleep(1);
                        ch=0x90; write(fd_out,&ch,1);
                        ch=60;   write(fd_out,&ch,1);
                        ch=0;    write(fd_out,&ch,1);
                }
        } else {
                if ((handle_in || fd_in!=-1) && (handle_out || fd_out!=-1)) {
                        if (verbose) {
                                fprintf(stderr,"Testing midi thru in\n");
                        }
                        while (!stop) {
                                unsigned char ch;
                        
                                if (handle_in) {
                                        snd_rawmidi_read(handle_in,&ch,1);
                                }
                                if (fd_in!=-1) {
                                        read(fd_in,&ch,1);
                                }       
                                if (verbose) {
                                        fprintf(stderr,"thru: %02x\n",ch);
                                }
                                if (handle_out) {
                                        snd_rawmidi_write(handle_out,&ch,1);
                                        snd_rawmidi_drain(handle_out); 
                                }
                                if (fd_out!=-1) {
                                        write(fd_out,&ch,1);
                                }
                        }
                }else{
                                fprintf(stderr,"Testing midi thru needs both input and output\n");              
                                exit(-1);
                }
        }
        if (verbose) {
                fprintf(stderr,"Closing\n");
        }
        
        if (handle_in) {
                snd_rawmidi_drain(handle_in); 
                snd_rawmidi_close(handle_in);   
        }
        if (handle_out) {
                snd_rawmidi_drain(handle_out); 
                snd_rawmidi_close(handle_out);  
        }
        if (fd_in!=-1) {
                close(fd_in);
        }
        if (fd_out!=-1) {
                close(fd_out);
        }
        return 0;
}
