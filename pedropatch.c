#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/string.h>
#include <linux/fs.h>
#include "../drivers/media/video/nexell/nx_vip.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Creates a second device for accessing the nexell camera: \n mknod /dev/camclone c 222 0 \n dd if=/dev/camclone bs=153600 count=1 > img.yuv \n convert -size 320x240 -depth 8 -sampling-factor 4:2:2 -interlace plane img.yuv img.jpg");
MODULE_AUTHOR("olg");

/*
Hexdump of nx_vip_open:

0d c0 a0 e1 f0 dd 2d e9 04 b0 4c e2 0c 30 90 e5  ......-...L..0..
84 a0 9f e5 00 80 a0 e1 24 30 93 e5 34 30 93 e5  ........$0..40..
ff 64 c3 e3 0f 66 c6 e3 aa 3f a0 e3 93 a6 24 e0  .d...f...?....$.
18 50 84 e2 05 00 a0 e1 c9 d6 02 eb 58 70 94 e5  .P..........Xp..
00 00 57 e3 10 00 00 1a 58 30 84 e2 9f 1f 93 e1  ..W.....X0......

01 10 81 e2 91 2f 83 e1 00 00 32 e3 fa ff ff 1a  ...../....2.....
05 00 a0 e1 a4 40 88 e5 eb d6 02 eb 7f 3f 86 e2  .....@.......?..
02 30 83 e2 04 00 a0 e1 03 31 9a e7 10 31 84 e5  .0.......1...1..
c7 ff ff eb 07 00 a0 e1 f0 ad 9d e8 05 00 a0 e1  ................
e1 d6 02 eb 0f 00 e0 e3 f0 ad 9d e8 a8 8d 43 c0  ..............C.
0d c0 a0 e1 30 d8 2d e9 04 b0 4c e2 08 d0 4d e2  ....0.-...L...M.
01 e0 a0 e1 a4 10 90 e5 48 20 9e e5 30 30 a0 e3  ........H ..00..
20 10 9e e9 93 12 22 e0 8c 31 91 e5 18 00 9e e5   ....."..1......
14 10 9e e5 0c 40 65 e0 03 00 54 e1 02 07 80 e3  .....@e...T.....
3c c0 c1 e3 18 00 8e e5 14 c0 8e e5 48 00 9f 85  <...........H...
90 21 92 e5 0c 00 00 8a 0a 30 00 e2 02 00 53     .!.......0....S

xxd -r -ps > z.bin
arm-linux-gnueabi-objdump -b binary -marm -D z.bin

00000000 <.data>:
   0:	e1a0c00d 	mov	ip, sp
   4:	e92dddf0 	push	{r4, r5, r6, r7, r8, sl, fp, ip, lr, pc}
   8:	e24cb004 	sub	fp, ip, #4
   c:	e590300c 	ldr	r3, [r0, #12]
  10:	e59fa084 	ldr	sl, [pc, #132]	; 0x9c
  14:	e1a08000 	mov	r8, r0
  18:	e5933024 	ldr	r3, [r3, #36]	; 0x24
  1c:	e5933034 	ldr	r3, [r3, #52]	; 0x34
  20:	e3c364ff 	bic	r6, r3, #-16777216	; 0xff000000
  24:	e3c6660f 	bic	r6, r6, #15728640	; 0xf00000
  28:	e3a03faa 	mov	r3, #680	; 0x2a8
  2c:	e024a693 	mla	r4, r3, r6, sl
  30:	e2845018 	add	r5, r4, #24
  34:	e1a00005 	mov	r0, r5
  38:	eb02d6c9 	bl	0xb5b64
  3c:	e5947058 	ldr	r7, [r4, #88]	; 0x58
  40:	e3570000 	cmp	r7, #0
  44:	1a000010 	bne	0x8c
  48:	e2843058 	add	r3, r4, #88	; 0x58
  4c:	e1931f9f 	ldrex	r1, [r3]
  50:	e2811001 	add	r1, r1, #1
  54:	e1832f91 	strex	r2, r1, [r3]
  58:	e3320000 	teq	r2, #0
  5c:	1afffffa 	bne	0x4c
  60:	e1a00005 	mov	r0, r5
  64:	e58840a4 	str	r4, [r8, #164]	; 0xa4
  68:	eb02d6eb 	bl	0xb5c1c
  6c:	e2863f7f 	add	r3, r6, #508	; 0x1fc
  70:	e2833002 	add	r3, r3, #2
  74:	e1a00004 	mov	r0, r4
  78:	e79a3103 	ldr	r3, [sl, r3, lsl #2]
  7c:	e5843110 	str	r3, [r4, #272]	; 0x110
  80:	ebffffc7 	bl	0xffffffa4
  84:	e1a00007 	mov	r0, r7
  88:	e89dadf0 	ldm	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
  8c:	e1a00005 	mov	r0, r5
  90:	eb02d6e1 	bl	0xb5c1c
  94:	e3e0000f 	mvn	r0, #15
  98:	e89dadf0 	ldm	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
*********** DATA: pointer to nx_vip:
  9c:	c0438da8 	subgt	r8, r3, r8, lsr #27

PEDROPATCH: found symbol nx_vip_open at 0xc0227808 (size=0xa0, offset= 0x0)
PEDROPATCH: found symbol2 nx_vip_set_active_camera at 0xc0227178 (size=0x28, offset= 0x0)
PEDROPATCH:found  nx_vip1 at 0xc0438da8:
00 00 00 00 6e 78 2d 76 69 70 30 00 00 00 00 00  ....nx-vip0.....
00 00 00 00 24 01 00 00 c0 8d 43 c0 c0 8d 43 c0  ....$.....C...C.
c8 8d 43 c0 c8 8d 43 c0 00 00 00 00 d4 8d 43 c0  ..C...C.......C.
d4 8d 43 c0 dc 8d 43 c0 dc 8d 43 c0 00 00 00 00  ..C...C...C.....
00 00 00 00 ec 8d 43 c0 ec 8d 43 c0 60 47 3e c0  ......C...C.`G>.
00 00 00 00 00 48 8f c7 01 00 00 00 02 00 00 00  .....H..........
58 54 40 c0 00 00 00 00 00 00 00 00 00 00 00 00  XT@.............
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
00 00 00 00 40 01 00 00 f0 00 00 00 f0 ff ff ff  ....@...........
f0 ff ff ff 60 01 00 00 10 01 00 00 00 00 00 00  ....`...........
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00     ...............
PEDROPATCH: loaded
PEDROPATCH: current cam config width:320 height:240 planes:3 format:4
PEDROPATCH: loaded

FORMAT_YCBCR422,
*/

