/*	$NetBSD: fstat.c,v 1.24 1997/10/20 00:00:49 thorpej Exp $	*/

/*-
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#ifndef lint
__COPYRIGHT("@(#) Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
#endif /* not lint */

#ifndef lint
#if 0
static char sccsid[] = "@(#)fstat.c	8.3 (Berkeley) 5/2/95";
#else
__RCSID("$NetBSD: fstat.c,v 1.24 1997/10/20 00:00:49 thorpej Exp $");
#endif
#endif /* not lint */

#include <sys/param.h>
#include <sys/time.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/stat.h>
#include <sys/vnode.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/unpcb.h>
#include <sys/sysctl.h>
#include <sys/filedesc.h>
#define	_KERNEL
#include <sys/file.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#undef _KERNEL
#define NFS
#include <sys/mount.h>
#include <nfs/nfsproto.h>
#include <nfs/rpcv2.h>
#include <nfs/nfs.h>
#include <nfs/nfsnode.h>
#undef NFS

#include <net/route.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/in_pcb.h>

#include <ctype.h>
#include <errno.h>
#include <kvm.h>
#include <limits.h>
#include <nlist.h>
#include <paths.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define	TEXT	-1
#define	CDIR	-2
#define	RDIR	-3
#define	TRACE	-4

typedef struct devs {
	struct	devs *next;
	long	fsid;
	ino_t	ino;
	char	*name;
} DEVS;
DEVS *devs;

struct  filestat {
	long	fsid;
	long	fileid;
	mode_t	mode;
	u_long	size;
	dev_t	rdev;
};

#ifdef notdef
struct nlist nl[] = {
	{ "" },
};
#endif

int 	fsflg,	/* show files on same filesystem as file(s) argument */
	pflg,	/* show files open by a particular pid */
	uflg;	/* show files open by a particular (effective) user */
int 	checkfile; /* true if restricting to particular files or filesystems */
int	nflg;	/* (numerical) display f.s. and rdev as dev_t */
int	vflg;	/* display errors in locating kernel data objects etc... */

#define dprintf	if (vflg) fprintf

struct file **ofiles;	/* buffer of pointers to file structures */
int maxfiles;
#define ALLOC_OFILES(d)	\
	if ((d) > maxfiles) { \
		free(ofiles); \
		ofiles = malloc((d) * sizeof(struct file *)); \
		if (ofiles == NULL) { \
			fprintf(stderr, "fstat: %s\n", strerror(errno)); \
			exit(1); \
		} \
		maxfiles = (d); \
	}

/*
 * a kvm_read that returns true if everything is read 
 */
#define KVM_READ(kaddr, paddr, len) \
	(kvm_read(kd, (u_long)(kaddr), (char *)(paddr), (len)) == (len))

kvm_t *kd;

void	dofiles __P((struct kinfo_proc *));
int	ext2fs_filestat __P((struct vnode *, struct filestat *));
int	getfname __P((char *));
void	getinetproto __P((int));
char   *getmnton __P((struct mount *));
int	main __P((int, char **));
int	nfs_filestat __P((struct vnode *, struct filestat *));
void	socktrans __P((struct socket *, int));
int	ufs_filestat __P((struct vnode *, struct filestat *));
void	usage __P((void));
void	vtrans __P((struct vnode *, int, int));

int
main(argc, argv)
	int argc;
	char **argv;
{
	struct passwd *passwd;
	struct kinfo_proc *p, *plast;
	int arg, ch, what;
	char *memf, *nlistf;
	char buf[_POSIX2_LINE_MAX];
	int cnt;

	arg = 0;
	what = KERN_PROC_ALL;
	nlistf = memf = NULL;
	while ((ch = getopt(argc, argv, "fnp:u:vN:M:")) != -1)
		switch((char)ch) {
		case 'f':
			fsflg = 1;
			break;
		case 'M':
			memf = optarg;
			break;
		case 'N':
			nlistf = optarg;
			break;
		case 'n':
			nflg = 1;
			break;
		case 'p':
			if (pflg++)
				usage();
			if (!isdigit(*optarg)) {
				fprintf(stderr,
				    "fstat: -p requires a process id\n");
				usage();
			}
			what = KERN_PROC_PID;
			arg = atoi(optarg);
			break;
		case 'u':
			if (uflg++)
				usage();
			if (!(passwd = getpwnam(optarg))) {
				fprintf(stderr, "%s: unknown uid\n",
				    optarg);
				exit(1);
			}
			what = KERN_PROC_UID;
			arg = passwd->pw_uid;
			break;
		case 'v':
			vflg = 1;
			break;
		case '?':
		default:
			usage();
		}

	if (*(argv += optind)) {
		for (; *argv; ++argv) {
			if (getfname(*argv))
				checkfile = 1;
		}
		if (!checkfile)	/* file(s) specified, but none accessable */
			exit(1);
	}

	ALLOC_OFILES(256);	/* reserve space for file pointers */

	if (fsflg && !checkfile) {	
		/* -f with no files means use wd */
		if (getfname(".") == 0)
			exit(1);
		checkfile = 1;
	}

	/*
	 * Discard setgid privileges if not the running kernel so that bad
	 * guys can't print interesting stuff from kernel memory.
	 */
	if (nlistf != NULL || memf != NULL)
		setgid(getgid());

	if ((kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, buf)) == NULL) {
		fprintf(stderr, "fstat: %s\n", buf);
		exit(1);
	}
