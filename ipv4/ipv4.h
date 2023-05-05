#ifndef _IPV4_H
#define _IPV4_H

class IPv4
{
private:
    unsigned char * adresse;
    unsigned char * masque ;
    //méthode privée pour calculer le masque de sous-réseau à partir du préfixe CIDR.
    void CalculerMasque(unsigned char _cidr);
public:
    //constructeur pour initialiser une adresse IPv4 avec une adresse et un préfixe CIDR.
    IPv4(const unsigned char * _adresse, const unsigned char _cidr); 
    //constructeur pour initialiser une adresse IPv4 avec une adresse et un masque de sous-réseau.
    IPv4(const unsigned char * _adresse, const unsigned char * _masque);
    //destructeur pour libérer la mémoire allouée dynamiquement pour les tableaux adresse et masque.
    ~IPv4();
    //méthode pour récupérer le masque de sous-réseau.
    void ObtenirMasque(unsigned char * _masque);
    //méthode pour récupérer l'adresse réseau.
    void ObtenirAdresseReseau(unsigned char * _reseau);
    //méthode pour récupérer l'adresse de diffusion.
    void ObtenirAdresseDiffusion(unsigned char * _diffusion);
};
#endif // IPV4_H
