# encoding: UTF-8

##
# Auteur LeNomDeLEtudiant
# Version 0.1 : Date : Wed Nov 10 14:44:43 CET 2021
#

class PosteSortie

	#@nbPiecesT
	#@attenteTotale
	#@attenteMax

	def initialize
		@nbPiecesT = 0
		@attenteTotale = 0
		@attenteMax = 0
	end

	#Traitement de la piece en sortie -> on met a jours les donées du poste de sortie
	def traiter(date, piece)
		@nbPiecesT += 1
		@attenteTotale += piece.attente
		if piece.attente > @attenteMax then
			@attenteMax = piece.attente
		end
	end

	def moyenneAttente
		if @nbPiecesT == 0 then
			return 0
		else
			@attenteTotale/@nbPiecesT
		end
	end

	def printStat
		print self.class," : ",@nbPiecesT," pièces traitées ; Attente max = ",@attenteMax,", Attente moy = ",moyenneAttente,"\n"
	end

end # Marqueur de fin de classe
