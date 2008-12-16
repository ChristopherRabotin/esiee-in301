/**
 * Code fourni dans libbourse: fonction de calcul de prix d'achat et de vente
 */

/**
 * PrixAchat: calcule le prix d'achat d'actions, suivant le stock disponible
 * et la quantité voulue
 * @param VInit valeur initiale de l'action
 * @param Stock quantité totale d'actions disponible
 * @param Qte quantité d'action voulue
 * @return prix d'achat total pour la quantité d'actions voulue au cours actuel  
 */
double PrixAchat(double VInit, int Stock, int Qte);

/**
 * PrixVente: calcule le prix de vente des actions, suivant le stock disponible
 * et la quantité à vendre
 * @param VInit valeur initiale de l'action
 * @param Stock quantité totale d'actions disponible
 * @param Qte quantité d'action à vendre
 * @return prix de vente total pour la quantité d'actions à vendre au cours actuel  
 */
/* ou VInit est la valeur initial de l'action
 ou Stock est la quantite d'action offerte
 ou Qte est la qte d'action dont on veut connaitre le prix
 retourne la valeur total de vente de Qte actions dont le prix
 initial etait VInit et le stock courant est de Stock */
double PrixVente(double VInit, int Stock, int Qte);
