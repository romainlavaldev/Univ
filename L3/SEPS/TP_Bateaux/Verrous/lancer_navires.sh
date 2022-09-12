if( test $# -ne 3 ) then 
    echo "Usage: $0 <fichier mer> <nb_bateaux> <energie>"
    exit 1
fi 

fich_mer=$1
nb_bateaux=$2
energie=$3

i=0
marque='A'
while( test $i -lt $nb_bateaux ) do 
   for marque in A B C D E F G H I J K L M N O P Q R S T U V W X Y Z ; do 
       if( test $i -ge $nb_bateaux ) then
           exit 0
       fi
       echo "lancement $i: bateau $marque"
       ./navire $fich_mer $marque $energie &
       i=`expr $i + 1`
   done 
done 

