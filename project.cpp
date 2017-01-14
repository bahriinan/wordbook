#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <cstring>
using namespace std;
class node{
	public:
	node(){
		next=0;
		counter=0;
	}
	node(char el[100],node*n=0){
		strcpy(info,el);next = n;
	}
	char info[100];
	int counter;
    	node *next;
};
class list{
	public:
		list(){
			head=tail=0;
			counter=0;
			
		}
		void insertion(char*);
		void deletion(char*);
		char search(char*);
		char search2(char*);
		void printAll()const;
		void wordcleaner(char*);
		int writefile(list *);
	private:
		node *head, *tail;
		int counter;
};
list *myList=new list();

void list::insertion(char *word){
	if(search(word)!=1){
		node *temp=new node(word);
		if(head==0){//eğer liste bossa
			head=temp;
			tail=temp;
			temp->next=NULL;
			temp->counter=1;
			myList->counter++;
			
		}
		else if(strcmp(word,head->info)<0){//eklenecek veri bastaysa
		 	temp->counter=1;
		 	temp->next=head;
		 	head=temp;
			myList->counter++;
	 	 	
		}
		else if(strcmp(word,tail->info)>0){//eklenecek veri sondaysa
		 	temp->counter=1;
         	 	temp->next=NULL;
		 	tail->next=temp;
		 	tail=temp;
			myList->counter++;
		 	
		}
		else{// eklenecek veri 2 veri arasındaysa
			node *data=new node(word);
			temp=head;
			for(temp; temp != 0; temp=temp->next){
				if(strcmp(word,temp->info)>0 && strcmp(word,temp->next->info)<0){//eklenecek veri bu 2 verinin arasında olmalı
				data->next=temp->next;
				temp->next=data;
				data->counter=1;
				myList->counter++;
				}
			}
		}
	}
}
void list::deletion(char *word){
	if(search(word)==1){
		if(head==0){
		cout << "there is no word into list";
		}
		else if(strcmp(word,head->info)==0){//silinecek veri bastaysa
			node *temp=head;
     			head = head->next;
    			delete temp;
			myList->counter--;
		}
		else if(strcmp(word,tail->info)==0){//silinecek veri sondaysa
			node *temp=head;
			for (temp; temp->next != tail; temp = temp->next);
         		delete tail;
         		tail = temp;      
         		tail->next = 0;
			myList->counter--;
		
		}
		else{//silincek veri aradaysa
			node *tmp,*pred;
			for (pred = head, tmp = head->next; tmp != 0 && (strcmp(word,tmp->info));pred = pred->next, tmp = tmp->next);
              		if (tmp != 0) {
                  	pred->next = tmp->next;
		   	delete tmp;
		   	myList->counter--;
			}
		}
	}
	else{
		cout << "there is no word like that";
	}
}
char list::search(char *word){
	node *temp=head;
	for(temp; temp != 0 ; temp=temp->next){
		if(strcmp(word,temp->info)==0){
			temp->counter++;
			return 1;			
		}
	} 
}
char list::search2(char *word){
	node *temp=head;
	for(temp; temp != 0 ; temp=temp->next){
		if(strcmp(word,temp->info)==0){
			return 1;			
		}
	} 
}
void list::wordcleaner(char *word){
     char temp[100]="!'^+%&/()=?_-*])\"[({}$#,;.:'0123456789";
     char *token;
     token=strtok(word,temp);
     while(token!=NULL){
     insertion(token);
     token=strtok(NULL,temp);
     }
}
void list::printAll() const {
    for (node *tmp = head; tmp != 0; tmp = tmp->next)
        cout << tmp->info << " " << tmp->counter << " " << myList->counter << " " << endl;
	cout << endl;
}
int readfile(list *myList){
	ifstream file;
	file.open ("1661.txt");
	if (!file.is_open()) return 0;
	char word[100];
	char *token;
	while (file >> word){
		strlwr(word);
		myList->wordcleaner(word);
	}
}
int list::writefile(list *myList){
     FILE *a;
     a=fopen("output.txt","w");
     if(a==NULL){
                 strcat("output",".txt");
                 }
     node *b;
     b=myList->head;
     while(b!=NULL){
                 fprintf(a,"%s %d\n",b->info,b->counter);
                 b=b->next;
                 }
      fclose(a);
     }				
int main(){
	int choice;
	char word[100];
	cout << "the book is reading.....\n";
	readfile (myList);
	cout << " reading is completed what do you want now\n";
	while(true){
		cout << "1. Print list\n2. insertion\n3. deletion\n4.search\n5.WriteFile\n6.Exit\n";
		cin >> choice;
		if(choice==1){
			myList->printAll();
		}
		else if(choice==2){
			cout << "Enter the word to insert:\n";
			cin >> word;
			    strlwr(word);
				myList->insertion(word);
		}
		else if(choice==3){
			cout << "Enter the word to delete:\n";
			cin >> word;
			    strlwr(word);
				myList->deletion(word);
		}
		else if(choice==4){
			cout << "Enter the word to search:\n";
			cin >> word;
            strlwr(word);
			myList->search2(word);
			if(myList->search2(word)==1){
                                        cout << "there is \n";
            }
            else{
                 cout << "there is no word like that \n";
                 }
		}
		else if(choice==5){
			myList->writefile (myList);
		}
		else if(choice==6){
			break;
		}
		else{
             cout << "read the menu correctly\n";
        }
	} 
}
