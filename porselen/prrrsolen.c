#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//! her yerden ulaşılacak değişkenler
// int tipliler
struct sayi {
    char plaka[10];
    int numara;
    int durum;
    int kilo;
    int ilktartim;
    int ürüncinsi;
    int sontartim;
    time_t giriştarihsaat, cikiştarihsaat;
} sayii;

//string tipliler
struct string {
    
    char sofor[30];
    char geldiye[30];
} araç;

//! menüler
//ana menü
int menü() {
    int secim;
    printf(" PORSELEN FABRIKASI KANTAR UYGULAMASI\n");
    printf("    ANA MENÜ\n");
    printf("1-ürün girişi işlemleri\n");
    printf("2-ürün çıkışı işlemleri\n");
    printf("0-programı kapat\n");
    printf("seçiminizi giriniz[0,1,2]: ");
    scanf("%d", &secim);
    return secim;
}

// ürün girişi menüsü
int urungirişmenü() {
    int secim;
    printf("\t\n\n\n\n\n\n\n ÜRÜN GİRİŞ İŞLEMLERİ\n");
    printf("1- araç kantar girişi yap\n");
    printf("2- araç kantar çıkışı yap\n");
    printf("3- boşaltımda bekleyen araçlar\n");
    printf("4- ürün girişlerini raporla\n");
    printf("0- ana menüye dön\n\n");
    printf("seçiminizi giriniz[0,1,2,3,4]: ");
    scanf("%d", &secim);
    return secim;
}

// ürün çıkışı menüsü
int uruncikismenü() {
    int secim;
    printf("\t\n\n ÜRÜN ÇIKIŞ İŞLEMLERİ\n");
    printf("1- araç kantar girişi yap\n");
    printf("2- araç kantar çıkışı yap\n");
    printf("3- yüklemede bekleyen araçlar\n");
    printf("4- giden ürünleri raporla\n");
    printf("0- ana menüye dön\n\n");
    printf("Seçiminizi giriniz[0,1,2,3,4]: ");
    scanf("%d", &secim);
    return secim;
}

//! giriş menüsünde fonksiyonlar
// ürün girişi menüsünde 1'e basılınca açılacak fonksiyon
void araçkantargirişiyap() {
    printf("Ürün giriş için kantar işlemi\n");
    araç a1;
    sayii a2;
    int numara = 0;

    // Numara okuma ve arttırma
    FILE *numPtr = fopen("araçnumaralari.txt", "a");
    if (numPtr == NULL) {
        printf("Numara dosyası açılamadı!\n");
        return;
    }

    while (fread(&numara, sizeof(int), 1, numPtr) == 1) {
    }
    numara++;
    fwrite(&numara, sizeof(int), 1, numPtr);
    fclose(numPtr);

    a2.numara = numara;
    printf("1-Kaolin\n");
    printf("2-Kuvars\n");
    printf("3-Feldispat\n");
    printf("Ürün cinsini giriniz: ");
    scanf("%d", &a2.ürüncinsi);

    printf("İlk tartımı giriniz: ");
    scanf("%d", &a2.ilktartim);

    printf("Plakayı giriniz: ");
    scanf("%s", a2.plaka);

    printf("Şoför ad soyad: ");
    scanf("%s", a1.sofor);

    //! Dosyaya kaydetme
    FILE *ptr = fopen("ürüngirişleri.txt", "a");
    if (ptr == NULL) {
        printf("Veri dosyası açılamadı!\n");
        return;
    }

    a2.sontartim = 0;
    a2.giriştarihsaat = time(0);
    a2.cikiştarihsaat = 0;
    a2.kilo = 0;
    a2.durum = 0;

    fwrite(&a2, sizeof(sayii), 1, ptr);
    fclose(ptr);

    printf("Araç giriş işlemi tamamlandı. Numara: %d\n", a2.numara);
}

// ürün girişi menüsünde 2'ye basılınca açılacak fonksiyon
void arackantarcikisi() {
    printf("Ürün çıkışı için kantar işlemi\n");
   
    int numara, sonuc = 0, sayac = 0;

    FILE *ptr = fopen("ürüngirişleri.txt", "r+b");

    while (fread(&a2, sizeof(sayii), 1, ptr) == 1) {
        if (a2.durum == 0) {
            sonuc = 1;
            break;
        }
    }

    if (sonuc == 0) {
        printf("Boşaltımda bekleyen araç yok.\n");
        fclose(ptr);
        return;
    }

    rewind(ptr);
    printf("%-20s%-20s%-20s\n", "NUMARA", "PLAKA", "İLK TARTIM");
    while (fread(&a2, sizeof(sayii), 1, ptr) == 1) {
        if (a2.durum == 0) {
            printf("%-20d%-20s%-20d\n", a2.numara, a2.plaka, a2.ilktartim);
        }
    }

    printf("Çıkış yapacak aracın numarası: ");
    scanf("%d", &numara);

    sonuc = 0;
    rewind(ptr);
    while (fread(&a2, sizeof(sayii), 1, ptr) == 1) {
        if (a2.durum == 0 && a2.numara == numara) {
            sonuc = 1;
            break;
        }
        sayac++;
    }

    if (sonuc == 0) {
        printf("%d numaralı araç yoktur\n", numara);
    } else {
        printf("Son tartımı giriniz: ");
        scanf("%d", &a2.sontartim);
        a2.cikiştarihsaat = time(0);
        a2.kilo = a2.ilktartim - a2.sontartim;
        a2.durum = 1;

        fseek(ptr, sayac * sizeof(sayii), SEEK_SET);
        fwrite(&a2, sizeof(sayii), 1, ptr);

        printf("Araç çıkışı başarıyla yapıldı.\n");
    }

    fclose(ptr);
}

