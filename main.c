#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>

int ihtiyac_sayisi = 10;
int bakiye=100;
int i;
char *ihtiyaclar[20] = {"TOKLUK", "UYKU", "SEVGI", "SOSYALLIK", "SAGLIK", "EGITIM", "HIJYEN", "TUVALET", "EGLENCE", "SU IHTIYACI"};
int duzeyler[] = {3, 0, 5, 5, 5, 5, 5, 5, 5, 7};
char *istek_secenekleri[35] = {"Lunapark", "Aileyle Oyun", "Telefondan | Tabletten Oyun", "Arkadaslarla Disari Cikmak"};
char *butun_yemekler[30] = {"Meyve", "Iskender", "Makarna", "Salata", "Fast Food", "Kuru-Pilav", "Et, Tavuk veya Balik", "Sebze Yemegi"};
char *bes_canta[40];
int bes_cantadaki_yiyecek_sayisi = 0;
float saat = 8.30;//gun icindeki saat her gun sifirlaniyor
int buzdolabindaki_toplam_yemek;
int susuz_gun = 0, uykusuz_gun = 0, tuvaletsiz_gun = 0, ac_gun = 0, tok_gun = 0;


int yemek_ye(char **yemekler, int *yemek_adetleri, int *toplam_yemek_sayi);
void su_ic();
void uyu(int uyunan_saat_miktari);
void temizlen();
void sevil();
void sosyalles();
void iyiles();
void okula_git(char **yemekler,int *toplamYemek, int *yemek_adetleri);
void beslenme_cantasi(char **yemekler, int *toplamYemek, int *yemek_adetleri);
void eglen();
void tuvalete_git();
void temizlen();
void dus_al();
void el_yika();
void markete_git(char **yemekler, int *toplamYemek, int *yemekSayilari);
void olum_kontrol();
void ihtVeDuzeyYazdir();
void duzeyYenile(char *ihtiyac, int miktar);
void dolapKontrol(char **yemekler, int *toplamYemek, int *yemekSayilari, int yemek, int adet);
void saatKontrol(float miktar);
void buzdolabiYazdir(char **yemekler, int *toplamYemek, int *yemek_adetleri);
int elemanCikar(char **dizi, char *eleman, int dizinin_eleman_sayisi);
void fonklari_yaz();


int main()
{
    char isim[50];
    int bebek_yas;
    int secim, uyku_saati;
    //Bebek Ozellikleri
    srand(time(NULL));
    char  **yemek_cesitleri;

    int yemek_sayisi = rand()%8 + 1;
    yemek_cesitleri = (char **)malloc(yemek_sayisi*sizeof(char *)); //Yemek seceneklerinden kac tanesini dahil edecek diye yemek sayisi kadar yer ayir ayiriyoruz.

    int yemek_adetleri[8];
    for(i = 0; i < yemek_sayisi; i++){
        yemek_adetleri[i] = rand() % 5 + 1;
        buzdolabindaki_toplam_yemek += yemek_adetleri[i];
    }
    int kullanildi_mi[8] = {0};

    for(i = 0; i < yemek_sayisi; i++){
        int kontrol = rand()%8;
        if(!kullanildi_mi[kontrol]){
            yemek_cesitleri[i] = butun_yemekler[kontrol];
            kullanildi_mi[kontrol]++;
        }
        else
            i--;
    }
    printf("Oyuna hosgeldiniz!!!!!\n");
    printf("Oncelikle karakterinizin adini ve yasini girerek baslayalim.\n");
    printf("Adiniz: ");
    gets(isim);
    printf("Yasiniz(4-18): ");
    scanf("%d", &bebek_yas);
    getchar();
    Sleep(1000);
    printf("Oyuna baslayalim o zaman. Oyunumuzun amaci karakterinizin ihityaclarini goz onunda bulundurarak hayatta tutmaktir. Iyi oyunlar!\n\n\n\n\n");
    Sleep(3000);

    while(1){
        printf("\t\t\t\t\t\t\tSAAT: %.2f\n", saat);
        printf("------------------Guncel Ihtiyaclar------------------\n\n");
        ihtVeDuzeyYazdir();
        printf("\n\n------------------Yapabilecegin secenekler------------------\n");
        Sleep(3000);
        fonklari_yaz();
        printf("Hangi aksiyonu yapmak istiyorsunuz?  ");
        scanf("%d", &secim);
        getchar();
        switch(secim){
        case 1:yemek_ye(yemek_cesitleri, yemek_adetleri, &yemek_sayisi);
                break;
        case 2:printf("Kac saat uyumak istiyorsunuz!");
                scanf("%d", &uyku_saati);
                uyu(uyku_saati);
                break;
        case 3:temizlen();
                break;
        case 4:sevil();
                break;
        case 5:sosyalles();
                break;
        case 6:iyiles();
                break;
        case 7:okula_git(yemek_cesitleri, &yemek_sayisi, yemek_adetleri);
                break;
        case 8:eglen();
                break;
        case 9:tuvalete_git();
                break;
        case 10:markete_git(yemek_cesitleri, &yemek_sayisi, yemek_adetleri);
                break;
        case 11:su_ic();
                break;
        default:printf("\nYanlis bir secim yaptiniz. Yeniden deneyiniz!\n\n");
                system("pause");
                continue;
        }
    }

    return 0;
}

