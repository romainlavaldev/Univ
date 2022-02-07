<?php

$USD = 1.17;
$CAD = 1.57;

if(isset($_GET['valider'])){
	if(!empty($_GET['somme']) && is_numeric($_GET['somme'])){
		$somme = $_GET['somme'];
		$deviseD = $_GET['deviseDepart'];
		$deviseA = $_GET['deviseArrive'];

		if($somme > 0){
			if(strcmp($deviseD,"eu") == 0){
				if(strcmp($deviseA,"eu") == 0){
					$res = $somme;
				}
				if(strcmp($deviseA,"us") == 0){
					$res = $somme * $USD;
				}
				if(strcmp($deviseA,"ca") == 0){
					$res = $somme * $CAD;
				}
			}
			if(strcmp($deviseD,"us") == 0){
				if(strcmp($deviseA,"eu") == 0){
					$res = $somme / $USD;
				}
				if(strcmp($deviseA,"us") == 0){
					$res = $somme;
				}
				if(strcmp($deviseA,"ca") == 0){
					$res = $somme / $USD * $CAD;
				}
			}
			if(strcmp($deviseD,"ca") == 0){
				if(strcmp($deviseA,"eu") == 0){
					$res = $somme / $CAD;
				}
				if(strcmp($deviseA,"us") == 0){
					$res = $somme / $CAD * $USD;
				}
				if(strcmp($deviseA,"ca") == 0){
					$res = $somme;
				}
			}
			echo $somme . " " . $deviseD . " = " . $res . " " . $deviseA;
		}
		else
		echo "la somme vaut est < 0 !";

	}
	else
	echo "la somme n'est pas definie";
}
else
echo "Vous êtes arrivé ici par erreur !";


?>
