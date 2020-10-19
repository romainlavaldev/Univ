<?php session_start(); ?>

<html>
<head>
<style>
table, th, td {
  border: 1px solid black;
  border-collapse: collapse;
}
</style>
<a href="../index.php">retour</a>
<h2><?php if (isset($_SESSION['prenom']) && !empty($_SESSION['prenom'])) {
	echo "Vous êtes " . $_SESSION['prenom'] . " !";
}else echo "Vous n'êtes personne"; ?> </h2>
</head>
<body>

<?php
	$repas = array("LUNdi" => "nuggets de Poulet", "MARDI" => "purée-Jambon", "mercredi" => "RISSOTO", "Jeudi" => "Steack-Frites", "Vendredi" => "PIZZA et salade verte");

	echo '<table> <tr> <th> Jour </th> <th> Plat </th>';
	foreach($repas as $jour => $plat){
		echo '<tr> <td>';
		echo strtoupper($jour);
		echo '</td> <td>';
		echo strtolower($plat);
		echo '</td> </tr>';
	}
	echo '</table>';
?>

</body>
</html>