void olum_kontrol(){
    while(i < ihtiyac_sayisi){
        if(!strcmp(*(ihtiyaclar + i), "TOKLUK")){
            if(duzeyler[i] == 10){
                tok_gun++;
                if(tok_gun == 2){
                    printf("\t\t\t2 GUNDUR TOKLUGUNUZ 10 OLDUGU ICIN PATLAYARAK OLDUNUZ!!!\n");
                    exit(0);
                }
            }
            else if(duzeyler[i] == 0){
                ac_gun++;
                if(ac_gun == 2){
                    printf("\t\t\t2 GUNDUR TOKLUGUNUZ 0 OLDUGU ICIN ACLIKTAN OLDUNUZ!!!\n");
                    exit(0);
                }
            }
        }
        else if(!strcmp(*(ihtiyaclar + i), "UYKU")){
            if(duzeyler[i] == 10){
                uykusuz_gun++;
                if(uykusuz_gun == 3){
                    printf("\t\t\tUYKUNUZ 3 GUNDUR 10 OLDUGU ICIN UYKUSUZLUKTAN OLDUNUZ!!!\n");
                    exit(0);
                }
            }
            else{
                uykusuz_gun = 0;
            }
        }
        else if(!strcmp(*(ihtiyaclar + i), "SEVGI")){
            if(duzeyler[i] == 0){
                printf("\t\t\tSEVGINIZ 0 OLDUGU ICIN INTIHAR EDIP OLDUNUZ!!!\n");
                exit(0);
            }
        }
        else if(!strcmp(*(ihtiyaclar + i), "SOSYALLIK")){
            if(duzeyler[i] == 0){
                printf("\t\t\tSOSYALLIK EKSIKLIGINDEN DOLAYI INTIHAR EDIP OLDUNUZ!!!\n");
                exit(0);
            }
        }
        else if(!strcmp(*(ihtiyaclar + i), "SAGLIK")){
            if(duzeyler[i] == 0){
                printf("\t\t\tSAGLIGINIZ 0 OLDUGU ICIN HASTA BIR SEKILDE YERE YIGILIP OLDUNUZ!!!\n");
                exit(0);
            }
        }
        else if(!strcmp(*(ihtiyaclar + i), "EGITIM")){
            if(duzeyler[i] == 0){
                printf("\t\t\tEGITIMINIZ 0 OLDUGU ICIN UYUSTURUCU BARONUNA KARISIP CIKAN CATISMADA OLDUNUZ!!!\n");
                exit(0);
            }
        }
        else if(!strcmp(*(ihtiyaclar + i), "HIJYEN")){
            if(duzeyler[i] == 0){
                printf("\t\t\tHIJYENINIZ 0 OLDUGU ICIN BAKTERILER SIZI YENI EVLERI OLARAK KULLANDI VE OLDUNUZ!!!\n");
                exit(0);
            }
        }
        else if(!strcmp(*(ihtiyaclar + i), "TUVALET")){
            if(duzeyler[i] == 10){
                tuvaletsiz_gun++;
                if(tuvaletsiz_gun == 2){
                    printf("\t\t\tTUVALETINIZ 2 GUNDUR 0 OLDUGU ICIN MESANENIZ PATLADI VE OLDUNUZ!!!\n");
                    exit(0);
                }
            }
            else{
                tuvaletsiz_gun = 0;
            }
        }
        else if(!strcmp(*(ihtiyaclar + i), "EGLENCE")){
            if(duzeyler[i] == 0){
                printf("\t\t\tEGLENCE EKSIKLIGINDEN DOLAYI INTIHAR EDIP OLDUNUZ!!!\n");
                exit(0);
            }
        }
        else if(!strcmp(*(ihtiyaclar + i), "SU IHTIYACI")){
            if(duzeyler[i] == 10){
                susuz_gun++;
                if(susuz_gun == 3){
                    printf("\t\t\t3 GUNDUR SUSUZ OLDUGUNUZ ICIN SUSUZLUKTAN KURUYUP OLDUNUZ!!!\n");
                    exit(0);
                }
            }
            else{
                susuz_gun = 0;
            }
        }
        i++;
    }
}