// ürün girişi menüsünde 3'e basılınca açılacak fonksiyon
void bosaltimdabekleyenaraclar() {
    printf("Boşaltımda bekleyen araçlar\n");
    araç a1;
    sayii a2;
    int sonuc = 0;

    FILE *ptr = fopen("ürüngirişleri.txt", "r+b");
    if (ptr == NULL) {
        printf("Veri dosyası açılamadı!\n");
        return;
    }

    printf("%-20s%-20s%-20s\n", "NUMARA", "PLAKA", "İLK TARTIM");

    while (fread(&a2, sizeof(sayii), 1, ptr) == 1) {
        if (a2.durum == 0) {
            sonuc = 1;
            printf("%-20d%-20s%-20d\n", a2.numara, a2.plaka, a2.ilktartim);
        }
    }

    if (sonuc == 0) {
        printf("Boşaltımda bekleyen araç yok.\n");
    }

    fclose(ptr);
}

// ürün girişi menüsünde 4'e basılınca açılacak fonksiyon
void urungirisleriniraporla() {
    printf("Ham madde giriş raporları\n");
    araç a1;
    sayii a2;
    int kuvarsToplam = 0, kaolinToplam = 0, feldispatToplam = 0;

    FILE *ptr = fopen("ürüngirişleri.txt", "r+b");

    while (fread(&a2, sizeof(sayii), 1, ptr) == 1) {
        if (a2.durum == 1) {
            if (a2.ürüncinsi == 1) {
                kaolinToplam += a2.kilo;
            } else if (a2.ürüncinsi == 2) {
                kuvarsToplam += a2.kilo;
            } else if (a2.ürüncinsi == 3) {
                feldispatToplam += a2.kilo;
            }
        }
    }

    fclose(ptr);

    printf("Kaolin toplam miktar: %d kg\n", kaolinToplam);
    printf("Kuvars toplam miktar: %d kg\n", kuvarsToplam);
    printf("Feldispat toplam miktar: %d kg\n", feldispatToplam);
}

