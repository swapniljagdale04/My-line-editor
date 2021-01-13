

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

typedef struct Editbuff
{  	char *line;
	struct Editbuff *next;
}Editbuff;

int ifd,ofd,line;
char c[1],list[2048],command[20],inputline[1024];

void HelpDemo()
{	
	printf("/****HELP*****/\n");
	printf("Here n1 n2 n3 are line positions\n");
	printf("1. print  => p n1 n2\n");
	printf("2. insert => i n1 \n");
	printf("3. append => a \n");
	printf("4. delete => d n1 n2\n");
	printf("5. move   => m n1 n2 n3\n");
	printf("6. copy   => c n1 n2 n3\n");
	printf("7. save   => s filename\n");
	printf("8. help   => h\n");
	printf("9. quit   => q\n");	
	printf("10. //**********MY_LINE_EDITOR************//\n");

}

void FileSave(Editbuff *head) //---only two validation case taken for filename.(name does not contain space and single dot)
{	Editbuff *node = head->next;char c = '\n';
	fgets(command,20,stdin);
	if(strcmp(command,".\n") == 0)
	{
		printf("invalid filename");
	}
	for(int i = 0; i < strlen(command); i++) {	
		if(command[i] == ' ') {
			printf("invalid filename");
		}
	}
	ofd=open(command,O_WRONLY | O_CREAT,0644);
	while(node!=NULL)
	{
		strcpy(inputline,node->line);
		write(ofd,inputline,strlen(inputline));
		write(ofd,&c,1);
		node=node->next;
	}
}

void CopyLines(Editbuff *head,int n1,int n2,int n3,int Totalline)     
{     	Editbuff *newnode,*address,*back,*curr,*back1,*curr1,*back2=head,*curr2=head->next;
	back=head;curr=head->next;
	if((n1<n2) && (n2 < n3) && (n1<=Totalline) && (n2<=Totalline) && (n3<=Totalline)){
		for(line=1;line<n1;line++)
		{       back=curr;
			curr=curr->next;
		}
		newnode=(Editbuff *)malloc(sizeof(curr));
		newnode->line=(char *)malloc(sizeof(curr->line));
		strcpy((newnode->line),curr->line);
		address=newnode;
		curr1=curr->next;
		line=line+1;	
		for(;line<=n2;line++)
		{	newnode->next=(Editbuff *)malloc(sizeof(curr1));
			newnode=newnode->next;
			newnode->line=(char *)malloc(sizeof(curr1->line));
			strcpy((newnode->line),curr1->line);
			curr1=curr1->next;
		}

		for(line=1;line<n3;line++)
		{       back2=curr2;
			curr2=curr2->next;
		}		
		back2->next=address;
		newnode->next=curr2;
	}else{
		printf("incorrect position");
	}
}

void MoveLines(Editbuff *head,int n1,int n2,int n3,int Totalline)   //----this fun have one problem (move from 1)
{	Editbuff *back,*curr,*back1,*curr1,*back2=head,*curr2=head->next;
	back=head;curr=head->next;
	if((n1<n2) && (n2 < n3) && (n1<=Totalline) && (n2<=Totalline) && (n3<=Totalline)){
		for(line=1;line<n1;line++)
		{	back=curr;
			curr=curr->next;
		}
		curr1=curr;
		for(;line<n2;line++)
		{
			curr1=curr1->next;
		}
		for(line=1;line<n3;line++)
		{	back2=curr2;
			curr2=curr2->next;
		}
		back2->next=curr;
		back->next=curr1->next;
		curr1->next=curr2;
	}else {
		printf("incorrect positions");
	}
}

void DeleteLines(Editbuff *head,int n1,int n2,int Totalline)
{	Editbuff *back,*curr,*back1,*curr1;
	curr=head->next;
	if((n1<=Totalline)&&(n2<=Totalline)){
		for(line=1;line<n1;line++)
		{	back=curr;	
			curr=curr->next;
		}
		for(;line<n2;line++)
		{
			back1=curr;
			curr=curr->next;
		}
		back->next=curr->next;		
	}else{
		printf("incorrect positions");
	}
}

void DeleteOne(Editbuff *head,int n1,int Totalline)
{
	Editbuff *back=head,*curr=head->next;
	if(n1<Totalline){
		for(line=1;line<n1;line++)
		{	back=curr;
			curr=curr->next;
		}
		back->next=curr->next;
	}else{
		printf("incorrect position");
	}
}

void AppendLines(Editbuff *head,int Totalline)
{	Editbuff *newnode,*back,*curr;
	curr=head->next;
	for(line=1;line<Totalline;line++)
	{
		back=curr;
		curr=curr->next;
	}
	fgets(inputline,1024,stdin);
	while((strcmp(inputline,".\n"))!=0)
	{	newnode=(Editbuff *)malloc(strlen(inputline) + 8);	
		newnode->line=(char *)malloc(strlen(inputline));
		strcpy((newnode->line),inputline);
		curr->next=newnode;
		newnode->next=NULL;
		curr=newnode;
		fgets(inputline,1024,stdin);
	}	
}