void fonklari_yaz(){
    printf("1)Yemek Ye\n");
    printf("2)Uyu\n");
    printf("3)Temizlen\n");
    printf("4)Sevil\n");
    printf("5)Sosyalles\n");
    printf("6)Iyiles\n");
    printf("7)Okula Git\n");
    printf("8)Eglen\n");
    printf("9)Tuvalete Git\n");
    printf("10)Markete Git\n");
    printf("11)Su Ic\n");
}

void saatKontrol(float miktar){
    printf("SAAT: %.2f >>>", saat);
    saat += miktar;
    if(saat - (int)saat >= 0.60){
        saat = saat + 1 - 0.60;
    }
    if(saat >= 24){
        saat -= 24;
    }
    printf(" %.2f\n", saat);
}

int elemanCikar(char **dizi, char *eleman, int dizinin_eleman_sayisi){
    //dizinin yeni eleman sayisini dondurur.
    int el_sayi = 0;
    char *temp[30];
    int j = 0, bir_kere = 1;
    for(i = 0; i < dizinin_eleman_sayisi; i++){
        if(!strcmp(dizi[i], eleman) && bir_kere){
            bir_kere--;
            continue;
        }
        else{
            el_sayi += 1;
            temp[j] = dizi[i];
            dizi[j] = temp[j];
            j++;
        }
    }
    return el_sayi;
}

void duzeyYenile(char *ihtiyac, int miktar){
    i = 0;
    int oldu_mu = 0;
    while(1){
        if(!strcmp(*(ihtiyaclar + i), ihtiyac)){
            *(duzeyler + i) += miktar;
            if(*(duzeyler + i) >= 10){
                *(duzeyler + i) = 10;
                printf("%s: %d -> %d\n", ihtiyac, *(duzeyler + i) - miktar, *(duzeyler + i));
                olum_kontrol();
            }
            else if(*(duzeyler + i) <= 0){
                *(duzeyler + i) = 0;
                printf("%s: %d -> %d\n", ihtiyac, *(duzeyler + i) - miktar, *(duzeyler + i));
                olum_kontrol();
            }
            else{
                printf("%s: %d -> %d\n", ihtiyac, *(duzeyler + i) - miktar, *(duzeyler + i));
                olum_kontrol();
            }
            break;
        }
        i++;
    }

}

