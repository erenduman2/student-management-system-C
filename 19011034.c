#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	int a;
	int b;
	struct node *next;
	struct node *prev;
};

typedef struct ders{
	char kod[50];
	char adi[50];
	int kredi;
	int kontenjan;	
	struct ders *next;
	int *ogrenciler;
}ders;

typedef struct ogrenci{
	int numara;
	char ad[15];
	char soyad[10];
	int ders_sayisi;
	int top_kredi;
	struct ogrenci *next;
	struct ogrenci *prev;
}ogrenci;

int ogrenci_ekle();
int ogrenci_sil();
int ders_ekle();
int ders_sil();
int kayit_yap();
int kayit_sil();
void print_menu();
void print_menu2();
int artan_sira();
ogrenci* strc_sirala();
void ogr_sirala();
void dosyayakaydet();
void dosyayakaydet2();
void ogrkayit();
void siniflist();
void proglist();
int ogroku();
int dersoku();
int kontrol();
int kontrol2();

int main(){
	int secim=1, i=0;
	ogrenci *og=NULL;
	ders *der=NULL;
	char *kod;
	int no;
	int cnt=1;
	int max_kredi, max_ders;
	kod=(char*)malloc(30*sizeof(char));
	
	printf("NOT:Program, gonderdigim ogrenciler.txt ve dersler.txt dosyalarindaki verileri okuyarak calismaya baslayacaktir.\nYapilan yeni islemler de ogrenci ders kayit dosyasinin sonuna 1000,1001.. id'leri ile kaydedilecektir.\n\n");

	printf("Bir ogrencinin alabilecegi maksimum kredi ve ders sayisiniz giriniz:");
	scanf("%d %d", &max_kredi ,&max_ders); //maksimum ders sayisinda sinir koyulacak.
	

	ogroku(&og);
	og=strc_sirala(og, artan_sira);
	dersoku(&der);	
	
	
	
	while(secim!=0){
		print_menu();
		scanf("%d", &secim);
		if(secim==1){
			ogrenci_ekle(&og, og);
			og=strc_sirala(og, artan_sira);
		}
		if(secim==2){
			ogrenci_sil(&og, og);
			og=strc_sirala(og, artan_sira);
		}
		if(secim==3){
			ders_ekle(&der, der);
			dosyayakaydet(der, "Dersler.txt");
		}
		if(secim==4){
			cnt=ders_sil(&der, der, cnt, &og, og);
			dosyayakaydet(der, "Dersler.txt");
		}
		if(secim==5){
			cnt=kayit_yap(&og, og, der, &der, cnt, max_kredi, max_ders);
		}
		if(secim==6){
			cnt=kayit_sil(&og, og, der, &der, cnt);
		}
		if(secim < 0 || secim > 6){
			printf("Lutfen 0 ve 6 arasinda bir giris yapiniz..!\n");
		}
	}
	dosyayakaydet2(og, "Ogrenciler.txt");
	secim=1;
	while(secim!=0){
		print_menu2();
		scanf("%d", &secim);
		if(secim==1){
			printf("Sinif listesini cikarmak istediginiz dersin kodunu giriniz:\n");
			scanf("%s", kod);
			siniflist(kod, der);
		}
		if(secim==2){
			printf("Programini cikarmak istediginiz ogrencinin numarasini giriniz:\n");
			scanf("%d", &no);
			proglist(no,der);
		}
		if(secim < 0 || secim > 2){
			printf("Lutfen 0 ve 2 arasinda bir giris yapiniz..!\n");
		}
	}
	
	return 0;
}

int kontrol2(){
	FILE *fp;
	fp = fopen("Ogrenciler.txt", "r");
	char c;
	c = fgetc(fp);
	if(c==-1){
		printf("Ogrenciler belgeniz bos oldugu icin ogrenci eklenememistir..\n");
		return -1;
	}
	else{
		return 0;
	}
}

