/*
* code from teacher
* compile with the mbr.c
*/

#include <sys/stat.h>

// #include <sys/ioctl.h>

#include <linux/hdreg.h>

#include <fcntl.h>

#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <sys/types.h>

#include "/root/Desktop/ext2utils/superblock/test5.h"





struct hd_geometry geometry;

short CurrentGroup;

short BlocksRead;







void getMetaData( int fd ) {



printMBR( fd );



}





main()

{

super_block_t *data_blk;

ext2_group_desc_t grp_desc[25][9000];

super_block_t *super[25];

long superblks[50];

FILE *out;

FILE *hd;

int fd;

char *s;

int i;

int j;

long count = 0;

long block_grp = 0;

long blk = 0;

char filename[25];

long numOfGrps;



fd = open("/dev/sdb1", O_RDONLY);

if ( fd <= 0 )

{

fprintf(stderr, "File not opened = %x\n", hd );

return;

}



getMetaData( fd );



close (fd );



}
