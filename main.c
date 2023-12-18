#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

int ihtiyac_sayisi = 10;
int i;
char *ihtiyaclar[20] = {"TOKLUK", "UYKU", "SEVGI", "SOSYALLIK", "SAGLIK", "EGITIM", "HIJYEN", "TUVALET", "EGLENCE", "SU IHTIYACI"};
int duzey[] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
char *istek_secenekleri[35] = {"Lunapark", "Aileyle Oyun", "Telefondan | Tabletten Oyun", "Arkadaslarla Disari Cikmak"};
char *butun_yemekler[30] = {"Meyve", "Iskender", "Makarna", "Salata", "Fast Food", "Kuru-Pilav", "Et, Tavuk veya Balik", "Sebze Yemegi"};
float saat = 22.30;//gun icindeki saat her gun sifirlaniyor


int yemek_ye(char **yemekler, int *yemek_adetleri, int *toplam_yemek_sayi);
void uyu(int uyunan_saat_miktari);
void temizlen();
void sevil();
void sosyalles(char *istek);
void iyiles();
void okula_git();
void aile_egitimi();
void eglen(char **eglenceler, char *istek);
char* istek_uret(char **istek_secenekleri);
void tuvalete_git();
void dus_al();
void markete_git(char **yemekler);
int olum_kontrol();
void ihtVeDuzeyYazdir();
void duzeyYenile(char *ihtiyac, int miktar);


int main()
{
    char bebek_ismi[50];
    int bebek_yas;
    int oldu_mu = 0;
    //Bebek Ozellikleri
    srand(time(NULL));
    char  **yemek_cesitleri, **eglence_turleri;//yemek_cesitleri ve eglence_turleri kullanici tarafindan tanimlanmayacak rastgele yollanacak.
    //her gun sifirdan bir istek belirlenecek



    int yemek_sayisi = rand()%8 + 1;
    yemek_cesitleri = (char **)malloc(yemek_sayisi*sizeof(char *)); //Yemek seceneklerinden kac tanesini dahil edecek diye yemek sayisi kadar yer ayir ayiriyoruz.



    int ailenin_aralarindaki_iliski;//0-10 arasinda bir deger

    int aileni_sevme_oranin;//kullanici ilk basta kendi girebilir(karar verilecek) ona gore aktivitelerin etkileme orani degisecek




    int yemek_adetleri[8];
    for(i = 0; i < 8; i++){
        yemek_adetleri[i] = rand() % 5 + 1;
    }
    int kullanildi_mi[8] = {0};

    char *istek = istek_uret(istek_secenekleri);

    for(i = 0; i < yemek_sayisi; i++){
        int kontrol = rand()%8;
        if(!kullanildi_mi[kontrol]){
            yemek_cesitleri[i] = butun_yemekler[kontrol];
            kullanildi_mi[kontrol]++;
        }
        else
            i--;
    }

    printf("istek = %s\n", istek);
    oldu_mu = yemek_ye(yemek_cesitleri, yemek_adetleri, &yemek_sayisi);
    uyu(8);
    tuvalete_git();
    if(oldu_mu){
        printf("\n\n\t\tOLDUNUZ!!!!\n\n");
    }
    return 0;
}






void duzeyYenile(char *ihtiyac, int miktar){
    i = 0;
    while(1){
        if(!strcmp(*(ihtiyaclar + i), ihtiyac)){
            *(duzey + i) += miktar;
            if(*(duzey + i) >= 10)
                *(duzey + i) = 10;
            if(*(duzey + i) <= 0)
                *(duzey + i) = 0;
            break;
        }
        i++;
    }
}

void ihtVeDuzeyYazdir(){
    for(i = 0; i < ihtiyac_sayisi; i++){
        printf("%s -> %d\n", *(ihtiyaclar + i), *(duzey + i));
    }
}


