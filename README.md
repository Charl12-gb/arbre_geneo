# Documentation d’utilisation du programme de gestion d’arbre généalogique

## 1. Compilation et exécution

1. **Compilation**  
   Ouvrez un terminal et placez-vous dans le dossier où se trouve votre fichier C (par exemple `arbre_genealogique.c`).  
   Tapez la commande :
   ```bash
   gcc arbre_genealogique.c -o arbre_genealogique
   ```
   Cette commande génère un exécutable nommé `arbre_genealogique`.

2. **Exécution**  
   Toujours dans le même dossier, lancez :
   ```bash
   ./arbre_genealogique
   ```
   Le programme démarre et affiche le **menu principal**.

---

## 2. Menu principal

Une fois le programme lancé, vous verrez :

```
=== MENU GESTION ARBRE GENEALOGIQUE ===
1. Creer/Definir la racine (si inexistante)
2. Ajouter un enfant
3. Ajouter un frere/une soeur
4. Afficher l'arbre
5. Afficher les enfants ou freres d'une personne (ordre decroissant)
6. Quitter
Choix :
```

Saisissez un chiffre (1 à 6), puis validez avec la touche **Entrée**.

### 1. Créer/Définir la racine (si inexistante)

- Si aucune racine n’existe encore, le programme vous demande de saisir :
  - Le **nom** de la racine.
  - L’**âge** de la racine.
- La « racine » est le premier membre de l’arbre, au plus haut niveau.

> **Exemple** :  
> Vous entrez « Alimata » comme nom, et 48 comme âge.  
> Le programme crée alors une première personne `Alimata, 48`.

### 2. Ajouter un enfant

- Le programme vous demande d’indiquer le **nom du parent** (existant dans l’arbre).  
- Ensuite, vous indiquez le **nom** et l’**âge** du nouvel enfant.  
- Si le parent est trouvé, l’enfant est ajouté comme **enfant** de ce parent.

> **Exemple** :  
> Vous tapez « Alimata » comme parent, puis « Job » et « 23 » comme enfant.  
> Le programme crée `Job, 23` comme enfant d’`Alimata, 48`.

### 3. Ajouter un frère/une sœur

- Le programme vous demande d’indiquer le **nom de la personne** à qui vous voulez ajouter un frère/une sœur.  
- Vous indiquez le **nom** et l’**âge** du nouveau frère/de la nouvelle sœur.  
- Si la personne est trouvée, le nouveau frère/soeur est ajouté **juste après** la personne indiquée dans la liste chaînée des frères/soeurs.

> **Exemple** :  
> Vous tapez « Alimata » comme personne, puis « Moussa » et « 55 » comme frère.  
> Désormais, `Moussa, 55` est le frère d’`Alimata, 48`.

### 4. Afficher l’arbre

- Cette option affiche l’intégralité de l’arbre (ou la « forêt » si plusieurs racines sont gérées) avec un **système d’indentation**.  
- Les **enfants** sont affichés sur la ligne suivante avec un niveau d’indentation supplémentaire (exemple : « .... »), et les **frères/soeurs** sont affichés au même niveau d’indentation.

> **Exemple de rendu** :
> ```
> Alimata, 48
> ....Job, 23
> ....Jeanne, 18
> ....Akim, 25
> ........Malic, 3
> ........Marie, 1
> ....Sadjdath, 16
> Moussa, 55
> ....Albert, 18
> Joseph, 39
> Pierre, 42
> ```

### 5. Afficher les enfants ou frères d’une personne (ordre décroissant)

- Le programme vous demande le **nom de la personne**.  
- Puis il vous propose de taper :
  - **1** pour afficher les **enfants** de cette personne (par âge décroissant).  
  - **2** pour afficher ses **frères/soeurs** (par âge décroissant).
- Si la personne a des enfants/frères/soeurs, ils sont listés du **plus âgé** au **moins âgé**.

> **Exemple** :  
> Vous tapez « Akim » comme nom de la personne, puis « 1 » (pour enfants).  
> S’il a deux enfants `Malic, 3` et `Marie, 1`, l’affichage en ordre décroissant donnera :
> ```
> Liste des enfants de Akim par ordre decroissant d'age :
> - Malic, 3
> - Marie, 1
> ```

### 6. Quitter

- Met fin au programme.

---

## 3. Remarques supplémentaires

1. **Recherche**  
   - Lorsqu’on vous demande le nom d’une personne (parent ou autre), le programme effectue une recherche récursive dans l’arbre (enfants, puis frères/soeurs).  
   - Si la personne n’est pas trouvée, un message l’indique.

2. **Ajout en tête**  
   - Lorsque vous ajoutez un enfant, celui-ci est inséré en **tête** de la liste des enfants existants.  
   - Lorsque vous ajoutez un frère/une sœur, il est inséré juste après la personne indiquée.

3. **Indentation**  
   - L’affichage utilise des points (`"...."`) pour marquer chaque niveau de profondeur.  
   - Vous pouvez modifier ce comportement en ajustant la fonction `afficherArbre()`.

4. **Mémoire**  
   - Dans un programme complet, vous pourriez ajouter une fonction pour libérer correctement toute la mémoire (parcours de l’arbre, `free` de chaque personne).  
   - Dans la version de démonstration, on n’illustre pas cette partie.

---

## 4. Conclusion

Ce programme permet de gérer **un arbre généalogique** avec un **menu simple** :
- **Création** de la racine,  
- **Ajout** d’enfants,  
- **Ajout** de frères/soeurs,  
- **Affichage** général de l’arbre,  
- **Affichage** sélectif (enfants ou frères/soeurs) par âge décroissant.