#ifdef notdef
	if (kvm_nlist(kd, nl) != 0) {
		fprintf(stderr, "fstat: no namelist: %s\n", kvm_geterr(kd));
		exit(1);
	}
#endif
	if ((p = kvm_getprocs(kd, what, arg, &cnt)) == NULL) {
		fprintf(stderr, "fstat: %s\n", kvm_geterr(kd));
		exit(1);
	}
	if (nflg)
		printf("%s",
"USER     CMD          PID   FD  DEV    INUM       MODE SZ|DV R/W");
	else
		printf("%s",
"USER     CMD          PID   FD MOUNT      INUM MODE         SZ|DV R/W");
	if (checkfile && fsflg == 0)
		printf(" NAME\n");
	else
		putchar('\n');

	for (plast = &p[cnt]; p < plast; ++p) {
		if (p->kp_proc.p_stat == SZOMB)
			continue;
		dofiles(p);
	}
	exit(0);
}

char	*Uname, *Comm;
int	Pid;

#define PREFIX(i) printf("%-8.8s %-10s %5d", Uname, Comm, Pid); \
	switch(i) { \
	case TEXT: \
		printf(" text"); \
		break; \
	case CDIR: \
		printf("   wd"); \
		break; \
	case RDIR: \
		printf(" root"); \
		break; \
	case TRACE: \
		printf("   tr"); \
		break; \
	default: \
		printf(" %4d", i); \
		break; \
	}

/*
 * print open files attributed to this process
 */
void
dofiles(kp)
	struct kinfo_proc *kp;
{
	int i;
	struct file file;
	struct filedesc0 filed0;
#define	filed	filed0.fd_fd
	struct proc *p = &kp->kp_proc;
	struct eproc *ep = &kp->kp_eproc;

	Uname = user_from_uid(ep->e_ucred.cr_uid, 0);
	Pid = p->p_pid;
	Comm = p->p_comm;

	if (p->p_fd == NULL)
		return;
	if (!KVM_READ(p->p_fd, &filed0, sizeof (filed0))) {
		dprintf(stderr, "can't read filedesc at %lx for pid %d\n",
			(long)p->p_fd, Pid);
		return;
	}
	if (filed.fd_nfiles < 0 || filed.fd_lastfile >= filed.fd_nfiles ||
	    filed.fd_freefile > filed.fd_lastfile + 1) {
		dprintf(stderr, "filedesc corrupted at %lx for pid %d\n",
			(long)p->p_fd, Pid);
		return;
	}
	/*
	 * root directory vnode, if one
	 */
	if (filed.fd_rdir)
		vtrans(filed.fd_rdir, RDIR, FREAD);
	/*
	 * current working directory vnode
	 */
	vtrans(filed.fd_cdir, CDIR, FREAD);
	/*
	 * ktrace vnode, if one
	 */
	if (p->p_tracep)
		vtrans(p->p_tracep, TRACE, FREAD|FWRITE);
	/*
	 * open files
	 */
#define FPSIZE	(sizeof (struct file *))
	ALLOC_OFILES(filed.fd_lastfile+1);
	if (filed.fd_nfiles > NDFILE) {
		if (!KVM_READ(filed.fd_ofiles, ofiles,
		    (filed.fd_lastfile+1) * FPSIZE)) {
			dprintf(stderr,
			    "can't read file structures at %lx for pid %d\n",
			    (long)filed.fd_ofiles, Pid);
			return;
		}
	} else
		memmove(ofiles, filed0.fd_dfiles,
		    (filed.fd_lastfile+1) * FPSIZE);
	for (i = 0; i <= filed.fd_lastfile; i++) {
		if (ofiles[i] == NULL)
			continue;
		if (!KVM_READ(ofiles[i], &file, sizeof (struct file))) {
			dprintf(stderr,
			    "can't read file %d at %lx for pid %d\n",
			    i, (long)ofiles[i], Pid);
			continue;
		}
		if (file.f_type == DTYPE_VNODE)
			vtrans((struct vnode *)file.f_data, i, file.f_flag);
		else if (file.f_type == DTYPE_SOCKET) {
			if (checkfile == 0)
				socktrans((struct socket *)file.f_data, i);
		}
		else {
			dprintf(stderr, 
				"unknown file type %d for file %d of pid %d\n",
				file.f_type, i, Pid);
		}
	}
}

