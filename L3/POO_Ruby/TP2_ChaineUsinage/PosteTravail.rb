# encoding: UTF-8

##
# Auteur LeNomDeLEtudiant
# Version 0.1 : Date : Wed Nov 10 14:25:02 CET 2021
#

class PosteTravail
	@@NumPosteGene = 1 #=> générateur du num de poste

	#@tpsProcess
	#@nbPiecesT => nombres de pièces traitées
	#@tpsActif => temps passé à usiner les pieces
	#@tpsInactif => temps passé sans pièce à usiner
	#@echeancier => echeancier de la chaine
	#@posteSuivant => poste suivant dans la chaine
	#@finPiecePrecedente => date de fin de l'usinage de la piece precedente
	#@numPoste => numéro du poste

	private_class_method :new
	def PosteTravail.creer(echeancier, suivant)
		new(echeancier, suivant)
	end

	def initialize(echeancier, suivant)
		@nbPiecesT = 0
		@tpsActif = 0
		@tpsInactif = 0
		@echeancier = echeancier
		@posteSuivant = suivant
		@finPiecePrecedente = -1
		@numPoste = @@NumPosteGene
		@@NumPosteGene += 1
	end

	
	def printStat
		print " : Nb pièces traitées = ",@nbPiecesT,", Activité = ",@tpsActif,", Inactivité = ",@tpsInactif,"\n"
	end

	def traiter(date, piece)

		#Initialisation de la derniere piece usinée dans le cas où il n'y en avait pas encore
		if @finPiecePrecedente == -1 then
			@finPiecePrecedente = date
		end

	
		if date < @finPiecePrecedente then
			#Si la machine n'est pas libre
			dateFin = @finPiecePrecedente + @tpsProcess
			#La piece va attendre que la place se libère + son temps de process
			piece.attendre((@finPiecePrecedente - date))
		else
			#Si la machine est libre
			dateFin = date + @tpsProcess
			@tpsInactif += date - @finPiecePrecedente
		end
		
		@tpsActif += @tpsProcess

		#On ajoute le nouveau Mouvement dans l'echeancier
		@echeancier.enregistrer(Mouvement.creer(dateFin, piece, @posteSuivant))
		
		@finPiecePrecedente = dateFin
		@nbPiecesT += 1
	end
end # Marqueur de fin de classe