int yemek_ye(char **yemekler, int *yemek_adetleri, int *toplam_yemek_sayi){
    printf("Lutfen hangi besin ile besleneceginizi seciniz:(Yanlarindaki numaralari yazarak onlari secebilirsiniz,orn. meyve icin 1) \n");
    int secim;
    for(i = 0; i < *toplam_yemek_sayi; i++){
        printf("%d) %s, adeti: %d\n", i+1, *(yemekler + i), *(yemek_adetleri + i));
    }
    printf("\nSeciminiz: ");
    scanf("%d", &secim);
    if(secim < *toplam_yemek_sayi + 1 && secim > 0){
        printf("%s yiyorsunuz...\n", *(yemekler + secim - 1));
        printf("Saat: %.2f -> %.2f\nYemekten kalan adet: %d -> %d\n", saat, saat + 1, *(yemek_adetleri + secim - 1), *(yemek_adetleri + secim - 1) - 1);
        saat += 1;
        *(yemek_adetleri + secim - 1) -= 1;
        printf("IHTIYACLAR\n----------\n");
        if(!strcmp(*(yemekler + secim - 1), "Meyve")){
            duzeyYenile( "TOKLUK", 1);
            duzeyYenile( "SAGLIK", 1);
            duzeyYenile( "TUVALET", 1);
        }
        if(!strcmp(*(yemekler + secim - 1), "Iskender")){
            duzeyYenile( "TOKLUK", 2);
            duzeyYenile( "TUVALET", 1);
        }
        if(!strcmp(*(yemekler + secim - 1), "Makarna")){
            duzeyYenile( "TOKLUK", 2);
            duzeyYenile( "TUVALET", 1);
        }
        if(!strcmp(*(yemekler + secim - 1), "Salata")){
            duzeyYenile( "TOKLUK", 2);
            duzeyYenile( "SAGLIK", 1);
            duzeyYenile( "TUVALET", 1);
        }
        if(!strcmp(*(yemekler + secim - 1), "Fast Food")){
            duzeyYenile( "TOKLUK", 2);
            duzeyYenile( "SAGLIK", -1);
            duzeyYenile( "TUVALET", 1);
        }
        if(!strcmp(*(yemekler + secim - 1), "Kuru-Pilav")){
            duzeyYenile( "TOKLUK", 2);
            duzeyYenile( "SAGLIK", 1);
            duzeyYenile( "TUVALET", 1);
        }
        if(!strcmp(*(yemekler + secim - 1), "Et, Tavuk veya Balik")){
            duzeyYenile( "TOKLUK", 2);
            duzeyYenile( "SAGLIK", 1);
            duzeyYenile( "TUVALET", 1);
        }
        if(!strcmp(*(yemekler + secim - 1), "Sebze Yemegi")){
            duzeyYenile( "TOKLUK", 1);
            duzeyYenile( "SAGLIK", 1);
            duzeyYenile( "TUVALET", 1);
        }
        duzeyYenile("UYKU", 1);
        ihtVeDuzeyYazdir(ihtiyaclar, duzey);
    }
    else{
        printf("Yanlis bir secim yaptiniz lutfen dogru secim yaptiginiza emin olunuz!\n");
        return yemek_ye(yemekler, yemek_adetleri, toplam_yemek_sayi);
    }

    return 0;
}

void uyu(int uyunan_saat_miktari){
    printf("Yataga Yattin, uyuyorsun...\n\n");
    int i, sayac = 1;
    printf("SAAT: %.2f\n", saat);
    for(i = 0; i < uyunan_saat_miktari; i++){

        Sleep(1000);
        if(sayac % 2){
            duzeyYenile("TOKLUK", -1);
            duzeyYenile("TUVALET", 1);
        }
        if(sayac % 4){
            duzeyYenile("UYKU", -5);
        }
        saat += 1;
        if(saat >= 24)
            saat -= 24;

        sayac++;
    }
    duzeyYenile( "HIJYEN", -2);
    printf("\n\t\t\t\tYeni Gune Gunaydin.\n\nBugunku ihtiyaclarin:\n");
    printf("Saat: %.2f\n\n", saat);
    ihtVeDuzeyYazdir(ihtiyaclar, duzey);
}

void tuvalete_git(){
    printf("\n\nTuvalete gittin...\n\n");
    Sleep(2500);
    duzeyYenile( "TUVALET", -7);
    duzeyYenile( "HIJYEN", -3);
    ihtVeDuzeyYazdir(ihtiyaclar, duzey);
}

char* istek_uret(char **istek_secenekleri){
    srand(time(NULL));
    return istek_secenekleri[rand()%4];
}

