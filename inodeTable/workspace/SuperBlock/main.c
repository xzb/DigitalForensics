/* 
 * File:   main.c
 * Author: Akshay Hacholli
 *
 * Created on October 01, 2014, 11:09 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "linux/ext3_fs.h"      

#define BOOT_SECTOR_OFFSET 1024

int read_superblock( int fd, struct ext3_super_block *sb );
void print_superblock( struct ext3_super_block *sb );

/*
 * 
 */
int main( int argc, char** argv )
{
    int fd;
    struct ext3_super_block sb;
    
    if ( argc == 1)
    {
        printf("Enter disk name as command line argument. e.g - sudo ./a.out \"/dev/sdb1\"\n");
        return -1;
    }

    if ( ( fd = open( argv[1], O_RDWR ) ) == -1 )
    {
        printf( "Could not open the filesystem %s", argv[1] );
        return -1;
    }

    printf( "%d\n", fd );
    printf( "Reading superblock\n" );
    int ret = read_superblock( fd, &sb );

    if ( close( fd ) == -1 )
    {
        printf( "close_fs error" );
        return -1;
    }

    return (EXIT_SUCCESS );
}

int read_superblock( int fd, struct ext3_super_block *sb )
{

    if ( ( lseek( fd, BOOT_SECTOR_OFFSET, SEEK_SET ) ) == -1 )
    {
        printf( "ext3Viewer error - lseek superblock error\n" );
        return -1;
    }

    if ( ( read( fd, sb, sizeof (struct ext3_super_block ) ) ) == -1 )
    {
        printf( "ext3Viewer error - superblock read error" );
        return -1;
    }
    printf( "Reading Complete\n" );

    print_superblock( sb );
    return 0;
}

void print_superblock( struct ext3_super_block *sb )
{
    printf( "\n" );
    printf( "\t\t\t\tSUPER BLOCK Information at 1024\n" );
    printf( "\n" );
    printf( "Total inode count    = %u\n", sb->s_inodes_count );
    printf( "Block count    = %u\n", sb->s_blocks_count );
    printf( "Reserved block count  = %u\n", sb->s_r_blocks_count );
    printf( "Free block count = %u\n", sb->s_free_blocks_count );
    printf( "Free inode count = %u\n", sb->s_free_inodes_count );
    printf( "First data block = %u\n", sb->s_first_data_block );
    printf( "Block size = 1024 * 2^%u octets\n", sb->s_log_block_size );
    printf( "Fragment size =%u\n", sb->s_log_frag_size );
    printf( "Blocks per group count =%u\n", sb->s_blocks_per_group );
    printf( "Fragments per group count =%u\n", sb->s_frags_per_group );
    printf( "Inode per group count =%u\n", sb->s_inodes_per_group );
    printf( "\n" );

    printf( "Last mounting operation timestamp =%u\n", sb->s_mtime );
    printf( "Last writing operation timestamp =%u\n", sb->s_wtime );
    printf( "Counter (times mounted)=%hu\n", sb->s_mnt_count );
    printf( "Authorized mount count before integrity checking =%hu\n", sb->s_max_mnt_count );
    printf( "Magic Number =%#.4hx\n", sb->s_magic );
    printf( "Status flag =%hx\n", sb->s_state );
    printf( "Behaviour when detecting errors =%hu\n", sb->s_errors );
    printf( "Minimum compatible revision level (version)=%hu\n", sb->s_minor_rev_level );
    printf( "Last check timestamp =%u\n", sb->s_lastcheck );
    printf( "Maximum interval between checks = %u secondes\n", sb->s_checkinterval );
    printf( "Creator OS =%u\n", sb->s_creator_os );
    printf( "Current revision level (version)=%u\n", sb->s_rev_level );

    printf( "%s", "\n" );

    printf( "Default UID for reserved blocks =%hu\n", sb->s_def_resuid );
    printf( "Default GID for reserved blocks =%hu\n", sb->s_def_resgid );
    printf( "First non-reserved inode number =%u\n", sb->s_first_ino );
    printf( "Inode size = %hu\n", sb->s_inode_size );
    printf( "Superblock block number (being read)= %hu\n", sb->s_block_group_nr );

    printf( "\n" );

    printf( "Compatible features set = %#.4x\n", sb->s_feature_compat );
    printf( "Incompatible features set = %#.4x\n", sb->s_feature_incompat );
    printf( "Read-Only Compatible features set = %#.4x\n", sb->s_feature_ro_compat );
    printf( "%s", "\n" );

    printf( "Volume name = \"%s\"\n", sb->s_volume_name );
    printf( "Last mounted in directory \"%s\"\n", sb->s_last_mounted );

    printf( "Compression usage bitmap = %u\n", sb->s_algorithm_usage_bitmap );
    printf( "Number of blocks to try to preallocate = %hu\n", sb->s_prealloc_blocks );
    printf( "Number of blocks to preallocate for directories = %hu\n", sb->s_prealloc_dir_blocks );

    printf( "\n" );

    printf( "Journal Inode number = %u\n", sb->s_journal_inum ); /* inode number of journal file */
    printf( "Journal device number = %u\n", sb->s_journal_dev ); /* device number of journal file */
    printf( "Start of list of orphaned inodes to delete = %u\n", sb->s_last_orphan ); /* start of list of inodes to delete */

    printf( "Hash default version = %hd\n", sb->s_def_hash_version );
    printf( "Default mount options = %u\n", sb->s_default_mount_opts );
    printf( "First metablock block group = %u\n", sb->s_first_meta_bg );
}