void ihtVeDuzeyYazdir(){

    for(i = 0; i < ihtiyac_sayisi; i++){
        printf("%s -> %d\n", *(ihtiyaclar + i), *(duzeyler + i));
    }
}

void yemek_duzey_yenile(char *yemek){
        if(!strcmp(yemek, "Meyve")){
            duzeyYenile("TOKLUK", 2);
            Sleep(5000);
            duzeyYenile("SAGLIK", 1);
            Sleep(1000);
            duzeyYenile("TUVALET", 1);
            Sleep(1000);
            duzeyYenile("SU IHTIYACI", 1);
            Sleep(1000);
        }
        if(!strcmp(yemek, "Iskender")){
            duzeyYenile("TOKLUK", 4);
            Sleep(1000);
            duzeyYenile("TUVALET", 1);
            Sleep(1000);
        }
        if(!strcmp(yemek, "Makarna")){
            duzeyYenile("TOKLUK", 3);
            Sleep(1000);
            duzeyYenile("TUVALET", 1);
            Sleep(1000);
            duzeyYenile("SU IHTIYACI", 2);
            Sleep(1000);
        }
        if(!strcmp(yemek, "Salata")){
            duzeyYenile("TOKLUK", 2);
            Sleep(1000);
            duzeyYenile("SAGLIK", 1);
            Sleep(1000);
            duzeyYenile("TUVALET", 1);
            Sleep(1000);
            duzeyYenile("SU IHTIYACI", 1);
            Sleep(1000);
        }
        if(!strcmp(yemek, "Fast Food")){
            duzeyYenile("TOKLUK", 4);
            Sleep(1000);
            duzeyYenile("SAGLIK", -3);
            Sleep(1000);
            duzeyYenile("TUVALET", 1);
            Sleep(1000);
            duzeyYenile("SU IHTIYACI", 2);
            Sleep(1000);
        }
        if(!strcmp(yemek, "Kuru-Pilav")){
            duzeyYenile("TOKLUK", 4);
            Sleep(1000);
            duzeyYenile("SAGLIK", 1);
            Sleep(1000);
            duzeyYenile("TUVALET", 1);
            Sleep(1000);
            duzeyYenile("SU IHTIYACI", 3);
            Sleep(1000);
        }
        if(!strcmp(yemek, "Et, Tavuk veya Balik")){
            duzeyYenile("TOKLUK", 4);
            Sleep(1000);
            duzeyYenile("SAGLIK", 1);
            Sleep(1000);
            duzeyYenile("TUVALET", 1);
            Sleep(1000);
            duzeyYenile("SU IHTIYACI", 2);
            Sleep(1000);
        }
        if(!strcmp(yemek, "Sebze Yemegi")){
            duzeyYenile("TOKLUK", 3);
            Sleep(1000);
            duzeyYenile("SAGLIK", 1);
            Sleep(1000);
            duzeyYenile("TUVALET", 1);
            Sleep(1000);
            duzeyYenile("SU IHTIYACI", 1);
            Sleep(1000);
        }
        duzeyYenile("UYKU", 1);
        Sleep(4000);
}

void buzdolabiYazdir(char **yemekler, int *toplamYemek, int *yemek_adetleri){
    for(i = 0; i < *toplamYemek; i++){
        printf("%d)%s'den %d adet var.\n", i + 1, *(yemekler + i), *(yemek_adetleri + i));
    }
    printf("\n\n");
}

