# encoding: UTF-8

##
# Auteur LeNomDeLEtudiant
# Version 0.1 : Date : Wed Nov 10 13:48:29 CET 2021
#

load "PosteTravail.rb"

class PosteConstant < PosteTravail

	#@tpsProcess => temps que le poste met à usiner une piece
	#@tpsActif => temps passé à usiner les pieces
	#@tpsInactif => temps passé sans pièce à usiner
	#@echeancier => echeancier de la chaine
	#@posteSuivant => poste suivant dans la chaine
	#@finPiecePrecedente => date de fin de l'usinage de la piece precedente

	def PosteConstant.creer(echeancier, suivant, tpsProcess)
		new(echeancier, suivant, tpsProcess)
	end

	def initialize(echeancier, suivant, tpsProcess)
		super(echeancier, suivant)
		@tpsProcess = tpsProcess
	end

	
	def printStat
		print "Travail (Constant-",@numPoste," (",@tpsProcess,"))"
		super
		@posteSuivant.printStat
	end

	def traiter(date, piece)

		super(date, piece)
		
	end

	

end # Marqueur de fin de classe