void
vtrans(vp, i, flag)
	struct vnode *vp;
	int i;
	int flag;
{
	struct vnode vn;
	struct filestat fst;
	char mode[15];
	char *badtype = NULL, *filename;

	filename = badtype = NULL;
	if (!KVM_READ(vp, &vn, sizeof (struct vnode))) {
		dprintf(stderr, "can't read vnode at %lx for pid %d\n",
			(long)vp, Pid);
		return;
	}
	if (vn.v_type == VNON || vn.v_tag == VT_NON)
		badtype = "none";
	else if (vn.v_type == VBAD)
		badtype = "bad";
	else
		switch (vn.v_tag) {
		case VT_UFS:
			if (!ufs_filestat(&vn, &fst))
				badtype = "error";
			break;
		case VT_MFS:
			if (!ufs_filestat(&vn, &fst))
				badtype = "error";
			break;
		case VT_NFS:
			if (!nfs_filestat(&vn, &fst))
				badtype = "error";
			break;
		case VT_EXT2FS:
			if (!ext2fs_filestat(&vn, &fst))
				badtype = "error";
			break;
		default: {
			static char unknown[10];
			(void)snprintf(badtype = unknown, sizeof unknown,
			    "?(%x)", vn.v_tag);
			break;;
		}
	}
	if (checkfile) {
		int fsmatch = 0;
		DEVS *d;

		if (badtype)
			return;
		for (d = devs; d != NULL; d = d->next)
			if (d->fsid == fst.fsid) {
				fsmatch = 1;
				if (d->ino == fst.fileid) {
					filename = d->name;
					break;
				}
			}
		if (fsmatch == 0 || (filename == NULL && fsflg == 0))
			return;
	}
	PREFIX(i);
	if (badtype) {
		(void)printf(" -         -  %10s    -\n", badtype);
		return;
	}
	if (nflg)
		(void)printf(" %2d,%-2d", major(fst.fsid), minor(fst.fsid));
	else
		(void)printf(" %-8s", getmnton(vn.v_mount));
	if (nflg)
		(void)snprintf(mode, sizeof mode, "%o", fst.mode);
	else
		strmode(fst.mode, mode);
	(void)printf(" %6ld %10s", (long)fst.fileid, mode);
	switch (vn.v_type) {
	case VBLK:
	case VCHR: {
		char *name;

		if (nflg || ((name = devname(fst.rdev, vn.v_type == VCHR ? 
		    S_IFCHR : S_IFBLK)) == NULL))
			printf("  %2d,%-2d", major(fst.rdev), minor(fst.rdev));
		else
			printf(" %6s", name);
		break;
	}
	default:
		printf(" %6ld", (long)fst.size);
	}
	putchar(' ');
	if (flag & FREAD)
		putchar('r');
	if (flag & FWRITE)
		putchar('w');
	if (filename && !fsflg)
		printf("  %s", filename);
	putchar('\n');
}

int
ufs_filestat(vp, fsp)
	struct vnode *vp;
	struct filestat *fsp;
{
	struct inode inode;

	if (!KVM_READ(VTOI(vp), &inode, sizeof (inode))) {
		dprintf(stderr, "can't read inode at %lx for pid %d\n",
			(long)VTOI(vp), Pid);
		return 0;
	}
	fsp->fsid = inode.i_dev & 0xffff;
	fsp->fileid = (long)inode.i_number;
	fsp->mode = (mode_t)inode.i_ffs_mode;
	fsp->size = (u_long)inode.i_ffs_size;
	fsp->rdev = inode.i_ffs_rdev;