int kontrol(){
	FILE *fp;
	fp = fopen("Dersler.txt", "r");
	char c;
	c = fgetc(fp);
	if(c==-1){
		printf("Dersler belgeniz bos oldugu icin ogrenci eklenememistir..\n");
		return -1;
	}
	else{
		return 0;
	}
}
int dersoku(ders **dr){
	FILE *fp;
	fp = fopen("Dersler.txt", "r");
	ders *tmp;
	char buff[60];
	char *token;
	int i=0, k, knt;
	char s[30], tmp2[30]="";
	int q, w;
	tmp = (ders*)malloc(sizeof(ders));
	if(tmp==NULL){
		return -1;
	}
	knt=kontrol();
	if(knt==0){
		while(i==0){
			fscanf(fp, "%s", &buff);
			token=strtok(buff,",\0");
			strcpy(s,token);
			if(strcmp(s,tmp2)==0){
				i=1;
			}
			else{
				tmp = (ders*)malloc(sizeof(ders));
				strcpy(tmp->kod,s);
				token=strtok(NULL,",\0");
				strcpy(tmp->adi,token);
				token=strtok(NULL,",\0");
				q=atoi(token);
				tmp->kredi=q;
				token=strtok(NULL,",\0");
				q=atoi(token);
				tmp->kontenjan=q;
				strcpy(tmp2,s);
				tmp->ogrenciler=(int*)malloc((tmp->kontenjan)*sizeof(int));
				for(k=0; k<tmp->kontenjan; k++){
					tmp->ogrenciler[k]=0;				
				}
				tmp->next=*dr;
				*dr=tmp;
			}
		}
	}
	fclose(fp);
}
int ogroku(ogrenci **og){
	FILE *fp;
	fp = fopen("Ogrenciler.txt", "r");
	ogrenci *tmp;
	char buff[20];
	char *token;
	int s, tmp2, i=0, knt;
	tmp = (ogrenci*)malloc(sizeof(ogrenci));
	if(tmp==NULL){
		return -1;
	}
	knt=kontrol2();
	if(knt==0){
		while(i==0){
			fscanf(fp, "%s", &buff);
			token=strtok(buff,",\0");
			s=atoi(token);
			if(s==tmp2){
				i=1;
			}
			else{
				tmp = (ogrenci*)malloc(sizeof(ogrenci));
				token=strtok(NULL,",\0");
				strcpy(tmp->ad,token);
				token=strtok(NULL,",\0");
				strcpy(tmp->soyad,token);
				tmp->numara=s;
				tmp2=s;
				tmp->ders_sayisi=0;
				tmp->top_kredi=0;
				tmp->next=*og;
				*og=tmp;
			}
		}
	}
	fclose(fp);
}
void proglist(int no, ders *drr){
	char tmp[50];
	int i=0;
	
	itoa(no,tmp,10);
	strcat(tmp,"_DERSPROGRAMI.txt");
	FILE *fp=fopen(tmp, "a");
	while(drr!=NULL){
		for(i=0;i<drr->kontenjan;i++){
			if(drr->ogrenciler[i]==no){
				fputs(drr->kod,fp);
				fputc('\n',fp);
			}
		}
		drr=drr->next;
	}
	fclose(fp);
}
void siniflist(char *kd, ders *drr){
	char tmp[50];
	int found=0;
	int i=0, j=0;
	while(drr!=NULL && found==0){
		if(strcmp(drr->kod,kd)==0){
			found=1;
		}
		else{
			drr=drr->next;
		}
	}
	strcat(kd,".txt");
	FILE *fp=fopen(kd, "a");
	if(drr!=NULL){
		while(drr->ogrenciler[j]!=0 && j!=drr->kontenjan){
			j++;
		}
		while(i!=j){
			itoa(drr->ogrenciler[i],tmp,10);
			fputs(tmp,fp);
			fputc('\n',fp);
			i++;
		}
	}
	fclose(fp);
}
void ogrkayit(char kod[20], int no, char date[11], char durum[20], char dosyadi[20], int cnt){
	FILE *fp=fopen(dosyadi, "a");	
	int id=1000; 
	char tmp[20];
	
	id=id+cnt;
	itoa(id,tmp,10);
	fputs(tmp,fp);
	fputc(',',fp);
	fputs(kod,fp);
	fputc(',',fp);
	itoa(no,tmp,10);
	fputs(tmp,fp);
	fputc(',',fp);
	fputs(date,fp);
	fputc(',',fp);	
	fputs(durum,fp);
	fputc('\n',fp);	

	fclose(fp);
}
void dosyayakaydet(ders *dr, char dosyadi[20]){
	FILE *fp=fopen(dosyadi, "w");	
	char tmp[20];
	
	while(dr!=NULL){
		fputs(dr->kod,fp);
		fputc(',',fp);
		fputs(dr->adi,fp);
    	fputc(',',fp);
		itoa(dr->kredi,tmp,10);
		fputs(tmp,fp);
		fputc(',',fp);	
		itoa(dr->kontenjan,tmp,10);
		fputs(tmp,fp);
		fputc('\n',fp);	
		dr=dr->next;	
	}
	fclose(fp);
}
void dosyayakaydet2(ogrenci *og, char dosyadi[20]){
	FILE *fp=fopen(dosyadi, "w");	
	char tmp[20];
	
	while(og!=NULL){
		itoa(og->numara,tmp,10);
		fputs(tmp,fp);
		fputc(',',fp);
		fputs(og->ad,fp);
		fputc(',',fp);
		fputs(og->soyad,fp);
    	fputc(',',fp);
		itoa(og->top_kredi,tmp,10);
		fputs(tmp,fp);
		fputc(',',fp);
		itoa(og->ders_sayisi,tmp,10);
		fputs(tmp,fp);
		fputc('\n',fp);
		og=og->next;	
	}
	fclose(fp);
}


