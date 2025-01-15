#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
// cette bibliotheque permet dans notre code de mettre les mots en majuscule a l'aide de sa fonction toupper()
#include<math.h>
#include<windows.h>


int saisie_securisee();
void ajout_nouvel_eleve();
void vider_buffer();
double creation_d_identifiant(char *nom, char *prenom, int annee_etude);
int sauvegarde_etudiant(char *nom, char *prenom,int annee_etude, double identifiant );
int verification_matricule(double identifiant);
int nombre_de_ligne_identifiant();
void supprimer_un_caractere_specifique_dans_une_chaine(char a, char *chaine);
void sauvegarde_des_notes_etudiant(double identifiant);
void recherche_etudiant(double identifiant_etudiant,char *etudiant);
double saisie_securisee_double();
int annee(double identifiant);
const char *matiere1(int numero);
void pause(int milli_seconde);
const char *matiere2(int numero);
void calcul_et_affichage_de_moyenne(double identifiant);
int verification_notes(double identifiant);
int nombre_de_ligne_notes();
void lecture_notes(int identifiant,double *tableau_de_notes);
int coefficient_1(int num_matiere);
int coefficient_2(int num_matiere);
int verification_calcul_moyenne(double identifiant);
int nombre_de_ligne_moyenne1();
int nombre_de_ligne_moyenne2();
double moyenne(double identifiant);
void classement();

int main()
{
    printf("\nBienvenue dans le Gestionnaire des notes etudiants");
    int choix=0;
    do
    {
        printf("\n|(1)\tAjout nouvel etudiant\t|(2)\tCalcul d'une moyenne\t|(3)\tAfficher listes des etudiants\t|(0)\tSortie\t|\n");
        do
        {
            printf(">>> ");
            choix=saisie_securisee();
            if (choix!=1 && choix!=2 && choix!=3 && choix!=0)
            {
                printf("\nVous devez entrez entre 1, 2 , 3 et 0 !\n");
            }
        } while (choix!=1 && choix!=2 && choix!=3 && choix!=0);
        
        // nous faisons appel a la fonction switch pour le choix des options
        switch (choix)
        {
            case 1:
            {
                ajout_nouvel_eleve();

            }break;
            case 2:
            {
                printf("\nCalcul et affichage de moyenne ! \n");
                double identifiant_etudiant=0;
                int compteur=0;
                while (1)
                {
                    int arret=1;
                    compteur++;
                    // cette petite condition va permettre a ce que la phrase ne s'affichera qu'au 2eme tour
                    if (compteur!=1)
                    {
                        printf("\nVous pouvez entrez (0) dans le matricule pour arreter le calcul !\n");
                    }
                    printf("\nEtudiant %d : ",compteur);
                    printf("\nEntrez le matricule de l'etudiant %d : ",compteur);
                    int comfirmation=0;
                    do
                    {
                        printf("\n>>> ");
                        identifiant_etudiant=saisie_securisee_double();
                        // cette condition est la pour permettre l'arret de la boucle
                        if (identifiant_etudiant==0)
                        {
                            arret=0;
                            break;
                        }
                        
                        if (verification_matricule(identifiant_etudiant))
                        {
                            pause(1000);
                            printf("\n\tNumero Matricule : %.0lf",identifiant_etudiant);
                            char etudiant_nom_prenom[101];
                            recherche_etudiant(identifiant_etudiant,etudiant_nom_prenom);
                            pause(900);
                            printf("\n\tEtudiant(e) : %s\nEntrez (1) pour comfirmez et (0) pour infirmer : ",etudiant_nom_prenom);
                            do
                            {
                                printf("\n>>> ");
                                comfirmation=saisie_securisee();
                                if (comfirmation==0)
                                {
                                    printf("\nEntrez le matricule de l'etudiant %d : ",compteur);
                                }
                                
                            } while (comfirmation!=1 && comfirmation!=0);
                        }
                        else
                        {
                            printf("\nIdentifiant inexistant !");
                        }
                        
                    } while (!verification_matricule(identifiant_etudiant) || comfirmation!=1);
                    if (arret==0)
                    {
                        break;
                    }
                    else
                    {
                        calcul_et_affichage_de_moyenne(identifiant_etudiant);
                    }

                }
            }break;
            case 3:
            {
                printf("\nListes des etudiants en ordre de merite :");
                classement();
            }break;
            case 0:
            {
                
            }break;
            default:
            {
                return 1;
            }
            break;
        }
    } while (choix!=0);
    
    
    return 0;
}

