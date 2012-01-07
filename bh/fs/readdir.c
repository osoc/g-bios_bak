#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <fs/fs.h>

int filldir(struct linux_dirent *lde, const char * name, int namlen, loff_t offset,
		   unsigned long ino, unsigned int d_type)
{
	size_t reclen;

	lde->d_ino = ino;
	lde->d_off = offset;

	reclen = (size_t)(&((struct linux_dirent *)0)->d_name) + namlen + 2;
	ALIGN_UP(reclen, sizeof(long));
	lde->d_reclen = reclen;

	strncpy(lde->d_name, name, namlen);

	return 0;
}

int getdents(unsigned int fd, struct linux_dirent *lde, unsigned int count)
{
	int ret;
	struct file *fp;

	fp = fget(fd);
	if (!fp || !fp->f_op)
		return -ENODEV;

	ret = fp->f_op->readdir(fp, lde);

	return ret;
}