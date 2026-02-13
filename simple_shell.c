#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>

#define MAX_LINE 80

int main(void) {
    char input[MAX_LINE];
    int should_run = 1;
    char *args[10];

    while (should_run) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Cansu_Shell[%s]> ", cwd);
        } else {
            printf("Cansu_Shell> ");
        }
        fflush(stdout);

        if (fgets(input, MAX_LINE, stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0;

        // --- DÜZELTME: Parçalama iþlemi tam burada, karþýlaþtýrmadan önce olmalý ---
        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL && i < 9) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Dizinin sonunu iþaretle

        if (i > 0) { // Eðer kullanýcý bir þey yazdýysa
            
            // 1. Çýkýþ kontrolü
            if (strcmp(args[0], "exit") == 0) {
                should_run = 0;
                continue;
            }
            
            // 2. Hakkýnda komutu
            if (strcmp(args[0], "hakkinda") == 0) {
                printf("\n-- Mery_Shell Info --\n");
                printf("Developer: Meryem Unaldi\n");
                printf("Bu shell projesi C dili ile sistem programlama temellerini ogrenmek icin yapilmistir.\n\n");
            } 
            // 3. Toplama komutu
            else if (strcmp(args[0], "topla") == 0) {
                if (args[1] != NULL && args[2] != NULL) {
                    int sayi1 = atoi(args[1]);
                    int sayi2 = atoi(args[2]);
                    printf("Sonuc: %d\n", sayi1 + sayi2);
                } else {
                    printf("Hata: Lutfen iki sayi girin. (Ornek: topla 5 10)\n");
                }
            }
            // 4. CD komutu
            else if (strcmp(args[0], "cd") == 0) {
                if (args[1] == NULL) {
                    printf("Hata: Gitmek istediginiz dizini belirtin.\n");
                } else {
                    if (chdir(args[1]) != 0) {
                        perror("Cansu_Shell Hata");
                    } else {
                        printf("Dizin degistirildi.\n");
                    }
                }
            }
            // 5. Bilinmeyen komutlarý sisteme gönder
            else {
                system(input);
            }
        }
    }

    return 0;
}