	return 1;
}

int
ext2fs_filestat(vp, fsp)
	struct vnode *vp;
	struct filestat *fsp;
{
	struct inode inode;

	if (!KVM_READ(VTOI(vp), &inode, sizeof (inode))) {
		dprintf(stderr, "can't read inode at %lx for pid %d\n",
		    (long)VTOI(vp), Pid);
		return 0;
	}
	fsp->fsid = inode.i_dev & 0xffff;
	fsp->fileid = (long)inode.i_number;
	fsp->mode = (mode_t)inode.i_e2fs_mode;
	fsp->size = (u_long)inode.i_e2fs_size;
	fsp->rdev = 0;  /* XXX */
	return 1;
}

int
nfs_filestat(vp, fsp)
	struct vnode *vp;
	struct filestat *fsp;
{
	struct nfsnode nfsnode;
	struct vattr va;
	mode_t mode;

	if (!KVM_READ(VTONFS(vp), &nfsnode, sizeof (nfsnode))) {
		dprintf(stderr, "can't read nfsnode at 0x%lx for pid %d\n",
			(u_long)VTONFS(vp), Pid);
		return 0;
	}
	if (!KVM_READ(nfsnode.n_vattr, &va, sizeof(va))) {
		dprintf(stderr,
		    "can't read vnode attributes at 0x%lx for pid %d\n",
		    (u_long)nfsnode.n_vattr, Pid);
		return 0;
	}
	fsp->fsid = va.va_fsid;
	fsp->fileid = va.va_fileid;
	fsp->size = nfsnode.n_size;
	fsp->rdev = va.va_rdev;
	mode = (mode_t)va.va_mode;
	switch (vp->v_type) {
	case VREG:
		mode |= S_IFREG;
		break;
	case VDIR:
		mode |= S_IFDIR;
		break;
	case VBLK:
		mode |= S_IFBLK;
		break;
	case VCHR:
		mode |= S_IFCHR;
		break;
	case VLNK:
		mode |= S_IFLNK;
		break;
	case VSOCK:
		mode |= S_IFSOCK;
		break;
	case VFIFO:
		mode |= S_IFIFO;
		break;
	default:
		break;
	};
	fsp->mode = mode;

	return 1;
}


char *
getmnton(m)
	struct mount *m;
{
	static struct mount mount;
	static struct mtab {
		struct mtab *next;
		struct mount *m;
		char mntonname[MNAMELEN];
	} *mhead = NULL;
	struct mtab *mt;

	for (mt = mhead; mt != NULL; mt = mt->next)
		if (m == mt->m)
			return (mt->mntonname);
	if (!KVM_READ(m, &mount, sizeof(struct mount))) {
		fprintf(stderr, "can't read mount table at %lx\n", (long)m);
		return (NULL);
	}
	if ((mt = malloc(sizeof (struct mtab))) == NULL) {
		fprintf(stderr, "fstat: %s\n", strerror(errno));
		exit(1);
	}
	mt->m = m;
	memmove(&mt->mntonname[0], &mount.mnt_stat.f_mntonname[0], MNAMELEN);
	mt->next = mhead;
	mhead = mt;
	return (mt->mntonname);
}

