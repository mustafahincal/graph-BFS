#include<stdio.h>
#include<stdlib.h>

int matris[9][9];
int queue[9],front=-1,rear=-1;

struct Node{
	int nodeNo;
	struct Node *next;
};

struct Node *temp;

struct Node row[9];

void initializeList(){
	int i;
	for(i=0;i<9;i++){
		row[i].nodeNo = -1;
		row[i].next = NULL;
	}
}

int controlList = 0;
void matrixToList(){
	for(int i=0;i<9;i++){
		row[i].nodeNo = i;
		temp = &row[i];
		for(int j=0;j<9;j++){
			if(matris[i][j] == 1){
				struct Node *adjNode = (Node*)malloc(sizeof(Node));
				adjNode -> nodeNo = j;
				adjNode -> next = NULL;
				while(temp -> next != NULL){
					temp = temp -> next;
				}
				temp -> next = adjNode;
			}
		}
	}
	controlList = 1;
	printf("\n Matris Listeye Cevrildi!\n");
}

void displayList(){
	for(int i=0;i<9;i++){
		temp = &row[i];
		printf("\n %d . Dugum Komsulari",i);
		while(temp != NULL){
			if(temp -> next == NULL){
				printf(" %d  ",temp -> nodeNo);
			}else{
				printf(" %d -> ",temp -> nodeNo);
			}
			temp = temp -> next;
		}
	}
	printf("\n\n");
}

void enQueue(int veri){
	
	if(rear==9){
		printf("\n Kuyruk Dolu");
	}
	else{
		if(front==-1)
		{
			front=0;
		}
		rear=rear+1;
		queue[rear]=veri;
	}
}


int deQueue(){
	if(front == -1 || front>rear)
	{
		printf("\n Kuyruk Bos");
		front =-1;
		rear=-1;
		return -1;
	}
	else
	{
		int removed = queue[front];
		front = front+1;
		return removed;
	}
}

bool isQueueEmpty(){
	if(front == -1 || front>rear){
		front = -1;
		rear = -1;
		return false;
	}else{
		return true;
	}
}

int color[9];
int pred[9];
int d[9];

// color ; 1=beyaz , 2=gri , 3=siyah
// pred ; -1=yok
// d ; -1=yok

void startBFS(){
	for(int i=0;i<9;i++){
		color[i] = 1;
		d[i] = -1;
		pred[i] = -1;
	}
	color[8] = 2;
	d[8] = 0;
	pred[8] = -1;
	
	enQueue(8);
	
	printf("----------------------------------------------------------------");
	printf("\n - Breath-First Search 8 numarali dugumden basladi!! ");
	printf("\n - 8 numarali dugum kuyruga eklendi.\n");
	
	while(isQueueEmpty()){
		
		printf("----------------------------------------------------------------");
		int adj;
		int u;
		u = deQueue();
		
		printf("\n - %d numarali dugum kuyruktan cikarildi.\n",u);
		
		temp = &row[u];
		temp = temp -> next;
		while(temp != NULL){
			
			printf("\n - %d numarali dugumunun %d numarali komsusu inceleniyor..",u,temp -> nodeNo);
		
			if(color[temp -> nodeNo] == 1){
				color[temp -> nodeNo] == 2;
				d[temp -> nodeNo] = d[u]+1;
				pred[temp -> nodeNo] = u;
				enQueue(temp -> nodeNo);
				
				printf("\n - %d numarali dugum kuyruga eklendi.",temp -> nodeNo);
				printf("\n - %d numarali dugumunun rengi gri yapildi",temp -> nodeNo);
				printf("\n - %d numarali dugum adim sayisi : %d",temp -> nodeNo,d[temp -> nodeNo]);
				printf("\n - %d numarali dugumun atasi : %d",temp -> nodeNo,pred[temp -> nodeNo]);
			}else{
				printf("\n - %d numarali dugum rengi beyaz degil daha once ziyaret edilmis.",temp -> nodeNo);
			}
			temp = temp -> next;
			printf("\n");
		}
		color[u] = 3;
		printf("\n - %d numarali dugumunun tum komsulari ziyaret edildi.",u);
		printf("\n - %d numarali dugumunun rengi siyah yapildi.",u);
		printf("\n\n");
	}
	printf("----------------------------------------------------------------");
	printf("\n Breath-First Search tamamlanmistir!!\n\n");
	
}

int controlMatris = 0;
void readFile(int matris[9][9]){
	
	FILE *file;
	file=fopen("graf.txt","r");
	if(file==NULL)
	{
		printf("\n Dosya bulunamadi");
	}else{
		while(!feof(file))
		{
			for(int i=0;i<9;i++){
				for(int j=0;j<9;j++){
					fscanf(file,"%d",&matris[i][j]);
				}
			}	
		}
		controlMatris = 1;
		printf("\n Okuma islemi tamamlandi.\n");
	}
	fclose(file);
}

void displayMatris(int matris[9][9]){
	if(controlMatris != 0){
		printf("\n -------------------------\n");
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				printf(" %d ",matris[i][j]);
			}
			printf("\n");
		}
		printf(" -------------------------\n");
	}else{
		printf("\n Once grafi dosyadan okumalisiniz..\n");
	}
}

int main(){
	int choice=1;
	initializeList();
	
	while(choice!=0){
		
		printf("\n 0 - Islemi sonlandir");
		printf("\n 1 - Dosyadan matrisi oku");
		printf("\n 2 - Matrisi goster");
		printf("\n 3 - Matrisi Listeye cevir");
		printf("\n 4 - Listeyi goster");
		printf("\n 5 - Breath First Search aramasini baslat");
		printf("\n\n Islem seciniz : ");
		scanf("%d",&choice);
		printf("\n");
		
		switch(choice){
			case 1 : 
				readFile(matris);
				break;
			case 2 : 
				displayMatris(matris);
				break;
			case 3 :
				if(controlMatris != 0){ 
					matrixToList();
				}else{
					printf("\n Once grafi dosyadan okumalisiniz!!\n");
				}
				break;
			case 4 : 
				if(controlMatris != 0){
					displayList();
				}else{
					printf("\n Once grafi dosyadan okumali ve Matrisi Listeye cevirmelisiniz!!\n");
				}
				break;		
			case 5 : 
				if(controlMatris != 0){
					startBFS();
				}else{
					printf("\n Once grafi dosyadan okumali ve Matrisi Listeye cevirmelisiniz!!\n");
				}
				break;	
			default : 
				printf("\n\n Hatali numara girdiniz.\n");			
		}
	}
	return 0;
}