int saisie_securisee()
{
    //cette fonction permet de saisir des entiers(uniquement) en gérant les cas d'erreurs 
    int entier=0, sortie_boucle=0;
    float reel_d_essai=0;
    char chaine_get_buffer=0;
    do
    {
        if (scanf("%f",&reel_d_essai)!=1)
        {
            // la condition 'if (scanf("%f",&reel_d_essai)!=1)' veut dire que si la personne entre une chaine de caractere (si la personne entre un reelcette condition n'est pas verifier)
            printf("\nEntrez un entier ! Reessayer !\n>>> ");
            vider_buffer();
            sortie_boucle=0;
        }
        else
        {
            float reel_prime=(int)reel_d_essai;

            // etant donne qu'on ne compare pas de reel comme on compare deux entiers
            if (reel_d_essai-reel_prime>0.00000000001)
            {
                printf("\nEntrez un entier ! Reessayer !\n>>> ");
                entier=saisie_securisee();
            }
            else
            {
                // a cet niveau, entier prends la partie reelle de reel d'essai
                entier=(int)reel_d_essai;
            }
            sortie_boucle=1;
            // sortie boucle=1 signifie que la condition a ete verifie
        }
    }while (sortie_boucle==0);
    vider_buffer();
    return entier;
}
void ajout_nouvel_eleve()
{
    struct etudiant
    {
        char nom[21];
        char prenom[101];
        int annee_etude;
        double identifiant;
    };
    // cette variable de type struct qui nous permettra de manipuler les informations relaitives a un(e) etudiant(e)
    int choix_d_entrer=0;
    struct etudiant nouvel_etudiant;
    printf("\nAjout nouvel etudiant(e) : ");
    printf("\nVous voulez ajoutez un seul etudiant (1) ou pluisieurs(0) ?\nChoisissez entre 1 et 0 :\n ");
    do
    {
        printf(">>> ");
        choix_d_entrer=saisie_securisee();
        if (choix_d_entrer!=1 && choix_d_entrer!=0)
        {
            printf("\nVous devez entrez entre 1 et 0 !\n");
        }
    } while (choix_d_entrer!=1 && choix_d_entrer!=0);

    if (choix_d_entrer==1)
    {
        printf("\nNom de l'etudiant(e) :\n>>> ");
        fgets(nouvel_etudiant.nom,20,stdin);
        nouvel_etudiant.nom[strlen(nouvel_etudiant.nom)-1]='\0';
        // cette ligne qui permet de supprimer l'aller a la ligne que prend la fonction fgets()

        for (int i = 0; i < strlen(nouvel_etudiant.nom); i++)
        {
            nouvel_etudiant.nom[i]=toupper(nouvel_etudiant.nom[i]);
        }
        // cette petite boucle permet de mettre le nom en majuscule si elle ne l'est pas déja
        printf("\nPrenoms de l'etudiant(e) (Entrez tous les prenoms et dans l'ordre de l'acte de naissance) :\n>>> ");
        fgets(nouvel_etudiant.prenom,100,stdin);
        nouvel_etudiant.prenom[strlen(nouvel_etudiant.prenom)-1]='\0';


        printf("\nL'etudiant(e) est en 1ere Annee ou en 2eme Annee ? \n");
        do
        {
            printf("\n>>> ");
            nouvel_etudiant.annee_etude=saisie_securisee();
            if (nouvel_etudiant.annee_etude!=1 && nouvel_etudiant.annee_etude!=2)
            {
                printf("\nChoisissez entre 1 et 2");
            }
        } while (nouvel_etudiant.annee_etude!=1 && nouvel_etudiant.annee_etude!=2);
        

        pause(1000);
        printf("\n\tL'etudiant(e) s'appele %s %s.",nouvel_etudiant.prenom,nouvel_etudiant.nom);
        pause(1000);
        printf("\n\tIl/Elle est en %de Annee d'etude au Cycle Preparatoire Pere Aupiais",nouvel_etudiant.annee_etude);
        pause(1000);

        // cette fonction permet de creer des identifiants pour chaque eleve
        nouvel_etudiant.identifiant= creation_d_identifiant(nouvel_etudiant.nom,nouvel_etudiant.prenom,nouvel_etudiant.annee_etude);
        if (verification_matricule(nouvel_etudiant.identifiant))
        {
            pause(1000);
            printf("\nCet etudiant a deja ete enregistre !");
        }
        else
        {
            pause(1000);
            printf("\n\tL'identifiant de %s %s est \"%.0lf\"",nouvel_etudiant.prenom,nouvel_etudiant.nom,nouvel_etudiant.identifiant);
            sauvegarde_etudiant(nouvel_etudiant.nom,nouvel_etudiant.prenom,nouvel_etudiant.annee_etude,nouvel_etudiant.identifiant);
        }
        
    }
    else if (choix_d_entrer==0)
    {
        for (int i = 0; 1 ; i++)
        {
            if (i!=0)
            {
                pause(900);
                printf("\nEntrez (0) pour le nom de l'etudiant si vous avez deja ajouter votre dernier etudiant !\n");
            }
            printf("\nEtudiant(e) %d : ",i+1);
            printf("\nNom de l'etudiant(e) %d :\n>>> ",i+1);
            fgets(nouvel_etudiant.nom,20,stdin);
            nouvel_etudiant.nom[strlen(nouvel_etudiant.nom)-1]='\0';
            // cette ligne qui permet de supprimer l'aller a la ligne que prend la fonction fgets()

            if (nouvel_etudiant.nom[0]=='0')
            {
                break;
            }
            for (int i = 0; i < strlen(nouvel_etudiant.nom); i++)
            {
                nouvel_etudiant.nom[i]=toupper(nouvel_etudiant.nom[i]);
            }
            // cette petite boucle permet de mettre le nom en majuscule si elle ne l'est pas déja
            printf("\nPrenoms de l'etudiant(e) %d (Entrez tous les prenoms et dans l'ordre de l'acte de naissance) :\n>>> ",i+1);
            fgets(nouvel_etudiant.prenom,100,stdin);
            nouvel_etudiant.prenom[strlen(nouvel_etudiant.prenom)-1]='\0';


            printf("\nL'etudiant(e) %d est en 1ere Annee ou en 2eme Annee ? \n",i+1);
            do
            {
                printf(">>> ");
                nouvel_etudiant.annee_etude=saisie_securisee();
                if (nouvel_etudiant.annee_etude!=1 && nouvel_etudiant.annee_etude!=2)
                {
                    printf("\nChoisissez entre 1 et 2");
                }
            } while (nouvel_etudiant.annee_etude!=1 && nouvel_etudiant.annee_etude!=2);
            

            pause(1000);
            printf("\n\tL'etudiant(e) %d s'appele %s %s.",i+1,nouvel_etudiant.prenom,nouvel_etudiant.nom);
            pause(1000);
            printf("\n\tIl/Elle est en %de Annee d'etude au Cycle Preparatoire Pere Aupiais",nouvel_etudiant.annee_etude);

            // cette fonction permet de creer des identifiants pour chaque eleve
            nouvel_etudiant.identifiant= creation_d_identifiant(nouvel_etudiant.nom,nouvel_etudiant.prenom,nouvel_etudiant.annee_etude);
            if (verification_matricule(nouvel_etudiant.identifiant))
            {
                pause(1000);
                printf("\nCet etudiant a deja ete enregistre !");
                i--;
            }
            else
            {
                pause(1000);
                printf("\n\tL'identifiant de %s %s est \"%.0lf\"",nouvel_etudiant.prenom,nouvel_etudiant.nom,nouvel_etudiant.identifiant);
                sauvegarde_etudiant(nouvel_etudiant.nom,nouvel_etudiant.prenom,nouvel_etudiant.annee_etude,nouvel_etudiant.identifiant);
            }
        }
        
    }
    else
    {
        exit(0);
    }
    pause(1000);
    printf("\nPriere toujours se rappeler de l'identifiant pour pouvoir acceder aux notes et autres !");
    
    // a partir d'ici, on demande a l'utilisateur si il evut saisir et sauvegarder les notes d'un etudiant
    // en faites, on aurait du le faire depuis  l'entree des donnees (nom, prenom, classe et autres...)
    // Mais comme, cle programme qui genere automatiquement l'identifiant et on a besoin de l'identifiantpour sauvegarder le notes, on n'a pas pu le faire directement
    
    printf("\n\nEntrez les notes des etudiants ?\nEntrez (1) pour un Oui et (0) pour un Non\n");
    int choix_save_notes=0;
    do
    {
        printf("\n>>> ");
        choix_save_notes=saisie_securisee();
        if (choix_save_notes!=1 && choix_save_notes!=0)
        {
            printf("\nVous devez choisir entre (1) et (0) ! ");
        }
    } while (choix_save_notes!=1 && choix_save_notes!=0);
    if (choix_save_notes==0)
    {
        
    }
    else if(choix_save_notes==1)
    {
        double identifiant_etudiant=0;
        int compteur=0;
        while (1)
        {
            int arret=1;
            compteur++;
            // cette petite condition va permettre a ce que la phrase ne s'affichera qu'au 2eme tour
            if (compteur!=1)
            {
                printf("\nVous pouvez entrez (0) dans le matricule pour arreter l'enregistrement !\n");
            }
            printf("\nEtudiant %d : ",compteur);
            printf("\nEntrez le matricule de l'etudiant %d : ",compteur);
            int comfirmation=0;
            do
            {
                printf("\n>>> ");
                identifiant_etudiant=saisie_securisee_double();
                // cette condition est la pour permettre l'arret de la boucle
                if (identifiant_etudiant==0)
                {
                    arret=0;
                    break;
                }
                
                if (verification_matricule(identifiant_etudiant))
                {
                    pause(1000);
                    printf("\n\tNumero Matricule : %.0lf",identifiant_etudiant);
                    char etudiant_nom_prenom[101];
                    recherche_etudiant(identifiant_etudiant,etudiant_nom_prenom);
                    pause(900);
                    printf("\n\tEtudiant(e) : %s\nEntrez (1) pour comfirmez et (0) pour infirmer : ",etudiant_nom_prenom);
                    do
                    {
                        printf("\n>>> ");
                        comfirmation=saisie_securisee();
                        if (comfirmation==0)
                        {
                            printf("\nEntrez le matricule de l'etudiant %d : ",compteur);
                        }
                        
                    } while (comfirmation!=1 && comfirmation!=0);
                }
                else
                {
                    printf("\nIdentifiant inexistant !");
                }
                
            } while (!verification_matricule(identifiant_etudiant) || comfirmation!=1);
            if (arret==0)
            {
                break;
            }
            else
            {
                sauvegarde_des_notes_etudiant(identifiant_etudiant);
            }

        }
        
        
    }
    else
    {
        exit(0);
    }
}
void vider_buffer()
{
    // cette fonction permet de vider le buffer pour eviter les erreurs avec l'utilisation de fgets() suivi de scanf
    int c=0;
    while (c!='\n' && c!=EOF)
    {
        c=getchar();
    }
}
double saisie_securisee_double()
{
    //cette fonction permet de saisir des entiers(uniquement) en gérant les cas d'erreurs 
    double reel=0, sortie_boucle=0;
    char chaine_get_buffer=0;
    do
    {
        if (scanf("%lf",&reel)!=1)
        {
            // la condition 'if (scanf("%f",&reel_d_essai)!=1)' veut dire que si la personne entre une chaine de caractere (si la personne entre un reelcette condition n'est pas verifier)
            printf("\nEntrez un reel ! Reessayer !\n>>> ");
            vider_buffer();
            sortie_boucle=0;
        }
        else
        {
            sortie_boucle=1;
            // sortie boucle=1 signifie que la condition a ete verifie
        }
    }while (sortie_boucle==0);
    vider_buffer();
    return reel;
}
void calcul_et_affichage_de_moyenne(double identifiant)
{
    if (verification_notes(identifiant) && !verification_calcul_moyenne(identifiant))
    {
        int nbre_matiere=0;
        if(annee(identifiant)==1)
        {
            nbre_matiere=12;
            double tableau_de_notes[nbre_matiere];
            lecture_notes(identifiant,tableau_de_notes);
            double somme=0,coef=0;
            
            for (int i = 0; i < nbre_matiere; i++)
            {
                somme+=tableau_de_notes[i]*coefficient_1(i);
                coef+=coefficient_1(i);
            }
            double moyenne=0;
            moyenne=somme/coef;
            char etudiant[101];
            recherche_etudiant(identifiant,etudiant);
            printf("\n\tLa moyenne de l'etudiant(e) \"%s\" est \"%.2lf\"\n",etudiant,moyenne);

            // moyenne deja calcule, on passe a l'enregistrement de la moyenne dans un fichier
            FILE *fichier=fopen("moyenne1.txt","a");
            if (fichier==NULL)
            {
                perror("\nErreur d'ouverture d'un fichier !");
                exit(0);
            }
            fprintf(fichier,"%.0lf*%.2lf\n",identifiant,moyenne);
            fclose(fichier);
            
        }
        else if(annee(identifiant)==2)
        {
            nbre_matiere=9;
            double tableau_de_notes[nbre_matiere];
            lecture_notes(identifiant,tableau_de_notes);
            double somme=0,coef=0;
            
            for (int i = 0; i < nbre_matiere; i++)
            {
                somme+=tableau_de_notes[i]*coefficient_2(i);
                coef+=coefficient_2(i);
            }
            double moyenne=0;
            moyenne=somme/coef;
            char etudiant[101];
            recherche_etudiant(identifiant,etudiant);
            printf("\n\tLa moyenne de l'etudiant(e) \"%s\" est \"%.2lf\"\n",etudiant,moyenne);

            // moyenne deja calcule, on passe a l'enregistrement de la moyenne dans un fichier
            FILE *fichier=fopen("moyenne2.txt","a");
            if (fichier==NULL)
            {
                perror("\nErreur d'ouverture d'un fichier !");
                exit(0);
            }
            fprintf(fichier,"%.0lf*%.2lf\n",identifiant,moyenne);
            fclose(fichier);
        }
        else
        {
            exit(0);
        }
    }
    else if (!verification_notes(identifiant))
    {
        sauvegarde_des_notes_etudiant(identifiant);
        calcul_et_affichage_de_moyenne(identifiant);
    }
    else if (verification_notes(identifiant) &&  verification_calcul_moyenne(identifiant))
    {
        pause(1000);
        printf("\nLa moyenne de cet(te) etudiant(e) a deja ete calculee !\n\tElle est de \"%.2lf\"",moyenne(identifiant));

    }
    
}
void lecture_notes(int identifiant,double *tableau_de_notes)
{
    // cette fonction permet de mettre les notes d'un etudiant auparavant deja enregistree dans un tableau de double
    int nbre_notes=0,nbre_line;
    if(annee(identifiant)==1)
    {
        nbre_notes=12;
        double n,identifiant_de_verification=0;

        // cherchons d'abord l'identifiant dans le fichier notes.txt et ensuite prenons cette ligne dans une variable char ligne[]
        FILE *fichier=fopen("notes.txt","r");
        if (fichier==NULL)
        {
            perror("\nErreur d'ouverture d'un fichier !");
        }
        char ligne[101];
        nbre_line=nombre_de_ligne_notes();
        for (int i = 0; i < nbre_line; i++)
        {

            fgets(ligne,101,fichier);
            char id[15];
            for (int j = 0; j < 12; j++)
            {
                id[j]=ligne[j];
            }
            char *end=NULL;
            identifiant_de_verification =strtod(id,&end);
            if (fabs(identifiant_de_verification-identifiant)<1)
            {
                break;
            }
            
        }
        // bon, a partir de cette ligne, on est censee avoir toutes les informations sur la note mais en bloc dans la variable char

        // passons au debriefing (analyse de char ligne[101])
        int len=strlen(ligne);
        char notes[6];
        int compteur=0;
        for (int i = 0; i < len; i++)
        {
            int k=0;
            if (ligne[i]=='*' && compteur<=nbre_notes)
            {
                for (int j = i+1; k < 5; j++)
                {
                    notes[k]=ligne[j];
                    k++;
                }
                char *end=NULL;
                n=strtod(notes,&end);
                tableau_de_notes[compteur]=n;
                compteur++;
            }
        }
        fclose(fichier);
    }
    else if(annee(identifiant)==2)
    {
        nbre_notes=9;
        double n,identifiant_de_verification=0;

        // cherchons d'abord l'identifiant dans le fichier notes.txt et ensuite prenons cette ligne dans une variable char ligne[]
        FILE *fichier=fopen("notes.txt","r");
        if (fichier==NULL)
        {
            perror("\nErreur d'ouverture d'un fichier !");
        }
        char ligne[101];
        nbre_line=nombre_de_ligne_notes();
        for (int i = 0; i < nbre_line; i++)
        {

            fgets(ligne,101,fichier);
            char id[15];
            for (int j = 0; j < 12; j++)
            {
                id[j]=ligne[j];
            }
            char *end=NULL;
            identifiant_de_verification =strtod(id,&end);
            if (fabs(identifiant_de_verification-identifiant)<1)
            {
                break;
            }
            
        }
        // bon, a partir de cette ligne, on est censee avoir toutes les informations sur la note mais en bloc dans la variable char

        // passons au debriefing (analyse de char ligne[101])
        int len=strlen(ligne);
        char notes[6];
        int compteur=0;
        for (int i = 0; i < len; i++)
        {
            int k=0;
            if (ligne[i]=='*' && compteur<=nbre_notes)
            {
                for (int j = i+1; k < 5; j++)
                {
                    notes[k]=ligne[j];
                    k++;
                }
                char *end=NULL;
                n=strtod(notes,&end);
                tableau_de_notes[compteur]=n;
                compteur++;
            }
        }
        fclose(fichier);
    }
    else
    {
        exit(0);
    }
}
// a partir d'ici ce sont les fonctions de bachar
double creation_d_identifiant(char *nom, char *prenom, int annee_etude)
{
    double identifiant=0;
    int a=(int)prenom[0];
    int b=(int)prenom[2];
    int c=(int)nom[0];
    int d=(int)nom[2];
    while (a>=100)
    {
        a=(int)(a/2);
    }
    while (b>=100)
    {
        b=(int)(b/2);
    }
    while (c>=100)
    {
        c=(int)(c/2);
    }
    while (d>=100)
    {
        d=(int)(d/2);
    }
    
    identifiant= annee_etude*1000000000 + a + b*100 + c*10000 + d*1000000;
    return identifiant;
}
void recherche_etudiant(double identifiant_etudiant,char *etudiant)
{
    FILE *fichier=fopen("donnee.txt","r");
    int nbre=nombre_de_ligne_identifiant(),compteur=0;
    char ligne[101],identifiant[12];
    if (fichier==NULL)
    {
        perror("\nErreur lors de l'ouverture d'un fichier !");
        exit(0);
    }
    for (int i = 0; i < nbre; i++)
    {
        compteur=0;
        fgets(ligne,101,fichier);
        supprimer_un_caractere_specifique_dans_une_chaine('\n',ligne);
        // cette boucle sert a rechercher l'identifiant dans la ligne lue
        int len=strlen(ligne);
        for (int j = 0; j < len; j++)
        {
            
            if (ligne[j]=='*')
            {
                compteur++;
                if (compteur==3)
                {
                    int l=0;
                    for (int k = j+1; k<len-1; k++)
                    {
                        identifiant[l]=ligne[k];
                        l++;
                    }
                    identifiant[l]='\0';
                    break;
                }
            }
            
        }
        // bon, a partir de cette ligne, on a l'identifiant en main
        // on le met d'abord dans une variable de type double parceque pour le moment, il est char
        double identifiant_lu=0;
        char *end=NULL;

        identifiant_lu=strtod(identifiant,&end);
        if (fabs(identifiant_lu-identifiant_etudiant)<1)
        {
            compteur=0;
            // si ce si est verifie c quon a trouve l'etudiant dont l'identifiant est en parametre de fonction
            char etudiant_trouve[101];
            int repere=0;
            // cette boucle permet de prendre le nom et le prenom sans les asteris au milieu
            for (int i = 0 ; i < strlen(ligne) ; i++)
            {
                if (ligne[i]!='*')
                {
                    if (repere==0)
                    {
                        etudiant_trouve[i]=ligne[i];
                    }
                    else if(repere==1)
                    {
                        etudiant_trouve[i]=ligne[i];
                    }
                    else
                    {
                        etudiant_trouve[i]='\0';
                        break;
                    }
                }
                else
                {
                    repere++;
                    etudiant_trouve[i]=' ';
                }
            }
            
            strcpy(etudiant,etudiant_trouve);
        }
    }
    fclose(fichier);
}
int nombre_de_ligne_moyenne1()
{
    int nbre=0;
    FILE *fichier=fopen("moyenne1.txt","r");
    if (fichier==NULL)
    {
        perror("\nOuverture lors de l'ouverture d'un fichier !");
        return 1;
    }
    char caractere_de_comptage=0;
    do
    {
        caractere_de_comptage=getc(fichier);
        if (caractere_de_comptage=='\n')
        {
            nbre++;
        }
    } while (caractere_de_comptage!=EOF);
    fclose(fichier);
    return nbre;
}
int nombre_de_ligne_moyenne2()
{
    int nbre=0;
    FILE *fichier=fopen("moyenne2.txt","r");
    if (fichier==NULL)
    {
        perror("\nOuverture lors de l'ouverture d'un fichier !");
        return 1;
    }
    char caractere_de_comptage=0;
    do
    {
        caractere_de_comptage=getc(fichier);
        if (caractere_de_comptage=='\n')
        {
            nbre++;
        }
    } while (caractere_de_comptage!=EOF);
    fclose(fichier);
    return nbre;
} 

