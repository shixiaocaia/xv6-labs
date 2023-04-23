// find.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *target) {
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;
	//printf("path: %s\n", path);

	if((fd = open(path, 0)) < 0){
		fprintf(2, "find: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "find: cannot fstat %s\n", path);
		close(fd); //及时关闭fd
		return;
	}

	while(read(fd, &de, sizeof(de)) == sizeof(de)){
		if(de.inum == 0){
			continue;
		}
		//printf("buf: %s, | path: %s, | de.name: %s\n",buf, path, de.name);
		strcpy(buf, path); //覆盖
		p = buf + strlen(buf); //移动到buf末尾
		*p++ = '/';
		memmove(p, de.name, DIRSIZ); // 覆盖
		p[DIRSIZ] = 0;

		if(stat(buf, &st) < 0){
			fprintf(2, "find: cannot stat %s\n", buf);
		}

		switch(st.type){
			case T_FILE:
				if(strcmp(target, de.name) == 0){
					printf("%s\n", buf);
				}
				break;

			case T_DIR:
				//printf("is dir %s\n", de.name);
				if((strcmp(de.name, ".") != 0) && strcmp(de.name, "..") != 0){
					find(buf, target);
				}
		}
	}
	close(fd);
	return;
}

int main(int argc, char *argv[])
{
	if(argc != 3){
		fprintf(2, "please enter correct argu\n");
		exit(1);  //error exit
	}

	char *pathname = argv[1];
	char *filename = argv[2];

	find(pathname, filename);
	exit(0);
}
