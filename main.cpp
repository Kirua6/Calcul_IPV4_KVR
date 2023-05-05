#include <iostream>
#include <cstdio>
#include "ipv4.h"
using namespace std;

void IPv4::ObtenirAdresseDiffusion(unsigned char *_diffusion)
{
    unsigned char adresseDuReseau[4];
    ObtenirAdresseReseau(adresseDuReseau);
    for(int indice = 0; indice < 4; indice++)
    _diffusion[indice] = adresseDuReseau[indice] | ~masque[indice] ;
}

IPv4::IPv4(const unsigned char * _adresse,const unsigned char _cidr)
{
    adresse = new unsigned char [4];
    masque  = new unsigned char [4];
    for(int indice = 0 ; indice < 4 ; indice++)
        adresse[indice] = _adresse[indice];
    if(_cidr <= 32)
        CalculerMasque(_cidr);
}
IPv4::IPv4(const unsigned char * _adresse,const unsigned char * _masque)
{
    adresse = new unsigned char [4];
    masque  = new unsigned char [4];
    for(int indice = 0 ; indice < 4 ; indice++)
        {
        adresse[indice] = _adresse[indice];
        masque[indice] = _masque[indice];
        }
}
IPv4::~IPv4()
{
    delete [] adresse;
    delete [] masque;
}

void IPv4::CalculerMasque(unsigned char _cidr)
{
    int indice ;
    for(indice = 0 ; indice < 4 ; indice ++)
        masque[indice] = 0 ;

    indice = 0;
    while(_cidr >= 8)
    {
        masque[indice++] = 255 ;
        _cidr -= 8 ;
    }

    unsigned char puissance = 128 ;
    while(_cidr-- > 0)
    {
        masque[indice] += puissance ;
        puissance /=2 ;
    }
}
void IPv4::ObtenirMasque(unsigned char * _masque)
{
    for(int indice = 0 ; indice < 4 ; indice++)
        _masque[indice] = masque[indice];
}
void IPv4::ObtenirAdresseReseau(unsigned char * _reseau)
{
    for(int indice = 0 ; indice < 4 ; indice++)
        _reseau[indice] = adresse[indice] & masque[indice] ;
}

void AfficherTableau(unsigned char *tab);

int main()
{
    unsigned char adresse[4];
    unsigned char masque [4];
    unsigned char reseau [4];
    unsigned char diffusion [4];

    cout << "Entrez une adresse IPv4 : ";
    scanf("%hhu.%hhu.%hhu.%hhu", &adresse[0], &adresse[1], &adresse[2], &adresse[3]);

    IPv4 uneAdresse(adresse, 24);

    cout << "Adresse IPv4 : ";
    AfficherTableau(adresse);
    uneAdresse.ObtenirMasque(masque);
    cout << "Masque : ";
    AfficherTableau(masque);
    uneAdresse.ObtenirAdresseReseau(reseau);
    cout << "Réseau : ";
    AfficherTableau(reseau);
    uneAdresse.ObtenirAdresseDiffusion(diffusion);
    cout << "Diffusion : ";
    AfficherTableau(diffusion);

    return 0;
}

void AfficherTableau(unsigned char *tab)
{
    for(int indice=0 ; indice < 4 ; indice ++)
    {
        cout << static_cast<int> (tab[indice]);
        if(indice < 3)
            cout << "." ;
    }
    cout << endl;
}