void classement()
{
    // cette fonction fait le classement des etudiants en prenants en compte leurs moyenne uniquement
    // ce qui veut dire que si la moyenne d'un etudiant n'a pas encore ete calcule, le classements se fera sans lui
    printf("\n1ere annee !");
    int nbre_line=nombre_de_ligne_moyenne1();
    double tableau_note_identifiant[nbre_line][2];
    FILE *fichier=fopen("moyenne1.txt","r");
    if (fichier==NULL)
    {
        perror("\nErreur d'ouverture d'un fichier !");
    }
    char ligne[101];
    for (int i = 0; i < nbre_line; i++)
    {
        int repere=0;
        // la variable repere va me servir pour lire la ligne : voyons voir comment je fais cela :-)
        fgets(ligne,101,fichier);
        char id[12];
        char moy[6];
        char *end=NULL;
        int k=0;
        for (int j = 0; j < strlen(ligne); j++)
        {
            if (repere==1)
            {
                moy[k]=ligne[j];
                k++;
            }
            else if(ligne[j]!='*' && repere==0)
            {
                id[j]=ligne[j];
            }
            else if(ligne[j]=='*')
            {
                repere=1;
                // repere=1 va me permettre de ne plus entrer dans le if precedent mais pas la meme me permettre d'entrer le premier
            }
        }
        tableau_note_identifiant[i][0]=strtod(id,&end);
        tableau_note_identifiant[i][1]=strtod(moy,&end);
    }
    fclose(fichier);
    // bon a partir de cette ligne on a la liste de tout les identifiants avec les moyennes deja calcule
    // on passe au classements

    double moyenne_id_range[nbre_line][2];

    // on fait la petite boucle classique imbriquee (for dans for) pour le rangement
    
    for (int i = 0; i < nbre_line; i++)
    {
        int repere=0;
        double maj=0;
        for (int j = 0; j < nbre_line; j++)
        {
            if(maj<tableau_note_identifiant[j][1])
            {
                maj=tableau_note_identifiant[j][1];
                repere=j;
            }
        }
        moyenne_id_range[i][1]=maj;
        tableau_note_identifiant[repere][1]=0;
        moyenne_id_range[i][0]=tableau_note_identifiant[repere][0];
    }

    // a la fin de cette boucle, les moyennes et les identifiants doivent se retrouver en ordre decroissant dans le double moyenne_id_range

    for (int i = 0; i < nbre_line; i++)
    {
        char etudiant[101];
        recherche_etudiant(moyenne_id_range[i][0],etudiant);
        pause(900);
        if(i==0)
        {
            printf("\n\t1er => %s avec %.2lf de moyenne. ",etudiant,moyenne_id_range[i][1]);
        }
        else
        {
            printf("\n\t%deme => %s avec %.2lf de moyenne. ",i+1,etudiant,moyenne_id_range[i][1]);
        }
    }

    printf("\n2eme annee !");
    nbre_line=nombre_de_ligne_moyenne2();
    double tableau_note_identifiant_2[nbre_line][2];
    FILE *fichier1=fopen("moyenne2.txt","r");
    if (fichier1==NULL)
    {
        perror("\nErreur d'ouverture d'un fichier !");
    }
    for (int i = 0; i < nbre_line; i++)
    {
        int repere=0;
        // la variable repere va me servir pour lire la ligne : voyons voir comment je fais cela :-)
        fgets(ligne,101,fichier1);
        char id[12];
        char moy[6];
        char *end=NULL;
        int k=0;
        for (int j = 0; j < strlen(ligne); j++)
        {
            if (repere==1)
            {
                moy[k]=ligne[j];
                k++;
            }
            else if(ligne[j]!='*' && repere==0)
            {
                id[j]=ligne[j];
            }
            else if(ligne[j]=='*')
            {
                repere=1;
                // repere=1 va me permettre de ne plus entrer dans le if precedent mais pas la meme me permettre d'entrer le premier
            }
        }
        tableau_note_identifiant_2[i][0]=strtod(id,&end);
        tableau_note_identifiant_2[i][1]=strtod(moy,&end);
    }
    fclose(fichier1);
    // bon a partir de cette ligne on a la liste de tout les identifiants avec les moyennes deja calcule
    // on passe au classements

    double moyenne_id_range_2[nbre_line][2];

    // on fait la petite boucle classique imbriquee (for dans for) pour le rangement
    
    for (int i = 0; i < nbre_line; i++)
    {
        int repere=0;
        double maj=0;
        for (int j = 0; j < nbre_line; j++)
        {
            if(maj<tableau_note_identifiant_2[j][1])
            {
                maj=tableau_note_identifiant_2[j][1];
                repere=j;
            }
        }
        moyenne_id_range_2[i][1]=maj;
        tableau_note_identifiant_2[repere][1]=0;
        moyenne_id_range_2[i][0]=tableau_note_identifiant_2[repere][0];
    }

    // a la fin de cette boucle, les moyennes et les identifiants doivent se retrouver en ordre decroissant dans le double moyenne_id_range

    for (int i = 0; i < nbre_line; i++)
    {
        char etudiant[101];
        recherche_etudiant(moyenne_id_range_2[i][0],etudiant);
        pause(900);
        if(i==0)
        {
            printf("\n\t1er => %s avec %.2lf de moyenne. ",etudiant,moyenne_id_range_2[i][1]);
        }
        else
        {
            printf("\n\t%deme => %s avec %.2lf de moyenne. ",i+1,etudiant,moyenne_id_range_2[i][1]);
        }
    }
}