int yemek_ye(char **yemekler, int *yemek_adetleri, int *toplam_yemek_sayi){
    printf("Lutfen hangi besin ile besleneceginizi seciniz:(Yanlarindaki numaralari yazarak onlari secebilirsiniz,orn. meyve icin 1) \n");
    int secim;
    for(i = 0; i < *toplam_yemek_sayi; i++){
        printf("%d) %s, adeti: %d\n", i+1, *(yemekler + i), *(yemek_adetleri + i));
    }
    printf("\nSeciminiz: ");
    scanf("%d", &secim);
    getchar();
    if(secim < *toplam_yemek_sayi + 1 && secim > 0){
        printf("%s yiyorsunuz...\n", *(yemekler + secim - 1));
        printf("\nYemekten kalan adet: %d -> %d\n", *(yemek_adetleri + secim - 1), *(yemek_adetleri + secim - 1) - 1);
        buzdolabindaki_toplam_yemek -= 1;
        saatKontrol(1);
        *(yemek_adetleri + secim - 1) -= 1;
        printf("-------------Guncel Ihtiyaclar-------------\n\n");
        yemek_duzey_yenile(yemekler[secim - 1]);
    }
    else{
        printf("Yanlis bir secim yaptiniz lutfen dogru secim yaptiginiza emin olunuz!\n");
        return yemek_ye(yemekler, yemek_adetleri, toplam_yemek_sayi);
    }

    return 0;
}

void su_ic(){
    printf("Su iciyorsunuz...");
    Sleep(1500);
    printf("-------------Guncel Ihtiyaclar-------------\n\n");
    duzeyYenile("SU IHTIYACI", -5);
}

void uyu(int uyunan_saat_miktari){
    printf("Yataga Yattin, uyuyorsun...\n\n");
    int i, sayac = 1;
    printf("SAAT: %.2f\n", saat);
    saatKontrol(uyunan_saat_miktari);
    printf("-------------Guncel Ihtiyaclar-------------\n\n");
    duzeyYenile("TOKLUK", -1 * uyunan_saat_miktari / 2);
    duzeyYenile("TUVALET", 1 * uyunan_saat_miktari / 2);
    duzeyYenile("UYKU", -5 * uyunan_saat_miktari / 4);
    duzeyYenile("HIJYEN", -2);
    duzeyYenile("SU IHTIYACI", 3);
    duzeyYenile("SOSYALLIK", -1);
    printf("Bakiye Yenilendi!");
    bakiye = 100;

    printf("\n\t\t\t\t\tYeni Gune Gunaydin\n");
}

void tuvalete_git(){
    printf("\n\nTuvalete gittin...\n\n");
    Sleep(2500);
    saatKontrol(0.15);
    printf("-------------Guncel Ihtiyaclar-------------\n\n");
    duzeyYenile("TUVALET", -7);
    duzeyYenile("HIJYEN", -3);
}

void eglen(){
    int istek;
    printf("Yapilabilecek aktivitiler: \n");
    for(i = 0; i < 4; i++){
        printf("%d) %s\n", i+1, istek_secenekleri[i]);
    }
    printf("\nBugun hangi aktiviteyi yapmak istiyorsun?: ");
    scanf("%d", &istek);
    getchar();
    printf("Ebeveynlerin senin icin sunu yapmaya karar verdi: ");
    char *secilen = istek_secenekleri[rand()%4];
    puts(secilen);
    Sleep(1500);

    if(strcasecmp(istek_secenekleri[istek - 1], secilen)){
        printf("Ailen senin sectigini yapmak istemedi! :((((\n");
        saatKontrol(1.30);
        Sleep(1500);
        printf("-------------Guncel Ihtiyaclar-------------\n\n");
        duzeyYenile("EGLENCE", 4);
        duzeyYenile("SEVGI", 1);
    }
    else{
        printf("Ailen senin istedigini yapmak istedi!!!! :(\n");
        saatKontrol(1.30);
        Sleep(1500);
        printf("-------------Guncel Ihtiyaclar-------------\n\n");
        duzeyYenile("EGLENCE", 8);
        duzeyYenile("SEVGI", 3);
    }
    duzeyYenile("SU IHTIYACI", 2);

}