void print_menu(){
	printf("Ogrenci Eklemek Icin 1'i\nOgrenci Silmek Icin 2'yi\nDers Eklemek Icin 3'u\nDers Silmek Icin 4'u\nDerse Kayit Olmak Icin 5'i\nDers Kaydi Silmek Icin 6'yi\nCikmak icin 0'i Tuslayiniz.\n");
}
void print_menu2(){
	printf("Ders koduna gore sinif listesi cikarmak icin 1'i\nOgrenci numarasina gore ders programi cikarmak icin 2'yi\nCikmak icin 0'i tuslayiniz.\n");
}
int ogrenci_ekle(ogrenci **og, ogrenci *ogg){
	int found=0;
	ogrenci *tmp;
	tmp = (ogrenci*)malloc(sizeof(ogrenci));
	if(tmp==NULL){
		return -1;
	}
	printf("Ogrencinin numarasini, adini ve soyadini giriniz:");
	scanf("%d %s %s", &tmp->numara, &tmp->ad, &tmp->soyad);
	tmp->ders_sayisi=0;
	tmp->top_kredi=0;
	
	int p;
	p=tmp->numara;
		
	while(ogg!=NULL && found==0){
		if(ogg->numara==p){
			printf("Var olan bir ogrenciyi eklemeyemezsiniz..!\n");
			found=1;
		}
		ogg=ogg->next;
	}
	if(found==0){
		tmp->next=*og;
		*og=tmp;
		printf("Ogrenci ekleme basarili.\n");	
	}
	
	
	return 0;
}

int ogrenci_sil(ogrenci **og, ogrenci *ogg){
	int num;
	int found=0;	
	ogrenci *tmp;
	ogrenci *prev=NULL;
	tmp=*og;
	printf("Silinmesini istediginiz ogrencinin numarasini giriniz:");
	scanf("%d", &num);

	
	while(ogg!=NULL && found==0){
		if(ogg->numara==num){
			found=1;
		}
		ogg=ogg->next;
	}	
	
	if(found==0){
		printf("Var olmayan bir ogrenciyi silemezsiniz..!\n");
	}
	
	else{
		found=0;
		while(!found && tmp!=NULL){
			if(tmp->numara==num){
				found=1;
				if(prev==NULL){
					*og = tmp->next;
				}
				else{
					prev->next = tmp->next;
				}
				free(tmp);
			}
			prev=tmp;
			tmp=tmp->next;
		}
		printf("Ogrenci silme basarili.\n");
	}
	
	return found;
}

