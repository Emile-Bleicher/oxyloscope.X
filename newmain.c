/*
 * File:   newmain.c
 * Author: emile
 *
 * Created on 25 octobre 2023, 21:36
 */
#include <xc.h>
#include "main.h"
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config LVP = OFF 		//Disable low voltage programmig
#pragma config DEBUG = OFF		//Debug ON
#define maSortie PORTAbits.RA4
int val=18;
float Amp=1;

void __interrupt() ISR() {
    if (PIR1bits.ADIF && CHS0==0 && CHS1==0) {
        ADC_Interupt(Amp);}
    if (PIR1bits.ADIF && CHS0==1 && CHS1==0) {
        Frequence_Echantillonage(&val);}
    if (PIR1bits.ADIF && CHS0==0 && CHS1==1){
       Amp=Amplitude_Echantillonage();}//A revoir notament en modiffiant l'�quation
    if(INTCONbits.TMR0IF){			//Est-ce que Timer0 a caus� l'interruption?
		T0_Interupt(val);  }      	//Si oui, ex�cuter T0 ISR (interrupt service routine)
    if(RBIF==1){
        external_interupt(Amp);}   
}

void main(void)
{
    glcd_Init(GLCD_ON);
    glcd_Image();
    __delay_ms(1000);
    glcd_FillScreen(0);
    print_oscylocope();
    init_ADC();
    InitTimer0(0x03, 0xE8);
    init_external_interupt();
    while(1){
    }
    return;
}