void insertLine(Editbuff *head,int n1,int Totalline)
{	Editbuff *newnode,*back,*curr;
	curr=head->next;
	if(n1<Totalline){
		fgets(inputline,1024,stdin);
		if(!strcmp(inputline,".\n")==0)
		{	newnode=(Editbuff *)malloc(strlen(inputline) + 8);
			newnode->line=(char *)malloc(strlen(inputline));
			strcpy((newnode->line),inputline); 
			newnode->next=NULL;
			for(line=1;line<n1;line++)
			{       back=curr;
				curr=curr->next;
			}
			back->next=newnode;
			newnode->next=curr;
		}else {
			printf("error :");
		}
	}else{
		printf("incorrect position");
	}
}

void Lprint(Editbuff *head,int n1,int Totalline)      
{	Editbuff *node=head->next,*back;
	back=node;
	if(n1<=Totalline){
		for(line=1;line<n1;line++)
		{	back=node;
			node=node->next;
		}
		printf("line %d %s\n",line,node->line);
	}else{
		printf("incorrect position");
	}
}

void LinSprint(Editbuff *head,int n1,int n2,int Totalline)
{	Editbuff *node=head->next;
	if((n1<=Totalline)&&(n2<=Totalline)){
		for(line=1;line<n1;line++)
		{
			node=node->next;
		}
		for(;line<=n2;line++)
		{
			printf("line - %d %s\n",line,node->line);
			node=node->next;
		}
	}else{
		printf("incorrect positions");
	}
}

int linecount(Editbuff *node)
{       Editbuff *temp;int count=0;
	temp=node->next;
	while(temp!=NULL){
		temp=temp->next;
		count ++;
	}return count;
}

Editbuff *Initialize(Editbuff *node)
{      Editbuff *head;
	head=(Editbuff *)malloc(sizeof(Editbuff));
	head->next=node;
	return head;
}

void printLineNode(Editbuff *list){
	while(list!=NULL){
		printf("%s\n",list->line);
		list=list->next;
	}
}

Editbuff *addLine(Editbuff *head,Editbuff *node){
	if(head==NULL) 
		return node;
	Editbuff *temp=head;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=node;
	return head;
}

Editbuff *Readbuff(char list[2048])
{
	Editbuff *lines=NULL,*temp;
	int i=0,j;
	char buff[1024];
	while(i<strlen(list)){
		j=0;
		while(list[i]!='\n'&& list[i]!='\0'){
			buff[j++]=list[i++];
		}
		buff[j]='\0';
		i++;
		temp=(Editbuff *)malloc(strlen(buff)+8);
		temp->line=(char* )malloc(strlen(buff));
		strcpy(temp->line,buff);
		temp->next=NULL;
		lines=addLine(lines,temp);
	}
	return lines;
}

int main(int argc,char **argv)
{	
	Editbuff *head,*Fhead;
	int Totalline,i=0,n,n1,n2,n3;char c1;
	if(argc != 2)
	{
		printf("Incorrect input");
	}
	ifd=open(argv[1],O_RDONLY);

	if(ifd == -1)
	{
		printf("error in opening file");
	}
	while(read(ifd,&c,1)!=0)
	{
		list[i++]=c[0];
	}
	list[i++]='\0';
	head=Readbuff(list);
	printLineNode(head);	
	Fhead=Initialize(head);          
	while(1){
		printf("\n?");
		fgets(command,20,stdin);
		n=sscanf(command,"%c%d%d%d",&c1,&n1,&n2,&n3);
		Totalline=linecount(Fhead);
		printf("Total line in file -  %d\n",Totalline);
		if(n1>=0 && n2>=0){ 
			switch(c1)
			{       
				case 'p':	if(n==2){
							Lprint(Fhead,n1,Totalline);
						}     
						else if(n==3){
							LinSprint(Fhead,n1,n2,Totalline);
						}
						else { 
							printf("incorrect command\n");
						}
						break;

				case 'i':    	if(n==2){
							insertLine(Fhead,n1,Totalline);
						}
						else{
							printf("incorrect command");
						}
						break;

				case 'a':	if(n==1){
							AppendLines(Fhead,Totalline);
						}
						else {
							printf("incorrect  command");
						}		 
						break;

				case 'd':       if(n==3){
							DeleteLines(Fhead,n1,n2,Totalline);
						}
						else if(n==2){
							DeleteOne(Fhead,n1,Totalline);
						}
						else { 
							printf("incorrect command");
						}
						break;

				case 'm':     	if(n==4){
							MoveLines(Fhead,n1,n2,n3,Totalline);
						}
						else{
							printf("incorrect command");
						}				
						break;

				case 'c':      if(n==4){
						       CopyLines(Fhead,n1,n2,n3,Totalline);
					       }
					       else{
						       printf("incorrect command");
					       }                               
					       break;

				case 's':      if(n==1){
						       FileSave(Fhead);
					       }
					       else{
						       printf("incorrect command");
					       }		
					       break;

				case 'l':	if(n==1){
						printf("Total lines in file %d\n",linecount(Fhead));;
						}else {
							printf("incorrect command");
						}
						break;
				
				case 'q':     exit(0);
				
				case 'h':     HelpDemo();
						break;

				default :     fprintf(stdout,"wrong command");

			}
		}else { 
			printf("incorrect positions");	
		}	
	}
}
