<?php
if(isset($_POST['rvalider'])){
	if(!empty($_POST['rlogin']) && !empty($_POST['rpass']) && !empty($_POST['rage']) && !empty($_POST['rnom']) && !empty($_POST['rprenom']) && !empty($_POST['remail'])){
		$login = $_POST['rlogin'];
		$con = mysqli_connect('info.univ-lemans.fr', 'l2infoetu', 'webdyn72', 'l2info');
		if(!$con){
			echo 'Y\'a eu un problème dans l\'équation !';
		}else{
			$query = "select nom from utilisateurs where login = \"" . $login . "\"";
			$res = mysqli_query($con,$query);
			$res = mysqli_fetch_array($res);
			if(!empty($res[0])){
				echo 't\'est déjà dans la base en fait ...';
			}else{
				echo 'on va t\'ajouter !';
				$query = "insert into utilisateurs (nom,prenom,age,login,password,email) values (\"" . $_POST['rnom'] . "\",\"" . $_POST['rprenom'] . "\"," . $_POST['rage'] . ",\"" . $_POST['rlogin'] . "\",\"" . $_POST['rpass'] . "\",\"" . $_POST['remail'] . "\")";
				mysqli_query($con, $query);
			}
		}
	}
	else{
	echo 'Faut remplir tous les champs quand même ...';
	}
}
else echo 'C\'est pas bien là';
?>

