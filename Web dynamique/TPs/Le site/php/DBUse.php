<?php
  session_start();
?>
<a href="../index.php">retour</a>
<?php
if(isset($_POST['valider'])){
	if(isset($_POST['login']) and isset($_POST['pass'])){
		$login = $_POST['login'];
		$pass = $_POST['pass'];
		$con = mysqli_connect('info.univ-lemans.fr', $login, $pass, 'l2info');
		if(!$con){
			echo 'Y\'a eu un problème dans l\'équation !';
		}else{
			echo 'Vous êtes connecté !!!';
			$query = "select prenom from utilisateurs where nom = \"" . $_POST['nom'] ."\" and prenom = \"" . $_POST['prenom'] . "\"";
			$res = mysqli_query($con,$query);
			$res = mysqli_fetch_array($res);
			if(!empty($res[0])){
				echo 'Bonjour ' . $res[0] . ' ! Vous êtes bien dans la base de donées';
				$_SESSION['prenom'] = $res[0];
			}else{
				echo 'Votre nom n\'apparait pas dans la base de données ......';
			}
		}
	}
	else{
	echo 'C\'est pas bon là';
	}
}
else echo 'C\'est pas bien là';
mysqli_close($con);
?>