int ders_ekle(ders **dr, ders *drr){
	int i, found=0;
	ders *tmp;
	tmp = (ders*)malloc(sizeof(ders));
	if(tmp==NULL){
		return -1;
	}
	printf("Dersin kodunu, adini, kredisini ve kontenjanini giriniz:");
	scanf("%s %s %d %d", &tmp->kod, &tmp->adi, &tmp->kredi, &tmp->kontenjan);
	tmp->ogrenciler=(int*)malloc((tmp->kontenjan)*sizeof(int));
	for(i=0;i<tmp->kontenjan;i++){
		tmp->ogrenciler[i]=0;
	}
	char p[50];
	strcpy(p,tmp->kod);
	
	while(drr!=NULL && found==0){
		if(strcmp(drr->kod,p)==0){
			printf("Var olan bir dersi eklemeyemezsiniz..!\n");
			found=1;
		}
		drr=drr->next;
	}
	if(found==0){
		tmp->next=*dr;
		*dr=tmp;	
		printf("Ders ekleme basarili.\n");
	}
	
	return 0;
}

int ders_sil(ders **dr, ders *drr, int cnt, ogrenci **og, ogrenci *ogg){
	char kod[50];
	int found1=0, found2=0;	
	int found=0;	
	ders *tmp;
	ders *prev=NULL;
	ogrenci *tmp2;
	tmp=*dr;
	int i=0;
	char date[20];
	printf("Silinmesini istediginiz dersin kodunu ve tarihi giriniz:");
	scanf("%s %s", &kod, &date);
	while(drr!=NULL && found1==0){
		if(strcmp(drr->kod,kod)==0){
			found1=1;
		}
		else{
			drr=drr->next;
		}
	}
	if(found1==0){
		printf("Var olmayan bir dersi silemezsiniz..!\n");
	}
	else{
		while(drr->ogrenciler[i]!=0 && drr!=NULL){
			found2=0;
			tmp2=*og;
			ogrkayit(kod, drr->ogrenciler[i], date, "Ders Kapandi", "OgrenciDersKayit.txt", cnt);	
			while(tmp2!=NULL && found2==0){
			if(tmp2->numara==drr->ogrenciler[i]){
				found2=1;
				tmp2->ders_sayisi-=1;
				tmp2->top_kredi-=drr->kredi;
			}
			else{
				tmp2=tmp2->next;	
				ogg=ogg->next;
			}
		}
		i++;
		cnt++;
		}
		while(!found && tmp!=NULL){
			if(strcmp(tmp->kod,kod)==0){
				found=1;
				if(prev==NULL){
					*dr = tmp->next;
				}
				else{
					prev->next = tmp->next;
				}
				free(tmp);
			}
			prev=tmp;
			tmp=tmp->next;
		}
		printf("Ders silme basarili.\n");
	}
	return cnt;
}

int kayit_yap(ogrenci **og, ogrenci *ogg, ders *drr, ders **dr, int cnt, int m_kredi, int m_ders){
	int found1=0, found2=0;
	int num;
	int i,k;
	char kod[50];
	ders *tmp;
	ogrenci *tmp2;
	char date[20];
	tmp=*dr;
	tmp2=*og;
	
	printf("Sirasiyla ogrenci numaranizi, kayit olmak istediginiz dersin kodunu ve tarihi giriniz\n");
	scanf("%d %s %s", &num, &kod, &date);
	
	while(ogg!=NULL && found1==0){
		if(ogg->numara==num) {
			found1=1;
		}
		else{
			tmp2=tmp2->next;	
			ogg=ogg->next;
		}
	}
	
	while(drr!=NULL && found2==0){
		if(strcmp(drr->kod,kod)==0) {
			found2=1;
		}
		else{
			drr=drr->next;
			tmp=tmp->next;
		}
	}
	
	
	if(found1==0 || found2==0){
		printf("Lutfen gecerli bir ogrenci numarasi veya ders kodu giriniz..!\n");
	}
	else if((tmp2->top_kredi)+(tmp->kredi)>m_kredi || tmp2->ders_sayisi == m_ders){
		printf("Alabileceginiz maksimum krediniz veya ders sayiniz doldugu icin derse kayit olamazsiniz..!\n");
	}
	else{
		i=0;
		while(tmp->ogrenciler[i]!=0 && i<tmp->kontenjan){
			i++;
		}
		k=0;
		while(drr->ogrenciler[k]!=num && k<drr->kontenjan){
			k++;
		}
		if(i >= tmp->kontenjan){
			printf("Dersin kontenjani dolmustur..!\n");
		}
		else if(k != drr->kontenjan){
			printf("Derse zaten kayitli oldugunuz icin kayit yaptiramazsiniz..!\n");
		}
		else{
			tmp->ogrenciler[i] = num;
			tmp2->ders_sayisi+=1;
			tmp2->top_kredi+=drr->kredi;
		
			tmp->ogrenciler;
			ogr_sirala(tmp->ogrenciler, tmp->kontenjan);
			ogrkayit(kod, num, date, "Kayitli", "OgrenciDersKayit.txt", cnt);
			printf("Kayit basarili.\n");
			cnt++;
		}
	}	
	return cnt;	
}