// a partir d'ici, ce sont les fonctions de Laurette

int verification_matricule(double identifiant)
{
    // cette fonction sert a verifier l'existence d'une matricule(identifiant)
    // si le matricule est trouve ca retourne 1 si non ca retourne 0;
    int reussite=0,nbre=nombre_de_ligne_identifiant();
    char ligne[15];
    double identifiant_de_verification=0;
    FILE *fichier=fopen("identifiant.txt","r");
    if (fichier==NULL)
    {
        printf("\nOuverture d'un fichier impossible !");
        return 2;
    }
    
    for (int i = 0; i < nbre; i++)
    {
        fgets(ligne,15,fichier);
        
        supprimer_un_caractere_specifique_dans_une_chaine('\n',ligne);
        char *end=NULL;
        identifiant_de_verification=strtod(ligne,&end);
        if (fabs(identifiant-identifiant_de_verification)<1)
        {
            reussite=1;
            break;
        }
    }
    
    fclose(fichier);
    return reussite;
}
void sauvegarde_des_notes_etudiant(double identifiant)
{
    printf("\nSauvegarde des notes : ");
    // la on aura besoin de l'annee d'etude de l'eleve car les matieres varient en fonction de l'annee 
    // c pour ca la fonction annee() retourne l'annee en prenant l'identifiant
    if (annee(identifiant)==1)
    {
        double tableau_des_notes[12];
        int verification=0;
        do
        {
            for (int i = 0; i < 12; i++)
            {
                do
                {
                    printf("\n\t%s : ",matiere1(i+1));
                    tableau_des_notes[i]=saisie_securisee_double();
                    if(tableau_des_notes[i]>20 || tableau_des_notes[i]<0)
                    {
                        printf("\nLa note de l'etudiant doit etre comprise entre 0 et 20 (strictement) ! ");
                    }
                } while (tableau_des_notes[i]>20 || tableau_des_notes[i]<0);
            }
            pause(1000);
            printf("\nEtes vous sure que vos notes sont les suivantes : ");
            for ( int i = 0; i < 12; i++)
            {
                pause(900);
                printf("\n\t%s => %.2lf",matiere1(i+1),tableau_des_notes[i]);
            }
            printf("\nEntrez (1) pour un oui et (0) pour un non : ");
            do
            {
                printf("\n>>> ");
                verification=saisie_securisee();
                if (verification!=1 && verification!=0)
                {
                    
                    printf("\nVous devez entrez entre (1) et (0) !");
                }
            } while (verification!=1 && verification!=0);
            if (verification==0)
            {
                printf("\nReprenez alors la saisie des notes !");
            }
        } while (verification!=1);
        // a partir de cette ligne, les notes sont deja dans une variable il reste donc a les enregistre dans le fichier notes.txt

        FILE *fichier_notes=fopen("notes.txt","a");
        if(fichier_notes==NULL)
        {
            perror("\nErreur lors de l'ouverture d'un fichier !\n");
            exit(0);
        }
        fprintf(fichier_notes,"%.0lf*",identifiant);
        for (int i = 0; i < 12; i++)
        {
            fprintf(fichier_notes,"%.2lf*",tableau_des_notes[i]);
            if(i==11)
            {
                fprintf(fichier_notes,"\n");
            }
        }
        printf("\nReussite de l'enregistrement des notes !");
        fclose(fichier_notes);
    }
    else if (annee(identifiant)==2)
    {
        double tableau_des_notes[9];
        int verification=0;
        do
        {
            for (int i = 0; i < 9; i++)
            {
                do
                {
                    printf("\n\t%s : ",matiere2(i+1));
                    tableau_des_notes[i]=saisie_securisee_double();
                    if(tableau_des_notes[i]>20 || tableau_des_notes[i]<0)
                    {
                        printf("\nLa note de l'etudiant doit etre comprise entre 0 et 20 (strictement) ! ");
                    }
                } while (tableau_des_notes[i]>20 || tableau_des_notes[i]<0);
            }
    
            printf("\nEtes vous sure que vos notes sont les suivantes : ");
            for ( int i = 0; i < 9; i++)
            {
                pause(900);
                printf("\n\t%s => %.2lf",matiere2(i+1),tableau_des_notes[i]);
            }
            printf("\nEntrez (1) pour un oui et (0) pour un non : ");
            do
            {
                printf("\n>>> ");
                verification=saisie_securisee();
                if (verification!=1 && verification!=0)
                {
                    
                    printf("\nVous devez entrez entre (1) et (0) !");
                }
            } while (verification!=1 && verification!=0);
            if (verification==0)
            {
                printf("\nReprenez alors la saisie des notes !");
            }
        } while (verification!=1);
        // a partir de cette ligne, les notes sont deja dans une variable il reste donc a les enregistre dans le fichier notes.txt

        FILE *fichier_notes=fopen("notes.txt","a");
        if(fichier_notes==NULL)
        {
            perror("\nErreur lors de l'ouverture d'un fichier !\n");
            exit(0);
        }
        fprintf(fichier_notes,"%.0lf*",identifiant);
        for (int i = 0; i < 9; i++)
        {
            fprintf(fichier_notes,"%.2lf*",tableau_des_notes[i]);
            if(i==8)
            {
                fprintf(fichier_notes,"\n");
            }
        }
        printf("\nReussite de l'enregistrement des notes !");
        fclose(fichier_notes);
    }
    else
    {
        printf("\nIdentidiant invalide !");
    }
}
int annee(double identifiant)
{
    if ((int)(identifiant/1000000000)==2)
    {
        return 2;
    }
    else if ((int)(identifiant/1000000000)==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void pause(int milli_seconde)
{
    // cette fonction fait une pause de n milliseconde lorsquelle est appele car parfois les resulatats sonts trop brusques a affichees
    Sleep(milli_seconde);
}
int nombre_de_ligne_notes()
{
    int nbre=0;
    FILE *fichier=fopen("notes.txt","r");
    if (fichier==NULL)
    {
        perror("\nOuverture lors de l'ouverture d'un fichier !");
        return 1;
    }
    char caractere_de_comptage=0;
    do
    {
        caractere_de_comptage=getc(fichier);
        if (caractere_de_comptage=='\n')
        {
            nbre++;
        }
    } while (caractere_de_comptage!=EOF);
    fclose(fichier);
    return nbre;
}
// A PARTIR D'ICI, CE SONT LES FONCTIONS DE NAWAL

int nombre_de_ligne_identifiant()
{
    int nbre=0;
    FILE *fichier=fopen("identifiant.txt","r");
    if (fichier==NULL)
    {
        perror("\nOuverture lors de l'ouverture d'un fichier !");
        return 1;
    }
    char caractere_de_comptage=0;
    do
    {
        caractere_de_comptage=getc(fichier);
        if (caractere_de_comptage=='\n')
        {
            nbre++;
        }
    } while (caractere_de_comptage!=EOF);
    fclose(fichier);
    return nbre;
}
void supprimer_un_caractere_specifique_dans_une_chaine(char a, char *chaine)
{
    for (int i = 0; i < strlen(chaine); i++)
    {
        if (chaine[i]==a)
        {
            chaine[i]='\0';
            break;
        }
        
    }
    
}

int verification_notes(double identifiant)
{
    // cette fonction prend en parametre un identifiant et verifie si ces notes ont deja ete enregistre

    int reussite=0,nbre=nombre_de_ligne_notes();
    char ligne[101];
    double identifiant_de_verification=0;
    FILE *fichier=fopen("notes.txt","r");
    if (fichier==NULL)
    {
        printf("\nOuverture d'un fichier impossible !");
        return 2;
    }
    
    for (int i = 0; i < nbre; i++)
    {
        fgets(ligne,101,fichier);
        
        supprimer_un_caractere_specifique_dans_une_chaine('\n',ligne);
        char *end=NULL;
        char id[15];
        // cette variable id va me permettre de prendre l'identifiant seul etant donne que dans ligne, c l'identifiant et les notes
        // pour cela, j'entre dans une boucle for
        for (int i = 0; i < 11; i++)
        {
            id[i]=ligne[i];
        }
        identifiant_de_verification=strtod(id,&end);
        if (fabs(identifiant-identifiant_de_verification)<1)
        {
            reussite=1;
            break;
        }
    }
    
    fclose(fichier);
    return reussite;
}

int verification_calcul_moyenne(double identifiant)
{
    // cette fonction prend en parametre un identifiant et verifie si sa moyenne a deja ete calcule
    if (annee(identifiant)==1)
    {
        int reussite=0,nbre=nombre_de_ligne_moyenne1();
        char ligne[101];
        double identifiant_de_verification=0;
        FILE *fichier=fopen("moyenne1.txt","r");
        if (fichier==NULL)
        {
            printf("\nOuverture d'un fichier impossible !");
            return 2;
        }
        
        for (int i = 0; i < nbre; i++)
        {
            fgets(ligne,101,fichier);
            
            supprimer_un_caractere_specifique_dans_une_chaine('\n',ligne);
            char *end=NULL;
            char id[15];
            // cette variable id va me permettre de prendre l'identifiant seul etant donne que dans ligne, c l'identifiant et les notes
            // pour cela, j'entre dans une boucle for
            for (int i = 0; i < 11; i++)
            {
                id[i]=ligne[i];
            }
            identifiant_de_verification=strtod(id,&end);
            if (fabs(identifiant-identifiant_de_verification)<1)
            {
                reussite=1;
                break;
            }
            fclose(fichier);
        }
        return reussite;
    }
    else if (annee(identifiant)==2)
    {
        int reussite=0,nbre=nombre_de_ligne_moyenne2();
        char ligne[101];
        double identifiant_de_verification=0;
        FILE *fichier=fopen("moyenne2.txt","r");
        if (fichier==NULL)
        {
            printf("\nOuverture d'un fichier impossible !");
            return 2;
        }
        
        for (int i = 0; i < nbre; i++)
        {
            fgets(ligne,101,fichier);
            
            supprimer_un_caractere_specifique_dans_une_chaine('\n',ligne);
            char *end=NULL;
            char id[15];
            // cette variable id va me permettre de prendre l'identifiant seul etant donne que dans ligne, c l'identifiant et les notes
            // pour cela, j'entre dans une boucle for
            for (int i = 0; i < 11; i++)
            {
                id[i]=ligne[i];
            }
            identifiant_de_verification=strtod(id,&end);
            if (fabs(identifiant-identifiant_de_verification)<1)
            {
                reussite=1;
                break;
            }
            fclose(fichier);
        }
        return reussite;
    }
    else
    {
        exit(0);
    }
}
