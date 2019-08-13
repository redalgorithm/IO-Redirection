#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include <string>
#include <getopt.h>
#include <signal.h>
#include <queue>
using namespace std;

//------------------------------------
// FUNCTION: argError
//
// prints to stderr (fd2) a message
// in response to an invalid argument
// during program execution.
//
// ARGS: char*, int, queue<int>
// RETURN: NA
//------------------------------------
string usage_statement =
"Usage: lab0 {[opt ...] | [opt ...] <arg>}\n--input <file>\n--output <file>\n--segfault\n--catch\n";
void argError(char* argv[], int argc, queue<int>indices)
{
    errno = EINVAL;
    fprintf(stderr, "lab0: %s\nARG: ", strerror(errno));
    
    while(!indices.empty())
    {
        fprintf(stderr, "'%s' ", argv[indices.front()]);
        indices.pop();
    }
    
    while(optind < argc)
        fprintf(stderr, "'%s' ", argv[optind++]);
    
    fprintf(stderr, "\nFILE: '%s'\n", optarg);
    cout << usage_statement << endl << endl;
    exit(1);
}

//------------------------------------
// FUNCTION: fileError
//
// prints to stderr (fd2) a message
// in response to a file error.
//
// ARGS: bool, string
// RETURN: NA
//------------------------------------
void fileError(bool in, string arg)
{
    int i = in;
    
    fprintf(stderr, "lab0: %s\n", strerror(errno));
    fprintf(stderr, "ARG: '%s'\n", arg.c_str());
    fprintf(stderr, "FILE: '%s'\n", optarg);
    switch(i)
    {
        case 1:
            exit(2);
            break;
        case 0:
            exit(3);
            break;
    }
}

//------------------------------------
// FUNCTION: sighandle
//
// catches a segmentation fault and
// prints to stderr (fd2) an error
// message.
//
// ARGS: int
// RETURN: NA
//------------------------------------
char* file;
void sighandle(int sig)
{
    fprintf(stderr, "lab0: %s\n", strerror(errno));
    fprintf(stderr, "ARG: '--segfault'\n");
    fprintf(stderr, "FILE: '%s'\n", file);
    cout << "PID: " << getpid() << endl;
    cout << "SNO: " << sig << endl;
    signal(sig, SIG_DFL);
    kill(getpid(), sig);
    exit(4);
}

// MAIN PROCESS
int main(int argc, char* argv[])
{
    queue<int>indices;      //collection of invalid entries
    int flag = 0;           //reusable flag
    int fd;                 //returned file descriptor
    int savedfd;            //useful for i/o redirection
    int c = 0;              //getopt return value
    string arg;             //save option for generating error
    char* buf = new char;   //buffer for keyboard entry
    
    // INFINITE LOOP UNTIL ALL OPTIONS PARSED
    while(1)
    {
        int argind = optind ? optind : 1;       //used to save index of option if error
        
        //prepare long options
        int option_index = 0;
        static struct option long_options[] =
        {
            {"input", required_argument, NULL, 1},
            {"output", required_argument, NULL, 2},
            {"segfault", no_argument, NULL, 3},
            {"catch", no_argument, NULL, 4},
            {0, 0, 0, 0}
        };
        
        c = getopt_long(argc, argv, "", long_options, &option_index);
        
        //no more valid options to parse?
        if(c == -1)
            break;
        
        //operations for each parameter
        switch(c)
        {
            //--input
            case 1:
            {
                fd = open(optarg, O_RDONLY);
                arg = "--input";
                file = optarg;
                
                if(fd < 0)
                    fileError(1, arg);
                else
                {   //redirect fd to stdin
                    savedfd = dup(0);
                    close(0);
                    dup2(fd, 0);
                    close(fd);
                }
                flag = 2;
                break;
            }
                
            //--output
            case 2:
            {
                fd = open(optarg, O_CREAT | O_WRONLY | O_EXCL, 0700);  //0700 for exe 0600 for rdwr
                arg = "--output";
                file = optarg;
                
                if(fd < 0)
                    fileError(0, arg);
                else
                {
                    cout << "WAITING FOR INPUT:\n";

                    //redirect fd to stdout
                    savedfd = dup(1);
                    close(1);
                    dup2(fd, 1);
                    close(fd);                  //cout << "output redirection successful" << endl;
                }
                flag = 2;
                break;
            }
             
            //--segfault
            case 3:
            {
                flag = 4;                       //cout << "segfault works" << endl;
                buf = NULL;
                break;
            }
             
            //--catch
            case 4:
            {
                signal(SIGSEGV, sighandle);     //cout << "catch works" << endl;
                break;
            }
             
            //ambiguous match or extraneous parameter
            case '?':
            {
                flag = 1;
                indices.push(argind);
                break;
            }
        }
        
        if(argv[optind] != NULL)
        {
            string cmp = argv[optind];
            if(cmp == "--segfault" || cmp == "--catch")
                continue;
        }
        if(flag == 1)
        {
            flag = 0;
            continue;
        }
        
        
        if(flag != 2)
            cout << "WAITING FOR INPUT:\n";
        
        //segfault problem occurs here
        while(read(0, buf, 1024) != 0)
        {
            if(buf == NULL)
                break;
        }
        
        fprintf(stderr, "\n\nMESSAGE: REACHED EOF\n\n");
        
        //get length of buffer
        int len = 0;
        while(buf[len] != 0)
            len++;
        
        
        if(flag != 2)
            cout << "OUTPUT:\n";
        
        long m = write(1, buf, len);
        
        //failed write to stdout?
        if (m < 0)
        {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(3);
        }
        
        switch(c)
        {
            case 1: dup2(savedfd, 0);
                    close(savedfd);
                    cout << endl;
                buf = new char;
                break;
            case 2: dup2(savedfd, 1);
                    close(savedfd);
                buf = new char;
                break;
        }
    }
    
    if(optind < argc || flag == 1)
        argError(argv, argc, indices);

    cout << endl;
    exit(0);
}

