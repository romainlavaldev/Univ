# encoding: UTF-8

##
# Auteur LeNomDeLEtudiant
# Version 0.1 : Date : Wed Nov 10 14:51:33 CET 2021
#

load "Piece.rb"
load "Mouvement.rb"
load "Echeancier.rb"
load "PosteConstant.rb"
load "PosteVariable.rb"
load "PosteTravail.rb"
load "PosteSortie.rb"

	class ChaineUsinage 
          def ChaineUsinage.test() 
               e = Echeancier.new()
               sortie = PosteSortie.new()
               p3 = PosteConstant.creer(e, sortie, 10)
               p2 = PosteVariable.creer(e, p3)
               p1 = PosteConstant.creer(e, p2, 6)
               p1.printStat
               e.enregistrer(Mouvement.creer(1, Piece.creer(3), p1))
               e.enregistrer(Mouvement.creer(2, Piece.creer(7), p1))
               e.enregistrer(Mouvement.creer(3, Piece.creer(5), p1))
               while (!e.vide()) do
                    m = e.prochain()
                    m.poste().traiter(m.date(), m.piece())
               end
               p1.printStat()
          end
	end

ChaineUsinage.test