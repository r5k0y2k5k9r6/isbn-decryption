/*
 ============================================================================
 Name        : decryption.c
 Author      : Rimi
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
	char code[15];
	int checkdigits10(int *num);
	int checkdigits13(int *num);
	int num[13];
	int prefix;
	int pub;
	char country[10][26]={"English","English","French","German","Japan",
			"Russia or ex Soviet Union","Other region","China","country8x","country9x"};
	char country8x[10][36]={"Czech or Slovakia","India","Norway",
			"Poland","Spain","Brazil","Serbia","Denmark","Italian","Korea"};
	char country9x[10][24]={"Dutch","Sweden","International NGO or EU","India","Dutch",
			"Other region","Other region","Other region","Other region","Other region"};
	char publisher0[20][30]={"HarperCollins","Unassigned","Collier Macmillan",
			"Holt,Rinehart and Winston","Unwin Hyman","Oliver & Boyd","HarperCollins","McGraw Hill",
			"Pergamon Press","Random House","HMSO","HMSO","Academic Press","John Wiley & Sons",
			"Penguin Books","Harcourt Brace Jovanovich","US Government Printing Office",
			"Thomas Nelson","Unassigned","Oxford University Press"};
	char publisher1[8][23]={"Unassigned","Pyramid Books","Berkley Publishing","Unassigned",
			"Popular Library","DAW Books","Celestial Publications","Scholastic Books"};
	char publisher2[11][51]={"Unknown","Hachette Education","Belin","Larousse","Bordas",
			"Slatkine","Michelin","Gallimard Education","Flammarion","Nathan","Dunod"};
	char publisher3[5][11]={"Unknown","Unknown","Unassigned","Unknown","Unassigned"};
	char publisher4[20][32]={"Iwanami Shoten","Obunsha","The Asahi Shimbun Company","KAISEI-SHA",
			"KADOKAWA CORPORATION","Gakken Holdings Company","Kodansha","SHUFUNOTOMO","Shueisha",
			"SHOGAKUKAN","SHINCHOSHA","Zen-On Music","CHUOKORO-SHINSHA","University of Tokyo Press",
			"NHK Publishing","Hayakawa Publishing Corporation","Bungeishunju","National Printing Bureau",
			"Meijitoshoshuppan Corporation","Tokuma Shoten"};
	char publisher7[5][26]={"Gateway Books","People's Publishing House",
			"People s Literature","Science Press","Higher Education Press"};
	printf("Input your ISBN code,and enter.\n");
	fgets(code,15,stdin);
	/*字数エラー*/
	if(strlen(code)!=14 && strlen(code)!=11){
		printf("Error.\nThis code is incorrect in the number of characters.\n");
		return (-1);
	}
	else{
		/*codeをnumに変換*/
		int i=0;
		while(code[i]!='\n'){
			if(code[i]=='x'||code[i]=='X'){
				num[i]=10;
			}
			else{num[i]=code[i]-'0';}
			i++;
		}
		switch(strlen(code)){
		int j,k;
		case 11:
			/*文字エラー*/
			for(j=0;j<9;j++){
				if(!isdigit(code[j])){
					printf("Error.\nThe 1st to 9th characters of this code includes non-numeric characters.\n");
					return(-1);
				}
			}
			if(!isdigit(code[9])&&(code[9])!='X'&&(code[9])!='x'){
				printf("Error.\nThe last character of this code is not a number or 'X' or 'x'.\n");
				return (-1);
			}
			/*チェックディジットエラー*/
			else if(checkdigits10(&num[0])){
				printf("Error.\nThis code is not exist.\n");
				return(-1);
			}
			break;
		case 14:
			/*文字エラー*/
			for(k=3;k<13;k++){
				if(!isdigit(code[k])){
					printf("Error.\nThis code includes non-numeric characters.\n");
					return(-1);
				}
			}
			prefix=num[0]*100+num[1]*10+num[2];
			if(prefix!=978&&prefix!=979){
				printf("Error.\nISBN-13 is a code that starts with '978' or '979'.\n");
				return (-1);
			}
			/*チェックディジットエラー*/
			else if(checkdigits13(&num[0])){
				printf("Error.\nThis code is not exist.\n");
				return(-1);
			}
			break;
		}
	}
	/*国名、出版社決定*/
	switch(strlen(code)){
	case 11:/*ISBN-10の時*/
		if(num[0]==8){/*8xxxxxxxxxのコードのもの*/
			printf("%s,Unknown.\n",country8x[num[1]]);
			break;
		}
		else if(num[0]==9){/*9xxxxxxxxxのコードのもの*/
			printf("%s,Unknown.\n",country9x[num[1]]);
			break;
		}
		else{
			printf("%s,",country[num[0]]);
			switch(num[0]){
			case 0:/*0xxxxxxxxxのコードのもの*/
				pub=num[1]*10+num[2];
				if(pub>=20){printf("Unknown.\n");
				break;
				}
				printf("%s.\n",publisher0[pub]);
				break;
			case 1:/*1xxxxxxxxxのコードのもの*/
				pub=num[1]*10+num[2];
				if(pub>=8){printf("Unknown.\n");
				break;
				}
				printf("%s.\n",publisher1[pub]);
				break;
			case 2:/*2xxxxxxxxxのコードのもの*/
				pub=num[1]*10+num[2];
				if(pub>=11){printf("Unknown.\n");
				break;
				}
				printf("%s.\n",publisher2[pub]);
				break;
			case 3:/*3xxxxxxxxxのコードのもの*/
				pub=num[1]*10+num[2];
				if(pub>=5){printf("Unknown.\n");
				break;
				}
				printf("%s.\n",publisher3[pub]);
				break;
			case 4:/*4xxxxxxxxxのコードのもの*/
				pub=num[1]*10+num[2];
				if(pub>=20){printf("Unknown.\n");
				break;
				}
				printf("%s.\n",publisher4[pub]);
				break;
			case 5:/*5xxxxxxxxxのコードのもの*/
				printf("Unknown.\n");
				break;
			case 6:/*6xxxxxxxxxのコードのもの*/
				printf("Unknown.\n");
				break;
			case 7:/*7xxxxxxxxxのコードのもの*/
				pub=num[1]*10+num[2];
				if(pub>=5){printf("Unknown.\n");
				break;
				}
				printf("%s.\n",publisher7[pub]);
				break;
			}
			break;
		}
	case 14:/*ISBN-13の時*/
		switch(prefix){
		case 978:/*978xxxxxxxxxxのコードのもの*/
			if(num[3]==8){/*9788xxxxxxxxxのコードのもの*/
				printf("%s,Unknown.\n",country8x[num[4]]);
				break;
			}
			else if(num[3]==9){/*9789xxxxxxxxxのコードのもの*/
				printf("%s,Unknown.\n",country9x[num[4]]);
				break;
			}
			else{
				printf("%s,",country[num[3]]);
				switch(num[3]){
				case 0:/*9780xxxxxxxxxのコードのもの*/
					pub=num[4]*10+num[5];
					if(pub>=20){printf("Unknown.\n");
					break;
					}
					printf("%s.\n",publisher0[pub]);
					break;
				case 1:/*9781xxxxxxxxxのコードのもの*/
					pub=num[4]*10+num[5];
					if(pub>=8){printf("Unknown.\n");
					break;
					}
					printf("%s.\n",publisher1[pub]);
					break;
				case 2:/*9782xxxxxxxxxのコードのもの*/
					pub=num[4]*10+num[5];
					if(pub>=11){printf("Unknown.\n");
					break;
					}
					printf("%s.\n",publisher2[pub]);
					break;
				case 3:/*9783xxxxxxxxxのコードのもの*/
					pub=num[4]*10+num[5];
					if(pub>=5){printf("Unknown.\n");
					break;
					}
					printf("%s.\n",publisher3[pub]);
					break;
				case 4:/*9784xxxxxxxxxのコードのもの*/
					pub=num[4]*10+num[5];
					if(pub>=20){printf("Unknown.\n");
					break;
					}
					printf("%s.\n",publisher4[pub]);
					break;
				case 5:/*9785xxxxxxxxxのコードのもの*/
					printf("Unknown.\n");
					break;
				case 6:/*9786xxxxxxxxxのコードのもの*/
					printf("Unknown.\n");
					break;
				case 7:/*9787xxxxxxxxxのコードのもの*/
					pub=num[4]*10+num[5];
					if(pub>=5){printf("Unknown.\n");
					break;
					}
					printf("%s.\n",publisher7[pub]);
					break;
				}
			}
			break;
		case 979:/*979xxxxxxxxxxのコードのもの*/
			if(num[3]==1){/*9791xxxxxxxxxのコードのもの*/
				switch(num[4]){
				case 0:/*97910xxxxxxxxのコードのもの*/
					printf("French,Unknown.\n");
					break;
				case 1:/*97911xxxxxxxxのコードのもの*/
					printf("Korea,Unknown.\n");
					break;
				case 2:/*97912xxxxxxxxのコードのもの*/
					printf("Italy,Unknown.\n;");
					break;
				default:/*97913xxxxxxxx〜97919xxxxxxxxのコードのもの*/
					printf("Unassigned.\n");
					break;
				}
			}
			else{/*9792xxxxxxxxx〜9799xxxxxxxxxのコードのもの*/
				printf("Unassigned.\n");
				break;
			}
			break;
		}
		break;
	}
	return(0);
}

/*ISBN-10のチェックディジットの適正チェック*/
int checkdigits10(int *num){
	int a=0,l=10;
	while(l>1){
		a+=*num*l;
		num++,l--;
	}
	if((11-(a%11))!=*num){
		return(-1);
	}
	return(0);
}
/*ISBN-13のチェックディジットの適正チェック*/
int checkdigits13(int *num){
	int b=0,n=1;
	while(n<13){
		switch(n%2){
		case 0:b+=*num*3;
		break;
		case 1:b+=*num*1;
		break;
		}
		num++,n++;
	}
	if((10-(b%10))!=*num){
		return(-1);
	}
	return(0);
}