int kayit_sil(ogrenci **og, ogrenci *ogg, ders *drr, ders **dr, int cnt){
	int found1=0, found2=0, found3=0;
	int num;
	int i,k;
	char kod[50];
	ders *tmp;
	ogrenci *tmp2;
	char date[20];
	tmp=*dr;
	tmp2=*og;
	
	printf("Sirasiyla ogrenci numaranizi, kaydinizi silmek istediginiz dersin kodunu ve tarihi giriniz\n");
	scanf("%d %s %s", &num, &kod, &date);
	
	while(ogg!=NULL && found1==0){
		if(ogg->numara==num) {
			found1=1;
		}
		else{
			ogg=ogg->next;
			tmp2=tmp2->next;
		}
	}
	
	while(drr!=NULL && found2==0){
		if(strcmp(drr->kod,kod)==0) {
			found2=1;
		}
		else{
			drr=drr->next;
			tmp=tmp->next;
		}
	}
	
	if(found1==0 || found2==0){
		printf("Lutfen gecerli bir ogrenci numarasi veya ders kodu giriniz..!\n");
	}
	else{
		for(i=0;i<drr->kontenjan;i++){
			if(drr->ogrenciler[i]==num){
				found3=1;
			}
			else{
				i++;
			}
		}
		i=0;
		while(drr->ogrenciler[i]!=num && i<drr->kontenjan){
			i++;
		}
			
		if(i==drr->kontenjan){
			printf("Girdiginiz ogrenci derse kayitli degildir..!\n");
		}
		else{
			for(k=i; k<(tmp->kontenjan); k++){
				tmp->ogrenciler[i]=tmp->ogrenciler[i+1];
				if(k==(tmp->kontenjan)-1){
				tmp->ogrenciler[i+1]=0;
				}	
			}
			tmp2->ders_sayisi-=1;
			tmp2->top_kredi-=drr->kredi;
			ogr_sirala(tmp->ogrenciler, tmp->kontenjan);	
			ogrkayit(kod, num, date, "Sildi", "OgrenciDersKayit.txt", cnt);
			cnt++;
		}
	}
	return cnt;
}

int artan_sira(int first,int second){
	return first<second;
}


ogrenci* strc_sirala(ogrenci* head,int (*Sort_Condition)(int,int)){
	if(head == NULL || head->next == NULL)
        return head;

    int max = head->numara;
    ogrenci *prev = head;
    ogrenci *to_move = NULL;
    ogrenci *tmp = head->next;

   
    while(tmp != NULL) {
        if(Sort_Condition(tmp->numara,max)) {
            max = tmp->numara;
            to_move = prev;
        }
        prev = tmp;
        tmp = tmp->next;
    }


    if(to_move == NULL) {
        head->next = strc_sirala(head->next,Sort_Condition);
        return head;
    }

    prev = to_move;
    to_move = prev->next;
    prev->next = prev->next->next;
    to_move->next = strc_sirala(head,Sort_Condition);
    return to_move;
	
}

void ogr_sirala(int *array, int size){
    int i,j,temp;
    int count=0;
    for(i=0;i<size;i++){
    	if(array[i]==0){
    		count++;
		}
	}
	for(i=1;i<size-count;i++){
		for(j=0;j<size-count-i;j++){
			if(array[j]>array[j+1]){   
				temp=array[j+1];
                array[j+1]=array[j];
                array[j]=temp;
            }   
        }       
    }
}


