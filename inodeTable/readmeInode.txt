/******************************************
* 听课笔记
******************************************/
main site:  http://www.utdallas.edu/~nkg140130/utdOpenSource.htm

project: the reopen of a destroyed files. (from USB)
1. github volunteer 1
2. opensource website
3. connection with teacher
4. tutorial document


The Second Extended File System   http://nongnu.org/ext2-doc/ext2.html 


/*****************************************
* terminal指令
******************************************/
apt-get source coreutils

uname    显示操作系统信息
dmesg    显示系统启动信息
du       显示指定的文件（目录）已使用的磁盘空间
df       显示文件系统磁盘空间的使用情况
free     显示当前内存和交换空间的使用情况
fdisk -l 显示磁盘信息


(eclipse)  ctrl+b  完整编译
gcc inode.c -o inode
sudo ./inode /dev/sda6

df -hT    //查到是ext4系统！


/*****************************************
* c语言
******************************************/
read( fd, buf, sizeof (struct ext3_super_block ) )
//从文件fd中读取sizeof(struct )个字节放到buf指针指向的内存中。

//struct ext3_super_block *sb;  不会分配地址？得sb然后&sb

函数原形: long lseek(int handle, long offset, int fromwhere)
函数功能: 移动文件位置指针到指定位置
参数描述: handle 文件句柄，offset 文件位置   
        fromwhere 从文件何处开始移动，该参数可使用以下宏定义： 
              SEEK_CUR  1  从当前位置计算offset
              SEEK_END  2  从文件结束位置计算offset，此时offset为负数。                        
              SEEK_SET  0  从文件开始位置计算offset


/******************************************
* 背景知识
******************************************/
ext2文件系统是非日志文件系统
在ext2文件系统中，文件由inode（包含有文件的所有信息）进行唯一标识。一个文件可能对应多个文件名，只有在所有文件名都被删除后，该文件才会被删除。此外，同一文件在磁盘中存放和被打开时所对应的inode是不同的，并由内核负责同步。
ext2文件系统采用三级间接块来存储数据块指针，并以块（block，默认为1KB）为单位分配空间。
在ext2系统中，所有元数据结构的大小均基于“块”，而不是“扇区”。块的大小随文件系统的大小而有所不同。而一定数量的块又组成一个块组，每个块组的起始部分有多种多样的描述该块组各种属性的元数据结构。ext2系统中对各个结构的定义都包含在原始码的include/linux/ext2_fs.h文件中。

1、超级块 superblock
每个ext2文件系统都必须包含一个超级块，其中存储了该文件系统的大量基本信息，包括块的大小、每块组中包含的块数等。超级块的起始位置为其所在分区的第1024个字节，占用1KB的空间，
The primary copy of the superblock is stored at an offset of 1024 bytes from the start of the device. This is block 1 for a 1KiB block formatted volume or within block 0 for larger block sizes. (4KB的block size，boot sector和superblock共用block 0)

2、块组描述符 group descriptors (n)
一个块组描述符用以描述一个块组的属性。块组描述符组由若干块组描述符组成，描述了文件系统中所有块组的属性，存放于超级块所在块的下一个块中。

3、块位图和inode位图    data block bitmap & inode bitmap
块位图和inode位图的每一位分别指出块组中对应的那个块或inode是否被使用。

4、inode表  inode table (n)
inode表用于跟踪定位每个文件，包括位置、大小等（但不包括文件名），一个块组只有一个inode表。

5、数据块   data blocks
数据块中存放文件的内容，包括目录表、扩展属性、符号链接等。

目录结构
在ext2文件系统中，目录是作为文件存储的。根目录总是在inode表的第二项，而其子目录则在根目录文件的内容中定义。目录项在include/linux/ext2_fs.h文件中定义，其结构如下：
struct ext2_dir_entry_2 {
__le32 inode; // 文件入口的inode号，0表示该项未使用
__le16 rec_len; // 目录项长度
__u8 name_len; // 文件名包含的字符数
__u8 file_type; // 文件类型
char name[255]; // 文件名
};

Every file in the EXT2 file system is described by a single inode and each inode has a single unique number identifying it.

To read an EXT2 inode we must look for it in the inode table of the appropriate Block Group. If, for example, the root inode number is 42, then we need the 42nd inode from the inode table of Block Group 0.
————【 http://tldp.org/LDP/tlk/fs/filesystem.html 】


//assume we have the inode number of the file
So I calculate (inodenr-1)/(inodes per group)=32 -> so the group nr for inode /usr/ is 32


EXT3:
最大分区：
    因为定义的是无符号32位数，所以可能定位的block范围为2^32，也就是4G，如果一个block大小为4KB，所以为4G * 4KB = 16TB
最大文件：
    前面直接指向12个数据块，一级间接块最大为block size / 4，block size就是数据块的大小，因为一个索引是4个字节，所以除以4，这样计算下来，最大的文件可以使用的总块数为:12 + (block size/4) + (block size/4)^2 + (block size/4)^3，如果block size大小为4K，则为(12 + 2^10 + 2^20 + 2^30) * 2^12 约等于4T。








---------------2/2/15--------------------------
Intern
Linux, interested
send resume to Gupta

partition type
networking project

file type, delete by mistake (1. Inode is still there, file value destroy, detect, 2. file is still there, scan the address blocks)

