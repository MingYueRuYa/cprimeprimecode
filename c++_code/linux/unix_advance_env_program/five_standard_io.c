#include "apue.h"
#include "error.c"

#include <sys/stat.h>

/*
 * 测试 getc、putc
 * 这两个函数使用宏来实现，不建议使用
 * */
void test_fgets_fputs();

/*
 * 测试 fgetc、fputc
 * */
void test_fgetc_fputc();

/*
 * 测试缓冲区属性
 * */
void test_buffer_attribute();

/*
 * 测试tmpnam, tmpfile
 * */
void test_tmpnam_tmpfile();
void make_temp(char *template);

/*
 * 测试mkstemp
 * */
void test_mkstemp();

/*
 * 测试内存流 fmemopen
 * */
void test_memstr();

void pr_stdio(const char *, FILE *);
int  is_unbuffered(FILE *);
int  is_linebuffered(FILE *);
int  buffer_size(FILE *);

int main(int argc, char *argv[])
{
//    test_getc_putc();

//    test_fgets_fputs();

//    test_buffer_attribute();

//    test_tmpnam_tmpfile();

//    test_mkstemp();

    test_memstr();

    return 0;
}

void 
test_getc_putc()
{
    int c;
    while ( (c = getc(stdin)) != EOF ) {
        if (putc(c, stdout) == EOF) {
            err_sys("output error");
        } //if
    } //while

    if (ferror(stdin)) {
        err_sys("input error");
    }
}

void 
test_fgets_fputs()
{
    char buf[MAXLINE];

    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (fputs(buf, stdout) == EOF) {
            err_sys("output error");
        } //if
    } //while

   if (ferror(stdin)) {
        err_sys("input error");
   } 
}


void
test_buffer_attribute()
{
    FILE *fp;

    fputs("enter any character\n", stdout);
    if (getchar() == EOF) {
        err_sys("getchar error");
    }
   
    fputs("one line to standard error\n", stderr);

    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);

    if ( (fp = fopen("/etc/passwd", "r")) == NULL) {
        err_sys("fopen error");
    }

    if (getc(fp) == EOF) {
        err_sys("getc error");
    }

    pr_stdio("/etc/passwd", fp);
}

void
pr_stdio(const char *name, FILE *fp)
{
    printf("stream = %s, ", name);
    
    if (is_unbuffered(fp)) {
        printf("unbuffered");
    } else if (is_linebuffered(fp)) {
        printf("line buffered");
    } else {
        printf("fully buffered");
    }

    printf(", buffer size = %d.\n", buffer_size(fp));
}

#if defined(_IO_UNBUFFERED)

int
is_unbuffered(FILE *fp)
{
    return (fp->_flags & _IO_UNBUFFERED);
}

int
is_linebuffered(FILE *fp)
{
    return (fp->_flags & _IO_LINE_BUF);
}

int
buffer_size(FILE *fp)
{
    return (fp->_IO_buf_end - fp->_IO_buf_base);    
}

#elif defined(__SNBF)

int
is_unbuffered(FILE *fp)
{
    return (fp->_flags & __SNBF);
}

int
is_linebuffered(FILE *fp)
{
    return (fp->_flags & __SNBF);
}

int
buffer_size(FILE *fp)
{
    return (fp->_bf.size);    
}

#elif defined(_IONBF)

#ifdef _LP64
#define _flag _pad[4]
#define _ptr __pad[1]
#define _base __pad[2]
#endif

int
is_unbuffered(FILE *fp)
{
    return (fp->_flags & _IONBF);
}

int
is_linebuffered(FILE *fp)
{
    return (fp->_flags & _IONBF);
}

int
buffer_size(FILE *fp)
{
#ifdef _LP64
    return (fp->_base - fp->ptr);    
#else
    return (BUFSIZ);    //just a guess
#endif
}

#else
#error unknow stdio implementation!
#endif

void 
test_tmpnam_tmpfile()
{
    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;

    printf("%s\n", tmpnam(NULL));   //first temp name

    tmpnam(name);
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL) { //creat temp file
        err_sys("tmpfile error");
    }
   
    fputs("one line of output\n", fp);  //write to temp file 
    rewind(fp);     // then read it back

    if (fgets(line, sizeof(line), fp) == NULL) {
        err_sys("fgets error.");
    }

    fputs(line, stdout);    // print the line we wrote

    fgetc(stdin);
}

void
test_mkstemp()
{
    char good_template[] = "/tmp/dirXXXXXX";    // right way
    char *bad_template   = "/tmp/dirXXXXXX";    // wrong way

    printf("trying to create first temp file...\n");
    make_temp(good_template);
    printf("trying to create first temp file...\n");
    make_temp(bad_template);
}

void 
make_temp(char *template)
{
    int         fd;
    struct stat sbuf;

    if ( (fd = mkstemp(template)) < 0) {
        err_sys("can't create temp file");
    }
    printf("temp name = %s\n", template);
    close(fd);

    if (stat(template,  &sbuf) < 0) {
        if (errno == ENOENT) {
            printf("file doesn't exist.\n");
        } else {
            err_sys("stat failed.");
        }
    } else {
        printf("file exists\n");
        unlink(template);
    }
}

#define BSZ 48

void 
test_memstr()
{
    FILE *fp;        
    char buf[BSZ];
    memset(buf, 'a', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';

    // 打开时会将起始处插入'\0'
    if ( (fp = fmemopen(buf, BSZ, "w+")) == NULL ) {
        err_sys("fmemopen failed"); 
    }

    printf("initial buffer contents: %s\n", buf);
    fprintf(fp, "hello, world");
    printf("before flush: %s\n", buf);
    fflush(fp);
    printf("after fflush: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'b', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    fprintf(fp, "hello, world");
    // fp指针指向文件起始处
    fseek(fp, 0, SEEK_SET);
    printf("after fseek: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'c', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    fprintf(fp, "hello, world");
    fclose(fp);
    printf("after fclose: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));
    //result:
    //initial buffer contents: 
    //before flush: 
    //after fflush: hello, world
    //len of string in buf = 12
    //after fseek: bbbbbbbbbbbbhello, world
    //len of string in buf = 24
    //after fclose: hello, worldcccccccccccccccccccccccccccccccccc
    //len of string in buf = 46
}






