<?php session_start(); ?>

<html>
<head>
<style>
table, th, td {
  border: 1px solid black;
  border-collapse: collapse;
}

.rouge{
 background-color: red
}

.bleu{
 background-color: green
}
</style>
<a href="index.php">retour</a>
<h2><?php if (isset($_SESSION['prenom']) && !empty($_SESSION['prenom'])) {
	echo "Vous êtes " . $_SESSION['prenom'] . " !";
}else echo "Vous n'êtes personne"; ?></h2>
</head>
<body>

<?php


	echo '<table> <tr> <th> Variable </th> <th> Valeur </th>';
	$classCouleur="rouge";
	foreach($_SERVER as $key => $value){
		if(!empty($value)){
			echo '<tr class="' . $classCouleur . '"> <td>';
			echo $key;
			echo '</td> <td>';
			echo $value;
			echo '</td> </tr>';
			if(strcmp($classCouleur, "rouge") == 0) $classCouleur = "bleu";
			else $classCouleur = "rouge";
		}
	}
	echo '</table>';
?>


</body>
</html>
