#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"
#include "fs.h"

#define BUFSIZE 1024

struct TextLine {
    char *text;
    int count;
};

void initialize_EachLine(struct TextLine *line,int size) {
    line->text = (char *)malloc(size);;
    line->count = 0;
}
void free_EachLine(struct TextLine *line) {
    free(line->text);
}

// converting the characters of the currentLine and PreviousLine to Uppercase and then comparing them.
int strcasecmp(const char *curr_line, const char *prv_line) {
    char ch1, ch2;
    while (*curr_line && *prv_line) {
        ch1 = (*curr_line >= 'a' && *curr_line <= 'z') ? (*curr_line - 'a' + 'A') : *curr_line;
        ch2 = (*prv_line >= 'a' && *prv_line <= 'z') ? (*prv_line - 'a' + 'A') : *prv_line;
        
        if (ch1 != ch2) {
            return ch1 - ch2;
        }
        
        curr_line++;
        prv_line++;
    }
    return *curr_line - *prv_line;
}
void printLines(struct TextLine prev_line, char ch)
{
    if(ch=='d')
            {
            if (prev_line.count > 1)
             printf(1, "%s\n",prev_line.text);;
            }
            else{
            if (prev_line.count > 0) {
                switch(ch)
                {
                    case 'c':
                    printf(1, "%d %s\n", prev_line.count, prev_line.text);
                    break;
                    case 'i':
                    printf(1, "%s\n",prev_line.text);
                    break;
                    default: 
                    printf(1, "%s\n",prev_line.text);
                    
                }
             }
            }

}
void printText(int fd,char ch)
{
   struct TextLine current_line;
    struct TextLine prev_line;
    initialize_EachLine(&current_line,BUFSIZE);
    initialize_EachLine(&prev_line,BUFSIZE);
    printf(1,"Uniq command is getting executed in user mode.\n");

    while (1) {
        int n = 0;
        char c;
       
        
        while (read(fd, &c, 1) == 1 && c != '\n' && n < BUFSIZE - 1) {
            current_line.text[n++] = c;
        }
   
        if (n == 0)
            break;
          current_line.text[n] = '\0';
        int cmp;
        if(ch=='i'){

            cmp=strcasecmp(prev_line.text, current_line.text);
        }
        else{
            cmp=strcmp(prev_line.text, current_line.text);
        }
        if (cmp == 0) {
            prev_line.count++;
        } else {    
         printLines(prev_line,ch);
            free_EachLine(&prev_line);
            initialize_EachLine(&prev_line,BUFSIZE);
            strcpy(prev_line.text, current_line.text);
            prev_line.count = 1;
        }
    }
          printLines(prev_line,ch);
          free_EachLine(&current_line);
    free_EachLine(&prev_line);
    close(fd);
    exit();
}
     

int main(int argc, char *argv[]) {
     char *cmnd="";
     //char ch; // for kernel level
    char *filename = "";
    //printf(1, "%s", cmnd);
    if (argc ==2) {
        filename=argv[1];
        
    } else if (argc == 3) {
        cmnd= argv[1];   //user level : to store the second argument of argv
        //ch=argv[1][1];      // for kernel level: to store the character (i.e: c,i,d)
        filename = argv[2];
        }
        else if (argc>3){
            printf(1,"Insufficient number of arguments passed");
        }

    int txt_file_desc = open(filename, BUFSIZE);
    if (argc == 1) {
      txt_file_desc=0;
    }
    if (txt_file_desc < 0) {
        printf(1, "Error: Cannot open input file %s\n", argv[1]);
        exit();
    }
    else{
    printText(txt_file_desc, cmnd[1]);  // for user level function call
    //uniq(txt_file_desc, &ch);  // for kernel level execution
    }

    close(txt_file_desc);
    exit();
}

    


  