void
socktrans(sock, i)
	struct socket *sock;
	int i;
{
	static char *stypename[] = {
		"unused",	/* 0 */
		"stream", 	/* 1 */
		"dgram",	/* 2 */
		"raw",		/* 3 */
		"rdm",		/* 4 */
		"seqpak"	/* 5 */
	};
#define	STYPEMAX 5
	struct socket	so;
	struct protosw	proto;
	struct domain	dom;
	struct inpcb	inpcb;
	struct unpcb	unpcb;
	int len;
	char dname[32];

	PREFIX(i);

	/* fill in socket */
	if (!KVM_READ(sock, &so, sizeof(struct socket))) {
		dprintf(stderr, "can't read sock at %lx\n", (long)sock);
		goto bad;
	}

	/* fill in protosw entry */
	if (!KVM_READ(so.so_proto, &proto, sizeof(struct protosw))) {
		dprintf(stderr, "can't read protosw at %lx", (long)so.so_proto);
		goto bad;
	}

	/* fill in domain */
	if (!KVM_READ(proto.pr_domain, &dom, sizeof(struct domain))) {
		dprintf(stderr, "can't read domain at %lx\n",
		    (long)proto.pr_domain);
		goto bad;
	}

	if ((len = kvm_read(kd, (u_long)dom.dom_name, dname,
	    sizeof(dname) - 1)) < 0) {
		dprintf(stderr, "can't read domain name at %lx\n",
			(long)dom.dom_name);
		dname[0] = '\0';
	}
	else
		dname[len] = '\0';

	if ((u_short)so.so_type > STYPEMAX)
		printf("* %s ?%d", dname, so.so_type);
	else
		printf("* %s %s", dname, stypename[so.so_type]);

	/* 
	 * protocol specific formatting
	 *
	 * Try to find interesting things to print.  For tcp, the interesting
	 * thing is the address of the tcpcb, for udp and others, just the
	 * inpcb (socket pcb).  For unix domain, its the address of the socket
	 * pcb and the address of the connected pcb (if connected).  Otherwise
	 * just print the protocol number and address of the socket itself.
	 * The idea is not to duplicate netstat, but to make available enough
	 * information for further analysis.
	 */
	switch(dom.dom_family) {
	case AF_INET:
		getinetproto(proto.pr_protocol);
		if (proto.pr_protocol == IPPROTO_TCP ) {
			if (so.so_pcb) {
				if (kvm_read(kd, (u_long)so.so_pcb,
				    (char *)&inpcb, sizeof(struct inpcb))
				    != sizeof(struct inpcb)) {
					dprintf(stderr, 
					    "can't read inpcb at %lx\n",
					    (long)so.so_pcb);
					goto bad;
				}
				printf(" %lx", (long)inpcb.inp_ppcb);
			}
		}
		else if (so.so_pcb)
			printf(" %lx", (long)so.so_pcb);
		break;
	case AF_UNIX:
		/* print address of pcb and connected pcb */
		if (so.so_pcb) {
			printf(" %lx", (long)so.so_pcb);
			if (kvm_read(kd, (u_long)so.so_pcb, (char *)&unpcb,
			    sizeof(struct unpcb)) != sizeof(struct unpcb)){
				dprintf(stderr, "can't read unpcb at %lx\n",
				    (long)so.so_pcb);
				goto bad;
			}
			if (unpcb.unp_conn) {
				char shoconn[4], *cp;

				cp = shoconn;
				if (!(so.so_state & SS_CANTRCVMORE))
					*cp++ = '<';
				*cp++ = '-';
				if (!(so.so_state & SS_CANTSENDMORE))
					*cp++ = '>';
				*cp = '\0';
				printf(" %s %lx", shoconn,
				    (long)unpcb.unp_conn);
			}
		}
		break;
	default:
		/* print protocol number and socket address */
		printf(" %d %lx", proto.pr_protocol, (long)sock);
	}
	printf("\n");
	return;
bad:
	printf("* error\n");
}

/*
 * getinetproto --
 *	print name of protocol number
 */
void
getinetproto(number)
	int number;
{
	char *cp;

	switch(number) {
	case IPPROTO_IP:
		cp = "ip"; break;
	case IPPROTO_ICMP:
		cp ="icmp"; break;
	case IPPROTO_GGP:
		cp ="ggp"; break;
	case IPPROTO_TCP:
		cp ="tcp"; break;
	case IPPROTO_EGP:
		cp ="egp"; break;
	case IPPROTO_PUP:
		cp ="pup"; break;
	case IPPROTO_UDP:
		cp ="udp"; break;
	case IPPROTO_IDP:
		cp ="idp"; break;
	case IPPROTO_RAW:
		cp ="raw"; break;
	default:
		printf(" %d", number);
		return;
	}
	printf(" %s", cp);
}

int
getfname(filename)
	char *filename;
{
	struct stat statbuf;
	DEVS *cur;

	if (stat(filename, &statbuf)) {
		fprintf(stderr, "fstat: %s: %s\n", filename, strerror(errno));
		return(0);
	}
	if ((cur = malloc(sizeof(DEVS))) == NULL) {
		fprintf(stderr, "fstat: %s\n", strerror(errno));
		exit(1);
	}
	cur->next = devs;
	devs = cur;

	cur->ino = statbuf.st_ino;
	cur->fsid = statbuf.st_dev & 0xffff;
	cur->name = filename;
	return(1);
}

void
usage()
{
	(void)fprintf(stderr,
 "usage: fstat [-fnv] [-p pid] [-u user] [-N system] [-M core] [file ...]\n");
	exit(1);
}
