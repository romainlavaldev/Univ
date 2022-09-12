# encoding: UTF-8

##
# Auteur LeNomDeLEtudiant
# Version 0.1 : Date : Wed Nov 10 13:32:58 CET 2021
#

load "Mouvement.rb"
class Echeancier

	#@mouvements => Array contenants les mouvements

	def initialize
		@mouvements = Array.new
	end

	def vide
		@mouvements.empty?
	end

	def prochain
		if self.vide then
			raise("Pas de prochain dans l'echeancier car il est vide")
		end

		print "\n avant tri"
		print self
		print "\n"
		
		#Pour retirer le plus ancien -> trier le tableau par date croissante et prendre la premiere
		@mouvements.sort!

		
		print "\n apres tri"
		print self
		print "\n"

		@mouvements.shift
	end

	def enregistrer(mouvement)
		if mouvement.instance_of? Mouvement then
			@mouvements.append(mouvement)
			return self
		else
			raise "Ajout de pas Mouvement dans l'echeancier"
		end
	end

	def to_s
		@mouvements.collect do |m| 
			m.date
		end.join(" ")+		
		@mouvements.collect do |m| 
			m.class
		end.join(" ")
		
	end

end # Marqueur de fin de classe