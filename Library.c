#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<windows.h>
 
//declaration d'enregistrement ouvrage

	typedef struct{
		char titre[40];
		char cote[100];
		int nbr_exmp;
		int nbr_exmp_empr;
	}ouvrage;

//declaration d'engreistrement etudiant

	typedef struct{
		char matricule[20];
		char type_abnmt[1];
		int penalite;
	}etudiant;

//declaration d'enregistrement ouvrage emprunte

	typedef struct{
		char matricule[20];
		char cote[100];
		int date_emprunte_jour;
		int date_emprunte_mois;
		int date_emprunte_anne;
		int date_retour_jour;
		int date_retour_mois;
		int date_retour_anne;
	}emprunte;

//declaration type date
	
	typedef struct{
		int jour_demprunte;
		int jour_retour;
		int dure_jour;
		int dure_mois;
		int dure_anne;
	}date;
	
//declaration de file d'attente

	typedef struct{
		char matricule[20];
		char cote[100];
	}file_dattente;	

//procedure de veridication si louvrage existe deja

	int test_if_ouvrage_existe(char titre[40],char cote[100]){
		int test=0;
		ouvrage ovrg;
		FILE*fovrg;
		fovrg=fopen("Fouvrage.txt","r");
		while(fread(&ovrg,sizeof(ouvrage),1,fovrg)){
			if(strcmp(ovrg.cote,cote)==0 && strcmp(ovrg.titre,titre)==0){
				test=1;
			}
		}
		fclose(fovrg);
		return test;
	}	
	