void dolapKontrol(char **yemekler, int *toplamYemek, int *yemekSayilari, int yemek, int adet){
    int var_mi = 0;
    for(i = 0; i < *toplamYemek; i++){
        if(!strcmp(butun_yemekler[yemek - 1], yemekler[i])){
            var_mi++;
            break;
        }
    }
    if(var_mi){
        yemekSayilari[i] += adet;
        buzdolabindaki_toplam_yemek += adet;
    }
    else{
        *toplamYemek += 1;
        yemekler[i] = butun_yemekler[yemek - 1];
        buzdolabindaki_toplam_yemek += adet;
        yemekSayilari[i] = adet;
    }

}

void iyiles(){
    printf("Hangi iyilesme yontemini istiyorsunuz?\n");
    printf("1)DOKTOR\n2)AILE HEKIMI\n3)GOOGLE'DAN ARASTIR\n\n");
    int secim, secim2 = 0;
    printf("Istediginiz yontemin numarasi: ");
    scanf("%d", &secim);
    getchar();

    switch(secim){
        case 1: printf("Hangi doktora gitmek istiyorsunuz:\n1)Ozel\n2)Devlet\n\t: ");
                scanf("%d", &secim2);
                getchar();
                printf("-------------Guncel Ihtiyaclar-------------\n\n");
                duzeyYenile("TOKLUK", -1);
                if(secim2 == 1){
                    saatKontrol(1);
                    duzeyYenile("SAGLIK", 6);
                    duzeyYenile("HIJYEN", 1);
                }
                else{
                    saatKontrol(2.3);
                    duzeyYenile("SAGLIK", 4);
                }
                break;
        case 2: saatKontrol(0.45);
                printf("-------------Guncel Ihtiyaclar-------------\n\n");
                duzeyYenile("TOKLUK", -1);
                duzeyYenile("SAGLIK", 4);
                duzeyYenile("HIJYEN", 1);
                break;
        case 3: saatKontrol(0.15);
                printf("-------------Guncel Ihtiyaclar-------------\n\n");
                duzeyYenile("TOKLUK", -1);
                duzeyYenile("SAGLIK", 1);
                break;
        default:printf("Gecersiz secim bir daha seciniz\n");
                iyiles();
                break;
    }
    duzeyYenile("SU IHTIYACI", 2);
}

void markete_git(char **yemekler, int *toplamYemek, int *yemekSayilari){
    printf("Marketteki Urunler\n\n");
    printf("1)Meyve -> 10 TL\n");
    printf("2)Iskender -> 20 TL\n");
    printf("3)Makarna -> 20 TL\n");
    printf("4)Salata -> 20 TL\n");
    printf("5)Fast food -> 20 TL\n");
    printf("6)Kuru-Pilav -> 20 TL\n");
    printf("7)Et, Tavuk veya Balik -> 20 TL\n");
    printf("8)Sebze yemegi -> 10 TL\n");
    int sec;
    int adet;
    int a=bakiye;
    while (1) {
        printf("Almak isteginiz urun numarasını girin: ");
        scanf("%d",&sec);
        printf("Kac adet alacaksınız: ");
        scanf("%d",&adet);
        switch (sec) {
            case 1:
                bakiye-=(adet*10);
                break;
            case 2:
                bakiye-=(adet*20);
                break;
            case 3:
                bakiye-=(adet*20);
                break;
            case 4:
                bakiye-=(adet*20);
                break;
            case 5:
                bakiye-=(adet*20);
                break;
            case 6:
                bakiye-=(adet*20);
                break;
            case 7:
                bakiye-=(adet*20);
                break;
            case 8:
                bakiye-=(adet*10);
                break;
            default:
                printf("Geçersiz seçim...");
                break;
        }
        if (bakiye<0){
            printf("Yetersiz bakiye...");
            bakiye=a;
        }
        else{
            printf("Kalan bakiye: %d\n\n",bakiye);
            dolapKontrol(yemekler, toplamYemek, yemekSayilari, sec, adet);
            break;
        }

    }
    printf("-------------Guncel Ihtiyaclar-------------\n\n");
    duzeyYenile("TOKLUK", -2);
    duzeyYenile("UYKU", 1);
    duzeyYenile("HIJYEN", -2);
    duzeyYenile("TUVALET", 1);
    duzeyYenile("SU IHTIYACI", 2);
    printf("%d adet %s aldin...\n",adet,*(butun_yemekler+sec-1));
    printf("Saat: %.2f -> %.2f\n", saat, saat + 1);
        saat += 1;
}

