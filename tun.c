#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define EXISTS(pathname)         (access(pathname, F_OK) == 0)
#define TUN_DEV   "/dev/net/tun"
#define TUN_PATH  "/dev/net"

int tun_create_dev(){
	mode_t mask = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	int i;
	if (!EXISTS(TUN_PATH) && mkdir(TUN_PATH, mask)) {
		return 1;
	}
	if (mknod (TUN_DEV, S_IFCHR | S_IRUSR | S_IWUSR, makedev(10, 200))) {
		printf("Error - unable to create tun device - maybe wrong user\n");
		return 1;
	}
	return 0;
}

int tun_check_or_create() {
	FILE *fp;
	if (!EXISTS(TUN_DEV)) {
		return tun_create_dev();
	}
	return 0;
}