//procedure d'insertion dans la liste des ouvrage

	void insertion_ouvrage(ouvrage ovrg){
		if(test_if_ouvrage_existe(ovrg.titre,ovrg.cote)==0){
			FILE*fovrg=NULL;
			fovrg=fopen("Fouvrage.txt","a");
			fwrite(&ovrg,sizeof(ouvrage),1,fovrg);
			fclose(fovrg);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("\n\n L'ouvrage %s a ete ajouter\n\n",ovrg.titre);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}else{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n L'ouvrage de titre: %s ,cote: %s deja existe \n\n",ovrg.titre,ovrg.cote);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}


//procedure de veridication si l'etudiant existe deja

	int test_if_etudiant_existe(char matricule[20]){
		int test=0;
		etudiant etd;
		FILE*fetd;
		fetd=fopen("Fetudiant.txt","r");
		while(fread(&etd,sizeof(etudiant),1,fetd)){
			if(strcmp(etd.matricule,matricule)==0){
				test=1;
			}
		}
		fclose(fetd);
		return test;
	}	


//procedure d'insertion dans la liste des etudiant

	void insertion_etudiant(etudiant etd){
		if(test_if_etudiant_existe(etd.matricule)==0){
			FILE*fetd=NULL;
			fetd=fopen("Fetudiant.txt","a");
			fwrite(&etd,sizeof(etudiant),1,fetd);
			fclose(fetd);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("\n\n L'etudiant qui a le matricule %s a ete ajouter\n\n",etd.matricule);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}else{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n L'etudiant de matricule: %s deja existe \n\n",etd.matricule);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}	
	}



//procedure de veridication si l'emprunte existe deja

	int test_if_emprunte_existe(char matricule[20],char cote[100]){
		int test=0;
		emprunte emprnt;
		FILE*femprnt;
		femprnt=fopen("Femprunte.txt","r");
		while(fread(&emprnt,sizeof(emprunte),1,femprnt)){
			if(strcmp(emprnt.cote,cote)==0 && strcmp(emprnt.matricule,matricule)==0){
				test=1;
			}
		}
		fclose(femprnt);
		return test;
	}	

//procedure d'insertion dans la liste des emprunt

	void insertion_emprunte(emprunte emprnt){
		
		if(test_if_emprunte_existe(emprnt.matricule,emprnt.cote)==0){
			
			int if_there_is_an_incrementation=0;
			if(recherche_if_ouvrage_exist(emprnt.cote)==1 && consulter_un_membre_test(emprnt.matricule)==1){
			
				if(recherche_if_penalite_below7(emprnt.matricule)==1 && verification_disponibilite_ovrg_test(emprnt.cote)==1)
			 	{
					 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	        		printf("\n\n Donner la date d'emprunte : \n\n");
	        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	        		printf("\n\n Donner l'annee 'Entre 2015 et 2023' : ");
	        		scanf("%d",&emprnt.date_emprunte_anne);	
	        		while(emprnt.date_emprunte_anne>2023 || emprnt.date_emprunte_anne<2015){
	        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		        		printf("\n\n Donner l'annee 'Entre 2015 et 2023': ");
		        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        		scanf("%d",&emprnt.date_emprunte_anne);		        			
					}
	        		printf("\n\n Donner le mois 'Entre 1 et 12' : ");
	        		scanf("%d",&emprnt.date_emprunte_mois);
	        		while(emprnt.date_emprunte_mois>12 || emprnt.date_emprunte_mois<1){
	        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		        		printf("\n\n Donner le mois 'Entre 1 et 12': ");
		        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        		scanf("%d",&emprnt.date_emprunte_mois);		        			
					}
					
					switch(emprnt.date_emprunte_mois){
						case 1:
						case 5:
						case 7:
						case 8:
						case 10:
						case 12:{
		
			        		printf("\n\n Donner le jour 'Entre 1 et 31' : ");
			        		scanf("%d",&emprnt.date_emprunte_jour);
			        		while(emprnt.date_emprunte_jour>31 || emprnt.date_emprunte_jour<1){
			        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				        		printf("\n\n Donner le jour 'Entre 1 et 31': ");
				        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				        		scanf("%d",&emprnt.date_emprunte_jour);		        			
							}
							break;
						}
						case 2:{
							if(emprnt.date_emprunte_anne==2016||emprnt.date_emprunte_anne==2020){
				        		printf("\n\n Donner le jour 'Entre 1 et 29' : ");
				        		scanf("%d",&emprnt.date_emprunte_jour);
				        		while(emprnt.date_emprunte_jour>29 || emprnt.date_emprunte_jour<1){
				        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					        		printf("\n\n Donner le jour 'Entre 1 et 29': ");
					        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					        		scanf("%d",&emprnt.date_emprunte_jour);		        			
								}								
							}else{
				        		printf("\n\n Donner le jour 'Entre 1 et 28' : ");
				        		scanf("%d",&emprnt.date_emprunte_jour);
				        		while(emprnt.date_emprunte_jour>28 || emprnt.date_emprunte_jour<1){
				        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					        		printf("\n\n Donner le jour 'Entre 1 et 28': ");
					        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					        		scanf("%d",&emprnt.date_emprunte_jour);		        			
								}									
							}
							break;
						} 
						default:{
				        		printf("\n\n Donner le jour 'Entre 1 et 30' : ");
				        		scanf("%d",&emprnt.date_emprunte_jour);
				        		while(emprnt.date_emprunte_jour>30 || emprnt.date_emprunte_jour<1){
				        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					        		printf("\n\n Donner le jour 'Entre 1 et 30': ");
					        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					        		scanf("%d",&emprnt.date_emprunte_jour);		        			
								}									
							break;
						}     	
					}
	
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);							        		
	        		printf("\n\n Donner la date de retour : \n\n");
	        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	        								
	        		printf("\n\n Donner l'annee 'Entre %d et 2023' : ",emprnt.date_emprunte_anne);
	        		scanf("%d",&emprnt.date_retour_anne);	
	        		while(emprnt.date_retour_anne>2023 || emprnt.date_retour_anne<emprnt.date_emprunte_anne){
	        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		        		printf("\n\n Donner l'annee 'Entre %d et 2023' (superieur ou egal a l'anne d'emprunt): ",emprnt.date_emprunte_anne);
		        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        		scanf("%d",&emprnt.date_retour_anne);		        			
					}
	        		printf("\n\n Donner le mois 'Entre 1 et 12' : ");
	        		scanf("%d",&emprnt.date_retour_mois);
	        		while(emprnt.date_retour_mois>12 || emprnt.date_retour_mois<1){
	        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		        		printf("\n\n Donner le mois 'Entre 1 et 12': ");
		        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        		scanf("%d",&emprnt.date_retour_mois);		        			
					}
					
					if(emprnt.date_emprunte_mois==emprnt.date_retour_mois&&emprnt.date_emprunte_anne==emprnt.date_retour_anne){
						
					
						switch(emprnt.date_retour_mois){
							case 1:
							case 5:
							case 7:
							case 8:
							case 10:
							case 12:{

				        		printf("\n\n Donner le jour 'Entre %d et 31' : ",emprnt.date_emprunte_jour+1);
				        		scanf("%d",&emprnt.date_retour_jour);
				        		while(emprnt.date_retour_jour>31 || emprnt.date_retour_jour<=emprnt.date_emprunte_jour){
				        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					        		printf("\n\n Donner le jour 'Entre %d et 31'{la date de retour toujour superieur a date emprunte} : ",emprnt.date_emprunte_jour+1);
					        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					        		scanf("%d",&emprnt.date_retour_jour);		        			
								}
								
								break;
							}
							case 2:{
								if(emprnt.date_retour_anne==2016||emprnt.date_retour_anne==2020){
									
					        		printf("\n\n Donner le jour 'Entre %d et 29' : ",emprnt.date_emprunte_jour+1);
					        		scanf("%d",&emprnt.date_retour_jour);
					        		while(emprnt.date_retour_jour>29 || emprnt.date_retour_jour<=emprnt.date_emprunte_jour){
					        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						        		printf("\n\n Donner le jour 'Entre %d et 29'{la date de retour toujour superieur a date emprunte}: ",emprnt.date_emprunte_jour+1);
						        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						        		scanf("%d",&emprnt.date_retour_jour);		        			
									}								
								}else{
					        		printf("\n\n Donner le jour 'Entre %d et 28' : ",emprnt.date_emprunte_jour+1);
					        		scanf("%d",&emprnt.date_retour_jour);
					        		while(emprnt.date_retour_jour>28 || emprnt.date_retour_jour<=emprnt.date_emprunte_jour){
					        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						        		printf("\n\n Donner le jour 'Entre %d et 28'{la date de retour toujour superieur a date emprunte}: ",emprnt.date_emprunte_jour+1);
						        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						        		scanf("%d",&emprnt.date_retour_jour);		        			
									}									
								}
								break;
							} 
							default:{
					        		printf("\n\n Donner le jour 'Entre %d et 30' : ",emprnt.date_emprunte_jour+1);
					        		scanf("%d",&emprnt.date_retour_jour);
					        		while(emprnt.date_retour_jour>30 || emprnt.date_retour_jour<=emprnt.date_emprunte_jour){
					        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						        		printf("\n\n Donner le jour 'Entre %d et 30':{la date de retour toujour superieur a date emprunte} ",emprnt.date_emprunte_jour+1);
						        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						        		scanf("%d",&emprnt.date_retour_jour);		        			
									}									
								break;
							}     	
						}
					}else{
						
					
						switch(emprnt.date_retour_mois){
							case 1:
							case 5:
							case 7:
							case 8:
							case 10:
							case 12:{
								
								
				        		printf("\n\n Donner le jour 'Entre 1 et 31' : ");
				        		scanf("%d",&emprnt.date_retour_jour);
				        		while(emprnt.date_retour_jour>31 || emprnt.date_retour_jour<1){
				        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					        		printf("\n\n Donner le jour 'Entre 1 et 31': ");
					        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					        		scanf("%d",&emprnt.date_retour_jour);		        			
								}
								
								break;
							}
							case 2:{
								if(emprnt.date_retour_anne==2016||emprnt.date_retour_anne==2020){
					        		printf("\n\n Donner le jour 'Entre 1 et 29' : ");
					        		scanf("%d",&emprnt.date_retour_jour);
					        		while(emprnt.date_retour_jour>29 || emprnt.date_retour_jour<1){
					        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						        		printf("\n\n Donner le jour 'Entre 1 et 29': ");
						        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						        		scanf("%d",&emprnt.date_retour_jour);		        			
									}								
								}else{
					        		printf("\n\n Donner le jour 'Entre 1 et 28' : ");
					        		scanf("%d",&emprnt.date_retour_jour);
					        		while(emprnt.date_retour_jour>28 || emprnt.date_retour_jour<1){
					        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						        		printf("\n\n Donner le jour 'Entre 1 et 28': ");
						        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						        		scanf("%d",&emprnt.date_retour_jour);		        			
									}									
								}
								break;
							} 
							default:{
					        		printf("\n\n Donner le jour 'Entre 1 et 30' : ");
					        		scanf("%d",&emprnt.date_retour_jour);
					        		while(emprnt.date_retour_jour>30 || emprnt.date_retour_jour<1){
					        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						        		printf("\n\n Donner le jour 'Entre 1 et 30': ");
						        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						        		scanf("%d",&emprnt.date_retour_jour);		        			
									}									
								break;
							}     	
						}						
					}	
		
				  	if_there_is_an_incrementation=1;	
					//tcopier lfichier f un autre fichier copy ou ldakhel switch t3awed tcopiyih hada kamel bech tzid 1 nombre dexemplaire emprunte 
				    ouvrage x;
		    		FILE*fcopy; 
		    		FILE*fovrg;
		    		fovrg = fopen("Fouvrage.txt","r");//+b
		    		fcopy = fopen("copy.txt","w");//+b
		    		ouvrage ovrg;
		    		while (fread(&ovrg,sizeof(ouvrage),1,fovrg)){
						
		    			if(strcmp(emprnt.cote,ovrg.cote)==0){
		    				if_there_is_an_incrementation=1;
		    				strcpy(x.titre,ovrg.titre);
		    				strcpy(x.cote,ovrg.cote);
		    				x.nbr_exmp=ovrg.nbr_exmp;
		    				x.nbr_exmp_empr=ovrg.nbr_exmp_empr+1;
		    				
		    				fwrite(&x,sizeof(ouvrage),1,fcopy);
		    				
		    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		    				printf("\n\n Le nombre d'exemplaire emprunte d'ouvrage de cote : %s a ete incrementer \n\n",emprnt.cote);
		    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		    				
						}else{
							fwrite(&ovrg,sizeof(ouvrage),1,fcopy); 
						} 			
		    		}
		    		fclose(fovrg);
		        	fclose(fcopy);  
		
					FILE*femprnt=NULL;
					femprnt=fopen("Femprunte.txt","a");
					fwrite(&emprnt,sizeof(emprunte),1,femprnt);
					fclose(femprnt);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					printf("\n\n L'emprunte a ete ajouter\n\n");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}else{
					if(recherche_if_penalite_below7(emprnt.matricule)!=1 && verification_disponibilite_ovrg_test(emprnt.cote)==1){
					   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					   printf("\n\n Impossible d'emprunt car la penalite depasse 7 \n\n");
					   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);						
					}else{
						if(recherche_if_penalite_below7(emprnt.matricule)==1 && verification_disponibilite_ovrg_test(emprnt.cote)!=1){
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					   		printf("\n\n Impossible d'emprunt car L'ouvrage n'est pas disponible \n\n");
					   		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					   		etudiant etd;
					   		file_dattente fd;
					   		FILE*fetd=NULL;
					   		FILE*fileP=NULL;
					   		FILE*fileC=NULL;
					   		fetd=fopen("Fetudiant.txt","r");
					   		fileP=fopen("fileP.txt","a");
					   		fileC=fopen("fileC.txt","a");
					   		while(fread(&etd,sizeof(etudiant),1,fetd)){
					   			if(strcmp(etd.matricule,emprnt.matricule)==0 && strcmp(etd.type_abnmt,"P")==0){
					   				strcpy(fd.cote,emprnt.cote);
					   				strcpy(fd.matricule,etd.matricule);
					   				fwrite(&fd,sizeof(file_dattente),1,fileP);
							   		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
							   		printf("\n\n L'etudiant de matricule: %s a ete ajouter a la file d'attente premium\n\n",fd.matricule);
							   		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
								}
					   			if(strcmp(etd.matricule,emprnt.matricule)==0 && strcmp(etd.type_abnmt,"C")==0){
					   				strcpy(fd.cote,emprnt.cote);
					   				strcpy(fd.matricule,etd.matricule);
					   				fwrite(&fd,sizeof(file_dattente),1,fileC);
							   		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
							   		printf("\n\n L'etudiant de matricule: %s a ete ajouter a la file d'attente classic\n\n",fd.matricule);
							   		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);					   				
								}								
							}
							fclose(fetd);
							fclose(fileP);
							fclose(fileC);
														
						}else{
							if(recherche_if_penalite_below7(emprnt.matricule)!=1 && verification_disponibilite_ovrg_test(emprnt.cote)!=1){
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					   			printf("\n\n Impossible d'emprunt car la penalite depasse 7 et L'ouvrage n'est pas disponible \n\n");
					   			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		
							}
						}
					}
				}	
			}else{
				if(recherche_if_ouvrage_exist(emprnt.cote)!=1 && consulter_un_membre_test(emprnt.matricule)==1){
					if(recherche_if_penalite_below7(emprnt.matricule)==1){
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						printf("\n\n Impossible d'emprunt car l'ouvrage n'existe pas \n\n");
					   	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					}
					if(recherche_if_penalite_below7(emprnt.matricule)!=1){
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						printf("\n\n Impossible d'emprunt car l'ouvrage n'existe pas et la penalite depasse 7 \n\n");
					   	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					}								
					
				}else{
					if(recherche_if_ouvrage_exist(emprnt.cote)==1 && consulter_un_membre_test(emprnt.matricule)!=1){
						if(verification_disponibilite_ovrg_test(emprnt.cote)==1){
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
							printf("\n\n Impossible d'emprunt car l'etudiant n'existe pas \n\n");
						   	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	
						}
						if(verification_disponibilite_ovrg_test(emprnt.cote)!=1){
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
							printf("\n\n Impossible d'emprunt car l'etudiant n'existe pas et l'ouvrage non disponible \n\n");
						   	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	
						}						
						
					}else{
						if(recherche_if_ouvrage_exist(emprnt.cote)!=1 && consulter_un_membre_test(emprnt.matricule)!=1){
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
							printf("\n\n Impossible d'emprunt car l'ouvrage et l'etudiant n'existent pas \n\n");
						   	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						}
					}
				}
			}
			//mettre les fichier de la copy dans le fichier originale
			if(if_there_is_an_incrementation==1){
			
				ouvrage ovrg;
				FILE*fcopy;
				FILE*fovrg;
				fcopy = fopen("copy.txt","r");
				fovrg = fopen("Fouvrage.txt","w");
				while(fread(&ovrg,sizeof(ouvrage),1,fcopy)){
					fwrite(&ovrg,sizeof(ouvrage),1,fovrg);
				}
				fclose(fovrg);
				fclose(fcopy);
		        remove("copy.txt");		
			}else{
				remove("copy.txt");
			}		
		}else{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n L'emprunte de matricule: %s ,cote: %s deja existe \n\n",emprnt.matricule,emprnt.cote);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);			
		}
    }

//procedure search if penalite below seven with the matricule

	int recherche_if_penalite_below7 (char matricule[20]){
		int x=0;
		FILE*fetd=NULL;
		fetd=fopen("Fetudiant.txt","r");
		etudiant etd;	
		while(fread(&etd,sizeof(etudiant),1,fetd)){
			if(strcmp(etd.matricule,matricule)==0 && (strcmp(etd.type_abnmt,"C")==0 && etd.penalite<7))
			{
				x=1;	
			}
			if(strcmp(etd.matricule,matricule)==0 && (strcmp(etd.type_abnmt,"P")==0)){
				x=1;
			}		
		}
		fclose(fetd);
		return x;		
	}  

//procedure search if the ouvrage existe 

	int recherche_if_ouvrage_exist(char cote[100]){		
		int x=0;
		FILE*fovrg=NULL;
		fovrg=fopen("Fouvrage.txt","r+");
		ouvrage ovrg;	
		while(fread(&ovrg,sizeof(ouvrage),1,fovrg)){
			if(strcmp(ovrg.cote,cote)==0)
			{
				x=1;
			}		
		}
		return x;	
		fclose(fovrg);		
	} 
	
	 	

