/*==================================================================
 *   FileName: inode.c
 *     Author: Zebin Xie
 *      Email: zebin.xie@gmail.com
 *     Readme: This version only read and print the first inode table.
 *     			Still have some doubts about the location method.
 *     			Please contact me if I write something wrong.
 * LastChange: 2014-11-01 morning
 *==================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "linux/ext3_fs.h"

#define BOOT_SECTOR_OFFSET 1024


int main( int argc, char** argv )
{

	int fd;

    if ( argc == 1)
    {
        printf("Enter disk name as command line argument. e.g - sudo ./inode /dev/sda1\n");
        return -1;
    }
	char* dev = argv[1];					//"/dev/sda1";

	if((fd=open( dev , O_RDONLY))==-1) {
		printf("Can't open.\n");
		return -1;
	}


	/*****************************************
	 * reading the superblock.
	 * we need to find the s_log_block_size
	 * ***************************************/
	struct ext3_super_block sb;			//not * here

    if ( ( lseek( fd, BOOT_SECTOR_OFFSET, SEEK_SET ) ) == -1 )    //128*1024*1024 is same
    {
        printf( "lseek error\n" );
        return -1;
    }
    if ( ( read( fd, &sb, sizeof (struct ext3_super_block ) ) ) == -1 )
    {
        printf( "read error\n" );
        return -1;
    }
    int blockSize = 1024<<sb.s_log_block_size;			//4KB
	printf( "s_log_block_size = %uByte\n", blockSize );
    int inodeSize= sb.s_inode_size;				//inode size is 256
	printf( "s_inode_size = %uByte\n", inodeSize );
	//int i_bnum_g= sb.s_inodes_per_group/(blockSize/inodeSize); 	//inode table occupy 512 blocks per group



	/*****************************************
	 * reading the groupDescriptor.
	 * we need to find the bg_inode_table
	 * ***************************************/
	struct ext3_group_desc gd;

	//1.不重新定位是不行的，因为上面读完不一定会指向结尾。2.对于4KiB，group discripter 是第一个block (就是boot secter和super block结合为一个block了)
    if ( ( lseek( fd, blockSize, SEEK_SET ) ) == -1 )		//not 1024+blockSize doubt?
    {
        printf( "lseek error\n" );
        return -1;
    }
    if ( ( read( fd, &gd, sizeof (struct ext3_group_desc ) ) ) == -1 )
    {
        printf( "read error\n" );
        return -1;
    }
    printf("bg_block_bitmap = %u\n", gd.bg_block_bitmap);
    printf("bg_inode_bitmap = %u\n", gd.bg_inode_bitmap);
    printf("bg_inode_table = %u\n", gd.bg_inode_table);		 //why +16 not +1?

    printf("bg_free_blocks_count= %u\n", gd.bg_free_blocks_count);
    printf("bg_free_inodes_count= %u\n", gd.bg_free_inodes_count);
    printf("bg_used_dirs_count= %u\n", gd.bg_used_dirs_count);
    printf("bg_pad= %u\n", gd.bg_pad);


	/*****************************************
	 * reading the inode table.
	 * ***************************************/
	struct ext3_inode inode;

    if ( ( lseek( fd, blockSize*(gd.bg_inode_table)+1, SEEK_SET ) ) == -1 )	//not quite sure here?  block number begin from 0 or 1?   
	//block ID increased by 16, so? Problem of 64bit System?
    {
        printf( "lseek error\n" );
        return -1;
    }
    if ( ( read( fd, &inode, sizeof (struct ext3_inode ) ) ) == -1 )
    {
        printf( "read error\n" );
        return -1;
    }

    printf("i_mode = %hu\n", inode.i_mode);
    printf("i_uid = %hu\n", inode.i_uid);
    printf("i_size = %u\n",inode.i_size);
    printf("i_atime = %u\n",inode.i_atime);
    printf("i_ctime = %u\n",inode.i_ctime);
    printf("i_mtime = %u\n",inode.i_mtime);
    printf("i_dtime = %u\n",inode.i_dtime);
    printf("i_gid = %hu\n",inode.i_gid);
    printf("i_links_count = %hu\n",inode.i_links_count);
    printf("i_blocks = %u\n",inode.i_blocks);
    printf("i_flags = %u\n",inode.i_flags);

    printf("i_generation = %u\n",inode.i_generation);
    printf("i_file_acl = %u\n",inode.i_file_acl);
    printf("i_dir_acl = %u\n",inode.i_dir_acl);
    printf("i_faddr = %u\n",inode.i_faddr);
    printf("i_extra_isize = %hu\n",inode.i_extra_isize);
    printf("i_pad1 = %hu\n",inode.i_pad1);


    printf( "read complete.\n" );

	close( fd );
	return 0;

}
