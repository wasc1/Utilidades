#include <stdio.h>
#include <stdlib.h>

void cpu();
void memoria();
void hd_ssd();
void geral();

int main(){

cpu();
memoria();
hd_ssd();
geral();

return(0);
}

void cpu(){
printf("\nInformações da CPU:\n");

FILE *cpu;
char caractere;
int contador;

cpu = fopen("/proc/cpuinfo","r");
if(cpu == NULL){
printf("Arquivo da CPU nao pode ser aberto ou nao encontrado\n");
exit(1);
}

while(!feof(cpu)){
caractere = fgetc(cpu);
if(!feof(cpu))
printf("%c",caractere);
contador++;
}
fclose(cpu);

}

void memoria(){
printf("Informações da Memoria:\n");

FILE *memoria;
char caractere;
int contador;

memoria = fopen("/proc/meminfo","r");
if(memoria == NULL){
printf("Arquivo de Memoria nao pode ser aberto ou nao encontrado.\n");
exit(1);
}

while(!feof(memoria)){
caractere = fgetc(memoria);
if(!feof(memoria))
printf("%c",caractere);
contador++;
}
fclose(memoria);

}

void hd_ssd(){
printf("\nInformações do HD_SSD: \n");
system("fdisk -l | grep /dev/");
}

void geral(){
printf("\nInformações de Bios, Placa mãe e outros...: \n");
system("dmidecode");
printf("\n-------------------------------------------------------------------\n");
printf("\nDetecção de erros e avisos do sistema: \n");
system("dmesg");
}