//procedure display ouvrage 

	void affichage_ouvrage(){
		int i=0;
		ouvrage ovrg;
		FILE*fovrg=NULL;
		fovrg=fopen("Fouvrage.txt","r");
		printf("\n\n                                        ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY);
        printf("AFFICHAGE LA LISTE DES OUVRAGES");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        printf("\n\n");
		while(fread(&ovrg,sizeof(ouvrage),1,fovrg))
		{   
			i=i+1;
			printf("\n\n ---------------------------------------------");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf(" \n");printf(" |\n |\n |               'OUVRAGE NUMERO %d' \n |\n",i);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf(" |\n");printf(" |\n |\n | - Le Titre : %s \n |\n",ovrg.titre);
			printf(" |\n");printf(" |\n |\n | - La cote : %s \n |\n",ovrg.cote);
			printf(" |\n");printf(" |\n |\n | - Le nombre d'exemplaire : %d \n |\n",ovrg.nbr_exmp);
			printf(" |\n");printf(" |\n |\n | - Le nombre d'exemplaire emprunte : %d \n |\n",ovrg.nbr_exmp_empr);
			printf(" ---------------------------------------------");
			printf("\n\n");
			sleep(1);
	    }   
		fclose(fovrg);
		if(i==0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n La liste des ouvrages est vide");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		} 
		printf("\n\n++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	}	
	
	
//procedure display etudiant 

	void affichage_etudiant(){
		int i=0;
		etudiant etd;
		FILE*fetd=NULL;
		fetd=fopen("Fetudiant.txt","r");
		printf("\n\n                                        ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY);
        printf(" AFFICHAGE LA LISTE DES ETUDIANT ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        printf("\n\n");
		while(fread(&etd,sizeof(etudiant),1,fetd))
		{   
			i=i+1;
			printf("\n\n ---------------------------------------------");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("\n");printf(" \n\n               'ETUDIANT NUMERO %d' \n \n",i);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf(" \n");printf(" \n\n  - Le matricule : %s \n\n",etd.matricule);
			printf(" \n");printf(" \n\n  - La penalite : %d \n\n",etd.penalite);
			printf(" \n");printf(" \n\n  - Le type d'abonnement est : %s \n\n",etd.type_abnmt);
			printf(" ---------------------------------------------");
			printf("\n\n");
			sleep(1);
	    }   
		fclose(fetd); 
		if(i==0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n La liste des etudiants est vide");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		} 
		printf("\n\n++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	}	
	
//procedure display emprunte

	void affichage_emprunte(){
		int i=0;
		emprunte emprnt;
		FILE*femprnt=NULL;
		femprnt=fopen("Femprunte.txt","r");
		printf("\n\n                                        ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY);
        printf(" AFFICHAGE LA LISTE DES EMPRUNTES ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        printf("\n\n");
		while(fread(&emprnt,sizeof(emprunte),1,femprnt))
		{   
			i=i+1;
			printf("\n\n ---------------------------------------------");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("\n");printf(" \n\n               'EMPRUNTE NUMERO %d' \n \n",i);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf(" \n");printf(" \n\n  - Le matricule  : %s \n\n",emprnt.matricule);
			printf(" \n");printf(" \n\n  - La cote : %s \n\n",emprnt.cote);
			printf(" \n");printf(" \n\n  - La date d'emprunte est : %d/%d/%d \n\n",emprnt.date_emprunte_jour,emprnt.date_emprunte_mois,emprnt.date_emprunte_anne);
			printf(" \n");printf(" \n\n  - La date de retour est : %d/%d/%d \n\n",emprnt.date_retour_jour,emprnt.date_retour_mois,emprnt.date_retour_anne);
			printf(" ---------------------------------------------");
			printf("\n\n");
			sleep(1);
	    }   
		fclose(femprnt); 
		if(i==0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n La liste des empruntes est vide");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		} 
		printf("\n\n++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	}	

//procedure consulter un membre

	int consulter_un_membre(char matricule[20]){
		int x=0;
		etudiant etd;
		FILE*fetd=NULL;
		fetd=fopen("Fetudiant.txt","r");
		while(fread(&etd,sizeof(etudiant),1,fetd)){
			if(strcmp(matricule,etd.matricule)==0){
				x=1;
				printf("\n\n ---------------------------------------------");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("\n");printf(" \n\n               'Les informations de membre:' \n \n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);			
				printf(" \n");printf(" \n\n  - Le matricule : %s \n\n",etd.matricule);
				printf(" \n");printf(" \n\n  - La penalite : %d \n\n",etd.penalite);
				printf(" \n");printf(" \n\n  - Le type d'abonnement est : %s \n\n",etd.type_abnmt);
				printf(" ---------------------------------------------");
				printf("\n\n");
				
			}
		}
		    fclose(fetd);
			if(x==0){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n L'etudiant n'exister pas \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
		return x;		
	}	
	
//procedure consulter un membre pour tester

	int consulter_un_membre_test(char matricule[20]){
		int x=0;
		etudiant etd;
		FILE*fetd=NULL;
		fetd=fopen("Fetudiant.txt","r");
		while(fread(&etd,sizeof(etudiant),1,fetd)){
			if(strcmp(matricule,etd.matricule)==0){
				x=1;
			}
		}
		fclose(fetd);
		return x;		
	}		
	
	
//procedure consulter un emprunt par matricule

	int consulter_un_emprunt_par_maticule(char matricule[20]){
		int x=0;
		int i=0;
		emprunte emprnt;
		FILE*femprnt=NULL;
		femprnt=fopen("Femprunte.txt","r");
		while(fread(&emprnt,sizeof(emprunte),1,femprnt)){
			if(strcmp(matricule,emprnt.matricule)==0){
				x=1;
				i=i+1;
				printf("\n\n ---------------------------------------------");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("\n");printf(" \n\n               'EMPRUNTE NUMERO %d' \n \n",i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);				
				printf(" \n");printf(" \n\n  - Le matricule : %s \n\n",emprnt.matricule);
				printf(" \n");printf(" \n\n  - La cote : %s \n\n",emprnt.cote);
				printf(" \n");printf(" \n\n  - La date d'emprunte est : %d/%d/%d \n\n",emprnt.date_emprunte_jour,emprnt.date_emprunte_mois,emprnt.date_emprunte_anne);
				printf(" \n");printf(" \n\n  - La date de retour est : %d/%d/%d \n\n",emprnt.date_retour_jour,emprnt.date_retour_mois,emprnt.date_retour_anne);
				printf(" ---------------------------------------------");
				printf("\n\n");
				
			}
		}
		fclose(femprnt);

		if(x==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n L'emprunte n'exister pas \n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		return x;		
	}


//procedure consulter un emprunt par matricule pour tester si le matricule existe dans qlq emprunt
		
	int consulter_un_emprunt_par_matricule_test(char matricule[20]){
		int x=0;
		emprunte emprnt;
		FILE*femprnt=NULL;
		femprnt=fopen("Femprunte.txt","r");
		while(fread(&emprnt,sizeof(emprunte),1,femprnt)){
			if(strcmp(matricule,emprnt.matricule)==0){
				x=1;
			}
		}fclose(femprnt);
		    
		if(x==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n L'emprunte n'exister pas \n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		return x;	
			
	}	
		
//procedure consulter un emprunt par cote

	int consulter_un_emprunt_par_cote(char cote[100]){
		int x=0;
		int i=0;
		emprunte emprnt;
		FILE*femprnt=NULL;
		femprnt=fopen("Femprunte.txt","r");
		while(fread(&emprnt,sizeof(emprunte),1,femprnt)){
			if(strcmp(cote,emprnt.cote)==0){
				x=1;
				i=i+1;
				printf("\n\n ---------------------------------------------");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("\n");printf(" \n\n               'EMPRUNTE NUMERO %d' \n \n",i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" \n");printf(" \n\n  - Le matricule : %s \n\n",emprnt.matricule);
				printf(" \n");printf(" \n\n  - La cote : %s \n\n",emprnt.cote);
				printf(" \n");printf(" \n\n  - La date d'emprunte est : %d/%d/%d \n\n",emprnt.date_emprunte_jour,emprnt.date_emprunte_mois,emprnt.date_emprunte_anne);
				printf(" \n");printf(" \n\n  - La date de retour est : %d/%d/%d \n\n",emprnt.date_retour_jour,emprnt.date_retour_mois,emprnt.date_retour_anne);
				printf(" ---------------------------------------------");
				printf("\n\n");
				
			}
		}fclose(femprnt);
		    
		if(x==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n L'emprunte n'exister pas \n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		return x;		
	}	

//procedure consulter un emprunt par cote pour tester

	int consulter_un_emprunt_par_cote_test(char cote[100]){
		int x=0;
		emprunte emprnt;
		FILE*femprnt=NULL;
		femprnt=fopen("Femprunte.txt","r");
		while(fread(&emprnt,sizeof(emprunte),1,femprnt)){
			if(strcmp(cote,emprnt.cote)==0){
				x=1;			
			}
		}fclose(femprnt);
		    
		if(x==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n L'emprunte n'exister pas \n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		return x;		
	}

//procedure consulter un emprunt par cote et matricule

	int consulter_un_emprunt(char cote[100],char matricule[20]){
		int x=0;
		emprunte emprnt;
		FILE*femprnt=NULL;
		femprnt=fopen("Femprunte.txt","r");
		while(fread(&emprnt,sizeof(emprunte),1,femprnt)){
			if(strcmp(cote,emprnt.cote)==0&&strcmp(matricule,emprnt.matricule)==0){
				x=1;
				printf("\n\n ---------------------------------------------");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("\n");printf(" \n\n               'EMPRUNTE' \n \n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" \n");printf(" \n\n  - Le matricule : %s \n\n",emprnt.matricule);
				printf(" \n");printf(" \n\n  - La cote : %s \n\n",emprnt.cote);
				printf(" \n");printf(" \n\n  - La date d'emprunte est : %d/%d/%d \n\n",emprnt.date_emprunte_jour,emprnt.date_emprunte_mois,emprnt.date_emprunte_anne);
				printf(" \n");printf(" \n\n  - La date de retour est : %d/%d/%d \n\n",emprnt.date_retour_jour,emprnt.date_retour_mois,emprnt.date_retour_anne);
				printf(" ---------------------------------------------");
				printf("\n\n");
				
			}
		}fclose(femprnt);
		    
		if(x==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n L'emprunte n'exister pas \n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		return x;		
	}	

		
//fonction de supression dun ouvrage 

	int suppression_ouvrage(char cote[100]) {
		int x=0;
		ouvrage ovrg;
		FILE*fovrg=NULL;
		FILE*fcopy=NULL;
		fovrg=fopen("Fouvrage.txt","r");
		fcopy=fopen("Fcopy.txt","w");
		while(fread(&ovrg,sizeof(ouvrage),1,fovrg)){
			if(strcmp(ovrg.cote,cote)==0){
				x=1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("\n\n L'ouvrage de cote: %s a ete supprimer\n\n",cote);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}else{
				fwrite(&ovrg,sizeof(ouvrage),1,fcopy);
			}
		}
		fclose(fovrg);
		fclose(fcopy);
		remove("Fouvrage.txt");
		rename("Fcopy.txt","Fouvrage.txt");
		if(x==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n L'ouvrage n'existe pas \n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);			
		}
	}

//procedure supprission etudiant
		
    int suppression_etudiant(char matricule[20]){
		int x=0;
		etudiant etd;
		FILE*fetd=NULL;
		FILE*fcopy=NULL;
		fetd=fopen("Fetudiant.txt","r");
		fcopy=fopen("Fcopy.txt","w");
		while(fread(&etd,sizeof(etudiant),1,fetd)){
			if(strcmp(etd.matricule,matricule)==0){
				x=1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("\n\n L'etudiant de matricule: %s a ete supprimer\n\n",matricule);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}else{
				fwrite(&etd,sizeof(etudiant),1,fcopy);
			}
		}
		fclose(fetd);
		fclose(fcopy);
		remove("Fetudiant.txt");
		rename("Fcopy.txt","Fetudiant.txt");
		if(x==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n L'etudiant n'existe pas \n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);			
		}    	
	}	
	
//procedure retourner un emprunte

    int retourner_emprunt(char matricule[20],char cote[100]){
    	
    	if( consulter_un_emprunt_par_matricule_test(matricule)==1 && consulter_un_emprunt_par_cote_test(cote)==1){
    		emprunte emprnt;
    		FILE*fcopy=NULL;
    		FILE*femprnt=NULL;
    		femprnt=fopen("Femprunte.txt","r");
    		fcopy=fopen("Fcopy.txt","w");
    		while(fread(&emprnt,sizeof(emprunte),1,femprnt)){
    			if(strcmp(emprnt.matricule,matricule)==0 && strcmp(emprnt.cote,cote)==0 ){
    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    				printf("\n\n L'emprunte de matricule: %s , cote: %s a ete Retourner \n\n",matricule,cote);
    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}else{
					fwrite(&emprnt,sizeof(emprunte),1,fcopy);
				}
			}
			fclose(fcopy);
			fclose(femprnt);
			remove("Femprunte.txt");
			rename("Fcopy.txt","Femprunte.txt");
			
		    ouvrage x; 
    		FILE*fovrg;
    		fovrg = fopen("Fouvrage.txt","r");//+b
    		fcopy = fopen("copy.txt","w");//+b
    		ouvrage ovrg;
    		while (fread(&ovrg,sizeof(ouvrage),1,fovrg)){
				
    			if(strcmp(cote,ovrg.cote)==0){
    				strcpy(x.titre,ovrg.titre);
    				strcpy(x.cote,ovrg.cote);
    				x.nbr_exmp=ovrg.nbr_exmp;
    				x.nbr_exmp_empr=ovrg.nbr_exmp_empr-1;
    				
    				fwrite(&x,sizeof(ouvrage),1,fcopy);
    				
    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    				printf("\n\n Le nombre d'exemplaire emprunte d'ouvrage de cote : %s a ete decremente \n\n",cote);
    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    				
				}else{
					fwrite(&ovrg,sizeof(ouvrage),1,fcopy); 
				} 			
    		}
    		fclose(fovrg);
        	fclose(fcopy); 

			fcopy = fopen("copy.txt","r");
			fovrg = fopen("Fouvrage.txt","w");
			while(fread(&ovrg,sizeof(ouvrage),1,fcopy)){
				fwrite(&ovrg,sizeof(ouvrage),1,fovrg);
			}
			fclose(fovrg);
			fclose(fcopy);
	        remove("copy.txt");			 				
		
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf("\n\n En train de verifier s'il existe une demande emprunt avec ce ouvrage dans les files d'attente ... \n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			sleep(3);
			
			int P,C;
			P=0;
			C=0;
			file_dattente gg,gg1,reader_file;
			emprunte empgg,empgg1;
			FILE*fileP=NULL;
			fileP=fopen("fileP.txt","r");
			while(fread(&gg,sizeof(file_dattente),1,fileP)){
				if(strcmp(gg.cote,cote)==0){
					P=1;
					strcpy(empgg.matricule,gg.matricule);
					strcpy(empgg.cote,gg.cote);
				}
			}
			fclose(fileP);
			
			FILE*fileC=NULL;
			fileC=fopen("fileC.txt","r");
			while(fread(&gg1,sizeof(file_dattente),1,fileC)){
				if(strcmp(gg1.cote,cote)==0){
					C=1;
					strcpy(empgg1.matricule,gg1.matricule);
					strcpy(empgg1.cote,gg1.cote);
				}
			}
			fclose(fileC);	
			int insert=0;
			
			if(P==1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				printf("\n Demande d'emprunt trouver dans la file d'attente premium \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("\n\n                         AJOUT D'EMPRUNT \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("\n\n - Le matricule : %s\n\n",gg.matricule);
				printf("\n\n - La cote : %s\n\n",gg.cote);
				insertion_emprunte(empgg);
				insert=1;				
			}else{
				if(C==1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				printf("\n Demande d'emprunt trouver dans la file d'attente classic \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("\n\n                         AJOUT D'EMPRUNT \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("\n\n - Le matricule : %s\n\n",gg1.matricule);
				printf("\n\n - La cote : %s\n\n",gg1.cote);
				insertion_emprunte(empgg);
				insert=2;	
				}else{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
					printf("\n Il n'existe aucune demande d'emprunt de ce ouvrage \n\n");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
			}
			
			
			if(insert==1){
				FILE*fcopy=NULL;
				fcopy=fopen("Fcopy.txt","w");
				fileP=fopen("fileP.txt","r");
				while(fread(&reader_file,sizeof(file_dattente),1,fileP)){
					if(strcmp(reader_file.cote,gg.cote)==0&&strcmp(reader_file.matricule,gg.matricule)==0){
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
						printf("\n L'emprunt de cote:");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						printf(" %s, ",gg.matricule);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
						printf("cote:");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						printf(" %s ",gg.cote);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
						printf("a ete supprimer de file d'attente car il est emprunte\n\n");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	
					}else{
						fwrite(&reader_file,sizeof(file_dattente),1,fcopy);
					}
				}
				fclose(fcopy);
				fclose(fileP);
				remove("fileP.txt");
				rename("Fcopy.txt","fileP.txt");
			}else{
				if(insert==2){
					
					FILE*fcopy=NULL;
					fcopy=fopen("Fcopy.txt","w");
					fileP=fopen("fileC.txt","r");
					while(fread(&reader_file,sizeof(file_dattente),1,fileC)){
						if(strcmp(reader_file.cote,gg1.cote)==0&&strcmp(reader_file.matricule,gg1.matricule)==0){
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
							printf("\n L'emprunt de cote:");
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
							printf(" %s, ",gg1.matricule);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
							printf("cote:");
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
							printf(" %s ",gg1.cote);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
							printf("a ete supprimer de file d'attente car il est emprunte\n\n");
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						}else{
							fwrite(&reader_file,sizeof(file_dattente),1,fcopy);
						}
					}
					fclose(fcopy);
					fclose(fileC);
					remove("fileC.txt");
					rename("Fcopy.txt","fileC.txt");
				}
			}	
		}
	}

//procedure supprission un emprunte

	int suppression_emprunte(char matricule[20],char cote[100]){
	
		if( consulter_un_emprunt_par_matricule_test(matricule)==1 && consulter_un_emprunt_par_cote_test(cote)==1){		
    		emprunte emprnt;
    		FILE*fcopy=NULL;
    		FILE*femprnt=NULL;
    		femprnt=fopen("Femprunte.txt","r");
    		fcopy=fopen("Fcopy.txt","w");
    		while(fread(&emprnt,sizeof(emprunte),1,femprnt)){
    			if(strcmp(emprnt.matricule,matricule)==0 && strcmp(emprnt.cote,cote)==0 ){
    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    				printf("\n\n L'emprunte de matricule: %s , cote: %s a ete supprimer \n\n",matricule,cote);
    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}else{
					fwrite(&emprnt,sizeof(emprunte),1,fcopy);
				}
			}
			fclose(fcopy);
			fclose(femprnt);
			remove("Femprunte.txt");
			rename("Fcopy.txt","Femprunte.txt");	
						
			etudiant etd,x;
			FILE*fetd=NULL;
			fetd=fopen("Fetudiant.txt","r");
			fcopy=fopen("Fcopy.txt","w");
			while(fread(&etd,sizeof(etudiant),1,fetd)){
				
				if(strcmp(etd.matricule,matricule)==0){
					
					if(strcmp(etd.type_abnmt,"P")==0){
						
						fwrite(&etd,sizeof(etudiant),1,fcopy);
				    }else{
						strcpy(x.matricule,etd.matricule);
						strcpy(x.type_abnmt,etd.type_abnmt);
						x.penalite=etd.penalite+1;
						fwrite(&x,sizeof(etudiant),1,fcopy);
	   				 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	    				printf("\n\n La penalite d'etudiant de matricule: %s a ete incremente \n\n",matricule);
	    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);						
					}
				}else{
					fwrite(&etd,sizeof(etudiant),1,fcopy);
				}
			}
			fclose(fetd);
			fclose(fcopy);
			
			fcopy = fopen("Fcopy.txt","r");
			fetd = fopen("Fetudiant.txt","w");
			while(fread(&etd,sizeof(etudiant),1,fcopy)){
				fwrite(&etd,sizeof(etudiant),1,fetd);
			}
			fclose(fetd);
			fclose(fcopy);
	        remove("Fcopy.txt");	
		}
	}

//fonction verification la disponibilite des exemplaire 

	void verification_disponibilite_ovrg(char cote[100]){
		int i=0;
		ouvrage ovrg;
		FILE*fovrg=NULL;
		fovrg=fopen("Fouvrage.txt","r");
		while(fread(&ovrg,sizeof(ouvrage),1,fovrg)){
			if(strcmp(ovrg.cote,cote)==0 ){
				i=1;
				if(((ovrg.nbr_exmp-ovrg.nbr_exmp_empr)==0)){
					printf("\n\n - Le nombre ");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
					printf("d'exemplaire");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					printf(" est : %d \n\n",ovrg.nbr_exmp);
					
					printf("\n\n - Le nombre ");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
					printf("d'exemplaire emprunte");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					printf(" est : %d \n\n",ovrg.nbr_exmp_empr);

	
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					printf("\n\n L'ouvrage n'est pas disponible \n\n");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
				if(((ovrg.nbr_exmp-ovrg.nbr_exmp_empr)>0)){
					printf("\n\n - Le nombre ");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
					printf("d'exemplaire");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					printf(" est : %d \n\n",ovrg.nbr_exmp);
					
					printf("\n\n - Le nombre ");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
					printf("d'exemplaire emprunte");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					printf(" est : %d \n\n",ovrg.nbr_exmp_empr);
					
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					printf("\n\n L'ouvrage est disponible \n\n");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}				
			}			
		}
		fclose(fovrg);
		if(i==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n La cote d'ouvrage donner n'existe pas  \n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}	
	
//fonction verification la disponibilite des exemplaire test 

	int verification_disponibilite_ovrg_test(char cote[100]){
		int x=0;
		ouvrage ovrg;
		FILE*fovrg=NULL;
		fovrg=fopen("Fouvrage.txt","r");
		while(fread(&ovrg,sizeof(ouvrage),1,fovrg)){
			if(strcmp(ovrg.cote,cote)==0 ){
			
				if(((ovrg.nbr_exmp-ovrg.nbr_exmp_empr)==0)){
					x=0;
				}
				if(((ovrg.nbr_exmp-ovrg.nbr_exmp_empr)>0)){
					x=1;
				}				
			}			
		}
		fclose(fovrg);
		return x;
	}	
		
//procedure modifier un membre

	void modifier_un_membre(char matricule[20]){
		etudiant nouv;
		int i=0;
		int choicetype;
		etudiant etd,nouvetd;
		FILE*fetd=NULL;
		FILE*fcopy=NULL;
		fetd=fopen("Fetudiant.txt","r");
		fcopy=fopen("Fcopy.txt","w");
			
		while(fread(&etd,sizeof(etudiant),1,fetd)){
			
			if(strcmp(matricule,etd.matricule)==0){
				i=1;
				/* mate9derch tmodifier matricule ta3 letudiant psq loukan tmodifyi lmatricule tweli chghoul insersion
				t9der tmodifier ghir type dabonement w lpenalite */
        		printf("\n\n Choisie le nouveau type d'abonement\n\n");
        		printf("\n\n 1 - Premium\n\n");
        		printf("\n\n 2 - Classic\n\n");
        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        		printf("\n\n Votre choix : ");
        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        		scanf("%d",&choicetype);  		
        		while(choicetype!=1 && choicetype!=2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        			printf("\n\n Votre choix : ");
        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        		    scanf("%d",&choicetype);    
				}
		
        		switch(choicetype){
        			case 1:{
        				strcpy(nouv.type_abnmt,"P");
        				nouv.penalite=0;
						break;
					}
					case 2:{
        				strcpy(nouv.type_abnmt,"C");
        				printf("\n\n Donner la penalite : ");
        				scanf("%d",&nouv.penalite);
						break;
					}				        												
				break;
				}									
				strcpy(nouvetd.matricule,matricule);
				strcpy(nouvetd.type_abnmt,nouv.type_abnmt);
				nouvetd.penalite=nouv.penalite;
				fwrite(&nouvetd,sizeof(etudiant),1,fcopy);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
				printf("\n\n L'etudiant de matricule: %s a ete modifier \n\n",matricule);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	
			}else{
				fwrite(&etd,sizeof(etudiant),1,fcopy);
			}
		}
		fclose(fetd);
		fclose(fcopy);
		remove("Fetudiant.txt");
		rename("Fcopy.txt","Fetudiant.txt");
		
		if(i==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n Le matricule d'etudiant donner n'existe pas  \n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}

//procedure modifier un emprunte

	void modifier_un_emprunte(char matricule[20],char cote[100]){
		/* Dans la modification dun emprunte u can change just the date because if u change the cote it will be another emprunte 
		so u can do this with delete and insert new emprunt bcs   */
		if(consulter_un_emprunt_par_matricule_test(matricule)==1 && consulter_un_emprunt_par_cote_test(cote)==1){
			emprunte nouv;
			int i=0;
			emprunte emprnt,nouvemprnt;
			FILE*femprnt=NULL;
			FILE*fcopy=NULL;
			femprnt=fopen("Femprunte.txt","r");
			fcopy=fopen("Fcopy.txt","w");
			
			while(fread(&emprnt,sizeof(emprunte),1,femprnt)){
				
				if(strcmp(matricule,emprnt.matricule)==0 && strcmp(cote,emprnt.cote)==0){
	
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	        		printf("\n\n Donner la date d'emprunte : \n\n");
	        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	        		printf("\n\n Donner l'annee 'Entre 2015 et 2023' : ");
	        		scanf("%d",&nouvemprnt.date_emprunte_anne);	
	        		while(nouvemprnt.date_emprunte_anne>2023 || nouvemprnt.date_emprunte_anne<2015){
	        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		        		printf("\n\n Donner l'annee 'Entre 2015 et 2023': ");
		        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        		scanf("%d",&nouvemprnt.date_emprunte_anne);		        			
					}
	        		printf("\n\n Donner le mois 'Entre 1 et 12' : ");
	        		scanf("%d",&nouvemprnt.date_emprunte_mois);
	        		while(nouvemprnt.date_emprunte_mois>12 || nouvemprnt.date_emprunte_mois<1){
	        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		        		printf("\n\n Donner le mois 'Entre 1 et 12': ");
		        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        		scanf("%d",&nouvemprnt.date_emprunte_mois);		        			
					}
					
					switch(nouvemprnt.date_emprunte_mois){
						case 1:
						case 5:
						case 7:
						case 8:
						case 10:
						case 12:{
		
			        		printf("\n\n Donner le jour 'Entre 1 et 31' : ");
			        		scanf("%d",&nouvemprnt.date_emprunte_jour);
			        		while(nouvemprnt.date_emprunte_jour>31 || nouvemprnt.date_emprunte_jour<1){
			        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				        		printf("\n\n Donner le jour 'Entre 1 et 31': ");
				        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				        		scanf("%d",&nouvemprnt.date_emprunte_jour);		        			
							}
							break;
						}
						case 2:{
							if(nouvemprnt.date_emprunte_anne==2016||nouvemprnt.date_emprunte_anne==2020){
				        		printf("\n\n Donner le jour 'Entre 1 et 29' : ");
				        		scanf("%d",&nouvemprnt.date_emprunte_jour);
				        		while(nouvemprnt.date_emprunte_jour>29 || nouvemprnt.date_emprunte_jour<1){
				        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					        		printf("\n\n Donner le jour 'Entre 1 et 29': ");
					        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					        		scanf("%d",&nouvemprnt.date_emprunte_jour);		        			
								}								
							}else{
				        		printf("\n\n Donner le jour 'Entre 1 et 28' : ");
				        		scanf("%d",&nouvemprnt.date_emprunte_jour);
				        		while(nouvemprnt.date_emprunte_jour>28 || nouvemprnt.date_emprunte_jour<1){
				        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					        		printf("\n\n Donner le jour 'Entre 1 et 28': ");
					        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					        		scanf("%d",&nouvemprnt.date_emprunte_jour);		        			
								}									
							}
							break;
						} 
						default:{
				        		printf("\n\n Donner le jour 'Entre 1 et 30' : ");
				        		scanf("%d",&nouvemprnt.date_emprunte_jour);
				        		while(nouvemprnt.date_emprunte_jour>30 || nouvemprnt.date_emprunte_jour<1){
				        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					        		printf("\n\n Donner le jour 'Entre 1 et 30': ");
					        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					        		scanf("%d",&nouvemprnt.date_emprunte_jour);		        			
								}									
							break;
						}     	
					}
					
					
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);							        		
	        		printf("\n\n Donner la date de retour : \n\n");
	        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	        								
	        		printf("\n\n Donner l'annee 'Entre %d et 2023' : ",nouvemprnt.date_emprunte_anne);
	        		scanf("%d",&nouvemprnt.date_retour_anne);	
	        		while(nouvemprnt.date_retour_anne>2023 || nouvemprnt.date_retour_anne<nouvemprnt.date_emprunte_anne){
	        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		        		printf("\n\n Donner l'annee 'Entre %d et 2023' (superieur ou egal a l'anne d'emprunt): ",nouvemprnt.date_emprunte_anne);
		        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        		scanf("%d",&nouvemprnt.date_retour_anne);		        			
					}
					if(nouvemprnt.date_emprunte_anne==nouvemprnt.date_retour_anne){
						
		        		printf("\n\n Donner le mois 'Entre %d et 12' : ",nouvemprnt.date_emprunte_mois);
		        		scanf("%d",&nouvemprnt.date_retour_mois);
		        		while(nouvemprnt.date_retour_mois>12 || nouvemprnt.date_retour_mois<nouvemprnt.date_emprunte_mois){
		        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			        		printf("\n\n Donner le mois 'Entre %d et 12'{la date de retour toujour superieur a date emprunte} : ",nouvemprnt.date_emprunte_mois);
			        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			        		scanf("%d",&nouvemprnt.date_retour_mois);		        			
						}
					}else{
		        		printf("\n\n Donner le mois 'Entre 1 et 12' : ");
		        		scanf("%d",&nouvemprnt.date_retour_mois);
		        		while(nouvemprnt.date_retour_mois>12 || nouvemprnt.date_retour_mois<1){
		        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			        		printf("\n\n Donner le mois 'Entre 1 et 12': ");
			        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			        		scanf("%d",&nouvemprnt.date_retour_mois);		        			
						}						
					}
					if(nouvemprnt.date_emprunte_mois==nouvemprnt.date_retour_mois&&nouvemprnt.date_emprunte_anne==nouvemprnt.date_retour_anne){
						
					
						switch(nouvemprnt.date_retour_mois){
							case 1:
							case 5:
							case 7:
							case 8:
							case 10:
							case 12:{
								
								
				        		printf("\n\n Donner le jour 'Entre %d et 31' : ",nouvemprnt.date_emprunte_jour+1);
				        		scanf("%d",&nouvemprnt.date_retour_jour);
				        		while(nouvemprnt.date_retour_jour>31 || nouvemprnt.date_retour_jour<=nouvemprnt.date_emprunte_jour){
				        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					        		printf("\n\n Donner le jour 'Entre %d et 31'{la date de retour toujour superieur a date emprunte} : ",nouvemprnt.date_emprunte_jour+1);
					        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					        		scanf("%d",&nouvemprnt.date_retour_jour);		        			
								}
								
								break;
							}
							case 2:{
								if(nouvemprnt.date_retour_anne==2016||nouvemprnt.date_retour_anne==2020){
									
					        		printf("\n\n Donner le jour 'Entre %d et 29' : ",nouvemprnt.date_emprunte_jour+1);
					        		scanf("%d",&nouvemprnt.date_retour_jour);
					        		while(nouvemprnt.date_retour_jour>29 || nouvemprnt.date_retour_jour<=nouvemprnt.date_emprunte_jour){
					        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						        		printf("\n\n Donner le jour 'Entre %d et 29'{la date de retour toujour superieur a date emprunte}: ",nouvemprnt.date_emprunte_jour+1);
						        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						        		scanf("%d",&nouvemprnt.date_retour_jour);		        			
									}								
								}else{
					        		printf("\n\n Donner le jour 'Entre %d et 28' : ",nouvemprnt.date_emprunte_jour+1);
					        		scanf("%d",&nouvemprnt.date_retour_jour);
					        		while(nouvemprnt.date_retour_jour>28 || nouvemprnt.date_retour_jour<=nouvemprnt.date_emprunte_jour){
					        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						        		printf("\n\n Donner le jour 'Entre %d et 28'{la date de retour toujour superieur a date emprunte}: ",nouvemprnt.date_emprunte_jour+1);
						        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						        		scanf("%d",&nouvemprnt.date_retour_jour);		        			
									}									
								}
								break;
							} 
							default:{
					        		printf("\n\n Donner le jour 'Entre %d et 30' : ",nouvemprnt.date_emprunte_jour+1);
					        		scanf("%d",&nouvemprnt.date_retour_jour);
					        		while(nouvemprnt.date_retour_jour>30 || nouvemprnt.date_retour_jour<=nouvemprnt.date_emprunte_jour){
					        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						        		printf("\n\n Donner le jour 'Entre %d et 30':{la date de retour toujour superieur a date emprunte} ",nouvemprnt.date_emprunte_jour+1);
						        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						        		scanf("%d",&nouvemprnt.date_retour_jour);		        			
									}									
								break;
							}     	
						}
					}else{
						
					
						switch(nouvemprnt.date_retour_mois){
							case 1:
							case 5:
							case 7:
							case 8:
							case 10:
							case 12:{
								
				        		printf("\n\n Donner le jour 'Entre 1 et 31' : ");
				        		scanf("%d",&nouvemprnt.date_retour_jour);
				        		while(nouvemprnt.date_retour_jour>31 || nouvemprnt.date_retour_jour<1){
				        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					        		printf("\n\n Donner le jour 'Entre 1 et 31': ");
					        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					        		scanf("%d",&nouvemprnt.date_retour_jour);		        			
								}
								
								break;
							}
							case 2:{
								if(nouvemprnt.date_retour_anne==2016||nouvemprnt.date_retour_anne==2020){
					        		printf("\n\n Donner le jour 'Entre 1 et 29' : ");
					        		scanf("%d",&nouvemprnt.date_retour_jour);
					        		while(nouvemprnt.date_retour_jour>29 || nouvemprnt.date_retour_jour<1){
					        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						        		printf("\n\n Donner le jour 'Entre 1 et 29': ");
						        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						        		scanf("%d",&nouvemprnt.date_retour_jour);		        			
									}								
								}else{
					        		printf("\n\n Donner le jour 'Entre 1 et 28' : ");
					        		scanf("%d",&nouvemprnt.date_retour_jour);
					        		while(nouvemprnt.date_retour_jour>28 || nouvemprnt.date_retour_jour<1){
					        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						        		printf("\n\n Donner le jour 'Entre 1 et 28': ");
						        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						        		scanf("%d",&nouvemprnt.date_retour_jour);		        			
									}									
								}
								break;
							} 
							default:{
					        		printf("\n\n Donner le jour 'Entre 1 et 30' : ");
					        		scanf("%d",&nouvemprnt.date_retour_jour);
					        		while(nouvemprnt.date_retour_jour>30 || nouvemprnt.date_retour_jour<1){
					        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						        		printf("\n\n Donner le jour 'Entre 1 et 30': ");
						        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						        		scanf("%d",&nouvemprnt.date_retour_jour);		        			
									}									
								break;
							}     	
						}						
					}									
					strcpy(nouvemprnt.matricule,emprnt.matricule);
					strcpy(nouvemprnt.cote,emprnt.cote);
					fwrite(&nouvemprnt,sizeof(emprunte),1,fcopy);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
					printf("\n\n L'emprunte de matricule: %s ,cote: %s a ete modifier \n\n",matricule,cote);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);					
				}else{
					fwrite(&emprnt,sizeof(emprunte),1,fcopy);
				}
			}
			fclose(femprnt);
			fclose(fcopy);
			remove("Femprunte.txt");
			rename("Fcopy.txt","Femprunte.txt");					
		}
	}
	

//fonction valeur absolue pour les date

	int abs(int a){
		if(a<0){
			a=a*(-1);
		}
		return a;
	}
	
//fonction de calcule dure 

	date calcule_dure(emprunte emprnt){	
		date gg;
		switch(emprnt.date_emprunte_mois){
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:{
				gg.jour_demprunte=31-emprnt.date_emprunte_jour;
				break;
			}
			case 4:
			case 6:
			case 9:
			case 11:{
				
				gg.jour_demprunte=30-emprnt.date_emprunte_jour;				
				break;
			}
			case 2:{
				
				if(emprnt.date_emprunte_anne!=2016&&emprnt.date_emprunte_anne!=2020){
					
					gg.jour_demprunte=29-emprnt.date_emprunte_jour;						
				}else{
					
					gg.jour_demprunte=28-emprnt.date_emprunte_jour;	
				}
				break;	
			}			
		}
		gg.jour_retour=emprnt.date_retour_jour;
			
		if(emprnt.date_emprunte_anne==emprnt.date_retour_anne&&emprnt.date_emprunte_mois==emprnt.date_retour_mois){
			
			gg.dure_jour=abs(emprnt.date_retour_jour-emprnt.date_emprunte_jour);
		}else{
			
			if(emprnt.date_emprunte_anne==emprnt.date_retour_anne&&emprnt.date_emprunte_mois!=emprnt.date_retour_mois){
				
				gg.dure_mois=abs(emprnt.date_retour_mois-emprnt.date_emprunte_mois);
				gg.dure_jour=((gg.dure_mois-1)*30)+gg.jour_demprunte+gg.jour_retour;
				
			}else{
				
				if(emprnt.date_emprunte_anne!=emprnt.date_retour_anne&&emprnt.date_emprunte_mois==emprnt.date_retour_mois){
					
					gg.dure_anne=abs(emprnt.date_retour_anne-emprnt.date_emprunte_anne);
					gg.dure_jour=(gg.dure_anne*365)+abs(emprnt.date_retour_jour-emprnt.date_emprunte_jour);
					
				}else{
					
					if(emprnt.date_emprunte_anne!=emprnt.date_retour_anne&&emprnt.date_emprunte_mois!=emprnt.date_retour_mois){
						
						gg.dure_mois=abs(emprnt.date_retour_mois-emprnt.date_emprunte_mois);
						gg.dure_anne=abs(emprnt.date_retour_anne-emprnt.date_emprunte_anne);
						gg.dure_jour=(gg.dure_anne*365)+((gg.dure_mois-1)*30)+gg.jour_demprunte+gg.jour_retour;
					}
				}
			}
		}
		return gg;			
	}
		
//definir la dure des emprunte

	void affichage_la_dure(){
		date x;
		int i=0;
		emprunte emprnt;
		FILE*femprnt=NULL;
		femprnt=fopen("Femprunte.txt","r");
		printf("\n\n                                        ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY);
        printf(" AFFICHAGE LES DUREE DES EMPRUNTES ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        printf("\n\n");
		while(fread(&emprnt,sizeof(emprunte),1,femprnt))
		{
			x=calcule_dure(emprnt);
			i=i+1;
			printf("\n\n ---------------------------------------------");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("\n");printf(" \n\n               'EMPRUNTE NUMERO %d' \n \n",i);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf(" \n");printf(" \n\n  - Le matricule  : %s \n\n",emprnt.matricule);
			printf(" \n");printf(" \n\n  - La cote : %s \n\n",emprnt.cote);
			
			printf(" \n");printf(" \n\n  - La duree d'emprunte : ");
			printf("%d",x.dure_jour);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf(" jours");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);				
			
			printf("\n\n");
			printf(" ---------------------------------------------");
			printf("\n\n");
			sleep(1);
	    }   
		fclose(femprnt); 
		if(i==0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n La liste des empruntes est vide");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		} 
		printf("\n\n++++++++++++++++++++++++++++++++++++++++++++++\n\n");		
		
		
	}
	
	
//procedure definir le maximum d'ouvrage emprunte

	void max_ouvrage_emprunte(){
		int max=0;
		int i=0;
		ouvrage ovrg,gg;
		FILE*fovrg;
		fovrg=fopen("Fouvrage.txt","r");
		while(fread(&ovrg,sizeof(ouvrage),1,fovrg)){
			if(ovrg.nbr_exmp_empr>max){
				i=1;
				strcpy(gg.cote,ovrg.cote);
				strcpy(gg.titre,ovrg.titre);
				gg.nbr_exmp=ovrg.nbr_exmp;
				gg.nbr_exmp_empr=ovrg.nbr_exmp_empr;
				max=ovrg.nbr_exmp_empr;
			}
		}
		fclose(fovrg);
		if(i==1){
		
			printf("\n\n ---------------------------------------------");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf(" \n");printf(" |\n |\n |               'Le maximum d'ouvrage a emprunter' \n |\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf(" |\n");printf(" |\n |\n | - Le Titre : %s \n |\n",gg.titre);
			printf(" |\n");printf(" |\n |\n | - La cote : %s \n |\n",gg.cote);
			printf(" |\n");printf(" |\n |\n | - Le nombre d'exemplaire : %d \n |\n",gg.nbr_exmp);
			printf(" |\n");printf(" |\n |\n | - Le nombre d'exemplaire emprunte : %d \n |\n",gg.nbr_exmp_empr);
			printf(" ---------------------------------------------");
			printf("\n\n");			
		}else{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n");printf("\n\n La liste des ouvrages est vide\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		} 
	}
	
//procedure retourner le nombre maximale de nombre exemplaire emprunte

	int return_max_ouvrage_emprunte(){
		int max=0;
		int i=0;
		ouvrage ovrg,gg;
		FILE*fovrg;
		fovrg=fopen("Fouvrage.txt","r");
		while(fread(&ovrg,sizeof(ouvrage),1,fovrg)){
			if(ovrg.nbr_exmp_empr>max){
				i=1;
				strcpy(gg.cote,ovrg.cote);
				strcpy(gg.titre,ovrg.titre);
				gg.nbr_exmp=ovrg.nbr_exmp;
				gg.nbr_exmp_empr=ovrg.nbr_exmp_empr;
				max=ovrg.nbr_exmp_empr;
			}
		}
		fclose(fovrg);
		return max;
	}	
	

//procedure definir le minimum d'ouvrage emprunte

	void min_ouvrage_emprunte(){
		int min;
		int i=0;
		int X=0;
		ouvrage ovrg,gg,ovrgmin;
		FILE*fovrg;
		fovrg=fopen("Fouvrage.txt","r");
		while(fread(&ovrg,sizeof(ouvrage),1,fovrg)&&X==0){
			X=1;
			strcpy(ovrgmin.cote,ovrg.cote);
			strcpy(ovrgmin.titre,ovrg.titre);
			ovrgmin.nbr_exmp=ovrg.nbr_exmp;
			ovrgmin.nbr_exmp_empr=ovrg.nbr_exmp_empr;				
			min=ovrgmin.nbr_exmp_empr;
		}
		while(fread(&ovrg,sizeof(ouvrage),1,fovrg)){
			if(ovrg.nbr_exmp_empr<min){
				i=1;
				strcpy(gg.cote,ovrg.cote);
				strcpy(gg.titre,ovrg.titre);
				gg.nbr_exmp=ovrg.nbr_exmp;
				gg.nbr_exmp_empr=ovrg.nbr_exmp_empr;
				min=ovrg.nbr_exmp_empr;
			}
		}
		fclose(fovrg);
		if(i==1){
		
			printf("\n\n ---------------------------------------------");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf(" \n");printf(" |\n |\n |               'Le minimum d'ouvrage a emprunter' \n |\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf(" |\n");printf(" |\n |\n | - Le Titre : %s \n |\n",gg.titre);
			printf(" |\n");printf(" |\n |\n | - La cote : %s \n |\n",gg.cote);
			printf(" |\n");printf(" |\n |\n | - Le nombre d'exemplaire : %d \n |\n",gg.nbr_exmp);
			printf(" |\n");printf(" |\n |\n | - Le nombre d'exemplaire emprunte : %d \n |\n",gg.nbr_exmp_empr);
			printf(" ---------------------------------------------");
			printf("\n\n");			
		}else{
			if(X==0){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("\n");printf("\n\n               'Le minimum d'ouvrage a emprunter' \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n");printf("\n\n La liste des ouvrages est vide\n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" ---------------------------------------------");
				printf("\n\n");	
			}else{
			printf("\n\n ---------------------------------------------");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf(" \n");printf(" |\n |\n |               'Le minimum d'ouvrage a emprunter' \n |\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf(" |\n");printf(" |\n |\n | - Le Titre : %s \n |\n",ovrgmin.titre);
			printf(" |\n");printf(" |\n |\n | - La cote : %s \n |\n",ovrgmin.cote);
			printf(" |\n");printf(" |\n |\n | - Le nombre d'exemplaire : %d \n |\n",ovrgmin.nbr_exmp);
			printf(" |\n");printf(" |\n |\n | - Le nombre d'exemplaire emprunte : %d \n |\n",ovrgmin.nbr_exmp_empr);
			printf(" ---------------------------------------------");
			printf("\n\n");	
			}					
		} 
	}	

//consulter la liste des penalites

	void consulter_penlites(){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("\n");printf(" \n\n                                      L'affichage de la liste des penalites \n \n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		int i=0;
		etudiant etd;
		FILE*fetd=NULL;
	    fetd=fopen("Fetudiant.txt","r");
	    while(fread(&etd,sizeof(etudiant),1,fetd)){
	    	if(strcmp(etd.type_abnmt,"C")==0 && etd.penalite>=7){
				i=i+1;
				printf("\n\n ---------------------------------------------");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n");printf(" \n\n               'PENALITE NUMERO %d' \n \n",i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("\n\n Le matricule : ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("%s\n\n",etd.matricule);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("\n\n La penalite : ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("%d \n\n",etd.penalite);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				sleep(1);
			}
		}
		fclose(fetd);
		if(i==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n");printf(" \n\n La liste des penalites est vide \n \n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);			
		}
		printf("\n\n ---------------------------------------------\n\n");
	}	
	
//procedure consulter l'ouvrage le plus solicite

	void consulter_ouvrage_sollicite(){

		int i=0;
		int max;
		ouvrage ovrg;
		max=return_max_ouvrage_emprunte()-2;
		FILE*fovrg=NULL;
		fovrg=fopen("Fouvrage.txt","r");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf(" \n");printf("\n\n                'Les ouvrages les plus solicites' \n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		while(fread(&ovrg,sizeof(ouvrage),1,fovrg)){
			
			if(ovrg.nbr_exmp_empr>=max){
				i=1;
				printf("\n\n ---------------------------------------------");
				printf(" |\n");printf(" |\n |\n | - Le Titre : %s \n |\n",ovrg.titre);
				printf(" |\n");printf(" |\n |\n | - La cote : %s \n |\n",ovrg.cote);
				printf(" |\n");printf(" |\n |\n | - Le nombre d'exemplaire : %d \n |\n",ovrg.nbr_exmp);
				printf(" |\n");printf(" |\n |\n | - Le nombre d'exemplaire emprunte : %d \n |\n",ovrg.nbr_exmp_empr);
				printf(" ---------------------------------------------");
				printf("\n\n");		
			}
		}
		fclose(fovrg);
		if(i==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf(" \n");printf("\n\n La liste des ouvrage est vide \n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf("\n\n++++++++++++++++++++++++++++++++++++++++++++++\n\n");			
		}	
	}	
	
//+++++++++++++++++++++++++++++++++++++++++++++++++++fonction main++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

int main() {
 
	int stay=1;
	while(stay==1)
	{   
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		printf("************************************************************************************************************************");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		
	    int retour=0;  
		int choice1;
		printf("\n\n                                         ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY);
        printf(" CHOISIR CE QUE VOUS VOULEZ FAIRE");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        printf("\n\n");				
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("\n\n 1 -");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf(" AJOUTER");	
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf(",");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("RETOURNER\n\n");			
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("\n\n 2 -");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf(" AFFICHER");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf(",");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("CONSULTER");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf(",");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("VERIFIER \n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("\n\n 3 -");	
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf(" MODIFIER");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf(",");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("SUPPRIMER \n\n");		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("\n\n Votre choix : ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		scanf("%d",&choice1);
		printf("\n\n");
			
		while(choice1!=1 && choice1!=2 && choice1!=3)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("\n\n Votre choix : ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			scanf("%d",&choice1);    
		}	        
		
		switch(choice1)
		{
			case 1:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				printf("************************************************************************************************************************");
				printf("\n\n                                              ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
		        printf("AJOUTER,RETOURNER");
		        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		        printf("\n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);			
				int choice2;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 1 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Ajouter un ouvrage \n\n");  
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 2 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Ajouter un etudiant \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 3 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Ajouter un emprunt \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 4 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Retourner un emprunt \n\n");				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 0 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" RETOUR \n\n");
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("\n\n Votre choix : ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        scanf("%d",&choice2);
		        while(choice2!=1 && choice2!=2 && choice2!=3 && choice2!=4 && choice2!=0)
				{
					
		        	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					printf("\n\n Votre choix : ");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					
		        	scanf("%d",&choice2);    
				}	        
		        switch(choice2){
		        	case 0:{
		        		retour=1;
						break;
					}
		        	case 1:{
		        		ouvrage ovrg;
		        		printf("\n\n Donner le titre : ");
		        		scanf(" %39[^\n]",ovrg.titre);
		        		printf("\n\n Donner la cote : ");
		        		scanf(" %39[^\n]",ovrg.cote);
		        		printf("\n\n Donner le nombre d'exemplaire : ");
		        		scanf("%d",&ovrg.nbr_exmp);
		        		printf("\n\n Donner le nombre d'exemplaire emprunte : ");
		        		scanf("%d",&ovrg.nbr_exmp_empr);
		        		while(ovrg.nbr_exmp_empr>ovrg.nbr_exmp){
		        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		        			printf("\n\n Le nombre d'exemplaire emprunter ne doit pas etre supperieur au nombre d'exemplaire '%d' \n\n",ovrg.nbr_exmp);
		        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			        		printf("\n Donner le nombre d'exemplaire emprunte : ");
			        		scanf("%d",&ovrg.nbr_exmp_empr);		        			
						}
		        		insertion_ouvrage(ovrg);
						break;
					}
		        	case 2:{
		        		etudiant etd;
		        		int choicetype;
		        		printf("\n\n Donner le matricule : ");
		        		scanf(" %19[^\n]",etd.matricule);
		        		printf("\n\n choisie le type d'abonement\n\n");
		        		printf("\n\n 1 - Premium\n\n");
		        		printf("\n\n 2 - Classic\n\n");
		        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		        		printf("\n\n Votre choix : ");
		        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        		scanf("%d",&choicetype);  		
		        		while(choicetype!=1 && choicetype!=2)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		        			printf("\n\n Votre choix : ");
		        			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        		    scanf("%d",&choicetype);    
						}
				
		        		switch(choicetype){
		        			case 1:{
		        				strcpy(etd.type_abnmt,"P");
		        				etd.penalite=0;
								break;
							}
							case 2:{
		        				strcpy(etd.type_abnmt,"C");
		        				printf("\n\n Donner la penalite : ");
		        				scanf("%d",&etd.penalite);
								break;
							}
						}
		        		insertion_etudiant(etd);
						break;
					}
					case 3:{
		        		emprunte emprnt;
		        		printf("\n\n Donner le matricule : ");
		        		scanf(" %39[^\n]",emprnt.matricule);
		        		printf("\n\n Donner la cote : ");
		        		scanf(" %99[^\n]",emprnt.cote);
		        		insertion_emprunte(emprnt);
						break;
					}
					case 4:{
						emprunte emprnt;
				        printf("\n\n Donner le matricule : ");
				        scanf(" %19[^\n]",emprnt.matricule);
				        printf("\n\n Donner la cote : ");
				        scanf(" %99[^\n]",emprnt.cote);	
						retourner_emprunt(emprnt.matricule,emprnt.cote);						
						break;
					}
									
				}
				break;
			}
			case 2:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				printf("************************************************************************************************************************");
				printf("\n\n                                              ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
		        printf("AFFICHER,CONSULTER,VERIFIER");
		        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		        printf("\n\n");				
				int choice2;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 1 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);   
				printf(" Afficher la liste des ouvrages \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 2 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Afficher la liste des etudiants \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 3 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Afficher la liste des empruntes \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 4 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Consulter un membre \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 5 -");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
				printf(" Consulter un emprunte \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 6 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Verifier la disponibilite des exemplaires \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 7 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Afficher la duree des empruntes \n\n");
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 8 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Afficher  le maximum d'ouvrage a emprunter \n\n");				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 9 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Afficher  le minimum d'ouvrage a emprunter \n\n");	
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 10 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Consulter la liste des penalites \n\n");								
								
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 11 -"); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Consulter les ouvrage les plus sollicites \n\n");									
							
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 0 - "); 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("RETOUR \n\n");
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("\n\n Votre choix : ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        scanf("%d",&choice2);
		        while(choice2!=1 && choice2!=2 && choice2!=3 && choice2!=4 && choice2!=5 && choice2!=6 && choice2!=7 && choice2!=8 && choice2!=9 && choice2!=10 && choice2!=11 && choice2!=0)
				{
		        	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					printf("\n\n Votre choix : ");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        	scanf("%d",&choice2);    
				}	        
		        
		        switch(choice2){
		        	
		        	case 0:{
		        		retour=1;
						break;
					}
					
		        	case 1:{
		        		affichage_ouvrage();
						break;
					}
					
					case 2:{
						affichage_etudiant();
						break;
					}
					
					case 3:{
						affichage_emprunte();
						break;
					}
					
					case 4:{
						etudiant etd;
						printf("\n\n Donner le matricule de membre a consulter : ");
		        		scanf(" %19[^\n]",etd.matricule);
						consulter_un_membre(etd.matricule);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
						printf("\n\n Les empruntes d'etudiant sont : \n\n");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						consulter_un_emprunt_par_maticule(etd.matricule);
						break;
					}
					
					case 5:{
						
						int choice3;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						printf("\n\n 1-");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						printf(" Consulter l'emprunte par le matricule d'etudiant\n\n");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						printf("\n\n 2-");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						printf(" Consulter l'emprunte par la cote de livre \n\n");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						printf("\n\n 3-");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						printf(" Consulter l'emprunte par la cote de livre et le matricule d'etudiant \n\n");						
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
						printf("\n\n Votre choix : ");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			        	scanf("%d",&choice3);
			        	while(choice3!=1 && choice3!=2  && choice3!=3)
						{
						
			        	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
						printf("\n\n Votre choix : ");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			        	scanf("%d",&choice3);
						    
						}	        
			        	switch(choice3){
			        		case 1:{
								emprunte emprnt;
								printf("\n\n Donner le matricule d'emprunte a consulter : ");
								scanf(" %19[^\n]",emprnt.matricule);
								consulter_un_emprunt_par_maticule(emprnt.matricule);		        			
								break;
							}
							case 2:{
								emprunte emprnt;
								printf("\n\n Donner la cote d'emprunte a consulter : ");
								scanf(" %99[^\n]",emprnt.cote);
								consulter_un_emprunt_par_cote(emprnt.cote);							
								break;
							}
							case 3:{
								emprunte emprnt;
								printf("\n\n Donner le matricule d'emprunte a consulter : ");
								scanf(" %19[^\n]",emprnt.matricule);	
								printf("\n\n Donner la cote d'emprunte a consulter : ");
								scanf(" %99[^\n]",emprnt.cote);
								consulter_un_emprunt(emprnt.cote,emprnt.matricule);														
								break;
							}
						}
						break;
					}
					
					case 6:{
						ouvrage ovrg;
						printf("\n\n Donner la cote d'ouvrage a verifier : ");
						scanf(" %99[^\n]",ovrg.cote);
						verification_disponibilite_ovrg(ovrg.cote);
						break;
					}
					case 7:{
						affichage_la_dure();
						break;
					}
					case 8:{
						max_ouvrage_emprunte();
						break;
					}
					case 9:{
						min_ouvrage_emprunte();
						break;
					}
					case 10:{
						consulter_penlites();
						break;
					}
					case 11:{
						consulter_ouvrage_sollicite();	
						break;
					}
				}
				
				break;
			}
			case 3:{ 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				printf("************************************************************************************************************************");
				printf("\n\n                                              ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
		        printf("MODIFIER,SUPPRIMER");
		        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		        printf("\n\n");			
				int choice2;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 1 -");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Modifier un membre \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 2 -");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Modifier un emprunte \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 3 -");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Supprimer un ouvrage \n\n");				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 4 -");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Supprimer un etudiant  \n\n");				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);		
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n 5 -");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" Supprimer un emprunte  \n\n");		
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);								
				printf("\n\n 0 -");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(" RETOUR  \n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("\n\n Votre choix : ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        scanf("%d",&choice2);
		        while(choice2!=1 && choice2!=2 && choice2!=3  && choice2!=4 && choice2!=5 && choice2!=0)
				{
		        	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					printf("\n\n Votre choix : ");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		        	scanf("%d",&choice2);    
				}	        
		        
		        switch(choice2){
		        	case 0:{
		        		retour=1;
						break;
					}
		        	case 3:{
		        		ouvrage ovrg;
				        printf("\n\n Donner la cote d'ouvrage a supprimer : ");
				        scanf(" %99[^\n]",ovrg.cote);
						suppression_ouvrage(ovrg.cote);
						break;
					}
					case 4:{
						etudiant etd;
				        printf("\n\n Donner le matricule d'etudiant a supprimer : ");
				        scanf(" %99[^\n]",etd.matricule);
						suppression_etudiant(etd.matricule);
						break;
					}
					case 5:{
						emprunte emprnt;
				        printf("\n\n Donner le matricule d'emprunt a supprimer: ");
				        scanf(" %19[^\n]",emprnt.matricule);
				        printf("\n\n Donner la cote d'emprunt a supprimer: ");
				        scanf(" %99[^\n]",emprnt.cote);	
						suppression_emprunte(emprnt.matricule,emprnt.cote);	        
						break;
					}
					case 1:{
						char matricule[20];
						int choicetype;
				        printf("\n\n Donner le matricule d'etudiant a modifier : ");
				        scanf(" %19[^\n]",matricule);
						modifier_un_membre(matricule);
						break;	
					}
					case 2:{
						emprunte emprnt;
				        printf("\n\n Donner le matricule d'emprunte a modifier : ");
				        scanf(" %19[^\n]",emprnt.matricule);
				        printf("\n\n Donner la cote d'emprunte a modifier : ");
				        scanf(" %99[^\n]",emprnt.cote);							
						modifier_un_emprunte(emprnt.matricule,emprnt.cote);
						break;
					}			
            	}
			}
		}
//		fflush(stdin);
		if(retour==0){
		printf("\n\n Voulez-vous continuer ?\n");
		printf("\n\n 1 - Oui\n");
		printf("\n 2 - Non\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("\n\n Votre choix : ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		scanf("%d",&stay);
		}
		printf("\n\n\n\n");
	}
	printf("\n\n++++++++++++++++++++++++++++++++++++");
	return 0;
}