//! çıkış menüsünde ki fonksiyonlar
// ürün çıkışı menüsünde 1 e basılınca açılacak fonksiyon
void araçkantargirişiyap2() {
    printf("Ürün satişi için kantar işlemi(fabrikadan çikiş)\n");
    araç a1;
    sayii a2;
    int numara = 0;

    FILE *numPtr = fopen("araçnumaralari2.txt", "a+b");
    while (fread(&numara, sizeof(int), 1, numPtr) == 1) {
    }
    numara++;
    fwrite(&numara, sizeof(int), 1, numPtr);
    fclose(numPtr);

    a2.numara = numara;
    printf("1-Porselen\n");
    printf("2-Seramik\n");
    printf("Ürün cinsini giriniz: ");
    scanf("%d", &a2.ürüncinsi);

    printf("İlk tartimi giriniz: ");
    scanf("%d", &a2.ilktartim);

    printf("Plakayi giriniz: ");
    scanf("%s",a2.plaka);

    printf("Şoför ad soyad: ");
    scanf("%s",a1.sofor);

    a2.sontartim = 0;
    a2.giriştarihsaat = time(0);
    a2.cikiştarihsaat = 0;
    a2.kilo = 0;
    a2.durum = 0;

    FILE *ptr = fopen("ürünçikişlari.txt", "a+b");
    fwrite(&a2, sizeof(sayii), 1, ptr); 
    fclose(ptr);
    printf("Araç giriş işlemi tamamlandı.\n");
}
// ürün çıkışı menüsünde 2 e basılınca açılacak fonksiyon
void arackantarcikisi2() {
    printf("Ürün çikişi için kantar işlemi(fabrikadan çikiş)\n");
    araç a1;
    sayii a2;
    int numara, sonuc = 0, sayac = 0;

    FILE *ptr = fopen("ürünçikişlari.txt", "r+b");

    while (fread(&a2, sizeof(sayii), 1, ptr) == 1) {
        if (a2.durum == 0) {
            sonuc = 1;
            break;
        }
    }

    if (sonuc == 0) {
        printf("Yüklemede bekleyen araç yok.\n");
        fclose(ptr);
        return;
    }

    rewind(ptr);
    printf("%-20s%-20s%-20s\n", "NUMARA", "PLAKA", "İLK TARTIM");
    while (fread(&a2, sizeof(sayii), 1, ptr) == 1) {
        if (a2.durum == 0) {
            printf("%-20d%-20s%-20d\n", a2.numara, a2.plaka, a2.ilktartim);
        }
    }

    printf("Çıkış yapacak aracın numarası: ");
    scanf("%d", &numara);

    sonuc = 0;
    rewind(ptr);
    while (fread(&a2, sizeof(sayii), 1, ptr) == 1) {
        if (a2.durum == 0 && a2.numara == numara) {
            sonuc = 1;
            break;
        }
        sayac++;
    }

    if (sonuc == 0) {
        printf("%d numaralı araç yoktur\n", numara);
    } else {
        printf("Son tartımı giriniz: ");
        scanf("%d", &a2.sontartim);
        a2.cikiştarihsaat = time(0);
        a2.kilo = a2.sontartim - a2.ilktartim;
        a2.durum = 1;

        fseek(ptr, sayac * sizeof(sayii), SEEK_SET);
        fwrite(&a2, sizeof(sayii), 1, ptr);
        printf("Araç çıkışı başarıyla yapıldı.\n");
    }

    fclose(ptr);
}
// ürün çıkışı menüsünde 3 e basılınca açılacak fonksiyon
void yüklmedebekleyenaraçlar(){
printf("Yüklemede bekleyen araçlar\n");
    araç a1;
    sayii a2;
    int numara, sonuc = 0, sayac = 0;

    FILE *ptr = fopen("ürünçikişlari.txt", "r+b");

    while (fread(&a2, sizeof(sayii), 1, ptr) == 1) {
        if (a2.durum == 0) {
            sonuc = 1;
            break;
        }
    }

    if (sonuc == 0) {
        printf("yüklemede bekleyen araç yok.\n");
        fclose(ptr);
        return;
    }

    rewind(ptr);
    printf("%-20s%-20s%-20s\n", "NUMARA", "PLAKA", "İLK TARTIM");
    while (fread(&a2, sizeof(sayii), 1, ptr) == 1) {
        if (a2.durum == 0) {
            printf("%-20d%-20s%-20d\n", a2.numara, a2.plaka, a2.ilktartim);
        }
    }
    fclose(ptr);
}
// ürün çıkışı menüsünde 4 e basılınca açılacak fonksiyon
void satişiyapilanürünleriraporla(){
    printf("satilan ürünlerin çikiş raporlari\n");
    araç a1;
    sayii a2;
    int numara, sonuc = 0, sayac = 0,PorselenToplam=0,SeramikToplam=0;

    FILE *ptr = fopen("ürünçikişlari.txt", "r+b");

    while (fread(&a2, sizeof(sayii), 1, ptr) == 1) {
        if (a2.durum == 0) {
            sonuc = 1;
            break;
        }
    }

    if (sonuc == 0) {
        printf("Ürün satişi/çikişi olmamiştir.\n");
        fclose(ptr);
        return;
    }

    rewind(ptr);
    printf("%-20s%-20s%-20s%-20s%-20s\n", "NUMARA", "PLAKA", "İLK TARTIM","SON TARTIM","NET KİLO\n");
    while (fread(&a2, sizeof(sayii), 1, ptr) == 1) {
        if (a2.durum == 0) {
            printf("%-20d%-20s%-20d%-20d%-20d\n", a2.numara, a2.plaka, a2.ilktartim,a2.sontartim,a2.kilo);
        }
        if (a2.ürüncinsi==1)
        {
            PorselenToplam+=a2.kilo;
        }else if (a2.ürüncinsi==2)
        {
            SeramikToplam+=a2.kilo;
        }
        
        
        
    }
    fclose(ptr);
    printf("Toplam sonuçlar\n\n");
    printf("Porselen toplam         :%d.kg\n",PorselenToplam);
    printf("Seramik  toplam         :%d.kg\n",SeramikToplam);

}
//!menüler arası geçiş için while döngüsü
int main() {
    int secim;
    while ((secim = menü()) != 0){
        if (secim == 1) {
            int girisSecim;
            while ((girisSecim = urungirişmenü()) != 0) {
                switch (girisSecim) {
                    case 1:
                        araçkantargirişiyap();
                        break;
                    case 2:
                        arackantarcikisi();
                        break;
                    case 3:
                        bosaltimdabekleyenaraclar();
                        break;
                    case 4:
                        urungirisleriniraporla();
                        break;
                    default:
                        printf("Geçersiz seçim!\n");
                        break;
                }
            }
        } else if (secim == 2) {
            int cikisSecim;
            while ((cikisSecim = uruncikismenü()) != 0) {
                switch (cikisSecim) {
                    case 1:
                        araçkantargirişiyap2();
                        break;
                    case 2:
                        arackantarcikisi2();
                        break;
                    case 3:
                        yüklmedebekleyenaraçlar();
                        break;
                    case 4:
                        satişiyapilanürünleriraporla();
                        break;
                    default:
                        printf("Geçersiz seçim!\n");
                        break;
                }
            }
        } else {
            printf("Geçersiz seçim!\n");
        }
    }
    printf("Program sonlandırıldı.\n");
    return 0;
}
