double PrixAchat(double VInit, int Stock, int Qte) {
	int i;
	double facteur =0.0;

	// Verification de la validite des parametres
	if ( (VInit <= 0) || (Stock <= 0)|| (Qte <= 0)|| (Qte > Stock))
		return -1;

	for (i = 0; i < Qte; i++) {
		facteur += 1/(double)(Stock - i);
	}
	return VInit*facteur;

}

double PrixVente(double VInit, int Stock, int Qte) {
	int i;
	double facteur =0.0;

	// Verification de la validite des parametres
	if ( (VInit <= 0) || (Stock <= 0)|| (Qte <= 0))
		return -1;

	for (i = 1; i < Qte+1; i++) {
		facteur += 1/(double)(Stock + i);
	}
	return VInit*facteur;
}
