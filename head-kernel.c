#include "types.h"
#include "stat.h"
#include "user.h"

char head_buf[1024];

// prints the desired number of lines of text from the file
int getText(int txt_file_desc,int no_of_lines)
{ 
  int l_cnt=0;
  int i=0;
  int rd_buf=read(txt_file_desc, head_buf, sizeof(head_buf));
		if(rd_buf<0)
		{
			printf(1,"unable to read the file");
			exit();
		}
		else{
  printf(1,"Head command is getting executed in user mode\n");
    while(i<sizeof(head_buf))
    {	
      if(head_buf[i]!='\n'){			
      	printf(1,"%c",head_buf[i]);
      }	
     else if (l_cnt == (no_of_lines-1)){
	  printf(1,"\n");	
	  exit();
	  }  
	else if (i== sizeof(head_buf)-1)
	  { l_cnt++;
		exit();
	  } 
    else{
      	printf(1,"\n");
      	l_cnt++;
      } 
	  i++;
    }

		}
 return 0;
}

// returns the number of lines of text from the textfile
int getLinesCount(int txt_file_desc, char *filename)
{   int line_count=0;
	int rd_buf=read(txt_file_desc, head_buf, sizeof(head_buf));
		if(rd_buf<0)
		{
			printf(1,"unable to read the file");
			return 0;
		}
		else{
    for(int i=0;i<sizeof(head_buf);i++)
    {				
      if(head_buf[i]=='\n'){		  
      	line_count=line_count+1;
     }
	 else if(i==sizeof(head_buf)-1)
	 {
		 line_count++;
		
	}
	}
		}
return line_count;		
}
  
int main(int argc,char *argv[])
{
	int def_lines=14;
	int txt_file_desc;
	char *filename="";
	int no_of_args= argc;
	//int flag=0;
 
	if(no_of_args<=1)
	{   
		head(0,def_lines);
		exit();
	}
	else{
        switch(no_of_args)
		{
			case 2:
			filename = argv[1];
			//flag=1;
			break;
			case 4:
			if(strcmp(argv[1], "-n") == 0)
			{
			filename=argv[3];
            def_lines=atoi(argv[2]);
			}
		    //printf(1,"%d", def_lines);
		    break;
		    default:
		    printf(1,"insufficient number of arguments");
			exit();
		    break;
		}
		}
		txt_file_desc=open(filename,0);
		if(txt_file_desc<0)
		{
			printf(1,"unable to open the file");
			exit();
		}
		// if(flag ==1){
		// def_lines = getLinesCount(txt_file_desc,filename);
		// if(def_lines>14)
		// def_lines=14;
//}

		//getText(txt_file_desc,def_lines);
		head(txt_file_desc,def_lines);
		close(txt_file_desc);
		exit();	
		}
	



