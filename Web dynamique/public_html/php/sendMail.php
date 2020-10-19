<?php

if(isset($_POST['valider'])){

	$corp = $_POST['corp'];
	$corp = $_POST['sujet'];

	if(!empty($corp) && !empty("sujet")){
		if(mail("romain.laval000@gmail.com",$sujet,$corp))
			echo "message envoyé";
		else
			echo "erreur";
	}
	else
	echo "Le corp ou le sujet est vide";
}
else
echo "vous êtes arrivé ici par erreur !";

?>