struct nx_vip_config *my_nx_vip;

struct nx_vip_config *get_nx_vip(void)
{

	int (*kallsyms_lookup_size_offset) (unsigned long, unsigned long *,
					    unsigned long *);
	kallsyms_lookup_size_offset =
	    kallsyms_lookup_name("kallsyms_lookup_size_offset");

	char *symb1 = "nx_vip_open";
	char *symb2 = "nx_vip_set_active_camera";
	unsigned long addr1, addr2, symbolsize1, symbolsize2, offset1, offset2;
	struct nx_vip_config *nx_vip1, *nx_vip2;

	addr1 = kallsyms_lookup_name(symb1);
	kallsyms_lookup_size_offset(addr1, &symbolsize1, &offset1);
	printk(KERN_INFO
	       "PEDROPATCH: found symbol %s at 0x%lx (size=0x%lx, offset= 0x%lx)\n",
	       symb1, addr1, symbolsize1, offset1);

	nx_vip1 = *((struct nx_vip_config **)(addr1 + symbolsize1 - 4));

	//printk(KERN_INFO "PEDROPATCH: nx_vip1 at 0x%lx:\n", nx_vip1);
	//print_hex_dump_bytes("", DUMP_PREFIX_NONE, nx_vip1, 0xff);

	addr2 = kallsyms_lookup_name(symb2);
	kallsyms_lookup_size_offset(addr2, &symbolsize2, &offset2);
	printk(KERN_INFO
	       "PEDROPATCH: found symbol2 %s at 0x%lx (size=0x%lx, offset= 0x%lx)\n",
	       symb2, addr2, symbolsize2, offset2);

