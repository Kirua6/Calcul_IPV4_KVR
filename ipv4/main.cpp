//Ce code est un exemple de classe C++ pour gérer les adresses IPv4. Il contient plusieurs fonctions pour initialiser, manipuler et afficher des adresses IPv4.
//La première partie du code contient les inclusions de bibliothèques nécessaires, y compris "ipv4.h", qui est le fichier d'en-tête de la classe IPv4.
#include <iostream>
#include <cstdio>
#include "ipv4.h"
using namespace std;
//La classe IPv4 a trois constructeurs : le premier prend une adresse IP et un nombre de bits pour le masque de sous-réseau ; 
//le deuxième prend une adresse IP et un masque de sous-réseau ; 
//et le dernier est le destructeur de la classe. La classe a également des fonctions pour calculer et obtenir le masque, l'adresse de réseau et l'adresse de diffusion.

//La fonction "ObtenirAdresseDiffusion" calcule l'adresse de diffusion pour l'adresse IPv4 actuelle en utilisant l'adresse de réseau et le masque de sous-réseau.
//Elle stocke le résultat dans le tableau "_diffusion".
void IPv4::ObtenirAdresseDiffusion(unsigned char *_diffusion)
{
    unsigned char adresseDuReseau[4];
    ObtenirAdresseReseau(adresseDuReseau);
    for(int indice = 0; indice < 4; indice++)
    _diffusion[indice] = adresseDuReseau[indice] | ~masque[indice] ;
}
//La fonction "IPv4(const unsigned char * _adresse,const unsigned char _cidr)" est un constructeur qui initialise la classe avec une adresse IPv4 et un nombre de bits pour le masque de sous-réseau.
//Il alloue de la mémoire pour les tableaux "adresse" et "masque", copie l'adresse IPv4 et calcule le masque à partir du nombre de bits.
IPv4::IPv4(const unsigned char * _adresse,const unsigned char _cidr)
{
    adresse = new unsigned char [4];
    masque  = new unsigned char [4];
    for(int indice = 0 ; indice < 4 ; indice++)
        adresse[indice] = _adresse[indice];
    if(_cidr <= 32)
        CalculerMasque(_cidr);
}
//La fonction "IPv4(const unsigned char * _adresse,const unsigned char * _masque)" est un constructeur qui initialise la classe avec une adresse IPv4 et un masque de sous-réseau.
//Il alloue de la mémoire pour les tableaux "adresse" et "masque", copie l'adresse IPv4 et le masque de sous-réseau.
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
//La fonction "CalculerMasque(unsigned char _cidr)" calcule le masque de sous-réseau à partir du nombre de bits dans "_cidr".
//Elle utilise une boucle pour initialiser le masque à zéro, puis une boucle while pour définir les octets du masque à 255 pour chaque bloc de 8 bits.
//Elle utilise une autre boucle while pour définir les bits restants du masque.
void IPv4::CalculerMasque(unsigned char _cidr)
{
    int indice ;
    //le masque est remis à zero
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
//La fonction "ObtenirMasque(unsigned char * _masque)" copie le masque de sous-réseau dans le tableau "_masque".
void IPv4::ObtenirMasque(unsigned char * _masque)
{
    for(int indice = 0 ; indice < 4 ; indice++)
        _masque[indice] = masque[indice];
}
//La fonction "ObtenirAdresseReseau(unsigned char * _reseau)" calcule l'adresse de réseau pour l'adresse IPv4 actuelle en utilisant l'adresse IP et le masque de sous-réseau.
//Elle stocke le résultat dans le tableau "_reseau".
void IPv4::ObtenirAdresseReseau(unsigned char * _reseau)
{
    for(int indice = 0 ; indice < 4 ; indice++)
        _reseau[indice] = adresse[indice] & masque[indice] ;
}
//La fonction "AfficherTableau(unsigned char *tab)" est une fonction qui affiche un tableau d'octets au format "x.x.x.x".
void AfficherTableau(unsigned char *tab);
//La fonction "main" demande à l'utilisateur de saisir une adresse IPv4, puis crée un objet "uneAdresse" de la classe IPv4 en utilisant cette adresse et un nombre de bits pour le masque de sous-réseau. 
//Elle utilise ensuite les fonctions de la classe IPv4 pour obtenir et afficher l'adresse IP, le masque de sous-réseau, l'adresse de réseau et l'adresse de diffusion.
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
