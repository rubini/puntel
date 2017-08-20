/*
 * Trivial program to write  LPC RAM and go to it 
 * Alessandro Rubini, 2007-2010 GNU GPL2 or later
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include "lpclib.h"

/* error message */
static void __attribute__((noreturn)) errorexit(char **argv, char *reason)
{
	fprintf(stderr, "%s: %s\n", argv[0], reason);
	fprintf(stderr, "%s: Usage: \"%s <file>\n", argv[0], argv[0]);
	fprintf(stderr, "    $LPC_PORT is the serial port (default %s)\n",
		LPC_PORT);
	fprintf(stderr, "    $LPC_CLK is the clock speed in kHz "
		"(default: %i)\n", LPC_CLK);
	fprintf(stderr, "    $LPC_VERBOSE forces verbose mode (default on)\n");
	fprintf(stderr, "    $LPC_QUIET disables verbose mode\n");
	exit(1);
}

/*
 * Main program
 */
#define V(format, ...) if (verbose) fprintf(stderr, format, ## __VA_ARGS__)
#define MAXSIZE (64*1024)

int main(int argc, char **argv)
{
	static unsigned char filebuf[MAXSIZE];
	unsigned char *ptr; /* binary */
	char s[128]; /* ascii */
	unsigned long run_addr;
	char *port, *reply;
	int fd, i, fsize, wrsize, secsize, size, pos, nline, clk, verbose;
	uint32_t check;
	struct lpc_dev *dev;
	FILE *f;

	if (argc != 2) errorexit(argv, "Wrong number of arguments");
	if (!(f = fopen(argv[1], "r"))) {
		sprintf(s, "%s: %s", argv[1], strerror(errno));
		errorexit(argv, s);
	}

	/* get arguments from environment */
	port = getenv("LPC_PORT");
	if (!port)
		port = LPC_PORT;
	clk = LPC_CLK;
	if (getenv("LPC_CLK"))
		clk = atoi(getenv("LPC_CLK"));
	verbose = 1;
	if (getenv("LPC_VERBOSE"))
		verbose = 1;
	if (getenv("LPC_QUIET"))
		verbose = 0;

	/* open serial port and make it raw */
	V("Opening serial port %s\n", port);
	if( (fd=open(port, LPC_OPEN_FLAGS)) < 0){
		fprintf(stderr, "%s: %s: %s\n", argv[0], port, strerror(errno));
		exit(1);
	}
	lpc_fd_configure(fd);

	/* reset, force programming, exit reset */
	V("Forcing boot loader mode\n");
	lpc_fd_forcebootloader(fd);

	/* synchronize (and remove echo) */
	fprintf(stderr, "Syncronizing... ");
	if (lpc_fd_sync(fd, clk) != 0) {
		fprintf(stderr, "failed!\n");
		exit(1);
	}
	fprintf(stderr, "done\n");

	/* Identify part */
	V("Identifying... ");
	i = lpc_fd_identify(fd);
	if (i == -1) {V("failure\n"); exit(1);}
	V("done\n");

	/* Report part to stderr */
	fprintf(stderr, "part number: %x\n", i);
	for (dev = lpc_devs; dev->id && dev->id != i; dev++)
		/* nothing */;
	if (!dev->id) {
		fprintf(stderr, "unknown part, using 2104 (minimal) values\n");
		dev = lpc_devs;
	} else {
		fprintf(stderr, "LPC%i, %ikB Flash, %ikB RAM\n", dev->name,
			dev->rom, dev->ram);
	}

	/* Report boot loader version */
	reply = lpc_fd_isp_version(fd);
	if (reply)
		fprintf(stderr, "ISP Boot loader: %s\n", reply);
	else
		fprintf(stderr, "Error getting ISP version\n");

	/* read file and check size */
	memset(filebuf, 0xff, sizeof(filebuf));
	fsize = fread(filebuf, 1, sizeof(filebuf), f);
	size = (fsize + 899) / 900 * 900; /* a multiple of 20 lines */
	if (size > dev->rom * 1024)
		errorexit(argv, "file size doesn't fit flash\n");
	V("size is %i (xfer %i)\n", fsize, size);

	/* checksum: the checksum vector is different for arm7 and cortex */
	{
		uint32_t *v = (void *)filebuf;
		v[dev->type->checksum_vector] = check = 0;
		for (i = 0; i < 8; i++)
			check += v[i];
		v[dev->type->checksum_vector] = -check;
		/* calculate the start address */
		if (dev->type->mode == 'A')
			run_addr = 0;
		else
			run_addr = v[1] & ~1;
	}

	/* For each block of 4kB or 8kB: copy to ram, prepare, erase, write */
	wrsize = secsize = dev->type->sector_size;

	/* But for devices with smaller RAM, copy 1k a time */
	if (dev->ram * 1024 <= secsize)
		wrsize = 1024; /* 2k is not allowed... */

	for (pos = 0; pos < fsize; pos += wrsize) {
		int copysize = fsize - pos;

		if (copysize > wrsize)
			copysize = wrsize;

		/*
		 * copysize should also better be a multiple of 20 lines.
		 * Summing hacks, to write 1k we copy 1800 bytes. Bah.
		 */
		copysize = (copysize + 899) / 900 * 900;

		/* Write data to RAM */
		sprintf(s, "W %lu %i\r\n", dev->type->ram_addr, copysize);
		V("%s", s);
		reply = lpc_write_c(fd, s, 2 /* echo and error code */);
		V("%s", reply);
		if (reply[0] != '0')
			return -1;
		check = 0;
		for (ptr = filebuf + pos, nline = 0, i = 0; i < copysize;) {
			int j;
			lpc_uuencode(ptr, 45, s);
			V(".");
			for (j=0; j<45; j++)
				check += ptr[j];
			strcat(s, "\r\n");
			lpc_write_c(fd, s, 1);
			ptr += 45; i += 45;
			nline++;
			if (nline && nline%20 == 0) {
				/* print checksum read OK */
				sprintf(s, "%li\r\n", (long)check); check = 0;
				reply = lpc_write_c(fd, s, 2);
				V("%s", reply); /* OK Hopefully */
			}
		}

		/* hopefully, everything worked. Now unlock */
		sprintf(s, "U 23130\r\n");
		V("%s", s);
		lpc_write_c(fd, s, 2);

		fprintf(stderr, "position 0x%05x, size %i:\n", pos,
			copysize > wrsize ? wrsize : copysize);

		if (pos % secsize == 0) {
			/* do not erase for trailing parts of a sector */
			sprintf(s, "P %i %i\r\n",
				pos/secsize, pos/secsize);
			V("%s", s);
			reply = lpc_write_c(fd, s, 2); lpc_trim(reply);
			fprintf(stderr, "   prepare: %s\n", reply);
			if (reply[0] != '0')
				return -1;

			sprintf(s, "E %i %i\r\n",
				pos/secsize, pos/secsize);
			V("%s", s);
			reply = lpc_write_c(fd, s, 2);
			while (!reply) { /* erase takes time */
			if (lpc_fd_gets(fd, s, sizeof(s)) > 0)
				reply = s;
			}
			lpc_trim(reply);
			fprintf(stderr, "   erase: %s\n", reply);
			if (reply[0] != '0')
				return -1;
		}
		sprintf(s, "P %i %i\r\n",
			pos/secsize, pos/secsize);
		V("%s", s);
		reply = lpc_write_c(fd, s, 2); lpc_trim(reply);
		fprintf(stderr, "   prepare: %s\n", reply);
		if (reply[0] != '0')
			return -1;

		sprintf(s, "C %i %lu %i\r\n", pos, dev->type->ram_addr,
			wrsize /* whole sector */);
		V("%s", s);
		reply = lpc_write_c(fd, s, 2);
		while (!reply) { /* copy takes time */
			if (lpc_fd_gets(fd, s, sizeof(s)) > 0)
				reply = s;
		}
		lpc_trim(reply);
		fprintf(stderr, "   copy: %s\n", reply);
		if (reply[0] != '0')
			return -1;
	}

	/* Force user flash on, or we'll read back ROM vectors */
	lpc_map_user_flash(fd, dev->type);

	/* Go to actual code (vector 1, not 0 like on ARM7) */
	sprintf(s, "G %li %c \r\n", run_addr, dev->type->mode);
	fprintf(stderr, "--> mode %i %c - %s\n", dev->name, dev->type->mode, s);
	lpc_write_c(fd, s, 2);

	while(1) {
		fd_set fds; struct timeval tv;

		if (lpc_fd_gets(fd, s, 80) >=0) /* data */
			V("%s", s);
		/* else read stdin, which is line-buffered */
		FD_ZERO(&fds);	FD_SET(0, &fds);
		tv.tv_sec = tv.tv_usec = 0;
		if (select(1, &fds, NULL, NULL, &tv) > 0) {
			if (fgets(s, 80, stdin) == NULL)
				exit(0);
			lpc_write_c(fd, s, 0);
		}
	}

	return 0;
}