	nx_vip2 = *((struct nx_vip_config **)(addr2 + symbolsize2 - 4));

	//printk(KERN_INFO "PEDROPATCH: nx_vip2 at 0x%lx:\n", nx_vip2);
	//print_hex_dump_bytes("", DUMP_PREFIX_NONE, nx_vip2, 0xff);

	if (nx_vip1 == nx_vip2) {
		printk(KERN_INFO "PEDROPATCH:found  nx_vip1 at 0x%lx:\n",
		       nx_vip1);
		print_hex_dump_bytes("", DUMP_PREFIX_NONE, nx_vip2, 0xff);

		struct nx_vip_control *ctrl;

		ctrl = &(nx_vip1->ctrl[0]);

		printk(KERN_INFO
		       "PEDROPATCH: current cam config width:%d height:%d planes:%d format:%d\n",
		       ctrl->out_frame.width, ctrl->out_frame.height,
		       ctrl->out_frame.planes, ctrl->out_frame.format);

		//printk(KERN_INFO "PEDROPATCH: &nx_vip->ctrl at 0x%lx:\n", ctrl);
		// print_hex_dump_bytes("", DUMP_PREFIX_NONE, ctrl, sizeof(*ctrl));

		return nx_vip1;
	} else {
		printk(KERN_INFO "PEDROPATCH: could not find nx_vip !\n");
		return 0;
	}

}

ssize_t my_read(struct file * filep, char *buff, size_t count, loff_t * offp)
{
	struct nx_vip_control *ctrl;

	ctrl = &(my_nx_vip->ctrl[0]);
	filep->private_data = ctrl;

	//static ssize_t nx_vip_read(struct file *filp, char *buf, size_t count, loff_t *pos)
	ssize_t(*nx_vip_read) (struct file *, char *, size_t, loff_t *) =
	    kallsyms_lookup_name("nx_vip_read");
	return nx_vip_read(filep, buff, count, offp);
}

ssize_t my_write(struct file * filep, const char *buff, size_t count,
		 loff_t * offp)
{
	return 0;
}

int my_open(struct inode *inode, struct file *filep)
{
	return 0;
}

int my_release(struct inode *inode, struct file *filep)
{
	return 0;
}

int my_ioctl(struct inode *inode,
	     struct file *file,	
	     unsigned int ioctl_num,
	     unsigned long ioctl_param)
{
	return 0;
}

struct file_operations my_fops = {
open:	my_open,
read:	my_read,
write:	my_write,
release:my_release,
ioctl:	my_ioctl,
};

static int __init lkm_init(void)
{
	//insmod /usr/tmp/pedropatch.ko
	//mknod /dev/camclone c 222 0

	my_nx_vip = get_nx_vip();

	if (my_nx_vip == 0)
		return (-1);

	if (register_chrdev(222, "camclone", &my_fops)) {
		printk(KERN_INFO "PEDROPATCH: failed to register chdev");
	}
	printk(KERN_INFO "PEDROPATCH: loaded! The next steps are:\n");
    printk(KERN_INFO "mknod /dev/camclone c 222 0 \n");
    printk(KERN_INFO "dd if=/dev/camclone bs=153600 count=1 > img.yuv \n");
    printk(KERN_INFO "on a host pc: convert -size 320x240 -depth 8 -sampling-factor 4:2:2 -interlace plane img.yuv img.jpg");
	return 0;

}

static void __exit lkm_exit(void)
{
	printk(KERN_INFO "PEDROPATCH: unload! \n");
	unregister_chrdev(222, "camclone");
}

module_init(lkm_init);
module_exit(lkm_exit);
