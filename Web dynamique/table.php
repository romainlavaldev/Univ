<html>
<head>
<link href="../css/styles.css" rel="stylesheet" />
</head>
<body>
<?php

function afficheTable($n){

	echo '<div clas="container"><div class="row"><div class="col-lg-8 mx-auto">';
			echo '<h2>';
			echo "Table de " . $n;
			echo '<ul>';
			for ($j = 0; $j <=10; $j++){
				echo "<li>" . $n . "*" . $j . " = " . $n*$j . "</li>";
			}
			echo '</ul>';
			
			echo "</div></div></div>";

}


if (isset($_POST['valider'])){
	if(!empty($_POST['min']) && !empty($_POST['max'])){
		$max = $_POST['max'];
		$min = $_POST['min'];
		if($max >= $min){
			for($i = $min; $i <= $max; $i++){
				afficheTable($i);
			}

		}
		else
		echo "Max est plus grand que Min !";
	}	
	else
	echo "Min ou Max non defini !";
}
else
echo "vous êtes arrivé ici par erreur !";


?>
</body>
</html>