void beslenme_cantasi(char **yemekler, int *toplamYemek, int *yemek_adetleri){
    int indis, sayi;
    if(bes_cantadaki_yiyecek_sayisi < 4){
        printf("Buzdolabindaki yiyecekler\n\n");
        buzdolabiYazdir(yemekler, toplamYemek, yemek_adetleri);
        printf("Toplam Kac Tane Yemek Alacaksiniz(Max 4): ");
        scanf("%d", &sayi);
        getchar();
        if(sayi > buzdolabindaki_toplam_yemek || sayi > 4 || sayi <= 0){
            printf("Yanlis bir sayi girdiniz. Tekrar giriniz.\n\n");
            i--;
            beslenme_cantasi(yemekler, toplamYemek, yemek_adetleri);
        }
        else{
            for(i = 0 ; i < sayi; i++){
                printf("Cantana almak istedigin %d. yemek: ",i+1);
                scanf("%d", &indis);
                getchar();
                if(indis > 0 && indis <= *toplamYemek && yemek_adetleri[indis - 1] != 0){
                    bes_canta[i] = yemekler[indis - 1];
                    bes_cantadaki_yiyecek_sayisi += 1;
                    yemek_adetleri[indis - 1] -= 1;
                }
                else{
                    printf("HATA -->\tSectiginiz yiyecek dolapta bulunmamaktadir!\n");
                    i--;
                    continue;
                }
            }
            printf("Beslenme cantandaki yiyecekler: \n\n");
            for (i=0; i< bes_cantadaki_yiyecek_sayisi; i++) {
                printf("%s \n",bes_canta[i]);
            }
        }
    }
    else{
        printf("\nBeslenme cantan maksimum kapasitesine sahip!!\n\n");
    }

}

void bes_can_yazdir(){
    printf("-------------Guncel beslenme cantan-------------\n\n");
    for(i = 0; i < bes_cantadaki_yiyecek_sayisi; i++){
        printf("%d)%s\n", i+1, bes_canta[i]);
    }
}

