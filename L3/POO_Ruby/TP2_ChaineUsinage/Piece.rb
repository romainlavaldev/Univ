# encoding: UTF-8

##
# Auteur LeNomDeLEtudiant
# Version 0.1 : Date : Wed Nov 10 13:25:57 CET 2021
#

class Piece

	#@attente => duree totale d'attente de la piece
	#@dureeTraitement => duree de traitement de la piece

	private_class_method :new
	def Piece.creer(dureeTraitement)
		new(dureeTraitement)
	end

	def initialize(dureeTraitement)
		@dureeTraitement = dureeTraitement
		@attente = 0
	end

	attr :attente, false
	attr :dureeTraitement, false

	def attendre(duree)
		@attente += duree
	end

end # Marqueur de fin de classe
