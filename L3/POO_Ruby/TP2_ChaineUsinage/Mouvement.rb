# encoding: UTF-8

##
# Auteur LeNomDeLEtudiant
# Version 0.1 : Date : Wed Nov 10 13:28:04 CET 2021
#

class Mouvement

	include Comparable
	#@piece => piece à laquelle on applique le mouvement
	#@poste => poste qui va recevoir le mouvement
	#@date => date à laquelle le mouvment doit être réalisé

	private_class_method :new
	def Mouvement.creer(date, piece, poste)
		new(date, piece, poste)
	end

	def initialize(date, piece, poste)
		@piece = piece
		@poste = poste
		@date = date
	end

	attr :piece, false
	attr :poste, false
	attr :date, false


	#On rend la classe triable par la date pour faciliter la recherche dans l'écheancier
	def <=>(other)
    	@date <=> other.date
  	end

end # Marqueur de fin de classe
