#include<stadio.h>
#include<string.h>
void frekanslariHesapla(char *metin){
	int freq[256]={0}; //TÜM ASCII KARAKTERLERÝ ÝCÝN SAYAC
	int i;
	
	for(int i=0; metin[i] !='\0'; i++){
		freq[(unsigned char)metin[i]]++;
	}
	printf("Karakter frekanslari:\n");
	for(i=0; i<256; i++){
		if(freq[i] > 0){
			printf("%c: %d\n", i, freq[i]);
		}
	}
}

int main(){
	char metin[100];
    printf("Bir metin giriniz: ");
    gets(metin);
    frekanslariHesapla(metin);
	
	return 0;
}