void okula_git(char **yemekler,int *toplamYemek, int *yemek_adetleri){
    float okul_gidis_saati = saat;
    int yemek_indis;
    char yemek_tercih, bes_karar;
    printf("Beslenme Cantasi yapmak istiyor musun?(Y/N)\n");
    scanf("%c", &bes_karar);
    getchar();
    if(saat <= 17 && saat >= 8){
        if(bes_karar == 'Y' || bes_karar == 'y'){
            beslenme_cantasi(yemekler, toplamYemek, yemek_adetleri);
        }
        printf("\n\n Iyi dersler...\n\n");
        Sleep(4000);
        if(saat < 12){
            saatKontrol(12-saat);
            duzeyYenile("TOKLUK", (int)((12.0 - okul_gidis_saati)/3 * -1));
            printf("Ogle arasi oldu\n\nBeslenme cantandan bir seyler yemek istiyor musun(Y/N): ");
            scanf("%c", &yemek_tercih);
            getchar();
            if(yemek_tercih == 'Y' || yemek_tercih == 'y'){
                bes_can_yazdir();
                printf("bir secim yapiniz: ");
                scanf("%d", &yemek_indis);
                getchar();
                printf("-------------Guncel Ihtiyaclar-------------\n\n");
                yemek_duzey_yenile(bes_canta[yemek_indis - 1]);
                bes_cantadaki_yiyecek_sayisi = elemanCikar(bes_canta, bes_canta[yemek_indis - 1], bes_cantadaki_yiyecek_sayisi);
                bes_can_yazdir();
            }
        }
        printf("\n\n OKULDAN CIKTIN...\n\n");
        Sleep(1000);
        printf("-------------Guncel Ihtiyaclar-------------\n\n");
        duzeyYenile("EGITIM", 1);//Duzenli gittigi takdirde egitimi 10 olabilir o zaman gitmesine gerek olmayabilir.
        Sleep(1000);
        duzeyYenile("UYKU", 2);
        Sleep(1000);
        duzeyYenile("TOKLUK", (int)((17.0 - saat)/3 * -1));
        Sleep(1000);
        duzeyYenile("SOSYALLIK", (int)(17- saat)/3 * 1);
        Sleep(1000);
        duzeyYenile("HIJYEN", (int)(17- saat)/3 * -1);
        Sleep(1000);
        duzeyYenile("EGLENCE", 2);
        Sleep(1000);
        duzeyYenile("SEVGI", 2);
        Sleep(1000);
        saatKontrol(17-saat);
    }
    else{
        printf("Saat su anda 8 ve 17 arasinda olmadigi icin okul kapalidir o yuzden lutfen baska bir etkinlik seciniz!!\n\n");
    }
}

void dus_al(){
    printf("\n\n Dus aldin...\n\n");
    Sleep(2000);
    saatKontrol(0.30);
    printf("-------------Guncel Ihtiyaclar-------------\n\n");
    duzeyYenile("TOKLUK",-1);
    duzeyYenile("HIJYEN",10);
    duzeyYenile("SAGLIK", 1);
}
void el_yika(){
    printf("\n\n Elini yikadin...\n\n");
    Sleep(2000);
    saatKontrol(0.05);
    printf("-------------Guncel Ihtiyaclar-------------\n\n");
    duzeyYenile("HIJYEN", 3);
    duzeyYenile("SAGLIK", 1);
}
void temizlen(){
    printf("1) Dus al\n");
    printf("2) El yika\n");
    printf("Yapmak istediginiz islemi secin: ");
    int sec;
    scanf("%d",&sec);
    getchar();
    if (sec==1) {
        dus_al();
    }
    else
        el_yika();
}

void sevil(){
    printf("\nBiraz ailenle vakit gecirip sevginizi yukselttiniz!\n\n");
    saatKontrol(2);
    printf("-------------Guncel Ihtiyaclar-------------\n\n");
    duzeyYenile("SEVGI", 3);
    duzeyYenile("EGLENCE", 1);
    duzeyYenile("UYKU", 1);
    duzeyYenile("TOKLUK", -2);
    duzeyYenile("SU IHTIYACI", 2);

}

void sosyalles(){
    printf("Arkadaslarinla mi yoksa Ailenle mi sosyallesmek istersin?\n");
    printf("1)Arkadaslarla\n2)Aile ile\n:");
    int secim;
    scanf("%d", &secim);
    getchar();
    saatKontrol(2);
    printf("-------------Guncel Ihtiyaclar-------------\n\n");
    if(secim == 1){
        duzeyYenile("SOSYALLIK", 3);
        duzeyYenile("UYKU", 2);
        duzeyYenile("HIJYEN", -2);
        duzeyYenile("TUVALET", 2);
        duzeyYenile("SU IHTIYACI", 2);
    }
    else{
        duzeyYenile("SOSYALLIK", 2);
        duzeyYenile("UYKU", 2);
        duzeyYenile("HIJYEN", -1);
        duzeyYenile("TUVALET", 2);
        duzeyYenile("SU IHTIYACI", 2);
    }
}



